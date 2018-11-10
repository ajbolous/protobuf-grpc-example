
#include "logging.h"

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

void Print(std::string &text, Color color, bool newLine = true)
{
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