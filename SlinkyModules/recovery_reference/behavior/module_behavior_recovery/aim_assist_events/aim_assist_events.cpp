#include <stdint.h>
#include <string.h>
typedef uint64_t (*dependency)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t q(const void *p){uint64_t v;memcpy(&v,p,8);return v;}
__declspec(dllexport) void recovered_aim_assist_2b5b0(uint8_t *event,uint8_t *image,dependency call){
    if(q(event+0x10)!=(uintptr_t)(image+0x2e8cc0) || event[0x18]!=0)return;
    uint64_t retained=q(image+0x2f7be0);
    if(retained){
        uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+8),*game=(uint8_t *)(uintptr_t)q(ctx);
        uint8_t *env=(uint8_t *)(uintptr_t)q(game+8),*table=(uint8_t *)(uintptr_t)q(env);
        call(q(table+0xb0),(uintptr_t)env,retained,0,0);
    }
    uint64_t zero=0;memcpy(image+0x2f7be0,&zero,8);image[0x2f7bd8]=0;
}
__declspec(dllexport) void recovered_aim_assist_2b610(uint8_t *event,uint8_t *image,dependency call){
    (void)call;if(image[0x2f7c20]!=1)return;
    event[8]=1;if(image[0x2e9068]==1)event[9]=1;
}
