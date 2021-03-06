//
// author: Lasha Khasaia
// contact: @_qaz_qaz
// license: MIT License
//

#include "stdafx.h"

#include "hook.h"

#define NO_MSG_BOX


VOID DoWork()
{
#ifdef _DEBUG
#ifndef NO_MSG_BOX
	MessageBox(nullptr, L"DLL injected successfully", L"Debug Mode", MB_ICONINFORMATION);
#endif
#endif

	Hook hook;
	if (!hook.HookFuncs())
	{
		OutputDebugString(L"Hooking Failed");
		ExitProcess(ERROR_SUCCESS);
	}
}


BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved
)
{
	UNREFERENCED_PARAMETER(hModule);
	UNREFERENCED_PARAMETER(lpReserved);

	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		// Reduce the size of the working set for some applications https://blogs.msdn.microsoft.com/larryosterman/2004/06/03/little-known-win32-apis-disablethreadlibrarycalls/
		DisableThreadLibraryCalls(hModule);

		DoWork();
	}

	return TRUE;
}
