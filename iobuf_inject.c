#include <windows.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

BOOL APIENTRY
DllMain(
    HANDLE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved ) {
  if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
    FILE* hf = _fdopen(_open_osfhandle(
            (intptr_t)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT), "w");
    *stdout = *hf;
    setvbuf(stdout, NULL, _IONBF, 0);
  }
  return TRUE;
}

/* vim:set et st=2 ts=2: */
