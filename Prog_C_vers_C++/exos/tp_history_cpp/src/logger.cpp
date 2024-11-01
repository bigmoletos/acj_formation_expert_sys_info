#include "logger.hpp"

// Initialisation du logger global avec le niveau par défaut
Logger logger(LogLevel::DEFAULT);
/**
 * @brief Constructeur de la classe Logger
 * @param level Niveau de log initial
 */
Logger::Logger(LogLevel level) : currentLevel(level) {}

/**
 * @brief Définit le niveau de journalisation souhaité
 * @param level Niveau de log
 */
void Logger::setLevel(LogLevel level)
{
    currentLevel = level;
}

/**
 * @brief Affiche un message d'information si le niveau est suffisant
 * @param message Message à afficher
 */
void Logger::info(const std::string &message) const
{
    logMessage(message, LogLevel::INFO);
}

/**
 * @brief Affiche un message d'avertissement si le niveau est suffisant
 * @param message Message à afficher
 */
void Logger::warning(const std::string &message) const
{
    logMessage(message, LogLevel::WARNING);
}

/**
 * @brief Affiche un message d'erreur si le niveau est suffisant
 * @param message Message à afficher
 */
void Logger::error(const std::string &message) const
{
    logMessage(message, LogLevel::ERROR);
}
/**
 * @brief Affiche un message d'erreur si le niveau est suffisant
 * @param message Message à afficher
 */
void Logger::critical(const std::string &message) const
{
    logMessage(message, LogLevel::CRITICAL);
}

/**
 * @brief Affiche un message de débogage si le niveau est suffisant
 * @param message Message à afficher
 */
void Logger::debug(const std::string &message) const
{
    logMessage(message, LogLevel::DEBUG);
}

/**
 * @brief Affiche un message avec un préfixe coloré en fonction de son niveau de log
 * @param message Message à afficher
 * @param level Niveau du message
 */
void Logger::logMessage(const std::string &message, LogLevel level) const
{
    if (level <= currentLevel)
    {
        std::cout << getLevelPrefix(level) << message << "\033[0m" << std::endl;
    }
}

/**
 * @brief Renvoie un préfixe coloré en fonction du niveau de log
 * @param level Niveau du message
 * @return Préfixe coloré pour le message
 */
std::string Logger::getLevelPrefix(LogLevel level) const
{
    switch (level)
    {
    case LogLevel::INFO:
        return "\033[32m[INFO] "; // Vert
    case LogLevel::WARNING:
        return "\033[33m[WARNING] "; // Jaune
    case LogLevel::ERROR:
        return "\033[31m[ERROR] "; // Rouge
    case LogLevel::DEBUG:
        return "\033[34m[DEBUG] "; // Bleu
    case LogLevel::CRITICAL:
        return "\033[41m[CRITICAL] "; // rouge sur fond rouge
    default:
        return "[UNKNOWN] ";
    }
}
