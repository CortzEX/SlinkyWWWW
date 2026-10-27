#ifndef SLINKY_SHARE_2B6A21C06408A9E4344B
#define SLINKY_SHARE_2B6A21C06408A9E4344B
#include "GuiControls.hpp"
namespace reconstruction::gui {
struct ConfigurationCalls {
    void *context;
    std::uint32_t (*refresh_ead0)(void*,std::uint64_t);
    std::uint64_t (*records_eea0)(void*,std::uint64_t,std::uint64_t*);
    std::uint64_t (*metadata_ea90)(void*,std::uint64_t);
    std::uint32_t (*load_be40)(void*,std::uint64_t,std::uint64_t);
    std::uint32_t (*save_c0b0)(void*,std::uint64_t,std::uint8_t,std::uint64_t);
    std::uint64_t (*current_c1f0)(void*);
    std::uint8_t (*pending_c200)(void*);
};
// These services bind the other independently recovered page bodies. Each
// field retains its native widths, including the fifth-argument float lane.
struct PageCalls {
    void *context;
    void (*category_12b20)(void*,std::uint8_t*,std::uint8_t*,std::uint64_t,std::uint32_t,float);
    void (*profileText_13420)(void*,std::uint8_t*,std::uint8_t*,std::uint64_t,std::uint8_t*,std::uint32_t,std::uint64_t,float*);
    void (*profilePopup_138f0)(void*,std::uint8_t*,std::uint64_t,std::uint64_t,const char*,std::uint32_t);
    void (*modal_16ca0)(void*,std::uint8_t*,std::uint8_t*);
};
struct RuntimeDependencies {
    const ControlDependencies &controls;
    const ConfigurationCalls &configuration;
    const PageCalls &pages;
    void *protectedContext;
    float (*binaryScalar_13cfe0)(void*,float,float);
    std::int32_t (*compare_13d0a0)(void*,std::uint64_t,std::uint64_t);
    std::uint64_t profileNameCallback_13ad0;
};
void fadeBackdrop_128c0(std::uint8_t*,float,const RuntimeDependencies&);
void render_11820(std::uint8_t*,std::uint8_t*,std::uint64_t,std::uint64_t,const RuntimeDependencies&);
void clearInteraction_12a90(std::uint8_t*);
std::uint8_t closeRequested_12ab0(std::uint8_t*);
std::uint8_t viewportIntersects_12ac0(std::uint8_t*,std::uint8_t*,const float*);
}
#endif // SLINKY_SHARE_2B6A21C06408A9E4344B
