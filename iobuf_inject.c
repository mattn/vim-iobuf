#include <windows.h>
#include <stdio.h>

BOOL APIENTRY
DllMain(
    HANDLE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved ) {
  if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
    setbuf(stdout, NULL);
  }
  return TRUE;
}

/* vim:set et st=2 ts=2: */
