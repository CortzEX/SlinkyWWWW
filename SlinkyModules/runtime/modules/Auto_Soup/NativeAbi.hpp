#ifndef SLINKY_SHARE_AF2CEAD1D0B7970C3411
#define SLINKY_SHARE_AF2CEAD1D0B7970C3411
// Source-equivalent reconstruction from supplied native recovery evidence.
// Semantic names were assigned during reverse engineering. Original locals,
// class spelling, namespaces, templates and inline boundaries are not
// recovered. Algorithms below are expressed directly from the supplied C
// behavior bodies. External calls preserve explicit native ABI boundaries and
// exact RVAs. Historical finite verification is not a newly rerun equivalence
// claim. Named setting labels/options come from the separately identified
// runtime observation; captured current/saved values are never treated as
// defaults.
#ifndef AUTO_SOUP_H
#define AUTO_SOUP_H
#include "../../shared/OwnedNativeBindings.hpp"
#include <stdint.h>
typedef struct soup_args {
  uint64_t rcx, rdx, r8, r9, xmm0, xmm1, xmm2;
  /* Original stack argument 5; the indirect item call uses this field to expose
   * its loaded target. */
  uint64_t stack5;
} soup_args;
typedef struct soup_result {
  uint64_t rax, xmm0;
} soup_result;
struct soup_dispatch {
  reconstruction::native_binding::Context &native;
  void (*unresolved)(uint32_t, const soup_args *, soup_result *, void *);
  void operator()(uint32_t rva, const soup_args *args, soup_result *result,
                  void *user) const {
    uint64_t g[4] = {args->rcx, args->rdx, args->r8, args->r9},
             x[4] = {args->xmm0, args->xmm1, args->xmm2, 0},
             st[2] = {args->stack5, 0};
    reconstruction::native_binding::Value value;
    if (reconstruction::native_binding::resolveFrame(native, rva, g, x, st,
                                                     value)) {
      if (value.floating) {
        result->xmm0 = value.bits;
        result->rax = 0;
      } else {
        result->rax = value.bits;
        result->xmm0 = 0;
      }
      return;
    }
    unresolved(rva, args, result, user);
  }
};
void recovered_auto_soup_2d510(uint8_t *event, uint8_t *image,
                               soup_dispatch call, void *user);
void recovered_auto_soup_2dae0(uint8_t *event, uint8_t *image);
void recovered_auto_soup_2db10(uint8_t *event, uint8_t *image);
#endif
#endif // SLINKY_SHARE_AF2CEAD1D0B7970C3411
