#include <stdint.h>
#include <string.h>

typedef uint64_t (*teams_dispatch)(uint32_t rva, uint64_t rcx, uint64_t rdx,
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

static void write_zero(void *p, size_t size)
{
    memset(p, 0, size);
}

static uint64_t invoke2(teams_dispatch call, uint32_t rva, uint64_t a, uint64_t b)
{
    return call(rva, a, b, 0, 0, 0, 0);
}

static uint64_t invoke3(teams_dispatch call, uint32_t rva,
    uint64_t a, uint64_t b, uint64_t c)
{
    return call(rva, a, b, c, 0, 0, 0);
}

__declspec(dllexport) void recovered_teams_31e10(
    uint8_t *event, uint8_t *image, teams_dispatch call)
{
    uint8_t *context = (uint8_t *)(uintptr_t)read64(event + 8);
    if (!read64(context + 0x28)) return;

    uint16_t owner;
    uint64_t game = read64(context);
    uint64_t game_object = read64((const void *)(uintptr_t)game);
    if (read32((const void *)(uintptr_t)game_object) != 0) {
        uint64_t first = invoke2(call, 0x22d10, read64(context), read64(context + 0x18));
        first = invoke2(call, 0x25eb0, read64(context), first);
        uint64_t target = invoke2(call, 0x23740, read64(context), read64(context + 0x28));
        uint64_t component = invoke3(call, 0x24f40, read64(context), first, target);
        if (component) {
            uint64_t result = invoke2(call, 0x26010, read64(context), component);
            if (result) {
                result = invoke2(call, 0x26090, read64(context), result);
                uint16_t value = (uint16_t)invoke2(call, 0x28b40, read64(context), result);
                owner = value ? value : 0x72;
                goto have_owner;
            }
            result = invoke2(call, 0x26030, read64(context), component);
            if (result) {
                owner = (uint16_t)invoke2(call, 0x28d20, read64(context), result);
                goto have_owner;
            }
        }
    }
    owner = (uint16_t)invoke2(call, 0x28e10, read64(context), read64(context + 0x28));

have_owner:
    {
        uint64_t collection = invoke2(call, 0x24600, read64(context), read64(context + 0x20));
        int32_t count = (int32_t)invoke2(call, 0x24e50, read64(context), collection);
        if (count <= 0) return;

        uint32_t index = 0;
        for (;;) {
            uint64_t item = invoke3(call, 0x24e80, read64(context), collection, index);
            uint64_t controller = read64((const void *)(uintptr_t)(read64(context) + 8));
            uint64_t target = read64(context + 0x28);
            uint64_t table = read64((const void *)(uintptr_t)controller);
            uint64_t endpoint = read64((const void *)(uintptr_t)(table + 0xc0));
            uint8_t is_teammate = (uint8_t)call(0x800001c0, controller, target, item, 0, 0, endpoint);
            if (!is_teammate) {
                uint32_t item_code = (uint32_t)invoke2(call, 0x28e10, read64(context), item);
                if (!(image[0x2eb628] == 1 && (uint16_t)item_code == owner)) {
                    uint8_t low = (uint8_t)item_code;
                    uint8_t character = (uint8_t)(((int8_t)low >= 0x61 ? 0xa9 : 0xd0) + low);
                    uint64_t result = call(0xdf00, read64(image + 0x2f9e20), 1,
                        (uintptr_t)(image + 0x2f9e28), (uintptr_t)&character,
                        UINT64_C(0x180000000) + 0x32170, 0);
                    if (!result) {
                        invoke3(call, 0x2ad80, read64(context), item, 1);
                        goto next_item;
                    }
                }
                invoke3(call, 0x2ad20, read64(context), item, 1);
            }
next_item:
            ++index;
            count = (int32_t)invoke2(call, 0x24e50, read64(context), collection);
            if ((int32_t)index >= count) return;
        }
    }
}

__declspec(dllexport) void recovered_teams_31ff0(
    uint8_t *event, uint8_t *image, teams_dispatch call)
{
    if (read64(event + 0x10) != (uintptr_t)(image + 0x2eb400) || event[0x18] != 0)
        return;
    uint8_t *context = (uint8_t *)(uintptr_t)read64(event + 8);
    uint64_t target = read64(context + 0x20);
    if (!target) return;

    uint64_t collection = invoke2(call, 0x24600, read64(context), target);
    int32_t count = (int32_t)invoke2(call, 0x24e50, read64(context), collection);
    if (count <= 0) return;

    uint32_t index = 0;
    do {
        uint64_t item = invoke3(call, 0x24e80, read64(context), collection, index);
        uint64_t controller = read64((const void *)(uintptr_t)(read64(context) + 8));
        uint64_t current_target = read64(context + 0x28);
        uint64_t table = read64((const void *)(uintptr_t)controller);
        uint64_t endpoint = read64((const void *)(uintptr_t)(table + 0xc0));
        uint8_t is_teammate = (uint8_t)call(0x800001c0, controller, current_target, item, 0, 0, endpoint);
        if (!is_teammate) invoke3(call, 0x2ad80, read64(context), item, 1);
        ++index;
        count = (int32_t)invoke2(call, 0x24e50, read64(context), collection);
    } while ((int32_t)index < count);
}

__declspec(dllexport) void recovered_teams_320b0(uint8_t *image, teams_dispatch call)
{
    uint64_t handle = read64(image + 0x2f9e20);
    call(0x13cf70, handle, 0, 0, 0, 0, 0);
    write_zero(image + 0x2f9e20, 16);
}

/* Direct comparator passed to the injected 0xdf00 registration dependency.
   Its supplied instruction bytes sign-extend both char operands. */
__declspec(dllexport) int32_t recovered_teams_compare_32170(
    const uint8_t *unused, const int8_t *left, const int8_t *right)
{
    (void)unused;
    return (int32_t)*left - (int32_t)*right;
}
