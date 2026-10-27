#include "GuiCanvas.hpp"
#include "GuiMemory.hpp"
#include "Rounding.hpp"
#include "Trigonometry.hpp"
#include "DisplayGeometry.hpp"
#include "../native/verified/module_memory.hpp"
namespace reconstruction::gui {
// Runtime observation; canvas state index is signed at +0x2288, stride 0x110.
void saveCanvas_73a70(std::uint8_t *c) {
    auto n=read<std::int32_t>(c,0x2288);
    if(n>31) return;
    if(n>0) {
        recovered_memory_copy(c+0x88+std::int64_t(n)*0x110,c+0x88+std::int64_t(n-1)*0x110,0x110);
        n=read<std::int32_t>(c,0x2288);
    }
    write(c,0x2288,std::uint32_t(n)+1u);
}
void restoreCanvas_749a0(std::uint8_t *c) {
    const auto n=read<std::int32_t>(c,0x2288);
    if(n>=2) write(c,0x2288,std::uint32_t(n)-1u);
}
static __m128 pair(const std::uint8_t *p) { return _mm_castpd_ps(_mm_load_sd(reinterpret_cast<const double*>(p))); }
static void storePair(std::uint8_t *p,__m128 v) { _mm_storel_pi(reinterpret_cast<__m64*>(p),v); }
void translateCanvas_74b40(std::uint8_t *c,float x,float y) {
    auto *s=c+std::int64_t(read<std::int32_t>(c,0x2288))*0x110;
    const auto a=pair(s+0x38),b=pair(s+0x40),translation=pair(s+0x48),zero=_mm_setzero_ps();
    storePair(s+0x38,_mm_add_ps(_mm_mul_ps(b,zero),a));
    storePair(s+0x40,_mm_add_ps(_mm_mul_ps(zero,a),b));
    auto result=_mm_add_ps(_mm_mul_ps(_mm_set1_ps(x),a),_mm_mul_ps(_mm_set1_ps(y),b));
    storePair(s+0x48,_mm_add_ps(result,translation));
}
void scaleCanvas_74d40(std::uint8_t *c,float x,float y) {
    auto *s=c+std::int64_t(read<std::int32_t>(c,0x2288))*0x110;
    const auto a=pair(s+0x38),b=pair(s+0x40),translation=pair(s+0x48),zero=_mm_setzero_ps();
    const auto scaledB=_mm_mul_ps(_mm_set1_ps(y),b),zeroB=_mm_mul_ps(b,zero);
    auto moved=_mm_add_ps(_mm_mul_ps(a,zero),zeroB);
    moved=_mm_add_ps(moved,translation);
    const auto twiceA=_mm_movelh_ps(a,a);
    const auto factors=_mm_set_ps(0,0,x,x);
    const auto four=_mm_add_ps(_mm_movelh_ps(zeroB,scaledB),_mm_mul_ps(factors,twiceA));
    _mm_storeu_ps(reinterpret_cast<float*>(s+0x38),four);
    storePair(s+0x48,moved);
}
void scissorCanvas_75630(std::uint8_t *c,float x,float y,float w,float h,const std::uint8_t *image) {
    auto *s=c+std::int64_t(read<std::int32_t>(c,0x2288))*0x110;
    const auto size=_mm_max_ps(_mm_setzero_ps(),_mm_set_ps(0,0,h,w));
    float sizes[4]; _mm_storeu_ps(sizes,size);
    const auto half=read<float>(image,0x2b5370);
    const auto centerX=add(mul(sizes[0],half),x),centerY=add(mul(sizes[1],half),y);
    const auto a=pair(s+0x38),b=pair(s+0x40),translation=pair(s+0x48),zero=_mm_setzero_ps();
    const auto first=_mm_add_ps(_mm_mul_ps(b,zero),a);
    const auto second=_mm_add_ps(_mm_mul_ps(zero,a),b);
    _mm_storeu_ps(reinterpret_cast<float*>(s+0x50),_mm_movelh_ps(first,second));
    auto center=_mm_add_ps(_mm_mul_ps(_mm_set1_ps(centerX),a),_mm_mul_ps(_mm_set1_ps(centerY),b));
    center=_mm_add_ps(center,translation);
    // The incoming saved XMM6 low pair is overwritten; only its high size pair reaches storage.
    auto extents=_mm_mul_ps(_mm_movelh_ps(zero,size),_mm_loadu_ps(reinterpret_cast<const float*>(image+0x2b5380)));
    _mm_storeu_ps(reinterpret_cast<float*>(s+0x60),_mm_castpd_ps(_mm_move_sd(_mm_castps_pd(extents),_mm_castps_pd(center))));
}
bool containsPoint_a0a0(const float *r,std::uint64_t p) {
    return recovered_rectangle_contains_a0a0(r,p)!=0;
}
bool intersectsRect_a0e0(const float *a,const float *b) {
    if(a[0]>add(b[0],b[2]) || b[0]>add(a[0],a[2]) || a[1]>add(b[1],b[3])) return false;
    return !(b[1]>add(a[1],a[3]));
}
float *insetRect_a130(float *out,const float *r,float inset) {
    return recovered_rectangle_inset_a130(out,r,inset);
}
float *roundRect_a160(float *out,const float *r,const std::uint8_t *image) {
    const auto x=r[0],y=r[1];
    const auto rx=recovered_round_float_b1fb0(x,image),ry=recovered_round_float_b1fb0(y,image);
    const auto rw=recovered_round_float_b1fb0(r[2],image),rh=recovered_round_float_b1fb0(r[3],image);
    out[0]=rx;out[1]=ry;out[2]=rw;out[3]=rh;return out;
}
std::uint64_t rectPosition_a1e0(const float *r) { return read<std::uint64_t>(r); }
float interpolate_a260(float start,float end,float amount,const std::uint8_t *image) {
    return recovered_limited_lerp_a260(start,end,amount,image);
}
void *imagePaint_75520(void *out,std::uint8_t*,float x,float y,float w,float h,float rotation,std::int32_t id,float alpha,const std::uint8_t *image) {
    auto *p=static_cast<std::uint8_t*>(out);
    _mm_storeu_ps(reinterpret_cast<float*>(p+0x20),_mm_setzero_ps()); write(p,0x30,std::uint64_t(0));
    const auto cosine=recovered_cosine_b3590(rotation,image);
    const auto sine=recovered_sine_b1cf0(rotation,image);
    write(p,0,cosine);write(p,4,sine);
    write(p,8,std::bit_cast<float>(std::bit_cast<std::uint32_t>(sine)^read<std::uint32_t>(image,0x2b5350)));
    write(p,0xc,cosine);write(p,0x10,x);write(p,0x14,y);write(p,0x18,w);write(p,0x1c,h);
    write(p,0x48,id);write(p,0x38,read<std::uint64_t>(image,0x2b5360));
    write(p,0x40,1.0f);write(p,0x44,alpha);
    write(p,0x28,read<std::uint64_t>(p,0x38));write(p,0x30,read<std::uint32_t>(p,0x40));write(p,0x34,read<std::uint32_t>(p,0x44));
    return out;
}
void fillPaint_74f60(std::uint8_t *c,const void *paint) {
    auto *s=c+std::int64_t(read<std::int32_t>(c,0x2288))*0x110;
    const auto *p=static_cast<const float*>(paint);
    const auto p0=_mm_loadu_ps(p),p1=_mm_loadu_ps(p+4),p2=_mm_loadu_ps(p+8),p3=_mm_loadu_ps(p+12);
    _mm_storeu_ps(reinterpret_cast<float*>(s-0x64),p1);_mm_storeu_ps(reinterpret_cast<float*>(s-0x74),p0);
    _mm_storeu_ps(reinterpret_cast<float*>(s-0x38),_mm_loadu_ps(p+15));
    _mm_storeu_ps(reinterpret_cast<float*>(s-0x44),p3);_mm_storeu_ps(reinterpret_cast<float*>(s-0x54),p2);
    auto a=pair(s+0x38),b=pair(s+0x40),translation=pair(s+0x48);
    auto moved=_mm_add_ps(_mm_mul_ps(_mm_set1_ps(read<float>(s,-0x64)),a),_mm_mul_ps(_mm_set1_ps(read<float>(s,-0x60)),b));
    moved=_mm_add_ps(moved,translation);
    const auto matrix=_mm_loadu_ps(reinterpret_cast<const float*>(s-0x74));
    auto transformed=_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps(matrix,matrix,0xa0),_mm_movelh_ps(a,a)),_mm_mul_ps(_mm_shuffle_ps(matrix,matrix,0xf5),_mm_movelh_ps(b,b)));
    _mm_storeu_ps(reinterpret_cast<float*>(s-0x74),transformed);storePair(s-0x64,moved);
}
void strokeColor_74de0(std::uint8_t *c,const void *rgba,const std::uint8_t *image) {
    const auto color=_mm_loadu_ps(static_cast<const float*>(rgba));
    auto *s=c+std::int64_t(read<std::int32_t>(c,0x2288))*0x110;
    const auto zero=_mm_setzero_ps();
    _mm_storeu_ps(reinterpret_cast<float*>(s-0x10),zero);_mm_storeu_ps(reinterpret_cast<float*>(s+0x10),zero);_mm_storeu_ps(reinterpret_cast<float*>(s),zero);
    write(s,0x20,std::uint32_t(0));_mm_storeu_ps(reinterpret_cast<float*>(s-0x28),_mm_loadu_ps(reinterpret_cast<const float*>(image+0x2b5280)));
    write(s,-0x18,std::uint64_t(0));write(s,-4,1.0f);
    _mm_storeu_ps(reinterpret_cast<float*>(s),color);_mm_storeu_ps(reinterpret_cast<float*>(s+0x10),color);
}
void lineWidth_749e0(std::uint8_t *c,float w) { write(c+std::int64_t(read<std::int32_t>(c,0x2288))*0x110,0x24,w); }
void moveTo_75bf0(std::uint8_t *c,float x,float y,const drawing::FontDependencies &deps) { float commands[]{0,x,y};drawing::appendCommands_75c30(c,commands,3,deps); }
void lineTo_75ec0(std::uint8_t *c,float x,float y,const drawing::FontDependencies &deps) { float commands[]{1,x,y};drawing::appendCommands_75c30(c,commands,3,deps); }
void rectPath_76950(std::uint8_t *c,float x,float y,float w,float h,const drawing::FontDependencies &deps) {
    const auto bottom=add(h,y),right=add(w,x);
    float commands[]{0,x,y,1,x,bottom,1,right,bottom,1,right,y,3};drawing::appendCommands_75c30(c,commands,13,deps);
}
void roundedRect_769d0(std::uint8_t*c,float x,float y,float w,float h,float radius,const std::uint8_t*image,const drawing::FontDependencies&deps){
    drawing::roundedRectVarying_76a10(c,x,y,w,h,radius,radius,radius,radius,image,deps);
}
}
