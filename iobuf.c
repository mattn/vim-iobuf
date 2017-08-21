#include <windows.h>
#include <stdio.h>

static char libpath[MAX_PATH];

BOOL APIENTRY
DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
  if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
    char *p, *last;
    if (!GetModuleFileNameA((HMODULE)hModule, libpath, MAX_PATH))
      return FALSE;
    last = p = libpath + 1;
    while (*p) {
	  if (*p == '\\' || *p == '/') last = p;
	  p++;
    }
    *last = 0;
    strcat(libpath, "\\iobuf_inject.dll");
  }
  return TRUE;
}

__declspec(dllexport) int
no_buffer(int pid) {
  char errmsg[512];

  HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
  if (!hProcess)
	goto failed;
  LPVOID  pRemoteDLLName = (LPVOID)VirtualAllocEx(hProcess, NULL, MAX_PATH, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
  if (!pRemoteDLLName)
	goto failed;
  if (!WriteProcessMemory(hProcess, pRemoteDLLName, libpath, lstrlen(libpath), NULL))
	goto failed;
  LPVOID pLoadLibrary = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
  if (!pLoadLibrary)
	goto failed;
  HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pLoadLibrary, pRemoteDLLName, 0, NULL);
  if (!hThread)
	goto failed;
  WaitForSingleObject(hThread, INFINITE);
  CloseHandle(hThread);
  return 0;

failed:
  FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), 0, errmsg, sizeof(errmsg), NULL);
  printf("%hs", errmsg);
  return 1;
}
