#include <stdint.h>
#include <string.h>

typedef uint64_t (*antibot_dispatch)(uint32_t rva, uint64_t rcx, uint64_t rdx,
    uint64_t r8, uint64_t r9, uint64_t fifth_stack_argument,
    uint64_t indirect_call_target);

static uint64_t read64(const void *p)
{
    uint64_t value;
    memcpy(&value, p, sizeof(value));
    return value;
}

static uint32_t read32(const void *p)
{
    uint32_t value;
    memcpy(&value, p, sizeof(value));
    return value;
}

static void write_zero(void *p, size_t size) { memset(p, 0, size); }

static uint64_t call2(antibot_dispatch call, uint32_t rva, uint64_t a, uint64_t b)
{
    return call(rva, a, b, 0, 0, 0, 0);
}

static uint64_t call3(antibot_dispatch call, uint32_t rva,
    uint64_t a, uint64_t b, uint64_t c)
{
    return call(rva, a, b, c, 0, 0, 0);
}

static uint64_t indirect3(antibot_dispatch call, uint32_t id,
    uint64_t a, uint64_t b, uint64_t c, uint64_t target)
{
    return call(id, a, b, c, 0, 0, target);
}

static void update_cache_world(uint8_t *image, uint32_t world,
    antibot_dispatch call)
{
    if (read32(image + 0x2f9de8) == world) return;
    call(0x13cf70, read64(image + 0x2f9df0), 0, 0, 0, 0, 0);
    write_zero(image + 0x2f9df0, 16);
    memcpy(image + 0x2f9de8, &world, sizeof(world));
}

__declspec(dllexport) void recovered_antibot_30e70(
    uint8_t *event, uint8_t *image, antibot_dispatch call)
{
    uint8_t *context = (uint8_t *)(uintptr_t)read64(event + 8);
    uint64_t target = read64(context + 0x20);
    uint32_t world = target ? (uint32_t)call2(call, 0x26060, read64(context), target) : 0;
    update_cache_world(image, world, call);
    if (!read64(context + 0x20)) return;

    uint64_t collection = call2(call, 0x24600, read64(context), read64(context + 0x20));
    int32_t count = (int32_t)call2(call, 0x24e50, read64(context), collection);
    if (count <= 0) return;

    uint32_t index = 0;
    const double distance_limit = *(const double *)(const void *)(image + 0x1510c8);
    for (;;) {
        uint64_t item = call3(call, 0x24e80, read64(context), collection, index);
        uint64_t controller = read64((const void *)(uintptr_t)(read64(context) + 8));
        uint64_t table = read64((const void *)(uintptr_t)controller);
        uint64_t target_fn = read64((const void *)(uintptr_t)(table + 0xc0));
        uint8_t teammate = (uint8_t)indirect3(call, 0x800000c0,
            controller, read64(context + 0x28), item, target_fn);
        if (!teammate) {
            uint64_t entity = call2(call, 0x23740, read64(context), item);
            uint64_t key0 = call2(call, 0x27dc0, read64(context), entity);
            uint64_t key1 = call2(call, 0x27d90, read64(context), entity);
            uint64_t key[4] = { key0, key1, 0, 0 };
            uint64_t entry_ptr = call(0xe0b0, (uintptr_t)(image + 0x2f9df0),
                0x20, (uintptr_t)(image + 0x2f9df8), (uintptr_t)key,
                UINT64_C(0x180000000) + 0x31530, 0);
            uint8_t *entry = (uint8_t *)(uintptr_t)entry_ptr;
            double a[3] = {0,0,0}, b[3] = {0,0,0};
            call3(call, 0x230d0, (uintptr_t)a, read64(context), item);
            call3(call, 0x23030, (uintptr_t)b, read64(context), item);
            double dx = a[0] - b[0];
            double dz = a[2] - b[2];
            double dz_squared = dz * dz;
            double dx_squared = dx * dx;
            double planar = dx_squared + dz_squared;
            double distance = planar + *(double *)(void *)(entry + 0x10);
            memcpy(entry + 0x10, &distance, sizeof(distance));

            if (image[0x2eaf30] == 1 && distance_limit > distance) goto ignored;
            uint32_t mode = read32(image + 0x2eaf88);
            if (mode != 0) {
                uint32_t group = read32(entry) & 0xf000;
                if (group == 0x2000 && (mode == 2 || distance_limit > distance))
                    goto ignored;
            }
            if (image[0x2eafb0] == 1 && (uint8_t)call2(call, 0x240a0,
                    read64(context), item)) goto ignored;

            int32_t age = (int32_t)call2(call, 0x23760, read64(context), item);
            if (image[0x2eafd0] == 1 && entry[0x19] == 0) {
                uint64_t armor_game = read64(context);
                uint8_t should_check = (uint8_t)call3(call, 0x23f60,
                    armor_game, item, read64(context + 0x28));
                if (should_check) {
                    uint64_t armor_object = call2(call, 0x23f40, armor_game, item);
                    const uint32_t slots[] = {0x24,0x25,0x26,0x27};
                    for (unsigned i=0; i<4; ++i) {
                        uint64_t descriptor = call3(call, 0x26140,
                            armor_game, armor_object, slots[i]);
                        if (!descriptor) continue;
                        uint64_t slot = call2(call, 0x25d10, armor_game, descriptor);
                        if (!slot) continue;
                        uint32_t occupied = (uint32_t)call2(call, 0x25c50,
                            armor_game, slot);
                        if (occupied != 0) goto armor_found;
                    }
                    goto ignored;
                }
armor_found:
                if (age >= 21) entry[0x19] = 1;
            }
armor_done:
            {
                float threshold;
                memcpy(&threshold, image + 0x2eaf10, sizeof(threshold));
                if (0.0f < threshold && (int8_t)entry[0x18] == 0) {
                    float age_as_float = (float)age;
                    if (age_as_float < threshold) goto ignored;
                    entry[0x18] = 1;
                }
            }

            if (image[0x2eaff0] == 1 && entry[0x1a] == 0) {
                uint64_t name_controller = read64((const void *)(uintptr_t)(read64(context) + 8));
                uint64_t name_object = call2(call, 0x23830, read64(context), item);
                uint64_t name_table = read64((const void *)(uintptr_t)name_controller);
                int32_t name_length = (int32_t)indirect3(call, 0x80000520,
                    name_controller, name_object, 0, read64((const void *)(uintptr_t)(name_table + 0x520)));
                name_table = read64((const void *)(uintptr_t)name_controller);
                uint64_t name = indirect3(call, 0x80000700, name_controller,
                    name_object, 0, read64((const void *)(uintptr_t)(name_table + 0x700)));
                int32_t i = 0;
                while (name_length > 0 && i < name_length) {
                    uint16_t ch = *(const uint16_t *)(uintptr_t)(name + (uint64_t)i * 2);
                    if (ch == 0xa7) { ++i; }
                    else {
                        uint16_t upper = (uint16_t)(ch & 0xffdf);
                        if ((uint16_t)(upper - 0x41) < 0x1a || ch == 0x5f ||
                            (uint16_t)(ch - 0x30) < 10) {
                            entry[0x1a] = 1;
                            break;
                        }
                    }
                    ++i;
                }
                uint64_t release_table = read64((const void *)(uintptr_t)name_controller);
                uint64_t release_target = read64((const void *)(uintptr_t)(release_table + 0x708));
                (void)call(0x80000708, name_controller, name_object, name,
                    release_table, 0, release_target);
                if (entry[0x1a] == 0) goto ignored;
            }
            call3(call, 0x2ad80, read64(context), item, 2);
            goto next;
ignored:
            call3(call, 0x2ad20, read64(context), item, 2);
        }
next:
        ++index;
        count = (int32_t)call2(call, 0x24e50, read64(context), collection);
        if ((int32_t)index >= count) return;
    }
}

__declspec(dllexport) void recovered_antibot_31310(
    uint8_t *event, uint8_t *image, antibot_dispatch call)
{
    if (read64(event + 0x10) != (uintptr_t)(image + 0x2eacd0) || event[0x18] != 0)
        return;
    call(0x13cf70, read64(image + 0x2f9df0), 0, 0, 0, 0, 0);
    write_zero(image + 0x2f9df0, 16);
    uint8_t *context = (uint8_t *)(uintptr_t)read64(event + 8);
    uint64_t target = read64(context + 0x20);
    if (!target) return;
    uint64_t collection = call2(call, 0x24600, read64(context), target);
    int32_t count = (int32_t)call2(call, 0x24e50, read64(context), collection);
    if (count <= 0) return;
    uint32_t index = 0;
    do {
        uint64_t item = call3(call, 0x24e80, read64(context), collection, index);
        uint64_t controller = read64((const void *)(uintptr_t)(read64(context) + 8));
        uint64_t table = read64((const void *)(uintptr_t)controller);
        uint64_t target_fn = read64((const void *)(uintptr_t)(table + 0xc0));
        uint8_t teammate = (uint8_t)indirect3(call, 0x800000c0, controller,
            read64(context + 0x28), item, target_fn);
        if (!teammate) call3(call, 0x2ad80, read64(context), item, 2);
        ++index;
        count = (int32_t)call2(call, 0x24e50, read64(context), collection);
    } while ((int32_t)index < count);
}

/* Comparator is lexicographic on the two qwords after big-endian byte swap. */
__declspec(dllexport) int32_t recovered_antibot_compare_31530(
    const uint8_t *unused, const uint64_t *left, const uint64_t *right)
{
    (void)unused;
    uint64_t l0=left[0], r0=right[0], l1=left[1], r1=right[1];
    uint64_t b0=0,b1=0,c0=0,c1=0;
    for (unsigned i=0;i<8;++i) {
        b0=(b0<<8)|((l0>>(i*8))&0xff); c0=(c0<<8)|((r0>>(i*8))&0xff);
        b1=(b1<<8)|((l1>>(i*8))&0xff); c1=(c1<<8)|((r1>>(i*8))&0xff);
    }
    if (b0 != c0) return b0 < c0 ? -1 : 1;
    if (b1 == c1) return 0;
    return b1 < c1 ? -1 : 1;
}
