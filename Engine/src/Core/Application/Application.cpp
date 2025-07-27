#include "Application.h"
#include "Core/Logger/Logger.h"

using namespace Engine;

Application::Application()
  : m_window(nullptr) {}

bool Application::createWindow(const Platform::WindowParams& windowParams)
{
  m_window = std::make_shared<Platform::Window>(windowParams);
  return m_window->create();
}

void Application::p_initializeSystems()
{
  Logger::initialize();
}

void Application::start()
{
  p_initializeSystems();
  p_startUpdateLoop();
}

void Application::p_startUpdateLoop()
{
  while (!m_window->shouldClose()) {
    m_window->update();
  }

  m_window->terminate();
}
