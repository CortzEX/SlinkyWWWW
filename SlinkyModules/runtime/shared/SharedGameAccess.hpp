#ifndef SLINKY_SHARE_457BCAFE2F1B4020D437
#define SLINKY_SHARE_457BCAFE2F1B4020D437
#include "Geometry.hpp"
#include "JniAccess.hpp"
#include "Rounding.hpp"
#include "Trigonometry.hpp"
#include <bit>
#include <cstring>
#include <emmintrin.h>

// Ordinary game access wrappers audited against the offline runtime image.
// RVAs identify observed instructions; these are assigned semantic names.
namespace reconstruction::game_access {
using Word = std::uint64_t;
using namespace recovered_jni;
inline Word readWord(const std::uint8_t *image, std::size_t rva) {
  Word v;
  std::memcpy(&v, image + rva, 8);
  return v;
}
inline float readSingle(const std::uint8_t *image, std::size_t rva) {
  float v;
  std::memcpy(&v, image + rva, 4);
  return v;
}
// 0x22c70: metadata 0x198, JNI GetObjectField 0x2f8.
inline Word playerObject(GameAccessBridge *b, Word client) {
  return objectField(b, client, 0x198);
}
// 0x22c90 retains the queried screen, then reloads bridge metadata/environment.
inline Word currentScreen(GameAccessBridge *b, Word client) {
  const Word screen = objectField(b, client, 0x1c8);
  return instance(b, screen, 0x4d8);
}
// 0x22cf0: metadata 0x1a0, JNI GetObjectField 0x2f8.
inline Word clientOptions(GameAccessBridge *b, Word client) {
  return objectField(b, client, 0x1a0);
}
// 0x23020 consumes only the comparison's AL result in known callers.
inline std::uint8_t positionModeZero(GameAccessBridge *b) {
  std::uint32_t mode;
  std::memcpy(&mode, b->metadata, 4);
  return mode == 0;
}
// 0x23030: output RCX, bridge RDX, entity R8. Three independent bridge reads.
inline Word position(Word output, GameAccessBridge *b, Word entity) {
  return getPosition(output, pointer(b), entity, 0x268);
}
// 0x230d0: same layout, previous coordinates metadata 0x280/0x288/0x290.
inline Word previousPosition(Word output, GameAccessBridge *b, Word entity) {
  return getPosition(output, pointer(b), entity, 0x280);
}
// 0x24160: server coordinates reload the bridge before each double field read.
inline Word serverPosition(Word output, GameAccessBridge *b, Word entity) {
  return getPosition(output, pointer(b), entity, 0x880);
}
// 0x23170: each JNI float is packed by its raw bits into RAX, yaw then pitch.
inline Word rotation(GameAccessBridge *b, Word entity) {
  const float yaw = field<float, 0x330>(b, entity, 0x298);
  const float pitch = field<float, 0x330>(b, entity, 0x2a0);
  return floatBits(yaw) | (floatBits(pitch) << 32);
}
// 0x23550: output RCX, bridge RDX, entity R8; metadata 0x2b8/0x2c0/0x2c8.
inline Word velocity(Word output, GameAccessBridge *b, Word entity) {
  return getPosition(output, pointer(b), entity, 0x2b8);
}
// 0x235f0: each input lane is loaded immediately before its JNI setter call.
inline void setVelocity(GameAccessBridge *b, Word entity, const double *value) {
  using Setter = void (*)(std::uintptr_t *, Word, Word, double);
  slot<Setter>(b->environment, 0x380)(b->environment, entity,
                                      identifier(b, 0x2b8), value[0]);
  slot<Setter>(b->environment, 0x380)(b->environment, entity,
                                      identifier(b, 0x2c0), value[1]);
  slot<Setter>(b->environment, 0x380)(b->environment, entity,
                                      identifier(b, 0x2c8), value[2]);
}
// 0x23670, 0x23720, 0x23740, 0x23760.
inline Word boundingBoxObject(GameAccessBridge *b, Word entity) {
  return objectField(b, entity, 0x2d0);
}
inline std::int32_t entityId(GameAccessBridge *b, Word entity) {
  return field<std::int32_t, 0x320>(b, entity, 0x2e0);
}
inline Word uuidObject(GameAccessBridge *b, Word entity) {
  return objectField(b, entity, 0x2e8);
}
inline std::int32_t ticksExisted(GameAccessBridge *b, Word entity) {
  return field<std::int32_t, 0x320>(b, entity, 0x2d8);
}
// 0x23780 normalizes AL only; unused upper native return bits are not claimed.
inline std::uint8_t onGround(GameAccessBridge *b, Word entity) {
  return field<std::uint8_t, 0x300>(b, entity, 0x2f0) != 0;
}
// 0x237e0 returns a float through XMM0.
inline float entityFloat300(GameAccessBridge *b, Word entity) {
  return field<float, 0x330>(b, entity, 0x300);
}
// 0x23990 forwards the binary64 constant as a variadic floating argument.
inline Word positionObject(GameAccessBridge *b, Word entity,
                           const std::uint8_t *image) {
  using Query = Word (*)(std::uintptr_t *, Word, Word, ...);
  return slot<Query>(b->environment,
                     0x110)(b->environment, entity, identifier(b, 0x508),
                            doubleValue(readWord(image, 0x14f770)));
}
// 0x239f0: signed integer field, native EAX result.
inline std::int32_t hurtTime(GameAccessBridge *b, Word entity) {
  return field<std::int32_t, 0x320>(b, entity, 0x558);
}
// 0x23a40 uses a payload-bit NaN test and exact image-backed replacement bits.
inline float health(GameAccessBridge *b, Word entity,
                    const std::uint8_t *image) {
  const float v = field<float, 0x1b8>(b, entity, 0x510);
  const auto bits = std::bit_cast<std::uint32_t>(v) & 0x7fffffffu;
  return bits >= 0x7f800001u ? readSingle(image, 0x14f778) : v;
}
// 0x23ac0/0x23ae0/0x23b40 are native float fields, without normalization.
inline float forwardInput(GameAccessBridge *b, Word entity) {
  return field<float, 0x330>(b, entity, 0x540);
}
inline float strafeInput(GameAccessBridge *b, Word entity) {
  return field<float, 0x330>(b, entity, 0x548);
}
inline float movementSpeed(GameAccessBridge *b, Word entity) {
  return field<float, 0x330>(b, entity, 0x568);
}
// 0x23f00 retains the input handle if the instance predicate's AL is nonzero.
inline Word livingInstance(GameAccessBridge *b, Word entity) {
  return instance(b, entity, 0x578);
}
// 0x23f60: CallBooleanMethod uses metadata 0x580 and forwards the player in R9.
// Native callers consume AL; only that low-byte truth value is represented.
inline std::uint8_t invisibleToPlayer(GameAccessBridge *b, Word entity,
                                     Word player) {
  using Query = std::uint8_t (*)(std::uintptr_t *, Word, Word, ...);
  return slot<Query>(b->environment, 0x128)(
             b->environment, entity, identifier(b, 0x580), player) != 0;
}
// 0x24020 forwards R8D to JNI SetIntField as R9D.
inline void setInteger5a8(GameAccessBridge *b, Word entity,
                          std::uint32_t value) {
  integerField(b, entity, 0x5a8, value);
}
// 0x240a0 normalizes the Boolean field's AL; higher return bits are unused.
inline std::uint8_t sleeping(GameAccessBridge *b, Word entity) {
  return field<std::uint8_t, 0x300>(b, entity, 0x5b8) != 0;
}
// 0x24120 preserves an instance-checked object handle.
inline Word remotePlayerInstance(GameAccessBridge *b, Word entity) {
  return instance(b, entity, 0x870);
}
// 0x24220 returns a binary64 value through XMM0.
inline double field898(GameAccessBridge *b, Word entity) {
  return field<double, 0x338>(b, entity, 0x898);
}
// 0x24280 uses JNI CallStaticIntMethod, metadata class/method 0x430/0x438.
inline std::int32_t blockNumericId(GameAccessBridge *b, Word block) {
  using Query = std::int32_t (*)(std::uintptr_t *, Word, Word, ...);
  return slot<Query>(b->environment, 0x408)(
      b->environment, identifier(b, 0x430), identifier(b, 0x438), block);
}
// 0x242c0 constructs an object from three exact signed 32-bit coordinate words.
inline Word blockPositionObject(GameAccessBridge *b, std::uint32_t x,
                                std::uint32_t y, std::uint32_t z) {
  using NewObject = Word (*)(std::uintptr_t *, Word, Word, ...);
  return slot<NewObject>(b->environment, 0xe0)(
      b->environment, identifier(b, 0x448), identifier(b, 0x450),
      std::bit_cast<std::int32_t>(x), std::bit_cast<std::int32_t>(y),
      std::bit_cast<std::int32_t>(z));
}
// 0x24600: native Word result, JNI slot 0x2f8, metadata 0x360.
inline Word worldPlayers(GameAccessBridge *b, Word object) {
  return field<Word, 0x2f8>(b, object, 0x360);
}
// 0x24bf0: native Word result, JNI slot 0x2f8, metadata 0x3e0.
inline Word hitVectorObject(GameAccessBridge *b, Word object) {
  return field<Word, 0x2f8>(b, object, 0x3e0);
}
// 0x24e30: native Word result, JNI slot 0x2f8, metadata 0x418.
inline Word hitEntityObject(GameAccessBridge *b, Word object) {
  return field<Word, 0x2f8>(b, object, 0x418);
}
// 0x24e50: native std::int32_t result, JNI slot 0x188, metadata 0x28.
inline std::int32_t listSize(GameAccessBridge *b, Word object) {
  return field<std::int32_t, 0x188>(b, object, 0x28);
}
// 0x25410: native std::int32_t result, JNI slot 0x320, metadata 0x488.
inline std::int32_t keyCode(GameAccessBridge *b, Word object) {
  return field<std::int32_t, 0x320>(b, object, 0x488);
}
// 0x253e0 forwards the incoming low DWORD to JNI SetIntField, metadata 0x480.
inline void setKeyPressCount(GameAccessBridge *b, Word key, std::uint32_t count) {
  integerField(b, key, 0x480, count);
}
// 0x259a0: native float result, JNI slot 0x330, metadata 0x390.
inline float renderPartialTicks(GameAccessBridge *b, Word object) {
  return field<float, 0x330>(b, object, 0x390);
}
// 0x25ad0: native Word result, JNI slot 0x2f8, metadata 0x5e0.
inline Word inventoryContainerObject(GameAccessBridge *b, Word object) {
  return field<Word, 0x2f8>(b, object, 0x5e0);
}
// 0x25b60: native Word result, JNI slot 0x2f8, metadata 0x4e8.
inline Word containerObject(GameAccessBridge *b, Word object) {
  return field<Word, 0x2f8>(b, object, 0x4e8);
}
// 0x25d10: native Word result, JNI slot 0x110, metadata 0x5f8.
inline Word stackItemObject(GameAccessBridge *b, Word object) {
  return field<Word, 0x110>(b, object, 0x5f8);
}
// 0x25d70: native std::int32_t result, JNI slot 0x320, metadata 0x628.
inline std::int32_t stackCount(GameAccessBridge *b, Word object) {
  return field<std::int32_t, 0x320>(b, object, 0x628);
}
// 0x25dc0: native std::int32_t result, JNI slot 0x320, metadata 0x630.
inline std::int32_t stackDamage(GameAccessBridge *b, Word object) {
  return field<std::int32_t, 0x320>(b, object, 0x630);
}
// 0x25de0: native Word result, JNI slot 0x110, metadata 0x608.
inline Word stackTagList(GameAccessBridge *b, Word object) {
  return field<Word, 0x110>(b, object, 0x608);
}
// 0x25e10: native std::int32_t result, JNI slot 0x188, metadata 0x610.
inline std::int32_t stackMaximumCount(GameAccessBridge *b, Word object) {
  return field<std::int32_t, 0x188>(b, object, 0x610);
}
// 0x26190: native std::int32_t result, JNI slot 0x320, metadata 0x6c8.
inline std::int32_t containerWindowId(GameAccessBridge *b, Word object) {
  return field<std::int32_t, 0x320>(b, object, 0x6c8);
}
// 0x261b0: native Word result, JNI slot 0x110, metadata 0x6d0.
inline Word slotItemObject(GameAccessBridge *b, Word object) {
  return field<Word, 0x110>(b, object, 0x6d0);
}
// 0x266f0: native std::int32_t result, JNI slot 0x320, metadata 0x790.
inline std::int32_t packetEntityId(GameAccessBridge *b, Word object) {
  return field<std::int32_t, 0x320>(b, object, 0x790);
}
// 0x26b90: native float result, JNI slot 0x330, metadata 0xa50.
inline float packetFloatA50(GameAccessBridge *b, Word object) {
  return field<float, 0x330>(b, object, 0xa50);
}
// 0x26c30: native float result, JNI slot 0x330, metadata 0xa60.
inline float packetFloatA60(GameAccessBridge *b, Word object) {
  return field<float, 0x330>(b, object, 0xa60);
}
// 0x27d90: native Word result, JNI slot 0x1a0, metadata 0xba0.
inline Word uuidLeastWord(GameAccessBridge *b, Word object) {
  return field<Word, 0x1a0>(b, object, 0xba0);
}
// 0x27dc0: native Word result, JNI slot 0x1a0, metadata 0xba8.
inline Word uuidMostWord(GameAccessBridge *b, Word object) {
  return field<Word, 0x1a0>(b, object, 0xba8);
}
// 0x27f10: native std::int32_t result, JNI slot 0x188, metadata 0xbf8.
inline std::int32_t tagListCount(GameAccessBridge *b, Word object) {
  return field<std::int32_t, 0x188>(b, object, 0xbf8);
}
// 0x24e80 forwards only R8D as the first variadic integer.
inline Word listElement(GameAccessBridge *b, Word object, std::uint32_t index) {
  return indexedMethod(b, object, 0x30, index);
}
// 0x26140 forwards only R8D as the first variadic integer.
inline Word inventoryStack(GameAccessBridge *b, Word object,
                           std::uint32_t index) {
  return indexedMethod(b, object, 0x6e0, index);
}
// 0x27f40 forwards only R8D as the first variadic integer.
inline Word tagListElement(GameAccessBridge *b, Word object,
                           std::uint32_t index) {
  return indexedMethod(b, object, 0xc00, index);
}
// 0x266b0 preserves the input handle only when predicate AL is nonzero.
inline Word entityVelocityPacket(GameAccessBridge *b, Word packet) {
  return instance(b, packet, 0x788);
}
// 0x26b10 preserves the input handle only when predicate AL is nonzero.
inline Word packetClassA40(GameAccessBridge *b, Word packet) {
  return instance(b, packet, 0xa40);
}
// 0x26b50 preserves the input handle only when predicate AL is nonzero.
inline Word packetClassA48(GameAccessBridge *b, Word packet) {
  return instance(b, packet, 0xa48);
}
// Key helpers capture the array, then reload the environment/table for
// GetObjectArrayElement.
inline Word keyAt(GameAccessBridge *b, Word options, std::uint32_t index) {
  const auto array = objectField(b, options, 0x3b8);
  using Element = Word (*)(std::uintptr_t *, Word, std::int32_t);
  return slot<Element>(b->environment, 0x568)(
      b->environment, array, std::bit_cast<std::int32_t>(index));
}
// 0x24fe0 and 0x252c0 reread metadata after array retrieval; SBB subtracts one
// only for mode zero.
inline Word versionedKeyAt(GameAccessBridge *b, Word options,
                           std::uint32_t base) {
  const auto array = objectField(b, options, 0x3b8);
  std::uint32_t mode;
  std::memcpy(&mode, b->metadata, 4);
  using Element = Word (*)(std::uintptr_t *, Word, std::int32_t);
  return slot<Element>(b->environment, 0x568)(
      b->environment, array,
      std::bit_cast<std::int32_t>(base - std::uint32_t(mode < 1)));
}
// 0x25380: increment wraps in a DWORD; bridge is reread after the getter.
inline void incrementPresses(GameAccessBridge *b, Word key) {
  const auto next =
      std::uint32_t(field<std::int32_t, 0x320>(b, key, 0x480)) + 1u;
  integerField(b, key, 0x480, next);
}
// 0x25540: get three double fields, then write the complete native vector.
inline Word vectorObjectValues(Word output, GameAccessBridge *b, Word vector) {
  return getPosition(output, pointer(b), vector, 0x660);
}
// 0x25640: six independent JNI reads; pair is written after both triples.
inline Word boxObjectValues(Word output, GameAccessBridge *b, Word box) {
  double lo[3], hi[3];
  getPosition(pointer(lo), pointer(b), box, 0x4a8);
  getPosition(pointer(hi), pointer(b), box, 0x4c0);
  recovered_geometry_pair_96b0(object(output), lo, hi);
  return output;
}
// 0x25a80: exact R8D forwarded to SetIntField metadata 0x5d8.
inline void selectSlot(GameAccessBridge *b, Word inventory,
                       std::uint32_t slotIndex) {
  integerField(b, inventory, 0x5d8, slotIndex);
}
// 0x25b80 normalizes the class predicate, including null input handles.
inline std::uint8_t inventoryScreen(GameAccessBridge *b, Word screen) {
  return field<std::uint8_t, 0x100>(b, screen, 0x8a0) != 0;
}
// 0x25be0: method 0x4e0, integer zero, R8D slot, R9D action, fifth-stack mode.
inline void inventoryClick(GameAccessBridge *b, Word screen,
                           std::uint32_t slotIndex, std::uint32_t action,
                           std::uint32_t mode) {
  using Call = void (*)(std::uintptr_t *, Word, Word, ...);
  slot<Call>(b->environment, 0x1e8)(b->environment, screen,
                                    identifier(b, 0x4e0), 0u, slotIndex, action,
                                    mode);
}
// 0x25af0: native R8W is zero-extended before the variadic screen method call.
inline void screenActionCb0(GameAccessBridge *b, Word screen,
                            std::uint16_t character, std::uint32_t code) {
  using Call = void (*)(std::uintptr_t *, Word, Word, ...);
  slot<Call>(b->environment, 0x1e8)(b->environment, screen,
                                    identifier(b, 0xcb0),
                                    std::uint32_t(character), code);
}
// 0x25d40: R8 object is moved to R9 for the float method argument.
inline float blockEfficiency(GameAccessBridge *b, Word stack, Word block) {
  using Call = float (*)(std::uintptr_t *, Word, Word, ...);
  return slot<Call>(b->environment, 0x1b8)(b->environment, stack,
                                           identifier(b, 0x600), block);
}
// 0x25e40: static Boolean method, two object arguments; only AL is normalized.
inline std::uint8_t stackCompare(GameAccessBridge *b, Word left, Word right) {
  using Call = std::uint8_t (*)(std::uintptr_t *, Word, Word, ...);
  return slot<Call>(b->environment, 0x3a8)(b->environment, identifier(b, 0x5e8),
                                           identifier(b, 0x618), left,
                                           right) != 0;
}
// 0x25e80: Boolean instance method, only AL is normalized.
inline std::uint8_t stackFlag(GameAccessBridge *b, Word stack) {
  return field<std::uint8_t, 0x128>(b, stack, 0x620) != 0;
}
// 0x27f70: call-site consumers use EAX, or truncate it to AX explicitly.
// Preserve EAX.
inline std::uint32_t tagShortEax(GameAccessBridge *b, Word tag, Word name) {
  using Call = std::uint32_t (*)(std::uintptr_t *, Word, Word, ...);
  return slot<Call>(b->environment, 0x170)(b->environment, tag,
                                           identifier(b, 0xc10), name);
}

// Primitive indirect JNI calls retain a target captured by the caller when
// supplied.
inline std::uint8_t sameObject(Word environment, Word left, Word right,
                               Word capturedTarget) {
  using F = std::uint8_t (*)(std::uintptr_t *, Word, Word);
  auto *env = reinterpret_cast<std::uintptr_t *>(environment);
  auto f =
      capturedTarget ? reinterpret_cast<F>(capturedTarget) : slot<F>(env, 0xc0);
  return f(env, left, right);
}
inline std::uint32_t stringLength(Word environment, Word string,
                                  Word capturedTarget) {
  using F = std::uint32_t (*)(std::uintptr_t *, Word);
  auto *env = reinterpret_cast<std::uintptr_t *>(environment);
  auto f = capturedTarget ? reinterpret_cast<F>(capturedTarget)
                          : slot<F>(env, 0x520);
  return f(env, string);
}
inline Word acquireCriticalString(Word environment, Word string, Word isCopy,
                                  Word capturedTarget) {
  using F = Word (*)(std::uintptr_t *, Word, void *);
  auto *env = reinterpret_cast<std::uintptr_t *>(environment);
  auto f = capturedTarget ? reinterpret_cast<F>(capturedTarget)
                          : slot<F>(env, 0x700);
  return f(env, string, object(isCopy));
}
inline void releaseCriticalString(Word environment, Word string,
                                  Word characters, Word capturedTarget) {
  using F = void (*)(std::uintptr_t *, Word, const void *);
  auto *env = reinterpret_cast<std::uintptr_t *>(environment);
  auto f = capturedTarget ? reinterpret_cast<F>(capturedTarget)
                          : slot<F>(env, 0x708);
  f(env, string, object(characters));
}
inline Word newStringUtf(Word environment, Word utf) {
  using F = Word (*)(std::uintptr_t *, const char *);
  auto *env = reinterpret_cast<std::uintptr_t *>(environment);
  return slot<F>(env, 0x538)(env, reinterpret_cast<const char *>(utf));
}
inline Word arrayElement(Word environment, Word array, std::uint32_t index) {
  using F = Word (*)(std::uintptr_t *, Word, std::int32_t);
  auto *env = reinterpret_cast<std::uintptr_t *>(environment);
  return slot<F>(env, 0x568)(env, array, std::bit_cast<std::int32_t>(index));
}
inline Word capturedObjectMethod(Word environment, Word objectValue,
                                 Word method, Word capturedTarget) {
  using F = Word (*)(std::uintptr_t *, Word, Word);
  return reinterpret_cast<F>(capturedTarget)(
      reinterpret_cast<std::uintptr_t *>(environment), objectValue, method);
}
// 0x28ac0: retain only AL; ID subtraction and shifts wrap as DWORD operations.
inline std::uint8_t heldItemCanBlock(GameAccessBridge *b, Word item) {
  if (!item)
    return 0;
  const auto index =
      std::uint32_t(recovered_game_item_numeric_id(b, item)) - 267u;
  if (index > 16u)
    return 0;
  return std::uint8_t((0x10223u >> (index & 31u)) & 1u);
}
// 0x28b00: static object conversion 0x24240 then numeric block-ID query.
inline std::uint8_t itemIsBlock(GameAccessBridge *b, Word item) {
  if (!item)
    return 0;
  using F = Word (*)(std::uintptr_t *, Word, Word, ...);
  const auto block = slot<F>(b->environment, 0x390)(
      b->environment, identifier(b, 0x430), identifier(b, 0x440), item);
  return block ? std::uint8_t(blockNumericId(b, block) != 0) : 0;
}
// 0x29080: frame words are reread after every call; input offset depends on key
// code.
inline std::uint8_t attackInput(Word frame) {
  auto load = [&](std::size_t o) {
    Word v;
    std::memcpy(&v, reinterpret_cast<const std::uint8_t *>(frame) + o, 8);
    return v;
  };
  auto *b = bridge(load(0));
  const auto options = clientOptions(b, load(0x18));
  b = bridge(load(0));
  const auto key = keyAt(b, options, 0);
  b = bridge(load(0));
  const auto code = keyCode(b, key);
  const auto *input = reinterpret_cast<const std::uint8_t *>(load(0x30));
  return input[1 + std::uint32_t(code == -99)] != 0;
}
// 0x24b90 rereads metadata after object retrieval before ordinal query.
inline std::uint32_t hitFacing(GameAccessBridge *b, Word hit) {
  if (positionModeZero(b))
    return std::uint32_t(field<std::int32_t, 0x320>(b, hit, 0x3e8));
  const auto face = objectField(b, hit, 0x3f0);
  return std::uint32_t(field<std::int32_t, 0x188>(b, face, 0x148));
}
// 0x24c10: integer coordinates converted to binary64, write after all three
// reads.
inline Word hitBlockPosition(Word output, GameAccessBridge *b, Word hit) {
  if (!positionModeZero(b)) {
    const auto position = objectField(b, hit, 0x410);
    double v[3] = {double(field<std::int32_t, 0x320>(b, position, 0x458)),
                   double(field<std::int32_t, 0x320>(b, position, 0x460)),
                   double(field<std::int32_t, 0x320>(b, position, 0x468))};
    recovered_geometry_construct_93b0(object(output), v[0], v[1], v[2]);
  } else {
    const double x = field<std::int32_t, 0x320>(b, hit, 0x3f8),
                 y = field<std::int32_t, 0x320>(b, hit, 0x400),
                 z = field<std::int32_t, 0x320>(b, hit, 0x408);
    recovered_geometry_construct_93b0(object(output), x, y, z);
  }
  return output;
}
// 0x24ce0 writes each DWORD after its query, including overlap side effects.
inline Word integerHitPosition(Word output, GameAccessBridge *b, Word hit) {
  const bool legacy = positionModeZero(b);
  const auto source = legacy ? hit : objectField(b, hit, 0x410);
  const std::size_t metadata = legacy ? 0x3f8 : 0x458;
  auto *out = reinterpret_cast<std::uint8_t *>(output);
  for (unsigned i = 0; i < 3; ++i) {
    const auto value = field<std::int32_t, 0x320>(b, source, metadata + i * 8);
    std::memcpy(out + i * 4, &value, 4);
  }
  return output;
}
// 0x2ad20/0x2ad80 write the NaN-payload-like relationship flags via float
// setter.
inline void changeEntityFlags(GameAccessBridge *b, Word entity,
                              std::uint32_t mask, bool clear) {
  const auto bits =
      std::bit_cast<std::uint32_t>(field<float, 0x330>(b, entity, 0x5c0));
  std::uint32_t value;
  if (clear) {
    const auto old =
        (bits & 0xffff0000u) == 0xb3150000u ? bits & 0xffffu : 0xb3150000u;
    value = (old & ~mask) | 0xb3150000u;
  } else {
    const auto old = (bits & 0xffff0000u) == 0xb3150000u ? bits : 0xb3150000u;
    value = 0xb3150000u | ((old | mask) & 0xffffu);
  }
  floatField(b, entity, 0x5c0, std::bit_cast<float>(value));
}

// 0x24690: modern constructor/state/block chain; legacy three signed DWORDs.
inline Word worldBlockAt(GameAccessBridge *b, Word world, std::uint32_t x,
                         std::uint32_t y, std::uint32_t z) {
  using F = Word (*)(std::uintptr_t *, Word, Word, ...);
  if (!positionModeZero(b)) {
    const auto position = blockPositionObject(b, x, y, z);
    const auto state = slot<F>(b->environment, 0x110)(
        b->environment, world, identifier(b, 0x328), position);
    return field<Word, 0x110>(b, state, 0x428);
  }
  return slot<F>(b->environment, 0x110)(
      b->environment, world, identifier(b, 0x320),
      std::bit_cast<std::int32_t>(x), std::bit_cast<std::int32_t>(y),
      std::bit_cast<std::int32_t>(z));
}
// 0x24720 updates an existing coordinate object one field at a time when
// nonnull.
inline Word cachedWorldBlock(GameAccessBridge *b, Word world, Word position,
                             std::uint32_t x, std::uint32_t y,
                             std::uint32_t z) {
  using F = Word (*)(std::uintptr_t *, Word, Word, ...);
  if (position) {
    integerField(b, position, 0x458, x);
    integerField(b, position, 0x460, y);
    integerField(b, position, 0x468, z);
    const auto state = slot<F>(b->environment, 0x110)(
        b->environment, world, identifier(b, 0x328), position);
    return field<Word, 0x110>(b, state, 0x428);
  }
  return slot<F>(b->environment, 0x110)(
      b->environment, world, identifier(b, 0x320),
      std::bit_cast<std::int32_t>(x), std::bit_cast<std::int32_t>(y),
      std::bit_cast<std::int32_t>(z));
}

// 0x231e0/0x232e0 snapshot the second setter before local clamp arithmetic.
inline void setClampedRotation(GameAccessBridge *b, Word entity, Word packed,
                               std::size_t metadata, std::size_t boundsRva,
                               const std::uint8_t *image) {
  const auto yaw = floatValue(packed), pitch = floatValue(packed >> 32);
  floatField(b, entity, metadata, yaw);
  auto *environment = b->environment;
  using F = void (*)(std::uintptr_t *, Word, Word, float);
  const auto target = slot<F>(environment, 0x378);
  const auto method = identifier(b, metadata + 8);
  const auto limited = recovered_float_clamp_a1f0(
      readSingle(image, boundsRva), readSingle(image, boundsRva + 4), pitch);
  target(environment, entity, method, limited);
}
// 0x23dc0/0x23ce0 retain packed inputs and reload each field setter.
inline void setRotationPair(GameAccessBridge *b, Word entity, Word packed,
                            std::size_t metadata) {
  floatField(b, entity, metadata, floatValue(packed));
  floatField(b, entity, metadata + 8, floatValue(packed >> 32));
}

inline Word clientSingleton(GameAccessBridge *b) {
  using F = Word (*)(std::uintptr_t *, Word, Word);
  return slot<F>(b->environment, 0x488)(b->environment, identifier(b, 0x150),
                                        identifier(b, 0x180));
}
inline Word clientPlayerObject(GameAccessBridge *b, Word client) {
  return objectField(b, client, 0x188);
}
inline std::uint8_t keyPressed(GameAccessBridge *b, Word key) {
  return field<std::uint8_t, 0x300>(b, key, 0x478) != 0;
}
inline void setKeyPressed(GameAccessBridge *b, Word key, std::uint32_t value) {
  using F = void (*)(std::uintptr_t *, Word, Word, std::uint32_t);
  slot<F>(b->environment, 0x348)(b->environment, key, identifier(b, 0x478),
                                 value);
}

// BEGIN REVIEWED RENDER GAME ACCESS
// 0x27250: JNI slot 0x330, metadata 0x7c8; native float result.
inline float field7c8(GameAccessBridge *b, Word object) {
  return field<float, 0x330>(b, object, 0x7c8);
}
// 0x237b0: JNI slot 0x300, metadata 0x2f8; native std::uint8_t result.
inline std::uint8_t entityDead(GameAccessBridge *b, Word object) {
  return field<std::uint8_t, 0x300>(b, object, 0x2f8) != 0;
}
// 0x24640: JNI slot 0x2f8, metadata 0x370; native Word result.
inline Word worldObject370(GameAccessBridge *b, Word object) {
  return field<Word, 0x2f8>(b, object, 0x370);
}
// 0x244f0: JNI slot 0x2f8, metadata 0x760; native Word result.
inline Word object760(GameAccessBridge *b, Word object) {
  return field<Word, 0x2f8>(b, object, 0x760);
}
// 0x272a0: JNI slot 0x2f8, metadata 0x7d0; native Word result.
inline Word object7d0(GameAccessBridge *b, Word object) {
  return field<Word, 0x2f8>(b, object, 0x7d0);
}
// 0x22dd0: JNI slot 0x2f8, metadata 0x1e8; native Word result.
inline Word clientObject1e8(GameAccessBridge *b, Word object) {
  return field<Word, 0x2f8>(b, object, 0x1e8);
}
// 0x27b50: JNI slot 0x330, metadata 0xab0; native float result.
inline float fieldAb0(GameAccessBridge *b, Word object) {
  return field<float, 0x330>(b, object, 0xab0);
}
// 0x22d90: JNI slot 0x2f8, metadata 0x210; native Word result.
inline Word clientObject210(GameAccessBridge *b, Word object) {
  return field<Word, 0x2f8>(b, object, 0x210);
}
// 0x22db0: JNI slot 0x2f8, metadata 0x208; native Word result.
inline Word clientObject208(GameAccessBridge *b, Word object) {
  return field<Word, 0x2f8>(b, object, 0x208);
}
// 0x25310: JNI slot 0x320, metadata 0x3c0; native std::int32_t result.
inline std::int32_t integer3c0(GameAccessBridge *b, Word object) {
  return field<std::int32_t, 0x320>(b, object, 0x3c0);
}
// 0x23800: JNI slot 0x110, metadata 0x240; native Word result.
inline Word objectMethod240(GameAccessBridge *b, Word object) {
  return field<Word, 0x110>(b, object, 0x240);
}
// 0x26090: JNI slot 0x110, metadata 0x6a8; native Word result.
inline Word objectMethod6a8(GameAccessBridge *b, Word object) {
  return field<Word, 0x110>(b, object, 0x6a8);
}
// 0x23830: JNI slot 0x110, metadata 0x248; native Word result.
inline Word objectMethod248(GameAccessBridge *b, Word object) {
  return field<Word, 0x110>(b, object, 0x248);
}
// 0x27200: JNI slot 0x330, metadata 0x7c0; native float result.
inline float field7c0(GameAccessBridge *b, Word object) {
  return field<float, 0x330>(b, object, 0x7c0);
}
// 0x24620: JNI slot 0x2f8, metadata 0x368; native Word result.
inline Word worldObject368(GameAccessBridge *b, Word object) {
  return field<Word, 0x2f8>(b, object, 0x368);
}
// 0x27fa0: JNI slot 0x300, metadata 0xc28; native std::uint8_t result.
inline std::uint8_t flagC28(GameAccessBridge *b, Word object) {
  return field<std::uint8_t, 0x300>(b, object, 0xc28);
}
// 0x249f0: JNI slot 0x2f8, metadata 0xb00; native Word result.
inline Word objectB00(GameAccessBridge *b, Word object) {
  return field<Word, 0x2f8>(b, object, 0xb00);
}
// 0x24a50: JNI slot 0x2f8, metadata 0xb20; native Word result.
inline Word objectB20(GameAccessBridge *b, Word object) {
  return field<Word, 0x2f8>(b, object, 0xb20);
}
// 0x24ab0: JNI slot 0x2f8, metadata 0xb38; native Word result.
inline Word objectB38(GameAccessBridge *b, Word object) {
  return field<Word, 0x2f8>(b, object, 0xb38);
}
// 0x24a10: JNI slot 0x320, metadata 0xb08; native std::int32_t result.
inline std::int32_t integerB08(GameAccessBridge *b, Word object) {
  return field<std::int32_t, 0x320>(b, object, 0xb08);
}
// 0x24a30: JNI slot 0x320, metadata 0xb10; native std::int32_t result.
inline std::int32_t integerB10(GameAccessBridge *b, Word object) {
  return field<std::int32_t, 0x320>(b, object, 0xb10);
}
// 0x26060: JNI slot 0x188, metadata 0xf8; native std::int32_t result.
inline std::int32_t integerMethodF8(GameAccessBridge *b, Word object) {
  return field<std::int32_t, 0x188>(b, object, 0xf8);
}
// 0x236f0: JNI slot 0x128, metadata 0x238; native std::uint8_t result.
inline std::uint8_t flagMethod238(GameAccessBridge *b, Word object) {
  return field<std::uint8_t, 0x128>(b, object, 0x238) != 0;
}
// 0x23fc0: JNI slot 0x320, metadata 0x5a8; native std::int32_t result.
inline std::int32_t integer5a8(GameAccessBridge *b, Word object) {
  return field<std::int32_t, 0x320>(b, object, 0x5a8);
}
// 0x23900: JNI slot 0x128, metadata 0x260; native std::uint8_t result.
inline std::uint8_t flagMethod260(GameAccessBridge *b, Word object) {
  return field<std::uint8_t, 0x128>(b, object, 0x260);
}
// 0x25bb0: JNI slot 0x100, metadata 0xcb8; native std::uint8_t result.
inline std::uint8_t classPredicateCb8(GameAccessBridge *b, Word object) {
  return field<std::uint8_t, 0x100>(b, object, 0xcb8) != 0;
}
// 0x25c30: JNI slot 0x2f8, metadata 0xcc0; native Word result.
inline Word objectCc0(GameAccessBridge *b, Word object) {
  return field<Word, 0x2f8>(b, object, 0xcc0);
}
// 0x26220: JNI slot 0x2f8, metadata 0xcd0; native Word result.
inline Word objectCd0(GameAccessBridge *b, Word object) {
  return field<Word, 0x2f8>(b, object, 0xcd0);
}
// 0x27760: JNI static void slot 0x468, class 0x9b0, method 0x9c0.
inline void staticAction9c0(GameAccessBridge *b) {
  using F = void (*)(std::uintptr_t *, Word, Word, ...);
  slot<F>(b->environment, 0x468)(b->environment, identifier(b, 0x9b0),
                                 identifier(b, 0x9c0));
}
// 0x27820: JNI static void slot 0x468, class 0x9b0, method 0x9e0.
inline void staticAction9e0(GameAccessBridge *b) {
  using F = void (*)(std::uintptr_t *, Word, Word, ...);
  slot<F>(b->environment, 0x468)(b->environment, identifier(b, 0x9b0),
                                 identifier(b, 0x9e0));
}
// 0x277f0: JNI static void slot 0x468, class 0x9b0, method 0x9d8.
inline void staticAction9d8(GameAccessBridge *b) {
  using F = void (*)(std::uintptr_t *, Word, Word, ...);
  slot<F>(b->environment, 0x468)(b->environment, identifier(b, 0x9b0),
                                 identifier(b, 0x9d8));
}
// 0x27730: JNI static void slot 0x468, class 0x9b0, method 0x9b8.
inline void staticAction9b8(GameAccessBridge *b) {
  using F = void (*)(std::uintptr_t *, Word, Word, ...);
  slot<F>(b->environment, 0x468)(b->environment, identifier(b, 0x9b0),
                                 identifier(b, 0x9b8));
}
// 0x27c90: JNI static void slot 0x468, class 0xad0, method 0xad8.
inline void staticActionAd8(GameAccessBridge *b) {
  using F = void (*)(std::uintptr_t *, Word, Word, ...);
  slot<F>(b->environment, 0x468)(b->environment, identifier(b, 0xad0),
                                 identifier(b, 0xad8));
}
// 0x27cc0: JNI static void slot 0x468, class 0xad0, method 0xae0.
inline void staticActionAe0(GameAccessBridge *b) {
  using F = void (*)(std::uintptr_t *, Word, Word, ...);
  slot<F>(b->environment, 0x468)(b->environment, identifier(b, 0xad0),
                                 identifier(b, 0xae0));
}
// 0x27790: JNI static void slot 0x468, class 0x9b0, method 0x9e8.
inline void staticAction9e8(GameAccessBridge *b) {
  using F = void (*)(std::uintptr_t *, Word, Word, ...);
  slot<F>(b->environment, 0x468)(b->environment, identifier(b, 0x9b0),
                                 identifier(b, 0x9e8));
}
// 0x27880: JNI static void slot 0x468, class 0x9b0, method 0xa10.
inline void staticActionA10(GameAccessBridge *b) {
  using F = void (*)(std::uintptr_t *, Word, Word, ...);
  slot<F>(b->environment, 0x468)(b->environment, identifier(b, 0x9b0),
                                 identifier(b, 0xa10));
}

// 0x271d0: static object field, including legacy target of 0x22d40.
inline Word staticObject7b8(GameAccessBridge *b) {
  using F = Word (*)(std::uintptr_t *, Word, Word);
  return slot<F>(b->environment, 0x488)(b->environment, identifier(b, 0x7b0),
                                        identifier(b, 0x7b8));
}
// 0x22d40: modern field; legacy tail delegates to the actual 0x271d0 body.
inline Word versionedClientObject1f0(GameAccessBridge *b, Word client) {
  return positionModeZero(b) ? staticObject7b8(b)
                             : objectField(b, client, 0x1f0);
}
// 0x23fe0: exact NaN payload test; replacement is positive zero.
inline float finiteMethod590(GameAccessBridge *b, Word object) {
  const float value = field<float, 0x1b8>(b, object, 0x590);
  return (std::bit_cast<std::uint32_t>(value) & 0x7fffffffu) >= 0x7f800001u
             ? 0.0f
             : value;
}
// 0x23a80: exact replacement bits remain borrowed from the runtime image.
inline float finiteMethod528(GameAccessBridge *b, Word object,
                             const std::uint8_t *image) {
  const float value = field<float, 0x1b8>(b, object, 0x528);
  return (std::bit_cast<std::uint32_t>(value) & 0x7fffffffu) >= 0x7f800001u
             ? readSingle(image, 0x14f77c)
             : value;
}
// 0x24510: branch chosen once; convert each signed result before the next call.
inline Word integerVector760(Word output, GameAccessBridge *b, Word source) {
  const bool legacy = positionModeZero(b);
  if (!legacy)
    source = objectField(b, source, 0x768);
  const auto metadata = legacy ? 0x770u : 0x458u;
  const double x = field<std::int32_t, 0x320>(b, source, metadata);
  const double y = field<std::int32_t, 0x320>(b, source, metadata + 8);
  const double z = field<std::int32_t, 0x320>(b, source, metadata + 16);
  recovered_geometry_construct_93b0(object(output), x, y, z);
  return output;
}
// 0x27b70: native XMM2 float becomes JNI XMM3, without promotion.
inline void setFieldAb0(GameAccessBridge *b, Word receiver, float value) {
  floatField(b, receiver, 0xab0, value);
}
// 0x273e0: promote native XMM2 float to binary64 and pass an integer one.
inline float floatMethod908(GameAccessBridge *b, Word receiver, float value) {
  using F = float (*)(std::uintptr_t *, Word, Word, ...);
  const double promoted =
      _mm_cvtsd_f64(_mm_cvtss_sd(_mm_setzero_pd(), _mm_set_ss(value)));
  return slot<F>(b->environment, 0x1b8)(b->environment, receiver,
                                        identifier(b, 0x908), promoted, 1u);
}
// 0x278f0: four native singles are promoted in native instruction order.
inline void staticFourSinglesA20(GameAccessBridge *b, float first, float second,
                                 float third, float fourth) {
  using F = void (*)(std::uintptr_t *, Word, Word, ...);
  const double
      a = _mm_cvtsd_f64(_mm_cvtss_sd(_mm_setzero_pd(), _mm_set_ss(first))),
      c = _mm_cvtsd_f64(_mm_cvtss_sd(_mm_setzero_pd(), _mm_set_ss(second))),
      d = _mm_cvtsd_f64(_mm_cvtss_sd(_mm_setzero_pd(), _mm_set_ss(third))),
      e = _mm_cvtsd_f64(_mm_cvtss_sd(_mm_setzero_pd(), _mm_set_ss(fourth)));
  slot<F>(b->environment, 0x468)(b->environment, identifier(b, 0x9b0),
                                 identifier(b, 0xa20), a, c, d, e);
}
// 0x27590 retains the metadata pointer across both legacy rounding calls.
inline std::int32_t fontDraw9a8(GameAccessBridge *b, Word receiver, Word text,
                                float first, float second, std::uint32_t color,
                                std::uint8_t flag, const std::uint8_t *image) {
  using F = std::int32_t (*)(std::uintptr_t *, Word, Word, ...);
  const auto *metadata = b->metadata;
  std::uint32_t mode;
  std::memcpy(&mode, metadata, 4);
  if (mode) {
    auto *environment = b->environment;
    const auto target = slot<F>(environment, 0x188);
    Word method;
    std::memcpy(&method, metadata + 0x9a8, 8);
    const double x = _mm_cvtsd_f64(
                     _mm_cvtss_sd(_mm_setzero_pd(), _mm_set_ss(first))),
                 y = _mm_cvtsd_f64(
                     _mm_cvtss_sd(_mm_setzero_pd(), _mm_set_ss(second)));
    return target(environment, receiver, method, text, x, y, color,
                  std::uint32_t(flag));
  }
  const auto x =
      _mm_cvttss_si32(_mm_set_ss(recovered_round_float_b1fb0(first, image)));
  const auto y =
      _mm_cvttss_si32(_mm_set_ss(recovered_round_float_b1fb0(second, image)));
  auto *environment = b->environment;
  const auto target = slot<F>(environment, 0x188);
  Word method;
  std::memcpy(&method, metadata + 0x9a8, 8);
  return target(environment, receiver, method, text, x, y, color,
                std::uint32_t(flag));
}
// 0x24050 forwards R8D to first variadic integer lane R9D.
inline Word objectMethod598(GameAccessBridge *b, Word receiver,
                            std::uint32_t index) {
  return indexedMethod(b, receiver, 0x598, index);
}
// 0x27ba0 modern arguments start at native fifth stack word; legacy also
// forwards R8 and R9. Integer stack inputs remain 32 bits in both branches.
inline void methodAc0(GameAccessBridge *b, Word receiver, Word first,
                      Word second, Word third, std::uint32_t x,
                      std::uint32_t y) {
  using F = void (*)(std::uintptr_t *, Word, Word, ...);
  const auto *metadata = b->metadata;
  std::uint32_t mode;
  std::memcpy(&mode, metadata, 4);
  auto *environment = b->environment;
  const auto target = slot<F>(environment, 0x1e8);
  Word method;
  std::memcpy(&method, metadata + 0xac0, 8);
  if (mode)
    target(environment, receiver, method, third, x, y);
  else
    target(environment, receiver, method, first, second, third, x, y);
}
// 0x27c10 keeps R8 in the first variadic lane in both branches, adding R9 only
// in legacy mode. The eighth native stack argument remains a full Word.
inline void methodAc8(GameAccessBridge *b, Word receiver, Word first,
                      Word second, Word third, std::uint32_t x, std::uint32_t y,
                      Word last) {
  using F = void (*)(std::uintptr_t *, Word, Word, ...);
  const auto *metadata = b->metadata;
  std::uint32_t mode;
  std::memcpy(&mode, metadata, 4);
  auto *environment = b->environment;
  const auto target = slot<F>(environment, 0x1e8);
  Word method;
  std::memcpy(&method, metadata + 0xac8, 8);
  if (mode)
    target(environment, receiver, method, first, third, x, y, last);
  else
    target(environment, receiver, method, first, second, third, x, y, last);
}
// 0x278b0: two native DWORD arguments to static void method 0xa18.
inline void staticIntegersA18(GameAccessBridge *b, std::uint32_t x,
                              std::uint32_t y) {
  using F = void (*)(std::uintptr_t *, Word, Word, ...);
  slot<F>(b->environment, 0x468)(b->environment, identifier(b, 0x9b0),
                                 identifier(b, 0xa18), x, y);
}
// 0x27b20 constructs an object without Java constructor arguments.
inline Word newObjectAb8(GameAccessBridge *b) {
  using F = Word (*)(std::uintptr_t *, Word, Word, ...);
  return slot<F>(b->environment, 0xe0)(b->environment, identifier(b, 0xaa8),
                                       identifier(b, 0xab8));
}
// 0x27560: integer method with one object argument.
inline std::int32_t fontMeasure9a0(GameAccessBridge *b, Word receiver,
                                   Word text) {
  using F = std::int32_t (*)(std::uintptr_t *, Word, Word, ...);
  return slot<F>(b->environment, 0x188)(b->environment, receiver,
                                        identifier(b, 0x9a0), text);
}
// 0x23860: static integer method with one exact Word argument.
inline std::int32_t staticIntegerAf0(GameAccessBridge *b, Word value) {
  using F = std::int32_t (*)(std::uintptr_t *, Word, Word, ...);
  return slot<F>(b->environment, 0x408)(b->environment, identifier(b, 0xae8),
                                        identifier(b, 0xaf0), value);
}
// 0x248f0: two native DWORDs to object method 0x340.
inline Word indexedObject340(GameAccessBridge *b, Word receiver,
                             std::uint32_t first, std::uint32_t second) {
  using F = Word (*)(std::uintptr_t *, Word, Word, ...);
  return slot<F>(b->environment, 0x110)(b->environment, receiver,
                                        identifier(b, 0x340), first, second);
}
// 0x24990 retains the fetched object only after its reloaded instance query.
inline Word retainedObject378(GameAccessBridge *b, Word receiver) {
  const auto value = objectField(b, receiver, 0x378);
  return instance(b, value, 0xb30);
}
// 0x254f0 snapshots all three binary64 words before invoking NewObject.
inline Word newVector658(GameAccessBridge *b, const double *coordinates) {
  using F = Word (*)(std::uintptr_t *, Word, Word, ...);
  auto *environment = b->environment;
  const auto target = slot<F>(environment, 0xe0);
  const auto cls = identifier(b, 0x650), method = identifier(b, 0x658);
  const double x = coordinates[0], y = coordinates[1], z = coordinates[2];
  return target(environment, cls, method, x, y, z);
}
// 0x24860: two object inputs followed by three byte-to-DWORD Boolean inputs.
inline Word rayMethod330(GameAccessBridge *b, Word receiver, Word first,
                         Word second, std::uint8_t a, std::uint8_t c,
                         std::uint8_t d) {
  using F = Word (*)(std::uintptr_t *, Word, Word, ...);
  return slot<F>(b->environment, 0x110)(
      b->environment, receiver, identifier(b, 0x330), first, second,
      std::uint32_t(a), std::uint32_t(c), std::uint32_t(d));
}
// 0x25840 normalizes the static Boolean method's AL only.
inline std::uint8_t staticFlag90(GameAccessBridge *b) {
  using F = std::uint8_t (*)(std::uintptr_t *, Word, Word, ...);
  return slot<F>(b->environment, 0x3a8)(b->environment, identifier(b, 0x88),
                                        identifier(b, 0x90)) != 0;
}
// 0x25880 zero-extends native DL rather than normalizing it to 0/1.
inline void staticByte98(GameAccessBridge *b, std::uint8_t value) {
  using F = void (*)(std::uintptr_t *, Word, Word, ...);
  slot<F>(b->environment, 0x468)(b->environment, identifier(b, 0x88),
                                 identifier(b, 0x98), std::uint32_t(value));
}
// 0x27a60/0x27a90 return signed DWORD static fields via JNI slot 0x4b0.
inline std::int32_t staticIntegerD0(GameAccessBridge *b) {
  using F = std::int32_t (*)(std::uintptr_t *, Word, Word);
  return slot<F>(b->environment, 0x4b0)(b->environment, identifier(b, 0xb8),
                                        identifier(b, 0xd0));
}
inline std::int32_t staticIntegerD8(GameAccessBridge *b) {
  using F = std::int32_t (*)(std::uintptr_t *, Word, Word);
  return slot<F>(b->environment, 0x4b0)(b->environment, identifier(b, 0xb8),
                                        identifier(b, 0xd8));
}
// 0x25940: two DWORDs to static void method 0xb0.
inline void staticIntegersB0(GameAccessBridge *b, std::uint32_t x,
                             std::uint32_t y) {
  using F = void (*)(std::uintptr_t *, Word, Word, ...);
  slot<F>(b->environment, 0x468)(b->environment, identifier(b, 0x88),
                                 identifier(b, 0xb0), x, y);
}
// 0x27fc0: object-valued static method, full Word Java argument.
inline Word staticObjectCe0(GameAccessBridge *b, Word argument) {
  using F = Word (*)(std::uintptr_t *, Word, Word, ...);
  return slot<F>(b->environment, 0x390)(b->environment, identifier(b, 0xcd8),
                                        identifier(b, 0xce0), argument);
}
// 0x261e0 retains its original input handle when the instance query AL is
// nonzero.
inline Word retainedClassCc8(GameAccessBridge *b, Word argument) {
  return instance(b, argument, 0xcc8);
}
// Direct dependencies of formatted message algorithm 0x291f0.
inline Word textComponentObject(GameAccessBridge *b, Word text) {
  using F = Word (*)(std::uintptr_t *, Word, Word, ...);
  return slot<F>(b->environment, 0xe0)(b->environment, identifier(b, 0xbb0),
                                       identifier(b, 0xbb8), text);
}
inline void entityMessage(GameAccessBridge *b, Word player, Word component) {
  using F = void (*)(std::uintptr_t *, Word, Word, ...);
  slot<F>(b->environment, 0x1e8)(b->environment, player, identifier(b, 0x8e0),
                                 component);
}
// END REVIEWED RENDER GAME ACCESS

// BEGIN REVIEWED REMAINING GAME ACCESS
// 0x22d10: JNI slot 0x110, metadata 0x158.
inline Word clientMethod158(GameAccessBridge*b,Word receiver){return field<Word,0x110>(b,receiver,0x158);}
// 0x22df0: JNI slot 0x2f8, metadata 0x218.
inline Word clientObject218(GameAccessBridge*b,Word receiver){return field<Word,0x2f8>(b,receiver,0x218);}
// 0x22e90: JNI slot 0x320, metadata 0x1b8.
inline std::int32_t clientInteger1b8(GameAccessBridge*b,Word receiver){return field<std::int32_t,0x320>(b,receiver,0x1b8);}
// 0x23930: JNI slot 0x2f8, metadata 0x308.
inline Word entityObject308(GameAccessBridge*b,Word receiver){return field<Word,0x2f8>(b,receiver,0x308);}
// 0x24080: JNI slot 0x2f8, metadata 0x5b0.
inline Word entityObject5b0(GameAccessBridge*b,Word receiver){return field<Word,0x2f8>(b,receiver,0x5b0);}
// 0x259f0: JNI slot 0x330, metadata 0x398.
inline float single398(GameAccessBridge*b,Word receiver){return field<float,0x330>(b,receiver,0x398);}
// 0x25eb0: JNI slot 0x2f8, metadata 0x690.
inline Word object690(GameAccessBridge*b,Word receiver){return field<Word,0x2f8>(b,receiver,0x690);}
// 0x25ed0: JNI slot 0x2f8, metadata 0x698.
inline Word object698(GameAccessBridge*b,Word receiver){return field<Word,0x2f8>(b,receiver,0x698);}
// 0x26010: JNI slot 0x2f8, metadata 0xc48.
inline Word objectC48(GameAccessBridge*b,Word receiver){return field<Word,0x2f8>(b,receiver,0xc48);}
// 0x26030: JNI slot 0x110, metadata 0xc50.
inline Word objectMethodC50(GameAccessBridge*b,Word receiver){return field<Word,0x110>(b,receiver,0xc50);}
// 0x26170: JNI slot 0x2f8, metadata 0xca0.
inline Word objectCa0(GameAccessBridge*b,Word receiver){return field<Word,0x2f8>(b,receiver,0xca0);}
// 0x27d30: JNI slot 0x110, metadata 0xb50.
inline Word objectMethodB50(GameAccessBridge*b,Word receiver){return field<Word,0x110>(b,receiver,0xb50);}
// 0x27df0: JNI slot 0x330, metadata 0xbc8.
inline float singleBc8(GameAccessBridge*b,Word receiver){return field<float,0x330>(b,receiver,0xbc8);}
// 0x27e90: JNI slot 0x300, metadata 0xbd8.
inline std::uint8_t byteBd8(GameAccessBridge*b,Word receiver){return field<std::uint8_t,0x300>(b,receiver,0xbd8);}
// 0x263c0: JNI slot 0x300, metadata 0x718.
inline std::uint8_t flag718(GameAccessBridge*b,Word receiver){return field<std::uint8_t,0x300>(b,receiver,0x718)!=0;}
// 0x271a0: JNI slot 0x188, metadata 0x148.
inline std::int32_t integerMethod148(GameAccessBridge*b,Word receiver){return field<std::int32_t,0x188>(b,receiver,0x148);}
// 0x240d0: JNI slot 0x330, metadata 0x5c0.
inline float single5c0(GameAccessBridge*b,Word receiver){return field<float,0x330>(b,receiver,0x5c0);}
// 0x23a10: native R8D to JNI R9D.
inline void setInteger550(GameAccessBridge*b,Word receiver,std::uint32_t value){integerField(b,receiver,0x550,value);}
// 0x23b80: native R8D to JNI R9D.
inline void setInteger570(GameAccessBridge*b,Word receiver,std::uint32_t value){integerField(b,receiver,0x570,value);}
// 0x25330: native R8D to JNI R9D.
inline void setInteger3c0(GameAccessBridge*b,Word receiver,std::uint32_t value){integerField(b,receiver,0x3c0,value);}
// 0x279c0: native R8D to JNI R9D.
inline void setIntegerC38(GameAccessBridge*b,Word receiver,std::uint32_t value){integerField(b,receiver,0xc38,value);}
// 0x27e60: native R8D to JNI R9D.
inline void setIntegerBd0(GameAccessBridge*b,Word receiver,std::uint32_t value){integerField(b,receiver,0xbd0,value);}
// 0x23e90: native XMM2 to JNI XMM3 without binary64 promotion.
inline void setSingle8d8(GameAccessBridge*b,Word receiver,float value){floatField(b,receiver,0x8d8,value);}
// 0x27e10: native XMM2 to JNI XMM3 without binary64 promotion.
inline void setSingleBc8(GameAccessBridge*b,Word receiver,float value){floatField(b,receiver,0xbc8,value);}
// 0x264f0: retain the original handle iff JNI AL is nonzero.
inline Word retainedClass738(GameAccessBridge*b,Word receiver){return instance(b,receiver,0x738);}
// 0x26cc0: retain the original handle iff JNI AL is nonzero.
inline Word retainedClassA70(GameAccessBridge*b,Word receiver){return instance(b,receiver,0xa70);}
// 0x26ec0: retain the original handle iff JNI AL is nonzero.
inline Word retainedClassBe8(GameAccessBridge*b,Word receiver){return instance(b,receiver,0xbe8);}
// 0x26f00: retain the original handle iff JNI AL is nonzero.
inline Word retainedClassC60(GameAccessBridge*b,Word receiver){return instance(b,receiver,0xc60);}
// 0x26ff0: retain the original handle iff JNI AL is nonzero.
inline Word retainedClassC88(GameAccessBridge*b,Word receiver){return instance(b,receiver,0xc88);}
// 0x27160: retain the original handle iff JNI AL is nonzero.
inline Word retainedClassD08(GameAccessBridge*b,Word receiver){return instance(b,receiver,0xd08);}
// 0x27cf0: retain the original handle iff JNI AL is nonzero.
inline Word retainedClassB48(GameAccessBridge*b,Word receiver){return instance(b,receiver,0xb48);}

// 0x257a0: normalize only the static Boolean method's AL.
inline std::uint8_t staticFlag70(GameAccessBridge*b){using F=std::uint8_t(*)(std::uintptr_t*,Word,Word,...);return slot<F>(b->environment,0x3a8)(b->environment,identifier(b,0x60),identifier(b,0x70))!=0;}
// 0x26f40: static object field with independent class and field IDs.
inline Word staticObjectC80(GameAccessBridge*b){using F=Word(*)(std::uintptr_t*,Word,Word);return slot<F>(b->environment,0x488)(b->environment,identifier(b,0xc78),identifier(b,0xc80));}
// 0x26f70 preserves the full native Word constructor argument.
inline Word newObjectC70(GameAccessBridge*b,Word argument){using F=Word(*)(std::uintptr_t*,Word,Word,...);return slot<F>(b->environment,0xe0)(b->environment,identifier(b,0xc60),identifier(b,0xc70),argument);}
// 0x27030 forwards native EDX, zero extended to the constructor's DWORD lane.
inline Word newIntegerObjectC90(GameAccessBridge*b,std::uint32_t argument){using F=Word(*)(std::uintptr_t*,Word,Word,...);return slot<F>(b->environment,0xe0)(b->environment,identifier(b,0xc88),identifier(b,0xc90),argument);}
// 0x274c0 returns the meaningful byte directly, including values other than 1.
inline std::uint8_t byteMethod978(GameAccessBridge*b,Word receiver,Word argument){using F=std::uint8_t(*)(std::uintptr_t*,Word,Word,...);return slot<F>(b->environment,0x128)(b->environment,receiver,identifier(b,0x978),argument);}
// 0x24f40 moves native R8 into the first JNI variadic Word lane.
inline Word objectMethod58(GameAccessBridge*b,Word receiver,Word argument){using F=Word(*)(std::uintptr_t*,Word,Word,...);return slot<F>(b->environment,0x110)(b->environment,receiver,identifier(b,0x58),argument);}
// 0x27eb0 forwards R8D unmodified, rather than normalizing or truncating AL.
inline void setBooleanBd8(GameAccessBridge*b,Word receiver,std::uint32_t value){using F=void(*)(std::uintptr_t*,Word,Word,std::uint32_t);slot<F>(b->environment,0x348)(b->environment,receiver,identifier(b,0xbd8),value);}
// 0x25f80 captures the first metadata pointer for the branch and array class.
// The bridge is reloaded after NewObjectArray, as in the observed instructions.
inline void objectAction6f8(GameAccessBridge*b,Word receiver,Word argument){
  using Array=Word(*)(std::uintptr_t*,std::uint32_t,Word,Word);
  using Action=void(*)(std::uintptr_t*,Word,Word,...);
  const auto*metadata=b->metadata;Word method;std::memcpy(&method,metadata+0x6f8,8);
  if(method){Word cls;std::memcpy(&cls,metadata+0xc58,8);auto*environment=b->environment;
    const auto array=slot<Array>(environment,0x560)(environment,0u,cls,Word(0));
    environment=b->environment;slot<Action>(environment,0x1e8)(environment,receiver,identifier(b,0x6f8),argument,array);
  }else{auto*environment=b->environment;std::memcpy(&method,metadata+0x700,8);slot<Action>(environment,0x1e8)(environment,receiver,method,argument);}
}
// 0x26fb0 reloads bridge metadata/environment between its two JNI operations.
inline std::int32_t objectIntegerC68(GameAccessBridge*b,Word receiver){const auto value=objectField(b,receiver,0xc68);return integerMethod148(b,value);}
// 0x2acb0 decodes a literal float payload tag; it does not compare a float value.
inline std::uint32_t taggedValue5c0(GameAccessBridge*b,Word receiver){const auto bits=std::bit_cast<std::uint32_t>(single5c0(b,receiver));return (bits&0xffff0000u)==0xb3150000u?bits&0xffffu:0u;}
// 0x29f90 reads current mutable storage; no runtime value becomes a default.
inline Word observedWord2f7b88(const std::uint8_t*stateImage){return readWord(stateImage,0x2f7b88);}
// 0x233b0: yaw/pitch fields, exact binary64 angle arithmetic, native single
// sine/cosine, then single products converted to the final binary64 vector.
inline Word directionVector233b0(Word output,GameAccessBridge*b,Word receiver,const std::uint8_t*image){
  const float yaw=field<float,0x330>(b,receiver,0x298);
  const float pitch=field<float,0x330>(b,receiver,0x2a0);
  double factor,divisor;std::memcpy(&factor,image+0x14f750,8);std::memcpy(&divisor,image+0x14f758,8);
  auto yawDouble=_mm_cvtss_sd(_mm_setzero_pd(),_mm_set_ss(yaw));
  yawDouble=_mm_mul_sd(yawDouble,_mm_set_sd(factor));yawDouble=_mm_div_sd(yawDouble,_mm_set_sd(divisor));yawDouble=_mm_add_sd(yawDouble,_mm_set_sd(factor));
  const float yawRadians=_mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),yawDouble));
  const float yawCosine=recovered_cosine_b3590(yawRadians,image);
  const float yawSine=recovered_sine_b1cf0(yawRadians,image);
  auto pitchDouble=_mm_cvtss_sd(_mm_setzero_pd(),_mm_set_ss(pitch));
  pitchDouble=_mm_mul_sd(pitchDouble,_mm_set_sd(factor));pitchDouble=_mm_div_sd(pitchDouble,_mm_set_sd(divisor));
  const float pitchRadians=_mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),pitchDouble));
  const float pitchCosine=recovered_cosine_b3590(pitchRadians,image);
  std::uint32_t sign;std::memcpy(&sign,image+0x14f760,4);
  const float negativeCosine=std::bit_cast<float>(std::bit_cast<std::uint32_t>(pitchCosine)^sign);
  const float pitchSine=recovered_sine_b1cf0(pitchRadians,image);
  const auto xProduct=_mm_mul_ss(_mm_set_ss(yawSine),_mm_set_ss(negativeCosine));
  const double x=_mm_cvtsd_f64(_mm_cvtss_sd(_mm_setzero_pd(),xProduct));
  const double y=_mm_cvtsd_f64(_mm_cvtss_sd(_mm_setzero_pd(),_mm_set_ss(pitchSine)));
  const auto zProduct=_mm_mul_ss(_mm_set_ss(negativeCosine),_mm_set_ss(yawCosine));
  const double z=_mm_cvtsd_f64(_mm_cvtss_sd(_mm_setzero_pd(),zProduct));
  recovered_geometry_construct_93b0(object(output),x,y,z);return output;
}
// 0x290d0: exact UTF16 character table, recovered from image RVA0x14fb00.
// Only constants are borrowed; the branch mapping is the observed immutable code.
inline Word textColor290d0(Word output,std::uint16_t code,const std::uint8_t*image){
  Word pair=0;std::uint32_t blue=0;auto blueAt=[&](std::size_t at){std::memcpy(&blue,image+at,4);};
  auto pairAt=[&](std::size_t at){pair=readWord(image,at);};
  switch(code){
  case '0':break;
  case '1':blueAt(0x14fa90);break;
  case '2':pairAt(0x14fae0);break;
  case '3':pairAt(0x14fae0);blueAt(0x14fa90);break;
  case '4':pair=std::bit_cast<std::uint32_t>(readSingle(image,0x14fa90));break;
  case '5':pair=std::bit_cast<std::uint32_t>(readSingle(image,0x14fa90));blueAt(0x14fa90);break;
  case '6':pairAt(0x14faf0);break;
  case '7':pairAt(0x14fa80);blueAt(0x14fa90);break;
  case '8':pairAt(0x14fa70);blueAt(0x14fa30);break;
  case '9':pairAt(0x14fa70);blueAt(0x14fa50);break;
  case 'a':pairAt(0x14fad0);blueAt(0x14fa30);break;
  case 'b':pairAt(0x14fad0);blueAt(0x14fa50);break;
  case 'c':pairAt(0x14fac0);blueAt(0x14fa30);break;
  case 'd':pairAt(0x14fac0);blueAt(0x14fa50);break;
  case 'e':pairAt(0x14fa20);blueAt(0x14fa30);break;
  default:pairAt(0x14fa20);blueAt(0x14fa50);break;
  }
  auto*destination=reinterpret_cast<std::uint8_t*>(std::uintptr_t(output));std::memcpy(destination,&pair,8);std::memcpy(destination+8,&blue,4);return output;
}

// END REVIEWED REMAINING GAME ACCESS
} // namespace reconstruction::game_access
#endif // SLINKY_SHARE_457BCAFE2F1B4020D437
