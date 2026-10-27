# Timer Range

The tick, rotation-frame, packet and disable callbacks retain the freeze/cooldown state transitions, targeting conditions, movement-key sampling, collision/ray tests, prediction iteration and Legit/Regular branches. Mode IDs are Regular=0 and Legit=1 as recovered in runtime metadata; this does not establish the startup mode.

MovementPrediction.cpp contains the actual 0x29290 algorithm: input scaling, binary32 squared magnitude and cutoff, speed normalization, yaw conversion, sine/cosine call order and X/Z construction. Shared geometry supplies reciprocal vectors, clamping and the slab ray routine. FrozenQuery.cpp implements 0x42C30 for external Item Use Fix consumers. Its documented contract is the native low byte: module enabled equals one and ((signed duration>0)|freeze byte)&1. The enabled native branch does not establish a meaningful full EAX return.

Shared Trigonometry.cpp concretely implements the captured 0xB1CF0 sine, 0xB3590 cosine and 0xAF1B0 float reduction bodies. LargeReduction.cpp implements the ordinary 0xAD400 reducer and its native scaling/floor helpers. Timer bindKnown now reaches these concrete routines. No host sine/cosine or generic native algorithm dispatcher substitutes for them. Coefficients and tables remain caller-owned at their native RVAs.

The protected 0x13CFD0 continuation has a statically proven two-double tail-call contract. DecodedNumericService.cpp reloads its encoded cell and calls the exact external service, whose captured export is ucrtbase!hypot. bindKnown now supplies the named hypotenuse endpoint with a borrowed Runtime cell context. The 1,345 rebuilt-only controlled traces include this binding and cell reloads; they do not test the external numerical engine. The angular 0x13CFB0 transfer remains an explicit provider contract. Original startup binding and external numerical policy remain evidence limits. bindKnown closes all game/key/item queries.

Source files: Bindings.cpp, FrozenQuery.cpp, MovementPrediction.cpp, Surface.cpp, timer_range_events.cpp, timer_range_update.cpp.

| Native RVA | Role | Ownership evidence | Concrete semantic implementation |
| --- | --- | --- | --- |
| 0x42c60 | callback | direct_reference | timer_range::onTick |
| 0x42f00 | callback | direct_reference | timer_range::onRotationFrame |
| 0x43950 | callback | direct_reference | timer_range::onPacket |
| 0x43970 | callback | direct_reference | timer_range::onDisabled |
| 0x439e0 | ui | direct_reference | recovered_timer_range_ui |
| 0x43ad0 | settings | direct_reference | recovered_timer_range_settings |
| 0x43bb0 | candidate_local | contiguous_code_interval | timer_range::writeStatus |
| 0x43bf0 | candidate_local | contiguous_code_interval | timer_range::beginFreeze |
| 0x43ca0 | candidate_local | contiguous_code_interval | timer_range::sampleMovementKeys |

UI and persistence route to the actual recovered surface implementation in native/verified/surfaces. The module façade is not a substitute engine. Status wrappers preserve a 32-byte destination bound; numeric statuses use `%.0fms`, enum statuses use `%s`. Their incoming output pointer was confirmed in captured instructions despite malformed decompiler signatures. Teams has no status entry in its module interval.

The 9 setting records, exact config keys, labels, types and numeric enum option order are in MetadataCatalog.json. Default values remain unknown: current/saved values in the offline capture are session observations. No record is treated as a constructor default.

Fresh verification in AimGroupSyntax.json is a syntax compilation of the module source group with a 30-second bound per compiler subprocess. This establishes compile validity, not callback equivalence. Supplied differential reports apply only to their original supplied ports and trace fixtures; missing original harness/checkpoint paths are not reconstructed by a claim. Root-run isolated geometry/noise comparisons are recorded separately and do not prove these full callbacks.

Remaining limits are live dispatcher/event wiring, original startup initialization, external JNI/game/UI/JSON/graphics/format endpoints, the exact external math routines and MXCSR modes outside recorded probes. Recoverable module algorithms are present in source; full native callback equivalence remains unverified. Candidate proximity alone is not ownership evidence. See AimFunctionMappingOverrides.json for exact source locations and SharedInfrastructureAudit.md for infrastructure boundaries.

Fresh TrigonometryVerification.json passes 732/732 cases for each of 0xB1CF0, 0xB3590 and 0xAF1B0 (2,196 total). Both host and same-emulator comparisons are bit-identical, with no cross-backend differences. The fixture covers both signs of every finite binary32 exponent, native threshold neighbors, selected mantissa corners, infinities/NaNs and 64 raw random inputs under default MXCSR. Source hashes remained stable throughout the bounded run. ReductionVerification.json separately covers the large reducer and its scaling/floor helpers. These are numerical routine comparisons, not full Timer Range callback comparisons.

<!-- SHARED_SCOPE_DOCUMENTARY_AUDIT -->
## Current shared-scope documentary audit

This appendix supersedes older helper-progress and copy-preservation statements above. Historical reports apply only to their recorded source versions and scopes.

The Timer Range interval has 9 accounted function rows: 7 direct bodies/ABI ports, 2 shared surfaces and 0 excluded/corrected-owner rows. Registration is `registered` with 4 callback slots. **local_accounting_complete=true**, local pending=0; ordinary local rows have concrete bodies/shared surfaces or explicit ownership exclusions. **whole_module_native_equivalence=false**. Local completeness is separate from shared contract review.

The supplied direct graph lists 53 helper/container targets (48 concrete_resolver_binding, 4 concrete_typed_or_local_binding, 1 protected_transfer). Body/index/resolver accounting is not independent proof of every caller ABI or complete transitive behavior.

Established captured contracts: 0x13cfd0 to ucrtbase.dll!hypot. Static proofs establish exact argument/result lanes, saved-state restoration and each entry's continuation, including any return adjustment or caller stack compensation. Permanent startup binding and external engine implementation remain separate evidence limits; these frame analyses are closed.

Ordinary shared path, FontStash, atlas, glyph/cache/packing, font-table/TT/CFF outline and raster bodies are concrete. Scoped checks: path 1,832; FontStash 640; atlas 34; glyph/cache/packing 127; font tables/outlines 1,275; CFF 2,362; curves/sort 328; raster/wrapper 225; float-log/Gaussian 3,814; six ordinary startup helpers 240; F4730 lifecycle/bound services 508; Window query/caller routes 353 (336 ordinary comparisons and 17 decoded-cell/full-Word contracts). Protected entries are intercepted before execution, and Window tests use synthetic endpoints with no OS input. The font ledger identifies 42 named transitive entries with no ordinary font pending rows. Controlled provider comparisons remain scoped; final protected/caller/startup analysis is separate. Common modal has 97 cases, color section 2,122 and profile transitions 126, without claiming complete UI equivalence.

[The ordinary raster CPU supplement](../FontRasterizerCpuVerification.json) has 225 captured-body versus rebuilt CPU memory/trace/default-MXCSR matches with controlled providers and declared arena-address normalization. All 215 CPU/emulator MXCSR differences remain recorded in the unchanged raw report; the CPU results agree in every supplied fixture. Its executable mapping contains only seven fixed ordinary bodies, controlled shape/box/error stubs and INT3 elsewhere. Masked exceptions and default MXCSR only are tested; startup, protected dispatch, OS/JVM/driver services, other rounding/DAZ/FTZ, traps, faults and concurrency are outside this scope.

The established captured-contract register contains 27 entries (26 service/resolver leaves plus the F4730 body), with 4 separate pending GUI/original-TLS/original-PE/provenance rows. Newly integrated ordinary C220/C290/4C7B0 GUI composition and captured DCDBE0 directory-service contract have 65 profile-action, 50 composition, 66 rendering-route and 91 adapter cases. C290 opens the profile directory; no Windows service executes in these fixtures. DCDBE0/cellACC76A are transitive additions outside the original415/1,995 catalogues. Current complete static-library and whole-object link snapshots pass with stable source sets including this batch. The available original TLS worksheet now tracks all seventeen saved register/flags words through a second physical layout; preferred-base/original-zero and captured-base/observed-bias bootstrap effects agree, with captured patch writer/order still unproved.

The broad GUI continuation worker stopped after content-safety screening for possible cybersecurity risk. Further broad continuation is paused at the stable126-packet/89-prefix checkpoint7716F8, with a separate86-record root physical scratch/parity audit. A separate759FC6 worksheet is provisional. The pause does not imply missing bytes or irrecoverability. This delivery remains incomplete with four pending rows; no new broad protected-initialization continuation is claimed.

The PE continuation worker also stopped after content-safety screening for possible cybersecurity risk. Further continuation is paused without retry. Its preserved stable worksheet records 2,875 selected fingerprints, next handler `captured_base+153126C`, stream `0x7ffbfd90ff7a`, key `0x770730978aeb950e`, `RSP=F` and `RDI=C-8, C=(S-8)&~40`. This is a tooling stop, not missing evidence or an irrecoverability conclusion; complete original PE effects remain pending. TLS stays at its separately saved checkpoint.

All four original inputs and all 480 extracted files match their recorded hashes/ZIP bytes. The retained working checkpoint is **202 byte-identical + four hash-pinned approved adaptations**: the two module_surface files add caller-owned UI frames; the two module_list_storage files preserve E310's calloc `(8 records, record stride)` contract. Evidence originals remain unchanged. Claims that all 206 retained files are unchanged are superseded. Runtime metadata/values remain observations, never startup defaults.

Current build/check snapshot status is recorded in [VERIFICATION_STATUS](../../VERIFICATION_STATUS.md). Syntax/link and finite helper traces do not prove the entire module, startup, real JNI/graphics, all pointer faults/concurrency or all FP modes. Available protected/startup analysis and concrete caller reviews persist in [PENDING_RECOVERY](../../PENDING_RECOVERY.md); actual evidence limits are separately stated in [UNRESOLVED](../../UNRESOLVED.md). See [README](../../README.md), [GLOBAL_AUDIT](../../GLOBAL_AUDIT.md) and [EvidencePreservation](../EvidencePreservation.md).

Selected independent GUI, PE, TLS-header and Window static reviews have a separate [input-integrity ledger](../IndependentStaticAuditInputs.md). The [TLS worksheet chain](../TlsStaticProofInputIntegrity.md) also pins its recorded inputs. [The preserved PE report's integrity audit](../PeStaticProofInputIntegrity.md) checks 44 declared hashes for its 2,875 selected records without proof replay or new-byte interpretation. These read-only consistency checks do not execute original/protected code or close the full GUI, original TLS or PE entry; the current fixed-prefix checkpoints remain available analysis in PendingAnalysis.json.
