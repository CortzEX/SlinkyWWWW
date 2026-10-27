# One file per module

Each of the 68 module files contains its recovered declarations, settings/state views,
UI/configuration code, callback bodies and local helpers. The shared runtime is packaged
once. Share this folder or ZIP; individual module files also need the runtime folder.

The files use consistent formatting and descriptive filenames. Existing semantic APIs
remain available. `shareable::<ModuleName>` adds a borrowed-image settings interface;
callbacks that use a borrowed image also appear as instance methods. Other recovered
entry points retain their typed parameters as static methods. Existing typed module
classes are reused directly. Some modules retain native ABI structures and parameters
because the evidence does not establish a safer higher-level replacement.

This is a source reorganization of the audited reconstruction, not a new equivalence
claim. Every original implementation segment is checked for unchanged C++ tokens after
reversing its documented internal-function renames and include relocation. Shared support
headers contain cross-module API declarations; those declarations also appear in the
owning module file. Matching include guards ensure they are defined only once per unit.

Recovery is still incomplete. GUI state transform 0x129B0, protected TLS/PE startup and
the earlier provenance of mutable bindings/default values remain unproved. Captured
current/saved values are not defaults. Speed and Chest Stealer are unregistered intervals.
The per-module audits retain the detailed boundaries. No unresolved behavior is replaced
with a guessed implementation.

## Build

Windows x64, Visual Studio 2022, C++20. Preserve `/fp:strict`.

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release --target shareable_modules --parallel 4
```

The separate `shareable_link_check` target checks the complete object set for missing
definitions and duplicate symbols. It is an offline link check, not a plugin entry point.
`BuildVerification.json` records the bounded compilation/link result. `ExportManifest.json`
records source hashes, ownership and identifier renames. `VerifyExport.py` rechecks the
package against its recorded hashes and token ledger without needing the original tree.

```powershell
python VerifyExport.py
```

## Modules

| Module | File | Captured settings |
| --- | --- | --- |
| Aim Assist | [AimAssist.cpp](modules/AimAssist.cpp) | 22 |
| Anti Bot | [AntiBot.cpp](modules/AntiBot.cpp) | 6 |
| Anti Debuff | [AntiDebuff.cpp](modules/AntiDebuff.cpp) | 2 |
| Auto Block | [AutoBlock.cpp](modules/AutoBlock.cpp) | 12 |
| Auto Clicker | [AutoClicker.cpp](modules/AutoClicker.cpp) | 9 |
| Auto Pot | [AutoPot.cpp](modules/AutoPot.cpp) | 4 |
| Auto Rod | [AutoRod.cpp](modules/AutoRod.cpp) | 7 |
| Auto Soup | [AutoSoup.cpp](modules/AutoSoup.cpp) | 9 |
| Auto Tool | [AutoTool.cpp](modules/AutoTool.cpp) | 9 |
| Auto Weapon | [AutoWeapon.cpp](modules/AutoWeapon.cpp) | 2 |
| Backtrack | [Backtrack.cpp](modules/Backtrack.cpp) | 12 |
| Blink | [Blink.cpp](modules/Blink.cpp) | 5 |
| Block ESP | [BlockESP.cpp](modules/BlockESP.cpp) | 5 |
| Block In | [BlockIn.cpp](modules/BlockIn.cpp) | 2 |
| Bridge Assist | [BridgeAssist.cpp](modules/BridgeAssist.cpp) | 10 |
| Chams | [Chams.cpp](modules/Chams.cpp) | 1 |
| Chest ESP | [ChestESP.cpp](modules/ChestESP.cpp) | 11 |
| Chest Stealer | [ChestStealer.cpp](modules/ChestStealer.cpp) | 5 |
| Clutch | [Clutch.cpp](modules/Clutch.cpp) | 18 |
| Criticals | [Criticals.cpp](modules/Criticals.cpp) | 7 |
| Debug | [Debug.cpp](modules/Debug.cpp) | 3 |
| Fake Lag | [FakeLag.cpp](modules/FakeLag.cpp) | 7 |
| Fast Accel | [FastAccel.cpp](modules/FastAccel.cpp) | 3 |
| Fast Mine | [FastMine.cpp](modules/FastMine.cpp) | 3 |
| Fast Place | [FastPlace.cpp](modules/FastPlace.cpp) | 2 |
| Free Look | [FreeLook.cpp](modules/FreeLook.cpp) | 1 |
| Friends | [Friends.cpp](modules/Friends.cpp) | 2 |
| Ghost Hand | [GhostHand.cpp](modules/GhostHand.cpp) | 12 |
| GUI | [GUI.cpp](modules/GUI.cpp) | 5 |
| Hit Select | [HitSelect.cpp](modules/HitSelect.cpp) | 12 |
| Hitboxes | [Hitboxes.cpp](modules/Hitboxes.cpp) | 1 |
| Indicators | [Indicators.cpp](modules/Indicators.cpp) | 6 |
| Instant Stop | [InstantStop.cpp](modules/InstantStop.cpp) | 0 |
| Inv Manager | [InvManager.cpp](modules/InvManager.cpp) | 16 |
| Inv Walk | [InvWalk.cpp](modules/InvWalk.cpp) | 4 |
| Item ESP | [ItemESP.cpp](modules/ItemESP.cpp) | 5 |
| Item Use Fix | [ItemUseFix.cpp](modules/ItemUseFix.cpp) | 0 |
| Keep Sprint | [KeepSprint.cpp](modules/KeepSprint.cpp) | 4 |
| Knockback Delay | [KnockbackDelay.cpp](modules/KnockbackDelay.cpp) | 7 |
| Knockback Displace | [KnockbackDisplace.cpp](modules/KnockbackDisplace.cpp) | 9 |
| Lag Range | [LagRange.cpp](modules/LagRange.cpp) | 8 |
| Mod Overlay | [ModOverlay.cpp](modules/ModOverlay.cpp) | 14 |
| Name Tags | [NameTags.cpp](modules/NameTags.cpp) | 12 |
| No Hit Delay | [NoHitDelay.cpp](modules/NoHitDelay.cpp) | 1 |
| No Hurt Cam | [NoHurtCam.cpp](modules/NoHurtCam.cpp) | 0 |
| No Item Release | [NoItemRelease.cpp](modules/NoItemRelease.cpp) | 1 |
| No Jump Delay | [NoJumpDelay.cpp](modules/NoJumpDelay.cpp) | 0 |
| No Slow | [NoSlow.cpp](modules/NoSlow.cpp) | 3 |
| No Use Delay | [NoUseDelay.cpp](modules/NoUseDelay.cpp) | 1 |
| Notifications | [Notifications.cpp](modules/Notifications.cpp) | 8 |
| Null Move | [NullMove.cpp](modules/NullMove.cpp) | 0 |
| Piercing | [Piercing.cpp](modules/Piercing.cpp) | 8 |
| Ping Fix | [PingFix.cpp](modules/PingFix.cpp) | 0 |
| Player ESP | [PlayerESP.cpp](modules/PlayerESP.cpp) | 13 |
| Pointers | [Pointers.cpp](modules/Pointers.cpp) | 13 |
| Reach | [Reach.cpp](modules/Reach.cpp) | 3 |
| Refill | [Refill.cpp](modules/Refill.cpp) | 8 |
| Safe Walk | [SafeWalk.cpp](modules/SafeWalk.cpp) | 4 |
| Speed | [Speed.cpp](modules/Speed.cpp) | 2 |
| Sprint | [Sprint.cpp](modules/Sprint.cpp) | 4 |
| Sprint Reset | [SprintReset.cpp](modules/SprintReset.cpp) | 6 |
| Strafe | [Strafe.cpp](modules/Strafe.cpp) | 5 |
| Teams | [Teams.cpp](modules/Teams.cpp) | 2 |
| Timer | [Timer.cpp](modules/Timer.cpp) | 4 |
| Timer Range | [TimerRange.cpp](modules/TimerRange.cpp) | 9 |
| Trajectories | [Trajectories.cpp](modules/Trajectories.cpp) | 7 |
| Velocity | [Velocity.cpp](modules/Velocity.cpp) | 14 |
| Weapons | [Weapons.cpp](modules/Weapons.cpp) | 16 |
