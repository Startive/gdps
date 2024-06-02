#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>
#include <string.h>

// not working for now

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
    UINT8 *getGJSongInfo = (UINT8*)(base + 0x2CDF44);

    // change them
    for (int i = 0; i < 52; i++) {
        printf("0x%X/%c ", getGJSongInfo[i], getGJSongInfo[i]);
    }

    printf("\n");

    // debug
    printf("%lu\n", base);

    while (!GetAsyncKeyState(0x51));

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