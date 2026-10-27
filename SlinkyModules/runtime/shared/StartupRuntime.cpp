// Instruction-backed recovery of AAFD0/AB050/AB070/AB080/AB0D0/4D0B0 and
// the exact FNINIT operation at12CCF0 from the supplied offline observation.
// See reports/StartupFunctionMapping.json and StartupVerification.json.
#include "StartupRuntime.hpp"
#include <cstring>

namespace reconstruction::startup {
namespace {
template<class T> T read(const void *pointer) {
  T value; std::memcpy(&value, pointer, sizeof value); return value;
}
template<class T> void write(void *pointer, T value) {
  std::memcpy(pointer, &value, sizeof value);
}
void *pointer(Word value) {
  return reinterpret_cast<void *>(std::uintptr_t(value));
}
}

// Ordinary captured TLS callback AAFD0. State is written for every reason.
// The native reason2 interval is exactly [2CB5C8,2CB5C8): it is empty even if
// callers modify nearby array storage. No initialization defaults are asserted.
void tlsCallback_aafd0(Word module, std::uint32_t reason, Word reserved,
                       std::uint8_t *image, const Dependencies &d) {
  auto *state = pointer(read<Word>(image + 0x2ba970));
  if (read<std::uint32_t>(state) != 2) write(state, std::uint32_t(2));
  if (reason == 1) d.lifecycle_f4730(d.context, module, 1, reserved);
}

// Ordinary captured TLS callback AB050. The tail target F4730 contains
// protected continuations, so its implementation remains a separate contract.
void tlsCallback_ab050(Word module, std::uint32_t reason, Word reserved,
                       std::uint8_t *, const Dependencies &d) {
  if (reason == 3 || reason == 0)
    d.lifecycle_f4730(d.context, module, reason, reserved);
}

Word startupStateAddress_ab070(std::uint8_t *image) {
  return std::uintptr_t(image + 0x2f65f0);
}

// AB080 reloads the mutable array cursor after each callback, advances that
// reloaded pointer, then reads the next target. The null slot is not advanced.
void runShutdownCallbacks_ab080(std::uint8_t *image, const Dependencies &d) {
  auto cursor = read<Word>(image + 0x2f65f8);
  auto target = read<Word>(pointer(cursor));
  while (target) {
    d.callback(d.context, target);
    cursor = read<Word>(image + 0x2f65f8) + Word(8);
    write(image + 0x2f65f8, cursor);
    target = read<Word>(pointer(cursor));
  }
}

// 4D0B0 forwards its callback in RDX and the image-owned registration record
// in RCX to the captured protected13D030 service. No CRT identity is guessed.
Word registerShutdown_4d0b0(Word callback, std::uint8_t *image,
                            const Dependencies &d) {
  return d.register_13d030(d.context, std::uintptr_t(image + 0x3065d0), callback);
}

// 12CCF0 contains only FNINIT between its stack-frame prolog/epilog. This
// architecture operation is explicit rather than guessed as a CRT routine.
void initializeX87_12ccf0(const ArchitectureOperations &operations) {
  operations.fninit(operations.context);
}

// AB0D0 writes its once guard before reading the initializer-table pointer.
// The -1 count case scans pointer slots1 onward. Calls use the retained table,
// in reverse order, then register the concrete AB080 shutdown callback token.
void runInitializers_ab0d0(std::uint8_t *image, const Dependencies &d) {
  if (image[0x3065e8]) return;
  image[0x3065e8] = 1;
  const auto table = read<Word>(image + 0x2ba978);
  auto count = read<std::uint32_t>(pointer(table));
  if (count == 0xffffffffu) {
    do {
      const auto index = count + 2u;
      ++count;
      if (!read<Word>(pointer(table + Word(index) * 8))) break;
    } while (true);
  }
  if (count) {
    Word index = Word(count) - 1;
    for (;;) {
      d.callback(d.context, read<Word>(pointer(table + (index + 1) * 8)));
      const auto previous = std::uint32_t(index);
      --index;
      if (!previous) break;
    }
  }
  registerShutdown_4d0b0(std::uintptr_t(image + 0xab080), image, d);
}
}
