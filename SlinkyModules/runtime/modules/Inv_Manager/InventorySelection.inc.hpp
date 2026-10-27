#ifndef SLINKY_SHARE_A774453B3D84C8726DFE
#define SLINKY_SHARE_A774453B3D84C8726DFE
// Owned interval candidates 0x47870..0x485df, recovered from Inv_Manager.cpp
// and audited against the separately labelled runtime_observed_locals.asm.
// Scalar return registers are narrowed only where original callers consume
// AL/AX.
static int32_t signedWord(uint32_t value) {
  int32_t result;
  memcpy(&result, &value, 4);
  return result;
}
static double imageDouble(uint8_t *image, uint32_t rva) {
  uint64_t bits = loadWord64(image + rva);
  double value;
  memcpy(&value, &bits, 8);
  return value;
}
static double dadd(double a, double b) {
  return _mm_cvtsd_f64(_mm_add_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
static double dsub(double a, double b) {
  return _mm_cvtsd_f64(_mm_sub_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
static double dmul(double a, double b) {
  return _mm_cvtsd_f64(_mm_mul_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
static double ddiv(double a, double b) {
  return _mm_cvtsd_f64(_mm_div_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
static float narrow(double a) {
  return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(), _mm_set_sd(a)));
}
static uint64_t environmentOf(uint8_t *ctx) {
  return loadWord64(reinterpret_cast<void *>(loadWord64(ctx) + 8));
}
// JNI environment vtable +0x538 NewStringUTF; +0x568 GetObjectArrayElement.
static uint64_t nameTag(uint64_t environment, uint8_t *image, uint32_t rva,
                        dependency call) {
  return call(0x80000538, environment, uintptr_t(image + rva), 0, 0, 0);
}
static uint64_t arrayElement(uint64_t environment, uint64_t array,
                             uint32_t index, dependency call) {
  return call(0x80000568, environment, array, index, 0, 0);
}
static uint64_t stackIdentity(uint8_t *ctx, uint64_t stack, dependency call) {
  uint64_t item = call(0x25d10, loadWord64(ctx), stack, 0, 0, 0);
  if (!item)
    return 0;
  uint32_t type = uint32_t(call(0x25c50, loadWord64(ctx), item, 0, 0, 0));
  int32_t damage =
      signedWord(uint32_t(call(0x25dc0, loadWord64(ctx), stack, 0, 0, 0)));
  return (uint64_t(type) << 32) | uint64_t(int64_t(damage));
}
// RVA 0x48360: low word category, high word material tier.
static uint64_t classifyToolMaterial(uint32_t item) {
  uint32_t category = 1, tier = 1;
  switch (item) {
  case 0x100:
    category = 16;
    tier = 3;
    break;
  case 0x101:
    category = 14;
    tier = 3;
    break;
  case 0x102:
    tier = 3;
    break;
  case 0x10b:
    category = 22;
    tier = 3;
    break;
  case 0x10c:
    category = 22;
    break;
  case 0x10d:
    category = 16;
    break;
  case 0x10e:
    category = 14;
    break;
  case 0x10f:
    break;
  case 0x110:
    category = 22;
    tier = 2;
    break;
  case 0x111:
    category = 16;
    tier = 2;
    break;
  case 0x112:
    category = 14;
    tier = 2;
    break;
  case 0x113:
    tier = 2;
    break;
  case 0x114:
    category = 22;
    tier = 5;
    break;
  case 0x115:
    category = 16;
    tier = 5;
    break;
  case 0x116:
    category = 14;
    tier = 5;
    break;
  case 0x117:
    tier = 5;
    break;
  case 0x11b:
    category = 22;
    tier = 4;
    break;
  case 0x11c:
    category = 16;
    tier = 4;
    break;
  case 0x11d:
    category = 14;
    tier = 4;
    break;
  case 0x11e:
    tier = 4;
    break;
  case 0x167:
    category = 15;
    break;
  default:
    category = 0;
    tier = 0;
  }
  return uint64_t(category) | (uint64_t(tier) << 32);
}
// RVA 0x484d0. Coefficient table indexes tag id; accumulation wraps at 32 bits.
static uint32_t weightedTagScore(uint8_t *ctx, uint64_t tags,
                                 uint8_t *coefficients, uint8_t *image,
                                 dependency call) {
  if (!tags)
    return 0;
  uint64_t environment = environmentOf(ctx);
  uint64_t idName = nameTag(environment, image, 0x155b94, call);
  if (!idName)
    return 0;
  uint64_t levelName = nameTag(environment, image, 0x155b97, call);
  if (!levelName)
    return 0;
  int32_t count =
      signedWord(uint32_t(call(0x27f10, loadWord64(ctx), tags, 0, 0, 0)));
  if (count <= 0)
    return 0;
  uint32_t total = 0;
  for (uint32_t index = 0; index != uint32_t(count); ++index) {
    uint64_t tag = call(0x27f40, loadWord64(ctx), tags, index, 0, 0);
    uint16_t id = uint16_t(call(0x27f70, loadWord64(ctx), tag, idName, 0, 0));
    uint8_t coefficient = id < 63 ? coefficients[id] : 0;
    if (coefficient) {
      uint32_t level =
          uint32_t(call(0x27f70, loadWord64(ctx), tag, levelName, 0, 0));
      uint32_t score = uint32_t(coefficient) * level;
      if (int16_t(uint16_t(level)) < 0)
        score = 0;
      total += score;
    }
  }
  return total;
}
// RVA 0x48080. Category numbering is native configuration numbering.
static uint16_t scoreItemCategory(uint8_t *ctx, uint32_t category,
                                  uint32_t item, uint32_t damage, uint64_t tags,
                                  uint8_t itemFlag, uint8_t *image,
                                  dependency call) {
  if (category - 1u > 25u)
    return 0;
  switch (category) {
  case 2:
    if (item - 1u > 0xa1u)
      return 0;
    switch (item) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 0x11:
    case 0x12:
    case 0x14:
    case 0x18:
    case 0x23:
    case 0x2d:
    case 0x31:
    case 0x4e:
    case 0x57:
    case 0x5f:
    case 0x62:
    case 0x79:
    case 0x7d:
    case 0x85:
    case 0x9b:
    case 0x9f:
    case 0xa2:
      return 1;
    default:
      return 0;
    }
  case 3:
    return item == 0x105
               ? uint16_t(weightedTagScore(ctx, tags, image + 0x155d30, image,
                                           call) +
                          1)
               : 0;
  case 4:
    return item == 0x36;
  case 5:
    return item == 0x170 ? uint16_t(2u - itemFlag) : 0;
  case 6:
    return item == 0x181;
  case 7:
    return item == 0x15a;
  case 8:
    return item == 0x103;
  case 9:
    return item == 0x142 ? uint16_t((damage == 1) + 1) : 0;
  case 10:
  case 11:
  case 19:
  case 21: {
    if (item != 0x175)
      return 0;
    uint16_t base;
    switch (damage & 15) {
    case 1:
      if (category != 10)
        return 0;
      base = 1;
      break;
    case 5:
      if (category != 10)
        return 0;
      base = 2;
      break;
    case 2:
      if (category != 19)
        return 0;
      base = 1;
      break;
    case 9:
      if (category != 21)
        return 0;
      base = 1;
      break;
    case 11:
      if (category != 11)
        return 0;
      base = 1;
      break;
    default:
      return 0;
    }
    return uint16_t(((damage >> 6) & 1) + base + ((damage >> 5) & 1));
  }
  case 12:
    return item == 0x41;
  case 13:
    return item == 0x147;
  case 17:
    return item == 0x14c || item == 0x158;
  case 18:
    return item == 0x19d || item == 0x11a;
  case 20:
    return item == 0x118;
  case 23:
    return item == 0x2e;
  case 24:
    return item == 0x146;
  case 26:
    return item == 0x23;
  case 22: {
    uint64_t classified = classifyToolMaterial(item);
    if (uint32_t(classified) != 22)
      return 0;
    uint32_t tier = image[0x155d1e + (classified >> 32)];
    return uint16_t(weightedTagScore(ctx, tags, image + 0x155ce0, image, call) +
                    tier * 40u + 160u);
  }
  case 25: {
    uint64_t classified = classifyToolMaterial(item);
    uint16_t preference;
    switch (uint32_t(classified)) {
    case 1:
      preference = 3;
      break;
    case 14:
      preference = 2;
      break;
    case 16:
      preference = 1;
      break;
    case 22:
      preference = 4;
      break;
    default:
      preference = 0;
    }
    uint32_t amount =
        (uint32_t(preference) + image[0x155d1e + (classified >> 32)]) * 40;
    return uint16_t(weightedTagScore(ctx, tags, image + 0x155ce0, image, call) +
                    amount);
  }
  default: {
    uint64_t classified = classifyToolMaterial(item);
    if (category != uint32_t(classified))
      return 0;
    uint32_t amount = uint32_t(classified >> 32) * 100u;
    return uint16_t(weightedTagScore(ctx, tags, image + 0x155d70, image, call) +
                    amount);
  }
  }
}
// RVA 0x47f90. Strict category wins in high 16 bits when the hotbar fallback
// setting is set.
static uint32_t scoreStackPolicy(uint8_t *ctx, uint64_t stack,
                                 uint32_t category, uint8_t *image,
                                 dependency call) {
  uint64_t item = call(0x25d10, loadWord64(ctx), stack, 0, 0, 0);
  if (!item)
    return 0;
  uint32_t type = uint32_t(call(0x25c50, loadWord64(ctx), item, 0, 0, 0));
  uint32_t damage = uint32_t(call(0x25dc0, loadWord64(ctx), stack, 0, 0, 0));
  uint64_t tags = call(0x25de0, loadWord64(ctx), stack, 0, 0, 0);
  uint8_t flag = uint8_t(call(0x25e80, loadWord64(ctx), stack, 0, 0, 0));
  uint16_t score =
      scoreItemCategory(ctx, category, type, damage, tags, flag, image, call);
  if (image[0x2f5208] == 1) {
    if (score)
      return uint32_t(score) << 16;
    uint32_t fallback;
    if (category == 22)
      fallback = 25;
    else if (category == 17)
      fallback = 7;
    else if (category == 7)
      fallback = 17;
    else
      return 0;
    return scoreItemCategory(ctx, fallback, type, damage, tags, flag, image,
                             call);
  }
  return score;
}
// RVA 0x47cf0. Score combines armor material and protection enchantments.
static uint32_t armorScore(uint8_t *ctx, uint64_t stack, uint32_t armorSlot,
                           uint8_t *image, dependency call) {
  if (!stack)
    return 0;
  uint64_t item = call(0x25d10, loadWord64(ctx), stack, 0, 0, 0);
  if (!item)
    return 0;
  uint32_t type = uint32_t(call(0x25c50, loadWord64(ctx), item, 0, 0, 0));
  uint32_t index = type - 0x12a;
  if (index >= 20 ||
      type + loadWord32(image + 0x155e70 + index * 4) != armorSlot)
    return 0;
  uint64_t material = loadWord64(image + 0x155ec0 + index * 8);
  uint64_t tags = call(0x25de0, loadWord64(ctx), stack, 0, 0, 0);
  uint8_t base = image[0x155b80 + material * 4 + armorSlot];
  double enchantments = 0;
  if (tags) {
    uint64_t environment = environmentOf(ctx),
             idName = nameTag(environment, image, 0x155b94, call);
    if (idName) {
      uint64_t levelName = nameTag(environment, image, 0x155b97, call);
      if (levelName) {
        int32_t count =
            signedWord(uint32_t(call(0x27f10, loadWord64(ctx), tags, 0, 0, 0)));
        double weight = imageDouble(image, 0x1555c0),
               scale = imageDouble(image, 0x1555c8),
               divisor = imageDouble(image, 0x1555d0);
        float fraction = loadFloat(image + 0x1555d8);
        float other = 0, protection = 0;
        for (uint32_t n = 0; signedWord(n) < count; ++n) {
          uint64_t tag = call(0x27f40, loadWord64(ctx), tags, n, 0, 0);
          uint16_t id =
              uint16_t(call(0x27f70, loadWord64(ctx), tag, idName, 0, 0));
          int16_t level = int16_t(
              uint16_t(call(0x27f70, loadWord64(ctx), tag, levelName, 0, 0)));
          if (level < 0)
            continue;
          if (uint32_t(id) - 1u < 4)
            other = narrow(dadd(dmul(double(level), weight), double(other)));
          else if (id == 0) {
            uint32_t power = uint32_t(level) * uint32_t(level) + 6u;
            double value =
                ddiv(dmul(double(signedWord(power)), scale), divisor);
            uint32_t quantized = uint32_t(_mm_cvttsd_si64(_mm_set_sd(value)));
            if (quantized >= 25)
              quantized = 25;
            uint32_t combined = (quantized >> 1) + ((quantized + 1) & 0x3e);
            protection = mul(float(signedWord(combined)), fraction);
          }
        }
        if (count > 0)
          enchantments = double(add(other, protection));
      }
    }
  }
  double factor = imageDouble(image, 0x1555e0),
         one = imageDouble(image, 0x1555e8);
  double materialRemainder = dsub(one, dmul(double(base), factor));
  double enchantRemainder = dsub(one, dmul(enchantments, factor));
  float combined = narrow(dsub(one, dmul(enchantRemainder, materialRemainder)));
  float scaled = mul(combined, loadFloat(image + 0x1555f0));
  return uint32_t(_mm_cvttss_si64(_mm_set_ss(scaled)));
}
// RVA 0x47870: plan one armor upgrade, retaining first strictly better score.
static bool planArmorUpgrade(uint8_t *ctx, uint8_t *action, uint8_t *image,
                             dependency call) {
  uint8_t armor = action[0x1c];
  uint64_t inventory =
      call(0x23f40, loadWord64(ctx), loadWord64(ctx + 0x28), 0, 0, 0);
  uint64_t equipped =
      call(0x26140, loadWord64(ctx), inventory, 39u - armor, 0, 0);
  uint64_t array = call(0x25ab0, loadWord64(ctx), inventory, 0, 0, 0),
           environment = environmentOf(ctx);
  uint32_t bestScore = armorScore(ctx, equipped, armor, image, call),
           best = UINT32_MAX;
  for (uint32_t slot = 0; slot != 36; ++slot) {
    uint64_t stack = arrayElement(environment, array, slot, call);
    uint32_t score = armorScore(ctx, stack, armor, image, call);
    if (bestScore < score) {
      bestScore = score;
      best = slot;
    }
  }
  if (best == UINT32_MAX)
    return false;
  if (!equipped) {
    storeWord64(action + 0x10, 0);
    action[0x1d] = uint8_t(best < 9 ? best + 36 : best);
  } else {
    storeWord32(action + 0x10, best < 9 ? 1 : 2);
    action[0x14] = uint8_t(best < 9 ? best : armor + 5);
    memset(action + 0x15, 0, 3);
    action[0x1d] = uint8_t(best < 9 ? action[0x1c] + 5 : best);
  }
  return true;
}
// RVA 0x479c0: compare total stack scores and compatible merge scores.
static bool planHotbarUpgrade(uint8_t *ctx, uint8_t *action, uint8_t *image,
                              dependency call) {
  uint8_t destination = action[0x1c];
  uint32_t category = loadWord32(image + 0x2f4fe0 + uint32_t(destination) * 64);
  if (!category)
    return false;
  uint64_t inventory =
               call(0x23f40, loadWord64(ctx), loadWord64(ctx + 0x28), 0, 0, 0),
           array = call(0x25ab0, loadWord64(ctx), inventory, 0, 0, 0),
           environment = environmentOf(ctx);
  uint64_t original = arrayElement(environment, array, destination, call);
  uint32_t originalCount = 0, maximumCount = 0, originalScore = 0;
  uint64_t identity = 0;
  if (original) {
    originalCount = uint32_t(call(0x25d70, loadWord64(ctx), original, 0, 0, 0));
    maximumCount = uint32_t(call(0x25e10, loadWord64(ctx), original, 0, 0, 0));
    identity = stackIdentity(ctx, original, call);
    originalScore = scoreStackPolicy(ctx, original, category, image, call);
  }
  bool hasEmpty = false;
  for (uint32_t slot = 9; slot != 36; ++slot) {
    if (!arrayElement(environment, array, slot, call)) {
      hasEmpty = true;
      break;
    }
  }
  if (signedWord(originalCount) <= 0)
    originalCount = 0;
  uint32_t bestScore = originalCount * originalScore, best = destination,
           mergeFlag = hasEmpty ? 0 : 36;
  for (uint32_t slot = 0; slot != 36; ++slot) {
    if (slot == destination || ((loadWord64(action + 8) >> (slot & 63)) & 1))
      continue;
    uint64_t stack = arrayElement(environment, array, slot, call);
    if (!stack)
      continue;
    uint32_t count = uint32_t(call(0x25d70, loadWord64(ctx), stack, 0, 0, 0));
    uint64_t candidateIdentity = stackIdentity(ctx, stack, call);
    uint32_t mergedScore = 0;
    if (signedWord(originalCount) < signedWord(maximumCount) &&
        signedWord(count) < signedWord(maximumCount) &&
        candidateIdentity == identity &&
        uint8_t(call(0x25e40, loadWord64(ctx), original, stack, 0, 0))) {
      uint32_t combined = count + originalCount;
      if (signedWord(combined) >= signedWord(maximumCount))
        combined = maximumCount;
      mergedScore = combined * originalScore;
    }
    uint32_t score =
                 scoreStackPolicy(ctx, stack, category, image, call) * count,
             previous = score - 1u;
    bool merge = previous < mergedScore;
    if (merge)
      score = mergedScore;
    if (bestScore < score) {
      bool admissible = slot >= 9 || hasEmpty || !merge;
      if (admissible) {
        best = slot;
        bestScore = score;
        mergeFlag = merge ? 1 : 0;
      } else
        mergeFlag &= 0xff;
    }
  }
  bool changed = best != destination;
  if (!changed && bestScore == 0)
    return false;
  if (changed) {
    memset(action + 0x15, 0, 3);
    storeWord32(action + 0x10, uint8_t(~uint8_t(mergeFlag)) & 1);
    action[0x14] = (mergeFlag & 1) ? 0 : destination;
    action[0x1d] = uint8_t(best < 9 ? best + 36 : best);
  }
  uint32_t word = 1u << (destination & 31);
  int64_t mask = int64_t(signedWord(word));
  storeWord64(action + 8, loadWord64(action + 8) | uint64_t(mask));
  return changed;
}
#endif // SLINKY_SHARE_A774453B3D84C8726DFE
