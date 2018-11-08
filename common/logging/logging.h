
#ifndef COMMON_LOGGING_LOGGING_H
#define COMMON_LOGGING_LOGGING_H

#include <iostream>
#include <string>

namespace Logging
{
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

void Info(std::string &&text, bool newLine = true)
{
    Print(text, Color::BLUE, newLine);
}

void Error(std::string &&text, bool newLine = true)
{
    Print(text, Color::RED, newLine);
}

void Success(std::string &&text, bool newLine = true)
{
    Print(text, Color::GREEN, newLine);
}

void Warning(std::string &&text, bool newLine = true)
{
    Print(text, Color::YELLOW, newLine);
}

} // namespace Logging

#endif