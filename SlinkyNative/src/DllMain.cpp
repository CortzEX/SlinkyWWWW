#include <windows.h>
#include "Logger.hpp"
#include "JvmManager.hpp"
#include "MinecraftDetector.hpp"
#include "PayloadLoader.hpp"

static HMODULE g_hModule = nullptr;

DWORD WINAPI SlinkyNativeWorkerThread(LPVOID lpParam) {
    HMODULE hModule = (HMODULE)lpParam;

    SlinkyNative::Logger::Initialize(hModule);

    if (!SlinkyNative::JvmManager::Initialize()) {
        SlinkyNative::Logger::Log(L"FINAL STATUS: FAILED");
        return 1;
    }

    SlinkyNative::MinecraftInfo mcInfo;
    if (!SlinkyNative::MinecraftDetector::Detect(mcInfo)) {
        SlinkyNative::Logger::Log(L"FINAL STATUS: FAILED");
        return 1;
    }

    SlinkyNative::InjectionStatus status = SlinkyNative::PayloadLoader::LoadAndStart(hModule, mcInfo);

    return (status == SlinkyNative::InjectionStatus::Success || status == SlinkyNative::InjectionStatus::AlreadyRunning) ? 0 : 1;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
        g_hModule = (HMODULE)hinstDLL;
        DisableThreadLibraryCalls(hinstDLL);
        CreateThread(nullptr, 0, SlinkyNativeWorkerThread, (LPVOID)hinstDLL, 0, nullptr);
        break;
    case DLL_PROCESS_DETACH:
        SlinkyNative::JvmManager::Shutdown();
        SlinkyNative::Logger::Shutdown();
        break;
    }
    return TRUE;
}
