#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <psapi.h>
#include <stdio.h>
#include <string.h>

// useless it just don't want to work :/


FILE *CreateConsole() {
    AllocConsole();
    static FILE *fp = NULL;
    freopen_s(&fp, "CONOUT$", "w", stdout);

    return fp;
}

void Thread(HMODULE hModule) {
    FILE *fp = CreateConsole();

    // get all the memory addresses to string blah blah adaa df d-9w
    DWORD base = (DWORD)GetModuleHandle(0);
    LPVOID memory = VirtualAlloc(NULL, 100, MEM_COMMIT | HEAP_ZERO_MEMORY, PAGE_READWRITE);
    UINT8 *getGJSongInfo = (UINT8*)(base + 0x2CDF44);

    strcpy(getGJSongInfo, "hello guys welcome back to my youtube channel");

    // debug
    printf("%lu\n", base);
    printf("%s\n", getGJSongInfo);
    while (!GetAsyncKeyState(0x51)); // q key

    FreeConsole();
    fclose(fp);
    FreeLibraryAndExitThread(hModule, 0);
}

int WINAPI DllMain(HMODULE hModule, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread, (LPVOID)hModule, 0, NULL);
    }

    return TRUE;
}