#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <iostream>

enum class LogLevel
{
    INFO,
    WARNING,
    ERROR,
    DEBUG
};

class Logger
{
public:
    Logger(LogLevel level = LogLevel::INFO); // Constructeur avec niveau par défaut

    // Méthodes de journalisation pour chaque niveau
    void info(const std::string &message) const;
    void warning(const std::string &message) const;
    void error(const std::string &message) const;
    void debug(const std::string &message) const;

    // Méthode pour définir le niveau de log
    void setLevel(LogLevel level);

private:
    LogLevel currentLevel;

    // Méthode pour afficher un message en fonction de son niveau
    void logMessage(const std::string &message, LogLevel level) const;

    // Méthode pour obtenir le préfixe coloré en fonction du niveau
    std::string getLevelPrefix(LogLevel level) const;
};

#endif // LOGGER_HPP
