# Fake Lag

Both actual behavior bodies are present. Event 0 updates the independent inbound/outbound counters and block bytes, consumes the shared configuration byte atomically, applies weapon/in-game/attack gating and publishes two 16-bit delay amounts. The pulse arithmetic retains binary32 conversion/addition/truncation and the 50-unit decrement. The update's captured return combines the prior low word with the converted outbound high word.

The shared event 2/3 packet callback preserves relative-move, teleport and head-look predicate order, result code 3 for selected real-time packets, block-byte test, unsigned amount subtraction and direct result sign-bit test. bind_fake_lag_known supplies all five concrete query functions. The State layout matches native 0x2FA304..0x2FA31A and is caller-owned, with no startup initializer.

Source files: Bindings.cpp, FakeLag.cpp, Surface.cpp.

| Native RVA | Role | Ownership evidence | Concrete semantic implementation |
| --- | --- | --- | --- |
| 0x32b30 | callback | direct_reference | fake_lag::semantic_fake_lag_update |
| 0x32cb0 | callback | direct_reference | fake_lag::semantic_fake_lag_packet |
| 0x32d60 | ui | direct_reference | recovered_fake_lag_ui |
| 0x32e20 | settings | direct_reference | recovered_fake_lag_settings |
| 0x32ed0 | candidate_local | contiguous_code_interval | fake_lag::writeStatus |

UI and persistence route to the actual recovered surface implementation in native/verified/surfaces. The module façade is not a substitute engine. Status wrappers preserve a 32-byte destination bound; numeric statuses use `%.0fms`, enum statuses use `%s`. Their incoming output pointer was confirmed in captured instructions despite malformed decompiler signatures. Teams has no status entry in its module interval.

The 7 setting records, exact config keys, labels, types and numeric enum option order are in MetadataCatalog.json. Default values remain unknown: current/saved values in the offline capture are session observations. No record is treated as a constructor default.

Fresh verification in AimGroupSyntax.json is a syntax compilation of the module source group with a 30-second bound per compiler subprocess. This establishes compile validity, not callback equivalence. Supplied differential reports apply only to their original supplied ports and trace fixtures; missing original harness/checkpoint paths are not reconstructed by a claim. Root-run isolated geometry/noise comparisons are recorded separately and do not prove these full callbacks.

Remaining limits are live dispatcher/event wiring, original startup initialization, external JNI/game/UI/JSON/graphics/format endpoints, the exact external math routines and MXCSR modes outside recorded probes. Recoverable module algorithms are present in source; full native callback equivalence remains unverified. Candidate proximity alone is not ownership evidence. See AimFunctionMappingOverrides.json for exact source locations and SharedInfrastructureAudit.md for infrastructure boundaries.

<!-- SHARED_SCOPE_DOCUMENTARY_AUDIT -->
## Current shared-scope documentary audit

This appendix supersedes older helper-progress and copy-preservation statements above. Historical reports apply only to their recorded source versions and scopes.

The Fake Lag interval has 5 accounted function rows: 3 direct bodies/ABI ports, 2 shared surfaces and 0 excluded/corrected-owner rows. Registration is `registered` with 3 callback slots. **local_accounting_complete=true**, local pending=0; ordinary local rows have concrete bodies/shared surfaces or explicit ownership exclusions. **whole_module_native_equivalence=false**. Local completeness is separate from shared contract review.

The supplied direct graph lists 13 helper/container targets (10 concrete_resolver_binding, 3 concrete_typed_or_local_binding). Body/index/resolver accounting is not independent proof of every caller ABI or complete transitive behavior.

No protected/external-cell/source-only review target is listed for this interval in the supplied direct graph. Downstream provider/state/startup contracts still have their own ledgers; this statement does not imply all transitive behavior is verified.

Ordinary shared path, FontStash, atlas, glyph/cache/packing, font-table/TT/CFF outline and raster bodies are concrete. Scoped checks: path 1,832; FontStash 640; atlas 34; glyph/cache/packing 127; font tables/outlines 1,275; CFF 2,362; curves/sort 328; raster/wrapper 225; float-log/Gaussian 3,814; six ordinary startup helpers 240; F4730 lifecycle/bound services 508; Window query/caller routes 353 (336 ordinary comparisons and 17 decoded-cell/full-Word contracts). Protected entries are intercepted before execution, and Window tests use synthetic endpoints with no OS input. The font ledger identifies 42 named transitive entries with no ordinary font pending rows. Controlled provider comparisons remain scoped; final protected/caller/startup analysis is separate. Common modal has 97 cases, color section 2,122 and profile transitions 126, without claiming complete UI equivalence.

[The ordinary raster CPU supplement](../FontRasterizerCpuVerification.json) has 225 captured-body versus rebuilt CPU memory/trace/default-MXCSR matches with controlled providers and declared arena-address normalization. All 215 CPU/emulator MXCSR differences remain recorded in the unchanged raw report; the CPU results agree in every supplied fixture. Its executable mapping contains only seven fixed ordinary bodies, controlled shape/box/error stubs and INT3 elsewhere. Masked exceptions and default MXCSR only are tested; startup, protected dispatch, OS/JVM/driver services, other rounding/DAZ/FTZ, traps, faults and concurrency are outside this scope.

The established captured-contract register contains 27 entries (26 service/resolver leaves plus the F4730 body), with 4 separate pending GUI/original-TLS/original-PE/provenance rows. Newly integrated ordinary C220/C290/4C7B0 GUI composition and captured DCDBE0 directory-service contract have 65 profile-action, 50 composition, 66 rendering-route and 91 adapter cases. C290 opens the profile directory; no Windows service executes in these fixtures. DCDBE0/cellACC76A are transitive additions outside the original415/1,995 catalogues. Current complete static-library and whole-object link snapshots pass with stable source sets including this batch. The available original TLS worksheet now tracks all seventeen saved register/flags words through a second physical layout; preferred-base/original-zero and captured-base/observed-bias bootstrap effects agree, with captured patch writer/order still unproved.

The broad GUI continuation worker stopped after content-safety screening for possible cybersecurity risk. Further broad continuation is paused at the stable126-packet/89-prefix checkpoint7716F8, with a separate86-record root physical scratch/parity audit. A separate759FC6 worksheet is provisional. The pause does not imply missing bytes or irrecoverability. This delivery remains incomplete with four pending rows; no new broad protected-initialization continuation is claimed.

The PE continuation worker also stopped after content-safety screening for possible cybersecurity risk. Further continuation is paused without retry. Its preserved stable worksheet records 2,875 selected fingerprints, next handler `captured_base+153126C`, stream `0x7ffbfd90ff7a`, key `0x770730978aeb950e`, `RSP=F` and `RDI=C-8, C=(S-8)&~40`. This is a tooling stop, not missing evidence or an irrecoverability conclusion; complete original PE effects remain pending. TLS stays at its separately saved checkpoint.

All four original inputs and all 480 extracted files match their recorded hashes/ZIP bytes. The retained working checkpoint is **202 byte-identical + four hash-pinned approved adaptations**: the two module_surface files add caller-owned UI frames; the two module_list_storage files preserve E310's calloc `(8 records, record stride)` contract. Evidence originals remain unchanged. Claims that all 206 retained files are unchanged are superseded. Runtime metadata/values remain observations, never startup defaults.

Current build/check snapshot status is recorded in [VERIFICATION_STATUS](../../VERIFICATION_STATUS.md). Syntax/link and finite helper traces do not prove the entire module, startup, real JNI/graphics, all pointer faults/concurrency or all FP modes. Available protected/startup analysis and concrete caller reviews persist in [PENDING_RECOVERY](../../PENDING_RECOVERY.md); actual evidence limits are separately stated in [UNRESOLVED](../../UNRESOLVED.md). See [README](../../README.md), [GLOBAL_AUDIT](../../GLOBAL_AUDIT.md) and [EvidencePreservation](../EvidencePreservation.md).

Selected independent GUI, PE, TLS-header and Window static reviews have a separate [input-integrity ledger](../IndependentStaticAuditInputs.md). The [TLS worksheet chain](../TlsStaticProofInputIntegrity.md) also pins its recorded inputs. [The preserved PE report's integrity audit](../PeStaticProofInputIntegrity.md) checks 44 declared hashes for its 2,875 selected records without proof replay or new-byte interpretation. These read-only consistency checks do not execute original/protected code or close the full GUI, original TLS or PE entry; the current fixed-prefix checkpoints remain available analysis in PendingAnalysis.json.
