#include "Application.h"
#include "Core/Logger/Logger.h"

#include <chrono>

using namespace Engine;

Application::Application(const Platform::WindowParams& windowParams)
{
  m_window = std::make_shared<Platform::Window>(windowParams);
  if (!m_window->create()) {
    Logger::logError("Failed to initialize window");
  }

  p_initializeSystems();
}

void Application::start() {
  Logger::logInfo("Started game");
}

void Application::update()
{
  Platform::Window::pollInput();
  m_window->swapBuffers();
}

void Application::onKeyboardInput(const EKeyCode& keyCode) {}

bool Application::shouldClose() const
{
  return m_window->shouldClose();
}

void Application::p_initializeSystems()
{
  // Init logger
  Logger::initialize();

  // Init input system
  m_inputSystem = std::make_shared<InputSystem>(m_window, this);
  m_inputSystem->initialize();
}
