#ifndef SLINKY_SHARE_E684753A7AC76897EB65
#define SLINKY_SHARE_E684753A7AC76897EB65
#include "GuiRuntime.hpp"
#include "WordInvoker.hpp"
#include "../native/verified/module_list_storage.hpp"
namespace reconstruction::gui {
struct PageDependencies {
    const ControlDependencies &controls;
    const ui::UiDependencies &input;
    std::uint8_t *image;
    void *context;
    void *(*allocate)(void *,std::uint64_t);
    void *(*allocateZeroed)(void *,std::uint64_t,std::uint64_t);
    double (*clock)(void *);
    void (*openDialog_16820)(void *,std::uint8_t *state,std::uint64_t user,
        std::uint64_t completion,const char *title,const char *initialText);
    std::uint32_t (*loadProfile_be40)(void *,const char *,std::uint64_t manager);
    // Native C290 explores the profile directory through 4C7B0.
    std::uint32_t (*openProfileDirectory_c290)(void *);
    std::uint32_t (*deleteProfile_c220)(void *,const char *);
    std::uint32_t (*saveProfile_c0b0)(void *,const char *,std::uint8_t,std::uint64_t);
    // Caller-installed callback identity, retained in the native dialog state.
    std::uint64_t completionCallback_139d0;
    RecoveredFrameInvoker calls;
    const ListMemoryDependencies &listMemory;
    std::uint64_t hexFilterCallback_18830; // Caller-owned native/mapped callback identity.
};
void profilePopup_138f0(std::uint8_t *state,std::uint64_t manager,
    std::uint64_t configuration,const char *name,std::uint32_t mode,
    const PageDependencies &);
void completeProfilePopup_139d0(std::uint8_t *record,const PageDependencies &);
void beginModal_16530(std::uint8_t *state,std::uint64_t title,
    std::uint64_t user,std::uint64_t filterCallback,std::uint64_t completion,
    const PageDependencies &);
float ceilFloat_b2920(float,const std::uint8_t *image);
void profileTextInput_13420(std::uint8_t *state,std::uint8_t *ui,
    std::uint64_t metadata,std::uint8_t *record,std::uint32_t key,
    std::uint8_t *modeFlag,const float *rectangle,const PageDependencies &);
void renderCategory_12b20(std::uint8_t *state,std::uint8_t *ui,
    std::uint64_t manager,std::uint32_t category,float elapsed,
    const PageDependencies &);
float moduleText_130c0(std::uint8_t *state,std::uint8_t *ui,
    std::uint8_t *module,const float *rectangle,float fontSize,
    const float *normal,const float *highlight,const char *text,
    const PageDependencies &);
}
#endif // SLINKY_SHARE_E684753A7AC76897EB65
