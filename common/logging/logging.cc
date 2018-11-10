
#include "logging.h"
#include <ctime>

enum Color
{
    DEFAULT,
    RED,
    BLUE,
    GREEN,
    YELLOW
};

std::map<int, std::string> colors = {
    {Color::DEFAULT, ""},
    {Color::RED, "\033[1;31m"},
    {Color::BLUE, "\033[1;34m"},
    {Color::YELLOW, "\033[1;33m"},
    {Color::GREEN, "\033[1;32m"},
};

std::string getTimeStamp()
{
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S ", timeinfo);
    return std::string(buffer);
}

void Print(std::string &text, Color color, bool newLine = true)
{
    std::cout << getTimeStamp();
    std::cout << colors.at(color);
    std::cout << text;
    if (color != Color::DEFAULT)
        std::cout << "\033[0m";
    if (newLine)
        std::cout << std::endl;
}

void logging::Text(std::string &&text, bool newLine)
{
    Print(text, Color::DEFAULT, newLine);
}

void logging::Info(std::string &&text, bool newLine)
{
    Print(text, Color::BLUE, newLine);
}

void logging::Error(std::string &&text, bool newLine)
{
    Print(text, Color::RED, newLine);
}

void logging::Success(std::string &&text, bool newLine)
{
    Print(text, Color::GREEN, newLine);
}

void logging::Warning(std::string &&text, bool newLine)
{
    Print(text, Color::YELLOW, newLine);
}