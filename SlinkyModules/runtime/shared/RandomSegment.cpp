#include "RandomSegment.hpp"
#include <cstring>
#include <bit>
#include <emmintrin.h>
namespace {
template<class T>T load(const std::uint8_t *p){T v;std::memcpy(&v,p,sizeof v);return v;}
float subtract(float a,float b){return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a),_mm_set_ss(b)));}
void refresh(SmoothRandomState *state,RandomState *random,float upper,float scale,std::uint32_t mask,double threshold){
    const RandomConstants constants{scale,0,0};
    do { state->right=recovered_random_interval(random,&constants,recovered_random_bounds(0,upper)); }
    while(threshold>double(std::bit_cast<float>(std::bit_cast<std::uint32_t>(subtract(state->left,state->right))&mask)));
}
}
// A870 accumulates a caller delta, resets elapsed to positive zero on expiry,
// regenerates endpoints, then interpolates in binary64. No global clock read.
float recovered_random_segment_a870(SmoothRandomState *state,std::uint64_t bounds,double duration,double delta,RandomState *random,const std::uint8_t *image){
    state->timestamp=_mm_cvtsd_f64(_mm_add_sd(_mm_set_sd(delta),_mm_set_sd(state->timestamp)));
    if(state->timestamp>duration){
        state->timestamp=0.0;
        const auto left=state->left,right=state->right;
        if(left==0.0f&&right==0.0f){
            RandomPolicyConstants constants{};
            constants.initialize.upper=load<float>(image+0x13e920);
            constants.initialize.scale=load<float>(image+0x13e924);
            constants.initialize.difference_mask=load<std::uint32_t>(image+0x13e930);
            constants.initialize.minimum_difference=load<double>(image+0x13e940);
            recovered_policy_initialize(state,1,random,&constants);
        }else{
            state->left=right;
            const auto upper=load<float>(image+0x13e950),scale=load<float>(image+0x13e954);
            const auto mask=load<std::uint32_t>(image+0x13e960);const auto threshold=load<double>(image+0x13e970);
            refresh(state,random,upper,scale,mask,threshold);
        }
    }
    const auto phase=_mm_div_sd(_mm_set_sd(state->timestamp),_mm_set_sd(duration));
    const auto left=_mm_cvtss_sd(_mm_setzero_pd(),_mm_set_ss(state->left));
    const auto difference=_mm_cvtss_sd(_mm_setzero_pd(),_mm_set_ss(subtract(state->right,state->left)));
    const auto curve=_mm_add_sd(_mm_mul_sd(difference,phase),left);
    const auto low=std::bit_cast<float>(std::uint32_t(bounds)),high=std::bit_cast<float>(std::uint32_t(bounds>>32));
    const auto value=_mm_add_sd(_mm_mul_sd(_mm_set_sd(double(subtract(high,low))),curve),_mm_set_sd(double(low)));
    return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),value));
}
