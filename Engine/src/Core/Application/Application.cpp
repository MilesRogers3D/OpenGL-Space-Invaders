#include "Application.h"
#include "Core/Logger/Logger.h"

#include <chrono>

using namespace Engine;

void Application::p_initializeSystems()
{
  // Init delta time timer
  m_lastTime = p_getTime();

  // Init logger
  Logger::initialize();
}

void Application::p_startUpdateLoop()
{
  while (!m_window->shouldClose()) {
    // Update game world w/ delta time
    const double time = p_getTime();
    update(time - m_lastTime);
    m_lastTime = time;

    // Update window
    m_window->update();
  }

  m_window->terminate();
}

Application::Application(const Platform::WindowParams& windowParams)
{
  m_window = std::make_shared<Platform::Window>(windowParams);
  if (!m_window->create()) {
    Logger::logError("Failed to initialize window");
  }

  p_initializeSystems();
  p_startUpdateLoop();
}

double Application::p_getTime()
{
  return static_cast<double>(std::chrono::duration_cast<
    std::chrono::milliseconds>(
    std::chrono::system_clock::now().time_since_epoch()
  ).count());
}

void Application::update(double deltaTime)
{
  Logger::logInfo("Delta time: {}", deltaTime);
}

void Application::start() {
  Logger::logInfo("Started game");
}

void Application::onInput(const InputEvent& event) {}
