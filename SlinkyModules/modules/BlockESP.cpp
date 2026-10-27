// Block ESP

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Block_ESP.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Block_ESP.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Block ESP: lib_win settings 0x3fbe0.
static constexpr SettingsStep settings_steps_Surface_Block_ESP[] = {
    {SettingsControl::number, "range", 0x2f1a28},
    {SettingsControl::list, "allowed_blocks", 0x2f1950},
    {SettingsControl::boolean, "should_limit_block_render", 0x2f1a60},
    {SettingsControl::number, "block_render_limit", 0x2f19f0},
    {SettingsControl::number, "line_width", 0x2f19b8},
};
static constexpr ModuleSurface surface_Surface_Block_ESP{
    nullptr, 0, settings_steps_Surface_Block_ESP, std::size(settings_steps_Surface_Block_ESP)};

extern "C" __declspec(dllexport) void
recovered_block_esp_settings(SettingsContext *context, std::uint8_t *image,
                             const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Block_ESP, context, image, *dependencies);
}

// Block ESP: lib_win runtime UI 0x3fb30.
extern "C" __declspec(dllexport) void
recovered_block_esp_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                       const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2f1a28);
    dependencies->list(layout, ui, image + 0x2f1950);
    dependencies->section(ui, layout, "Block render limit");
    dependencies->checkbox(layout, ui, image + 0x2f1a60);
    if (image[0x2f1a78] == 1) {
        dependencies->number(layout, ui, image + 0x2f19f0);
    }
    dependencies->section(ui, layout, "Customization");
    dependencies->number(layout, ui, image + 0x2f19b8);
}
// END SOURCE native/verified/surfaces/Surface_Block_ESP.cpp

// BEGIN SOURCE shared/BoundSurfaces.cpp@Block_ESP
// Same native ordering as reconstruction/native/verified/surfaces/Surface_Block_ESP.cpp
extern "C" __declspec(dllexport) void
recovered_block_esp_bound_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                             const BoundSurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2f1a28);
    dependencies->list(layout, ui, image + 0x2f1950);
    dependencies->section(ui, layout, "Block render limit");
    dependencies->checkbox(layout, ui, image + 0x2f1a60);
    if (image[0x2f1a78] == 1) {
        dependencies->number(layout, ui, image + 0x2f19f0);
    }
    dependencies->section(ui, layout, "Customization");
    dependencies->number(layout, ui, image + 0x2f19b8);
}
// END SOURCE shared/BoundSurfaces.cpp@Block_ESP

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Block_ESP/block_esp_lifecycle.cpp
#ifndef SLINKY_SHARE_49335D3339ED17ACC90E
#define SLINKY_SHARE_49335D3339ED17ACC90E
// BEGIN SOURCE modules/Block_ESP/Module.hpp
#include "../runtime/shared/RenderNativeBindings.hpp"
#include "../runtime/native/verified/module_esp_lists.hpp"
#include "../runtime/native/verified/module_surface.hpp"
#include "../runtime/shared/Geometry.hpp"
#include <cstddef>
#include <cstdint>

// These are the existing verified shared UI/configuration implementations.
extern "C" void recovered_block_esp_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                             const BoundSurfaceUiDependencies *);
extern "C" void recovered_block_esp_settings(SettingsContext *, std::uint8_t *,
                                             const SurfaceSettingsDependencies *);

namespace reconstruction::block_esp {
// The image view retains native storage offsets. It does not invent initialization.
using Dependency5 = reconstruction::native_binding::RenderEndpoint<4, std::uint32_t>;
using Endpoint5 = reconstruction::native_binding::RenderEndpoint<4, std::uint64_t>;
using BlockEndpoint = reconstruction::native_binding::RenderEndpoint<5, std::uint64_t>;
struct BlockPositionRecord {
    std::uint8_t x, y, z, reserved[5];
    std::uintptr_t policy;
};
struct BlockRegionRecord {
    std::uint64_t key, count, capacity;
    std::uintptr_t positions;
    std::uint64_t vertexCount, vertexCapacity;
    std::uintptr_t vertices;
    std::uint64_t indexCount, indexCapacity;
    std::uintptr_t indices;
};
static_assert(sizeof(BlockPositionRecord) == 16);
static_assert(sizeof(BlockRegionRecord) == 80);
__declspec(dllexport) void updateWorld(uint8_t *event, uint8_t *image, std::uintptr_t nativeBase,
                                       BlockEndpoint call);
__declspec(dllexport) void onModuleStateChanged(uint8_t *event, uint8_t *image,
                                                std::uintptr_t nativeBase, BlockEndpoint call);
__declspec(dllexport) void onBlockEvent(uint8_t *event, uint8_t *image, std::uintptr_t nativeBase,
                                        BlockEndpoint call);
__declspec(dllexport) void releaseCollections(uint8_t *event, uint8_t *image, BlockEndpoint call);
__declspec(dllexport) void renderBlocks(uint8_t *event, uint8_t *image, Endpoint5 call);

inline void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *stateImage,
                           const BoundSurfaceUiDependencies &deps) {
    recovered_block_esp_bound_ui(ui, layout, stateImage, &deps);
}
inline void serializeConfig(SettingsContext *context, std::uint8_t *stateImage,
                            const SurfaceSettingsDependencies &deps) {
    recovered_block_esp_settings(context, stateImage, &deps);
}
} // namespace reconstruction::block_esp

namespace reconstruction::block_esp {
void releaseWorldCollection(std::uint8_t *, BlockEndpoint);
std::int32_t compareRegionKey(const void *, const void *);
void releaseRegion(std::uint8_t *, BlockEndpoint);
void rebuildMesh(std::uint8_t *, std::uint8_t *, BlockEndpoint);
std::uint8_t *findOrCreateRegion(std::uint64_t, std::uint8_t *, std::uintptr_t, BlockEndpoint);
void scanByteIds(std::uint32_t, std::uint32_t, std::uint32_t, const std::uint8_t *, std::uint8_t **,
                 std::uint8_t *, std::uintptr_t, BlockEndpoint);
void scanPackedIds(std::uint32_t, std::uint32_t, std::uint32_t, const std::uint8_t *,
                   std::uint8_t **, std::uint8_t *, std::uintptr_t, BlockEndpoint);
void appendCatalogCharacter(char *, std::uint8_t, BlockEndpoint);
void onRegionChange(std::uint8_t *, std::uint8_t *, std::uintptr_t, BlockEndpoint);
void collectLoadedRegions(std::uint8_t *, std::uint8_t *, std::uintptr_t, BlockEndpoint);
} // namespace reconstruction::block_esp

namespace reconstruction::block_esp::setting_offset {
// Config keys identify storage. These constants assert no initial values.
inline constexpr std::size_t range = 0x2f1a28 + offsetof(NumberSetting, current);
inline constexpr std::size_t should_limit_block_render =
    0x2f1a60 + offsetof(BooleanSetting, current);
inline constexpr std::size_t block_render_limit = 0x2f19f0 + offsetof(NumberSetting, current);
inline constexpr std::size_t line_width = 0x2f19b8 + offsetof(NumberSetting, current);
} // namespace reconstruction::block_esp::setting_offset
// END SOURCE modules/Block_ESP/Module.hpp

#endif // SLINKY_SHARE_49335D3339ED17ACC90E

#include <stdint.h>
#include <string.h>
#define API __declspec(dllexport)
using Dispatch = reconstruction::block_esp::BlockEndpoint;
static uint64_t readWord_block_esp_lifecycle(const void *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static uint8_t *ptr_block_esp_lifecycle(uint64_t v) {
    return (uint8_t *)(uintptr_t)v;
}
static void w(void *p, uint64_t v) {
    memcpy(p, &v, 8);
}
void reconstruction::block_esp::releaseWorldCollection(uint8_t *stateImage,
                                                       Dispatch invokeEndpoint) {
    if (readWord_block_esp_lifecycle(stateImage + 0x3020f0))
        for (uint64_t n = 0, off = 0;; off += 0x50) {
            uint8_t *entry =
                ptr_block_esp_lifecycle(readWord_block_esp_lifecycle(stateImage + 0x302100)) + off;
            memset(entry + 8, 0, 16);
            invokeEndpoint(0x13cf70, readWord_block_esp_lifecycle(entry + 0x18), 0, 0, 0, 0);
            memset(entry + 0x18, 0, 16);
            memset(entry + 0x28, 0, 8);
            invokeEndpoint(0x13cf70, readWord_block_esp_lifecycle(entry + 0x30), 0, 0, 0, 0);
            memset(entry + 0x30, 0, 16);
            memset(entry + 0x40, 0, 8);
            invokeEndpoint(0x13cf70, readWord_block_esp_lifecycle(entry + 0x48), 0, 0, 0, 0);
            memset(entry + 0x48, 0, 8);
            if (++n >= readWord_block_esp_lifecycle(stateImage + 0x3020f0))
                break;
        }
    memset(stateImage + 0x3020f0, 0, 16);
    invokeEndpoint(0x13cf70, readWord_block_esp_lifecycle(stateImage + 0x302100), 0, 0, 0, 0);
    memset(stateImage + 0x302100, 0, 8);
}
API void reconstruction::block_esp::updateWorld(uint8_t *event, uint8_t *stateImage,
                                                uintptr_t nativeBase, Dispatch invokeEndpoint) {
    uint8_t *gameContext = ptr_block_esp_lifecycle(readWord_block_esp_lifecycle(event + 8));
    if (gameContext[0x40] == 1 && stateImage[0x2f19b0]) {
        if (readWord_block_esp_lifecycle(stateImage + 0x3020f0))
            for (uint64_t n = 0, off = 0;; off += 0x50) {
                reconstruction::block_esp::rebuildMesh(
                    ptr_block_esp_lifecycle(readWord_block_esp_lifecycle(stateImage + 0x302100)) +
                        off,
                    stateImage, invokeEndpoint);
                if (++n >= readWord_block_esp_lifecycle(stateImage + 0x3020f0))
                    break;
            }
        stateImage[0x2f19b0] = 0;
    }
    uint64_t world = readWord_block_esp_lifecycle(gameContext + 0x20);
    if (world) {
        invokeEndpoint(0x26060, readWord_block_esp_lifecycle(gameContext), world, 0, 0, 0);
        if (stateImage[0x302108] != 1)
            return;
        reconstruction::block_esp::releaseWorldCollection(stateImage, invokeEndpoint);
        reconstruction::block_esp::collectLoadedRegions(gameContext, stateImage, nativeBase,
                                                        invokeEndpoint);
        stateImage[0x302108] = 0;
    } else
        reconstruction::block_esp::releaseWorldCollection(stateImage, invokeEndpoint);
}
API void reconstruction::block_esp::onModuleStateChanged(uint8_t *event, uint8_t *stateImage,
                                                         uintptr_t nativeBase,
                                                         Dispatch invokeEndpoint) {
    if (readWord_block_esp_lifecycle(event + 0x10) != (uint64_t)(uintptr_t)(stateImage + 0x2f1740))
        return;
    if (event[0x18]) {
        uint8_t *gameContext = ptr_block_esp_lifecycle(readWord_block_esp_lifecycle(event + 8));
        uint32_t kind;
        memcpy(&kind,
               ptr_block_esp_lifecycle(readWord_block_esp_lifecycle(
                   ptr_block_esp_lifecycle(readWord_block_esp_lifecycle(gameContext)))),
               4);
        w(stateImage + 0x302128, nativeBase + (kind ? 0x40af0 : 0x40980));
        if (readWord_block_esp_lifecycle(gameContext + 0x20))
            reconstruction::block_esp::collectLoadedRegions(gameContext, stateImage, nativeBase,
                                                            invokeEndpoint);
    } else
        reconstruction::block_esp::releaseWorldCollection(stateImage, invokeEndpoint);
}
API void reconstruction::block_esp::onBlockEvent(uint8_t *event, uint8_t *stateImage,
                                                 uintptr_t nativeBase, Dispatch invokeEndpoint) {
    reconstruction::block_esp::onRegionChange(event + 8, stateImage, nativeBase, invokeEndpoint);
}
API void reconstruction::block_esp::releaseCollections(uint8_t *event, uint8_t *stateImage,
                                                       Dispatch invokeEndpoint) {
    (void)event;
    memset(stateImage + 0x302110, 0, 16);
    invokeEndpoint(0x13cf70, readWord_block_esp_lifecycle(stateImage + 0x302120), 0, 0, 0, 0);
    memset(stateImage + 0x302120, 0, 8);
    reconstruction::block_esp::releaseWorldCollection(stateImage, invokeEndpoint);
}
// END SOURCE modules/Block_ESP/block_esp_lifecycle.cpp

// BEGIN SOURCE modules/Block_ESP/block_esp_render.cpp
#include "../runtime/shared/RenderNativeBindings.hpp"
// Source-equivalent reconstruction from the supplied native evidence.
// Semantic identifiers were assigned during reverse engineering. Original names,
// namespaces and inline boundaries generally cannot be recovered.
// Reuses
// evidence/recovered_cpp/behavior/module_behavior_recovery/block_esp_render/block_esp_render.cpp
// SHA-256 99129bf8b0bd7b548f99dac85592d015edbe14d378a55ca19235c654212cde68
// Changes rename recovered algorithms and make C pointer/scope rules explicit in C++.
// External endpoint arguments retain native widths, ordering and identities.

#include <emmintrin.h>
#include <stdint.h>
#include <string.h>
using Endpoint = reconstruction::native_binding::RenderEndpoint<4, std::uint64_t>;
static uint64_t readWord_block_esp_render(const void *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t readDword(const void *p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}
static float readFloat(const void *p) {
    float v;
    memcpy(&v, p, 4);
    return v;
}
static double dbl(const void *p) {
    double v;
    memcpy(&v, p, 8);
    return v;
}
static uint64_t db(double v) {
    uint64_t u;
    memcpy(&u, &v, 8);
    return u;
}
static uint32_t floatBits(float v) {
    uint32_t u;
    memcpy(&u, &v, 4);
    return u;
}
static uint8_t *ptr_block_esp_render(uint64_t v) {
    return (uint8_t *)(uintptr_t)v;
}
static uint64_t target(uint8_t *im, uint32_t slot) {
    return readWord_block_esp_render(ptr_block_esp_render(readWord_block_esp_render(im + slot)));
}
__declspec(dllexport) void reconstruction::block_esp::renderBlocks(uint8_t *event,
                                                                   uint8_t *stateImage,
                                                                   Endpoint invokeEndpoint) {
    if (!readWord_block_esp_render(stateImage + 0x3020f0))
        return;
    uint8_t *enable = ptr_block_esp_render(readWord_block_esp_render(stateImage + 0x14fd08));
    invokeEndpoint(readWord_block_esp_render(enable), 0x8074, 0, 0, 0);
    invokeEndpoint(readWord_block_esp_render(enable), 0x8076, 0, 0, 0);
    invokeEndpoint(target(stateImage, 0x150cb0),
                   readDword(stateImage + reconstruction::block_esp::setting_offset::line_width), 0,
                   0, 0);
    float amount = _mm_cvtss_f32(
        _mm_mul_ss(_mm_set_ss(readFloat(
                       stateImage + reconstruction::block_esp::setting_offset::block_render_limit)),
                   _mm_set_ss(readFloat(stateImage + 0x154158))));
    int64_t first = _mm_cvttss_si64(_mm_set_ss(amount));
    float shifted =
        _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(amount), _mm_set_ss(readFloat(stateImage + 0x15415c))));
    int64_t second = _mm_cvttss_si64(_mm_set_ss(shifted));
    uint64_t limit =
        stateImage[reconstruction::block_esp::setting_offset::should_limit_block_render]
            ? ((uint64_t)first | ((uint64_t)second & (first < 0 ? UINT64_MAX : 0)))
            : 0x1000;
    uint64_t count = readWord_block_esp_render(stateImage + 0x3020f0);
    if (count) {
        double scale = dbl(stateImage + 0x154150), cx = dbl(event + 8) * scale,
               cz = scale * dbl(event + 0x18);
        uint8_t *entries = ptr_block_esp_render(readWord_block_esp_render(stateImage + 0x302100));
        float radius = readFloat(stateImage + reconstruction::block_esp::setting_offset::range);
        double midpoint = dbl(stateImage + 0x154160);
        uint8_t *pop = ptr_block_esp_render(readWord_block_esp_render(stateImage + 0x150cb8));
        for (uint64_t entryIndex = 0, off = 0; entryIndex < count; entryIndex++, off += 0x50) {
            double x = cx - ((double)(int32_t)readDword(entries + off) + midpoint);
            double z = cz - ((double)(int32_t)readDword(entries + off + 4) + midpoint);
            uint64_t result = invokeEndpoint(0x13cfd0, db(x), db(z), 0, 0);
            double distance;
            memcpy(&distance, &result, 8);
            if (distance > (double)radius)
                continue;
            invokeEndpoint(target(stateImage, 0x150cc0), 0, 0, 0, 0);
            double position[3] = {(double)(int32_t)(readDword(entries + off) << 4), 0.,
                                  (double)(int32_t)(readDword(entries + off + 4) << 4)};
            double camera[3], relative[3];
            memcpy(camera, event + 8, 24);
            recovered_vector_subtract_93d0(relative, position, camera);
            invokeEndpoint(target(stateImage, 0x150cd8), floatBits((float)relative[0]),
                           floatBits((float)relative[1]), floatBits((float)relative[2]), 0);
            invokeEndpoint(target(stateImage, 0x14fd10), 3, 0x1406, 0x10,
                           readWord_block_esp_render(entries + off + 0x30));
            invokeEndpoint(target(stateImage, 0x154310), 3, 0x1401, 0x10,
                           readWord_block_esp_render(entries + off + 0x30) + 12);
            uint64_t vertices = readWord_block_esp_render(entries + off + 0x38);
            invokeEndpoint(target(stateImage, 0x14fd00), 1, vertices > limit ? limit : vertices,
                           0x1403, readWord_block_esp_render(entries + off + 0x48));
            invokeEndpoint(readWord_block_esp_render(pop), 0, 0, 0, 0);
            entries = ptr_block_esp_render(readWord_block_esp_render(stateImage + 0x302100));
            radius = readFloat(stateImage + reconstruction::block_esp::setting_offset::range);
            count = readWord_block_esp_render(stateImage + 0x3020f0);
        }
    }
    uint8_t *disable = ptr_block_esp_render(readWord_block_esp_render(stateImage + 0x14fcf8));
    invokeEndpoint(readWord_block_esp_render(disable), 0x8074, 0, 0, 0);
    invokeEndpoint(readWord_block_esp_render(disable), 0x8076, 0, 0, 0);
}
// END SOURCE modules/Block_ESP/block_esp_render.cpp

// BEGIN SOURCE modules/Block_ESP/BlockCollection.cpp
#include <bit>
#include <cstring>
#include <emmintrin.h>

namespace reconstruction::block_esp {
namespace {
template <class T> T load(const void *p) {
    T value;
    std::memcpy(&value, p, sizeof value);
    return value;
}
template <class T> void store(void *p, T value) {
    std::memcpy(p, &value, sizeof value);
}
std::uintptr_t address(const void *p) {
    return reinterpret_cast<std::uintptr_t>(p);
}
std::uint64_t jniTarget(std::uintptr_t environment, std::size_t offset) {
    return load<std::uint64_t>(reinterpret_cast<const std::uint8_t *>(load<std::uintptr_t>(
                                   reinterpret_cast<const void *>(environment))) +
                               offset);
}
float addFloat(float left, float right) {
    return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(left), _mm_set_ss(right)));
}
std::uint8_t colorByte(float color, float scale) {
    return static_cast<std::uint8_t>(
        _mm_cvttss_si32(_mm_mul_ss(_mm_set_ss(color), _mm_set_ss(scale))));
}
std::uint32_t chunkCoordinate(std::uint32_t position) {
    return static_cast<std::uint32_t>(std::bit_cast<std::int32_t>(position) >> 4);
}
bool grow(std::uint8_t *data, std::uint64_t stride, std::uint64_t count, std::uint8_t *capacity,
          BlockEndpoint invoke) {
    return static_cast<std::uint8_t>(
               invoke(0xe310, address(data), stride, count, address(capacity), 0)) != 0;
}
std::uint8_t *searchRegion(std::uint64_t key, std::uint8_t *image, std::uintptr_t nativeBase,
                           BlockEndpoint invoke) {
    if (!load<std::uintptr_t>(image + 0x302100))
        return nullptr;
    return reinterpret_cast<std::uint8_t *>(
        invoke(0x13d0e0, address(&key), load<std::uintptr_t>(image + 0x302100),
               load<std::uint64_t>(image + 0x3020f0), 80, nativeBase + 0x40960));
}
std::uint8_t *insertRegion(std::uint64_t key, std::uint8_t *image, BlockEndpoint invoke) {
    const auto count = load<std::uint64_t>(image + 0x3020f0);
    auto *records = reinterpret_cast<std::uint8_t *>(load<std::uintptr_t>(image + 0x302100));
    std::uint64_t slot = 0;
    for (; slot < count; ++slot)
        if (compareRegionKey(&key, records + slot * 80) <= 0)
            break;
    if (!grow(image + 0x302100, 80, load<std::uint64_t>(image + 0x3020f0), image + 0x3020f8,
              invoke))
        return nullptr;
    records = reinterpret_cast<std::uint8_t *>(load<std::uintptr_t>(image + 0x302100));
    auto *record = records + slot * 80;
    invoke(0xab910, address(record + 80), address(record),
           (load<std::uint64_t>(image + 0x3020f0) - slot) * 80, 0, 0);
    store(record, key);
    std::memset(record + 8, 0, 72);
    store(image + 0x3020f0, load<std::uint64_t>(image + 0x3020f0) + 1);
    // The original helper reloads the global base after moving and filling records.
    return reinterpret_cast<std::uint8_t *>(load<std::uintptr_t>(image + 0x302100)) + slot * 80;
}
void removeRegion(std::uint8_t *record, std::uint8_t *image, BlockEndpoint invoke) {
    releaseRegion(record, invoke);
    const auto count = load<std::uint64_t>(image + 0x3020f0);
    const auto distance = address(record) - load<std::uintptr_t>(image + 0x302100);
    const auto remaining = count + (distance >> 4) * UINT64_C(0x3333333333333333) - 1;
    store(image + 0x3020f0, count - 1);
    invoke(0xab910, address(record), address(record + 80), remaining * 80, 0, 0);
}
bool appendBlock(std::uint8_t *region, std::uint8_t x, std::uint8_t y, std::uint8_t z,
                 std::uintptr_t policy, BlockEndpoint invoke) {
    if (!grow(region + 24, 16, load<std::uint64_t>(region + 8), region + 16, invoke))
        return false;
    auto *block = reinterpret_cast<std::uint8_t *>(load<std::uintptr_t>(region + 24)) +
                  load<std::uint64_t>(region + 8) * 16;
    block[0] = x;
    block[1] = y;
    block[2] = z;
    std::memset(block + 3, 0, 5);
    store(block + 8, policy);
    store(region + 8, load<std::uint64_t>(region + 8) + 1);
    return true;
}
} // namespace

std::int32_t compareRegionKey(const void *left, const void *right) {
    auto difference = load<std::uint32_t>(left) - load<std::uint32_t>(right);
    if (difference == 0)
        difference = load<std::uint32_t>(static_cast<const std::uint8_t *>(left) + 4) -
                     load<std::uint32_t>(static_cast<const std::uint8_t *>(right) + 4);
    return std::bit_cast<std::int32_t>(difference);
}

void releaseRegion(std::uint8_t *region, BlockEndpoint invoke) {
    std::memset(region + 8, 0, 16);
    invoke(0x13cf70, load<std::uintptr_t>(region + 24), 0, 0, 0, 0);
    std::memset(region + 24, 0, 24);
    invoke(0x13cf70, load<std::uintptr_t>(region + 48), 0, 0, 0, 0);
    std::memset(region + 48, 0, 24);
    invoke(0x13cf70, load<std::uintptr_t>(region + 72), 0, 0, 0, 0);
    std::memset(region + 72, 0, 8);
}

void rebuildMesh(std::uint8_t *region, std::uint8_t *stateImage, BlockEndpoint invoke) {
    store(region + 32, std::uint64_t(0));
    store(region + 56, std::uint64_t(0));
    if (!load<std::uint64_t>(region + 8))
        return;
    const auto colorScale = load<float>(stateImage + 0x154168);
    std::uint64_t blockIndex = 0;
    do {
        auto *block =
            reinterpret_cast<std::uint8_t *>(load<std::uintptr_t>(region + 24)) + blockIndex * 16;
        auto *policy = reinterpret_cast<const std::uint8_t *>(load<std::uintptr_t>(block + 8));
        const std::uint8_t color[4] = {colorByte(load<float>(policy + 8), colorScale),
                                       colorByte(load<float>(policy + 12), colorScale),
                                       colorByte(load<float>(policy + 16), colorScale), 0xff};
        const auto firstVertex = load<std::uint64_t>(region + 32);
        for (std::uint32_t corner = 0; corner < 8; ++corner) {
            const auto packed = load<std::uint64_t>(block);
            const auto xy = load<std::uint64_t>(stateImage + 0x1541b0 + corner * 12);
            const auto z = load<float>(stateImage + 0x1541b8 + corner * 12);
            if (!grow(region + 48, 16, load<std::uint64_t>(region + 32), region + 40, invoke))
                return;
            auto *vertex = reinterpret_cast<std::uint8_t *>(load<std::uintptr_t>(region + 48)) +
                           load<std::uint64_t>(region + 32) * 16;
            const float position[3] = {
                addFloat(std::bit_cast<float>(static_cast<std::uint32_t>(xy)),
                         static_cast<float>(static_cast<std::uint8_t>(packed))),
                addFloat(std::bit_cast<float>(static_cast<std::uint32_t>(xy >> 32)),
                         static_cast<float>(static_cast<std::uint8_t>(packed >> 8))),
                addFloat(z, static_cast<float>(static_cast<std::uint8_t>(packed >> 16)))};
            std::memcpy(vertex, position, 12);
            std::memcpy(vertex + 12, color, 4);
            store(region + 32, load<std::uint64_t>(region + 32) + 1);
        }
        for (std::uint32_t index = 0; index < 24; ++index) {
            const auto baseIndex = load<std::uint16_t>(stateImage + 0x154210 + index * 2);
            if (!grow(region + 72, 2, load<std::uint64_t>(region + 56), region + 64, invoke))
                return;
            auto *destination =
                reinterpret_cast<std::uint8_t *>(load<std::uintptr_t>(region + 72)) +
                load<std::uint64_t>(region + 56) * 2;
            store(destination,
                  static_cast<std::uint16_t>(baseIndex + static_cast<std::uint16_t>(firstVertex)));
            store(region + 56, load<std::uint64_t>(region + 56) + 1);
        }
    } while (++blockIndex < load<std::uint64_t>(region + 8));
}

std::uint8_t *findOrCreateRegion(std::uint64_t key, std::uint8_t *stateImage,
                                 std::uintptr_t nativeBase, BlockEndpoint invoke) {
    if (auto *found = searchRegion(key, stateImage, nativeBase, invoke))
        return found;
    return insertRegion(key, stateImage, invoke);
}

void scanByteIds(std::uint32_t chunkX, std::uint32_t section, std::uint32_t chunkZ,
                 const std::uint8_t *data, std::uint8_t **region, std::uint8_t *stateImage,
                 std::uintptr_t nativeBase, BlockEndpoint invoke) {
    if (!load<std::uint64_t>(stateImage + 0x302110))
        return;
    const auto key = std::uint64_t(chunkX) | (std::uint64_t(chunkZ) << 32);
    std::uint64_t policyIndex = 0;
    do {
        auto *policy =
            reinterpret_cast<const std::uint8_t *>(load<std::uintptr_t>(stateImage + 0x302120)) +
            policyIndex * 24;
        const auto identifier = _mm_set1_epi8(static_cast<char>(load<std::uint32_t>(policy + 20)));
        for (std::uint64_t group = 0; group < 256; ++group) {
            const auto mask = static_cast<std::uint16_t>(_mm_movemask_epi8(_mm_cmpeq_epi8(
                _mm_loadu_si128(reinterpret_cast<const __m128i *>(data + group * 16)),
                identifier)));
            if (mask)
                for (std::uint32_t bit = 0; bit < 16; ++bit)
                    if ((mask >> bit) & 1) {
                        if (!*region) {
                            *region = findOrCreateRegion(key, stateImage, nativeBase, invoke);
                            if (!*region)
                                return;
                        }
                        if (!appendBlock(*region, static_cast<std::uint8_t>(bit),
                                         static_cast<std::uint8_t>((group >> 4) + section * 16),
                                         static_cast<std::uint8_t>(group & 15), address(policy),
                                         invoke))
                            return;
                    }
        }
    } while (++policyIndex < load<std::uint64_t>(stateImage + 0x302110));
}

void scanPackedIds(std::uint32_t chunkX, std::uint32_t section, std::uint32_t chunkZ,
                   const std::uint8_t *data, std::uint8_t **region, std::uint8_t *stateImage,
                   std::uintptr_t nativeBase, BlockEndpoint invoke) {
    if (!load<std::uint64_t>(stateImage + 0x302110))
        return;
    const auto key = std::uint64_t(chunkX) | (std::uint64_t(chunkZ) << 32);
    std::uint64_t policyIndex = 0;
    do {
        auto *policy =
            reinterpret_cast<const std::uint8_t *>(load<std::uintptr_t>(stateImage + 0x302120)) +
            policyIndex * 24;
        const auto identifier =
            _mm_set1_epi16(static_cast<short>(load<std::uint32_t>(policy + 20)));
        for (std::uint64_t group = 0; group < 512; ++group) {
            const auto shifted = _mm_srai_epi16(
                _mm_loadu_si128(reinterpret_cast<const __m128i *>(data + group * 16)), 4);
            const auto mask =
                static_cast<std::uint16_t>(_mm_movemask_epi8(_mm_cmpeq_epi16(shifted, identifier)));
            if (mask)
                for (std::uint32_t bit = 0; bit < 16; bit += 2)
                    if ((mask >> bit) & 3) {
                        if (!*region) {
                            *region = findOrCreateRegion(key, stateImage, nativeBase, invoke);
                            if (!*region)
                                return;
                        }
                        if (!appendBlock(*region,
                                         static_cast<std::uint8_t>(((group & 1) << 3) + (bit >> 1)),
                                         static_cast<std::uint8_t>((group >> 5) + section * 16),
                                         static_cast<std::uint8_t>((group >> 1) & 15),
                                         address(policy), invoke))
                            return;
                    }
        }
    } while (++policyIndex < load<std::uint64_t>(stateImage + 0x302110));
}

void appendCatalogCharacter(char *text, std::uint8_t character, BlockEndpoint invoke) {
    const auto length = invoke(0xab840, address(text), 0, 0, 0, 0);
    if (length < 100 && (static_cast<std::uint8_t>((character & 0xdf) + 0xbf) < 0x1a ||
                         character == 0x20 || static_cast<std::uint8_t>(character - 0x30) < 10))
        text[length] = static_cast<char>(character);
}

void onRegionChange(std::uint8_t *event, std::uint8_t *stateImage, std::uintptr_t nativeBase,
                    BlockEndpoint invoke) {
    const auto kind = load<std::uint32_t>(event + 16);
    if (kind < 2) {
        const auto key = load<std::uint64_t>(event + 20);
        if (auto *existing = searchRegion(key, stateImage, nativeBase, invoke))
            removeRegion(existing, stateImage, invoke);
        if (load<std::uint32_t>(event + 16) != 1)
            return;
        const auto bridge = load<std::uintptr_t>(event), world = load<std::uint64_t>(event + 8);
        const auto chunkX = load<std::uint32_t>(event + 20),
                   chunkZ = load<std::uint32_t>(event + 24);
        const auto chunk = invoke(0x248f0, bridge, world, chunkX, chunkZ, 0);
        if (!chunk)
            return;
        const auto environment =
            load<std::uintptr_t>(reinterpret_cast<const std::uint8_t *>(bridge) + 8);
        const auto sections = invoke(0x249f0, bridge, chunk, 0, 0, 0);
        std::uint8_t *region = nullptr;
        for (std::uint32_t section = 0; section < 16; ++section) {
            const auto object =
                invoke(jniTarget(environment, 0x568), environment, sections, section, 0, 0);
            if (!object)
                continue;
            const auto blocks = invoke(0x24a50, bridge, object, 0, 0, 0);
            const auto data = invoke(jniTarget(environment, 0x6f0), environment, blocks, 0, 0, 0);
            const auto scanner = load<std::uintptr_t>(stateImage + 0x302128);
            if (scanner == nativeBase + 0x40980)
                scanByteIds(chunkX, section, chunkZ, reinterpret_cast<const std::uint8_t *>(data),
                            &region, stateImage, nativeBase, invoke);
            else if (scanner == nativeBase + 0x40af0)
                scanPackedIds(chunkX, section, chunkZ, reinterpret_cast<const std::uint8_t *>(data),
                              &region, stateImage, nativeBase, invoke);
            else
                invoke(scanner, chunkX, section, chunkZ, data, address(&region));
            invoke(jniTarget(environment, 0x6f8), environment, blocks, data, 0, 0);
        }
        if (region)
            rebuildMesh(region, stateImage, invoke);
        return;
    }
    if (kind != 2)
        return;
    const auto identifier = load<std::uint32_t>(event + 32);
    std::uintptr_t policy = 0;
    if (load<std::uintptr_t>(stateImage + 0x302120))
        policy = invoke(0x13d0e0, address(&identifier), load<std::uintptr_t>(stateImage + 0x302120),
                        load<std::uint64_t>(stateImage + 0x302110), 24, nativeBase + 0x40410);
    const auto chunkX = chunkCoordinate(load<std::uint32_t>(event + 20)),
               chunkZ = chunkCoordinate(load<std::uint32_t>(event + 28));
    const auto key = std::uint64_t(chunkX) | (std::uint64_t(chunkZ) << 32);
    auto *region = searchRegion(key, stateImage, nativeBase, invoke);
    const auto x = static_cast<std::uint8_t>(load<std::uint32_t>(event + 20) - (chunkX << 4));
    const auto z = static_cast<std::uint8_t>(load<std::uint32_t>(event + 28) - (chunkZ << 4));
    const auto y = static_cast<std::uint8_t>(load<std::uint64_t>(event + 24));
    if (!region) {
        if (!policy)
            return;
        region = insertRegion(key, stateImage, invoke);
        if (!load<std::uintptr_t>(stateImage + 0x302100))
            return;
        if (!region)
            return;
    } else {
        auto count = load<std::uint64_t>(region + 8);
        auto *block = reinterpret_cast<std::uint8_t *>(load<std::uintptr_t>(region + 24));
        for (std::uint64_t i = 0; i < count; ++i, block += 16)
            if (block[0] == x && block[1] == y && block[2] == z) {
                if (!policy) {
                    store(region + 8, count - 1);
                    invoke(0xab910, address(block), address(block + 16), (count - i - 1) * 16, 0,
                           0);
                    if (!load<std::uint64_t>(region + 8)) {
                        removeRegion(region, stateImage, invoke);
                        return;
                    }
                } else
                    store(block + 8, policy);
                rebuildMesh(region, stateImage, invoke);
                return;
            }
        if (!policy)
            return;
    }
    if (!appendBlock(region, x, y, z, policy, invoke))
        return;
    rebuildMesh(region, stateImage, invoke);
}

void collectLoadedRegions(std::uint8_t *context, std::uint8_t *stateImage,
                          std::uintptr_t nativeBase, BlockEndpoint invoke) {
    const auto manager =
        invoke(0x24990, load<std::uintptr_t>(context), load<std::uint64_t>(context + 32), 0, 0, 0);
    if (!manager)
        return;
    const auto list = invoke(0x24ab0, load<std::uintptr_t>(context), manager, 0, 0, 0);
    const auto count =
        static_cast<std::int32_t>(invoke(0x24e50, load<std::uintptr_t>(context), list, 0, 0, 0));
    if (count <= 0)
        return;
    std::uint32_t index = 0;
    do {
        const auto chunk = invoke(0x24e80, load<std::uintptr_t>(context), list, index, 0, 0);
        const auto x = static_cast<std::uint32_t>(
            invoke(0x24a10, load<std::uintptr_t>(context), chunk, 0, 0, 0));
        const auto z = static_cast<std::uint32_t>(
            invoke(0x24a30, load<std::uintptr_t>(context), chunk, 0, 0, 0));
        std::uint8_t event[40];
        store(event, load<std::uint64_t>(context));
        store(event + 8, load<std::uint64_t>(context + 32));
        store(event + 16, std::uint32_t(1));
        store(event + 20, x);
        store(event + 24, z);
        std::memset(event + 28, 0, 12);
        onRegionChange(event, stateImage, nativeBase, invoke);
    } while (++index != static_cast<std::uint32_t>(count));
}
} // namespace reconstruction::block_esp
// END SOURCE modules/Block_ESP/BlockCollection.cpp

// Convenient borrowed-state interface

namespace shareable {
class BlockESP {
  public:
    static constexpr const char *kName = "Block ESP";
    static constexpr const char *kDescription = "Highlights blocks.";
    explicit BlockESP(std::uint8_t *image) : image_(image) {}
    // Range. Config key: range.
    NumberSetting &range() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f1a28);
    }
    // allowed_blocks. Config key: allowed_blocks.
    ListSetting &allowed_blocks() const {
        return *reinterpret_cast<ListSetting *>(image_ + 0x2f1950);
    }
    // Enabled. Config key: should_limit_block_render.
    BooleanSetting &should_limit_block_render() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f1a60);
    }
    // Limit per chunk section. Config key: block_render_limit.
    NumberSetting &block_render_limit() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f19f0);
    }
    // Line width. Config key: line_width.
    NumberSetting &line_width() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f19b8);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_block_esp_ui(ui, layout, image_, &dependencies);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const BoundSurfaceUiDependencies &dependencies) {
        recovered_block_esp_bound_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_block_esp_settings(&context, image_, &dependencies);
    }
    void releaseWorldCollection(Dispatch invokeEndpoint) {
        ::reconstruction::block_esp::releaseWorldCollection(image_, invokeEndpoint);
    }
    void renderBlocks(uint8_t *event, Endpoint invokeEndpoint) {
        ::reconstruction::block_esp::renderBlocks(event, image_, invokeEndpoint);
    }
    static std::int32_t compareRegionKey(const void *left, const void *right) {
        return ::reconstruction::block_esp::compareRegionKey(left, right);
    }
    static void releaseRegion(std::uint8_t *region,
                              ::reconstruction::block_esp::BlockEndpoint invoke) {
        ::reconstruction::block_esp::releaseRegion(region, invoke);
    }
    void rebuildMesh(std::uint8_t *region, ::reconstruction::block_esp::BlockEndpoint invoke) {
        ::reconstruction::block_esp::rebuildMesh(region, image_, invoke);
    }
    void scanByteIds(std::uint32_t chunkX, std::uint32_t section, std::uint32_t chunkZ,
                     const std::uint8_t *data, std::uint8_t **region, std::uintptr_t nativeBase,
                     ::reconstruction::block_esp::BlockEndpoint invoke) {
        ::reconstruction::block_esp::scanByteIds(chunkX, section, chunkZ, data, region, image_,
                                                 nativeBase, invoke);
    }
    void scanPackedIds(std::uint32_t chunkX, std::uint32_t section, std::uint32_t chunkZ,
                       const std::uint8_t *data, std::uint8_t **region, std::uintptr_t nativeBase,
                       ::reconstruction::block_esp::BlockEndpoint invoke) {
        ::reconstruction::block_esp::scanPackedIds(chunkX, section, chunkZ, data, region, image_,
                                                   nativeBase, invoke);
    }
    static void appendCatalogCharacter(char *text, std::uint8_t character,
                                       ::reconstruction::block_esp::BlockEndpoint invoke) {
        ::reconstruction::block_esp::appendCatalogCharacter(text, character, invoke);
    }
    void onRegionChange(std::uint8_t *event, std::uintptr_t nativeBase,
                        ::reconstruction::block_esp::BlockEndpoint invoke) {
        ::reconstruction::block_esp::onRegionChange(event, image_, nativeBase, invoke);
    }
    void collectLoadedRegions(std::uint8_t *context, std::uintptr_t nativeBase,
                              ::reconstruction::block_esp::BlockEndpoint invoke) {
        ::reconstruction::block_esp::collectLoadedRegions(context, image_, nativeBase, invoke);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
