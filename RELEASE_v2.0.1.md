## OpenSlinky+ v2.0.1: polish & parity fixes :cherry_blossom:
**OpenSlinky+ by lallu**, built on OpenSlinky by **Skid Solutions**.

### What's new
- **Teams color list fixed:** the `Colors` setting now shows the 16 vanilla Minecraft color names (`Black`, `Dark blue`, `Gold`, `White`, etc.) instead of every block in the game.
- **Auto Tool "Allowed blocks" fixed:** the search list now returns blocks, not items.
- **Build cleaned up:** eliminated the remaining MSVC compiler warnings in `FontTables.cpp`, `Clutch.cpp`, `AntiBot.cpp` and `AutoSoup.cpp`.
- **Docs parity pass:** scraped and compared every module page on `docs.slinky.gg` against OpenSlinky+ settings. The full machine-readable report is included in the repo as `docs_comparison_report.json`.
- **Project tree cleaned:** active source moved to `C:\dev\OpenSlinkyPlus-main`; the stale `Documents\Default Project` tree was removed.
- **Version bumped** to `2.0.1` in `CMakeLists.txt`, `README.md` and `CHANGES.md`.

### Supported clients (Minecraft 1.8.9)
Forge · Vanilla · OptiFine · Lunar · Badlion · Legacy Fabric (experimental)

### Building
- Windows 64-bit, Visual Studio (or Build Tools) with **Desktop development with C++**, and **CMake 3.20 or newer**.
- Run `powershell -ExecutionPolicy Bypass -File .\build.ps1`. Python 3 is optional and only used for the export check.
- Output: `dist\OpenSlinkyPlus.exe` + `dist\SlinkyNative.dll` (keep them together), plus `build\lib\Release\shareable_modules.lib`.

### Also in the repo
- `SlinkyModules/recovery_reference/` holds reference material (decompiler views, readable ports, verification ledgers). It is documentation only and is not part of the build.
- `docs_comparison_report.json` contains the docs-vs-OpenSlinky+ module/setting comparison from this release.

### Notes
- Windows 64-bit, Minecraft 1.8.9 only.
- No new modules or payload remapping in this release; this is a bug-fix / parity release.
- Antivirus or SmartScreen may warn about this kind of program, because it loads a DLL into another process.

### Verify your download
SHA-256 of `OpenSlinkyPlus-v2.0.1.zip`: `1FCB0A8B3E867C8A8E8CED824BBA34B41140E2425CD5C4C27166308E0C98573D`
