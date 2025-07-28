#pragma once

#include "defs.h"
#include "Platform/Window/Window.h"
#include "Platform/Input/Input.h"

#include <memory>

namespace Engine {

class ENG_API Application
{
public:
  explicit Application(const Platform::WindowParams& windowParams);
  virtual ~Application() = default;

protected:
  virtual void start();
  virtual void update(double deltaTime);
  virtual void onInput(const InputEvent& event);

private:
  void p_initializeSystems();
  void p_startUpdateLoop();

  [[nodiscard]]
  static double p_getTime();

private:
  std::shared_ptr<Platform::Window> m_window;
  double m_lastTime = 0;
};

} // Engine
