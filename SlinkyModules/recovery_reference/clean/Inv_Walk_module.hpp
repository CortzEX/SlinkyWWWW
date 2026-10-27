#pragma once
#include "Inv_Walk.hpp"

// Restores the captured settings baseline into host-owned storage. This does not
// establish the original constructor's behavior before the capture.
extern "C" __declspec(dllexport) void recovered_inv_walk_initialize_settings(InvWalkSettings *);

class InvWalkModule {
public:
    enum class Mode : std::uint32_t { Vanilla, Spoof };
    enum class StopMode : std::uint32_t { Full, Partial, No };
    static constexpr const char *name = "Inv Walk";
    static constexpr const char *description = "Allows moving in inventory.";

    InvWalkSettings settings{};
    InvWalkState state{};
    InvWalkDependencies access;

    // Identity is the host's module token used by the disable event.
    InvWalkModule(std::uintptr_t identity, const InvWalkDependencies &dependencies)
        : access(dependencies), identity_(identity) {
        recovered_inv_walk_initialize_settings(&settings);
    }
    InvWalkModule(const InvWalkModule &) = delete;
    InvWalkModule &operator=(const InvWalkModule &) = delete;

    void update(TimerEvent &event) {
        recovered_inv_walk_typed_update(&event, &settings, &state, &access);
    }
    void disable(TimerEvent &event) {
        recovered_inv_walk_typed_disable(&event, identity_, &state, &access);
    }
    void packet(InvWalkPacketEvent &event) {
        recovered_inv_walk_typed_packet(&event, &settings, &state, &access);
    }
    void finish(TimerEvent &event) {
        recovered_inv_walk_typed_finish(&event, &state, &access);
    }
    std::uint8_t flush(GameAccessBridge &bridge, std::uintptr_t client) {
        return recovered_inv_walk_typed_flush(&bridge, client, &state, &access);
    }
    std::uint64_t render(std::uint64_t ui, std::uint64_t layout, UiDirtyState &dirty,
                         const ChoiceUiEndpoints &endpoints) {
        return recovered_inv_walk_typed_ui(ui, layout, &settings, &dirty, &endpoints);
    }
    void configure(SettingsContext &context, const ValueSettingsDependencies &endpoints) {
        recovered_inv_walk_typed_settings(&context, &settings, &endpoints);
    }
    std::uint64_t status(char (&destination)[32], FormatState &format) const {
        static constexpr const char *labels[] = {"Vanilla", "Spoof"};
        return recovered_inv_walk_label(destination, &settings.mode, labels, &format);
    }

private:
    std::uintptr_t identity_;
};
