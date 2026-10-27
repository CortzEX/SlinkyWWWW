#ifndef SLINKY_SHARE_C850E92CB9CD0E7C9669
#define SLINKY_SHARE_C850E92CB9CD0E7C9669
#include "FontRasterizer.hpp"
namespace reconstruction::font {
struct BoundRasterDependencies {
    const RasterDependencies &original;
    const fonttables::ShapeDependencies &shape;
    RasterDependencies value;
    BoundRasterDependencies(const RasterDependencies &source,
        const fonttables::ShapeDependencies &shapes):original(source),shape(shapes),value(source){
        value.context=this;
        value.getGlyphShape_62bb0=[](void *p,std::uint8_t *f,std::int32_t g,Vertex **out){
            auto &b=*static_cast<BoundRasterDependencies*>(p);
            return fonttables::getGlyphShape_62bb0(f,g,out,b.shape);
        };
        value.getGlyphBox_63cf0=[](void*,std::uint8_t *f,std::int32_t g,
            std::int32_t *x0,std::int32_t *y0,std::int32_t *x1,std::int32_t *y1){
            return fonttables::glyphBox_63cf0(f,g,x0,y0,x1,y1);
        };
    }
};
}
#endif // SLINKY_SHARE_C850E92CB9CD0E7C9669
