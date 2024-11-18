#include "pch.h"
#include "exported_function.h"
#include <iostream>

extern "C" __declspec(dllexport) void PrintMessage() {
    std::cout << "Message depuis la DLL dynamique exported_function.cpp !" << std::endl;
}