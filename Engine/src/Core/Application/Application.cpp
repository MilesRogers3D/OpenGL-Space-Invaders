#include "Application.h"
#include "Core/Logger/Logger.h"

using namespace Engine;

Application::Application(const Platform::WindowParams& windowParams)
{
  Logger::initialize();

  m_window = std::make_shared<Platform::Window>(windowParams);
  m_window->create();
}