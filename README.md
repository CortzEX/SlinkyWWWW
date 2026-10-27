<p align="center">
  <font size="6"><b>OpenSlinky+</b></font>
  <br>
  <font size="3">by CortzEX · v2.0.3</font>
  <br>
</p>

---

## Supported clients (Minecraft 1.8.9)

| Client | Names the game uses | Payload used |
|---|---|---|
| Vanilla (Mojang launcher) | notch (`ave`) | official |
| OptiFine (standalone) | notch (`ave`) | official |
| Lunar Client | notch (`ave`) | official |
| Badlion Client | notch (`ave`) | official |
| Forge (and OptiFine on Forge) | SRG (`func_71410_x`) | srg |
| MCP/dev environment | MCP (`getMinecraft`) | named |
| Legacy Fabric (vanilla 1.8.9 with Fabric intermediary) | intermediary (`class_1600`, `field_3774`) | intermediary |

The loader inspects the running JVM and chooses the payload automatically. Check
`%TEMP%\slinky-<pid>\slinky-native.log` - it shows the detected namespace, e.g.
`detected Minecraft 1.8.9 with official names (class ave, ...)`. For Legacy Fabric the log reads
`intermediary`; the Java side keeps its `official` namespace argument because the intermediary
payload is byte-consistent with it.

## How to build

Prerequisites: Visual Studio 2019/2022 (or Build Tools) with **Desktop development with C++**, and CMake 3.20+.
No Java/Gradle is needed - the four payload jars are prebuilt in `SlinkyNative/payload`.

```powershell
powershell -ExecutionPolicy Bypass -File .\build.ps1
```

Output: `dist\OpenSlinkyPlus.exe` + `dist\SlinkyNative.dll` (keep them in the same folder), plus the
native module layer built as `build/lib/Release/shareable_modules.lib`. `build.ps1 -CheckOnly` only
runs the module export verification (`SlinkyModules/VerifyExport.py`).
Manual build: `cmake -S . -B build -A x64` then `cmake --build build --config Release`
(appends `shareable_modules` automatically). The offline link check is the `shareable_link_check` target.

## Module layer (`SlinkyModules`)

The client's modules are implemented in **native C++** in `SlinkyModules/`: one file per module
(68 `modules/*.cpp`) plus a shared runtime (`runtime/`), built as the static `shareable_modules`
library with `/fp:strict` preserved. Compile/link results are recorded in `BuildVerification.json`;
source hashes, ownership and identifier renames are recorded in `ExportManifest.json` (recheck
them with `VerifyExport.py`).

`SlinkyModules/recovery_reference/` carries the accompanying recovery corpus: decompiler views,
clean/behaviour ports, manifests and verification ledgers. It is documentation and audit material
and is not wired into any build target. The source trees of the retired Java payload client are
described in CHANGES.md.
