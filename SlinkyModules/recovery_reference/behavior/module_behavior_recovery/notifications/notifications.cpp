#include <stdint.h>
#include <string.h>
#include <intrin.h>
#include <emmintrin.h>
typedef uint64_t (*endpoint)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t q(const void *p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t d(const void *p){uint32_t v;memcpy(&v,p,4);return v;}
static float f(const void *p){float v;memcpy(&v,p,4);return v;}
static double g(const void *p){double v;memcpy(&v,p,8);return v;}
static void wq(void *p,uint64_t v){memcpy(p,&v,8);}
static void wd(void *p,uint32_t v){memcpy(p,&v,4);}
static void wf(void *p,float v){memcpy(p,&v,4);}
static float af(float a,float b){return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static uint8_t *append(uint8_t *image,uint32_t kind){
    uint64_t start=q(image+0x2fc440),count=q(image+0x2fbfd8);uint8_t *row=image+0x2fbfe0+112*((start+count)%10);
    wd(row,kind);wd(row+0x6c,0);if(count==10)wq(image+0x2fc440,start+1);else wq(image+0x2fbfd8,count+1);return row+4;
}
static uint64_t image_address(uint8_t *image,uint64_t original){return (uintptr_t)image+(original-UINT64_C(0x180000000));}
extern "C" __declspec(dllexport) void recovered_notifications_35000(uint8_t *event,uint8_t *image,endpoint call){
    uint8_t *descriptor=(uint8_t *)(uintptr_t)q(event+0x10);
    if(descriptor==image+0x2ed320){
        if(!event[0x18]){wq(image+0x2fbfd8,0);return;}
        if(_InterlockedCompareExchange8((volatile char *)(image+0x2fbfb0),1,0)!=0)return;
        uint8_t *text=append(image,1);uint64_t app=q(image+0x13e498);uint64_t key=call(0x9380,d((void *)(uintptr_t)(app+0x1c)),0,0,0,0);
        call(0xab710,(uintptr_t)text,101,(uintptr_t)(image+0x151f02),key,0);return;
    }
    uint32_t flags=d(descriptor+0x18);if(flags&16)return;if((flags&2) && image[0x2ed548])return;if(descriptor[0x20]==1 && image[0x2ed568])return;
    switch(d(descriptor+0x10)){
        case 0:if(!image[0x2ed588])return;break;
        case 1:if(!image[0x2ed5a8])return;break;
        case 2:if(!image[0x2ed5e8])return;break;
        case 3:if(!image[0x2ed5c8])return;break;
        case 4:if(image[0x2ed608]!=1)return;break;
    }
    uint8_t *pending=image+(event[0x18]?0x2fbfb8:0x2fbfc8);wq(pending,q(descriptor));wd(pending+8,d(pending+8)+1);
}
extern "C" __declspec(dllexport) void recovered_notifications_351a0(uint8_t *event,uint8_t *image,endpoint call){
    if(image[0x2ed628]==1 && !*(uint8_t *)(uintptr_t)(q(image+0x13e498)+0x14)){wq(image+0x2fbfd8,0);wd(image+0x2fbfc0,0);wd(image+0x2fbfd0,0);return;}
    uint64_t count=q(image+0x2fbfd8),start=q(image+0x2fc440);float expiry=f(image+0x151e48);
    while(count){if(!(f(image+0x2fbfe0+112*(start%10)+0x6c)>expiry))break;++start;wq(image+0x2fc440,start);--count;wq(image+0x2fbfd8,count);}
    for(unsigned disabled=0;disabled<2;++disabled){
        uint8_t *pending=image+(disabled?0x2fbfc8:0x2fbfb8);uint32_t total=d(pending+8);if(!total)continue;
        uint8_t *text=append(image,1);uint64_t label=(uintptr_t)(image+(disabled?0x151f74:0x151f6c));
        call(0xab710,(uintptr_t)text,101,(uintptr_t)(image+(total==1?0x151f66:0x151f7d)),label,total==1?q(pending):total);wd(pending+8,0);
    }
    count=q(image+0x2fbfd8);if(!count)return;
    uint32_t old_flags=d(event+0x10);wd(event+0x10,old_flags|1);start=q(image+0x2fc440);float elapsed=f(event+0x14);double late=g(image+0x151e50),early=g(image+0x151e58);uint8_t transitioning=0;
    for(uint64_t i=0;i<count;++i){uint8_t *age=image+0x2fbfe0+112*((start+i)%10)+0x6c;float next=af(f(age),elapsed);wf(age,next);if((double)next>late || (double)next<early)transitioning=1;}
    if(transitioning)wd(event+0x10,old_flags|3);
}
extern "C" __declspec(dllexport) void recovered_notifications_35960(uint8_t *event,uint8_t *image,endpoint call){
    uint32_t kind=d(event+0x10);if(kind==2)return;
    uint64_t action=image_address(image,q(image+0x151f90+8*(uint64_t)kind)),label=q(event+8);if(!label)label=(uintptr_t)(image+0x151fb0);
    uint8_t *text=append(image,0);call(0xab710,(uintptr_t)text,101,(uintptr_t)(image+0x151f66),action,label);
}
extern "C" __declspec(dllexport) void recovered_notifications_35a30(uint8_t *event,uint8_t *image,endpoint call){
    uint8_t *text=append(image,2);uint64_t message=q(event+0x10);
    call(0xab710,(uintptr_t)text,101,(uintptr_t)(image+(message?0x151fe5:0x151fe8)),message?message:d(event+8),0);
}
extern "C" __declspec(dllexport) void recovered_notifications_35af0(uint8_t *event,uint8_t *image,endpoint call){
    (void)call;uint8_t *text=append(image,1);
    if(event[8]==1){wq(text+5,UINT64_C(0x64656464612064));wq(text,UINT64_C(0x6120646e65697246));}
    else{wq(text+7,UINT64_C(0x6465766f6d6572));wq(text,UINT64_C(0x7220646e65697246));}
}
