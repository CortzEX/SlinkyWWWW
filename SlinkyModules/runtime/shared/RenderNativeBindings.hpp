#ifndef SLINKY_SHARE_E0D4B122475CF848371D
#define SLINKY_SHARE_E0D4B122475CF848371D
#include "OwnedNativeBindings.hpp"
#include "Graphics.hpp"
#include "Text.hpp"
#include "Trigonometry.hpp"
#include "SquareRoot.hpp"
#include "DoubleTrigonometry.hpp"
#include "ByteStrings.hpp"
#include "KeyNames.hpp"
#include "DisplayGeometry.hpp"
#include "RayPoint.hpp"
#include "RandomSegment.hpp"
#include "ListRuntime.hpp"
#include "UiControlRuntime.hpp"
#include "FontRuntime.hpp"
#include "UiRuntime.hpp"
#include "WidgetState.hpp"
#include "Widgets.hpp"
#include "WidgetModal.hpp"
#include "GuiCanvas.hpp"
#include "GuiControls.hpp"
#include "BoundGuiServices.hpp"
#include "GuiPages.hpp"
#include "GuiModalColor.hpp"
#include "ColorSpace.hpp"
#include "TextAtlas.hpp"
#include "BoundFontDependencies.hpp"
#include "BoundPathDependencies.hpp"
#include "BoundRasterDependencies.hpp"
#include "FontStashGlyph.hpp"
#include "Exponential.hpp"
#include "ConfigurationPersistence.hpp"
#include "../native/verified/module_item_catalog.hpp"
#include "../native/verified/module_surface.hpp"
#include "../native/verified/module_memory.hpp"
#include "../native/verified/module_clock.hpp"
#include "../native/verified/No_Item_Release.hpp"
#include "../modules/Aim_Assist/Support.hpp"
#include "../modules/Teams/Teams.hpp"
#include <array>
#include <cstring>
#include <optional>

namespace reconstruction::native_binding {
// Callers supply mutable image storage, the native binding context, and actual
// external/library/protected endpoints. No process-wide active adapter exists.
struct RenderContext {
    Context &native;
    std::uint8_t *image;
    Word nativeBase;
    Word nativeImageSize;
    std::uint64_t *clockFrequencyBits;
    const std::uint8_t *encodedFrequencyTarget;
    const std::uint8_t *encodedCounterTarget;
    std::uint32_t listGrowthIncomingRsi;
    std::uint32_t inputIncomingRsi;
    void *user;
    Word (*boundary)(void *, Word target, const Word *, std::size_t);
    const ItemCatalog &catalog;
    const SurfaceSettingsDependencies &settings;
    const drawing::FontDependencies &fonts;
    const ui::UiDependencies &interface;
    const configuration::Dependencies *configuration=nullptr;
    const gui::ControlDependencies *controls=nullptr;
    const gui::PageDependencies *pages=nullptr;
    const gui::RuntimeDependencies *guiRuntime=nullptr;
    const drawing::TextAtlasDependencies *textAtlas=nullptr;
    const drawing::PathDependencies *path=nullptr;
    const fontstash::Dependencies *fontStash=nullptr;
    const font::RasterDependencies *raster=nullptr;
    const fonttables::ShapeDependencies *fontShape=nullptr;
    const fontstash::GlyphDependencies *fontGlyph=nullptr;
    const gui::DialogDependencies *dialogs=nullptr;
    const gui::ProfileActionDependencies *profileActions=nullptr;
    configuration::ProfileManagerDependencies *profileManager=nullptr;
    const directory_service::Context *directoryService=nullptr;
    Word invoke(Word target, const Word *arguments, std::size_t count);
    RecoveredFrameInvoker frame() { return {this, [](void *opaque,Word target,const Word *a,std::size_t n) { return static_cast<RenderContext *>(opaque)->invoke(target,a,n); }}; }
};

template<std::size_t Payloads, class Target = Word> struct RenderEndpoint {
    RenderContext *context;
    explicit RenderEndpoint(RenderContext &value) : context(&value) {}
    template<std::size_t Other, class OtherTarget>
    explicit RenderEndpoint(RenderEndpoint<Other, OtherTarget> value) : context(value.context) {}
    template<class... Arguments> Word operator()(Target target, Arguments... arguments) const {
        static_assert(sizeof...(Arguments) == Payloads, "native payload count changed");
        const std::array<Word, Payloads> words{Word(arguments)...};
        return context->invoke(Word(target), words.data(), words.size());
    }
    // Preserve the enclosing callback's explicit zero-padded native frame.
    operator RecoveredWordInvoker() const {
        return {context, [](void *opaque, Word target, Word a, Word b, Word c, Word d) -> Word {
            std::array<Word, Payloads> words{};
            static_assert(Payloads >= 4);
            words[0] = a; words[1] = b; words[2] = c; words[3] = d;
            return static_cast<RenderContext *>(opaque)->invoke(target, words.data(), words.size());
        }};
    }
};

inline Word RenderContext::invoke(Word target, const Word *arguments, std::size_t count) {
    // Only addresses within the caller's stated image are normalized. JNI
    // virtual targets and graphics import addresses keep their actual identity.
    Word rva = target;
    if (nativeBase && target >= nativeBase && target - nativeBase < nativeImageSize)
        rva = target - nativeBase;
    std::array<Word, 12> storage{};
    const auto copied = count < storage.size() ? count : storage.size();
    std::memcpy(storage.data(), arguments, copied * sizeof(Word));
    const Word *a = storage.data();
    // The word array is the explicit Windows x64 variadic save area. Retain
    // every supplied argument; a fixed two-argument formatter loses wider calls.
    if (rva == 0xab710)
        return recovered_format_arguments(&native.format,
            reinterpret_cast<char *>(std::uintptr_t(a[0])), std::size_t(a[1]),
            reinterpret_cast<const char *>(std::uintptr_t(a[2])),
            reinterpret_cast<char *>(storage.data() + 3));
    if (rva == 0xab770)
        return recovered_format_arguments(&native.format,
            reinterpret_cast<char *>(std::uintptr_t(a[0])), std::size_t(a[1]),
            reinterpret_cast<const char *>(std::uintptr_t(a[2])),
            reinterpret_cast<char *>(std::uintptr_t(a[3])));
    Value value;
    if (resolve(native, rva, a, value)) return value.bits;
    auto pointer = [](Word value) { return reinterpret_cast<void *>(std::uintptr_t(value)); };
    auto vector = [&](Word value) { return static_cast<double *>(pointer(value)); };
    // Nested four-payload operations retain this call's wider frame as zeros.
    struct Nested { RenderContext *context; std::size_t count; } nested{this, count};
    RecoveredWordInvoker invokeFour{&nested, [](void *opaque, Word target, Word a, Word b, Word c, Word d) {
        auto &state = *static_cast<Nested *>(opaque);
        std::array<Word, 12> words{};
        words[0] = a; words[1] = b; words[2] = c; words[3] = d;
        return state.context->invoke(target, words.data(), state.count < 4 ? 4 : state.count);
    }};
    const auto invokeFrame=frame();
    struct PageFallback { RenderContext &outer;const RecoveredFrameInvoker *calls; } pageFallback{*this,this->pages?&this->pages->calls:nullptr};
    // Canonical nested page calls keep their original external fallback. This
    // borrowed copy shares every image/service reference and owns no state.
    RenderContext pageResolver=*this;
    pageResolver.user=&pageFallback;
    pageResolver.boundary=[](void *opaque,Word target,const Word *a,std::size_t count){
        const auto &f=*static_cast<PageFallback *>(opaque);
        if(f.calls&&f.calls->invoke)return f.calls->invoke(f.calls->context,target,a,count);
        return f.outer.boundary(f.outer.user,target,a,count);
    };
    std::optional<drawing::BoundPathDependencies> pathFrame;
    if(this->path)pathFrame.emplace(*this->path,
        numeric_service::Context{native.image,native.numericFloatUnaryEncodedCell_13d190},
        numeric_service::Context{native.image,native.numericFloatDirectionEncodedCell_13cfc0});
    const auto *path=pathFrame?&pathFrame->value:nullptr;
    std::optional<font::BoundRasterDependencies> rasterFrame;
    if(this->raster&&fontShape)rasterFrame.emplace(*this->raster,*fontShape);
    const auto *raster=rasterFrame?&rasterFrame->value:this->raster;
    drawing::BoundFontDependencies fontFrame{this->fonts,path,textAtlas,fontStash};
    const auto &fonts=fontFrame.value;
    std::optional<drawing::BoundFontDependencies> controlFonts,pageFonts,runtimeFonts;
    std::optional<gui::BoundControlDependencies> controlFrame,pageControls,runtimeControls;
    std::optional<gui::BoundPageDependencies> pageFrame;
    std::optional<gui::PageCalls> runtimePageCalls;
    std::optional<gui::ConfigurationCalls> runtimeConfigurationCalls;
    std::optional<gui::BoundRuntimeDependencies> runtimeFrame;
    // Borrow this exact invocation's clock/platform frame. An explicitly
    // supplied dialog context takes priority; both have caller-owned services.
    gui::DialogDependencies defaultDialogs{interface,image,native.format,this,
        [](void *opaque){auto &c=*static_cast<RenderContext *>(opaque);
            if(c.pages)return c.pages->clock(c.pages->context);
            return recovered_clock_value(c.clockFrequencyBits,c.encodedFrequencyTarget,c.encodedCounterTarget);}};
    const auto *dialogs=this->dialogs?this->dialogs:&defaultDialogs;
    const auto *pageConfiguration=configuration?configuration:
        (profileManager?&profileManager->paths:(profileActions?&profileActions->paths:nullptr));
    std::optional<gui::BoundProfileActionDependencies> profileActionFrame;
    if(pageConfiguration&&directoryService)
        profileActionFrame.emplace(*pageConfiguration,*directoryService);
    const auto *profileActions=profileActionFrame?&profileActionFrame->value:this->profileActions;
    const auto *crt=native.crt?&native.crt->services:nullptr;
    numeric_service::Context scalar{native.image,native.numericBinaryScalarEncodedCell_13cfe0};
    if(this->controls){
        const auto &c=*this->controls;controlFonts.emplace(c.fonts,path,textAtlas,fontStash);
        controlFrame.emplace(c,controlFonts->value,crt,dialogs);
    }
    if(this->pages){
        const auto &p=*this->pages;const auto &c=p.controls;pageFonts.emplace(c.fonts,path,textAtlas,fontStash);
        pageControls.emplace(c,pageFonts->value,crt,dialogs);
        pageFrame.emplace(p,pageControls->value,dialogs,pageConfiguration,profileActions,pageResolver.frame());
        runtimePageCalls.emplace(gui::pageCalls(pageFrame->value));
    }
    if(profileManager)runtimeConfigurationCalls.emplace(gui::configurationCalls(*profileManager));
    if(this->guiRuntime){
        const auto &g=*this->guiRuntime;const auto &c=g.controls;runtimeFonts.emplace(c.fonts,path,textAtlas,fontStash);
        runtimeControls.emplace(c,runtimeFonts->value,crt,dialogs);
        runtimeFrame.emplace(g,runtimeControls->value,
            native.numericBinaryScalarEncodedCell_13cfe0?&scalar:nullptr,crt,
            runtimePageCalls?&*runtimePageCalls:nullptr,
            runtimeConfigurationCalls?&*runtimeConfigurationCalls:nullptr);
    }
    const auto *controls=controlFrame?&controlFrame->value:nullptr;
    const auto *pages=pageFrame?&pageFrame->value:nullptr;
    const auto *guiRuntime=runtimeFrame?&runtimeFrame->value:nullptr;
    switch (rva) {
    case 0x774d0: if(path){drawing::flattenPaths_774d0(static_cast<std::uint8_t *>(pointer(a[0])),*path);return 0;}return boundary(user,target,arguments,count);
    case 0x77a50: if(path){drawing::expandFill_77a50(static_cast<std::uint8_t *>(pointer(a[0])),single(a[1]),*path);return 0;}return boundary(user,target,arguments,count);
    case 0x782c0: if(path){drawing::expandStroke_782c0(static_cast<std::uint8_t *>(pointer(a[0])),single(a[1]),single(a[2]),std::uint32_t(a[3]),std::uint32_t(a[4]),single(a[5]),*path);return 0;}return boundary(user,target,arguments,count);
    case 0x93eb0: if(path){drawing::addPoint_93eb0(static_cast<std::uint8_t *>(pointer(a[0])),single(a[1]),single(a[2]),std::uint32_t(a[3]),*path);return 0;}return boundary(user,target,arguments,count);
    case 0x94000: if(path){drawing::tessellateBezier_94000(static_cast<std::uint8_t *>(pointer(a[0])),single(a[1]),single(a[2]),single(a[3]),single(a[4]),single(a[5]),single(a[6]),single(a[7]),single(a[8]),std::int32_t(a[9]),std::uint32_t(a[10]),*path);return 0;}return boundary(user,target,arguments,count);
    case 0x942f0: if(path){drawing::calculateJoins_942f0(static_cast<std::uint8_t *>(pointer(a[0])),single(a[1]),std::uint32_t(a[2]),single(a[3]),*path);return 0;}return boundary(user,target,arguments,count);
    case 0x945c0: return std::uintptr_t(drawing::bevelJoin_945c0(static_cast<drawing::PathVertex *>(pointer(a[0])),static_cast<const drawing::PathPoint *>(pointer(a[1])),static_cast<const drawing::PathPoint *>(pointer(a[2])),single(a[3]),single(a[4]),single(a[5]),single(a[6])));
    case 0x6cde0: if(fontStash)return floatBits(fontstash::textBounds_6cde0(static_cast<std::uint8_t *>(pointer(a[0])),single(a[1]),single(a[2]),static_cast<const char *>(pointer(a[3])),static_cast<const char *>(pointer(a[4])),static_cast<float *>(pointer(a[5])),*fontStash));return boundary(user,target,arguments,count);
    case 0x6ebc0: if(fontStash){fontstash::lineBounds_6ebc0(static_cast<std::uint8_t *>(pointer(a[0])),single(a[1]),static_cast<float *>(pointer(a[2])),static_cast<float *>(pointer(a[3])),*fontStash);return 0;}return boundary(user,target,arguments,count);
    case 0x6dff0: if(fontStash)return std::uint32_t(fontstash::iteratorInit_6dff0(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<fontstash::TextIterator *>(pointer(a[1])),single(a[2]),single(a[3]),static_cast<const char *>(pointer(a[4])),static_cast<const char *>(pointer(a[5])),std::int32_t(a[6]),*fontStash));return boundary(user,target,arguments,count);
    case 0x6e2d0: if(fontStash)return std::uint32_t(fontstash::iteratorNext_6e2d0(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<fontstash::TextIterator *>(pointer(a[1])),static_cast<fontstash::GlyphQuad *>(pointer(a[2])),*fontStash));return boundary(user,target,arguments,count);
    case 0x6de40: if(fontStash){fontstash::glyphQuad_6de40(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<std::uint8_t *>(pointer(a[1])),std::int32_t(a[2]),static_cast<const std::uint8_t *>(pointer(a[3])),single(a[4]),single(a[5]),static_cast<float *>(pointer(a[6])),static_cast<float *>(pointer(a[7])),static_cast<fontstash::GlyphQuad *>(pointer(a[8])),*fontStash);return 0;}return boundary(user,target,arguments,count);
    case 0x79eb0: if(textAtlas)return drawing::allocateTextAtlas_79eb0(static_cast<std::uint8_t *>(pointer(a[0])),*textAtlas);return boundary(user,target,arguments,count);
    case 0x6f380: if(textAtlas)return drawing::resetTextAtlas_6f380(static_cast<std::uint8_t *>(pointer(a[0])),std::uint32_t(a[1]),std::uint32_t(a[2]),*textAtlas);return boundary(user,target,arguments,count);
    case 0x26530:return recovered_no_item_release_action(static_cast<GameAccessBridge*>(pointer(a[0])),a[1]);
    case 0x26580:return recovered_no_item_release_use_packet(static_cast<GameAccessBridge*>(pointer(a[0])),a[1]);
    case 0x62850:return std::uint32_t(fonttables::mapGlyph_62850(static_cast<std::uint8_t*>(pointer(a[0])),std::uint32_t(a[1])));
    case 0x63cf0:return std::uint32_t(fonttables::glyphBox_63cf0(static_cast<std::uint8_t*>(pointer(a[0])),std::int32_t(a[1]),static_cast<std::int32_t*>(pointer(a[2])),static_cast<std::int32_t*>(pointer(a[3])),static_cast<std::int32_t*>(pointer(a[4])),static_cast<std::int32_t*>(pointer(a[5]))));
    case 0x64170:return std::uint32_t(fonttables::kerning_64170(static_cast<std::uint8_t*>(pointer(a[0])),std::int32_t(a[1]),std::int32_t(a[2])));
    case 0x7d0e0:return std::uint32_t(fonttables::glyphClass_7d0e0(static_cast<const std::uint8_t*>(pointer(a[0])),std::int32_t(a[1])));
    case 0x62bb0:if(fontShape)return std::uint32_t(fonttables::getGlyphShape_62bb0(static_cast<std::uint8_t*>(pointer(a[0])),std::int32_t(a[1]),static_cast<fonttables::Vertex**>(pointer(a[2])),*fontShape));return boundary(user,target,arguments,count);
    case 0x6d1d0:if(fontGlyph)return std::uintptr_t(fontstash::lookupGlyph_6d1d0(static_cast<std::uint8_t*>(pointer(a[0])),static_cast<std::uint8_t*>(pointer(a[1])),std::uint32_t(a[2]),std::uint32_t(a[3]),std::int16_t(a[4]),std::int32_t(a[5]),*fontGlyph));return boundary(user,target,arguments,count);
    case 0x7dd90:if(fontGlyph)return std::uint32_t(fontstash::addRectangle_7dd90(static_cast<std::uint8_t*>(pointer(a[0])),std::int32_t(a[1]),std::int32_t(a[2]),static_cast<std::int32_t*>(pointer(a[3])),static_cast<std::int32_t*>(pointer(a[4])),*fontGlyph));return boundary(user,target,arguments,count);
    case 0x66f00:if(raster){font::makeGlyphBitmap_66f00(static_cast<std::uint8_t*>(pointer(a[0])),static_cast<std::uint8_t*>(pointer(a[1])),std::int32_t(a[2]),std::int32_t(a[3]),std::int32_t(a[4]),single(a[5]),single(a[6]),single(a[7]),single(a[8]),std::int32_t(a[9]),*raster);return 0;}return boundary(user,target,arguments,count);
    case 0x64e50:if(raster){font::rasterize_64e50(static_cast<font::Bitmap*>(pointer(a[0])),single(a[1]),static_cast<font::Vertex*>(pointer(a[2])),std::int32_t(a[3]),single(a[4]),single(a[5]),single(a[6]),single(a[7]),std::int32_t(a[8]),std::int32_t(a[9]),std::int32_t(a[10]),static_cast<std::uint8_t*>(pointer(a[11])),*raster);return 0;}return boundary(user,target,arguments,count);
    case 0x7d1d0:font::flattenQuadratic_7d1d0(static_cast<font::Point*>(pointer(a[0])),static_cast<std::int32_t*>(pointer(a[1])),single(a[2]),single(a[3]),single(a[4]),single(a[5]),single(a[6]),single(a[7]),single(a[8]),std::int32_t(a[9]),image);return 0;
    case 0x7d3b0:font::flattenCubic_7d3b0(static_cast<font::Point*>(pointer(a[0])),static_cast<std::int32_t*>(pointer(a[1])),single(a[2]),single(a[3]),single(a[4]),single(a[5]),single(a[6]),single(a[7]),single(a[8]),single(a[9]),single(a[10]),std::int32_t(a[11]),image);return 0;
    case 0x7d720:font::sortEdges_7d720(static_cast<font::Edge*>(pointer(a[0])),std::int32_t(a[1]));return 0;
    case 0xb2b40:return floatBits(recovered_exponential_b2b40(single(a[0]),image));
    case 0xb2cb0:return floatBits(recovered_scale_float_b2cb0(single(a[0]),std::int32_t(a[1]),image));
    case 0x11820: if(guiRuntime){gui::render_11820(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<std::uint8_t *>(pointer(a[1])),a[2],a[3],*guiRuntime);return 0;}return boundary(user,target,arguments,count);
    case 0x128c0: if(guiRuntime){gui::fadeBackdrop_128c0(static_cast<std::uint8_t *>(pointer(a[0])),single(a[1]),*guiRuntime);return 0;}return boundary(user,target,arguments,count);
    case 0x12a90: gui::clearInteraction_12a90(static_cast<std::uint8_t *>(pointer(a[0])));return 0;
    case 0x12ac0: return gui::viewportIntersects_12ac0(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<std::uint8_t *>(pointer(a[1])),static_cast<const float *>(pointer(a[2])));
    case 0x12b20: if(pages){gui::renderCategory_12b20(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<std::uint8_t *>(pointer(a[1])),a[2],std::uint32_t(a[3]),single(a[4]),*pages);return 0;}return boundary(user,target,arguments,count);
    case 0x13420: if(pages){gui::profileTextInput_13420(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<std::uint8_t *>(pointer(a[1])),a[2],static_cast<std::uint8_t *>(pointer(a[3])),std::uint32_t(a[4]),static_cast<std::uint8_t *>(pointer(a[5])),static_cast<const float *>(pointer(a[6])),*pages);return 0;}return boundary(user,target,arguments,count);
    case 0x138f0: if(pages){gui::profilePopup_138f0(static_cast<std::uint8_t *>(pointer(a[0])),a[1],a[2],static_cast<const char *>(pointer(a[3])),std::uint32_t(a[4]),*pages);return 0;}return boundary(user,target,arguments,count);
    case 0x139d0: if(pages){gui::completeProfilePopup_139d0(static_cast<std::uint8_t *>(pointer(a[0])),*pages);return 0;}return boundary(user,target,arguments,count);
    case 0x130c0: if(pages)return floatBits(gui::moduleText_130c0(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<std::uint8_t *>(pointer(a[1])),static_cast<std::uint8_t *>(pointer(a[2])),static_cast<const float *>(pointer(a[3])),single(a[4]),static_cast<const float *>(pointer(a[5])),static_cast<const float *>(pointer(a[6])),static_cast<const char *>(pointer(a[7])),*pages));return boundary(user,target,arguments,count);
    case 0x16ca0: if(pages){gui::renderModal_16ca0(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<std::uint8_t *>(pointer(a[1])),*pages);return 0;}return boundary(user,target,arguments,count);
    case 0x16820: gui::openDialog_16820(static_cast<std::uint8_t *>(pointer(a[0])),a[1],a[2],static_cast<const char *>(pointer(a[3])),reinterpret_cast<std::va_list>(storage.data()+4),*dialogs);return 0;
    case 0xc220: if(pageConfiguration)return gui::deleteProfile_c220(static_cast<const char *>(pointer(a[0])),*pageConfiguration);return boundary(user,target,arguments,count);
    case 0xc290: if(profileActions)return gui::openProfileDirectory_c290(*profileActions);return boundary(user,target,arguments,count);
    case 0x4c7b0: if(profileActions)return gui::exploreDirectory_4c7b0(static_cast<std::uint16_t **>(pointer(a[0])),*profileActions);return boundary(user,target,arguments,count);
    case 0xdcdbe0: if(directoryService)return directory_service::execute_dcdbe0(*directoryService,a[0],static_cast<const std::uint16_t *>(pointer(a[1])),static_cast<const std::uint16_t *>(pointer(a[2])),a[3],a[4],std::uint32_t(a[5]));return boundary(user,target,arguments,count);
    case 0x18830: return gui::filterHexColor_18830(static_cast<std::uint8_t *>(pointer(a[0])),std::uint32_t(a[1]));
    case 0x18880: return gui::modalColorSlider_18880(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<std::uint8_t *>(pointer(a[1])),static_cast<const float *>(pointer(a[2])),std::uint32_t(a[3]),static_cast<const float *>(pointer(a[4])),image,invokeFrame);
    case 0x74220: return std::uintptr_t(recovered_hsl_74220(static_cast<float *>(pointer(a[0])),single(a[1]),single(a[2]),single(a[3]),image));
    case 0x74250: return std::uintptr_t(recovered_hsla_74250(static_cast<float *>(pointer(a[0])),single(a[1]),single(a[2]),single(a[3]),std::uint8_t(a[4]),image));
    case 0xb2a70: return floatBits(recovered_floor_b2a70(single(a[0]),image));
    case 0xb2920: return floatBits(gui::ceilFloat_b2920(single(a[0]),image));
    case 0x10360: gui::resetLayout_10360(static_cast<std::uint8_t *>(pointer(a[0])));return 0;
    case 0x10380: gui::pushLayout_10380(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<float *>(pointer(a[1])),single(a[2]),single(a[3]));return 0;
    case 0x104f0: gui::pushScissor_104f0(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<std::uint8_t *>(pointer(a[1])),static_cast<float *>(pointer(a[2])),single(a[3]),single(a[4]),image);return 0;
    case 0x105b0: return floatBits(gui::endLayout_105b0(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<std::uint8_t *>(pointer(a[1])),image));
    case 0x106b0: gui::setColumns_106b0(static_cast<std::uint8_t *>(pointer(a[0])),std::int32_t(a[1]),image);return 0;
    case 0x10780: gui::autoColumns_10780(static_cast<std::uint8_t *>(pointer(a[0])),single(a[1]),image);return 0;
    case 0x10a10: gui::fillRectangle_10a10(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<const float *>(pointer(a[1])),fonts);return 0;
    case 0x10ba0: if(controls){gui::drawIcon_10ba0(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<const float *>(pointer(a[1])),std::uint32_t(a[2]),single(a[3]),*controls);return 0;}return boundary(user,target,arguments,count);
    case 0x10e70: if(controls){gui::drawCaret_10e70(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<const float *>(pointer(a[1])),static_cast<const float *>(pointer(a[2])),single(a[3]),single(a[4]),*controls);return 0;}return boundary(user,target,arguments,count);
    case 0x112b0: return gui::active_112b0(static_cast<std::uint8_t *>(pointer(a[0])),a[1]);
    case 0x113f0: if(controls){gui::tabs_113f0(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<std::uint8_t *>(pointer(a[1])),single(a[2]),*controls);return 0;}return boundary(user,target,arguments,count);
    case 0x117f0: gui::requestClose_117f0(static_cast<std::uint8_t *>(pointer(a[0])));return 0;
    case 0x14cb0: if(controls){gui::tooltip_14cb0(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<std::uint8_t *>(pointer(a[1])),static_cast<const char *>(pointer(a[2])),std::int32_t(a[3]),std::int32_t(a[4]),*controls);return 0;}return boundary(user,target,arguments,count);
    case 0x16330: return gui::textButton_16330(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<std::uint8_t *>(pointer(a[1])),static_cast<const float *>(pointer(a[2])),a[3],a[4]);
    case 0x16380: if(controls){gui::textEntry_16380(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<std::uint8_t *>(pointer(a[1])),static_cast<const float *>(pointer(a[2])),*controls);return 0;}return boundary(user,target,arguments,count);
    case 0x16430: if(controls){gui::alignedTextEntry_16430(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<std::uint8_t *>(pointer(a[1])),static_cast<const float *>(pointer(a[2])),std::uint32_t(a[3]),*controls);return 0;}return boundary(user,target,arguments,count);
    case 0x13ad0: gui::filterProfileName_13ad0(static_cast<char *>(pointer(a[0])),std::uint32_t(a[1]));return 0;
    case 0x16c80: return gui::modalVisible_16c80(static_cast<std::uint8_t *>(pointer(a[0])));
    case 0x16c90: return gui::modalAllows_16c90(static_cast<std::uint8_t *>(pointer(a[0])));
    case 0x769d0: gui::roundedRect_769d0(static_cast<std::uint8_t *>(pointer(a[0])),single(a[1]),single(a[2]),single(a[3]),single(a[4]),single(a[5]),image,fonts);return 0;
    case 0x16600: return recovered_color_modal_16600(static_cast<std::uint8_t *>(pointer(a[0])),a[1],a[2],static_cast<const std::uint8_t *>(pointer(a[3])),a[4],image,invokeFrame);
    case 0x168f0: recovered_suggestion_modal_168f0(static_cast<std::uint8_t *>(pointer(a[0])),a[1],a[2],a[3],a[4],a[5],a[6],invokeFrame);return 0;
    case 0x158e0: return recovered_list_widget_158e0(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<std::uint8_t *>(pointer(a[1])),a[2],a[3],a[4],std::uint32_t(a[5]),static_cast<std::uint8_t *>(pointer(a[6])),a[7],a[8],image,nativeBase?nativeBase+0x158c0:0x158c0,nativeBase?nativeBase+0x16190:0x16190,nativeBase?nativeBase+0x161d0:0x161d0,invokeFrame);
    case 0x16190: recovered_list_suggestion_accept_16190(static_cast<std::uint8_t *>(pointer(a[0])),a[2],image,invokeFrame);return 0;
    case 0x161d0: recovered_list_text_accept_161d0(static_cast<std::uint8_t *>(pointer(a[0])),a[1],image,invokeFrame);return 0;
    case 0x10da0: if(controls)return floatBits(gui::measuredText_10da0(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<float *>(pointer(a[1])),std::uint32_t(a[2]),std::uint32_t(a[3]),static_cast<const char *>(pointer(a[4])),static_cast<const char *>(pointer(a[5])),*controls));return boundary(user,target,arguments,count);
    case 0x16530: if(pages){gui::beginModal_16530(static_cast<std::uint8_t *>(pointer(a[0])),a[1],a[2],a[3],a[4],*pages);return 0;}return boundary(user,target,arguments,count);
    case 0x14d00: return recovered_choice_widget_14d00(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<std::uint8_t *>(pointer(a[1])),a[2],static_cast<std::uint8_t *>(pointer(a[3])),std::uint32_t(a[4]),static_cast<const std::uint64_t *>(pointer(a[5])),static_cast<std::uint32_t *>(pointer(a[6])),std::uint8_t(a[7]),image,nativeBase?nativeBase+0x15540:0x15540,nativeBase?nativeBase+0x15590:0x15590,invokeFrame);
    case 0x15540: return recovered_choice_filter_15540(static_cast<std::uint8_t *>(pointer(a[0])),std::uint32_t(a[1]));
    case 0x15590: recovered_choice_accept_15590(static_cast<std::uint32_t *>(pointer(a[0])),std::uint32_t(a[1]),a[2]);return 0;
    case 0x10b00: ui::strokeRoundedRect_10b00(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<const float *>(pointer(a[1])),single(a[2]),image,fonts);return 0;
    case 0x75340: return std::uintptr_t(drawing::linearGradient_75340(pointer(a[0]),single(a[2]),single(a[3]),single(a[4]),single(a[5]),pointer(a[6]),pointer(a[7]),image));
    case 0x76de0: drawing::ellipse_76de0(static_cast<std::uint8_t *>(pointer(a[0])),single(a[1]),single(a[2]),single(a[3]),single(a[4]),image,fonts);return 0;
    case 0x76f40: drawing::circle_76f40(static_cast<std::uint8_t *>(pointer(a[0])),single(a[1]),single(a[2]),single(a[3]),image,fonts);return 0;
    case 0x77f80: drawing::stroke_77f80(static_cast<std::uint8_t *>(pointer(a[0])),image,fonts);return 0;
    case 0x14580: return recovered_range_widget_14580(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<std::uint8_t *>(pointer(a[1])),static_cast<const char *>(pointer(a[2])),static_cast<const char *>(pointer(a[3])),static_cast<const char *>(pointer(a[4])),static_cast<std::uint8_t *>(pointer(a[5])),single(a[6]),single(a[7]),single(a[8]),single(a[9]),static_cast<float *>(pointer(a[10])),static_cast<float *>(pointer(a[11])),image,nativeBase?nativeBase+0x164f0:0x164f0,invokeFrame);
    case 0x155a0: return recovered_color_widget_155a0(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<std::uint8_t *>(pointer(a[1])),a[2],static_cast<std::uint32_t *>(pointer(a[3])),image,nativeBase?nativeBase+0x158c0:0x158c0,invokeFrame);
    case 0x158c0: return recovered_color_accept_158c0(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<const std::uint8_t *>(pointer(a[1])));
    case 0xbbd0: if(configuration)return configuration::saveConfiguration_bbd0(static_cast<const std::uint8_t *>(pointer(a[0])),static_cast<const std::uint8_t *>(pointer(a[1])),*configuration);return boundary(user,target,arguments,count);
    case 0x164f0: return recovered_numeric_filter_164f0(static_cast<std::uint8_t *>(pointer(a[0])),std::uint32_t(a[1]));
    case 0x73a70: gui::saveCanvas_73a70(static_cast<std::uint8_t *>(pointer(a[0])));return 0;
    case 0x749a0: gui::restoreCanvas_749a0(static_cast<std::uint8_t *>(pointer(a[0])));return 0;
    case 0x749e0: gui::lineWidth_749e0(static_cast<std::uint8_t *>(pointer(a[0])),single(a[1]));return 0;
    case 0x74b40: gui::translateCanvas_74b40(static_cast<std::uint8_t *>(pointer(a[0])),single(a[1]),single(a[2]));return 0;
    case 0x74d40: gui::scaleCanvas_74d40(static_cast<std::uint8_t *>(pointer(a[0])),single(a[1]),single(a[2]));return 0;
    case 0x74de0: gui::strokeColor_74de0(static_cast<std::uint8_t *>(pointer(a[0])),pointer(a[1]),image);return 0;
    case 0x74f60: gui::fillPaint_74f60(static_cast<std::uint8_t *>(pointer(a[0])),pointer(a[1]));return 0;
    case 0x75520: return std::uintptr_t(gui::imagePaint_75520(pointer(a[0]),static_cast<std::uint8_t *>(pointer(a[1])),single(a[2]),single(a[3]),single(a[4]),single(a[5]),single(a[6]),std::int32_t(a[7]),single(a[8]),image));
    case 0x75630: gui::scissorCanvas_75630(static_cast<std::uint8_t *>(pointer(a[0])),single(a[1]),single(a[2]),single(a[3]),single(a[4]),image);return 0;
    case 0x75bf0: gui::moveTo_75bf0(static_cast<std::uint8_t *>(pointer(a[0])),single(a[1]),single(a[2]),fonts);return 0;
    case 0x75ec0: gui::lineTo_75ec0(static_cast<std::uint8_t *>(pointer(a[0])),single(a[1]),single(a[2]),fonts);return 0;
    case 0x76950: gui::rectPath_76950(static_cast<std::uint8_t *>(pointer(a[0])),single(a[1]),single(a[2]),single(a[3]),single(a[4]),fonts);return 0;
    case 0xa0e0: return gui::intersectsRect_a0e0(static_cast<const float *>(pointer(a[0])),static_cast<const float *>(pointer(a[1])));
    case 0xa160: return std::uintptr_t(gui::roundRect_a160(static_cast<float *>(pointer(a[0])),static_cast<const float *>(pointer(a[1])),image));
    case 0xa1e0: return gui::rectPosition_a1e0(static_cast<const float *>(pointer(a[0])));
    case 0x13f40: return recovered_number_widget_13f40(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<std::uint8_t *>(pointer(a[1])),static_cast<const char *>(pointer(a[2])),static_cast<const char *>(pointer(a[3])),static_cast<std::uint8_t *>(pointer(a[4])),single(a[5]),single(a[6]),single(a[7]),single(a[8]),static_cast<float *>(pointer(a[9])),image,nativeBase?nativeBase+0x164f0:0x164f0,invokeFrame);
    case 0x14370: return recovered_numeric_action_14370(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<const float *>(pointer(a[1])),static_cast<const float *>(pointer(a[2])),single(a[3]),single(a[4]),single(a[5]),single(a[6]),static_cast<std::uint8_t *>(pointer(a[7])),static_cast<float *>(pointer(a[8])),nativeBase?nativeBase+0x164f0:0x164f0,image);
    case 0xa0a0: return recovered_rectangle_contains_a0a0(static_cast<const float *>(pointer(a[0])),a[1]);
    case 0xa130: return std::uintptr_t(recovered_rectangle_inset_a130(static_cast<float *>(pointer(a[0])),static_cast<const float *>(pointer(a[1])),single(a[2])));
    case 0xa260: return floatBits(recovered_limited_lerp_a260(single(a[0]),single(a[1]),single(a[2]),image));
    case 0x741d0: return std::uintptr_t(recovered_color_blend_741d0(static_cast<float *>(pointer(a[0])),static_cast<const float *>(pointer(a[1])),static_cast<const float *>(pointer(a[2])),single(a[3]),image));
    case 0x11180: return recovered_widget_hover_11180(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<const float *>(pointer(a[1])));
    case 0x111f0: return recovered_widget_click_111f0(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<const float *>(pointer(a[1])));
    case 0x11270: recovered_widget_capture_11270(static_cast<std::uint8_t *>(pointer(a[0])));return 0;
    case 0x11290: recovered_widget_action_11290(static_cast<std::uint8_t *>(pointer(a[0])),a[1],a[2]);return 0;
    case 0x112d0: recovered_widget_input_112d0(static_cast<std::uint8_t *>(pointer(a[0])),a[1],a[2]);return 0;
    case 0x11340: return recovered_widget_identity_11340(static_cast<std::uint8_t *>(pointer(a[0])),a[1]);
    case 0x11370: recovered_widget_release_11370(static_cast<std::uint8_t *>(pointer(a[0])));return 0;
    case 0x11390: return std::uintptr_t(recovered_widget_take_text_11390(static_cast<std::uint8_t *>(pointer(a[0]))));
    case 0x113d0: return std::uintptr_t(recovered_widget_text_113d0(static_cast<std::uint8_t *>(pointer(a[0]))));
    case 0x13b20: return recovered_toggle_widget_13b20(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<std::uint8_t *>(pointer(a[1])),static_cast<float *>(pointer(a[2])),static_cast<std::uint8_t *>(pointer(a[3])),static_cast<std::uint8_t *>(pointer(a[4])),image,invokeFrame);
    case 0x13d90: return recovered_checkbox_widget_13d90(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<std::uint8_t *>(pointer(a[1])),static_cast<const char *>(pointer(a[2])),static_cast<std::uint8_t *>(pointer(a[3])),static_cast<std::uint8_t *>(pointer(a[4])),image,invokeFrame);
    case 0x10340: ui::selectFont_10340(static_cast<std::uint8_t *>(pointer(a[0])),std::uint32_t(a[1]));return 0;
    case 0x10860: return std::uintptr_t(ui::nextColumnRect_10860(static_cast<float *>(pointer(a[0])),static_cast<std::uint8_t *>(pointer(a[1])),single(a[2]),image));
    case 0x10a60: ui::fillRoundedRect_10a60(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<float *>(pointer(a[1])),single(a[2]),image,fonts);return 0;
    case 0x10cb0: return floatBits(ui::drawAlignedText_10cb0(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<float *>(pointer(a[1])),std::uint32_t(a[2]),std::uint32_t(a[3]),static_cast<const char *>(pointer(a[4])),image,fonts));
    case 0x10f30: return ui::processInputWord_10f30(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<std::uint8_t *>(pointer(a[1])),image,inputIncomingRsi,interface);
    case 0x12ab0: return static_cast<std::uint8_t *>(pointer(a[0]))[0x4cb];
    case 0x165f0: ui::resetModal_165f0(static_cast<std::uint8_t *>(pointer(a[0])),image,interface);return 0;
    case 0x169c0: ui::finishModal_169c0(static_cast<std::uint8_t *>(pointer(a[0])),std::uint8_t(a[1]),image,interface);return 0;
    case 0x74a60: drawing::setGlobalAlpha_74a60(static_cast<std::uint8_t *>(pointer(a[0])),single(a[1]));return 0;
    case 0x74ef0: drawing::setFillColor_74ef0(static_cast<std::uint8_t *>(pointer(a[0])),pointer(a[1]),image);return 0;
    case 0x75bc0: drawing::beginPath_75bc0(static_cast<std::uint8_t *>(pointer(a[0])));return 0;
    case 0x75c30: drawing::appendCommands_75c30(static_cast<std::uint8_t *>(pointer(a[0])),static_cast<float *>(pointer(a[1])),std::uint32_t(a[2]),fonts);return 0;
    case 0x76a10: drawing::roundedRectVarying_76a10(static_cast<std::uint8_t *>(pointer(a[0])),single(a[1]),single(a[2]),single(a[3]),single(a[4]),single(a[5]),single(a[6]),single(a[7]),single(a[8]),image,fonts);return 0;
    case 0x77210: drawing::fill_77210(static_cast<std::uint8_t *>(pointer(a[0])),fonts);return 0;
    case 0x79610: drawing::setFontSize_79610(static_cast<std::uint8_t *>(pointer(a[0])),single(a[1]));return 0;
    case 0x79630: drawing::setFontBlur_79630(static_cast<std::uint8_t *>(pointer(a[0])),single(a[1]));return 0;
    case 0x79650: drawing::setLetterSpacing_79650(static_cast<std::uint8_t *>(pointer(a[0])),single(a[1]));return 0;
    case 0x79670: drawing::setLineHeight_79670(static_cast<std::uint8_t *>(pointer(a[0])),single(a[1]));return 0;
    case 0x79690: drawing::setTextAlignment_79690(static_cast<std::uint8_t *>(pointer(a[0])),std::uint32_t(a[1]));return 0;
    case 0x796b0: drawing::setFontIndex_796b0(static_cast<std::uint8_t *>(pointer(a[0])),std::uint32_t(a[1]));return 0;
    case 0x79770: return floatBits(drawing::text_79770(static_cast<std::uint8_t *>(pointer(a[0])),single(a[1]),single(a[2]),static_cast<const char *>(pointer(a[3])),static_cast<const char *>(pointer(a[4])),image,fonts));
    case 0x7ae90: return floatBits(drawing::textBounds_7ae90(static_cast<std::uint8_t *>(pointer(a[0])),single(a[1]),single(a[2]),static_cast<const char *>(pointer(a[3])),static_cast<const char *>(pointer(a[4])),static_cast<float *>(pointer(a[5])),image,fonts));
    case 0x9b00: return recovered_box_ray_point_9b00(vector(a[0]),vector(a[1]),vector(a[2]),vector(a[3]),image);
    case 0x9dc0: return recovered_angle_pack_9dc0(single(a[0]),single(a[1]));
    case 0xa070: return std::uintptr_t(recovered_rect_a070(static_cast<float *>(pointer(a[0])),single(a[1]),single(a[2]),single(a[3]),single(a[4])));
    case 0xa280: return floatBits(recovered_smooth_a280(single(a[0]),image));
    case 0xa2f0: return recovered_chunk_coordinate_a2f0(std::uint32_t(a[0]));
    case 0xa300: return recovered_block_coordinate_a300(std::uint32_t(a[0]));
    case 0xa870: return floatBits(recovered_random_segment_a870(static_cast<SmoothRandomState *>(pointer(a[0])),a[1],binary64(a[2]),binary64(a[3]),&native.random,image));
    case 0x74130: return std::uintptr_t(recovered_color_74130(static_cast<std::uint32_t *>(pointer(a[0])),std::uint32_t(a[1]),std::uint32_t(a[2]),std::uint32_t(a[3])));
    case 0x74150: return std::uintptr_t(recovered_color_74150(static_cast<float *>(pointer(a[0])),single(a[1]),single(a[2]),single(a[3]),single(a[4])));
    case 0x741b0: return std::uintptr_t(recovered_color_741b0(static_cast<float *>(pointer(a[0])),static_cast<float *>(pointer(a[1])),single(a[2])));
    case 0xdf90: return std::uintptr_t(recovered_sorted_insert_df90(pointer(a[0]),std::uint32_t(a[1]),pointer(a[2]),pointer(a[3]),a[4],invokeFrame,native.listMemory));
    case 0xe0b0: return std::uintptr_t(recovered_unique_insert_e0b0(pointer(a[0]),std::uint32_t(a[1]),pointer(a[2]),pointer(a[3]),a[4],invokeFrame,native.listMemory));
    case 0xe1d0: return std::uintptr_t(recovered_remove_index_e1d0(pointer(a[0]),std::uint32_t(a[1]),pointer(a[2]),std::uint32_t(a[3]),native.listMemory));
    case 0xe210: return std::uintptr_t(recovered_remove_pointer_e210(pointer(a[0]),std::uint32_t(a[1]),pointer(a[2]),pointer(a[3]),native.listMemory));
    case 0xe3c0: return std::uint32_t(recovered_catalog_find_identifier(static_cast<const char *>(pointer(a[0])),&catalog));
    case 0xe420: return std::uintptr_t(recovered_catalog_find_name(std::int32_t(a[0]),&catalog));
    case 0xc3b0: recovered_boolean_settings(static_cast<SettingsContext *>(pointer(a[0])),static_cast<const char *>(pointer(a[1])),static_cast<BooleanSetting *>(pointer(a[2])),&settings.boolean);return 0;
    case 0xc450: recovered_number_settings(static_cast<SettingsContext *>(pointer(a[0])),static_cast<const char *>(pointer(a[1])),static_cast<NumberSetting *>(pointer(a[2])),&settings.values);return 0;
    case 0xc7e0: recovered_color_settings(static_cast<SettingsContext *>(pointer(a[0])),static_cast<const char *>(pointer(a[1])),static_cast<ColorSetting *>(pointer(a[2])),&settings.colors);return 0;
    case 0xc6f0: recovered_choice_settings(static_cast<SettingsContext *>(pointer(a[0])),static_cast<const char *>(pointer(a[1])),static_cast<ChoiceSetting *>(pointer(a[2])),&settings.values);return 0;
    case 0xc550: recovered_range_settings(static_cast<SettingsContext *>(pointer(a[0])),static_cast<const char *>(pointer(a[1])),static_cast<RangeSetting *>(pointer(a[2])),&settings.colors);return 0;
    case 0xca00: recovered_list_settings(static_cast<SettingsContext *>(pointer(a[0])),static_cast<const char *>(pointer(a[1])),static_cast<ListSetting *>(pointer(a[2])),&settings.lists);return 0;
    case 0xcef0: return recovered_ui_checkbox_cef0(a[0],a[1],static_cast<std::uint8_t *>(pointer(a[2])),image,invokeFrame);
    case 0xcf30: return recovered_ui_number_cf30(a[0],a[1],static_cast<std::uint8_t *>(pointer(a[2])),image,invokeFrame);
    case 0xcfb0: return recovered_ui_range_cfb0(a[0],a[1],static_cast<std::uint8_t *>(pointer(a[2])),image,invokeFrame);
    case 0xd040: return recovered_ui_choice_d040(a[0],a[1],static_cast<std::uint8_t *>(pointer(a[2])),image,invokeFrame);
    case 0xd0a0: return recovered_ui_color_d0a0(a[0],a[1],static_cast<std::uint8_t *>(pointer(a[2])),image,invokeFrame);
    case 0xd0e0: return recovered_ui_list_d0e0(a[0],a[1],static_cast<std::uint8_t *>(pointer(a[2])),image,invokeFrame);
    case 0x13e90: return recovered_ui_section_13e90(a[0],a[1],static_cast<const char *>(pointer(a[2])),image,invokeFrame);
    case 0x9380: return std::uintptr_t(recovered_key_name_9380(std::uint32_t(a[0]), image));
    case 0x93b0: return std::uintptr_t(recovered_geometry_construct_93b0(pointer(a[0]), binary64(a[1]), binary64(a[2]), binary64(a[3])));
    case 0x93d0: return std::uintptr_t(recovered_vector_subtract_93d0(vector(a[0]), vector(a[1]), vector(a[2])));
    case 0x9430: return std::uintptr_t(recovered_vector_scale_9430(vector(a[0]), vector(a[1]), binary64(a[2])));
    case 0x9460: return std::uintptr_t(recovered_vector_lerp_9460(vector(a[0]), vector(a[1]), vector(a[2]), binary64(a[3])));
    case 0x9650: return std::uintptr_t(recovered_vector_reciprocal_9650(vector(a[0]), vector(a[1]), image));
    case 0x9770: return std::uintptr_t(recovered_box_expand_9770(vector(a[0]), vector(a[1]), binary64(a[2])));
    case 0x98e0: return recovered_box_ray_98e0(vector(a[0]), vector(a[1]), vector(a[2]), image);
    case 0x9f60: return recovered_angle_magnitude_9f60(a[0], &native.distanceConstants);
    case 0xb1cf0: return floatBits(recovered_sine_b1cf0(single(a[0]), image));
    case 0xb3590: return floatBits(recovered_cosine_b3590(single(a[0]), image));
    case 0xaf2f0: return std::bit_cast<Word>(recovered_square_root_af2f0(binary64(a[0]), image));
    case 0xaf4a0: return floatBits(recovered_square_root_af4a0(single(a[0]), image));
    case 0xb1990: return std::bit_cast<Word>(recovered_sine_b1990(binary64(a[0]), image));
    case 0xaec00: return std::uint32_t(recovered_reduce_double_aec00(binary64(a[0]), vector(a[1]), image));
    case 0x4c270: return recovered_clock_bits(clockFrequencyBits, encodedFrequencyTarget, encodedCounterTarget);
    case 0xab840: return recovered_string_length_ab840(static_cast<const std::uint8_t *>(pointer(a[0])));
    case 0xab860: return recovered_bytes_compare_ab860(static_cast<const std::uint8_t *>(pointer(a[0])), static_cast<const std::uint8_t *>(pointer(a[1])), a[2]);
    case 0xab890: return std::uintptr_t(recovered_bytes_fill_ab890(pointer(a[0]), std::uint8_t(a[1]), a[2]));
    case 0xab910: return std::uintptr_t(recovered_memory_move(pointer(a[0]), pointer(a[1]), a[2]));
    case 0xabbf0: return std::uintptr_t(recovered_memory_copy(pointer(a[0]), pointer(a[1]), a[2]));
    case 0xe310: return recovered_list_growth(pointer(a[0]), a[1], a[2], pointer(a[3]), listGrowthIncomingRsi, &native.listMemory);
    case 0x2b1c0: return std::uintptr_t(aim_assist::currentTarget(image));
    case 0x28b40: return teams::prefixColor(static_cast<GameAccessBridge *>(pointer(a[0])), a[1]);
    case 0x28d20: return teams::componentColor(static_cast<GameAccessBridge *>(pointer(a[0])), a[1]);
    case 0x28e10: return teams::entityColor(static_cast<GameAccessBridge *>(pointer(a[0])), a[1]);
    case 0xdc20: recovered_text_initialize_dc20(static_cast<std::uint8_t *>(pointer(a[0])), static_cast<std::uint8_t *>(pointer(a[1])), a[2]); return 0;
    case 0xdc40: return recovered_text_append_dc40(static_cast<std::uint8_t *>(pointer(a[0])), static_cast<const char *>(pointer(a[1])), invokeFour);
    case 0xdca0: return recovered_text_format_dca0(static_cast<std::uint8_t *>(pointer(a[0])), static_cast<const char *>(pointer(a[1])), static_cast<const Word *>(pointer(a[2])), invokeFour);
    case 0xdd10: return recovered_text_byte_dd10(static_cast<std::uint8_t *>(pointer(a[0])), std::uint8_t(a[1]));
    case 0xdd40: return recovered_text_finish_dd40(static_cast<std::uint8_t *>(pointer(a[0])));
    case 0x293c0: return recovered_render_293c0(image, invokeFour);
    case 0x29400: return recovered_render_29400(image, invokeFour);
    case 0x29430: return recovered_render_29430(image, invokeFour);
    case 0x29460: return recovered_render_29460(image, invokeFour);
    case 0x294a0: return recovered_render_294a0(image, invokeFour);
    case 0x294d0: return recovered_render_294d0(image, invokeFour);
    case 0x29500: return recovered_render_29500(image, invokeFour);
    case 0x29540: return recovered_render_29540(image, invokeFour);
    case 0x29570: return recovered_render_29570(image, invokeFour);
    case 0x295a0: return recovered_render_295a0(image, invokeFour);
    case 0x295c0: return recovered_screen_project_295c0(static_cast<std::uint8_t *>(pointer(a[0])), vector(a[1]), static_cast<float *>(pointer(a[2])), image);
    case 0x295f0: return recovered_screen_project_295f0(static_cast<std::uint8_t *>(pointer(a[0])), vector(a[1]), static_cast<float *>(pointer(a[2])), static_cast<float *>(pointer(a[3])), image);
    default: return boundary(user, target, arguments, count);
    }
}
} // namespace reconstruction::native_binding
#endif // SLINKY_SHARE_E0D4B122475CF848371D
