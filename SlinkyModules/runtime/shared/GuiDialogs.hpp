#ifndef SLINKY_SHARE_4403ABE57573BE37D6FB
#define SLINKY_SHARE_4403ABE57573BE37D6FB
#include "UiRuntime.hpp"
#include "../native/verified/module_format.hpp"
namespace reconstruction::gui {
struct DialogDependencies {
    const ui::UiDependencies &input;
    std::uint8_t *image;
    FormatState &format;
    void *context;
    double (*clock_4c270)(void*);
};
void openDialog_16820(std::uint8_t*state,std::uint64_t user,
    std::uint64_t completion,const char*format,std::va_list nativeArguments,
    const DialogDependencies&);
void openDialogText_16820(std::uint8_t*state,std::uint64_t user,
    std::uint64_t completion,const char*format,const char*firstArgument,
    const DialogDependencies&);
void openPayloadDialog_168f0(std::uint8_t*state,std::uint64_t title,
    std::uint64_t user,std::uint64_t completion,const void*payload16,
    std::uint64_t payloadWord,const DialogDependencies&);
}
#endif // SLINKY_SHARE_4403ABE57573BE37D6FB
