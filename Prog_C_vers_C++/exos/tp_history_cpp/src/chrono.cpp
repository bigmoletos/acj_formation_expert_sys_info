#include "chrono.hpp"
#include <iostream>
#include "logger.hpp" // Inclusion du fichier logger


/**
 * @brief [Description de chrono_start]
 *
 * @param &t1 [Description du paramètre]
 * @return void [Description du retour]
 */
void chrono_start(std::chrono::high_resolution_clock::time_point &t1)
{
    t1 = std::chrono::high_resolution_clock::now();
}

/**
 * @brief [Description de chrono_end]
 *
 * @param &t1 [Description du paramètre]
 * @param &message [Description du paramètre]
 * @return void [Description du retour]
 */
void chrono_end(const std::chrono::high_resolution_clock::time_point &t1, const std::string &message)
{
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    // std::cout << message << ": " << duration << " ms" << std::endl;
    logger.info(message + ": " + std::to_string(duration) + " ms");
}