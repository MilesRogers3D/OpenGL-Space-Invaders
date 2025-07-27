#include "Logger.h"

using namespace Engine;

void Logger::initialize()
{
  spdlog::set_pattern(
    "[%H:%M:%S %z] [ENGINE] %v");
  logInfo("Logger initialized");
}