#include "FontRasterizer.hpp"
#include "ByteStrings.hpp"
#include "ColorSpace.hpp"
#include <cstring>
#include <immintrin.h>

namespace reconstruction::font {
namespace {
template<class T> T load(const void *p){T v;std::memcpy(&v,p,sizeof v);return v;}
template<class T> void store(void *p,T v){std::memcpy(p,&v,sizeof v);}
float constant(const std::uint8_t *image,std::size_t rva){return load<float>(image+rva);}
float add(float a,float b){return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float sub(float a,float b){return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float mul(float a,float b){return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float div(float a,float b){return _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float sqrtFloat(float a){return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(a)));}
double sqrtDouble(float a){return _mm_cvtsd_f64(_mm_sqrt_sd(_mm_setzero_pd(),_mm_cvtss_sd(_mm_setzero_pd(),_mm_set_ss(a))));}
double addDouble(double a,double b){return _mm_cvtsd_f64(_mm_add_sd(_mm_set_sd(a),_mm_set_sd(b)));}
float narrow(double a){return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),_mm_set_sd(a)));}
std::int32_t wrapAdd(std::int32_t a,std::int32_t b){return std::int32_t(std::uint32_t(a)+std::uint32_t(b));}
void point(Point *p,std::int32_t *count,float x,float y){
    const auto index=*count;
    if(p){store(&p[index].x,x);store(&p[index].y,y);}
    *count=wrapAdd(index,1);
}
void swapEdge(Edge *a,Edge *b){
    // The captured copies preserve all twenty bytes, including direction.
    const auto tail=load<std::uint32_t>(reinterpret_cast<std::uint8_t*>(a)+16);
    const auto front=_mm_loadu_ps(reinterpret_cast<float*>(a));
    store(reinterpret_cast<std::uint8_t*>(a)+16,load<std::uint32_t>(reinterpret_cast<std::uint8_t*>(b)+16));
    _mm_storeu_ps(reinterpret_cast<float*>(a),_mm_loadu_ps(reinterpret_cast<float*>(b)));
    store(reinterpret_cast<std::uint8_t*>(b)+16,tail);
    _mm_storeu_ps(reinterpret_cast<float*>(b),front);
}
}
void flattenQuadratic_7d1d0(Point *points,std::int32_t *count,float x0,float y0,
    float x1,float y1,float x2,float y2,float flatness,std::int32_t depth,
    const std::uint8_t *image){
    if(depth>16)return;
    const float quarter=constant(image,0x2b5b70),half=constant(image,0x2b5b80);
    const float packedHalf=constant(image,0x2b5b90);
    depth=wrapAdd(depth,1);
    for(;;){
        const float mx=mul(add(add(add(x1,x1),x0),x2),quarter);
        const float my=mul(add(add(add(y1,y1),y0),y2),quarter);
        const float dx=sub(mul(add(x2,x0),half),mx);
        const float dy=sub(mul(add(y2,y0),half),my);
        const float distance=add(mul(dy,dy),mul(dx,dx));
        // Native UCOMISS/JBE takes the terminal branch for unordered values.
        if(!(distance>flatness)){point(points,count,x2,y2);return;}
        const float leftX=mul(add(x0,x1),half),leftY=mul(add(y1,y0),half);
        flattenQuadratic_7d1d0(points,count,x0,y0,leftX,leftY,mx,my,flatness,depth,image);
        x1=mul(add(x1,x2),packedHalf);y1=mul(add(y1,y2),packedHalf);
        x0=mx;y0=my;depth=wrapAdd(depth,1);
        if(depth==18)return;
    }
}
void flattenCubic_7d3b0(Point *points,std::int32_t *count,float x0,float y0,
    float x1,float y1,float x2,float y2,float x3,float y3,float flatness,
    std::int32_t depth,const std::uint8_t *image){
    if(depth>16)return;
    const float half=constant(image,0x2b5ba0),packedHalf=constant(image,0x2b5bb0);
    const std::int32_t terminal=depth>=18?depth:17;
    depth=wrapAdd(depth,1);
    for(;;){
        const float dx03=sub(x3,x0),dy03=sub(y3,y0);
        const float longLength=sqrtFloat(add(mul(dx03,dx03),mul(dy03,dy03)));
        const float dx23=sub(x3,x2),dy23=sub(y3,y2);
        const double length23=sqrtDouble(add(mul(dx23,dx23),mul(dy23,dy23)));
        const float dx01=sub(x1,x0),dy01=sub(y1,y0),dx12=sub(x2,x1),dy12=sub(y2,y1);
        const double length01=sqrtDouble(add(mul(dx01,dx01),mul(dy01,dy01)));
        const double length12=sqrtDouble(add(mul(dx12,dx12),mul(dy12,dy12)));
        const float length=narrow(addDouble(addDouble(length01,length12),length23));
        if(!(sub(mul(length,length),mul(longLength,longLength))>flatness)){
            point(points,count,x3,y3);return;
        }
        const float x01=mul(add(x0,x1),packedHalf),x23=mul(add(x3,x2),packedHalf);
        const float y01=mul(add(y0,y1),packedHalf),y23=mul(add(y3,y2),packedHalf);
        const float x12=mul(add(x1,x2),half),y12=mul(add(y1,y2),half);
        const float x012=mul(add(x12,x01),packedHalf),x123=mul(add(x12,x23),packedHalf);
        const float y012=mul(add(y12,y01),packedHalf),y123=mul(add(y12,y23),packedHalf);
        const float mx=mul(add(x123,x012),half),my=mul(add(y123,y012),half);
        flattenCubic_7d3b0(points,count,x0,y0,x01,y01,x012,y012,mx,my,flatness,depth,image);
        x0=mx;y0=my;x1=x123;y1=y123;x2=x23;y2=y23;
        const auto oldDepth=depth;depth=wrapAdd(depth,1);
        if(wrapAdd(oldDepth,-terminal+1)==1)return;
    }
}
void sortEdges_7d720(Edge *edges,std::int32_t count){
    while(count>12){
        const std::int32_t middle=std::int32_t(std::uint32_t(count)>>1);
        const float a=edges[0].y0,b=edges[middle].y0,c=edges[count-1].y0;
        // CMPNLT includes unordered; these XOR predicates select the pivot.
        if((!(a<b))==(b<c)){
            const auto pivot=((!(a<c))!=(b<c))?0:count-1;
            swapEdge(edges+pivot,edges+middle);
        }
        swapEdge(edges,edges+middle);
        std::int32_t i=1,j=count-1;
        for(;;){
            const float pivot=edges[0].y0;
            while(pivot>edges[i].y0)++i;
            while(edges[j].y0>pivot)--j;
            if(i>=j)break;
            swapEdge(edges+i,edges+j);++i;--j;
        }
        if(count-i<=j){
            sortEdges_7d720(edges+i,count-i);
            count=j;
        }else{
            sortEdges_7d720(edges,j);
            edges+=i;count-=i;
        }
    }
}
namespace {
float fromInteger(std::int32_t n){return _mm_cvtss_f32(_mm_cvtsi32_ss(_mm_setzero_ps(),n));}
std::int32_t truncate(float f){return _mm_cvttss_si32(_mm_set_ss(f));}
float minimum(float a,float b){return _mm_cvtss_f32(_mm_min_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float maximum(float a,float b){return _mm_cvtss_f32(_mm_max_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float toggleSign(float f,const std::uint8_t *image){
    return _mm_cvtss_f32(_mm_xor_ps(_mm_set_ss(f),_mm_loadu_ps(reinterpret_cast<const float*>(image+0x2b4cd0))));
}
struct Scratch {
    std::uint8_t *owner;
    const RasterDependencies &dependencies;
    void error(){
        const auto target=load<std::uint64_t>(owner+0x5270);
        if(target)dependencies.calls(target,load<std::uint64_t>(owner+0x5278),2);
    }
    std::uint8_t *allocate(std::uint32_t bytes,bool testBase=true){
        const auto old=load<std::int32_t>(owner+0x5088);
        const auto aligned=(bytes+15u)&~15u;
        const auto next=wrapAdd(old,std::int32_t(aligned));
        if(next>=0x17701){error();return nullptr;}
        auto *base=load<std::uint8_t*>(owner+0x5080);
        store(owner+0x5088,next);
        if(testBase&&!base)return nullptr;
        return reinterpret_cast<std::uint8_t*>(std::uintptr_t(base)+std::intptr_t(old));
    }
};
struct ActiveEdge {
    ActiveEdge *next;
    float x,dx,dy,direction,start,end;
};
static_assert(sizeof(ActiveEdge)==32);
struct ActivePool {
    Scratch &scratch;
    std::uint8_t *chunk=nullptr;
    std::int32_t remaining=0;
    ActiveEdge *free=nullptr;
    ActiveEdge *allocate(){
        if(free){auto *p=free;free=p->next;return p;}
        if(remaining){--remaining;return reinterpret_cast<ActiveEdge*>(chunk+8+std::intptr_t(remaining)*32);}
        const auto used=load<std::int32_t>(scratch.owner+0x5088);
        if(used>=0x112f1){scratch.error();return nullptr;}
        auto *base=load<std::uint8_t*>(scratch.owner+0x5080);
        store(scratch.owner+0x5088,wrapAdd(used,0x6410));
        if(!base)return nullptr;
        auto *next=base+std::intptr_t(used);store(next,chunk);chunk=next;remaining=799;
        return reinterpret_cast<ActiveEdge*>(chunk+8+799*32);
    }
    void release(ActiveEdge *p){p->direction=0.f;p->next=free;free=p;}
};
void insertionSort(Edge *edges,std::int32_t count){
    for(std::int32_t i=1;i<count;++i){
        const Edge value=edges[i];auto j=i;
        while(j>0&&edges[j-1].y0>value.y0){edges[j]=edges[j-1];--j;}
        if(j!=i)edges[j]=value;
    }
}
void clippedEdge(float *scan,std::int32_t x,const ActiveEdge *e,float x0,float y0,
    float x1,float y1,float one,float negativeHalf){
    if(y0==y1||y0>e->end||y1<e->start)return;
    if(y0<e->start){x0=add(x0,div(mul(sub(x1,x0),sub(e->start,y0)),sub(y1,y0)));y0=e->start;}
    if(y1>e->end){x1=add(x1,div(mul(sub(x1,x0),sub(e->end,y1)),sub(y1,y0)));y1=e->end;}
    const float left=fromInteger(x),right=fromInteger(wrapAdd(x,1));
    const float signedHeight=mul(sub(y1,y0),e->direction);
    if(x0<=left&&x1<=left)scan[x]=add(signedHeight,scan[x]);
    else if(!(x0>=right&&x1>=right)){
        const float fraction=add(mul(add(sub(x1,left),sub(x0,left)),negativeHalf),one);
        scan[x]=add(mul(fraction,signedHeight),scan[x]);
    }
}
void fillActive(float *scan,float *fill,std::int32_t width,ActiveEdge *edge,
    float top,float bottom,const std::uint8_t *image){
    const float one=constant(image,0x2b4ce0),negativeHalf=constant(image,0x2b4cec),half=constant(image,0x2b4cf0);
    const float widthFloat=fromInteger(width);
    for(auto *e=edge;e;e=e->next){
        const float x0=e->x,dx=e->dx;
        if(dx==0.f){
            if(!(x0<widthFloat))continue;
            if(x0>=0.f){
                const auto x=truncate(x0);
                clippedEdge(scan,x,e,x0,top,x0,bottom,one,negativeHalf);
                clippedEdge(fill-1,wrapAdd(x,1),e,x0,top,x0,bottom,one,negativeHalf);
            }else clippedEdge(fill-1,0,e,x0,top,x0,bottom,one,negativeHalf);
            continue;
        }
        const float xBottomUnclipped=add(dx,x0);
        const float xTop=e->start>top?add(mul(sub(e->start,top),dx),x0):x0;
        const float xBottom=e->end<bottom?add(mul(sub(e->end,top),dx),x0):xBottomUnclipped;
        if(xTop>=0.f&&xBottom>=0.f&&xTop<widthFloat&&xBottom<widthFloat){
            float sy0=maximum(e->start,top),sy1=minimum(e->end,bottom);
            auto first=truncate(xTop),last=truncate(xBottom);
            if(first==last){
                const float signedFraction=mul(add(mul(add(sub(xBottom,fromInteger(first)),sub(xTop,fromInteger(first))),negativeHalf),one),e->direction);
                scan[first]=add(mul(signedFraction,sub(sy1,sy0)),scan[first]);
                fill[first]=add(mul(sub(sy1,sy0),e->direction),fill[first]);
                continue;
            }
            float leftX=xTop,rightX=xBottom,dy=e->dy,origin=x0;
            if(xTop>xBottom){
                const float flipped0=add(sub(top,sy0),bottom),flipped1=add(sub(top,sy1),bottom);
                sy1=flipped0;sy0=flipped1;dy=toggleSign(dy,image);
                leftX=xBottom;rightX=xTop;origin=xBottomUnclipped;
                first=truncate(leftX);last=truncate(rightX);
            }
            const float cross=add(mul(sub(fromInteger(wrapAdd(first,1)),origin),dy),top);
            float area=mul(sub(cross,sy0),e->direction);
            const float firstFraction=add(mul(add(sub(leftX,fromInteger(first)),one),negativeHalf),one);
            scan[first]=add(mul(firstFraction,area),scan[first]);
            const auto span=wrapAdd(last,-wrapAdd(first,1));
            if(span>0){
                const float step=mul(dy,e->direction),halfStep=mul(step,half);
                for(auto x=wrapAdd(first,1);x<last;++x){scan[x]=add(add(halfStep,area),scan[x]);area=add(area,step);}
            }
            const float finalY=add(mul(dy,fromInteger(span)),cross);
            const float lastFraction=mul(add(mul(sub(rightX,fromInteger(last)),negativeHalf),one),e->direction);
            scan[last]=add(add(mul(sub(sy1,finalY),lastFraction),area),scan[last]);
            fill[last]=add(mul(sub(sy1,sy0),e->direction),fill[last]);
        }else{
            // The captured slow path clips every crossed pixel independently.
            for(std::int32_t x=0;x<width;++x){
                const float left=fromInteger(x),right=fromInteger(wrapAdd(x,1));
                const float yLeft=add(div(sub(left,x0),dx),top);
                const float yRight=add(div(sub(right,x0),dx),top);
                if(x0<left&&xBottomUnclipped>right){
                    clippedEdge(scan,x,e,x0,top,left,yLeft,one,negativeHalf);
                    clippedEdge(scan,x,e,left,yLeft,right,yRight,one,negativeHalf);
                    clippedEdge(scan,x,e,right,yRight,xBottomUnclipped,bottom,one,negativeHalf);
                }else if(xBottomUnclipped<left&&x0>right){
                    clippedEdge(scan,x,e,x0,top,right,yRight,one,negativeHalf);
                    clippedEdge(scan,x,e,right,yRight,left,yLeft,one,negativeHalf);
                    clippedEdge(scan,x,e,left,yLeft,xBottomUnclipped,bottom,one,negativeHalf);
                }else if(x0<left&&xBottomUnclipped>left){
                    clippedEdge(scan,x,e,x0,top,left,yLeft,one,negativeHalf);
                    clippedEdge(scan,x,e,left,yLeft,xBottomUnclipped,bottom,one,negativeHalf);
                }else if(xBottomUnclipped<left&&x0>left){
                    clippedEdge(scan,x,e,x0,top,left,yLeft,one,negativeHalf);
                    clippedEdge(scan,x,e,left,yLeft,xBottomUnclipped,bottom,one,negativeHalf);
                }else if(x0<right&&xBottomUnclipped>right){
                    clippedEdge(scan,x,e,x0,top,right,yRight,one,negativeHalf);
                    clippedEdge(scan,x,e,right,yRight,xBottomUnclipped,bottom,one,negativeHalf);
                }else if(xBottomUnclipped<right&&x0>right){
                    clippedEdge(scan,x,e,x0,top,right,yRight,one,negativeHalf);
                    clippedEdge(scan,x,e,right,yRight,xBottomUnclipped,bottom,one,negativeHalf);
                }else clippedEdge(scan,x,e,x0,top,xBottomUnclipped,bottom,one,negativeHalf);
            }
        }
    }
}
}
void rasterize_64e50(Bitmap *bitmap,float flatness,Vertex *vertices,std::int32_t vertexCount,
    float scaleX,float scaleY,float shiftX,float shiftY,std::int32_t offsetX,
    std::int32_t offsetY,std::int32_t invert,std::uint8_t *owner,const RasterDependencies &d){
    if(vertexCount<=0)return;
    std::int32_t contours=0;
    for(std::int32_t i=0;i<vertexCount;++i)if(vertices[i].type==1)contours=wrapAdd(contours,1);
    if(contours==0)return;
    Scratch scratch{owner,d};
    auto *lengths=reinterpret_cast<std::int32_t*>(scratch.allocate(std::uint32_t(contours)*4));
    if(!lengths)return;
    const float tolerance=div(flatness,minimum(scaleY,scaleX));flatness=mul(tolerance,tolerance);
    Point *points=nullptr;std::int32_t pointCount=0;
    for(int pass=0;pass<2;++pass){
        if(pass){points=reinterpret_cast<Point*>(scratch.allocate(std::uint32_t(pointCount)*8));if(!points)return;}
        pointCount=0;std::int32_t contour=-1,start=0;float x=0.f,y=0.f;
        for(std::int32_t i=0;i<vertexCount;++i){
            const auto v=vertices[i];
            switch(v.type){
            case 1:
                if(contour>=0)lengths[contour]=wrapAdd(pointCount,-start);
                contour=wrapAdd(contour,1);start=pointCount;x=fromInteger(v.x);y=fromInteger(v.y);
                point(points,&pointCount,x,y);break;
            case 2:x=fromInteger(v.x);y=fromInteger(v.y);point(points,&pointCount,x,y);break;
            case 3:
                flattenQuadratic_7d1d0(points,&pointCount,x,y,fromInteger(v.controlX),fromInteger(v.controlY),fromInteger(v.x),fromInteger(v.y),flatness,0,d.image);
                x=fromInteger(v.x);y=fromInteger(v.y);break;
            case 4:
                flattenCubic_7d3b0(points,&pointCount,x,y,fromInteger(v.controlX),fromInteger(v.controlY),fromInteger(v.controlX1),fromInteger(v.controlY1),fromInteger(v.x),fromInteger(v.y),flatness,0,d.image);
                x=fromInteger(v.x);y=fromInteger(v.y);break;
            }
        }
        lengths[contour]=wrapAdd(pointCount,-start);
    }
    std::int32_t total=0;for(std::int32_t i=0;i<contours;++i)total=wrapAdd(total,lengths[i]);
    if(invert)scaleY=toggleSign(scaleY,d.image);
    auto *edges=reinterpret_cast<Edge*>(scratch.allocate(std::uint32_t(total)*20+20));
    if(!edges)return;
    std::int32_t edgeCount=0,base=0;
    for(std::int32_t contour=0;contour<contours;++contour){
        auto previous=wrapAdd(lengths[contour],-1);
        for(std::int32_t i=0;i<lengths[contour];++i){
            const Point a=points[base+previous],b=points[base+i];
            if(a.y!=b.y){
                const bool forward=invert?a.y>b.y:b.y>a.y;
                const Point first=forward?a:b,last=forward?b:a;
                Edge *e=edges+edgeCount;e->direction=forward?1:0;
                e->x0=add(mul(first.x,scaleX),shiftX);e->y0=add(mul(first.y,scaleY),shiftY);
                e->x1=add(mul(last.x,scaleX),shiftX);e->y1=add(mul(last.y,scaleY),shiftY);
                edgeCount=wrapAdd(edgeCount,1);
            }
            previous=i;
        }
        base=wrapAdd(base,lengths[contour]);
    }
    sortEdges_7d720(edges,edgeCount);insertionSort(edges,edgeCount);
    float localScan[129];float *scan=localScan;
    if(bitmap->width>=65)scan=reinterpret_cast<float*>(scratch.allocate(std::uint32_t(bitmap->width)*8+4,false));
    edges[edgeCount].y0=add(fromInteger(wrapAdd(offsetY,bitmap->height)),constant(d.image,0x2b4ce0));
    if(bitmap->height<=0)return;
    float *fill=scan+bitmap->width;ActiveEdge *active=nullptr;ActivePool pool{scratch};
    Edge *edge=edges;
    const float xOffset=fromInteger(offsetX),one=constant(d.image,0x2b4ce0);
    std::int32_t y=offsetY;
    for(std::int32_t row=0;row<bitmap->height;++row,y=wrapAdd(y,1)){
        const float top=fromInteger(y),bottom=add(top,one);
        recovered_bytes_fill_ab890(scan,0,std::uint64_t(std::int64_t(bitmap->width)*4));
        recovered_bytes_fill_ab890(fill,0,std::uint64_t(std::int64_t(bitmap->width)*4+4));
        for(auto **link=&active;*link;){auto *a=*link;if(top>=a->end){*link=a->next;pool.release(a);}else link=&a->next;}
        while(bottom>=edge->y0){
            if(edge->y0!=edge->y1){
                if(auto *a=pool.allocate()){
                    a->dx=div(sub(edge->x1,edge->x0),sub(edge->y1,edge->y0));
                    a->dy=a->dx==0.f?0.f:div(one,a->dx);
                    a->x=sub(add(mul(a->dx,sub(top,edge->y0)),edge->x0),xOffset);
                    a->direction=constant(d.image,edge->direction?0x2b4ce4:0x2b4ce8);
                    a->start=edge->y0;a->end=edge->y1;a->next=nullptr;
                    if(row==0&&offsetY!=0&&top>a->end)a->end=top;
                    a->next=active;active=a;
                }
            }
            ++edge;
        }
        fillActive(scan,fill+1,bitmap->width,active,top,bottom,d.image);
        float sum=0.f;
        for(std::int32_t x=0;x<bitmap->width;++x){
            sum=add(sum,fill[x]);float coverage=add(scan[x],sum);
            coverage=_mm_cvtss_f32(_mm_and_ps(_mm_set_ss(coverage),_mm_loadu_ps(reinterpret_cast<const float*>(d.image+0x2b4d00))));
            auto value=truncate(add(mul(coverage,constant(d.image,0x2b4d10)),constant(d.image,0x2b4cf0)));
            if(value>=255)value=255;
            bitmap->pixels[std::int64_t(bitmap->stride)*row+x]=std::uint8_t(value);
        }
        for(auto *a=active;a;a=a->next)a->x=add(a->dx,a->x);
    }
}
void makeGlyphBitmap_66f00(std::uint8_t *font,std::uint8_t *output,std::int32_t width,
    std::int32_t height,std::int32_t stride,float scaleX,float scaleY,float shiftX,
    float shiftY,std::int32_t glyph,const RasterDependencies &d){
    auto *shape=d.incomingShapePointer;
    const auto count=d.getGlyphShape_62bb0(d.context,font,glyph,&shape);
    std::int32_t x0=0,y0,x1,y1;
    std::int32_t offsetX=0,offsetY=0;
    if(d.getGlyphBox_63cf0(d.context,font,glyph,&x0,&y0,&x1,&y1)){
        offsetX=truncate(recovered_floor_b2a70(add(mul(fromInteger(x0),scaleX),shiftX),d.image));
        offsetY=truncate(recovered_floor_b2a70(add(mul(fromInteger(std::int32_t(0u-std::uint32_t(y1))),scaleY),shiftY),d.image));
    }
    if(width==0||height==0)return;
    Bitmap bitmap;bitmap.width=width;bitmap.height=height;bitmap.stride=stride;bitmap.pixels=output;
    rasterize_64e50(&bitmap,constant(d.image,0x2b4d28),shape,count,scaleX,scaleY,shiftX,shiftY,offsetX,offsetY,1,load<std::uint8_t*>(font),d);
}
}
