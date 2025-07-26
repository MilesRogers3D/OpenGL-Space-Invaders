#pragma once

#include <spdlog/spdlog.h>

#include <string>

namespace Engine {

class Logger 
{
public:
  static void initialize();

  template<typename... Args>
  static void logInfo(
    const std::string& msg,
    Args... args);

  template<typename... Args>
  static void logWarn(
    const std::string& msg,
    Args... args);

  template<typename... Args>
  static void logError(
    const std::string& msg,
    Args... args);
};

template<typename... Args>
void Logger::logInfo(const std::string& msg, Args... args)
{
  spdlog::info(msg, std::forward<Args>(args)...);
}

template<typename ... Args>
void Logger::logWarn(const std::string& msg, Args... args)
{
  spdlog::warn(msg, std::forward<Args>(args)...);
}

template<typename ... Args>
void Logger::logError(const std::string& msg, Args... args)
{
  spdlog::error(msg, std::forward<Args>(args)...);
}

} // Engine
