# Name Tags reconstruction

Registration: `registered`. Candidate interval: ['0x3c210', '0x3da80'].

The algorithm bodies below reuse the supplied recovered C/C++ implementation. Semantic function names are inferred. Native data offsets, raw byte/DWORD tests, operation order, endpoint identities and explicit scalar/SSE arithmetic are retained. C++ casts and lexical scopes were adjusted where the supplied C-derived component failed C++ compilation. No startup state or live registry wiring was added.

## Source evidence

- `recovered_cpp/behavior/module_behavior_recovery/name_tags/name_tags.cpp`, SHA-256 `0ea8ab2ba5628609a793cae8e4d03075be0dfe7f99e49e0c9a38e526a75c5547`. Manifest field `cpp_differentially_verified` is false; this is an unrerun component, not a recorded failing comparison.
- `recovered_cpp/behavior/module_behavior_recovery/name_tags_update/name_tags_update.cpp`, SHA-256 `85a10e22bb2986eaca972bbfc061271c1117adc0ce9846d2cb89d20bf7ffd4d1`. Manifest field `cpp_differentially_verified` is false; this is an unrerun component, not a recorded failing comparison.
- Shared UI/configuration source: `native/verified/surfaces/Surface_Name_Tags.cpp`, copied with identical bytes.

## Function accounting

| Native RVA | Kind | Implementation status |
| --- | --- | --- |
| `0x3c210` | callback | Algorithm body: `onLifecycleEvent` |
| `0x3c280` | callback | Algorithm body: `renderTags` |
| `0x3ca20` | callback | Algorithm body: `updateTags` |
| `0x3d5b0` | ui | Reused verified shared surface |
| `0x3d6e0` | settings | Reused verified shared surface |
| `0x3d800` | candidate_local | Algorithm body: `releaseTags` |
| `0x3da40` | candidate_local | Algorithm body: `compareDistance` |
| `0x3da60` | candidate_local | Algorithm body: `compareEnchantment` |

## Instruction audit and reuse

The supplied callback bodies are retained with semantic names and explicit C++ pointer conversions. No additional proximity candidates remain in this module interval.

## Source organization

`Module.hpp` declares the recovered algorithms and named settings storage offsets. Offsets combine the config key setting address from `MetadataCatalog.json` with `offsetof` from the recovered setting structs. The metadata is runtime evidence and no current or saved value is installed as a startup default. Typed record layouts use static assertions where the supplied source establishes their sizes.

| Implementation file | SHA-256 |
| --- | --- |
| `Module.hpp` | `88f8a85b9d1c849b875e05fc04e631fe2410509025b0ca9164c1f6def931a6dd` |
| `name_tags.cpp` | `77426b9a61b72c81c617e0f5e5a57ea438debb134b7080761f3f6eba074a0922` |
| `name_tags_update.cpp` | `1107157095f78b216beac4af578df4e270fab199bbe918b890c1b22c06e8834c` |

## Boundaries and verification

The 28 newly organized algorithm translation units across this rendering/interface group pass clang-cl 22.1.8 with C++20, `/EHsc /fp:strict /Zs`. The group check took 8.02 seconds; two declaration attribute warnings were corrected and the affected source rechecked without warnings. Block ESP was rechecked after wiring the local helpers directly; all three sources pass. Local quoted includes resolve. The 206 copied clean files remain byte-identical to evidence. These checks compile the reconstruction; they do not execute the supplied binary or recovered callbacks.

The new names, C++ repairs and native-instruction reconstructions have not been differentially rerun. Historical comparison reports cover their stated controlled paths and do not prove live scheduling, startup initialization, Java, graphics, fonts, JSON, allocation ownership or concurrency. Source-present shared numerical/text/render routines are separate reconstruction work, not an absence of evidence. Genuine game/JNI, CRT and graphics/font backend calls remain dependency contracts. No callback uses an invented default state.

## Additional native query and helper recovery

Native accounting: 0x3c1a0 `queryNameTagValue`.

The owning enabled byte is 0x2f02e4, in Name Tags descriptor 0x2f02d0. It is not a Friends function despite interval proximity. The ordinary 0x274c0 tail helper is expanded into the JNI slot 0x128 call using metadata field 0x978. Runtime instructions pass four JNI arguments and do not pass the decompiler's uninitialized RBP value. The eligibility helpers are explicit game boundaries.

- `modules/Name_Tags/Query.cpp`, SHA-256 `8f32968543f4f4c23d792efafcb060c5d64e477688443b9992f84f56dd280d65`.
- `modules/Name_Tags/Query.hpp`, SHA-256 `6a6056f821a79351fccb65daf0b6ce195c819a5d022da5b7d5d8b0def29f35ea`.

The new source is an instruction-audited reconstruction, not original source spelling. Forty-four sources in the assigned and follow-up directories pass clang-cl C++20 `/EHsc /fp:strict /Zs` in 10.06 seconds with no diagnostics. No new original-instruction differential execution was performed, and no startup defaults were supplied.

<!-- SHARED_SCOPE_DOCUMENTARY_AUDIT -->
## Current shared-scope documentary audit

This appendix supersedes older helper-progress and copy-preservation statements above. Historical reports apply only to their recorded source versions and scopes.

The Name Tags interval has 8 accounted function rows: 6 direct bodies/ABI ports, 2 shared surfaces and 0 excluded/corrected-owner rows. Registration is `registered` with 3 callback slots. **local_accounting_complete=true**, local pending=0; ordinary local rows have concrete bodies/shared surfaces or explicit ownership exclusions. **whole_module_native_equivalence=false**. Local completeness is separate from shared contract review.

The supplied direct graph lists 68 helper/container targets (65 concrete_resolver_binding, 2 indirect_external_cell, 1 protected_transfer). Body/index/resolver accounting is not independent proof of every caller ABI or complete transitive behavior.

Established captured contracts: 0x13d0f0 to ucrtbase.dll!qsort. Static proofs establish exact argument/result lanes, saved-state restoration and each entry's continuation, including any return adjustment or caller stack compensation. Permanent startup binding and external engine implementation remain separate evidence limits; these frame analyses are closed. External cells in this direct graph: 0x13cf60, 0x13cf70. Exact captured allocator destinations are now identified in ExternalCellObservation.json; startup permanence is separate.

Ordinary shared path, FontStash, atlas, glyph/cache/packing, font-table/TT/CFF outline and raster bodies are concrete. Scoped checks: path 1,832; FontStash 640; atlas 34; glyph/cache/packing 127; font tables/outlines 1,275; CFF 2,362; curves/sort 328; raster/wrapper 225; float-log/Gaussian 3,814; six ordinary startup helpers 240; F4730 lifecycle/bound services 508; Window query/caller routes 353 (336 ordinary comparisons and 17 decoded-cell/full-Word contracts). Protected entries are intercepted before execution, and Window tests use synthetic endpoints with no OS input. The font ledger identifies 42 named transitive entries with no ordinary font pending rows. Controlled provider comparisons remain scoped; final protected/caller/startup analysis is separate. Common modal has 97 cases, color section 2,122 and profile transitions 126, without claiming complete UI equivalence.

[The ordinary raster CPU supplement](../FontRasterizerCpuVerification.json) has 225 captured-body versus rebuilt CPU memory/trace/default-MXCSR matches with controlled providers and declared arena-address normalization. All 215 CPU/emulator MXCSR differences remain recorded in the unchanged raw report; the CPU results agree in every supplied fixture. Its executable mapping contains only seven fixed ordinary bodies, controlled shape/box/error stubs and INT3 elsewhere. Masked exceptions and default MXCSR only are tested; startup, protected dispatch, OS/JVM/driver services, other rounding/DAZ/FTZ, traps, faults and concurrency are outside this scope.

The established captured-contract register contains 27 entries (26 service/resolver leaves plus the F4730 body), with 4 separate pending GUI/original-TLS/original-PE/provenance rows. Newly integrated ordinary C220/C290/4C7B0 GUI composition and captured DCDBE0 directory-service contract have 65 profile-action, 50 composition, 66 rendering-route and 91 adapter cases. C290 opens the profile directory; no Windows service executes in these fixtures. DCDBE0/cellACC76A are transitive additions outside the original415/1,995 catalogues. Current complete static-library and whole-object link snapshots pass with stable source sets including this batch. The available original TLS worksheet now tracks all seventeen saved register/flags words through a second physical layout; preferred-base/original-zero and captured-base/observed-bias bootstrap effects agree, with captured patch writer/order still unproved.

The broad GUI continuation worker stopped after content-safety screening for possible cybersecurity risk. Further broad continuation is paused at the stable126-packet/89-prefix checkpoint7716F8, with a separate86-record root physical scratch/parity audit. A separate759FC6 worksheet is provisional. The pause does not imply missing bytes or irrecoverability. This delivery remains incomplete with four pending rows; no new broad protected-initialization continuation is claimed.

The PE continuation worker also stopped after content-safety screening for possible cybersecurity risk. Further continuation is paused without retry. Its preserved stable worksheet records 2,875 selected fingerprints, next handler `captured_base+153126C`, stream `0x7ffbfd90ff7a`, key `0x770730978aeb950e`, `RSP=F` and `RDI=C-8, C=(S-8)&~40`. This is a tooling stop, not missing evidence or an irrecoverability conclusion; complete original PE effects remain pending. TLS stays at its separately saved checkpoint.

All four original inputs and all 480 extracted files match their recorded hashes/ZIP bytes. The retained working checkpoint is **202 byte-identical + four hash-pinned approved adaptations**: the two module_surface files add caller-owned UI frames; the two module_list_storage files preserve E310's calloc `(8 records, record stride)` contract. Evidence originals remain unchanged. Claims that all 206 retained files are unchanged are superseded. Runtime metadata/values remain observations, never startup defaults.

Current build/check snapshot status is recorded in [VERIFICATION_STATUS](../../VERIFICATION_STATUS.md). Syntax/link and finite helper traces do not prove the entire module, startup, real JNI/graphics, all pointer faults/concurrency or all FP modes. Available protected/startup analysis and concrete caller reviews persist in [PENDING_RECOVERY](../../PENDING_RECOVERY.md); actual evidence limits are separately stated in [UNRESOLVED](../../UNRESOLVED.md). See [README](../../README.md), [GLOBAL_AUDIT](../../GLOBAL_AUDIT.md) and [EvidencePreservation](../EvidencePreservation.md).

Selected independent GUI, PE, TLS-header and Window static reviews have a separate [input-integrity ledger](../IndependentStaticAuditInputs.md). The [TLS worksheet chain](../TlsStaticProofInputIntegrity.md) also pins its recorded inputs. [The preserved PE report's integrity audit](../PeStaticProofInputIntegrity.md) checks 44 declared hashes for its 2,875 selected records without proof replay or new-byte interpretation. These read-only consistency checks do not execute original/protected code or close the full GUI, original TLS or PE entry; the current fixed-prefix checkpoints remain available analysis in PendingAnalysis.json.
