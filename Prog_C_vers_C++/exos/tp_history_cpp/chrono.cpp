#include "header.hpp"
#include <iostream>



void chrono_start(std::chrono::high_resolution_clock::time_point &t1)
{
    t1 = std::chrono::high_resolution_clock::now();
}

void chrono_end(const std::chrono::high_resolution_clock::time_point &t1, const std::string &message)
{
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << message << ": " << duration << " ms" << std::endl;
}