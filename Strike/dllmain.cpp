// dllmain.cpp : Defines the entry point for the DLL application.
#include "framework.h"

__declspec(dllexport) bool WINAPI DllMain(HINSTANCE hInstDll, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
	Game::Setup();
        break;
    }
    return true;
}


