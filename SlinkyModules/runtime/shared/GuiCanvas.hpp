#ifndef SLINKY_SHARE_3D1D212EA6BB8020BD9E
#define SLINKY_SHARE_3D1D212EA6BB8020BD9E
#include <cstdint>
#include "FontRuntime.hpp"
namespace reconstruction::gui {
void saveCanvas_73a70(std::uint8_t*);
void restoreCanvas_749a0(std::uint8_t*);
void translateCanvas_74b40(std::uint8_t*,float,float);
void scaleCanvas_74d40(std::uint8_t*,float,float);
void scissorCanvas_75630(std::uint8_t*,float,float,float,float,const std::uint8_t*);
bool containsPoint_a0a0(const float*,std::uint64_t);
bool intersectsRect_a0e0(const float*,const float*);
float *insetRect_a130(float*,const float*,float);
float *roundRect_a160(float*,const float*,const std::uint8_t*);
std::uint64_t rectPosition_a1e0(const float*);
float interpolate_a260(float,float,float,const std::uint8_t*);
void *imagePaint_75520(void*,std::uint8_t*,float,float,float,float,float,std::int32_t,float,const std::uint8_t*);
void fillPaint_74f60(std::uint8_t*,const void*);
void strokeColor_74de0(std::uint8_t*,const void*,const std::uint8_t*);
void lineWidth_749e0(std::uint8_t*,float);
void moveTo_75bf0(std::uint8_t*,float,float,const drawing::FontDependencies&);
void lineTo_75ec0(std::uint8_t*,float,float,const drawing::FontDependencies&);
void rectPath_76950(std::uint8_t*,float,float,float,float,const drawing::FontDependencies&);
void roundedRect_769d0(std::uint8_t*,float,float,float,float,float,const std::uint8_t*,const drawing::FontDependencies&);
}
#endif // SLINKY_SHARE_3D1D212EA6BB8020BD9E
