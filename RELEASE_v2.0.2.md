## OpenSlinky+ v2.0.2: Lunar menu crash fix :cherry_blossom:
**OpenSlinky+ by lallu**, built on OpenSlinky by **Skid Solutions**.

### What's new
- **Fixed immediate crash on Lunar Client when opening the Slinky menu:** removed the explicit `Mouse.setCursorPosition` call from the GUI open path. Lunar (and several other custom clients) handle cursor warping internally when the mouse is ungrabbed, so the manual call was causing a native crash.
- **Fixed GUI "Allow input while open" behavior:** when this setting is enabled, the render loop no longer forces the mouse ungrabbed every frame, so the camera keeps working correctly on Lunar/Badlion-style clients.
- **Teams color list fixed (v2.0.1):** the `Colors` setting now shows the 16 vanilla Minecraft color names instead of every block in the game.
- **Auto Tool "Allowed blocks" fixed (v2.0.1):** the search list now returns blocks, not items.
- **Build cleaned up (v2.0.1):** eliminated the remaining MSVC compiler warnings.
- **Docs parity pass (v2.0.1):** scraped and compared every module page on `docs.slinky.gg` against OpenSlinky+ settings. The full report is included as `docs_comparison_report.json`.

### Supported clients (Minecraft 1.8.9)
Forge · Vanilla · OptiFine · Lunar · Badlion · Legacy Fabric (experimental)

### Building
- Windows 64-bit, Visual Studio (or Build Tools) with **Desktop development with C++**, and **CMake 3.20 or newer**.
- Run `powershell -ExecutionPolicy Bypass -File .\build.ps1`. Python 3 is optional and only used for the export check.
- Output: `dist\OpenSlinkyPlus.exe` + `dist\SlinkyNative.dll` (keep them together), plus `build\lib\Release\shareable_modules.lib`.

### Also in the repo
- `SlinkyModules/recovery_reference/` holds reference material (decompiler views, readable ports, verification ledgers). It is documentation only and is not part of the build.
- `docs_comparison_report.json` contains the docs-vs-OpenSlinky+ module/setting comparison.

### Notes
- Windows 64-bit, Minecraft 1.8.9 only.
- No new modules or payload remapping in this release; this is a bug-fix release.
- Antivirus or SmartScreen may warn about this kind of program, because it loads a DLL into another process.

### Verify your download
SHA-256 of `OpenSlinkyPlus-v2.0.2.zip`: `DBBCFAD1A40CC111AEB3D253F369EC582F28E620C8DB8C76749792C63D6B726B`
