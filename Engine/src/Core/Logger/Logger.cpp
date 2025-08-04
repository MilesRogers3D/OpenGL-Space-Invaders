#include "Logger.h"

using namespace Engine;

void Logger::initialize()
{
  spdlog::set_pattern(
    "[%H:%M:%S] %v");
  logInfo("Logger initialized");
}