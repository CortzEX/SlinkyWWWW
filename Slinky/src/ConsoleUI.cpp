#include "ConsoleUI.hpp"
#include <cstdio>
#include <cstring>

namespace Slinky {

CRITICAL_SECTION ConsoleUI::s_CriticalSection;
char ConsoleUI::s_StatusText[512] = { 0 };
std::atomic<bool> ConsoleUI::s_Running(false);
HANDLE ConsoleUI::s_hAnimationThread = nullptr;
DWORD ConsoleUI::s_OriginalConsoleMode = 0;
HANDLE ConsoleUI::s_hConsole = INVALID_HANDLE_VALUE;

void ConsoleUI::PrintBanner() {
    const char* bannerLines[] = {
        "   _____ __    _     __",
        "  / ___// /__ (_)___/ /",
        "  \\__ \\/ //_// / __  / ",
        " ___/ / ,<  / / /_/ /  ",
        "/____/_/|_|/_/\\__,_/   ",
        "   _____       __      __  _                 ",
        "  / ___/____  / /_  __/ /_(_)___  ____  _____",
        "  \\__ \\/ __ \\/ / / / / __/ / __ \\/ __ \\/ ___/",
        " ___/ / /_/ / / /_/ / /_/ / /_/ / / / (__  ) ",
        "/____/\\____/_/\\__,_/\\__/_/\\____/_/ /_/____/  "
    };

    for (size_t lineIdx = 0; lineIdx < 10; ++lineIdx) {
        const char* line = bannerLines[lineIdx];
        size_t blockWidth = (lineIdx < 5) ? 24 : 45;
        size_t len = strlen(line);
        for (size_t i = 0; i < len; ++i) {
            float ratio = (float)i / (float)(blockWidth - 1);
            if (ratio > 1.0f) ratio = 1.0f;
            int val = (int)(255 - ratio * 200.0f);
            if (val < 45) val = 45;
            printf("\x1b[38;2;%d;%d;%dm%c", val, val, val, line[i]);
        }
        printf("\x1b[0m\n");
    }
    printf("\n");
    fflush(stdout);
}

void ConsoleUI::Initialize() {
    InitializeCriticalSection(&s_CriticalSection);
    s_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (s_hConsole != INVALID_HANDLE_VALUE) {
        GetConsoleMode(s_hConsole, &s_OriginalConsoleMode);
        SetConsoleMode(s_hConsole, s_OriginalConsoleMode | 0x0004);
    }

    SetConsoleTitleW(L"Slinky");
    strcpy_s(s_StatusText, "SCANNING");

    PrintBanner();
}

void ConsoleUI::Shutdown() {
    StopAnimation();
    if (s_hConsole != INVALID_HANDLE_VALUE && s_OriginalConsoleMode != 0) {
        SetConsoleMode(s_hConsole, s_OriginalConsoleMode);
    }
    DeleteCriticalSection(&s_CriticalSection);
}

void ConsoleUI::SetStatusText(const char* text) {
    EnterCriticalSection(&s_CriticalSection);
    strncpy_s(s_StatusText, text, _TRUNCATE);
    LeaveCriticalSection(&s_CriticalSection);
}

void ConsoleUI::PrintError(const char* action, DWORD errorCode) {
    wchar_t* msgBuf = nullptr;
    FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPWSTR)&msgBuf, 0, nullptr);

    char errorStr[512] = "unknown";
    if (msgBuf) {
        WideCharToMultiByte(CP_UTF8, 0, msgBuf, -1, errorStr, 512, nullptr, nullptr);
        LocalFree(msgBuf);

        size_t len = strlen(errorStr);
        while (len > 0 && (errorStr[len - 1] == '\r' || errorStr[len - 1] == '\n')) {
            errorStr[--len] = '\0';
        }
    }

    EnterCriticalSection(&s_CriticalSection);
    printf("\n[!] %s failed with error %lu: %s\n", action, errorCode, errorStr);
    fflush(stdout);
    LeaveCriticalSection(&s_CriticalSection);
}

void ConsoleUI::StartAnimation() {
    if (s_Running) return;
    s_Running = true;
    s_hAnimationThread = CreateThread(nullptr, 0, AnimationThread, nullptr, 0, nullptr);
}

void ConsoleUI::StopAnimation() {
    if (!s_Running) return;
    s_Running = false;
    if (s_hAnimationThread) {
        WaitForSingleObject(s_hAnimationThread, 1000);
        CloseHandle(s_hAnimationThread);
        s_hAnimationThread = nullptr;
    }
    printf("\n");
    fflush(stdout);
}

DWORD WINAPI ConsoleUI::AnimationThread(LPVOID lpParam) {
    const char* spinner[] = { "-", "\\", "|", "/" };
    int frame = 0;

    while (s_Running) {
        char currentStatus[512] = { 0 };
        EnterCriticalSection(&s_CriticalSection);
        strncpy_s(currentStatus, s_StatusText, _TRUNCATE);
        LeaveCriticalSection(&s_CriticalSection);

        printf("\r\x1b[2K  [%s] %s", spinner[frame % 4], currentStatus);
        fflush(stdout);

        frame++;
        Sleep(160);
    }

    char finalStatus[512] = { 0 };
    EnterCriticalSection(&s_CriticalSection);
    strncpy_s(finalStatus, s_StatusText, _TRUNCATE);
    LeaveCriticalSection(&s_CriticalSection);

    printf("\r\x1b[2K  [+] %s\n", finalStatus);
    fflush(stdout);

    return 0;
}

} // namespace Slinky
