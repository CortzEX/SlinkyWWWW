#ifndef SLINKY_SHARE_42758F3EF8B71EA4CC07
#define SLINKY_SHARE_42758F3EF8B71EA4CC07
// Compatibility declaration for the existing verified registry implementation.
// The implementation and native layout remain unchanged.
#include "../native/verified/module_runtime.hpp"

extern "C" __declspec(dllexport) std::uint64_t recovered_initialize_module_registry(
    ModuleRegistry *registry, void *context, const std::uint8_t *const modules[66],
    const RegistryDependencies *deps);
#endif // SLINKY_SHARE_42758F3EF8B71EA4CC07
