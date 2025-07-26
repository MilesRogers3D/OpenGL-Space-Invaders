#pragma once

#include "Platform/Window/Window.h"

#include <memory>

namespace Engine {

class Application 
{
public:
  explicit Application(
    const Platform::WindowParams& windowParams);
  ~Application() = default;

private:
  std::shared_ptr<Platform::Window> m_window;
};

} // Engine
