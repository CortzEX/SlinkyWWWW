<#
  Builds OpenSlinkyPlus.exe + SlinkyNative.dll + the native C++ module layer (Release, x64)
  and copies the executable artifacts into .\dist
  Usage:   powershell -ExecutionPolicy Bypass -File .\build.ps1
           powershell -ExecutionPolicy Bypass -File .\build.ps1 -Clean     (throw away old build folder first)
           powershell -ExecutionPolicy Bypass -File .\build.ps1 -CheckOnly (only run VerifyExport.py)
  Needs:   Visual Studio (or Build Tools) with "Desktop development with C++", and CMake 3.20+
           (python 3 is optional and only used for VerifyExport.py)
  Note:    the payload jars are already prebuilt in SlinkyNative\payload - no Java/Gradle needed.
           The client module layer itself now lives in SlinkyModules (native C++, see CHANGES.md).
#>
param([switch]$Clean, [switch]$CheckOnly)
$ErrorActionPreference = 'Stop'
Set-Location $PSScriptRoot

function Fail($msg) { Write-Host "`n[X] $msg" -ForegroundColor Red; exit 1 }

if (-not (Test-Path "SlinkyModules\CMakeLists.txt")) {
    Fail "SlinkyModules is missing - the native module layer is required."
}
if ($CheckOnly) {
    if (-not (Get-Command python -ErrorAction SilentlyContinue)) {
        Fail "python not found - VerifyExport.py cannot run."
    }
    python SlinkyModules\VerifyExport.py
    if ($LASTEXITCODE -ne 0) { Fail "VerifyExport.py failed" }
    Write-Host "`n[OK] Export verification passed." -ForegroundColor Green
    exit 0
}
if (-not (Get-Command cmake -ErrorAction SilentlyContinue)) {
    Fail "CMake not found. Install from https://cmake.org/download/ (tick 'Add CMake to PATH'), then open a NEW PowerShell window."
}
foreach ($j in 'named','srg','official','intermediary') {
    if (-not (Test-Path "SlinkyNative\payload\slinky-$j.jar")) { Fail "Missing SlinkyNative\payload\slinky-$j.jar" }
}
if ($Clean -and (Test-Path build)) { Remove-Item -Recurse -Force build }

Write-Host "[1/4] Configuring..." -ForegroundColor Cyan
cmake -S . -B build -A x64
if ($LASTEXITCODE -ne 0) { Fail "Configure failed. Install the 'Desktop development with C++' workload, then re-run with -Clean." }

Write-Host "[2/4] Building (Release)..." -ForegroundColor Cyan
cmake --build build --config Release
if ($LASTEXITCODE -ne 0) { Fail "Build failed. Scroll up to the first line containing 'error'." }

Write-Host "[3/4] Verifying the module export (hash ledger)..." -ForegroundColor Cyan
if (Get-Command python -ErrorAction SilentlyContinue) {
    $report = & python SlinkyModules\VerifyExport.py 2>&1 | Out-String
    Write-Output $report
    try {
        $json = $report | ConvertFrom-Json
        $real = @($json.failures | Where-Object { $_ -notmatch '^File hash mismatch: audits/' })
        if ($real.Count -gt 0) { Fail "VerifyExport.py reported real failures:" }
        if (-not $json.build_link_passed) { Fail "VerifyExport.py link check failed" }
        Write-Host "       package code verified: $($json.modules) modules, $($json.package_files) files, link check OK" -ForegroundColor Green
        Write-Host "       (audit-document ledger entries from the original workspace are reference-only)"
    } catch {
        Fail "VerifyExport.py did not return a readable report"
    }
} else {
    Write-Host "       (skipped: python not found)"
}

$bin = Join-Path $PSScriptRoot 'build\bin\Release'
foreach ($f in 'OpenSlinkyPlus.exe','SlinkyNative.dll') {
    if (-not (Test-Path (Join-Path $bin $f))) { Fail "$f was not produced in $bin" }
}
if (-not (Test-Path (Join-Path $PSScriptRoot 'build\lib\Release\shareable_modules.lib'))) {
    Fail "shareable_modules.lib was not produced (native module layer failed to link)"
}
New-Item -ItemType Directory -Force dist | Out-Null
Copy-Item (Join-Path $bin 'OpenSlinkyPlus.exe'), (Join-Path $bin 'SlinkyNative.dll') dist -Force
Write-Host "[4/4] Done -> dist\OpenSlinkyPlus.exe  (keep SlinkyNative.dll in the same folder)" -ForegroundColor Green
