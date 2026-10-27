# Changes in this build

This project is **OpenSlinky+ by lallu** (credits: Skid Solutions).

## Main change: the module layer is now native C++

OpenSlinky+ v2.0.0 moves the module implementations that previously lived in `SlinkyClient/` into the new `SlinkyModules/` C++ module layer. The old Java module layer is retired; the existing module catalogue now has corresponding native C++ implementations, with the documented `Scaffold c[BETA]` placeholder remaining unimplemented because no recovered implementation defines its behavior.

The native layer is organized as one portable source file per module, plus a shared runtime for registration, dispatch, lifecycle, UI/settings, game access, fonts/canvas, profiles, and JSON/config handling. It is built as the static `shareable_modules` library using C++20 and `/fp:strict`.

## What changed

| File or directory | Change |
|---|---|
| `SlinkyModules/` | **New.** Contains the native C++ module implementations and shared runtime. The module catalogue has 68 entries matching the previous Java catalogue one-for-one: 66 registered modules, plus Speed and Chest Stealer. |
| `SlinkyModules/modules/` | Holds one portable C++ source file per module. |
| `SlinkyModules/runtime/` | Holds shared infrastructure for the module registry, event dispatch, lifecycle, UI/settings, game access, fonts/canvas, profiles, and JSON/config handling. |
| `SlinkyModules/recovery_reference/` | **New.** Documentation and audit material: decompiler views, readable C++ ports, behavior/callback ports, verification JSON, manifests, call graph, and `MODULE_RECOVERY_STANDARD.md`. It is not included in any build target. |
| `SlinkyClient/` | **Removed.** The Java sources for the retired module layer are no longer part of the source tree; their module implementations now have native counterparts in `SlinkyModules/`. |
| `CMakeLists.txt` | Updated for CMake 3.20 or newer and to build `SlinkyModules/` as a subdirectory. Adds the native module targets and verification wiring. |
| `build.ps1` | Updated for the v2 build. `-CheckOnly` runs the export verification without performing the full build. |
| `README.md`, `.gitignore` | Updated for the new native module layout and build flow. |
| License and release configuration | Adds the MIT license and automatic Discord release announcements. |

## Native module build and verification

The module layer builds as `shareable_modules`. Supporting targets are `shareable_module_objects` and `shareable_link_check`; the latter checks that the native module layer links without missing definitions or duplicate symbols.

The verification package was refreshed to complete the package/export ledger. The `woof` package includes the seven root audit ledgers and 68 per-module audit pages. The `meow` package includes the behavior-recovery ports and their coverage ledger.

Verification status for this source tree:

- CMake configuration and the full Release build of `Slinky`, `SlinkyNative`, and `shareable_modules` succeed.
- `shareable_link_check` links cleanly, with no missing definitions or duplicate symbols.
- `VerifyExport.py` reports a full pass: `"passed": true`, with no failures.
- `build.ps1 -CheckOnly` runs the export verification only.

Python 3 is optional and is used only for the export check.

## Module coverage and documented limits

The native catalogue covers all 68 modules from the retired Java layer: 66 registered modules, plus Speed and Chest Stealer. The only catalogue entry without an implementation remains the documented `Scaffold c[BETA]` placeholder (RVA `0x0`). The available source packs do not define recovered logic for that entry, so this port does not invent behavior for it.

The accompanying reference material records the recovery and verification work, but is documentation only and is not compiled into the application. Extra reference clients reviewed for potential gaps—including `chat-v4` / Vape V4 recode, `Myau.jar`, and `RavenXD 3.2`—were not integrated: their Java logic does not map to the recovered native ABI surfaces, and their provenance is third-party.

## Legacy Fabric support (experimental)

The loader recognizes Minecraft 1.8.9 running on Legacy Fabric and selects a matching payload automatically. This support is experimental.

Supported Minecraft 1.8.9 client targets are Forge, Vanilla, OptiFine, Lunar, Badlion, and Legacy Fabric (experimental).

## Existing loader and payload behavior

The v2.0.0 module-layer change does not rewrite `Slinky/` or `SlinkyNative/`. The injector, loader, JVM detection, and payload embedding remain separate from the native module library. The prebuilt payload JARs remain embedded resources in `SlinkyNative.dll`.

The previously introduced payload-remapping, mouse-focus recovery, and click-tracking changes remain part of the existing payloads; they are not new changes introduced by the C++ module-layer port.

## Build requirements and output

- Windows 64-bit.
- Visual Studio or Visual Studio Build Tools with **Desktop development with C++**.
- CMake 3.20 or newer.

Run the build from PowerShell:

```powershell
powershell -ExecutionPolicy Bypass -File .\build.ps1