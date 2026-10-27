#include <stdint.h>
#include <stddef.h>
#include <string.h>

/* Unknown game/runtime methods remain explicit RVA-keyed boundaries. */
typedef uint64_t (*rod_dispatch)(void *opaque, uint32_t rva,
    uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9,
    uint64_t fifth_stack_arg);

/* Stacked callback context prevents recursive calls from overwriting parents. */
static __declspec(thread) uint8_t *g_image;
static __declspec(thread) rod_dispatch g_call;
static __declspec(thread) void *g_opaque;

static uint64_t load64(const void *p, size_t off)
{ uint64_t v; memcpy(&v, (const uint8_t *)p + off, 8); return v; }
static uint32_t load32(const void *p, size_t off)
{ uint32_t v; memcpy(&v, (const uint8_t *)p + off, 4); return v; }
static uint8_t load8(const void *p, size_t off)
{ return *((const uint8_t *)p + off); }
static void store32(void *p, size_t off, uint32_t v)
{ memcpy((uint8_t *)p + off, &v, 4); }
static void store8(void *p, size_t off, uint8_t v)
{ *((uint8_t *)p + off) = v; }
static uint64_t image64(size_t off) { return load64(g_image, off); }
static uint32_t image32(size_t off) { return load32(g_image, off); }
static uint8_t image8(size_t off) { return load8(g_image, off); }
static void set32(size_t off, uint32_t v) { store32(g_image, off, v); }
static void set8(size_t off, uint8_t v) { store8(g_image, off, v); }
static uint64_t call5(uint32_t rva, uint64_t a, uint64_t b, uint64_t c,
    uint64_t d, uint64_t stack_arg)
{ return g_call(g_opaque, rva, a, b, c, d, stack_arg); }
static uint64_t call0(uint32_t rva)
{ return call5(rva, 0, 0, 0, 0, 0); }
static float f32_from_bits(uint32_t bits)
{ float f; memcpy(&f, &bits, 4); return f; }
static float call_f32(uint32_t rva)
{ return f32_from_bits((uint32_t)call0(rva)); }
static uint64_t descriptor(void) { return (uint64_t)(uintptr_t)(g_image + 0x2f3520); }

static uint64_t game_of(uint8_t *bridge) { return load64(bridge, 0); }

static uint64_t current_item(uint8_t *bridge)
{
    uint64_t game = game_of(bridge);
    uint64_t slotptr = load64(bridge, 0x28);
    return call5(0x23f40, game, slotptr, 0, 0, 0);
}

static void select_slot(uint8_t *bridge, uint64_t item, uint32_t slot)
{
    uint64_t game = game_of(bridge);
    call5(0x25a80, game, item, (uint32_t)slot, 0, 0);
}

static void restore_selected(uint8_t *bridge)
{
    if ((int32_t)image32(0x2f3730) != -1) {
        uint64_t item = current_item(bridge);
        select_slot(bridge, item, image32(0x2f3730));
        set32(0x2f3730, UINT32_MAX);
    }
}

static void unregister_module(void)
{ call5(0x2aab0, descriptor(), 0, 0, 0, 0); }

static uint32_t item_kind(uint8_t *bridge, uint64_t item)
{
    uint64_t game = game_of(bridge);
    uint64_t obj = call5(0x25d10, game, item, 0, 0, 0);
    if (!obj) return 0;
    game = game_of(bridge);
    return (uint32_t)call5(0x25c50, game, obj, 0, 0, 0);
}

static int32_t scan_rod_slot(uint8_t *bridge, uint64_t held, uint8_t *recognized)
{
    int32_t candidate = -1;
    for (uint32_t i = 0; i < 9; ++i) {
        uint64_t game = game_of(bridge);
        uint64_t item = call5(0x26140, game, held, i, 0, 0);
        if (!item) continue;
        uint32_t kind = item_kind(bridge, item);
        if (kind == 0x14c || kind == 0x158) {
            if (image8(0x2f3770) == 1) { *recognized = 0; return (int32_t)i; }
        } else if (kind == 0x15a) {
            *recognized = 1; set8(0x304414, 1); candidate=(int32_t)i;
            if (image8(0x2f3770) == 0) return candidate;
        }
    }
    return candidate;
}

static void schedule_event(uint8_t *bridge)
{
    uint64_t context = load64(bridge, 8);
    call5(0x284f0, context, descriptor(), 0, 0, 0);
}

static void auto_rod_impl_43d80(uint8_t *event, uint8_t *image)
{
    uint8_t *bridge = (uint8_t *)(uintptr_t)load64(event, 8);
    if (load8(bridge, 0x40) != 1) return;

    if (image8(0x304400) != 0) {
        restore_selected(bridge);
        unregister_module();
        uint64_t context = load64(bridge, 8);
        call5(0x284f0, context, descriptor(), 0, 0, 0);
        set8(0x304400, 0);
        return;
    }

    for (uint32_t iteration = 0; iteration < 3; ++iteration) {
        if (image8(0x2f3750) == 1) {
            uint64_t game = game_of(bridge);
            uint64_t target = call5(0x22e10, game, load64(bridge, 0x18), 0, 0, 0);
            if (target) {
                game = game_of(bridge);
                uint32_t result = (uint32_t)call5(0x24b50, game, target, 0, 0, 0);
                if (result == 2) {
                    restore_selected(bridge); unregister_module(); set32(0x304404, 6);
                    goto finish_state6;
                }
            }
        }

        if (image32(0x304404) == 7) {
            restore_selected(bridge); unregister_module();
            set32(0x304404, 0);
            return;
        }

        if (image32(0x304410) != 0) set32(0x304410, image32(0x304410) - 1);
        float delay = f32_from_bits(image32(0x30440c));
        if (delay > 0.0f) {
            delay = delay - 1.0f;
            uint32_t bits; memcpy(&bits, &delay, 4); set32(0x30440c, bits);
            if (delay > 0.0f) break;
        }

        uint64_t held = current_item(bridge);
        uint32_t held_slot = (uint32_t)call5(0x25a60, game_of(bridge), held, 0, 0, 0);
        uint32_t state = image32(0x304404);
        if (state > 1 && held_slot != image32(0x304408)) {
            unregister_module(); set32(0x304404, 6);
            goto finish_state6;
        }
        if (state > 5) break;

        if (state == 0) {
            set8(0x304414, 0);
            uint8_t recognized = 0;
            int32_t selected = scan_rod_slot(bridge, held, &recognized);
            if (selected < 0) { set32(0x304404, 6); goto finish_state6; }
            if ((uint8_t)call5(0x2aa80, descriptor(), 0, 0, 0, 0) == 0) {
                set32(0x304404, 6); goto finish_state6;
            }
            set32(0x2f3730, held_slot); set32(0x304408, (uint32_t)selected);
            if (image8(0x2f3790) == 1) {
                uint32_t better = (uint32_t)call5(0x380c0, (uint64_t)(uintptr_t)bridge, held, 0, 0, 0);
                if (better != UINT32_MAX) set32(0x2f3730, better);
                held_slot = image32(0x2f3730);
            }
            set32(0x304404, image32(0x304408) == held_slot ? 2 : 1);
            goto next_iteration;
        } else if (state == 1) {
            /* 0x43ec3 reloads the selected slot after the getter call. */
            select_slot(bridge, held, image32(0x304408));
            set32(0x304404, 2); set8(0x304415, 0);
        } else if (state == 2) {
            set8(0x304414, 0);
            uint8_t recognized = 0;
            int32_t selected = scan_rod_slot(bridge, held, &recognized);
            if (selected < 0) { set32(0x304404, 5); return; }
            if ((uint32_t)selected == held_slot) {
                uint64_t game = game_of(bridge);
                uint64_t target = call5(0x22cf0, game, load64(bridge, 0x18), 0, 0, 0);
                game = game_of(bridge); target = call5(0x24f90, game, target, 0, 0, 0);
                game = game_of(bridge); call5(0x253e0, game, target, 1, 0, 0);
                if (image8(0x304414) == 1) {
                    set32(0x304404, 3);
                    set32(0x304410, (uint32_t)call5(0x44660, (uint64_t)(uintptr_t)bridge,0,0,0,0));
                    float delta=call_f32(0x445a0);
                    float previous=f32_from_bits(image32(0x30440c));
                    float d=delta+previous;
                    uint32_t bits; memcpy(&bits,&d,4); set32(0x30440c,bits);
                    return;
                }
                if (image8(0x2f3540) != 1) {
                    set32(0x304404, 5);
                    float delta=call_f32(0x445a0);
                    float previous=f32_from_bits(image32(0x30440c));
                    float d=delta+previous;
                    uint32_t bits; memcpy(&bits,&d,4); set32(0x30440c,bits);
                    return;
                } else {
                    float delta=call_f32(0x44860);
                    float previous=f32_from_bits(image32(0x30440c));
                    float d=delta+previous;
                    uint32_t bits; memcpy(&bits,&d,4); set32(0x30440c,bits);
                    return;
                }
            } else {
                set32(0x304404, 1); set32(0x304408, (uint32_t)selected);
                float delta=call_f32(0x445a0);
                float previous=f32_from_bits(image32(0x30440c));
                float d=delta+previous;
                uint32_t bits; memcpy(&bits,&d,4); set32(0x30440c,bits);
                goto next_iteration;
            }
        } else if (state == 3) {
            if (image32(0x304410) != 0) break;
            set32(0x304404, ((image32(0x2f3730) == image32(0x304408)) ? 1u : 0u) ^ 5u);
        } else if (state == 4) {
            int32_t slot=(int32_t)image32(0x2f3730);
            uint32_t wrapped=(uint32_t)slot+1u;
            int32_t signed_wrapped; memcpy(&signed_wrapped,&wrapped,sizeof(wrapped));
            int32_t next=signed_wrapped%9;
            select_slot(bridge, held, (uint32_t)next);
            set32(0x304404, 5); return;
        } else if (state == 5) {
            set32(0x304404, 6); restore_selected(bridge); unregister_module();
            float delta=call_f32(0x445a0);
            float previous=f32_from_bits(image32(0x30440c));
            float d=delta+previous;
            uint32_t bits; memcpy(&bits,&d,4); set32(0x30440c,bits);
            goto finish_state6;
        }
        {
            float delta=call_f32(0x445a0);
            float previous=f32_from_bits(image32(0x30440c));
            float d=delta+previous;
            uint32_t bits; memcpy(&bits,&d,4); set32(0x30440c,bits);
        }
next_iteration:
        ;
    }
    if (image32(0x304404) == 6) goto finish_state6;
    return;

finish_state6:
    if (image32(0x304404) != 6) return;
    if (image8(0x2f3540) == 1) { set32(0x304404, 0); return; }
    schedule_event(bridge);
}

__declspec(dllexport) void recovered_auto_rod_43d80(uint8_t *event, uint8_t *image, rod_dispatch dispatch, void *opaque)
{
    uint8_t *old_image=g_image; rod_dispatch old_call=g_call; void *old_opaque=g_opaque;
    g_image=image; g_call=dispatch; g_opaque=opaque;
    auto_rod_impl_43d80(event,image);
    g_image=old_image; g_call=old_call; g_opaque=old_opaque;
}

__declspec(dllexport) void recovered_auto_rod_44340(uint8_t *event, uint8_t *image)
{
    if (load8(image,0x304400)!=0) return;
    if (load64(event,8)!=(uint64_t)(uintptr_t)(image+0x2f3520)) return;
    if (load8(image,0x2f3540)==1) store8(image,0x304400,1);
    else {
        uint32_t state=load32(image,0x304404);
        if (state==6) return;
        if (state==3) store32(image,0x304404,7);
    }
    store8(event,0x10,1);
}

__declspec(dllexport) void recovered_auto_rod_44390(uint8_t *event, uint8_t *image)
{
    if (load64(event,0x10)==(uint64_t)(uintptr_t)(image+0x2f3520) && load8(event,0x18)==1)
        store32(image,0x304404,0);
}

__declspec(dllexport) void recovered_auto_rod_443c0(uint8_t *event, uint8_t *image, rod_dispatch dispatch, void *opaque)
{
    if (load8(event,0x10)!=0) return;
    uint8_t *bridge=(uint8_t *)(uintptr_t)load64(event,8);
    uint64_t obj=dispatch(opaque,0x28a50,game_of(bridge),load64(bridge,0x28),0,0,0);
    if (!obj) return;
    uint32_t kind=(uint32_t)dispatch(opaque,0x25c50,game_of(bridge),obj,0,0,0);
    if (kind==0x15a) {
        if (load8(image,0x304415)==0) store8(image,0x304415,1);
        else store8(event,0x11,1);
    }
}
