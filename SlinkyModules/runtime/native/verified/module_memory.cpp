#include "module_memory.hpp"

#include <array>
#include <cstdint>
#include <cstring>

// Copy 0xabbf0 loads and stores each group before reading the next group.
// Separate calls retain that ordering even when the ranges overlap.
template <std::size_t Width>
static __declspec(noinline) void copy_group(std::uint8_t *destination, const std::uint8_t *source) {
    std::array<std::uint8_t, Width> loaded;
    std::memcpy(loaded.data(), source, Width);
    std::memcpy(destination, loaded.data(), Width);
}

// Move 0xab910 produces memmove's byte result for valid backed ranges.
extern "C" __declspec(dllexport) void *recovered_memory_move(
    void *destination, const void *source, std::size_t count) {
    if (count) std::memmove(destination, source, count);
    return destination;
}

extern "C" __declspec(dllexport) void *recovered_memory_copy(
    void *destination, const void *source, std::size_t count) {
    auto *out = static_cast<std::uint8_t *>(destination);
    const auto *in = static_cast<const std::uint8_t *>(source);
    if (count <= 3) {
        if (count) {
            copy_group<1>(out, in);
            const auto middle = count >> 1;
            copy_group<1>(out + middle, in + middle);
            copy_group<1>(out + count - 1, in + count - 1);
        }
    } else if (count <= 15) {
        const auto middle = (count >> 1) & 4;
        const auto tail = count - 4 - middle;
        copy_group<4>(out, in);
        copy_group<4>(out + middle, in + middle);
        copy_group<4>(out + tail, in + tail);
        copy_group<4>(out + count - 4, in + count - 4);
    } else if (count <= 63) {
        const auto middle = (count >> 1) & 16;
        const auto tail = count - 16 - middle;
        copy_group<16>(out, in);
        copy_group<16>(out + middle, in + middle);
        copy_group<16>(out + tail, in + tail);
        copy_group<16>(out + count - 16, in + count - 16);
    } else {
        copy_group<16>(out, in);
        const auto alignment = reinterpret_cast<std::uintptr_t>(source) & 15;
        const auto vectors = (alignment + count - 16) >> 4;
        const auto groups = vectors >= 4 ? vectors & ~std::size_t{3} : 0;
        for (std::size_t i = 0; i < groups; i += 4) {
            const auto offset = 16 - alignment + i * 16;
            copy_group<16>(out + offset, in + offset);
            copy_group<16>(out + offset + 16, in + offset + 16);
            copy_group<16>(out + offset + 32, in + offset + 32);
            copy_group<16>(out + offset + 48, in + offset + 48);
        }
        for (auto i = groups; i < vectors; ++i) {
            const auto offset = 16 - alignment + i * 16;
            copy_group<16>(out + offset, in + offset);
        }
        copy_group<16>(out + count - 16, in + count - 16);
    }
    return destination;
}
