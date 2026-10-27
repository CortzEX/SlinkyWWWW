#ifndef SLINKY_SHARE_15DC00F9EC86ABEB20A8
#define SLINKY_SHARE_15DC00F9EC86ABEB20A8
#include "GuiPages.hpp"
namespace reconstruction::gui {
// Values carried from the common 16CA0 frame into its mode-specific sections.
// Only the low byte of native R12 is consumed by the common finish sequence.
struct ModalFrame {
    std::uint8_t *state;
    std::uint8_t *ui;
    std::uint8_t closeButton;
    std::int32_t finishMode; // Native R15D: 0 wait, 1 apply, 2 cancel after callback.
};
void renderModal_16ca0(std::uint8_t *state,std::uint8_t *ui,
    const PageDependencies &);
// Ordinary captured section174BF..18784, independently owned color renderer.
void renderModalColorSection(ModalFrame &,const PageDependencies &);
}
#endif // SLINKY_SHARE_15DC00F9EC86ABEB20A8
