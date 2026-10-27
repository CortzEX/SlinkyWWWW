# Callback C++ ports

[manifest.json](manifest.json) maps 74 C-derived components to all 170 distinct registered callback bodies. The source copies are work in progress: 43 compile as C++20, and twelve components covering 43 callback bodies have been compared with the original instructions. They are not a complete module implementation.

| Component | Callback bodies | Original-instruction cases |
| --- | ---: | ---: |
| [Sprint](recovered_native_source/sprint_behavior.cpp) | 2 | [3,456](sprint_behavior_cpp_verification.json) |
| [Auto Clicker](module_behavior_recovery/auto_clicker/auto_clicker.cpp) | 3 | [310](auto_clicker_cpp_verification.json) |
| [Fake Lag](module_behavior_recovery/fake_lag/fake_lag.cpp) | 2 | [6,477](fake_lag_cpp_verification.json) |
| [Sprint Reset](module_behavior_recovery/sprint_reset/sprint_reset.cpp) | 1 | [3,315](sprint_reset_cpp_verification.json) |
| [Notifications](module_behavior_recovery/notifications/notifications.cpp) | 5 | [388](notifications_cpp_verification.json) |
| [Velocity](module_behavior_recovery/velocity/velocity.cpp) | 7 | [401](velocity_cpp_verification.json) |
| [GUI](module_behavior_recovery/gui/gui.cpp) | 5 | [534](gui_cpp_verification.json) |
| [Block In events](module_behavior_recovery/block_in_events/block_in_events.cpp) | 4 | [198](block_in_events_cpp_verification.json) |
| [Debug](module_behavior_recovery/debug/debug.cpp) | 4 | [649](debug_cpp_verification.json) |
| [Timer and Free Look](module_behavior_recovery/state_events/state_events.cpp) | 4 | [2,852](state_events_cpp_verification.json) |
| [Timer Range events](module_behavior_recovery/timer_range_events/timer_range_events.cpp) | 3 | [467](timer_range_events_cpp_verification.json) |
| [Keep Sprint](module_behavior_recovery/keep_sprint/keep_sprint.cpp) | 3 | [1,730](keep_sprint_cpp_verification.json) |

These tests execute the original callback instructions in bounded Unicorn. They compare returned values, state changes, and calls at controlled game and helper boundaries. Keep Sprint retains two recorded NaN payload differences caused by Unicorn and host SSE selecting different payloads for the same multiply operand order. The tests do not verify full live gameplay, event registration, UI, or settings.

From a Visual Studio x64 developer shell at the workspace root, rerun the C++ checks with outer timeouts:

```powershell
py -3 -c "import subprocess,sys; subprocess.run([sys.executable,'analysis/recovered_native_source/verify_sprint_behavior.py','--cpp'],check=True,timeout=180)"
py -3 -c "import subprocess,sys; subprocess.run([sys.executable,'analysis/module_behavior_recovery/auto_clicker/verify.py','--cpp'],check=True,timeout=180)"
py -3 -c "import subprocess,sys; subprocess.run([sys.executable,'analysis/module_behavior_recovery/fake_lag/verify_fake_lag.py','--cpp'],check=True,timeout=240)"
py -3 -c "import subprocess,sys; subprocess.run([sys.executable,'analysis/module_behavior_recovery/sprint_reset/verify_sprint_reset.py','--cpp'],check=True,timeout=240)"
py -3 -c "import subprocess,sys; subprocess.run([sys.executable,'analysis/module_behavior_recovery/notifications/verify.py','--cpp'],check=True,timeout=180)"
py -3 -c "import subprocess,sys; subprocess.run([sys.executable,'analysis/module_behavior_recovery/velocity/verify.py','--cpp'],check=True,timeout=180)"
py -3 -c "import subprocess,sys; subprocess.run([sys.executable,'analysis/module_behavior_recovery/gui/verify.py','--cpp'],check=True,timeout=180)"
py -3 -c "import subprocess,sys; subprocess.run([sys.executable,'analysis/module_behavior_recovery/block_in_events/verify.py','--cpp'],check=True,timeout=180)"
py -3 -c "import subprocess,sys; subprocess.run([sys.executable,'analysis/module_behavior_recovery/debug/verify.py','--cpp'],check=True,timeout=180)"
py -3 -c "import subprocess,sys; subprocess.run([sys.executable,'analysis/module_behavior_recovery/state_events/verify.py','--cpp'],check=True,timeout=180)"
py -3 -c "import subprocess,sys; subprocess.run([sys.executable,'analysis/module_behavior_recovery/timer_range_events/verify.py','--cpp'],check=True,timeout=180)"
py -3 -c "import subprocess,sys; subprocess.run([sys.executable,'analysis/module_behavior_recovery/keep_sprint/verify_keep_sprint.py','--cpp'],check=True,timeout=240)"
```
