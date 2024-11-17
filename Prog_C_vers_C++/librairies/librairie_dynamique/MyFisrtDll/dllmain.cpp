#include "pch.h"
#include "exported_function.h"

// Utiliser DllMain uniquement pour des opérations sûres.
BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        // Ne pas utiliser std::cout ici, déplacer le message dans une fonction exportée.
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
