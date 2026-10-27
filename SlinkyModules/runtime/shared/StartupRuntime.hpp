#ifndef SLINKY_SHARE_64C2C8EF318D2E529CCF
#define SLINKY_SHARE_64C2C8EF318D2E529CCF
// Recovered from the supplied lib_win runtime observation at base7FFBFB3B0000.
// Ordinary RVA contracts and original-file TLS provenance are recorded in
// reports/StartupFunctionMapping.json; captured state is never a default.

#include <cstdint>

namespace reconstruction::startup {
using Word = std::uint64_t;
struct Dependencies {
  void *context;
  // Synthetic/host callbacks are explicit services. Captured addresses are
  // tokens, never cast to a native function by these reconstructed bodies.
  void (*callback)(void *, Word target);
  void (*lifecycle_f4730)(void *, Word module, std::uint32_t reason, Word reserved);
  Word (*register_13d030)(void *, Word state, Word callback);
};
struct ArchitectureOperations {
  void *context;
  // Execute the single FNINIT operation: reset only x87 environment, with
  // its native non-waiting semantics. SSE/MXCSR must remain unchanged.
  void (*fninit)(void *);
};

void tlsCallback_aafd0(Word module, std::uint32_t reason, Word reserved,
                       std::uint8_t *image, const Dependencies &);
void tlsCallback_ab050(Word module, std::uint32_t reason, Word reserved,
                       std::uint8_t *image, const Dependencies &);
Word startupStateAddress_ab070(std::uint8_t *image);
void runShutdownCallbacks_ab080(std::uint8_t *image, const Dependencies &);
void runInitializers_ab0d0(std::uint8_t *image, const Dependencies &);
Word registerShutdown_4d0b0(Word callback, std::uint8_t *image,
                            const Dependencies &);
void initializeX87_12ccf0(const ArchitectureOperations &);
}
#endif // SLINKY_SHARE_64C2C8EF318D2E529CCF
