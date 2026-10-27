#ifndef SLINKY_SHARE_2A5D67645802CB2C4789
#define SLINKY_SHARE_2A5D67645802CB2C4789
#include "FontRuntime.hpp"
#include "FontStashRuntime.hpp"
#include "PathTessellation.hpp"
#include "TextAtlas.hpp"
#include "ByteStrings.hpp"
#include "../native/verified/module_memory.hpp"
namespace reconstruction::drawing {
// This frame lives in the caller's stack or owned storage. Every surviving
// provider receives its original context; recovered services use explicit data.
struct BoundFontDependencies {
    const FontDependencies &original;
    const PathDependencies *path;
    const TextAtlasDependencies *atlas;
    const fontstash::Dependencies *stash;
    FontDependencies value;
    BoundFontDependencies(const FontDependencies &source,const PathDependencies *paths,
        const TextAtlasDependencies *atlases,const fontstash::Dependencies *fontStash)
        :original(source),path(paths),atlas(atlases),stash(fontStash),value(source){
        value.context=this;
        value.resize=[](void *c,void *p,std::uint64_t n){auto &f=*static_cast<BoundFontDependencies *>(c);return f.original.resize(f.original.context,p,n);};
        value.copy=[](void *,void *p,const void *s,std::uint64_t n){recovered_memory_copy(p,s,n);};
        value.length=[](void *,const char *s){return recovered_string_length_ab840(reinterpret_cast<const std::uint8_t*>(s));};
        value.flattenPaths=[](void *c,std::uint8_t *p){auto &f=*static_cast<BoundFontDependencies *>(c);if(f.path)flattenPaths_774d0(p,*f.path);else f.original.flattenPaths(f.original.context,p);};
        value.expandFill=[](void *c,std::uint8_t *p,float w){auto &f=*static_cast<BoundFontDependencies *>(c);if(f.path)expandFill_77a50(p,w,*f.path);else f.original.expandFill(f.original.context,p,w);};
        value.renderFill=[](void *c,std::uint64_t t,std::uint64_t u,const void *p,const void *o,const void *s,float w,const void *b,const void *paths,std::int32_t n){auto &f=*static_cast<BoundFontDependencies *>(c);f.original.renderFill(f.original.context,t,u,p,o,s,w,b,paths,n);};
        value.fontBounds=[](void *c,std::uint8_t *p,float x,float y,const char *s,const char *e,float *b){auto &f=*static_cast<BoundFontDependencies *>(c);return f.stash?fontstash::textBounds_6cde0(p,x,y,s,e,b,*f.stash):f.original.fontBounds(f.original.context,p,x,y,s,e,b);};
        value.fontLineBounds=[](void *c,std::uint8_t *p,float y,float *lo,float *hi){auto &f=*static_cast<BoundFontDependencies *>(c);if(f.stash)fontstash::lineBounds_6ebc0(p,y,lo,hi,*f.stash);else f.original.fontLineBounds(f.original.context,p,y,lo,hi);};
        value.fontIteratorInit=[](void *c,std::uint8_t *p,void *it,float x,float y,const char *s,const char *e,std::int32_t b){auto &f=*static_cast<BoundFontDependencies *>(c);if(f.stash)fontstash::iteratorInit_6dff0(p,static_cast<fontstash::TextIterator *>(it),x,y,s,e,b,*f.stash);else f.original.fontIteratorInit(f.original.context,p,it,x,y,s,e,b);};
        value.fontIteratorNext=[](void *c,std::uint8_t *p,void *it,void *q){auto &f=*static_cast<BoundFontDependencies *>(c);return f.stash?fontstash::iteratorNext_6e2d0(p,static_cast<fontstash::TextIterator *>(it),static_cast<fontstash::GlyphQuad *>(q),*f.stash):f.original.fontIteratorNext(f.original.context,p,it,q);};
        value.allocateTextAtlas=[](void *c,std::uint8_t *p){auto &f=*static_cast<BoundFontDependencies *>(c);return f.atlas?std::int32_t(allocateTextAtlas_79eb0(p,*f.atlas)):f.original.allocateTextAtlas(f.original.context,p);};
        value.updateTexture=[](void *c,std::uint64_t t,std::uint64_t u,std::int32_t texture,std::int32_t x,std::int32_t y,std::int32_t w,std::int32_t h,const void *p){auto &f=*static_cast<BoundFontDependencies *>(c);f.original.updateTexture(f.original.context,t,u,texture,x,y,w,h,p);};
        value.renderText=[](void *c,std::uint64_t t,std::uint64_t u,const void *p,const void *o,const void *s,const void *v,std::int32_t n,float w){auto &f=*static_cast<BoundFontDependencies *>(c);f.original.renderText(f.original.context,t,u,p,o,s,v,n,w);};
        value.expandStroke=[](void *c,std::uint8_t *p,float w,float fringe,std::uint32_t cap,std::uint32_t join,float miter){auto &f=*static_cast<BoundFontDependencies *>(c);if(f.path)expandStroke_782c0(p,w,fringe,cap,join,miter,*f.path);else f.original.expandStroke(f.original.context,p,w,fringe,cap,join,miter);};
        value.renderStroke=[](void *c,std::uint64_t t,std::uint64_t u,const void *p,const void *o,const void *s,float fringe,float w,const void *paths,std::int32_t n){auto &f=*static_cast<BoundFontDependencies *>(c);f.original.renderStroke(f.original.context,t,u,p,o,s,fringe,w,paths,n);};
    }
};
}
#endif // SLINKY_SHARE_2A5D67645802CB2C4789
