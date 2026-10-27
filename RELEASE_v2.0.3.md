## OpenSlinky+ v2.0.3: payload StackMapTable crash fix :cherry_blossom:
**OpenSlinky+ by CortzEX**, built on OpenSlinky by **Skid Solutions**.

### What's new
- **Fixed `java.lang.ClassFormatError: StackMapTable format error: bad verification type` on Lunar / Java 17 (menu open crash):** the payload `InlineModuleSettings.suggestions` method carried a corrupt stack map table from the earlier bytecode patch. All four payload jars were rebuilt from pristine sources with the ASM tree API + `COMPUTE_FRAMES`, so every frame now matches the patched bytecode; the rebuilt classes pass a spec-exact StackMapTable validator (511 classes × 4 jars) and ASM's full dataflow analyzer.
- **Suggestions behavior unchanged:** *Block ESP* / *Auto Tool* return the block list, *Teams* returns the 16 vanilla color names, everything else returns the default item list.
- **Lunar native crash fixed (v2.0.2):** removed the explicit `Mouse.setCursorPosition` call from the GUI open path; Lunar and several custom clients handle cursor warping internally when the mouse is ungrabbed.
- **Teams color list fixed (v2.0.1):** the `Colors` setting now shows the 16 vanilla Minecraft color names instead of every block in the game.
- **Auto Tool "Allowed blocks" fixed (v2.0.1):** the search list now returns blocks, not items.

### Supported clients (Minecraft 1.8.9)
Forge · Vanilla · OptiFine · Lunar · Badlion · Legacy Fabric (experimental)

### Building
- Windows 64-bit, Visual Studio (or Build Tools) with **Desktop development with C++**, and **CMake 3.20 or newer**.
- Run `powershell -ExecutionPolicy Bypass -File .\build.ps1`. Python 3 is optional and only used for the export check.
- Output: `dist\OpenSlinkyPlus.exe` + `dist\SlinkyNative.dll` (keep them together), plus `build\lib\Release\shareable_modules.lib`.

### Also in the repo
- `tools/verify_stackmaps.py` — StackMapTable validator (JVMS 4.7.9) used as the release gate for the payload jars.
- `SlinkyModules/recovery_reference/` holds reference material (decompiler views, readable ports, verification ledgers). It is documentation only and is not part of the build.
- `docs_comparison_report.json` contains the docs-vs-OpenSlinky+ module/setting comparison.

### Notes
- Windows 64-bit, Minecraft 1.8.9 only.
- Antivirus or SmartScreen may warn about this kind of program, because it loads a DLL into another process.

### Verify your download
SHA-256 of `OpenSlinkyPlus-v2.0.3.zip`: `FBE04FABB6369A7E97C1DAA066FD54A53B0453366775DEA21FCBE69132EC0F04`
