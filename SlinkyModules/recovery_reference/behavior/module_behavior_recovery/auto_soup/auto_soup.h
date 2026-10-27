#ifndef AUTO_SOUP_H
#define AUTO_SOUP_H
#include <stdint.h>
typedef struct soup_args {
    uint64_t rcx,rdx,r8,r9,xmm0,xmm1,xmm2;
    /* Original stack argument 5; the indirect item call uses this field to expose its loaded target. */
    uint64_t stack5;
} soup_args;
typedef struct soup_result { uint64_t rax,xmm0; } soup_result;
typedef void (*soup_dispatch)(uint32_t,const soup_args *,soup_result *,void *);
__declspec(dllexport) void recovered_auto_soup_2d510(uint8_t *event,uint8_t *image,soup_dispatch call,void *user);
__declspec(dllexport) void recovered_auto_soup_2dae0(uint8_t *event,uint8_t *image);
__declspec(dllexport) void recovered_auto_soup_2db10(uint8_t *event,uint8_t *image);
#endif
