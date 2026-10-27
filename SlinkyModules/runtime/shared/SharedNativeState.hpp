#ifndef SLINKY_SHARE_261765C11DFE4C0891E9
#define SLINKY_SHARE_261765C11DFE4C0891E9
#include "../native/verified/module_access_helpers.hpp"
#include "../native/verified/module_float_math.hpp"
#include "../native/verified/module_format.hpp"
#include "Rounding.hpp"
#include "SharedGameAccess.hpp"
#include "Trigonometry.hpp"
#include "DecodedNumericService.hpp"
#include "DecodedWindowQueryService.hpp"
#include <bit>
#include <cstdint>
#include <cstring>
#include <emmintrin.h>
// Shared native state is caller-owned and mutable. Offsets describe observed
// storage relationships, without assigning captured values as defaults.
namespace reconstruction::native_state {
using Word = std::uint64_t;
template <class T> inline T read(const std::uint8_t *image, std::size_t rva) {
  T v;
  std::memcpy(&v, image + rva, sizeof(v));
  return v;
}
template <class T>
inline void write(std::uint8_t *image, std::size_t rva, T v) {
  std::memcpy(image + rva, &v, sizeof(v));
}
// 0x29800 retains a maximum unsigned priority; known callers consume AL.
inline std::uint8_t claimRotation(std::uint8_t *image, std::uint32_t priority) {
  const auto previous = read<std::uint32_t>(image, 0x2f7b50);
  if (priority >= previous)
    write(image, 0x2f7b50, priority);
  return priority >= previous;
}
// 0x29820 adds packed native floats then resets the age DWORD.
inline void publishRotationDelta(std::uint8_t *image, Word delta) {
  const auto result =
      recovered_angle_add_9de0(read<Word>(image, 0x2f7b58), delta);
  write(image, 0x2f7b58, result);
  write(image, 0x2f7b60, std::uint32_t(0));
}
inline Word rotationOffset(const std::uint8_t *image) {
  return read<Word>(image, 0x2f7b58);
}
// 0x42c30 consumes the timer-range enable byte, signed duration and flag bit0.
inline std::uint8_t timerRangeFrozen(const std::uint8_t *image) {
  if(image[0x2f3174]!=1)return 0;
  return (std::uint8_t(read<std::int32_t>(image,0x3043d8)>0)|image[0x3043dc])&1;
}
inline std::uint8_t rotationStateAvailable(const std::uint8_t *image) {
  return image[0x2f7b90];
}
inline Word retainedRotation(const std::uint8_t *image) {
  return read<Word>(image, 0x2f7b70);
}
// 0x2aa80/0x2aab0 retain an owner token until the matching owner releases it.
inline std::uint8_t claimAction(std::uint8_t *image, Word token) {
  const auto owner = read<Word>(image, 0x2f7ba8);
  if (owner == token)
    return 1;
  if (owner)
    return 0;
  write(image, 0x2f7ba8, token);
  return 1;
}
inline void releaseAction(std::uint8_t *image, Word token) {
  if (read<Word>(image, 0x2f7ba8) == token)
    write(image, 0x2f7ba8, Word(0));
}
// 0x2aad0: native DWORD arithmetic precedes zero-extension for CVTSI2SS r64.
inline Word inventoryGrid(std::uint32_t index) {
  std::uint32_t first, secondBits;
  if (index <= 8u) {
    first = index - 5u;
    secondBits = 0x3f800000u;
  } else {
    const auto quotient =
        std::uint32_t((std::uint64_t(index) * 0x38e38e39u) >> 33);
    const auto remainder = index - quotient * 9u;
    first = quotient + 3u;
    secondBits = std::bit_cast<std::uint32_t>(_mm_cvtss_f32(_mm_cvtsi32_ss(
        _mm_setzero_ps(), std::bit_cast<std::int32_t>(remainder))));
  }
  const float low = _mm_cvtss_f32(
      _mm_cvtsi64_ss(_mm_setzero_ps(), std::int64_t(std::uint64_t(first))));
  return std::bit_cast<std::uint32_t>(low) | (Word(secondBits) << 32);
}
// 0x284f0 queues module state changes after its event-table cancellation pass.
inline std::uint8_t scheduleModuleAction(Word manager, Word module,
                                         std::uint8_t enabled) {
  auto *m = reinterpret_cast<std::uint8_t *>(manager);
  if (reinterpret_cast<const std::uint8_t *>(module)[0x14] == enabled)
    return 1;
  std::size_t offset = 0x2e8;
  if (!enabled) {
    std::uint8_t event[0x48] = {};
    write(event, 0, std::uint32_t(4));
    write(event, 8, module);
    const auto table = read<Word>(m, 0x230);
    auto *entry = reinterpret_cast<const Word *>(table);
    Word function = *entry++;
    if (function) {
      do {
        reinterpret_cast<void (*)(std::uint8_t *)>(function)(event);
        function = *entry++;
      } while (function);
      if (event[0x10] & 1)
        return 0;
    }
    offset = 0x2f8;
  }
  const auto data = read<Word>(m, offset), count = read<Word>(m, offset + 8);
  write(reinterpret_cast<std::uint8_t *>(data), std::size_t(count * 8), module);
  write(m, offset + 8, count + 1u);
  return 1;
}
// 0x9f10 forwards ordered single-precision coordinate differences to 0x13cfc0.
template<class Angular> inline float gridBearingUsing(Word from, Word to,
                         Angular singleAngular) {
  const auto x0 = std::bit_cast<float>(std::uint32_t(from)),
             y0 = std::bit_cast<float>(std::uint32_t(from >> 32)),
             x1 = std::bit_cast<float>(std::uint32_t(to)),
             y1 = std::bit_cast<float>(std::uint32_t(to >> 32));
  const auto dx = _mm_sub_ss(_mm_set_ss(x1), _mm_set_ss(x0)),
             dy = _mm_sub_ss(_mm_set_ss(y1), _mm_set_ss(y0));
  return singleAngular(_mm_cvtss_f32(dy), _mm_cvtss_f32(dx));
}
inline float gridBearing(Word from, Word to,float (*singleAngular)(float,float)) {
  return gridBearingUsing(from,to,singleAngular);
}
inline float gridBearingDecoded(Word from, Word to,const numeric_service::Context &numeric) {
  return gridBearingUsing(from,to,[&numeric](float first,float second) {
    return numeric_service::floatDirection_13cfc0(numeric,first,second);
  });
}
// 0x9f80 retains native SSE sequence and two-double 0x13cfb0 endpoint.
template<class Angular> inline Word targetAnglesUsing(const double *from, const double *to,
                         const std::uint8_t *image,
                         Angular angular) {
  const auto dx = _mm_sub_sd(_mm_set_sd(to[0]), _mm_set_sd(from[0])),
             dy = _mm_sub_sd(_mm_set_sd(to[1]), _mm_set_sd(from[1])),
             dz = _mm_sub_sd(_mm_set_sd(to[2]), _mm_set_sd(from[2]));
  const auto z2 = _mm_mul_sd(dz, dz), x2 = _mm_mul_sd(dx, dx);
  const double horizontal =
      _mm_cvtsd_f64(_mm_sqrt_sd(_mm_setzero_pd(), _mm_add_sd(x2, z2)));
  auto yaw = _mm_set_sd(angular(_mm_cvtsd_f64(dz), _mm_cvtsd_f64(dx)));
  yaw = _mm_mul_sd(yaw, _mm_set_sd(read<double>(image, 0x13e8a0)));
  const auto pi = _mm_set_sd(read<double>(image, 0x13e8a8));
  yaw = _mm_div_sd(yaw, pi);
  yaw = _mm_add_sd(yaw, _mm_set_sd(read<double>(image, 0x13e8b0)));
  const auto low = _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(), yaw));
  auto pitch = _mm_set_sd(angular(_mm_cvtsd_f64(dy), horizontal));
  pitch = _mm_mul_sd(pitch, _mm_set_sd(read<double>(image, 0x13e8b8)));
  pitch = _mm_div_sd(pitch, pi);
  const auto high = _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(), pitch));
  return std::bit_cast<std::uint32_t>(low) |
         (Word(std::bit_cast<std::uint32_t>(high)) << 32);
}
inline Word targetAngles(const double *from, const double *to,
                         const std::uint8_t *image,
                         double (*angular)(double, double)) {
  return targetAnglesUsing(from,to,image,angular);
}
inline Word targetAnglesDecoded(const double *from, const double *to,
                                const std::uint8_t *image,
                                const numeric_service::Context &numeric) {
  return targetAnglesUsing(from,to,image,[&numeric](double first,double second) {
    return numeric_service::direction_13cfb0(numeric,first,second);
  });
}
// 0x29290: typed native five-argument movement vector; exact float lanes.
inline double *movementVector(double *out, Word rotation, float forward,
                              float strafe, float speed,
                              const std::uint8_t *image) {
  auto f = _mm_mul_ss(_mm_set_ss(forward),
                      _mm_set_ss(read<float>(image, 0x14fbd8))),
       s = _mm_mul_ss(_mm_set_ss(strafe),
                      _mm_set_ss(read<float>(image, 0x14fbd8)));
  auto norm = _mm_add_ss(_mm_mul_ss(s, s), _mm_mul_ss(f, f));
  if (read<float>(image, 0x14fbdc) > _mm_cvtss_f32(norm)) {
    recovered_geometry_construct_93b0(out, 0, 0, 0);
    return out;
  }
  auto scale =
      _mm_mul_ss(_mm_set_ss(speed), _mm_set_ss(read<float>(image, 0x14fbe0)));
  auto length = _mm_sqrt_ss(norm);
  length = _mm_max_ss(_mm_set_ss(read<float>(image, 0x14fbe4)), length);
  scale = _mm_div_ss(scale, length);
  s = _mm_mul_ss(s, scale);
  f = _mm_mul_ss(f, scale);
  auto angle =
      _mm_cvtss_sd(_mm_setzero_pd(),
                   _mm_set_ss(std::bit_cast<float>(std::uint32_t(rotation))));
  angle = _mm_mul_sd(angle, _mm_set_sd(read<double>(image, 0x14fbe8)));
  angle = _mm_div_sd(angle, _mm_set_sd(read<double>(image, 0x14fbf0)));
  const auto theta = _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(), angle));
  const auto sine = _mm_set_ss(recovered_sine_b1cf0(theta, image));
  const auto cosine = _mm_set_ss(recovered_cosine_b3590(theta, image));
  auto x = _mm_sub_ss(_mm_mul_ss(s, cosine), _mm_mul_ss(f, sine));
  out[0] = _mm_cvtsd_f64(_mm_cvtss_sd(_mm_setzero_pd(), x));
  write(reinterpret_cast<std::uint8_t *>(out), 8, Word(0));
  auto z = _mm_add_ss(_mm_mul_ss(f, cosine), _mm_mul_ss(s, sine));
  out[2] = _mm_cvtsd_f64(_mm_cvtss_sd(_mm_setzero_pd(), z));
  return out;
}

// 0x29950 quantizes two accumulated floats, then writes current/previous
// rotations.
inline void applyRotation(GameAccessBridge *b, Word entity,
                          std::uint8_t alsoOther, std::uint8_t *image) {
  const auto q = read<float>(image, 0x2f7b64);
  if (q == 0.0f)
    return;
  const auto negative = std::bit_cast<float>(
      std::bit_cast<std::uint32_t>(q) ^ read<std::uint32_t>(image, 0x14fd40));
  auto quantize = [&](float value) {
    if (!(negative >= value || value >= q))
      return 0.0f;
    auto quotient = _mm_div_ss(_mm_set_ss(value), _mm_set_ss(q));
    return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(recovered_truncate_float_abeb0(
                                        _mm_cvtss_f32(quotient), image)),
                                    _mm_set_ss(q)));
  };
  const auto yawStep = quantize(read<float>(image, 0x2f7b58));
  write(image, 0x2f7b58,
        _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(read<float>(image, 0x2f7b58)),
                                 _mm_set_ss(yawStep))));
  const auto pitchStep = quantize(read<float>(image, 0x2f7b5c));
  write(image, 0x2f7b5c,
        _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(read<float>(image, 0x2f7b5c)),
                                 _mm_set_ss(pitchStep))));
  if (yawStep == 0.0f && pitchStep == 0.0f)
    return;
  const auto step = Word(std::bit_cast<std::uint32_t>(yawStep)) |
                    (Word(std::bit_cast<std::uint32_t>(pitchStep)) << 32);
  const auto next =
      recovered_angle_add_9de0(game_access::rotation(b, entity), step);
  game_access::setClampedRotation(b, entity, next, 0x298, 0x14f740, image);
  game_access::setClampedRotation(b, entity, next, 0x2a8, 0x14f748, image);
  if (alsoOther) {
    game_access::setRotationPair(b, entity, next, 0x8c0);
    game_access::setRotationPair(b, entity, next, 0x8b0);
  }
}
// Runtime table-backed callback 0x4bc60: strong direct call proof from
// Block_In.
inline std::int32_t blockInItemRank(std::uint32_t id) {
  switch (id) {
  case 1:
  case 2:
  case 3:
  case 20:
  case 24:
  case 45:
  case 87:
  case 159:
    return 2;
  case 4:
  case 5:
  case 17:
  case 121:
  case 162:
    return 3;
  case 49:
    return 4;
  case 35:
    return 1;
  default:
    return -1;
  }
}
// Runtime table-backed callback 0x2af70 is the concrete 0x2af50 ranking shim.
inline std::int32_t bridgeItemRank(std::uint32_t id) {
  if (id - 1u <= 86u) {
    switch (id) {
    case 1:
    case 2:
    case 3:
    case 35:
    case 45:
      return 2;
    case 5:
    case 17:
    case 20:
    case 24:
    case 87:
      return 1;
    default:
      return -1;
    }
  }
  const auto offset = id - 121u;
  return offset <= 41u && ((0x24000000001ull >> (offset & 63u)) & 1u) ? 1 : -1;
}
// 0x2ade0 scans nine slots in native order, selects an exact preferred ID or a
// strictly greater signed rank, claims the token, writes the chosen slot and
// owner.
inline void selectHotbarAction(Word frame, Word token, std::uint8_t force,
                               std::int32_t (*rank)(std::uint32_t),
                               std::uint8_t *image) {
  if (read<Word>(image, 0x2f7bb0))
    return;
  if (!force && !read<std::uint32_t>(image, 0x2f7bb8))
    return;
  auto *ctx = reinterpret_cast<const std::uint8_t *>(frame);
  auto game = [&] {
    return reinterpret_cast<GameAccessBridge *>(read<Word>(ctx, 0));
  };
  const auto inventory =
      recovered_game_inventory(game(), read<Word>(ctx, 0x28));
  const auto preferred = read<std::uint32_t>(image, 0x2f7bb8);
  const auto first =
      std::uint32_t(recovered_game_inventory_index(game(), inventory)) +
      std::uint32_t(image[0x2f7bc0]);
  const auto array = recovered_game_inventory_array(game(), inventory);
  auto *environment = game()->environment;
  std::int32_t selected = -1, best = -1;
  for (std::uint32_t n = 0; n < 9; ++n) {
    const auto raw = std::bit_cast<std::int32_t>(first + n);
    const auto slotIndex = raw % 9;
    const auto stack =
        game_access::arrayElement(reinterpret_cast<Word>(environment), array,
                                  std::bit_cast<std::uint32_t>(slotIndex));
    if (!stack)
      continue;
    const auto item = game_access::stackItemObject(game(), stack);
    if (!item)
      continue;
    const auto id = std::uint32_t(recovered_game_item_numeric_id(game(), item));
    if (preferred && id == preferred) {
      selected = slotIndex;
      break;
    }
    const auto score = rank(id);
    if (score > best) {
      best = score;
      selected = slotIndex;
    }
  }
  if (selected == -1 || !claimAction(image, token))
    return;
  game_access::selectSlot(game(), inventory,
                          std::bit_cast<std::uint32_t>(selected));
  write(image, 0x2f7bb0, token);
}

// 0x29af0 captures four key handles, then either restores each saved bit or
// remaps their signed forward/strafe direction by a rounded eight-way yaw
// sector.
inline void remapMovementKeys(GameAccessBridge *b, std::uint8_t enabled,
                              std::uint8_t *image,
                              const AngleWrapConstants *wrap) {
  const auto client = game_access::clientSingleton(b);
  if (!recovered_null_move_ready(b, client))
    return;
  const auto options = game_access::clientOptions(b, client);
  const auto forwardKey = game_access::keyAt(b, options, 2),
             backKey = game_access::keyAt(b, options, 4),
             leftKey = game_access::keyAt(b, options, 3),
             rightKey = game_access::keyAt(b, options, 5);
  if (!enabled) {
    game_access::setKeyPressed(b, forwardKey, image[0x2f7ba1] & 1u);
    game_access::setKeyPressed(b, backKey, (image[0x2f7ba1] >> 1) & 1u);
    game_access::setKeyPressed(b, leftKey, (image[0x2f7ba1] >> 2) & 1u);
    game_access::setKeyPressed(b, rightKey, (image[0x2f7ba1] >> 3) & 1u);
    return;
  }
  const auto f = game_access::keyPressed(b, forwardKey),
             back = game_access::keyPressed(b, backKey),
             left = game_access::keyPressed(b, leftKey),
             right = game_access::keyPressed(b, rightKey);
  image[0x2f7ba1] = std::uint8_t(f | (back << 1) | (left << 2) | (right << 3));
  const auto entity = game_access::clientPlayerObject(b, client);
  const auto rotation = game_access::rotation(b, entity);
  const auto difference =
      _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(game_access::floatValue(rotation)),
                               _mm_set_ss(read<float>(image, 0x2f7b70))));
  const auto yaw = recovered_wrap_angle(difference, wrap);
  const auto mask = image[0x2f7ba1];
  const int forward = (mask & 1) - ((mask >> 1) & 1),
            strafe = ((mask >> 2) & 1) - ((mask >> 3) & 1);
  std::uint16_t direction = 0;
  if (forward || strafe) {
    std::uint32_t sector;
    if (!forward)
      sector = strafe == 1 ? 2u : (strafe == -1 ? 6u : 0u);
    else if (forward == -1)
      sector = 5u - std::uint32_t(std::uint8_t(strafe + 1));
    else
      sector = strafe == 1 ? 1u : (strafe == -1 ? 7u : 0u);
    const auto divided = _mm_cvtss_f32(
        _mm_div_ss(_mm_set_ss(yaw), _mm_set_ss(read<float>(image, 0x14fd50))));
    const auto rounded = recovered_round_float_b1fb0(divided, image);
    const auto step = std::uint32_t(_mm_cvttss_si32(_mm_set_ss(rounded)));
    direction =
        read<std::uint16_t>(image, 0x14fd60 + ((step + sector) & 7u) * 2u);
  }
  const auto low = std::uint8_t(direction), high = std::uint8_t(direction >> 8);
  game_access::setKeyPressed(b, forwardKey, low == 1);
  game_access::setKeyPressed(b, backKey, low == 255);
  game_access::setKeyPressed(b, leftKey, high == 1);
  game_access::setKeyPressed(b, rightKey, high == 255);
}
// 0x29d90 transitions the retained camera state with exact byte inputs and a
// fifth packed rotation. Frame/JNI bridge words are refreshed after calls.
inline void changeRotationMode(Word frame, std::uint8_t active,
                               std::uint8_t remap, std::uint8_t useRetained,
                               Word retained, std::uint8_t *image,
                               const AngleWrapConstants *wrap) {
  auto *ctx = reinterpret_cast<const std::uint8_t *>(frame);
  auto game = [&] {
    return reinterpret_cast<GameAccessBridge *>(read<Word>(ctx, 0));
  };
  if (image[0x2f7b69] == 1) {
    remapMovementKeys(game(), 0, image, wrap);
    image[0x2f7b69] = 0;
    image[0x2f7b68] = 0;
  }
  const auto previous = image[0x2f7b90];
  if (active) {
    if (!(previous & 1u) && read<Word>(ctx, 0x28)) {
      image[0x2f7b90] = 1;
      write(image, 0x2f7b88,
            game_access::rotation(game(), read<Word>(ctx, 0x28)));
    }
    image[0x2f7b6a] = useRetained;
    write(image, 0x2f7b70, retained);
    image[0x2f7b68] = remap;
    return;
  }
  if (!(previous & 1u))
    return;
  image[0x2f7b90] = 0;
  const auto source = image[0x2f7b6a] ? 0x2f7b70u : 0x2f7b88u;
  const float yaw = read<float>(image, source);
  const auto pitchBits = read<std::uint32_t>(image, source + 4);
  const auto current = game_access::rotation(game(), read<Word>(ctx, 0x28));
  const float currentYaw = game_access::floatValue(current);
  const auto delta =
      _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(yaw), _mm_set_ss(currentYaw)));
  const auto wrapped = recovered_wrap_angle(delta, wrap);
  const auto nextYaw =
      _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(wrapped), _mm_set_ss(currentYaw)));
  const auto next =
      Word(std::bit_cast<std::uint32_t>(nextYaw)) | (Word(pitchBits) << 32);
  game_access::setClampedRotation(game(), read<Word>(ctx, 0x28), next, 0x298,
                                  0x14f740, image);
  game_access::setClampedRotation(game(), read<Word>(ctx, 0x28), next, 0x2a8,
                                  0x14f748, image);
  game_access::setRotationPair(game(), read<Word>(ctx, 0x28), next, 0x8c0);
  game_access::setRotationPair(game(), read<Word>(ctx, 0x28), next, 0x8b0);
}

// 0x4c390: cache the message endpoint before the mutable-cell window query.
// The query frame and exact captured GetActiveWindow identity are established
// in ProtectedWindowQueryStaticReview.json. Caller-owned cells remain mutable.
struct WindowInputEndpoints {
  Word (*const *messageCell)(Word, std::uint32_t, Word, Word);
  const std::uint8_t *queryEncodedCell = nullptr;
};
inline Word mouseMessage(std::uint8_t button, std::uint8_t release,
                         const WindowInputEndpoints &endpoints,
                         const window_service::Context &query) {
  const auto message = 0x8cf4u + 2u * std::uint32_t(std::uint8_t(button ^ 1u)) -
                       std::uint32_t(release);
  const auto target = *endpoints.messageCell;
  const auto window = window_service::query_103762f(query);
  return target(window, message, 0, 0);
}
// 0x28480: the event type selects a captured null-terminated callback table.
inline void dispatchEvent(Word manager, Word event) {
  const auto *owner = reinterpret_cast<const std::uint8_t *>(manager);
  const auto type =
      read<std::uint32_t>(reinterpret_cast<const std::uint8_t *>(event), 0);
  const auto table = read<Word>(owner, 0x210 + std::size_t(type) * 8);
  const auto *entry = reinterpret_cast<const Word *>(table);
  Word target = *entry++;
  while (target) {
    reinterpret_cast<void (*)(Word)>(target)(event);
    target = *entry++;
  }
}
// 0x291f0: the explicit variadic save area is caller-owned. Capture the player,
// format into shared storage, then construct and deliver a JNI text component.
inline void formattedEntityMessage(GameAccessBridge *b, const char *format,
                                   std::va_list arguments, std::uint8_t *image,
                                   FormatState &formatState) {
  const auto client = game_access::clientSingleton(b);
  const auto player = game_access::clientPlayerObject(b, client);
  if (!player)
    return;
  auto *destination = reinterpret_cast<char *>(image + 0x2f7a50);
  recovered_format_arguments(&formatState, destination, 0x100, format,
                             arguments);
  const auto text =
      game_access::newStringUtf(reinterpret_cast<Word>(b->environment),
                                reinterpret_cast<Word>(destination));
  if (!text)
    return;
  const auto component = game_access::textComponentObject(b, text);
  if (component)
    game_access::entityMessage(b, player, component);
}
} // namespace reconstruction::native_state
#endif // SLINKY_SHARE_261765C11DFE4C0891E9
