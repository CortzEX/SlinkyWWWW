#ifndef SLINKY_SHARE_49335D3339ED17ACC90E
#define SLINKY_SHARE_49335D3339ED17ACC90E
#include "../../shared/RenderNativeBindings.hpp"
#include "../../native/verified/module_esp_lists.hpp"
#include "../../native/verified/module_surface.hpp"
#include "../../shared/Geometry.hpp"
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
__declspec(dllexport) void onModuleStateChanged(uint8_t *event, uint8_t *image, std::uintptr_t nativeBase,
                                                BlockEndpoint call);
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
void scanPackedIds(std::uint32_t, std::uint32_t, std::uint32_t, const std::uint8_t *, std::uint8_t **,
                   std::uint8_t *, std::uintptr_t, BlockEndpoint);
void appendCatalogCharacter(char *, std::uint8_t, BlockEndpoint);
void onRegionChange(std::uint8_t *, std::uint8_t *, std::uintptr_t, BlockEndpoint);
void collectLoadedRegions(std::uint8_t *, std::uint8_t *, std::uintptr_t, BlockEndpoint);
} // namespace reconstruction::block_esp

namespace reconstruction::block_esp::setting_offset {
// Config keys identify storage. These constants assert no initial values.
inline constexpr std::size_t range = 0x2f1a28 + offsetof(NumberSetting, current);
inline constexpr std::size_t should_limit_block_render = 0x2f1a60 + offsetof(BooleanSetting, current);
inline constexpr std::size_t block_render_limit = 0x2f19f0 + offsetof(NumberSetting, current);
inline constexpr std::size_t line_width = 0x2f19b8 + offsetof(NumberSetting, current);
} // namespace reconstruction::block_esp::setting_offset
#endif // SLINKY_SHARE_49335D3339ED17ACC90E
