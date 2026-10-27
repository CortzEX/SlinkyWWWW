#include <stdint.h>
#include <stddef.h>

/* Analyst-assigned names; layout and behavior are recovered from lib_win. */
typedef struct {
    uintptr_t bridge, reserved[2], client, reserved2, player;
} recovered_sprint_game;
typedef struct {
    uintptr_t reserved;
    recovered_sprint_game *game;
    float sideways, forward, scale;
} recovered_sprint_event;
typedef struct {
    uintptr_t (*screen)(uintptr_t, uintptr_t);
    uintptr_t (*options)(uintptr_t, uintptr_t);
    uintptr_t (*sprint_key)(uintptr_t, uintptr_t);
    void (*set_key)(uintptr_t, uintptr_t, uint8_t);
    uint8_t (*ready)(uintptr_t, uintptr_t);
    uint8_t (*using_item)(uintptr_t, uintptr_t);
    void (*set_sprinting)(uintptr_t, uintptr_t, uint8_t);
} recovered_sprint_dependencies;
static_assert(offsetof(recovered_sprint_event, forward) == 20, "event layout");
static_assert(offsetof(recovered_sprint_game, player) == 40, "game layout");

/* RVA 35d80. Settings pointer addresses the four records at RVA 2eda50. */
extern "C" __declspec(dllexport) void recovered_sprint_update(recovered_sprint_event *event,
    const uint8_t *settings, uint8_t *last_state, const recovered_sprint_dependencies *d)
{
    recovered_sprint_game *game = event->game;
    uintptr_t screen = d->screen(game->bridge, game->client);
    uint8_t active = (uint8_t)(((screen == 0) | settings[24]) & 1);
    uintptr_t options = d->options(game->bridge, game->client);
    uintptr_t key = d->sprint_key(game->bridge, options);
    d->set_key(game->bridge, key, active);
    if (game->player) {
        if (!active) {
            if (*last_state == 1) d->set_sprinting(game->bridge, game->player, 0);
            return;
        }
        if (d->ready(game->bridge, game->player)) d->set_sprinting(game->bridge, game->player, 1);
    }
    *last_state = active;
}

/* RVA 35e30. The 1.3 multiplication is double precision, rounded back to float. */
extern "C" __declspec(dllexport) void recovered_sprint_movement(recovered_sprint_event *event,
    const uint8_t *settings, const recovered_sprint_dependencies *d)
{
    recovered_sprint_game *game = event->game;
    if (event->forward == 0.0f && event->sideways == 0.0f) return;
    uint8_t using_item = d->using_item(game->bridge, game->player);
    if (using_item && !settings[56]) return;
    float forward = event->forward;
    if (forward < 0.0f) {
        if (!settings[88]) return;
    } else if (forward == 0.0f && event->sideways != 0.0f) {
        if (!settings[120]) return;
    } else if (!using_item) return;
    event->scale = (float)((double)event->scale * 1.3);
    d->set_sprinting(game->bridge, game->player, 1);
}
