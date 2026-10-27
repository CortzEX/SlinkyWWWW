# Evidence limits and pending analysis

This register separates facts that a snapshot alone cannot establish from available code analysis that has not been completed. **Captured protected bytes are present and are not declared irrecoverable.** The repeatable pending register is [PENDING_RECOVERY.md](PENDING_RECOVERY.md); its source is [PendingAnalysis.json](reports/PendingAnalysis.json). Ordinary font/path/table/outline/raster and float-log/Gaussian bodies are concrete with scoped checks. Whole-module native equivalence remains unclaimed.

## Evidence limits

| Fact / subsystem | Established evidence | Precise limit | Evidence needed to establish the missing fact |
| --- | --- | --- | --- |
| Pristine startup state/defaults | 66 descriptors, 426 settings, exact keys/layouts, observed session values and event writes. | A post-startup observation cannot by itself distinguish defaults, config restoration and later mutation, or establish complete initial ownership/RNG/cache state. A complete immutable startup trace is not supplied. | Relevant initializer/write-order analysis where bytes exist, or an initial-state trace/checkpoint tied to this build. Ordinary startup/registry bodies are concrete. The original protected PE/TLS entry paths retain analysis. Registration and all eight F4730 service/resolver frames are established; their event writes do not prove earlier defaults. No generic ordinary initializer inventory remains. No observed value is installed as a default. |
| Permanent allocator/import policy | At the capture, `13CF60/70/80/90` RIP cells `2CC170/178/180/188` exactly match `ucrtbase.dll` exports **calloc/free/malloc/realloc**. These are exact export matches, not nearest-symbol guesses. | Observed identity does not establish original source import spelling, permanence across startup/rebinding or constructor policy. | Import/initializer provenance and destination-binding lifecycle analysis. [ExternalCellObservation.json](reports/ExternalCellObservation.json) records exact captured pointers/module/export identities. |
| Historical verification rerun artifacts | Supplied report results and hashes are inventoried; fresh scoped suites have separate records. | Some historical harness/source/checkpoint paths named by those reports are absent. A reference to a missing artifact cannot reproduce its exact original suite. | The named original harness/checkpoint, or an explicitly new scoped fixture. Current reconstruction tests are not silently substituted for historical evidence. |
| Exact original identifiers/decomposition | Offsets, instruction effects, strings and callers justify recovered semantic names and structures. | Native compilation does not preserve all original variable/class/namespace spellings, comments, macros, templates, formatting or inline boundaries. No artifact establishes those exact spellings where stripped. | Original source/debug/symbol artifacts retaining the text. Behavioral recovery does not require fictional original names. |
| Real external environments | Recovered consumers retain explicit JNI, graphics-driver, file/platform, allocator and clock contracts and lifecycle order. | Controlled callback equality does not establish every external implementation/version/environment or live scheduling behavior. | Actual service implementation/version and ABI/lifetime evidence, plus appropriately scoped integration observations. Local adapters and available code remain separately accountable. |

## Available captured analysis remains pending

| Entries / scope | Known evidence | Concrete remaining analysis |
| --- | --- | --- |
| GUI `129B0` | Its ordinary caller is concrete; `129B0` calls `1040A38` and uses saved-state target chains. | Complete the selected entry/target/frame tracing and actual state reads/writes. A normalized provider fixture proves the consumer, not this native service. |
| Concrete source callers | All historical source-only rows now have reviewed resolver or typed/local/inline connections, with source hashes and route evidence. | Finite caller review is distinct from proof of every external environment, input, fault or concurrency behavior; no missing ordinary body is implied. |
| Startup/initializer paths | Six ordinary helpers AAFD0/AB050/AB070/AB080/AB0D0/4D0B0 have 240 scoped cases. All eight actual F4730 service/resolver frames are statically established; its concrete lifecycle body and bound callers have 508 controlled cases. Reason2 is exactly FNINIT. | Protected first TLS callback1A72C5E and PE entry255FCC7 remain named available-code analysis. Earlier bindings/pristine critical-section/list state remain unproved. [StartupReasonVerification.json](reports/StartupReasonVerification.json) separates 492 ordinary native comparisons from 16 rebuilt service-contract cases. Protected entries were intercepted before execution; complete external thread/TLS/lock/fault equivalence is unclaimed. |

<!-- CURRENT_TLS_STATIC_PROGRESS -->
The original TLS review has reached handler `0x14a5b3b`, stream `0x1a7c4ea`, key `0x1c7ebeeb35a0b12a`, physical `RSP=F`, operand RDI=B+1A7C4EA (backward operand cursor), frame RSI=S-40 (now saved-bias cell). [The latest fixed worksheet](reports/TlsSecondStreamPointerAddStaticReview.md) records saved-context transports and scratch effects. [The paired-base audit](reports/TlsBootstrapPairedBaseAudit.md) proves original preferred-base/zero-immediate equivalence with the captured-base/observed-bias bootstrap; its captured patch writer/order remains unproved. [The offset-convention audit](reports/TlsPhysicalOffsetConventionAudit.md) normalizes historical decimal byte labels without changing their arithmetic. [The independent recurring-header review](reports/Tls14A8994IndependentHeaderAudit.md) confirms the pre-NOT operand. No caller value has blocked this selected transport prefix; full TLS effects and binding order remain available analysis.
<!-- END_CURRENT_TLS_STATIC_PROGRESS -->

[GlobalStateAudit.md](reports/GlobalStateAudit.md) records bounded analysis attempted, actual targets, caller registers and missing proof. [PENDING_RECOVERY.md](PENDING_RECOVERY.md) lists each direct protected entry with available prefix facts, source caller references and specific remaining work, plus the current caller-binding reviews. Map regeneration preserves these rows; a zero module-local pending count does not erase shared/protected/startup work.

No entry is called insufficient merely because it is large, resembles a library or uses protection. Known scalar/bit/frame transforms are retained even where the final engine has not been established. Runtime allocator identities and six exact captured numeric tail dispatches are established facts; startup permanence is a different question. Neutral globals, constants, split lanes and function-holder addresses are not automatically missing algorithms or startup values.

<!-- ESTABLISHED_CAPTURED_DISPATCHES -->
## Established captured dispatch contracts

The service frame/cell analyses below are closed. Their exact captured identities, external implementation and permanent startup binding have separate scopes; the transfer bytes can remain classified as protected in the direct graph.

| Entry | Exact captured export | Static proof |
| --- | --- | --- |
| `0x13cfa0` | `ucrtbase.dll!acos` | [ProtectedProjectionStaticReview.md](reports/ProtectedProjectionStaticReview.md) |
| `0x13cfb0` | `ucrtbase.dll!atan2` | [ProtectedDirectionStaticReview.md](reports/ProtectedDirectionStaticReview.md) |
| `0x13cfc0` | `ucrtbase.dll!atan2f` | [ProtectedFloatDirectionStaticReview.md](reports/ProtectedFloatDirectionStaticReview.md) |
| `0x13cfd0` | `ucrtbase.dll!hypot` | [ProtectedNumericStaticReview.md](reports/ProtectedNumericStaticReview.md) |
| `0x13d190` | `ucrtbase.dll!acosf` | [ProtectedFloatUnaryStaticReview.md](reports/ProtectedFloatUnaryStaticReview.md) |
| `0x13d0e0` | `ucrtbase.dll!bsearch` | [ProtectedSearchStaticReview.md](reports/ProtectedSearchStaticReview.md) |
| `0x13d0f0` | `ucrtbase.dll!qsort` | [ProtectedSortStaticReview.md](reports/ProtectedSortStaticReview.md) |
| `0x13d0a0` | `ucrtbase.dll!strcmp` | [ProtectedCompareStaticReview.md](reports/ProtectedCompareStaticReview.md) |
| `0x13d0d0` | `ucrtbase.dll!_time64` | [ProtectedClockStaticReview.md](reports/ProtectedClockStaticReview.md) |
| `0x13d0b0` | `ucrtbase.dll!strncpy` | [ProtectedCopyStaticReview.md](reports/ProtectedCopyStaticReview.md) |
| `0x13cfe0` | `ucrtbase.dll!powf` | [ProtectedBinaryScalarStaticReview.md](reports/ProtectedBinaryScalarStaticReview.md) |
| `0x13d030` | `ucrtbase.dll!_register_onexit_function` | [ProtectedRegistrationStaticReview.md](reports/ProtectedRegistrationStaticReview.md) |
| `0x32ecfb` | `ucrtbase.dll!tolower` | [ProtectedOverlayCharacterStaticReview.md](reports/ProtectedOverlayCharacterStaticReview.md) |
| `0xbb8f39` | `ucrtbase.dll!tolower` | [ProtectedOverlayStatusCharacterStaticReview.md](reports/ProtectedOverlayStatusCharacterStaticReview.md) |
| `0xe28595` | `ucrtbase.dll!tolower` | [ProtectedOverlayRenderStatusStaticReview.md](reports/ProtectedOverlayRenderStatusStaticReview.md) |
| `0xe6314d` | `ucrtbase.dll!tolower` | [ProtectedOverlayRenderNameStaticReview.md](reports/ProtectedOverlayRenderNameStaticReview.md) |
| `0xe042c7` | `ntdll.dll!RtlInitializeCriticalSection` | [ProtectedStartupInitializeStaticReview.md](reports/ProtectedStartupInitializeStaticReview.md) |
| `0xf7922b` | `ntdll.dll!RtlDeleteCriticalSection` | [ProtectedStartupDeleteStaticReview.md](reports/ProtectedStartupDeleteStaticReview.md) |
| `0xe3c461` | `ntdll.dll!RtlLeaveCriticalSection` | [ProtectedStartupReleaseStaticReview.md](reports/ProtectedStartupReleaseStaticReview.md) |
| `0xae25c1` | `kernel32.dll!TlsGetValue` | [ProtectedStartupThreadResolverStaticReview.md](reports/ProtectedStartupThreadResolverStaticReview.md) |
| `0xb012ba` | `ntdll.dll!RtlEnterCriticalSection` | [ProtectedStartupEnterStaticReview.md](reports/ProtectedStartupEnterStaticReview.md) |
| `0xf56385` | `ntdll.dll!RtlLeaveCriticalSection` | [ProtectedStartupReason0ReleaseStaticReview.md](reports/ProtectedStartupReason0ReleaseStaticReview.md) |
| `0xb30557` | `ntdll.dll!RtlEnterCriticalSection` | [ProtectedStartupReason0EnterStaticReview.md](reports/ProtectedStartupReason0EnterStaticReview.md) |
| `0xbbbc7e` | `kernel32.dll!TlsGetValue` | [ProtectedStartupProcessResolverStaticReview.md](reports/ProtectedStartupProcessResolverStaticReview.md) |
| `0x103762f` | `user32.dll!GetActiveWindow` | [ProtectedWindowQueryStaticReview.md](reports/ProtectedWindowQueryStaticReview.md) |
| `0xdcdbe0` | `shell32.dll!ShellExecuteW` | [DirectoryServiceStaticFrameReview.md](reports/DirectoryServiceStaticFrameReview.md) |
| `0xf4730` | Mixed ordinary lifecycle body and eight established service/resolver frame contracts | [StartupReasonVerification.json](reports/StartupReasonVerification.json), [StartupCallSiteIdentity.json](reports/StartupCallSiteIdentity.json) |

The 27 listed register entries comprise 26 leaf service/resolver contracts plus the F4730 mixed-body summary. Six numeric tail dispatches are included. These counts do not claim original PE/TLS startup closure.

<!-- STATIC_WORKSHEET_INTEGRITY -->
[IndependentStaticAuditInputs](reports/IndependentStaticAuditInputs.md) checks the declared hashes of selected independent GUI, PE, TLS-header and Window reviews without replay. [The PE stack/width review](reports/Pe1529D32IndependentWidthAudit.md) additionally pins 38 exact original instruction records and resolves its provisional stack-offset discrepancy. [PeStaticProofInputIntegrity](reports/PeStaticProofInputIntegrity.md) checks 44 declared input hashes for the preserved 2,875-record PE report without rerunning its proofs or interpreting new bytes. [TlsStaticProofInputIntegrity](reports/TlsStaticProofInputIntegrity.md) checks the TLS worksheet chain's recorded inputs. These checks establish report/input consistency, not full GUI or original startup semantics; those available analyses remain open.
<!-- END_STATIC_WORKSHEET_INTEGRITY -->

<!-- GUI_CONTINUATION_EXECUTION_STATUS -->
The broad GUI continuation worker stopped after content-safety screening for possible cybersecurity risk. Further broad continuation is paused at its stable126-packet/89-prefix checkpoint `0x7716f8`. [The separate root physical scratch/parity audit](reports/Gui7716F8IndependentParityAudit.md) checks86 records. A separate759FC6 worksheet remains provisional. This is not a missing-byte or irrecoverability conclusion. The delivery remains incomplete with four pending GUI/original-TLS/original-PE/earlier-provenance rows; no new broad protected-initialization work is claimed.
<!-- END_GUI_CONTINUATION_EXECUTION_STATUS -->

<!-- RASTER_CPU_SUPPLEMENT -->
[The ordinary raster CPU supplement](reports/FontRasterizerCpuVerification.json) matches captured-body and rebuilt CPU memory, controlled-provider traces and default-MXCSR results in 225 finite cases, under the declared arena-address normalization. All 215 raw CPU/emulator MXCSR differences are reproduced: the CPU outputs match each other, while the raw emulator differences remain preserved in the unchanged [original raster report](reports/FontRasterizerVerification.json). [The dependency audit](reports/FontRasterizerCpuDependencyAudit.json) limits executable captured bytes to seven fixed ordinary bodies with controlled shape/box/error providers and INT3 elsewhere. This adds no startup, protected-dispatch, OS/JVM/driver, arbitrary-input, other rounding/DAZ/FTZ, trap, fault or concurrency claim; exceptions are masked and MXCSR starts at its default value.
<!-- END_RASTER_CPU_SUPPLEMENT -->

<!-- PE_CONTINUATION_EXECUTION_STATUS -->
The PE continuation worker stopped after content-safety screening for possible cybersecurity risk. Further continuation is paused, with no retry. [The preserved stable PE worksheet](reports/PeContextContinuationStaticReview.json) records 2,875 selected fingerprints and the next handler `captured_base+153126C`, stream `0x7ffbfd90ff7a`, key `0x770730978aeb950e`, `RSP=F` and `RDI=C-8, C=(S-8)&~40`. The pause does not establish missing bytes or irrecoverability, and the stable worksheet is not changed by this documentary update. Complete original PE effects remain one of the four pending rows.
<!-- END_PE_CONTINUATION_EXECUTION_STATUS -->
