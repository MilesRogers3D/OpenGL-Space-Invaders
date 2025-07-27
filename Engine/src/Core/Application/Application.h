#pragma once

#include "defs.h"
#include "Platform/Window/Window.h"

#include <memory>

namespace Engine {

class ENG_API Application
{
public:
  Application();
  ~Application() = default;

  bool createWindow(const Platform::WindowParams& windowParams);

  void start();

private:
  void p_initializeSystems();
  void p_startUpdateLoop();

private:
  std::shared_ptr<Platform::Window> m_window;
};

} // Engine
