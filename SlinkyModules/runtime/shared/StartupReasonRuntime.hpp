#ifndef SLINKY_SHARE_C61C3CCCE49F0760C375
#define SLINKY_SHARE_C61C3CCCE49F0760C375
#include "StartupRuntime.hpp"

namespace reconstruction::startup {
// Exact captured transforms and export identities are recorded separately
// from this caller-owned, portable representation of their ABI.
struct NativeServices {
    const std::uint8_t *image;
    const std::uint8_t *initializeCell = nullptr;
    const std::uint8_t *deleteCell = nullptr;
    const std::uint8_t *enterCell = nullptr;
    const std::uint8_t *leaveCell = nullptr;
    const std::uint8_t *tlsCell = nullptr;
    const std::uint8_t *lastErrorCell = nullptr;
    const std::uint8_t *freeCell = nullptr;
    std::int32_t initialize(void *section) const;
    std::int32_t destroy(void *section) const;
    std::int32_t enter(void *section) const;
    std::int32_t leave(void *section) const;
    using TlsEndpoint = Word (*)(std::uint32_t);
    using ErrorEndpoint = std::uint32_t (*)();
    TlsEndpoint resolveTls() const;
    ErrorEndpoint resolveLastError() const;
    void release(void *node) const;
};

struct CallbackOperations {
    void *context;
    // An arbitrary node callback token needs an explicit callable binding.
    void (*invoke)(void *, Word target, Word value);
};
Word lifecycle_f4730(std::uint32_t reason, std::uint8_t *image,
                     const NativeServices &, const ArchitectureOperations &,
                     const CallbackOperations &);

// Compose this frame with the ordinary TLS/initializer dependencies. The
// All four reasons use the reconstructed body and caller-owned services.
struct BoundLifecycleDependencies {
    const Dependencies &source;
    std::uint8_t *image;
    const NativeServices &services;
    const ArchitectureOperations &architecture;
    const CallbackOperations &callbacks;
    Dependencies value;
    BoundLifecycleDependencies(const Dependencies &original,
        std::uint8_t *borrowedImage, const NativeServices &native,
        const ArchitectureOperations &operations, const CallbackOperations &nodes)
        :source(original),image(borrowedImage),services(native),
         architecture(operations),callbacks(nodes),value{this,callback,lifecycle,registration} {}
    BoundLifecycleDependencies(const BoundLifecycleDependencies &) = delete;
    static void callback(void *, Word target);
    static void lifecycle(void *, Word module, std::uint32_t reason, Word reserved);
    static Word registration(void *, Word state, Word callback);
};
}
#endif // SLINKY_SHARE_C61C3CCCE49F0760C375
