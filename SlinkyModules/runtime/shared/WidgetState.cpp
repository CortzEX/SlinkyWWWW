#include "WidgetState.hpp"
#include "DisplayGeometry.hpp"
#include <cstring>
#include <initializer_list>
#include <emmintrin.h>
#include <intrin.h>
namespace {
template<class T>T get(const void *p){T v;std::memcpy(&v,p,sizeof v);return v;}
template<class T>void put(void *p,T v){std::memcpy(p,&v,sizeof v);}
bool inputAllowed(std::uint8_t *state){return get<std::uint32_t>(state+0x3f8)==0||state[0x420]!=0;}
}
std::uint32_t recovered_widget_hover_11180(std::uint8_t *state,const float *rectangle){
    if(!inputAllowed(state))return 0;
    float copy[4];std::memcpy(copy,rectangle,16);
    if(!recovered_rectangle_contains_a0a0(copy,get<std::uint64_t>(state+0x4a8)))return 0;
    const auto mode=get<std::uint32_t>(state+0x370);
    return (mode&0xffffff00u)|std::uint32_t(mode==0||mode==3);
}
std::uint32_t recovered_widget_click_111f0(std::uint8_t *state,const float *rectangle){
    float copy[4];std::memcpy(copy,rectangle,16);
    if(!inputAllowed(state))return 0;
    if(!recovered_rectangle_contains_a0a0(copy,get<std::uint64_t>(state+0x4a8)))return 0;
    const auto mode=get<std::uint32_t>(state+0x370);
    if(mode!=0&&mode!=3)return 0;
    if(state[0x4c8]!=1||state[0x4c9]!=0)return 0;
    state[0x4c9]=1;return 1;
}
void recovered_widget_capture_11270(std::uint8_t *state){if(state[0x4c8]==1&&state[0x4c9]==0)state[0x4c9]=1;}
void recovered_widget_action_11290(std::uint8_t *state,std::uint64_t callback,std::uint64_t identity){
    put(state+0x370,std::uint32_t(1));put(state+0x378,callback);put(state+0x380,identity);
}
void recovered_widget_input_112d0(std::uint8_t *state,std::uint64_t callback,std::uint64_t identity){
    if((get<std::uint32_t>(state+0x370)&0xfffffffeu)==2&&get<std::uint64_t>(state+0x3e8)==identity)return;
    put(state+0x370,std::uint32_t(2));const auto zero=_mm_setzero_ps();
    for(auto offset:{0x3d8,0x3e8,0x378,0x388,0x398,0x3a8,0x3b8,0x3c8}){_mm_storeu_ps(reinterpret_cast<float *>(state+offset),zero);_ReadWriteBarrier();}
    put(state+0x3e0,callback);put(state+0x3e8,identity);
}
std::uint32_t recovered_widget_identity_11340(std::uint8_t *state,std::uint64_t identity){
    return (get<std::uint32_t>(state+0x370)&0xfffffffeu)==2&&get<std::uint64_t>(state+0x3e8)==identity;
}
void recovered_widget_release_11370(std::uint8_t *state){if(get<std::uint32_t>(state+0x370)==2)put(state+0x370,std::uint32_t(3));}
char *recovered_widget_take_text_11390(std::uint8_t *state){
    if((get<std::uint32_t>(state+0x370)&0xfffffffeu)!=2||state[0x3f0]!=1)return nullptr;
    put(state+0x370,std::uint32_t(0));state[0x3f0]=0;return reinterpret_cast<char *>(state+0x378);
}
char *recovered_widget_text_113d0(std::uint8_t *state){
    return (get<std::uint32_t>(state+0x370)&0xfffffffeu)==2?reinterpret_cast<char *>(state+0x378):nullptr;
}
