# Mod Overlay reconstruction

Registration: `registered`. Candidate interval: ['0x34080', '0x35000'].

The algorithm bodies below reuse the supplied recovered C/C++ implementation. Semantic function names are inferred. Native data offsets, raw byte/DWORD tests, operation order, endpoint identities and explicit scalar/SSE arithmetic are retained. C++ casts and lexical scopes were adjusted where the supplied C-derived component failed C++ compilation. No startup state or live registry wiring was added.

## Source evidence

- `recovered_cpp/behavior/module_behavior_recovery/mod_overlay_extended/mod_overlay.cpp`, SHA-256 `fe7fb5d6a0053f8b090c98064d62f27bcf795ede61934967e430784079867a46`. Manifest field `cpp_differentially_verified` is false; this is an unrerun component, not a recorded failing comparison.
- `recovered_cpp/behavior/module_behavior_recovery/mod_overlay_render/mod_overlay_render.cpp`, SHA-256 `51fde7512b0ab23020613e05bf4d00b7ba893e65b0cdb9c8ce94977f724ea645`. Manifest field `cpp_differentially_verified` is false; this is an unrerun component, not a recorded failing comparison.
- Shared UI/configuration source: `native/verified/surfaces/Surface_Mod_Overlay.cpp`, copied with identical bytes.

## Function accounting

| Native RVA | Kind | Implementation status |
| --- | --- | --- |
| `0x34080` | callback | Algorithm body: `onSettingChanged` |
| `0x34290` | callback | Algorithm body: `onModuleStateChanged` |
| `0x344d0` | callback | Algorithm body: `onStatusEvent` |
| `0x34510` | callback | Algorithm body: `renderOverlay` |
| `0x349f0` | callback | Algorithm body: `onControlEvent` |
| `0x34a10` | callback | Algorithm body: `collectModules` |
| `0x34a40` | ui | Reused verified shared surface |
| `0x34b90` | settings | Reused verified shared surface |
| `0x34ce0` | candidate_local | Algorithm body: `refreshVisibleModules` |
| `0x34e90` | candidate_local | Algorithm body: `appendModule`; two captured character resolver contracts are concrete |
| `0x34fb0` | candidate_local | Algorithm body: `compareWidth` |
| `0x34ff0` | candidate_local | Ownership corrected to Notifications: `clearHandshake` |

## Instruction audit and reuse

`ModuleCollection.cpp` implements the ordinary paths at `0x34ce0` and `0x34e90`. `refreshVisibleModules` preserves different byte comparisons in the two passes, category gating, registry-count reloads after callbacks, and re-enabling existing records. `appendModule` preserves width/progress initialization, dynamic status callbacks and count reloads. Fresh static proofs and canonical borrowed-cell source close the actual `0x32ecfb` name and `0xbb8f39` status resolver contracts. The separate collectModules `0xe6314d` name resolver and per-byte `0xe28595` status tail service are also concrete, each preserving its captured cell reload policy. Exact captured ucrtbase!tolower behavior remains an external service. RVA `0x34ff0` was placed near this interval in the input but its byte at `0x2fbfb0` belongs to Notifications, whose new `Handshake.cpp` provides the atomic exchange body.

## Source organization

`Module.hpp` declares the recovered algorithms and named settings storage offsets. Offsets combine the config key setting address from `MetadataCatalog.json` with `offsetof` from the recovered setting structs. The metadata is runtime evidence and no current or saved value is installed as a startup default. Typed record layouts use static assertions where the supplied source establishes their sizes.

| Implementation file | SHA-256 |
| --- | --- |
| `mod_overlay_extended.cpp` | `0375506b895fb781abc5614cfddc92e69619bbcf4dc2be72cfb6b03ca1694253` |
| `mod_overlay_render.cpp` | `6a2e75ae8e82330bfb7478c70ef31069189713d55bbf12c4be3aa6f6a5cff6de` |
| `Module.hpp` | `ce52095105808eccb414b8a6ef9750b1c1be66186761316c162207555551419f` |
| `ModuleCollection.cpp` | `5b1c6cb5248dab1ebda20903b67223a874b0d92b4149581495f994542416f9f0` |

## Boundaries and verification

The 28 newly organized algorithm translation units across this rendering/interface group pass clang-cl 22.1.8 with C++20, `/EHsc /fp:strict /Zs`. The group check took 8.02 seconds; two declaration attribute warnings were corrected and the affected source rechecked without warnings. Block ESP was rechecked after wiring the local helpers directly; all three sources pass. Local quoted includes resolve. The 206 copied clean files remain byte-identical to evidence. These checks compile the reconstruction; they do not execute the supplied binary or recovered callbacks.

The new names, C++ repairs and native-instruction reconstructions have not been differentially rerun. Historical comparison reports cover their stated controlled paths and do not prove live scheduling, startup initialization, Java, graphics, fonts, JSON, allocation ownership or concurrency. Source-present shared numerical/text/render routines are separate reconstruction work, not an absence of evidence. Genuine game/JNI, CRT and graphics/font backend calls remain dependency contracts. The protected character provider is an unresolved protected boundary. No callback uses an invented default state.


The later character routing follow-up is in `ModOverlayCharacterBindings.json`. The actual append/collect caller suite passes1,038 controlled checks without protected or captured-engine execution. `ModOverlayDependencies` appends a borrowed encoded-cell override for partial images; the canonical paths use concrete resolvers rather than its retained character compatibility fields.

<!-- SHARED_SCOPE_DOCUMENTARY_AUDIT -->
## Current shared-scope documentary audit

This appendix supersedes older helper-progress and copy-preservation statements above. Historical reports apply only to their recorded source versions and scopes.

The Mod Overlay interval has 12 accounted function rows: 9 direct bodies/ABI ports, 2 shared surfaces and 1 excluded/corrected-owner rows. Registration is `registered` with 6 callback slots. **local_accounting_complete=true**, local pending=0; ordinary local rows have concrete bodies/shared surfaces or explicit ownership exclusions. **whole_module_native_equivalence=false**. Local completeness is separate from shared contract review.

The supplied direct graph lists 29 helper/container targets (23 concrete_resolver_binding, 6 protected_transfer). Body/index/resolver accounting is not independent proof of every caller ABI or complete transitive behavior.

Captured protected transforms: 0x32ecf3 actual entry 0x32ecfb. Complete saved-frame/target-chain/effect analysis remains pending, with available bytes and no irrecoverability claim. Established captured contracts: 0x13d0a0 to ucrtbase.dll!strcmp, 0x13d0f0 to ucrtbase.dll!qsort, 0xbb8f39 to ucrtbase.dll!tolower, 0xe28595 to ucrtbase.dll!tolower, 0xe6314d to ucrtbase.dll!tolower. Static proofs establish exact argument/result lanes, saved-state restoration and each entry's continuation, including any return adjustment or caller stack compensation. Permanent startup binding and external engine implementation remain separate evidence limits; these frame analyses are closed.

Ordinary shared path, FontStash, atlas, glyph/cache/packing, font-table/TT/CFF outline and raster bodies are concrete. Scoped checks: path 1,832; FontStash 640; atlas 34; glyph/cache/packing 127; font tables/outlines 1,275; CFF 2,362; curves/sort 328; raster/wrapper 225; float-log/Gaussian 3,814; six ordinary startup helpers 240; F4730 lifecycle/bound services 508; Window query/caller routes 353 (336 ordinary comparisons and 17 decoded-cell/full-Word contracts). Protected entries are intercepted before execution, and Window tests use synthetic endpoints with no OS input. The font ledger identifies 42 named transitive entries with no ordinary font pending rows. Controlled provider comparisons remain scoped; final protected/caller/startup analysis is separate. Common modal has 97 cases, color section 2,122 and profile transitions 126, without claiming complete UI equivalence.

[The ordinary raster CPU supplement](../FontRasterizerCpuVerification.json) has 225 captured-body versus rebuilt CPU memory/trace/default-MXCSR matches with controlled providers and declared arena-address normalization. All 215 CPU/emulator MXCSR differences remain recorded in the unchanged raw report; the CPU results agree in every supplied fixture. Its executable mapping contains only seven fixed ordinary bodies, controlled shape/box/error stubs and INT3 elsewhere. Masked exceptions and default MXCSR only are tested; startup, protected dispatch, OS/JVM/driver services, other rounding/DAZ/FTZ, traps, faults and concurrency are outside this scope.

The established captured-contract register contains 27 entries (26 service/resolver leaves plus the F4730 body), with 4 separate pending GUI/original-TLS/original-PE/provenance rows. Newly integrated ordinary C220/C290/4C7B0 GUI composition and captured DCDBE0 directory-service contract have 65 profile-action, 50 composition, 66 rendering-route and 91 adapter cases. C290 opens the profile directory; no Windows service executes in these fixtures. DCDBE0/cellACC76A are transitive additions outside the original415/1,995 catalogues. Current complete static-library and whole-object link snapshots pass with stable source sets including this batch. The available original TLS worksheet now tracks all seventeen saved register/flags words through a second physical layout; preferred-base/original-zero and captured-base/observed-bias bootstrap effects agree, with captured patch writer/order still unproved.

The broad GUI continuation worker stopped after content-safety screening for possible cybersecurity risk. Further broad continuation is paused at the stable126-packet/89-prefix checkpoint7716F8, with a separate86-record root physical scratch/parity audit. A separate759FC6 worksheet is provisional. The pause does not imply missing bytes or irrecoverability. This delivery remains incomplete with four pending rows; no new broad protected-initialization continuation is claimed.

The PE continuation worker also stopped after content-safety screening for possible cybersecurity risk. Further continuation is paused without retry. Its preserved stable worksheet records 2,875 selected fingerprints, next handler `captured_base+153126C`, stream `0x7ffbfd90ff7a`, key `0x770730978aeb950e`, `RSP=F` and `RDI=C-8, C=(S-8)&~40`. This is a tooling stop, not missing evidence or an irrecoverability conclusion; complete original PE effects remain pending. TLS stays at its separately saved checkpoint.

All four original inputs and all 480 extracted files match their recorded hashes/ZIP bytes. The retained working checkpoint is **202 byte-identical + four hash-pinned approved adaptations**: the two module_surface files add caller-owned UI frames; the two module_list_storage files preserve E310's calloc `(8 records, record stride)` contract. Evidence originals remain unchanged. Claims that all 206 retained files are unchanged are superseded. Runtime metadata/values remain observations, never startup defaults.

Current build/check snapshot status is recorded in [VERIFICATION_STATUS](../../VERIFICATION_STATUS.md). Syntax/link and finite helper traces do not prove the entire module, startup, real JNI/graphics, all pointer faults/concurrency or all FP modes. Available protected/startup analysis and concrete caller reviews persist in [PENDING_RECOVERY](../../PENDING_RECOVERY.md); actual evidence limits are separately stated in [UNRESOLVED](../../UNRESOLVED.md). See [README](../../README.md), [GLOBAL_AUDIT](../../GLOBAL_AUDIT.md) and [EvidencePreservation](../EvidencePreservation.md).

Selected independent GUI, PE, TLS-header and Window static reviews have a separate [input-integrity ledger](../IndependentStaticAuditInputs.md). The [TLS worksheet chain](../TlsStaticProofInputIntegrity.md) also pins its recorded inputs. [The preserved PE report's integrity audit](../PeStaticProofInputIntegrity.md) checks 44 declared hashes for its 2,875 selected records without proof replay or new-byte interpretation. These read-only consistency checks do not execute original/protected code or close the full GUI, original TLS or PE entry; the current fixed-prefix checkpoints remain available analysis in PendingAnalysis.json.
