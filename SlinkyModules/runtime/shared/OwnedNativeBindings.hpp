#ifndef SLINKY_SHARE_1841AF5CF9ADE46A223B
#define SLINKY_SHARE_1841AF5CF9ADE46A223B
#include "../native/verified/Chams.hpp"
#include "../native/verified/Fast_Place_access.hpp"
#include "../native/verified/Weapons.hpp"
#include "../native/verified/module_float_distance.hpp"
#include "../native/verified/module_float_math.hpp"
#include "../native/verified/module_format.hpp"
#include "../native/verified/module_game_access.hpp"
#include "../native/verified/module_item_policy_lookup.hpp"
#include "../native/verified/module_list_storage.hpp"
#include "../native/verified/module_random.hpp"
#include "../native/verified/module_random_policy.hpp"
#include "Geometry.hpp"
#include "GaussianRandomBindings.hpp"
#include "Rounding.hpp"
#include "ScalarCeiling.hpp"
#include "SharedGameAccess.hpp"
#include "SharedNativeState.hpp"
#include "DecodedNumericService.hpp"
#include "CrtNativeBindings.hpp"
#include "Trigonometry.hpp"
#include <bit>
#include <cstddef>
#include <cstdint>
#include <emmintrin.h>
namespace reconstruction::native_binding {
using Word = std::uint64_t;
// Caller supplies the exact image-backed mutable RNG, constants and clock.
// This adapter neither initializes state nor derives defaults from
// observations.
struct WeaponContext {
  WeaponCache &cache;
  const WeaponSettings &settings;
  const ItemPolicyTable &items;
  const WeaponDependencies &endpoints;
};
struct Context {
  RandomState &random;
  const RandomConstants &scalarConstants;
  const RandomPolicyConstants &policyConstants;
  const double &clock;
  const GaussianRandomEndpoints &gaussian;
  const AngleWrapConstants &angleWrap;
  WeaponContext &weapons;
  const std::uint8_t *image;
  const AccessHelperContext &accessContext;
  const FloatDistanceConstants &distanceConstants;
  const FastPlaceAccessContext &placementAccess;
  const ListMemoryDependencies &listMemory;
  FormatState &format;
  std::uint8_t *stateImage;
  float (*singleAngular)(float, float); // exact protected 0x13cfc0 boundary
  double (*binary64Angular)(double,
                            double); // exact protected 0x13cfb0 boundary
  const native_state::WindowInputEndpoints &windowInput;
  const std::uint8_t *numericPairEncodedCell_13cfd0 = nullptr;
  const std::uint8_t *numericDirectionEncodedCell_13cfb0 = nullptr;
  const std::uint8_t *numericProjectionEncodedCell_13cfa0 = nullptr;
  const std::uint8_t *numericFloatDirectionEncodedCell_13cfc0 = nullptr;
  const std::uint8_t *numericFloatUnaryEncodedCell_13d190 = nullptr;
  const std::uint8_t *numericBinaryScalarEncodedCell_13cfe0 = nullptr;
  const crt_service::BoundServices *crt = nullptr;
};
struct Value {
  Word bits;
  bool floating;
};
inline float single(Word bits) {
  return std::bit_cast<float>(std::uint32_t(bits));
}
inline double binary64(Word bits) { return std::bit_cast<double>(bits); }
inline Word floatBits(float value) {
  return std::bit_cast<std::uint32_t>(value);
}
inline bool resolve(Context &context, Word rva, const Word *a, Value &result) {
  auto pointer = [](Word value) {
    return reinterpret_cast<void *>(std::uintptr_t(value));
  };
  auto bridge = [&]() {
    return static_cast<GameAccessBridge *>(pointer(a[0]));
  };
  result.floating = false;
  if(context.crt && context.crt->resolve(rva,a,result.bits)) return true;
  switch (rva) {
  case 0x13cfe0:
    result={floatBits(numeric_service::binaryScalar_13cfe0(
        {context.image,context.numericBinaryScalarEncodedCell_13cfe0},single(a[0]),single(a[1]))),true};
    return true;
  case 0x13cfc0:
    result = {floatBits(numeric_service::floatDirection_13cfc0(
                  {context.image, context.numericFloatDirectionEncodedCell_13cfc0},
                  single(a[0]),single(a[1]))),true};
    return true;
  case 0x13d190:
    result = {floatBits(numeric_service::floatUnary_13d190(
                  {context.image, context.numericFloatUnaryEncodedCell_13d190},single(a[0]))),true};
    return true;
  case 0x13cfa0:
    result = {std::bit_cast<Word>(numeric_service::projection_13cfa0(
                  {context.image, context.numericProjectionEncodedCell_13cfa0},
                  binary64(a[0]))), true};
    return true;
  case 0x13cfb0:
    result = {std::bit_cast<Word>(numeric_service::direction_13cfb0(
                  {context.image, context.numericDirectionEncodedCell_13cfb0},
                  binary64(a[0]), binary64(a[1]))), true};
    return true;
  case 0x13cfd0:
    result = {std::bit_cast<Word>(numeric_service::pair_13cfd0(
                  {context.image, context.numericPairEncodedCell_13cfd0},
                  binary64(a[0]), binary64(a[1]))), true};
    return true;
  case 0xa050:
    result.bits = recovered_random_bounds(single(a[0]), single(a[1]));
    return true;
  case 0xa3e0:
    result = {floatBits(recovered_random_interval(
                  &context.random, &context.scalarConstants, a[0])),
              true};
    return true;
  case 0xa460:
    result.bits = recovered_random_chance(
        &context.random, &context.scalarConstants, single(a[0]));
    return true;
  case 0xa510:
    result = {recovered_policy_smooth_bits(
                  static_cast<SmoothRandomState *>(pointer(a[0])), a[1],
                  binary64(a[2]), &context.random, &context.clock,
                  &context.policyConstants),
              true};
    return true;
  case 0xaa30:
    result.bits = recovered_policy_gate(
        static_cast<SmoothRandomState *>(pointer(a[0])), a[1], binary64(a[2]),
        &context.random, &context.clock, &context.policyConstants);
    return true;
  case 0xab00: {
    gaussian_binding::Context bound{context.image, context.distanceConstants};
    const auto endpoints = gaussian_binding::endpoints(bound);
    result = {recovered_policy_gaussian_bits(
                  static_cast<GaussianRandomState *>(pointer(a[0])),
                  &context.random, &context.policyConstants, &endpoints),
              true};
    return true;
  }
  case 0xb2050:
    result = {floatBits(recovered_logarithm_b2050(single(a[0]), context.image)),
              true};
    return true;
  case 0xb2170:
    result = {recovered_remainder_b2170(a[0], a[1]), true};
    return true;
  case 0xb2300:
    result = {
        recovered_remainder_b2300(std::uint32_t(a[0]), std::uint32_t(a[1])),
        true};
    return true;
  case 0xa210:
    result = {floatBits(recovered_wrap_angle(single(a[0]), &context.angleWrap)),
              true};
    return true;
  case 0xa1f0:
    result = {floatBits(recovered_float_clamp_a1f0(single(a[0]), single(a[1]),
                                                   single(a[2]))),
              true};
    return true;
  case 0xa2b0:
    result = {floatBits(recovered_scalar_lerp_a2b0(single(a[0]), single(a[1]),
                                                   single(a[2]))),
              true};
    return true;
  case 0xa2d0:
    result = {std::bit_cast<Word>(recovered_scalar_lerp_a2d0(
                  binary64(a[0]), binary64(a[1]), binary64(a[2]))),
              true};
    return true;
  case 0x9e60:
    result.bits = recovered_angle_scale_9e60(a[0], single(a[1]));
    return true;
  case 0x9e90:
    result.bits = recovered_angle_lerp_9e90(a[0], a[1], single(a[2]));
    return true;
  case 0x9400:
    result.bits = std::uintptr_t(
        recovered_geometry_add_9400(static_cast<double *>(pointer(a[0])),
                                    static_cast<double *>(pointer(a[1])),
                                    static_cast<double *>(pointer(a[2]))));
    return true;
  case 0x94b0:
    result = {std::bit_cast<Word>(recovered_vector_distance_squared(
                  static_cast<double *>(pointer(a[0])),
                  static_cast<double *>(pointer(a[1])))),
              true};
    return true;
  case 0x94f0:
    result = {std::bit_cast<Word>(recovered_vector_distance_94f0(
                  static_cast<double *>(pointer(a[0])),
                  static_cast<double *>(pointer(a[1])))),
              true};
    return true;
  case 0x96b0:
    result.bits = std::uintptr_t(recovered_geometry_pair_96b0(
        pointer(a[0]), pointer(a[1]), pointer(a[2])));
    return true;
  case 0x97d0:
    result.bits = recovered_geometry_intersects_97d0(
        static_cast<double *>(pointer(a[0])),
        static_cast<double *>(pointer(a[1])));
    return true;
  case 0x9880:
    result.bits = std::uintptr_t(
        recovered_box_clamp_9880(static_cast<double *>(pointer(a[0])),
                                 static_cast<double *>(pointer(a[1])),
                                 static_cast<double *>(pointer(a[2]))));
    return true;
  // These supplied typed helpers use GameAccessBridge's exact metadata/env
  // words.
  case 0x239d0:
    result.bits =
        std::uint32_t(recovered_game_last_attacker_time(bridge(), a[1]));
    return true;
  case 0x23f40:
    result.bits = recovered_game_inventory(bridge(), a[1]);
    return true;
  case 0x25a60:
    result.bits = std::uint32_t(recovered_game_inventory_index(bridge(), a[1]));
    return true;
  case 0x25ab0:
    result.bits = recovered_game_inventory_array(bridge(), a[1]);
    return true;
  case 0x25c50:
    result.bits = std::uint32_t(recovered_game_item_numeric_id(bridge(), a[1]));
    return true;
  case 0x28a50:
    result.bits = recovered_game_item_object(bridge(), a[1]);
    return true;
  case 0x23690:
    result.bits = recovered_game_sprinting(bridge(), a[1]);
    return true;
  case 0x23f90:
    result.bits = recovered_game_using_item(bridge(), a[1]);
    return true;
  case 0x37e50:
    result.bits = recovered_weapon_cache(
        bridge(), a[1], static_cast<std::uint32_t *>(pointer(a[2])),
        &context.weapons.cache, &context.weapons.settings,
        &context.weapons.items, &context.weapons.endpoints);
    return true;
  case 0x37f60:
    result.bits =
        recovered_weapon_groups(bridge(), a[1], &context.weapons.endpoints);
    return true;
  case 0x38040:
    result.bits = recovered_weapon_allowed(
        bridge(), a[1], &context.weapons.settings, &context.weapons.items,
        &context.weapons.endpoints);
    return true;
  case 0x380b0:
    result.bits = recovered_weapon_cached_query(
        bridge(), a[1], &context.weapons.cache, &context.weapons.settings,
        &context.weapons.items, &context.weapons.endpoints);
    return true;
  case 0x380c0:
    result.bits = recovered_weapon_select(
        static_cast<GameAccessBridge *const *>(pointer(a[0])), a[1],
        &context.weapons.settings, &context.weapons.items,
        &context.weapons.endpoints);
    return true;
  case 0x22c70:
    result.bits = game_access::playerObject(bridge(), a[1]);
    return true;
  case 0x22c90:
    result.bits = game_access::currentScreen(bridge(), a[1]);
    return true;
  case 0x22cf0:
    result.bits = game_access::clientOptions(bridge(), a[1]);
    return true;
  case 0x23020:
    result.bits = game_access::positionModeZero(bridge());
    return true;
  case 0x23030:
    result.bits = game_access::position(
        a[0], static_cast<GameAccessBridge *>(pointer(a[1])), a[2]);
    return true;
  case 0x230d0:
    result.bits = game_access::previousPosition(
        a[0], static_cast<GameAccessBridge *>(pointer(a[1])), a[2]);
    return true;
  case 0x24160:
    result.bits = game_access::serverPosition(
        a[0], static_cast<GameAccessBridge *>(pointer(a[1])), a[2]);
    return true;
  case 0x253e0:
    game_access::setKeyPressCount(bridge(), a[1], std::uint32_t(a[2]));
    result.bits = 0;
    return true;
  case 0x42c30:
    result.bits = native_state::timerRangeFrozen(context.stateImage);
    return true;
  case 0x23170:
    result.bits = game_access::rotation(bridge(), a[1]);
    return true;
  case 0x23550:
    result.bits = game_access::velocity(
        a[0], static_cast<GameAccessBridge *>(pointer(a[1])), a[2]);
    return true;
  case 0x235f0:
    game_access::setVelocity(bridge(), a[1],
                             static_cast<const double *>(pointer(a[2])));
    result.bits = 0;
    return true;
  case 0x23670:
    result.bits = game_access::boundingBoxObject(bridge(), a[1]);
    return true;
  case 0x23720:
    result.bits = std::uint32_t(game_access::entityId(bridge(), a[1]));
    return true;
  case 0x23740:
    result.bits = game_access::uuidObject(bridge(), a[1]);
    return true;
  case 0x23760:
    result.bits = std::uint32_t(game_access::ticksExisted(bridge(), a[1]));
    return true;
  case 0x23780:
    result.bits = game_access::onGround(bridge(), a[1]);
    return true;
  case 0x237e0:
    result = {floatBits(game_access::entityFloat300(bridge(), a[1])), true};
    return true;
  case 0x23990:
    result.bits = game_access::positionObject(bridge(), a[1], context.image);
    return true;
  case 0x239f0:
    result.bits = std::uint32_t(game_access::hurtTime(bridge(), a[1]));
    return true;
  case 0x23a40:
    result = {floatBits(game_access::health(bridge(), a[1], context.image)),
              true};
    return true;
  case 0x23ac0:
    result = {floatBits(game_access::forwardInput(bridge(), a[1])), true};
    return true;
  case 0x23ae0:
    result = {floatBits(game_access::strafeInput(bridge(), a[1])), true};
    return true;
  case 0x23b40:
    result = {floatBits(game_access::movementSpeed(bridge(), a[1])), true};
    return true;
  case 0x23f00:
    result.bits = game_access::livingInstance(bridge(), a[1]);
    return true;
  case 0x23f60:
    result.bits = game_access::invisibleToPlayer(bridge(), a[1], a[2]);
    return true;
  case 0x24020:
    game_access::setInteger5a8(bridge(), a[1], std::uint32_t(a[2]));
    result.bits = 0;
    return true;
  case 0x240a0:
    result.bits = game_access::sleeping(bridge(), a[1]);
    return true;
  case 0x24120:
    result.bits = game_access::remotePlayerInstance(bridge(), a[1]);
    return true;
  case 0x24220:
    result = {std::bit_cast<Word>(game_access::field898(bridge(), a[1])), true};
    return true;
  case 0x24280:
    result.bits = std::uint32_t(game_access::blockNumericId(bridge(), a[1]));
    return true;
  case 0x242c0:
    result.bits = game_access::blockPositionObject(
        bridge(), std::uint32_t(a[1]), std::uint32_t(a[2]),
        std::uint32_t(a[3]));
    return true;
  case 0x95c0:
    result.bits = std::uintptr_t(recovered_vector_adjust_95c0(
        static_cast<double *>(pointer(a[0])),
        static_cast<const double *>(pointer(a[1])), context.image));
    return true;
  case 0x9590:
    result.bits = std::uintptr_t(recovered_vector_y_offset_9590(
        static_cast<double *>(pointer(a[0])),
        static_cast<const double *>(pointer(a[1])), context.image));
    return true;
  case 0x9de0:
    result.bits = recovered_angle_add_9de0(a[0], a[1]);
    return true;
  case 0x9e20:
    result.bits = recovered_angle_subtract_9e20(a[0], a[1]);
    return true;
  case 0x9ee0:
    result = {
        recovered_packed_float_distance(a[0], a[1], &context.distanceConstants),
        true};
    return true;
  case 0x22e10:
    result.bits =
        recovered_access_helper(bridge(), 0x22e10, a[1], a[2],
                                context.accessContext.caller_frame_token);
    return true;
  case 0x24b50:
    result.bits =
        recovered_access_helper(bridge(), 0x24b50, a[1], a[2],
                                context.accessContext.caller_frame_token);
    return true;
  case 0x22eb0:
    result.bits =
        recovered_access_helper(bridge(), 0x22eb0, a[1], a[2],
                                context.accessContext.caller_frame_token);
    return true;
  case 0x23bb0:
    result.bits =
        recovered_access_helper(bridge(), 0x23bb0, a[1], a[2],
                                context.accessContext.caller_frame_token);
    return true;
  case 0x24f90:
    result.bits =
        recovered_access_helper(bridge(), 0x24f90, a[1], a[2],
                                context.accessContext.caller_frame_token);
    return true;
  case 0x25430:
    result.bits =
        recovered_access_helper(bridge(), 0x25430, a[1], a[2],
                                context.accessContext.caller_frame_token);
    return true;
  case 0x25490:
    result.bits =
        recovered_access_helper(bridge(), 0x25490, a[1], a[2],
                                context.accessContext.caller_frame_token);
    return true;
  case 0x25460:
    result.bits =
        recovered_access_helper(bridge(), 0x25460, a[1], a[2],
                                context.accessContext.caller_frame_token);
    return true;
  case 0x23c10:
    result.bits =
        recovered_access_helper(bridge(), 0x23c10, a[1], a[2],
                                context.accessContext.caller_frame_token);
    return true;
  case 0x27960:
    result.bits =
        recovered_access_helper(bridge(), 0x27960, a[1], a[2],
                                context.accessContext.caller_frame_token);
    return true;
  case 0x24600:
    result.bits = game_access::worldPlayers(bridge(), a[1]);
    return true;
  case 0x24bf0:
    result.bits = game_access::hitVectorObject(bridge(), a[1]);
    return true;
  case 0x24e30:
    result.bits = game_access::hitEntityObject(bridge(), a[1]);
    return true;
  case 0x24e50:
    result.bits = std::uint32_t(game_access::listSize(bridge(), a[1]));
    return true;
  case 0x25410:
    result.bits = std::uint32_t(game_access::keyCode(bridge(), a[1]));
    return true;
  case 0x259a0:
    result = {floatBits(game_access::renderPartialTicks(bridge(), a[1])), true};
    return true;
  case 0x25ad0:
    result.bits = game_access::inventoryContainerObject(bridge(), a[1]);
    return true;
  case 0x25b60:
    result.bits = game_access::containerObject(bridge(), a[1]);
    return true;
  case 0x25d10:
    result.bits = game_access::stackItemObject(bridge(), a[1]);
    return true;
  case 0x25d70:
    result.bits = std::uint32_t(game_access::stackCount(bridge(), a[1]));
    return true;
  case 0x25dc0:
    result.bits = std::uint32_t(game_access::stackDamage(bridge(), a[1]));
    return true;
  case 0x25de0:
    result.bits = game_access::stackTagList(bridge(), a[1]);
    return true;
  case 0x25e10:
    result.bits = std::uint32_t(game_access::stackMaximumCount(bridge(), a[1]));
    return true;
  case 0x26190:
    result.bits = std::uint32_t(game_access::containerWindowId(bridge(), a[1]));
    return true;
  case 0x261b0:
    result.bits = game_access::slotItemObject(bridge(), a[1]);
    return true;
  case 0x266f0:
    result.bits = std::uint32_t(game_access::packetEntityId(bridge(), a[1]));
    return true;
  case 0x26b90:
    result = {floatBits(game_access::packetFloatA50(bridge(), a[1])), true};
    return true;
  case 0x26c30:
    result = {floatBits(game_access::packetFloatA60(bridge(), a[1])), true};
    return true;
  case 0x27d90:
    result.bits = game_access::uuidLeastWord(bridge(), a[1]);
    return true;
  case 0x27dc0:
    result.bits = game_access::uuidMostWord(bridge(), a[1]);
    return true;
  case 0x27f10:
    result.bits = std::uint32_t(game_access::tagListCount(bridge(), a[1]));
    return true;
  case 0x24e80:
    result.bits = game_access::listElement(bridge(), a[1], std::uint32_t(a[2]));
    return true;
  case 0x26140:
    result.bits =
        game_access::inventoryStack(bridge(), a[1], std::uint32_t(a[2]));
    return true;
  case 0x27f40:
    result.bits =
        game_access::tagListElement(bridge(), a[1], std::uint32_t(a[2]));
    return true;
  case 0x266b0:
    result.bits = game_access::entityVelocityPacket(bridge(), a[1]);
    return true;
  case 0x26b10:
    result.bits = game_access::packetClassA40(bridge(), a[1]);
    return true;
  case 0x26b50:
    result.bits = game_access::packetClassA48(bridge(), a[1]);
    return true;
  case 0x25030:
    result.bits = game_access::keyAt(bridge(), a[1], 7);
    return true;
  case 0x25080:
    result.bits = game_access::keyAt(bridge(), a[1], 6);
    return true;
  case 0x250d0:
    result.bits = game_access::keyAt(bridge(), a[1], 2);
    return true;
  case 0x25120:
    result.bits = game_access::keyAt(bridge(), a[1], 4);
    return true;
  case 0x25170:
    result.bits = game_access::keyAt(bridge(), a[1], 3);
    return true;
  case 0x251c0:
    result.bits = game_access::keyAt(bridge(), a[1], 5);
    return true;
  case 0x25270:
    result.bits = game_access::keyAt(bridge(), a[1], 0);
    return true;
  case 0x24fe0:
    result.bits = game_access::versionedKeyAt(bridge(), a[1], 9);
    return true;
  case 0x252c0:
    result.bits = game_access::versionedKeyAt(bridge(), a[1], 10);
    return true;
  case 0x25380:
    game_access::incrementPresses(bridge(), a[1]);
    result.bits = 0;
    return true;
  case 0x25540:
    result.bits = game_access::vectorObjectValues(
        a[0], static_cast<GameAccessBridge *>(pointer(a[1])), a[2]);
    return true;
  case 0x25640:
    result.bits = game_access::boxObjectValues(
        a[0], static_cast<GameAccessBridge *>(pointer(a[1])), a[2]);
    return true;
  case 0x25a80:
    game_access::selectSlot(bridge(), a[1], std::uint32_t(a[2]));
    result.bits = 0;
    return true;
  case 0x25b80:
    result.bits = game_access::inventoryScreen(bridge(), a[1]);
    return true;
  case 0x25be0:
    game_access::inventoryClick(bridge(), a[1], std::uint32_t(a[2]),
                                std::uint32_t(a[3]), std::uint32_t(a[4]));
    result.bits = 0;
    return true;
  case 0x25af0:
    game_access::screenActionCb0(bridge(), a[1], std::uint16_t(a[2]),
                                 std::uint32_t(a[3]));
    result.bits = 0;
    return true;
  case 0x25d40:
    result = {floatBits(game_access::blockEfficiency(bridge(), a[1], a[2])),
              true};
    return true;
  case 0x25e40:
    result.bits = game_access::stackCompare(bridge(), a[1], a[2]);
    return true;
  case 0x25e80:
    result.bits = game_access::stackFlag(bridge(), a[1]);
    return true;
  case 0x27f70:
    result.bits = game_access::tagShortEax(bridge(), a[1], a[2]);
    return true;
  case 0xb2920:
    result = {floatBits(recovered_ceiling_float_b2920(single(a[0]), context.image)), true};
    return true;
  case 0xb1cf0:
    result = {floatBits(recovered_sine_b1cf0(single(a[0]), context.image)),
              true};
    return true;
  case 0xb3590:
    result = {floatBits(recovered_cosine_b3590(single(a[0]), context.image)),
              true};
    return true;
  case 0xb29b0:
    result = {std::bit_cast<Word>(recovered_floor_binary64_b29b0(
                  binary64(a[0]), context.image)),
              true};
    return true;
  case 0xb1fb0:
    result = {
        floatBits(recovered_round_float_b1fb0(single(a[0]), context.image)),
        true};
    return true;
  case 0x24d80:
    recovered_fast_place_adjacent_position(
        static_cast<PlacementPosition *>(pointer(a[0])),
        static_cast<GameAccessBridge *>(pointer(a[1])), a[2],
        &context.placementAccess);
    result.bits = a[0];
    return true;
  case 0x2ac60:
    result.bits = recovered_item_policy_lookup(
        static_cast<const ItemPolicyTable *>(pointer(a[0])),
        std::uint32_t(a[1]));
    return true;
  case 0x2ace0:
    result.bits = recovered_chams_flags(bridge(), a[1], std::uint32_t(a[2]));
    return true;
  case 0x22e60:
    result.bits = recovered_null_move_ready(bridge(), a[1]);
    return true;
  case 0xab710:
    result.bits = recovered_format(
        &context.format, static_cast<char *>(pointer(a[0])), std::size_t(a[1]),
        static_cast<const char *>(pointer(a[2])), a[3], a[4]);
    return true;
  case 0x800000c0:
    result.bits = game_access::sameObject(a[0], a[1], a[2], a[5]);
    return true;
  case 0x80000520:
    result.bits = game_access::stringLength(a[0], a[1], a[5]);
    return true;
  case 0x80000700:
    result.bits = game_access::acquireCriticalString(a[0], a[1], a[2], a[5]);
    return true;
  case 0x80000708:
    game_access::releaseCriticalString(a[0], a[1], a[2], a[5]);
    result.bits = 0;
    return true;
  case 0x80000538:
    result.bits = game_access::newStringUtf(a[0], a[1]);
    return true;
  case 0x80000568:
    result.bits = game_access::arrayElement(a[0], a[1], std::uint32_t(a[2]));
    return true;
  case 0x70000000:
    result.bits = game_access::capturedObjectMethod(a[0], a[1], a[2], a[5]);
    return true;
  case 0x28ac0:
    result.bits = game_access::heldItemCanBlock(bridge(), a[1]);
    return true;
  case 0x28b00:
    result.bits = game_access::itemIsBlock(bridge(), a[1]);
    return true;
  case 0x29080:
    result.bits = game_access::attackInput(a[0]);
    return true;
  case 0x24b90:
    result.bits = game_access::hitFacing(bridge(), a[1]);
    return true;
  case 0x24c10:
    result.bits = game_access::hitBlockPosition(
        a[0], static_cast<GameAccessBridge *>(pointer(a[1])), a[2]);
    return true;
  case 0x24ce0:
    result.bits = game_access::integerHitPosition(
        a[0], static_cast<GameAccessBridge *>(pointer(a[1])), a[2]);
    return true;
  case 0x2ad20:
    game_access::changeEntityFlags(bridge(), a[1], std::uint32_t(a[2]), false);
    result.bits = 0;
    return true;
  case 0x2ad80:
    game_access::changeEntityFlags(bridge(), a[1], std::uint32_t(a[2]), true);
    result.bits = 0;
    return true;
  case 0x29800:
    result.bits =
        native_state::claimRotation(context.stateImage, std::uint32_t(a[0]));
    return true;
  case 0x29820:
    native_state::publishRotationDelta(context.stateImage, a[0]);
    result.bits = 0;
    return true;
  case 0x29850:
    result.bits = native_state::rotationOffset(context.stateImage);
    return true;
  case 0x29f80:
    result.bits = native_state::rotationStateAvailable(context.stateImage);
    return true;
  case 0x29ff0:
    result.bits = native_state::retainedRotation(context.stateImage);
    return true;
  case 0x2aa80:
    result.bits = native_state::claimAction(context.stateImage, a[0]);
    return true;
  case 0x2aab0:
    native_state::releaseAction(context.stateImage, a[0]);
    result.bits = 0;
    return true;
  case 0x2aad0:
    result.bits = native_state::inventoryGrid(std::uint32_t(a[0]));
    return true;
  case 0x284f0:
    result.bits =
        native_state::scheduleModuleAction(a[0], a[1], std::uint8_t(a[2]));
    return true;
  case 0x9f10:
    result = {
        floatBits(native_state::gridBearingDecoded(a[0], a[1],
            {context.image,context.numericFloatDirectionEncodedCell_13cfc0})),
        true};
    return true;
  case 0x9f80:
    result.bits =
        native_state::targetAnglesDecoded(static_cast<const double *>(pointer(a[0])),
                                   static_cast<const double *>(pointer(a[1])),
                                   context.image,{context.image,context.numericDirectionEncodedCell_13cfb0});
    return true;
  case 0x29290:
    result.bits = std::uintptr_t(native_state::movementVector(
        static_cast<double *>(pointer(a[0])), a[1], single(a[2]), single(a[3]),
        single(a[4]), context.image));
    return true;
  case 0x24690:
    result.bits =
        game_access::worldBlockAt(bridge(), a[1], std::uint32_t(a[2]),
                                  std::uint32_t(a[3]), std::uint32_t(a[4]));
    return true;
  case 0x24720:
    result.bits =
        game_access::cachedWorldBlock(bridge(), a[1], a[2], std::uint32_t(a[3]),
                                      std::uint32_t(a[4]), std::uint32_t(a[5]));
    return true;
  case 0x29950:
    native_state::applyRotation(bridge(), a[1], std::uint8_t(a[2]),
                                context.stateImage);
    result.bits = 0;
    return true;
  case 0x2ade0:
    native_state::selectHotbarAction(
        a[0], a[1], std::uint8_t(a[2]),
        reinterpret_cast<std::int32_t (*)(std::uint32_t)>(a[3]),
        context.stateImage);
    result.bits = 0;
    return true;
  case 0x2af50:
    native_state::selectHotbarAction(a[0], a[1], std::uint8_t(a[2]),
                                     native_state::bridgeItemRank,
                                     context.stateImage);
    result.bits = 0;
    return true;
  case 0x4bc60:
    result.bits =
        std::uint32_t(native_state::blockInItemRank(std::uint32_t(a[0])));
    return true;
  case 0x29d90:
    native_state::changeRotationMode(
        a[0], std::uint8_t(a[1]), std::uint8_t(a[2]), std::uint8_t(a[3]), a[4],
        context.stateImage, &context.angleWrap);
    result.bits = 0;
    return true;
  case 0x29af0:
    native_state::remapMovementKeys(bridge(), std::uint8_t(a[1]),
                                    context.stateImage, &context.angleWrap);
    result.bits = 0;
    return true;
  case 0x4c390:
    result.bits = native_state::mouseMessage(
        std::uint8_t(a[0]), std::uint8_t(a[1]), context.windowInput,
        {context.image,context.windowInput.queryEncodedCell});
    return true;
  case 0x28480:
    native_state::dispatchEvent(a[0], a[1]);
    result.bits = 0;
    return true;
  case 0x291f0:
    native_state::formattedEntityMessage(
        bridge(), static_cast<const char *>(pointer(a[1])),
        reinterpret_cast<char *>(const_cast<Word *>(a + 2)), context.stateImage,
        context.format);
    result.bits = 0;
    return true;
  case 0x22c00:
    result.bits = game_access::clientSingleton(bridge());
    return true;
  case 0x22c30:
    result.bits = game_access::clientPlayerObject(bridge(), a[1]);
    return true;
  case 0xabeb0:
    result = {
        floatBits(recovered_truncate_float_abeb0(single(a[0]), context.image)),
        true};
    return true;
  case 0x2af70:
    result.bits =
        std::uint32_t(native_state::bridgeItemRank(std::uint32_t(a[0])));
    return true;
  case 0xab770:
    result.bits = recovered_format_arguments(
        &context.format, static_cast<char *>(pointer(a[0])), std::size_t(a[1]),
        static_cast<const char *>(pointer(a[2])),
        static_cast<char *>(pointer(a[3])));
    return true;
  // BEGIN REVIEWED RENDER GAME ADAPTER
  case 0x27250:
    result = {floatBits(game_access::field7c8(bridge(), a[1])), true};
    return true;
  case 0x237b0:
    result.bits = game_access::entityDead(bridge(), a[1]);
    return true;
  case 0x24640:
    result.bits = game_access::worldObject370(bridge(), a[1]);
    return true;
  case 0x244f0:
    result.bits = game_access::object760(bridge(), a[1]);
    return true;
  case 0x272a0:
    result.bits = game_access::object7d0(bridge(), a[1]);
    return true;
  case 0x22dd0:
    result.bits = game_access::clientObject1e8(bridge(), a[1]);
    return true;
  case 0x27b50:
    result = {floatBits(game_access::fieldAb0(bridge(), a[1])), true};
    return true;
  case 0x22d90:
    result.bits = game_access::clientObject210(bridge(), a[1]);
    return true;
  case 0x22db0:
    result.bits = game_access::clientObject208(bridge(), a[1]);
    return true;
  case 0x25310:
    result.bits = std::uint32_t(game_access::integer3c0(bridge(), a[1]));
    return true;
  case 0x23800:
    result.bits = game_access::objectMethod240(bridge(), a[1]);
    return true;
  case 0x26090:
    result.bits = game_access::objectMethod6a8(bridge(), a[1]);
    return true;
  case 0x23830:
    result.bits = game_access::objectMethod248(bridge(), a[1]);
    return true;
  case 0x27200:
    result = {floatBits(game_access::field7c0(bridge(), a[1])), true};
    return true;
  case 0x24620:
    result.bits = game_access::worldObject368(bridge(), a[1]);
    return true;
  case 0x27fa0:
    result.bits = game_access::flagC28(bridge(), a[1]);
    return true;
  case 0x249f0:
    result.bits = game_access::objectB00(bridge(), a[1]);
    return true;
  case 0x24a50:
    result.bits = game_access::objectB20(bridge(), a[1]);
    return true;
  case 0x24ab0:
    result.bits = game_access::objectB38(bridge(), a[1]);
    return true;
  case 0x24a10:
    result.bits = std::uint32_t(game_access::integerB08(bridge(), a[1]));
    return true;
  case 0x24a30:
    result.bits = std::uint32_t(game_access::integerB10(bridge(), a[1]));
    return true;
  case 0x26060:
    result.bits = std::uint32_t(game_access::integerMethodF8(bridge(), a[1]));
    return true;
  case 0x236f0:
    result.bits = game_access::flagMethod238(bridge(), a[1]);
    return true;
  case 0x23fc0:
    result.bits = std::uint32_t(game_access::integer5a8(bridge(), a[1]));
    return true;
  case 0x23900:
    result.bits = game_access::flagMethod260(bridge(), a[1]);
    return true;
  case 0x25bb0:
    result.bits = game_access::classPredicateCb8(bridge(), a[1]);
    return true;
  case 0x25c30:
    result.bits = game_access::objectCc0(bridge(), a[1]);
    return true;
  case 0x26220:
    result.bits = game_access::objectCd0(bridge(), a[1]);
    return true;
  case 0x27760:
    game_access::staticAction9c0(bridge());
    result.bits = 0;
    return true;
  case 0x27820:
    game_access::staticAction9e0(bridge());
    result.bits = 0;
    return true;
  case 0x277f0:
    game_access::staticAction9d8(bridge());
    result.bits = 0;
    return true;
  case 0x27730:
    game_access::staticAction9b8(bridge());
    result.bits = 0;
    return true;
  case 0x27c90:
    game_access::staticActionAd8(bridge());
    result.bits = 0;
    return true;
  case 0x27cc0:
    game_access::staticActionAe0(bridge());
    result.bits = 0;
    return true;
  case 0x27790:
    game_access::staticAction9e8(bridge());
    result.bits = 0;
    return true;
  case 0x27880:
    game_access::staticActionA10(bridge());
    result.bits = 0;
    return true;
  case 0x271d0:
    result.bits = game_access::staticObject7b8(bridge());
    return true;
  case 0x22d40:
    result.bits = game_access::versionedClientObject1f0(bridge(), a[1]);
    return true;
  case 0x23fe0:
    result = {floatBits(game_access::finiteMethod590(bridge(), a[1])), true};
    return true;
  case 0x23a80:
    result = {
        floatBits(game_access::finiteMethod528(bridge(), a[1], context.image)),
        true};
    return true;
  case 0x24510:
    result.bits = game_access::integerVector760(
        a[0], static_cast<GameAccessBridge *>(pointer(a[1])), a[2]);
    return true;
  case 0x27b70:
    game_access::setFieldAb0(bridge(), a[1], single(a[2]));
    result.bits = 0;
    return true;
  case 0x273e0:
    result = {
        floatBits(game_access::floatMethod908(bridge(), a[1], single(a[2]))),
        true};
    return true;
  case 0x278f0:
    game_access::staticFourSinglesA20(bridge(), single(a[1]), single(a[2]),
                                      single(a[3]), single(a[4]));
    result.bits = 0;
    return true;
  case 0x27590:
    result.bits = std::uint32_t(game_access::fontDraw9a8(
        bridge(), a[1], a[2], single(a[3]), single(a[4]), std::uint32_t(a[5]),
        std::uint8_t(a[6]), context.image));
    return true;
  case 0x24050:
    result.bits =
        game_access::objectMethod598(bridge(), a[1], std::uint32_t(a[2]));
    return true;
  case 0x27ba0:
    game_access::methodAc0(bridge(), a[1], a[2], a[3], a[4],
                           std::uint32_t(a[5]), std::uint32_t(a[6]));
    result.bits = 0;
    return true;
  case 0x27c10:
    game_access::methodAc8(bridge(), a[1], a[2], a[3], a[4],
                           std::uint32_t(a[5]), std::uint32_t(a[6]), a[7]);
    result.bits = 0;
    return true;
  case 0x278b0:
    game_access::staticIntegersA18(bridge(), std::uint32_t(a[1]),
                                   std::uint32_t(a[2]));
    result.bits = 0;
    return true;
  case 0x27b20:
    result.bits = game_access::newObjectAb8(bridge());
    return true;
  case 0x27560:
    result.bits =
        std::uint32_t(game_access::fontMeasure9a0(bridge(), a[1], a[2]));
    return true;
  case 0x23860:
    result.bits = std::uint32_t(game_access::staticIntegerAf0(bridge(), a[1]));
    return true;
  case 0x248f0:
    result.bits = game_access::indexedObject340(
        bridge(), a[1], std::uint32_t(a[2]), std::uint32_t(a[3]));
    return true;
  case 0x24990:
    result.bits = game_access::retainedObject378(bridge(), a[1]);
    return true;
  case 0x254f0:
    result.bits = game_access::newVector658(
        bridge(), static_cast<const double *>(pointer(a[1])));
    return true;
  case 0x24860:
    result.bits = game_access::rayMethod330(
        bridge(), a[1], a[2], a[3], std::uint8_t(a[4]), std::uint8_t(a[5]),
        std::uint8_t(a[6]));
    return true;
  case 0x25840:
    result.bits = game_access::staticFlag90(bridge());
    return true;
  case 0x25880:
    game_access::staticByte98(bridge(), std::uint8_t(a[1]));
    result.bits = 0;
    return true;
  case 0x27a60:
    result.bits = std::uint32_t(game_access::staticIntegerD0(bridge()));
    return true;
  case 0x27a90:
    result.bits = std::uint32_t(game_access::staticIntegerD8(bridge()));
    return true;
  case 0x25940:
    game_access::staticIntegersB0(bridge(), std::uint32_t(a[1]),
                                  std::uint32_t(a[2]));
    result.bits = 0;
    return true;
  case 0x27fc0:
    result.bits = game_access::staticObjectCe0(bridge(), a[1]);
    return true;
  case 0x261e0:
    result.bits = game_access::retainedClassCc8(bridge(), a[1]);
    return true;
  case 0x260c0:
    result.bits = game_access::textComponentObject(bridge(), a[1]);
    return true;
  case 0x23e30:
    game_access::entityMessage(bridge(), a[1], a[2]);
    result.bits = 0;
    return true;
  // END REVIEWED RENDER GAME ADAPTER

// BEGIN REVIEWED REMAINING GAME ADAPTER
  case 0x22d10: result.bits=game_access::clientMethod158(bridge(),a[1]); return true;
  case 0x22df0: result.bits=game_access::clientObject218(bridge(),a[1]); return true;
  case 0x22e90: result.bits=std::uint32_t(game_access::clientInteger1b8(bridge(),a[1])); return true;
  case 0x23930: result.bits=game_access::entityObject308(bridge(),a[1]); return true;
  case 0x24080: result.bits=game_access::entityObject5b0(bridge(),a[1]); return true;
  case 0x259f0: result={floatBits(game_access::single398(bridge(),a[1])),true}; return true;
  case 0x25eb0: result.bits=game_access::object690(bridge(),a[1]); return true;
  case 0x25ed0: result.bits=game_access::object698(bridge(),a[1]); return true;
  case 0x26010: result.bits=game_access::objectC48(bridge(),a[1]); return true;
  case 0x26030: result.bits=game_access::objectMethodC50(bridge(),a[1]); return true;
  case 0x26170: result.bits=game_access::objectCa0(bridge(),a[1]); return true;
  case 0x27d30: result.bits=game_access::objectMethodB50(bridge(),a[1]); return true;
  case 0x27df0: result={floatBits(game_access::singleBc8(bridge(),a[1])),true}; return true;
  case 0x27e90: result.bits=game_access::byteBd8(bridge(),a[1]); return true;
  case 0x263c0: result.bits=game_access::flag718(bridge(),a[1]); return true;
  case 0x271a0: result.bits=std::uint32_t(game_access::integerMethod148(bridge(),a[1])); return true;
  case 0x240d0: result={floatBits(game_access::single5c0(bridge(),a[1])),true}; return true;
  case 0x23a10: game_access::setInteger550(bridge(),a[1],std::uint32_t(a[2])); result.bits=0; return true;
  case 0x23b80: game_access::setInteger570(bridge(),a[1],std::uint32_t(a[2])); result.bits=0; return true;
  case 0x25330: game_access::setInteger3c0(bridge(),a[1],std::uint32_t(a[2])); result.bits=0; return true;
  case 0x279c0: game_access::setIntegerC38(bridge(),a[1],std::uint32_t(a[2])); result.bits=0; return true;
  case 0x27e60: game_access::setIntegerBd0(bridge(),a[1],std::uint32_t(a[2])); result.bits=0; return true;
  case 0x23e90: game_access::setSingle8d8(bridge(),a[1],single(a[2])); result.bits=0; return true;
  case 0x27e10: game_access::setSingleBc8(bridge(),a[1],single(a[2])); result.bits=0; return true;
  case 0x264f0: result.bits=game_access::retainedClass738(bridge(),a[1]); return true;
  case 0x26cc0: result.bits=game_access::retainedClassA70(bridge(),a[1]); return true;
  case 0x26ec0: result.bits=game_access::retainedClassBe8(bridge(),a[1]); return true;
  case 0x26f00: result.bits=game_access::retainedClassC60(bridge(),a[1]); return true;
  case 0x26ff0: result.bits=game_access::retainedClassC88(bridge(),a[1]); return true;
  case 0x27160: result.bits=game_access::retainedClassD08(bridge(),a[1]); return true;
  case 0x27cf0: result.bits=game_access::retainedClassB48(bridge(),a[1]); return true;
  case 0x257a0: result.bits=game_access::staticFlag70(bridge()); return true;
  case 0x26f40: result.bits=game_access::staticObjectC80(bridge()); return true;
  case 0x26f70: result.bits=game_access::newObjectC70(bridge(),a[1]); return true;
  case 0x27030: result.bits=game_access::newIntegerObjectC90(bridge(),std::uint32_t(a[1])); return true;
  case 0x274c0: result.bits=game_access::byteMethod978(bridge(),a[1],a[2]); return true;
  case 0x24f40: result.bits=game_access::objectMethod58(bridge(),a[1],a[2]); return true;
  case 0x27eb0: game_access::setBooleanBd8(bridge(),a[1],std::uint32_t(a[2])); result.bits=0; return true;
  case 0x25f80: game_access::objectAction6f8(bridge(),a[1],a[2]); result.bits=0; return true;
  case 0x26fb0: result.bits=std::uint32_t(game_access::objectIntegerC68(bridge(),a[1])); return true;
  case 0x2acb0: result.bits=game_access::taggedValue5c0(bridge(),a[1]); return true;
  case 0x29f90: result.bits=game_access::observedWord2f7b88(context.stateImage); return true;
  case 0x233b0: result.bits=game_access::directionVector233b0(a[0],static_cast<GameAccessBridge*>(pointer(a[1])),a[2],context.image); return true;
  case 0x290d0: result.bits=game_access::textColor290d0(a[0],std::uint16_t(a[1]),context.image); return true;
// END REVIEWED REMAINING GAME ADAPTER
  default:
    return false;
  }
}
// Normalized word adapters encode native floating inputs/results as their bits.
// The boundary exists only for endpoints without a matched typed
// implementation.
struct WordEndpoints {
  Context &native;
  void *user;
  Word (*unresolved)(void *, Word, const Word *, std::size_t);
  template <class... Arguments>
  Word operator()(Word rva, Arguments... arguments) const {
    const Word words[sizeof...(Arguments) < 6 ? 6 : sizeof...(Arguments)] = {
        Word(arguments)...};
    Value value;
    if (resolve(native, rva, words, value))
      return value.bits;
    return unresolved(user, rva, words, sizeof...(Arguments));
  }
};
// Mixed Microsoft x64 frames preserve GPR/XMM/stack inputs independently.
inline bool resolveFrame(Context &context, Word rva, const Word *g,
                         const Word *x, const Word *stack, Value &result) {
  Word a[8] = {g[0], g[1], g[2], g[3], stack[0], stack[1], 0, 0};
  switch (rva) {
  case 0x13d190:
  case 0x13cfa0:
    a[0] = x[0];
    break;
  case 0x13cfc0:
  case 0x13cfe0:
  case 0x13cfb0:
  case 0x13cfd0:
    a[0] = x[0];
    a[1] = x[1];
    break;
  case 0x23e90:
  case 0x27e10:
  case 0x27b70:
  case 0x273e0:
    a[2] = x[2];
    break;
  case 0x278f0:
    a[1] = x[1];
    a[2] = x[2];
    a[3] = x[3];
    break;
  case 0x27590:
    a[3] = x[3];
    a[6] = stack[2];
    break;
  case 0x27ba0:
  case 0x24860:
    a[6] = stack[2];
    break;
  case 0x27c10:
    a[6] = stack[2];
    a[7] = stack[3];
    break;
  case 0x70000000:
    a[5] = stack[0];
    break;
  case 0x29290:
    a[2] = x[2];
    a[3] = x[3];
    break;
  case 0xa050:
    a[0] = x[0];
    a[1] = x[1];
    break;
  case 0xa460:
    a[0] = x[0];
    break;
  case 0xa510:
  case 0xaa30:
    a[2] = x[2];
    break;
  case 0xa1f0:
  case 0xa2b0:
  case 0xa2d0:
    a[0] = x[0];
    a[1] = x[1];
    a[2] = x[2];
    break;
  case 0xa210:
  case 0xb2050:
  case 0xb2920:
  case 0xb1cf0:
  case 0xb3590:
  case 0xb29b0:
  case 0xb1fb0:
  case 0xabeb0:
    a[0] = x[0];
    break;
  case 0xb2170:
  case 0xb2300:
    a[0] = x[0];
    a[1] = x[1];
    break;
  case 0x9e60:
  case 0x9e90:
    a[2] = x[2];
    a[1] = rva == 0x9e60 ? x[1] : g[1];
    break;
  }
  return resolve(context, rva, a, result);
}
} // namespace reconstruction::native_binding
#endif // SLINKY_SHARE_1841AF5CF9ADE46A223B
