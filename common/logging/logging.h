
#ifndef COMMON_LOGGING_LOGGING_H
#define COMMON_LOGGING_LOGGING_H

#include <iostream>
#include <string>

namespace logging
{

void Text(std::string &&text, bool newLine = true);
void Info(std::string &&text, bool newLine = true);
void Error(std::string &&text, bool newLine = true);
void Success(std::string &&text, bool newLine = true);
void Warning(std::string &&text, bool newLine = true);
} // namespace logging

#endif