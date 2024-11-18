#ifdef _WIN32
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

extern "C" DLL_EXPORT void PrintMessage();

//#ifndef EXPORTED_FUNCTIONS_H
//#define EXPORTED_FUNCTIONS_H
//
//#ifdef _WIN32
//  #ifdef BUILD_DLL
//    #define DLL_EXPORT __declspec(dllexport)
//  #else
//    #define DLL_EXPORT __declspec(dllimport)
//  #endif
//#else
//  #define DLL_EXPORT
//#endif
//
//// Déclaration de la fonction exportée
//extern "C" DLL_EXPORT void PrintMessage();
//
//#endif // EXPORTED_FUNCTIONS_H

