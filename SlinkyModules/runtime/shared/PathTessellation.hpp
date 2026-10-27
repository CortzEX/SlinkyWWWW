#ifndef SLINKY_SHARE_368CB9DF5BC56DD2A240
#define SLINKY_SHARE_368CB9DF5BC56DD2A240
#include <cstdint>

namespace reconstruction::drawing {
struct PathPoint {
    float x,y,dx,dy,length,miterX,miterY;
    std::uint8_t flags,padding[3];
};
struct PathVertex {float x,y,u,v;};
struct TessellatedPath {
    std::int32_t first,count;
    std::uint8_t closed,padding0[3];
    std::int32_t bevelCount;
    PathVertex *fill;
    std::int32_t fillCount,padding1;
    PathVertex *stroke;
    std::int32_t strokeCount,winding,convex,padding2;
};
struct PathCache {
    PathPoint *points;
    std::int32_t pointCount,pointCapacity;
    TessellatedPath *paths;
    std::int32_t pathCount,pathCapacity;
    PathVertex *vertices;
    std::int32_t vertexCount,vertexCapacity;
    float bounds[4];
};
static_assert(sizeof(PathPoint)==32 && sizeof(PathVertex)==16);
static_assert(sizeof(TessellatedPath)==56 && sizeof(PathCache)==64);
struct PathDependencies {
    void *context;
    const std::uint8_t *image;
    void *(*resize_13cf90)(void *,void *,std::uint64_t);
    // Exact captured exports are acosf and atan2f. BoundPathDependencies binds
    // their proved decoded cells while retaining these original typed APIs.
    float (*angle_13d190)(void *,float);
    float (*direction_13cfc0)(void *,float,float);
};
void addPoint_93eb0(std::uint8_t *,float,float,std::uint32_t,const PathDependencies &);
void tessellateBezier_94000(std::uint8_t *,float,float,float,float,float,float,
    float,float,std::int32_t,std::uint32_t,const PathDependencies &);
void flattenPaths_774d0(std::uint8_t *,const PathDependencies &);
void calculateJoins_942f0(std::uint8_t *,float,std::uint32_t,float,const PathDependencies &);
PathVertex *bevelJoin_945c0(PathVertex *,const PathPoint *,const PathPoint *,
    float,float,float,float);
void expandFill_77a50(std::uint8_t *,float,const PathDependencies &);
void expandStroke_782c0(std::uint8_t *,float,float,std::uint32_t,std::uint32_t,
    float,const PathDependencies &);
}
#endif // SLINKY_SHARE_368CB9DF5BC56DD2A240
