# Verification status

Reports below retain raw outcomes and tested source identities. A passing finite check is not a whole-module equivalence claim. Historical supplied checks remain separate.

| Fresh report | Raw pass | Same-emulator resolution | Captured/rebuilt CPU resolves backend differences | Cases | Recorded source hashes current |
| --- | --- | --- | --- | --- | --- |
| CombinedBuild.json | True | None | None | None | True |
| CombinedLinkAudit.json | True | None | None | None | True |
| EvidencePreservation.json | True | None | None | None | True |
| GeometryVerification.json | False | True | True | 2472 | True |
| NumericsVerification.json | False | True | True | 363 | True |
| ReductionVerification.json | True | None | None | 722 | True |
| modules/TrigonometryVerification.json | True | None | None | 2196 | True |
| DoubleTrigonometryVerification.json | True | None | None | 1322 | True |
| SquareRootVerification.json | True | None | None | 2566 | True |
| JniVerification.json | True | None | None | 568 | True |
| GraphicsVerification.json | True | None | None | 20 | True |
| modules/OwnedRoundingVerification.json | True | None | None | 20040 | True |
| JsonVerification.json | True | None | None | 736 | True |
| RemainingJniVerification.json | True | None | None | 336 | True |
| SharedUiFontVerification.json | True | None | None | 97 | True |
| NumericWidgetVerification.json | True | None | None | 110 | True |
| RenderWidgetVerification.json | True | None | None | 105 | True |
| WidgetModalVerification.json | True | None | None | 72 | True |
| UiWrapperVerification.json | True | None | None | 24 | True |
| ConfigurationVerification.json | True | None | None | 367 | True |
| ColorSpaceVerification.json | True | None | None | 2749 | True |
| GameAlgorithmVerification.json | True | None | None | 65742 | True |
| ModalColorVerification.json | True | None | None | 2122 | True |
| TextAtlasVerification.json | True | None | None | 34 | True |
| FontStashVerification.json | True | None | None | 640 | True |
| FontGlyphVerification.json | True | None | None | 127 | True |
| ExponentialVerification.json | True | None | None | 7296 | True |
| GuiModalVerification.json | True | None | None | 97 | True |
| PathVerification.json | True | None | None | 1832 | True |
| FontTablesVerification.json | True | None | None | 1275 | True |
| FontRasterizerVerification.json | True | None | None | 225 | True |
| BoundFontAdapterVerification.json | True | None | None | None | True |
| CeilingAdapterVerification.json | True | None | None | 1692 | True |
| DecodedBinaryScalarVerification.json | True | None | None | 7115 | True |
| DecodedCrtCallerVerification.json | True | None | None | 21 | True |
| DecodedCrtRoutingVerification.json | True | None | None | 35 | True |
| DecodedCrtVerification.json | True | None | None | 927 | True |
| DecodedDirectionVerification.json | True | None | None | 2344 | True |
| DecodedFloatVerification.json | True | None | None | 2338 | True |
| DecodedNumericVerification.json | True | None | None | 1345 | True |
| DirectoryServiceAdapterVerification.json | True | None | None | 91 | True |
| FontCffVerification.json | True | None | None | 2362 | True |
| FontCurveVerification.json | True | None | None | 328 | True |
| FontRasterizerCpuVerification.json | True | None | True | 225 | True |
| GaussianBindingVerification.json | True | None | None | 3814 | True |
| GuiCompositionVerification.json | True | None | None | 50 | True |
| GuiDirectoryRoutingVerification.json | True | None | None | 66 | True |
| GuiPagesVerification.json | True | None | None | 126 | True |
| GuiProfileActionsVerification.json | True | None | None | 65 | True |
| LiteralCallerRoutingVerification.json | True | None | None | 373 | True |
| ModOverlayCharacterVerification.json | True | None | None | 1038 | True |
| NativeCopyVerification.json | True | None | None | 2766 | True |
| OwnedSharedSyntaxVerification.json | True | None | None | None | True |
| ProfileManagerVerification.json | True | None | None | 192 | True |
| StartupReasonVerification.json | True | None | None | 508 | True |
| StartupVerification.json | True | None | None | 240 | True |
| WindowQueryVerification.json | True | None | None | 353 | True |

Source mismatch lists and exact report scopes are in `reports/VerificationStatus.json`. Geometry/projection cross-backend NaN differences are retained; their same-emulator results have a separate column. Build reports distinguish compiler/link success from source changes during a build.

Current coverage counts: function_assignments=429, unique_function_rvas=426, callback_slots=171, distinct_callbacks=170, globals=1995, external_targets=415, source_present_pending=0, pending_shared_analysis=4, pending_caller_binding_review=0, captured_protected_direct_transfers=12, closed_protected_direct_contracts=11, pending_protected_direct_transforms=1, modules=68, registered_modules=66, settings=426, module_reports=68.

The [raster CPU supplement](reports/FontRasterizerCpuVerification.json) compares captured ordinary CPU bodies with rebuilt CPU across the same 225 fixtures. Normalized bytes, callback traces and default MXCSR match, confirming the CPU results behind all 215 raw emulator discrepancies. The original raster report remains unchanged. This resolves those finite comparisons under masked exceptions; other FP modes, traps, faults and concurrency remain outside the suite.
