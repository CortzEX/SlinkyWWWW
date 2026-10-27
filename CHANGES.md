# Changes in this build

## OpenSlinky+ v2.0.3: payload StackMapTable crash fix

### What's new
- **Fixed `java.lang.ClassFormatError: StackMapTable format error: bad verification type` (opening the Slinky menu on Lunar / Java 17):** the payload `InlineModuleSettings.suggestions` method carried a corrupt stack map table written by the earlier bytecode patch — 7 frames where the patched body needs 3, plus frames at offsets beyond the end of the method and an invalid verification-type tag (0x10). Java 8 verifiers tolerated it; Java 9+ (Lunar, modern JDKs) do not.
- **All four payload jars rebuilt from pristine sources** (`slinky-named`, `slinky-official`, `slinky-srg`, `slinky-intermediary`) with the ASM tree API (`ClassReader` → `ClassNode` → replace method instructions → `ClassWriter(COMPUTE_FRAMES)`), so regenerated frames always match the new body. Suggestions behavior is unchanged: *Block ESP* / *Auto Tool* return the block list and *Teams* returns the 16 vanilla color names.
- **New release gate: `tools/verify_stackmaps.py`** — a spec-exact StackMapTable parser (JVMS 4.7.9) that validates frame tags, verification-type info, `ITEM_Object` / `ITEM_Uninitialized` payloads and frame offsets for every class in every payload jar (511 classes × 4 jars must pass).

This project is **OpenSlinky+ by lallu** (credits: Skid Solutions).

## OpenSlinky+ v2.0.2: Lunar menu crash fix

### What's new
- **Fixed immediate crash on Lunar Client when opening the Slinky menu:** removed the explicit `Mouse.setCursorPosition` call from the GUI open path; Lunar and several custom clients handle cursor warping internally when ungrabbing the mouse.
- **Fixed GUI "Allow input while open" interaction:** when this setting is enabled, the render loop no longer forces the mouse ungrabbed every frame, so the camera keeps working on Lunar/Badlion-style clients.

### Notes
- Windows 64-bit, Minecraft 1.8.9 only.
- This is a hotfix on top of v2.0.1.

## OpenSlinky+ v2.0.1: polish & parity fixes

### What's new
- **Teams color list fixed:** the `Colors` setting now shows the 16 vanilla Minecraft color names instead of every block in the game.
- **Auto Tool "Allowed blocks" fixed:** the search list now shows blocks instead of items.
- **Build cleaned up:** removed all MSVC compiler warnings (`FontTables.cpp`, `Clutch.cpp`, `AntiBot.cpp`, `AutoSoup.cpp`).
- **Docs parity pass:** every module page on `docs.slinky.gg` was scraped and compared against OpenSlinky+ settings. A full report is saved in `docs_comparison_report.json`.
- **Project relocated** to `C:\dev\OpenSlinkyPlus-main`; the stale `Documents\Default Project` tree was removed.
- **Version bumped** to `2.0.1` in `CMakeLists.txt`.

### Notes
- Windows 64-bit, Minecraft 1.8.9 only.
- No new modules or payload remapping in this release; this is a bug-fix / parity release.

## Root cause of "Slinky could not start" (`NoSuchMethodError: Minecraft.getMinecraft()`)
The original `slinky-srg.jar` / `slinky-official.jar` were NOT remapped: their bytecode still called
MCP names (`getMinecraft`, `gameSettings`, `rotationYaw` ...) and only a `mappings.txt` was added.
On any runtime that is not MCP-named (Forge = SRG, Vanilla/OptiFine/Lunar/Badlion = notch) the first
direct call crashed. `tools/verify_payload.py` finds 303 (srg) / 340 (official) stale references in the
old jars and 0 in the new ones.

## What changed
| File | Change |
|---|---|
| `SlinkyNative/payload/slinky-srg.jar`, `slinky-official.jar`, `slinky-named.jar`, `slinky-intermediary.jar` | Fully remapped payloads (from the BLC-Slinky work): srg for Forge, notch for Vanilla/OptiFine/Lunar/Badlion, intermediary for Legacy Fabric. |
| `SlinkyNative/src/PayloadLoader.cpp` | `addURL` is best-effort (JDK 9+ loaders are not URLClassLoaders); classes are defined directly in multiple dependency-aware passes; **new:** `addURL` is only called on real `URLClassLoader`s (calling it on anything else is undefined behaviour in JNI). **new:** the intermediary scheme aliases to the `official` Java namespace argument (`Platform$Namespace` has no intermediary value; the jar is byte-self-consistent) while logs and disk names stay `intermediary`. |
| `SlinkyNative/src/MinecraftDetector.cpp` | Rewritten: checks both `net/minecraft/client/Minecraft` and `ave`, finds the singleton field by type instead of one hard-coded name, waits until the game object exists (Lunar/Badlion load the class early), frees JNI refs while polling, logs loader class, and gives a diagnostic log for unknown naming schemes. **new:** third signature `net/minecraft/class_1600` (Legacy Fabric intermediary) with singleton `field_3774` and `method_2965` accessor fallback; unknown-scheme log now lists intermediary as supported. |
| `Slinky/src/Main.cpp` | Injects into the JVM that has LWJGL loaded (prefers titles with Minecraft/Lunar/Badlion) instead of the first Java window on the machine. |
| `Slinky/src/Injector.cpp` | Startup monitor timeout 30 s -> 150 s (Bootstrap can legitimately wait 2 min). |
| `build.ps1`, `tools/verify_payload.py` | One-command Windows build; static payload checker. |

## Not changed
`SlinkyClient/` (Java sources) is identical to upstream. Rebuilding it with Gradle only produces the *named* jar.

## Mouse stays free after the server closes the GUI (MMC queue, lobby changes, kicks)
When a server closed the click GUI, vanilla re-grabbed the mouse but the GUI module's tick handler released it again
(the module was still "enabled" for one more tick). Once disabled, `setIngameFocus()` did nothing because the game
already believed it had focus, leaving a visible cursor while the camera still turned.
`GuiModule` now (1) disables itself on the first tick where no OpenSlinky+ screen is open and (2) re-grabs the mouse
whenever the game owns the mouse but the cursor is free (`currentScreen == null`, `inGameHasFocus`, window active).
Applied to the Java source and patched into all three prebuilt jars (verified with the JVM bytecode verifier).

## Branding
Display names, chat prefix, GUI title, console banner/title/status messages, window title, READMEs and the output exe
(`OpenSlinkyPlus.exe`) now say OpenSlinky+ / lallu, with credits to Skid Solutions. Technical identifiers (packages,
`SlinkyNative.dll`, resource paths, `/slinky` command, config file names, log file names) are unchanged on purpose.
The Discord links were removed. `assets/` images and the `docs.slinky.gg` help links inside the GUI metadata are untouched.

## Aim assist with auto-click macros (mouse "fire key" at ~20 cps) and Hit Select
Aim assist's "require mouse pressed" gate read `Mouse.isButtonDown` once per tick. A macro presses the button for only a
few milliseconds per click, so most ticks saw "up", which cleared the target and restarted the 1-2 tick re-engage delay
every time. New helper `ClickTracker` samples the buttons every frame/event and keeps the gate on for 180 ms after the last
press. Clicks that Hit Select cancels (with or without fake swing) are reported to it as clicks, so aim assist keeps working
while Hit Select pauses your hits. Changed: `AimAssistModule` (gate + per-event sampling), `HitSelectModule` (one call when it
cancels an attack), new `ClickTracker`. Patched into all three prebuilt jars and verified with the JVM verifier.

## Module layer ported from Java to native C++ (2026-10-26)

The parts of OpenSlinky+ that the recovery packages replace are replaced. From this build on the
client's module implementations live in **SlinkyModules** (native C++), not in Java:

| Item | Change |
|---|---|
| `SlinkyModules/` (new) | The C++ module layer: `modules/` holds one portable source file per module (68 modules, matching the old Java catalog one-for-one) and `runtime/` holds the shared runtime (registry, dispatch, lifecycle, UI/settings, game access, fonts/canvas, profiles, JSON/config). Builds as the static `shareable_modules` library (C++20, `/fp:strict`); targets: `shareable_modules`, `shareable_module_objects`, `shareable_link_check` (offline symbol check). |
| `SlinkyModules/recovery_reference/` (new) | The accompanying recovery corpus: decompiler views for all 68 module labels, `clean/` readable C++ ports with verification JSONs, `behavior/` callback ports, manifests (`manifest.json`, `call_graph.json`) and `MODULE_RECOVERY_STANDARD.md`. Documentation/audit material only - not part of any build target. |
| `SlinkyClient/` (removed) | The Java client sources are retired: every module they implemented now has its native C++ counterpart in `SlinkyModules`, so the Java module layer is no longer part of the tree. Nothing else depended on it at build time or runtime. |
| `CMakeLists.txt`, `build.ps1`, `README.md`, `.gitignore` | Build wiring adapts: CMake 3.20 minimum, the module layer is built as a subdirectory and verified; `build.ps1 -CheckOnly` runs only the export verification. |
| `Slinky/`, `SlinkyNative/` (unchanged) | Loader, injector, JVM detection and payload embedding are untouched; all three prebuilt payload jars stay embedded resources in `SlinkyNative.dll`. |

Verification status in this tree: CMake configure + full Release build of `Slinky` + `SlinkyNative` +
`shareable_modules` succeed; the `shareable_link_check` target links cleanly (no missing definitions or
duplicate symbols); `VerifyExport.py` now returns a **full pass** (`"passed": true`, no failures) - the
packages were refreshed with the corrected exports that complete the package ledger: `woof` now ships
the missing `audits/` documentation set (7 root ledgers + 68 per-module audit pages) and `meow` now
ships the complete `behavior/module_behavior_recovery/` port set with its coverage ledger.

Module coverage is complete, so no third-party code was borrowed: the 68 modules implemented by the
retired Java layer (66 registered + Speed + Chest Stealer) all have native counterparts in
`SlinkyModules`, and the only catalog entry without any implementation anywhere remains the documented
`Scaffold c[BETA]` placeholder (RVA `0x0`, no recovered logic exists for it in any source pack, and
this port deliberately does not invent behavior that no evidence defines). Extra reference clients
supplied alongside (`chat-v4` / Vape V4 recode, `Myau.jar`, `RavenXD 3.2`) were reviewed for gaps and
are not integrated into this tree - their Java logic does not map to the recovered native ABI surfaces,
and their provenance is third-party.
