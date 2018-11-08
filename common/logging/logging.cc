
#include "logging.h"

enum Color
{
    DEFAULT,
    RED,
    BLUE,
    GREEN,
    YELLOW
};

void Print(std::string &text, Color color, bool newLine = true)
{
    switch (color)
    {
    case Color::RED:
        std::cout << "\033[1;31m" << text << "\033[0m";
        break;
    case Color::BLUE:
        std::cout << "\033[1;34m" << text << "\033[0m";
        break;
    case Color::YELLOW:
        std::cout << "\033[1;33m" << text << "\033[0m";
        break;
    case Color::GREEN:
        std::cout << "\033[1;32m" << text << "\033[0m";
        break;
    default:
        std ::cout << text;
    }
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