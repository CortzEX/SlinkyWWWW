#include "PathTessellation.hpp"
#include "Trigonometry.hpp"
#include "ScalarCeiling.hpp"
#include <bit>
#include <cstring>
#include <immintrin.h>

namespace reconstruction::drawing {
namespace {
template<class T>T load(const void *p,std::uint64_t at=0) {
    T v;std::memcpy(&v,static_cast<const std::uint8_t *>(p)+at,sizeof(v));return v;
}
PathCache *cache(std::uint8_t *canvas){return load<PathCache *>(canvas,0x2290);}
float constant(const PathDependencies &d,std::uint32_t rva){return load<float>(d.image,rva);}
float add(float a,float b){return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float sub(float a,float b){return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float mul(float a,float b){return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float div(float a,float b){return _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float min(float a,float b){return _mm_cvtss_f32(_mm_min_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float max(float a,float b){return _mm_cvtss_f32(_mm_max_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float neg(float x){return std::bit_cast<float>(std::bit_cast<std::uint32_t>(x)^0x80000000);}
float nativeAbsolute(float x) {
    const __m128 original=_mm_set_ss(x),opposite=_mm_set_ss(neg(x));
    const __m128 choose=_mm_cmple_ss(opposite,original);
    return _mm_cvtss_f32(_mm_or_ps(_mm_and_ps(choose,original),_mm_andnot_ps(choose,opposite)));
}
std::int32_t integer(float f){return _mm_cvttss_si32(_mm_set_ss(f));}
std::int32_t wrap(std::uint32_t v){return std::bit_cast<std::int32_t>(v);}
std::int32_t grown(std::int32_t count,std::int32_t capacity) {
    return wrap(static_cast<std::uint32_t>(count)+static_cast<std::uint32_t>(capacity/2)+1);
}
std::uint64_t allocationSize(std::int32_t count,std::uint32_t stride) {
    return static_cast<std::uint64_t>(static_cast<std::int64_t>(count))*stride;
}
template<class T>T *indexed(T *base,std::int64_t index) {
    return reinterpret_cast<T *>(reinterpret_cast<std::uintptr_t>(base)+
        static_cast<std::uint64_t>(index)*sizeof(T));
}
TessellatedPath *lastPath(PathCache *c) {
    if(c->pathCount<=0)return nullptr;
    auto *end=indexed(c->paths,c->pathCount);
    return reinterpret_cast<std::uintptr_t>(end)==56?nullptr:indexed(end,-1);
}
void addPath(std::uint8_t *canvas,const PathDependencies &d) {
    auto *c=cache(canvas);auto count=c->pathCount;
    auto *paths=c->paths;
    if(count>=c->pathCapacity) {
        const auto capacity=grown(count,c->pathCapacity);
        paths=static_cast<TessellatedPath *>(d.resize_13cf90(d.context,paths,allocationSize(capacity,56)));
        if(!paths)return;
        c=cache(canvas);c->paths=paths;c->pathCapacity=capacity;count=c->pathCount;
    }
    auto *path=indexed(paths,count);std::memset(path,0,56);
    c=cache(canvas);path->first=c->pointCount;path->winding=1;
    c->pathCount=wrap(static_cast<std::uint32_t>(c->pathCount)+1);
}
float normalize(float &dx,float &dy,float threshold,float one) {
    const float length=_mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(add(mul(dx,dx),mul(dy,dy)))));
    if(length>threshold) {const float inverse=div(one,length);dx=mul(dx,inverse);dy=mul(dy,inverse);}
    return length;
}
PathVertex *temporaryVertices(std::uint8_t *canvas,std::int32_t count,const PathDependencies &d) {
    auto *c=cache(canvas);
    if(count<=c->vertexCapacity)return c->vertices;
    const auto capacity=wrap((static_cast<std::uint32_t>(count)+255)&0xffffff00u);
    auto *vertices=static_cast<PathVertex *>(d.resize_13cf90(d.context,c->vertices,allocationSize(capacity,16)));
    if(!vertices)return nullptr;
    c=cache(canvas);c->vertices=vertices;c->vertexCapacity=capacity;return vertices;
}
void vertex(PathVertex *&dst,float x,float y,float u,float v=1) {*dst={x,y,u,v};++dst;}
struct Pair {float x,y;};
void chooseBevel(bool bevel,const PathPoint *p0,const PathPoint *p1,float width,Pair &a,Pair &b) {
    if(bevel) {
        a={add(mul(p0->dy,width),p1->x),sub(p1->y,mul(p0->dx,width))};
        b={add(mul(p1->dy,width),p1->x),sub(p1->y,mul(p1->dx,width))};
    } else {
        a={add(mul(p1->miterX,width),p1->x),add(mul(p1->miterY,width),p1->y)};b=a;
    }
}
}

void addPoint_93eb0(std::uint8_t *canvas,float x,float y,std::uint32_t flags,const PathDependencies &d) {
    auto *c=cache(canvas);auto *path=lastPath(c);if(!path)return;
    auto count=c->pointCount;
    if(path->count>0 && count>0) {
        auto *p=indexed(c->points,static_cast<std::uint32_t>(count)-1);
        const float dx=sub(x,p->x),dy=sub(y,p->y),tolerance=load<float>(canvas,0x229c);
        if(mul(tolerance,tolerance)>add(mul(dx,dx),mul(dy,dy))) {p->flags|=static_cast<std::uint8_t>(flags);return;}
    }
    auto *points=c->points;
    if(count>=c->pointCapacity) {
        const auto capacity=grown(count,c->pointCapacity);
        points=static_cast<PathPoint *>(d.resize_13cf90(d.context,points,allocationSize(capacity,32)));
        if(!points)return;
        c=cache(canvas);c->points=points;c->pointCapacity=capacity;count=c->pointCount;
    }
    auto *p=indexed(points,count);std::memset(p,0,32);p->x=x;p->y=y;p->flags=static_cast<std::uint8_t>(flags);
    c=cache(canvas);c->pointCount=wrap(static_cast<std::uint32_t>(c->pointCount)+1);
    path->count=wrap(static_cast<std::uint32_t>(path->count)+1);
}

void tessellateBezier_94000(std::uint8_t *canvas,float x1,float y1,float x2,float y2,
    float x3,float y3,float x4,float y4,std::int32_t level,std::uint32_t flags,const PathDependencies &d) {
    if(level>10)return;
    const float dx=sub(x4,x1),dy=sub(y4,y1);
    const float d2=nativeAbsolute(sub(mul(sub(x2,x4),dy),mul(sub(y2,y4),dx)));
    const float d3=nativeAbsolute(sub(mul(sub(x3,x4),dy),mul(sub(y3,y4),dx)));
    const float distance=add(d3,d2);
    if(mul(add(mul(dx,dx),mul(dy,dy)),load<float>(canvas,0x2298))>mul(distance,distance)) {
        addPoint_93eb0(canvas,x4,y4,flags,d);return;
    }
    const float half=constant(d,0x2b6060);
    const float x12=mul(add(x1,x2),half),y12=mul(add(y1,y2),half);
    const float x23=mul(add(x2,x3),half),y23=mul(add(y2,y3),half);
    const float x34=mul(add(x4,x3),half),y34=mul(add(y4,y3),half);
    const float x123=mul(add(x23,x12),half),y123=mul(add(y23,y12),half);
    const float x234=mul(add(x23,x34),half),y234=mul(add(y23,y34),half);
    const float x1234=mul(add(x234,x123),half),y1234=mul(add(y234,y123),half);
    const auto next=wrap(static_cast<std::uint32_t>(level)+1);
    tessellateBezier_94000(canvas,x1,y1,x12,y12,x123,y123,x1234,y1234,next,0,d);
    tessellateBezier_94000(canvas,x1234,y1234,x234,y234,x34,y34,x4,y4,next,flags,d);
}

void flattenPaths_774d0(std::uint8_t *canvas,const PathDependencies &d) {
    auto *c=cache(canvas);if(c->pathCount>0)return;
    std::uint32_t offset=0;
    while(wrap(offset)<load<std::int32_t>(canvas,0x7c)) {
        const float *commands=load<float *>(canvas,0x70);const auto command=integer(commands[offset]);
        switch(command) {
        case 0:addPath(canvas,d);commands=load<float *>(canvas,0x70);[[fallthrough]];
        case 1:addPoint_93eb0(canvas,commands[offset+1],commands[offset+2],1,d);offset+=3;break;
        case 2: {
            auto *current=cache(canvas);
            if(current->pointCount>0) {
                auto *end=indexed(current->points,current->pointCount);
                if(reinterpret_cast<std::uintptr_t>(end)!=32) {
                    auto *p=indexed(end,-1);
                    tessellateBezier_94000(canvas,p->x,p->y,commands[offset+1],commands[offset+2],
                        commands[offset+3],commands[offset+4],commands[offset+5],commands[offset+6],0,1,d);
                }
            }offset+=7;break;
        }
        case 3:if(auto *p=lastPath(cache(canvas)))p->closed=1;++offset;break;
        case 4:if(auto *p=lastPath(cache(canvas)))p->winding=integer(commands[offset+1]);offset+=2;break;
        default:++offset;break;
        }
    }
    std::memcpy(c->bounds,d.image+0x2b5580,16);
    const float half=constant(d,0x2b5590),threshold=constant(d,0x2b5594),one=constant(d,0x2b5598);
    for(std::int64_t j=0;j<c->pathCount;++j) {
        auto *path=indexed(c->paths,j);auto *points=indexed(c->points,path->first);
        auto *previous=indexed(points,static_cast<std::int64_t>(path->count)-1);
        const float dx=sub(points->x,previous->x),dy=sub(points->y,previous->y),tolerance=load<float>(canvas,0x229c);
        if(mul(tolerance,tolerance)>add(mul(dx,dx),mul(dy,dy))) {
            path->count=wrap(static_cast<std::uint32_t>(path->count)-1);previous=indexed(previous,-1);path->closed=1;
        }
        if(path->count>2) {
            float area=0;
            for(std::int32_t i=2;i<path->count;++i) {
                const auto &a=points[i-1],&b=points[i];
                const float cross=sub(mul(sub(b.x,points->x),sub(a.y,points->y)),
                    mul(sub(b.y,points->y),sub(a.x,points->x)));
                area=add(area,cross);
            }
            area=mul(area,half);
            if((path->winding==1 && 0>area)||(path->winding==2 && area>0)) {
                for(std::int32_t i=0,k=path->count-1;i<k;++i,--k) {
                    const auto p=points[i];points[i]=points[k];points[k]=p;
                }
            }
        }
        for(std::int32_t i=0;i<path->count;++i) {
            auto *next=indexed(points,i);float px=sub(next->x,previous->x),py=sub(next->y,previous->y);
            const float length=normalize(px,py,threshold,one);
            previous->dx=px;previous->dy=py;previous->length=length;
            c->bounds[0]=min(c->bounds[0],previous->x);c->bounds[1]=min(c->bounds[1],previous->y);
            c->bounds[2]=max(c->bounds[2],previous->x);c->bounds[3]=max(c->bounds[3],previous->y);previous=next;
        }
    }
}

void calculateJoins_942f0(std::uint8_t *canvas,float width,std::uint32_t join,float miter,const PathDependencies &d) {
    auto *c=cache(canvas);const auto count=c->pathCount;auto *points=c->points;auto *paths=c->paths;
    const float one=constant(d,0x2b6080),half=constant(d,0x2b60a0),threshold=constant(d,0x2b60a4);
    const float maximum=constant(d,0x2b60a8),minimum=constant(d,0x2b60ac),inverse=width>0?div(one,width):0;
    for(std::int64_t i=0;i<count;++i) {
        auto *path=indexed(paths,i);auto *first=indexed(points,path->first);const auto n=path->count;
        auto *previous=indexed(first,static_cast<std::int64_t>(n)-1);path->bevelCount=0;std::uint32_t left=0;
        for(std::int32_t j=0;j<n;++j) {
            auto *p=indexed(first,j);
            p->miterX=mul(add(previous->dy,p->dy),half);
            p->miterY=mul(sub(neg(p->dx),previous->dx),half);
            const float squared=add(mul(p->miterX,p->miterX),mul(p->miterY,p->miterY));
            if(squared>threshold) {const float scale=min(maximum,div(one,squared));p->miterX=mul(p->miterX,scale);p->miterY=mul(p->miterY,scale);}
            p->flags&=1;
            const float cross=sub(mul(previous->dy,p->dx),mul(previous->dx,p->dy));
            if(cross>0){++left;p->flags|=2;}
            const float limit=max(minimum,mul(min(previous->length,p->length),inverse));
            if(one>mul(mul(squared,limit),limit))p->flags|=8;
            if((p->flags&1) && ((join&~2u)==1 || one>mul(mul(squared,miter),miter)))p->flags|=4;
            if(p->flags&12)path->bevelCount=wrap(static_cast<std::uint32_t>(path->bevelCount)+1);
            previous=p;
        }
        path->convex=left==static_cast<std::uint32_t>(n);
    }
}

PathVertex *bevelJoin_945c0(PathVertex *dst,const PathPoint *p0,const PathPoint *p1,float lw,float rw,float lu,float ru) {
    const float dx0=p0->dy,dy0=neg(p0->dx),dx1=p1->dy,dy1=neg(p1->dx);Pair a,b;
    if(p1->flags&2) {
        chooseBevel((p1->flags&8)!=0,p0,p1,lw,a,b);
        const Pair r0{add(mul(neg(dx0),rw),p1->x),add(mul(neg(dy0),rw),p1->y)};
        const Pair r1{add(mul(neg(dx1),rw),p1->x),add(mul(neg(dy1),rw),p1->y)};
        vertex(dst,a.x,a.y,lu);vertex(dst,r0.x,r0.y,ru);
        if(p1->flags&4) {
            vertex(dst,a.x,a.y,lu);vertex(dst,r0.x,r0.y,ru);
            vertex(dst,b.x,b.y,lu);vertex(dst,r1.x,r1.y,ru);
        } else {
            const Pair center{add(mul(p1->miterX,neg(rw)),p1->x),add(mul(p1->miterY,neg(rw)),p1->y)};
            vertex(dst,p1->x,p1->y,0.5f);vertex(dst,r0.x,r0.y,ru);
            vertex(dst,center.x,center.y,ru);vertex(dst,center.x,center.y,ru);
            vertex(dst,p1->x,p1->y,0.5f);vertex(dst,r1.x,r1.y,ru);
        }
        vertex(dst,b.x,b.y,lu);vertex(dst,r1.x,r1.y,ru);
    } else {
        chooseBevel((p1->flags&8)!=0,p0,p1,neg(rw),a,b);
        const Pair l0{add(mul(dx0,lw),p1->x),add(mul(dy0,lw),p1->y)};
        const Pair l1{add(mul(dx1,lw),p1->x),add(mul(dy1,lw),p1->y)};
        vertex(dst,l0.x,l0.y,lu);vertex(dst,a.x,a.y,ru);
        if(p1->flags&4) {
            vertex(dst,l0.x,l0.y,lu);vertex(dst,a.x,a.y,ru);
            vertex(dst,l1.x,l1.y,lu);vertex(dst,b.x,b.y,ru);
        } else {
            const Pair center{add(mul(p1->miterX,lw),p1->x),add(mul(p1->miterY,lw),p1->y)};
            vertex(dst,l0.x,l0.y,lu);vertex(dst,p1->x,p1->y,0.5f);
            vertex(dst,center.x,center.y,lu);vertex(dst,center.x,center.y,lu);
            vertex(dst,l1.x,l1.y,lu);vertex(dst,p1->x,p1->y,0.5f);
        }
        vertex(dst,l1.x,l1.y,lu);vertex(dst,b.x,b.y,ru);
    }
    return dst;
}

void expandFill_77a50(std::uint8_t *canvas,float width,const PathDependencies &d) {
    auto *c=cache(canvas);const float fringe=load<float>(canvas,0x22a0);
    calculateJoins_942f0(canvas,width,4,constant(d,0x2b55b0),d);
    std::uint32_t required=0;
    for(std::int64_t i=0;i<c->pathCount;++i) {
        const auto &path=c->paths[i];const auto n=static_cast<std::uint32_t>(path.count),b=static_cast<std::uint32_t>(path.bevelCount);
        required+=n+b+1;if(width>0)required+=2*(n+5*b)+2;
    }
    auto *vertices=temporaryVertices(canvas,wrap(required),d);if(!vertices)return;
    const bool convex=c->pathCount==1 && c->paths[0].convex!=0;
    const float offset=mul(fringe,constant(d,0x2b55b4));
    const float left=convex?offset:add(width,offset),right=sub(width,offset),lu=convex?constant(d,0x2b55b4):0;
    for(std::int64_t i=0;i<c->pathCount;++i) {
        auto *path=indexed(c->paths,i);
        auto *points=indexed(c->points,path->first);auto *dst=vertices;path->fill=dst;
        if(width>0) {
            auto *previous=indexed(points,static_cast<std::int64_t>(path->count)-1);
            for(std::int32_t j=0;j<path->count;++j) {
                auto *p=indexed(points,j);
                if((p->flags&4) && !(p->flags&2)) {
                    vertex(dst,add(mul(previous->dy,offset),p->x),add(mul(neg(previous->dx),offset),p->y),0.5f);
                    vertex(dst,add(mul(p->dy,offset),p->x),sub(p->y,mul(p->dx,offset)),0.5f);
                } else vertex(dst,add(mul(p->miterX,offset),p->x),add(mul(p->miterY,offset),p->y),0.5f);
                previous=p;
            }
        } else for(std::int32_t j=0;j<path->count;++j)vertex(dst,points[j].x,points[j].y,0.5f);
        path->fillCount=static_cast<std::int32_t>(dst-vertices);vertices=dst;
        if(width>0) {
            path->stroke=dst;auto *previous=indexed(points,static_cast<std::int64_t>(path->count)-1);
            for(std::int32_t j=0;j<path->count;++j) {
                auto *p=indexed(points,j);
                if(p->flags&12)dst=bevelJoin_945c0(dst,previous,p,left,right,lu,1);
                else {vertex(dst,add(mul(p->miterX,left),p->x),add(mul(p->miterY,left),p->y),lu);
                    vertex(dst,sub(p->x,mul(p->miterX,right)),sub(p->y,mul(p->miterY,right)),1);}
                previous=p;
            }
            vertex(dst,vertices[0].x,vertices[0].y,lu);vertex(dst,vertices[1].x,vertices[1].y,1);
            path->strokeCount=static_cast<std::int32_t>(dst-vertices);vertices=dst;
        } else {path->stroke=nullptr;path->strokeCount=0;}
    }
}

namespace {
void capDirection(float &dx,float &dy,const PathDependencies &d) {
    const float length=_mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(add(mul(dx,dx),mul(dy,dy)))));
    const bool normalized=length>constant(d,0x2b5650);
    const float inverse=div(constant(d,0x2b5654),length);
    const float x=mul(inverse,dx),y=mul(inverse,dy);
    if(normalized){dx=x;dy=y;}
}
void flatCap(PathVertex *&dst,const PathPoint *p,float dx,float dy,float width,
    float distance,float aa,float u0,float u1,bool end) {
    const float px=end?add(mul(dx,distance),p->x):sub(p->x,mul(dx,distance));
    const float py=end?add(mul(dy,distance),p->y):sub(p->y,mul(dy,distance));
    const Pair a{add(mul(dy,width),px),add(mul(neg(dx),width),py)};
    const Pair b{add(mul(neg(dy),width),px),add(mul(dx,width),py)};
    const float extrudeX=mul(end?dx:neg(dx),aa),extrudeY=mul(end?dy:neg(dy),aa);
    if(end){vertex(dst,a.x,a.y,u0);vertex(dst,b.x,b.y,u1);}
    vertex(dst,add(extrudeX,a.x),add(extrudeY,a.y),u0,0);
    vertex(dst,add(extrudeX,b.x),add(extrudeY,b.y),u1,0);
    if(!end){vertex(dst,a.x,a.y,u0);vertex(dst,b.x,b.y,u1);}
}
void roundCap(PathVertex *&dst,const PathPoint *p,float dx,float dy,float width,
    std::int32_t divisions,float u0,float u1,bool end,const PathDependencies &d) {
    if(end){vertex(dst,add(mul(dy,width),p->x),add(mul(neg(dx),width),p->y),u0);
        vertex(dst,add(mul(neg(dy),width),p->x),add(mul(dx,width),p->y),u1);}
    const float denominator=_mm_cvtss_f32(_mm_cvtsi32_ss(_mm_setzero_ps(),divisions-1));
    for(std::int32_t i=0;i<divisions;++i) {
        const float index=_mm_cvtss_f32(_mm_cvtsi32_ss(_mm_setzero_ps(),i));
        const float angle=mul(div(index,denominator),constant(d,0x2b5620));
        const float ax=mul(recovered_cosine_b3590(angle,d.image),width);
        const float ay=mul(recovered_sine_b1cf0(angle,d.image),width);
        const float x=add(mul(end?dx:neg(dx),ay),add(mul(neg(dy),ax),p->x));
        const float y=add(mul(end?dy:neg(dy),ay),add(mul(dx,ax),p->y));
        if(end)vertex(dst,p->x,p->y,0.5f);
        vertex(dst,x,y,u0);
        if(!end)vertex(dst,p->x,p->y,0.5f);
    }
    if(!end){vertex(dst,add(mul(dy,width),p->x),add(mul(neg(dx),width),p->y),u0);
        vertex(dst,add(mul(neg(dy),width),p->x),add(mul(dx,width),p->y),u1);}
}
PathVertex *roundJoin(PathVertex *dst,const PathPoint *p0,const PathPoint *p1,
    float width,float lu,float ru,std::int32_t divisions,const PathDependencies &d) {
    const bool left=(p1->flags&2)!=0;Pair a,b;
    chooseBevel((p1->flags&8)!=0,p0,p1,left?width:neg(width),a,b);
    const float a0=d.direction_13cfc0(d.context,left?p0->dx:neg(p0->dx),left?neg(p0->dy):p0->dy);
    float a1=d.direction_13cfc0(d.context,left?p1->dx:neg(p1->dx),left?neg(p1->dy):p1->dy);
    // The conditional arithmetic preserves the captured comparison direction.
    if(left ? a0<a1 : a1<a0)a1=add(a1,constant(d,left?0x2b5670:0x2b5674));
    const float signWidth=left?neg(width):width;
    const Pair p{add(mul(p0->dy,signWidth),p1->x),add(mul(neg(p0->dx),signWidth),p1->y)};
    const Pair q{add(mul(p1->dy,signWidth),p1->x),add(mul(neg(p1->dx),signWidth),p1->y)};
    if(left){vertex(dst,a.x,a.y,lu);vertex(dst,p.x,p.y,ru);}
    else {vertex(dst,p.x,p.y,lu);vertex(dst,a.x,a.y,ru);}
    const float arc=left?sub(a0,a1):sub(a1,a0);
    const auto count=integer(recovered_ceiling_float_b2920(mul(div(arc,constant(d,0x2b5620)),
        _mm_cvtss_f32(_mm_cvtsi32_ss(_mm_setzero_ps(),divisions))),d.image));
    const auto n=count<2?2:(count<divisions?count:divisions);
    const float denominator=_mm_cvtss_f32(_mm_cvtsi32_ss(_mm_setzero_ps(),n-1));
    for(std::int32_t i=0;i<n;++i) {
        const float index=_mm_cvtss_f32(_mm_cvtsi32_ss(_mm_setzero_ps(),i));
        const float angle=add(mul(div(index,denominator),sub(a1,a0)),a0);
        const float x=add(mul(recovered_cosine_b3590(angle,d.image),width),p1->x);
        const float y=add(mul(recovered_sine_b1cf0(angle,d.image),width),p1->y);
        if(left)vertex(dst,p1->x,p1->y,0.5f);
        vertex(dst,x,y,left?ru:lu);
        if(!left)vertex(dst,p1->x,p1->y,0.5f);
    }
    if(left){vertex(dst,b.x,b.y,lu);vertex(dst,q.x,q.y,ru);}
    else {vertex(dst,q.x,q.y,lu);vertex(dst,b.x,b.y,ru);}
    return dst;
}
}

void expandStroke_782c0(std::uint8_t *canvas,float width,float fringe,std::uint32_t cap,
    std::uint32_t join,float miter,const PathDependencies &d) {
    auto *c=cache(canvas);
    float arc=d.angle_13d190(d.context,div(width,add(load<float>(canvas,0x2298),width)));
    arc=add(arc,arc);
    const auto steps=integer(recovered_ceiling_float_b2920(div(constant(d,0x2b5620),arc),d.image));
    const auto divisions=steps>=3?steps:2;
    width=add(mul(fringe,constant(d,0x2b5624)),width);
    const float u0=fringe==0?constant(d,0x2b5624):0;
    calculateJoins_942f0(canvas,width,join,miter,d);
    std::uint32_t required=0;
    for(std::int64_t i=0;i<c->pathCount;++i) {
        const auto &p=c->paths[i];const auto n=static_cast<std::uint32_t>(p.count),b=static_cast<std::uint32_t>(p.bevelCount);
        required+=2*(n+b*(join==1?static_cast<std::uint32_t>(divisions)+2:5))+2;
        if(p.closed==0)required+=cap==1?static_cast<std::uint32_t>(divisions)*4+4:12;
    }
    auto *vertices=temporaryVertices(canvas,wrap(required),d);if(!vertices)return;
    const float u1=constant(d,fringe==0?0x2b562c:0x2b5628);
    const float buttDistance=mul(fringe,constant(d,0x2b5630)),squareDistance=sub(width,fringe);
    for(std::int64_t i=0;i<c->pathCount;++i) {
        auto *path=indexed(c->paths,i);auto *points=indexed(c->points,path->first);const bool loop=path->closed!=0;
        path->fill=nullptr;path->fillCount=0;auto *dst=vertices;path->stroke=dst;
        auto *p0=loop?indexed(points,static_cast<std::int64_t>(path->count)-1):points;
        auto *p1=loop?points:indexed(points,1);
        const auto start=loop?0:1,end=loop?path->count:wrap(static_cast<std::uint32_t>(path->count)-1);
        if(!loop) {
            float dx=sub(p1->x,p0->x),dy=sub(p1->y,p0->y);capDirection(dx,dy,d);
            if(cap==0 || cap==2)flatCap(dst,p0,dx,dy,width,cap==0?buttDistance:squareDistance,fringe,u0,u1,false);
            else if(cap==1)roundCap(dst,p0,dx,dy,width,divisions,u0,u1,false,d);
        }
        for(std::int32_t j=start;j<end;++j) {
            if(p1->flags&12) {
                if(join==1)dst=roundJoin(dst,p0,p1,width,u0,u1,divisions,d);
                else dst=bevelJoin_945c0(dst,p0,p1,width,width,u0,u1);
            } else {
                vertex(dst,add(mul(p1->miterX,width),p1->x),add(mul(p1->miterY,width),p1->y),u0);
                vertex(dst,sub(p1->x,mul(p1->miterX,width)),sub(p1->y,mul(p1->miterY,width)),u1);
            }
            p0=p1;p1=indexed(p1,1);
        }
        if(loop){vertex(dst,vertices[0].x,vertices[0].y,u0);vertex(dst,vertices[1].x,vertices[1].y,u1);}
        else {
            float dx=sub(p1->x,p0->x),dy=sub(p1->y,p0->y);capDirection(dx,dy,d);
            if(cap==0 || cap==2)flatCap(dst,p1,dx,dy,width,cap==0?buttDistance:squareDistance,fringe,u0,u1,true);
            else if(cap==1)roundCap(dst,p1,dx,dy,width,divisions,u0,u1,true,d);
        }
        path->strokeCount=static_cast<std::int32_t>(dst-vertices);vertices=dst;
    }
}
}
