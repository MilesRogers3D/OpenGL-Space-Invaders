#include "Logger.h"

using namespace Engine;

void Logger::initialize()
{
  spdlog::set_pattern(
    "[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
  logInfo("Logger initialized");
}