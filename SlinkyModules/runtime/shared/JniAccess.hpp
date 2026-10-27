#ifndef SLINKY_SHARE_0A44111024B15EF554FC
#define SLINKY_SHARE_0A44111024B15EF554FC
#include "../native/verified/module_game_access.hpp"
#include "Geometry.hpp"
#include <cstring>
#include "../native/verified/module_access_helpers.hpp"
#include "../native/verified/Null_Move.hpp"
#include <bit>

// Concrete JNI contracts corroborated by the supplied clean sources and the
// captured instructions. Slot numbers describe JNI calls, not module algorithms.
namespace recovered_jni {
using Word=std::uint64_t;
inline GameAccessBridge *bridge(Word value) {return reinterpret_cast<GameAccessBridge *>(value);}
inline void *object(Word value) {return reinterpret_cast<void *>(value);}
inline Word pointer(const void *value) {return reinterpret_cast<Word>(value);}
inline Word identifier(const GameAccessBridge *b,std::size_t offset) {Word value;std::memcpy(&value,b->metadata+offset,8);return value;}
template<class F> F slot(std::uintptr_t *environment,std::size_t offset) {
    return reinterpret_cast<F>(reinterpret_cast<const std::uintptr_t *>(*environment)[offset/8]);
}
template<class T,std::size_t Slot> T field(GameAccessBridge *b,Word entity,std::size_t offset) {
    using Getter=T (*)(std::uintptr_t *,Word,Word);
    return slot<Getter>(b->environment,Slot)(b->environment,entity,identifier(b,offset));
}
inline Word objectField(GameAccessBridge *b,Word entity,std::size_t offset) {return field<Word,0x2f8>(b,entity,offset);}
inline Word instance(GameAccessBridge *b,Word entity,std::size_t offset) {
    using Query=std::uint8_t (*)(std::uintptr_t *,Word,Word);
    return slot<Query>(b->environment,0x100)(b->environment,entity,identifier(b,offset))?entity:0;
}
inline void floatField(GameAccessBridge *b,Word entity,std::size_t offset,float value) {
    using Setter=void (*)(std::uintptr_t *,Word,Word,float);
    slot<Setter>(b->environment,0x378)(b->environment,entity,identifier(b,offset),value);
}
inline void integerField(GameAccessBridge *b,Word entity,std::size_t offset,std::uint32_t value) {
    using Setter=void (*)(std::uintptr_t *,Word,Word,std::uint32_t);
    slot<Setter>(b->environment,0x368)(b->environment,entity,identifier(b,offset),value);
}
inline Word indexedMethod(GameAccessBridge *b,Word entity,std::size_t offset,std::uint32_t value) {
    using Query=Word (*)(std::uintptr_t *,Word,Word,...);
    return slot<Query>(b->environment,0x110)(b->environment,entity,identifier(b,offset),value);
}
inline Word getPosition(Word output,Word game,Word entity,std::size_t offset) {
    auto *b=bridge(game);
    const double x=field<double,0x338>(b,entity,offset);
    const double y=field<double,0x338>(b,entity,offset+8);
    const double z=field<double,0x338>(b,entity,offset+16);
    recovered_geometry_construct_93b0(reinterpret_cast<void *>(output),x,y,z);
    return output;
}
inline float floatValue(Word bits) {return std::bit_cast<float>(static_cast<std::uint32_t>(bits));}
inline Word floatBits(float value) {return std::bit_cast<std::uint32_t>(value);}
inline Word doubleBits(double value) {return std::bit_cast<Word>(value);}
inline double doubleValue(Word value) {return std::bit_cast<double>(value);}
template<class Vector> inline Word storedVector(Word output,Vector value) {std::memcpy(reinterpret_cast<void *>(output),&value,24);return output;}
}
#endif // SLINKY_SHARE_0A44111024B15EF554FC
