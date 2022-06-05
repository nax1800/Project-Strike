// dllmain.cpp : Defines the entry point for the DLL application.
#include "framework.h"

__declspec(dllexport) bool WINAPI DllMain(HINSTANCE hInstDll, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
    {
		Game::Setup();
        break;
    }

    case DLL_PROCESS_DETACH:
    {
        break;
    }

    case DLL_THREAD_ATTACH:
    {
        break;
    }

    case DLL_THREAD_DETACH:
    {
        break;
    }
    }
    return true;
}


