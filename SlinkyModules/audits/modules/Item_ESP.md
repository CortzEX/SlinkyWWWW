# Item ESP reconstruction

Registration: `registered`. Candidate interval: ['0x40de0', '0x41a90'].

The algorithm bodies below reuse the supplied recovered C/C++ implementation. Semantic function names are inferred. Native data offsets, raw byte/DWORD tests, operation order, endpoint identities and explicit scalar/SSE arithmetic are retained. C++ casts and lexical scopes were adjusted where the supplied C-derived component failed C++ compilation. No startup state or live registry wiring was added.

## Source evidence

- `recovered_cpp/behavior/module_behavior_recovery/item_esp/item_esp.cpp`, SHA-256 `ecddfb5edfe4a030d02b43b85429f85a84dc8f9e8b2ffb3e4049847e33a2997b`. Manifest field `cpp_differentially_verified` is false; this is an unrerun component, not a recorded failing comparison.
- `recovered_cpp/behavior/module_behavior_recovery/item_esp_update/item_esp_update.cpp`, SHA-256 `aca9dd71e36ce3864d5be462f19cfe1a47df01d0d95692a658deb16c7a634afd`. Manifest field `cpp_differentially_verified` is false; this is an unrerun component, not a recorded failing comparison.
- Shared UI/configuration source: `native/verified/surfaces/Surface_Item_ESP.cpp`, copied with identical bytes.

## Function accounting

| Native RVA | Kind | Implementation status |
| --- | --- | --- |
| `0x40de0` | callback | Algorithm body: `renderItems` |
| `0x41250` | callback | Algorithm body: `updateItems` |
| `0x416c0` | callback | Algorithm body: `onLifecycleEvent` |
| `0x41700` | ui | Reused verified shared surface |
| `0x417b0` | settings | Reused verified shared surface |
| `0x41830` | candidate_local | Algorithm body: `compareItemIdentifier`; exact typed variant also reused as `recovered_esp_list_compare` |
| `0x41840` | candidate_local | Algorithm body: `appendCatalogCharacter` |
| `0x41890` | candidate_local | Exact reuse: `recovered_esp_list_count` |
| `0x418a0` | candidate_local | Exact reuse: `recovered_esp_list_name` |
| `0x418c0` | candidate_local | Exact reuse: `recovered_esp_list_color` |
| `0x418e0` | candidate_local | Exact reuse: `recovered_item_esp_list_add` |
| `0x41a20` | candidate_local | Exact reuse: `recovered_item_esp_list_remove` |
| `0x41a60` | candidate_local | Exact reuse: `recovered_item_esp_list_clear`; named raw ABI body `releaseBuffer` |

## Instruction audit and reuse

`CatalogInput.cpp` implements RVA `0x41840` with the same alphabetic/space/decimal byte filter compiled at Block ESP `0x3ffb0`. The callback overwrites the string terminator and does not write a replacement terminator. RVA `0x41830` compares item identifiers by wrapping DWORD subtraction, so its name was corrected to `compareItemIdentifier`. `Buffer.cpp` provides the native raw buffer-clear ABI at `0x41a60`; the exact typed implementation is also reused from `module_esp_lists.cpp`. The shared list report covers count/name/color/add/remove/clear/compare behavior.

## Source organization

`Module.hpp` declares the recovered algorithms and named settings storage offsets. Offsets combine the config key setting address from `MetadataCatalog.json` with `offsetof` from the recovered setting structs. The metadata is runtime evidence and no current or saved value is installed as a startup default. Typed record layouts use static assertions where the supplied source establishes their sizes.

| Implementation file | SHA-256 |
| --- | --- |
| `Buffer.cpp` | `6e28bdd2222b72d35aa2680db93ac67c039c65984cf3f3d33c465942fc709fe6` |
| `CatalogInput.cpp` | `a27335f393ca1a2c00b6ef9fb98d23e5f9c7f86036855d3b1583676a58f4edcf` |
| `item_esp.cpp` | `6fe9c4dfb1e7ea75ce5a9187a143b784876de8acc4200fb4e316e94b2d2c72c7` |
| `item_esp_update.cpp` | `8df5ac0b28c30c5265a01c54c77630e90032606ec9872829a20140bf17d1e7ed` |
| `Module.hpp` | `581c00661e759b58bb966f629854cc309c13687f4334c895e7e4ebd4d3b917f0` |

## Boundaries and verification

The 28 newly organized algorithm translation units across this rendering/interface group pass clang-cl 22.1.8 with C++20, `/EHsc /fp:strict /Zs`. The group check took 8.02 seconds; two declaration attribute warnings were corrected and the affected source rechecked without warnings. Block ESP was rechecked after wiring the local helpers directly; all three sources pass. Local quoted includes resolve. The 206 copied clean files remain byte-identical to evidence. These checks compile the reconstruction; they do not execute the supplied binary or recovered callbacks.

The new names, C++ repairs and native-instruction reconstructions have not been differentially rerun. Historical comparison reports cover their stated controlled paths and do not prove live scheduling, startup initialization, Java, graphics, fonts, JSON, allocation ownership or concurrency. Source-present shared numerical/text/render routines are separate reconstruction work, not an absence of evidence. Genuine game/JNI, CRT and graphics/font backend calls remain dependency contracts. No callback uses an invented default state.

<!-- SHARED_SCOPE_DOCUMENTARY_AUDIT -->
## Current shared-scope documentary audit

This appendix supersedes older helper-progress and copy-preservation statements above. Historical reports apply only to their recorded source versions and scopes.

The Item ESP interval has 13 accounted function rows: 11 direct bodies/ABI ports, 2 shared surfaces and 0 excluded/corrected-owner rows. Registration is `registered` with 3 callback slots. **local_accounting_complete=true**, local pending=0; ordinary local rows have concrete bodies/shared surfaces or explicit ownership exclusions. **whole_module_native_equivalence=false**. Local completeness is separate from shared contract review.

The supplied direct graph lists 43 helper/container targets (41 concrete_resolver_binding, 1 indirect_external_cell, 1 protected_transfer). Body/index/resolver accounting is not independent proof of every caller ABI or complete transitive behavior.

Established captured contracts: 0x13d0e0 to ucrtbase.dll!bsearch. Static proofs establish exact argument/result lanes, saved-state restoration and each entry's continuation, including any return adjustment or caller stack compensation. Permanent startup binding and external engine implementation remain separate evidence limits; these frame analyses are closed. External cells in this direct graph: 0x13cf70. Exact captured allocator destinations are now identified in ExternalCellObservation.json; startup permanence is separate.

Ordinary shared path, FontStash, atlas, glyph/cache/packing, font-table/TT/CFF outline and raster bodies are concrete. Scoped checks: path 1,832; FontStash 640; atlas 34; glyph/cache/packing 127; font tables/outlines 1,275; CFF 2,362; curves/sort 328; raster/wrapper 225; float-log/Gaussian 3,814; six ordinary startup helpers 240; F4730 lifecycle/bound services 508; Window query/caller routes 353 (336 ordinary comparisons and 17 decoded-cell/full-Word contracts). Protected entries are intercepted before execution, and Window tests use synthetic endpoints with no OS input. The font ledger identifies 42 named transitive entries with no ordinary font pending rows. Controlled provider comparisons remain scoped; final protected/caller/startup analysis is separate. Common modal has 97 cases, color section 2,122 and profile transitions 126, without claiming complete UI equivalence.

[The ordinary raster CPU supplement](../FontRasterizerCpuVerification.json) has 225 captured-body versus rebuilt CPU memory/trace/default-MXCSR matches with controlled providers and declared arena-address normalization. All 215 CPU/emulator MXCSR differences remain recorded in the unchanged raw report; the CPU results agree in every supplied fixture. Its executable mapping contains only seven fixed ordinary bodies, controlled shape/box/error stubs and INT3 elsewhere. Masked exceptions and default MXCSR only are tested; startup, protected dispatch, OS/JVM/driver services, other rounding/DAZ/FTZ, traps, faults and concurrency are outside this scope.

The established captured-contract register contains 27 entries (26 service/resolver leaves plus the F4730 body), with 4 separate pending GUI/original-TLS/original-PE/provenance rows. Newly integrated ordinary C220/C290/4C7B0 GUI composition and captured DCDBE0 directory-service contract have 65 profile-action, 50 composition, 66 rendering-route and 91 adapter cases. C290 opens the profile directory; no Windows service executes in these fixtures. DCDBE0/cellACC76A are transitive additions outside the original415/1,995 catalogues. Current complete static-library and whole-object link snapshots pass with stable source sets including this batch. The available original TLS worksheet now tracks all seventeen saved register/flags words through a second physical layout; preferred-base/original-zero and captured-base/observed-bias bootstrap effects agree, with captured patch writer/order still unproved.

The broad GUI continuation worker stopped after content-safety screening for possible cybersecurity risk. Further broad continuation is paused at the stable126-packet/89-prefix checkpoint7716F8, with a separate86-record root physical scratch/parity audit. A separate759FC6 worksheet is provisional. The pause does not imply missing bytes or irrecoverability. This delivery remains incomplete with four pending rows; no new broad protected-initialization continuation is claimed.

The PE continuation worker also stopped after content-safety screening for possible cybersecurity risk. Further continuation is paused without retry. Its preserved stable worksheet records 2,875 selected fingerprints, next handler `captured_base+153126C`, stream `0x7ffbfd90ff7a`, key `0x770730978aeb950e`, `RSP=F` and `RDI=C-8, C=(S-8)&~40`. This is a tooling stop, not missing evidence or an irrecoverability conclusion; complete original PE effects remain pending. TLS stays at its separately saved checkpoint.

All four original inputs and all 480 extracted files match their recorded hashes/ZIP bytes. The retained working checkpoint is **202 byte-identical + four hash-pinned approved adaptations**: the two module_surface files add caller-owned UI frames; the two module_list_storage files preserve E310's calloc `(8 records, record stride)` contract. Evidence originals remain unchanged. Claims that all 206 retained files are unchanged are superseded. Runtime metadata/values remain observations, never startup defaults.

Current build/check snapshot status is recorded in [VERIFICATION_STATUS](../../VERIFICATION_STATUS.md). Syntax/link and finite helper traces do not prove the entire module, startup, real JNI/graphics, all pointer faults/concurrency or all FP modes. Available protected/startup analysis and concrete caller reviews persist in [PENDING_RECOVERY](../../PENDING_RECOVERY.md); actual evidence limits are separately stated in [UNRESOLVED](../../UNRESOLVED.md). See [README](../../README.md), [GLOBAL_AUDIT](../../GLOBAL_AUDIT.md) and [EvidencePreservation](../EvidencePreservation.md).

Selected independent GUI, PE, TLS-header and Window static reviews have a separate [input-integrity ledger](../IndependentStaticAuditInputs.md). The [TLS worksheet chain](../TlsStaticProofInputIntegrity.md) also pins its recorded inputs. [The preserved PE report's integrity audit](../PeStaticProofInputIntegrity.md) checks 44 declared hashes for its 2,875 selected records without proof replay or new-byte interpretation. These read-only consistency checks do not execute original/protected code or close the full GUI, original TLS or PE entry; the current fixed-prefix checkpoints remain available analysis in PendingAnalysis.json.
