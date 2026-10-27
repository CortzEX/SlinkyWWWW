#ifndef SLINKY_SHARE_D1AE47E41D82BF51BC59
#define SLINKY_SHARE_D1AE47E41D82BF51BC59
#include "FontStashRuntime.hpp"
#include "FontStashGlyph.hpp"
#include "FontTables.hpp"
#include "FontRasterizer.hpp"
namespace reconstruction::fontstash {
struct BoundContext {
    const std::uint8_t *image;
    const font::RasterDependencies &raster;
    void *services;
    void *(*resize_13cf90)(void*,void*,std::uint64_t);
    void (*atlasError)(void*,std::uint64_t,std::uint64_t,std::int32_t,std::int32_t);
};
inline GlyphDependencies glyphDependencies(BoundContext&c){
    return {&c,c.image,
        [](void*,std::uint8_t*f,std::uint32_t cp){return fonttables::mapGlyph_62850(f,cp);},
        [](void*,std::uint8_t*f,std::int32_t g,std::int32_t*x0,std::int32_t*y0,std::int32_t*x1,std::int32_t*y1){return fonttables::glyphBox_63cf0(f,g,x0,y0,x1,y1);},
        [](void*p,void*storage,std::uint64_t bytes){auto&b=*static_cast<BoundContext*>(p);return b.resize_13cf90(b.services,storage,bytes);},
        [](void*p,std::uint64_t target,std::uint64_t user,std::int32_t error,std::int32_t value){auto&b=*static_cast<BoundContext*>(p);b.atlasError(b.services,target,user,error,value);},
        [](void*p,std::uint8_t*f,std::uint8_t*out,std::int32_t w,std::int32_t h,std::int32_t stride,float sx,float sy,float tx,float ty,std::int32_t glyph){auto&b=*static_cast<BoundContext*>(p);font::makeGlyphBitmap_66f00(f,out,w,h,stride,sx,sy,tx,ty,glyph,b.raster);}};
}
inline Dependencies runtimeDependencies(BoundContext&c){
    return {&c,c.image,
        [](void*p,std::uint8_t*s,std::uint8_t*f,std::uint32_t cp,std::uint32_t size,std::int16_t blur,std::int32_t bitmap){auto&b=*static_cast<BoundContext*>(p);return lookupGlyph_6d1d0(s,f,cp,size,blur,bitmap,glyphDependencies(b));},
        [](void*,std::uint8_t*f,std::int32_t previous,std::int32_t current){return fonttables::kerning_64170(f,previous,current);}};
}
}
#endif // SLINKY_SHARE_D1AE47E41D82BF51BC59
