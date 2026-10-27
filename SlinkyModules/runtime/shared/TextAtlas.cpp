#include "TextAtlas.hpp"
#include "ByteStrings.hpp"
#include <bit>
#include <cstring>
#include <emmintrin.h>
#include <intrin.h>
namespace reconstruction::drawing {
namespace {
using W=std::uint64_t;
template<class T>T read(const void *p){T v;std::memcpy(&v,p,sizeof v);return v;}
template<class T>void write(void *p,T v){std::memcpy(p,&v,sizeof v);_ReadWriteBarrier();}
std::int32_t signed32(std::uint32_t v){return std::bit_cast<std::int32_t>(v);}
W address(const void *p){return reinterpret_cast<std::uintptr_t>(p);}
std::uint8_t *pointer(W p){return reinterpret_cast<std::uint8_t *>(std::uintptr_t(p));}
std::ptrdiff_t indexOffset(std::uint32_t index){return std::ptrdiff_t(signed32(index))*4;}
}
// RVA79EB0. The next texture slot, signed index reloads and wrapped DWORD
// doubling preserve the captured NanoVG-style atlas growth routine.
std::uint32_t allocateTextAtlas_79eb0(std::uint8_t *canvas,const TextAtlasDependencies &d){
    auto *font=pointer(read<W>(canvas+0x22a8));
    const auto x=read<std::uint32_t>(font+0x50),endX=read<std::uint32_t>(font+0x58);
    const auto width=endX-x;
    if(signed32(endX)>signed32(x)){
        const auto y=read<std::uint32_t>(font+0x54),endY=read<std::uint32_t>(font+0x5c);
        if(signed32(endY)>signed32(y)){
            const auto height=endY-y;
            write(font+0x50,read<W>(font));write(font+0x58,W(0));
            const auto current=read<std::uint32_t>(canvas+0x22c0);
            const auto texture=read<std::uint32_t>(canvas+0x22b0+indexOffset(current));
            if(texture)d.calls(read<W>(canvas+0x28),read<W>(canvas),texture,x,y,width,height,read<W>(font+0x48));
        }
    }
    auto index=read<std::uint32_t>(canvas+0x22c0);
    if(signed32(index)>2)return 0;
    std::uint32_t dimensions[2]={d.incomingQueryWidth,d.incomingQueryHeight};
    auto texture=read<std::uint32_t>(canvas+0x22b4+indexOffset(index));
    if(texture){
        d.calls(read<W>(canvas+0x30),read<W>(canvas),texture,address(dimensions),address(dimensions+1));
    }else{
        texture=read<std::uint32_t>(canvas+0x22b0+indexOffset(index));
        d.calls(read<W>(canvas+0x30),read<W>(canvas),texture,address(dimensions),address(dimensions+1));
        if(signed32(dimensions[0])>signed32(dimensions[1]))dimensions[1]+=dimensions[1];
        else dimensions[0]+=dimensions[0];
        if(signed32(dimensions[0])>=0x801||signed32(dimensions[1])>=0x801)dimensions[0]=dimensions[1]=0x800;
        const auto created=std::uint32_t(d.calls(read<W>(canvas+0x18),read<W>(canvas),1,dimensions[0],dimensions[1],0,0));
        index=read<std::uint32_t>(canvas+0x22c0);
        write(canvas+0x22b4+indexOffset(index),created);
    }
    write(canvas+0x22c0,read<std::uint32_t>(canvas+0x22c0)+1);
    resetTextAtlas_6f380(pointer(read<W>(canvas+0x22a8)),dimensions[0],dimensions[1],d);
    return 1;
}

// RVA6F380. Font/atlas/cache state is reset in native order. Allocation and
// actual drawing-driver targets remain explicit caller-owned frame services.
std::uint32_t resetTextAtlas_6f380(std::uint8_t *font,std::uint32_t width,std::uint32_t height,const TextAtlasDependencies &d){
    if(!font)return 0;
    if(signed32(read<std::uint32_t>(font+0x50))<signed32(read<std::uint32_t>(font+0x58))&&signed32(read<std::uint32_t>(font+0x54))<signed32(read<std::uint32_t>(font+0x5c))){
        const auto target=read<W>(font+0x28);
        if(target)d.calls(target,read<W>(font+0x10),address(font+0x50),read<W>(font+0x48));
        write(font+0x50,read<W>(font));write(font+0x58,W(0));
    }
    const auto vertexCount=read<std::uint32_t>(font+0x5078);
    if(signed32(vertexCount)>0){
        const auto target=read<W>(font+0x30);
        if(target)d.calls(target,read<W>(font+0x10),address(font+0x78),address(font+0x2078),address(font+0x4078),vertexCount);
        write(font+0x5078,std::uint32_t(0));
    }
    const auto resizeTarget=read<W>(font+0x20);
    if(resizeTarget&&std::uint32_t(d.calls(resizeTarget,read<W>(font+0x10),width,height))==0)return 0;
    auto *atlas=pointer(read<W>(font+0x68));
    write(atlas,width);write(atlas+4,height);
    auto *nodes=pointer(read<W>(atlas+8));write(nodes,std::uint32_t(0));write(nodes+4,std::uint16_t(width));write(atlas+0x10,std::uint32_t(1));
    const auto size=W(std::int64_t(signed32(height*width)));
    auto *pixels=pointer(d.calls(0x13cf90,read<W>(font+0x48),size));write(font+0x48,address(pixels));
    if(!pixels)return 0;
    recovered_bytes_fill_ab890(pixels,0,size);
    write(font+0x50,width);write(font+0x54,height);write(font+0x58,W(0));
    if(signed32(read<std::uint32_t>(font+0x74))>0){
        auto *table=pointer(read<W>(font+0x60));
        for(W i=0;;++i){
            auto *entry=pointer(read<W>(table+8*i));write(entry+0x10c,std::uint32_t(0));
            recovered_bytes_fill_ab890(entry+0x110,0xff,0x400);
            if(std::int64_t(i+1)>=std::int64_t(signed32(read<std::uint32_t>(font+0x74))))break;
        }
    }
    write(font,width);write(font+4,height);
    const auto dimensions=_mm_cvtepi32_ps(_mm_set_epi32(0,0,signed32(height),signed32(width)));
    const auto inverse=_mm_div_ps(_mm_loadu_ps(reinterpret_cast<const float *>(d.image+0x2b4f60)),dimensions);
    _mm_storel_epi64(reinterpret_cast<__m128i *>(font+0x40),_mm_castps_si128(inverse));_ReadWriteBarrier();
    std::uint32_t x=d.incomingResetX,y=d.incomingResetY;
    if(std::uint32_t(d.calls(0x7dd90,read<W>(font+0x68),2,2,address(&x),address(&y)))){
        auto *data=pointer(read<W>(font+0x48));
        const auto offset=read<std::uint32_t>(font)*y+x;
        auto *point=data+std::ptrdiff_t(signed32(offset));write(point,std::uint16_t(0xffff));
        write(point+std::ptrdiff_t(signed32(read<std::uint32_t>(font))),std::uint16_t(0xffff));
        const auto lowX=read<std::uint32_t>(font+0x50),lowY=read<std::uint32_t>(font+0x54);
        write(font+0x50,signed32(lowX)>=signed32(x)?x:lowX);
        write(font+0x54,signed32(lowY)>=signed32(y)?y:lowY);
        const auto highX=read<std::uint32_t>(font+0x58);x+=2;write(font+0x58,signed32(highX)>signed32(x)?highX:x);
        const auto highY=read<std::uint32_t>(font+0x5c);y+=2;write(font+0x5c,signed32(highY)>signed32(y)?highY:y);
    }
    return 1;
}
}
