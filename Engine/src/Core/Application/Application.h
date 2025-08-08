#pragma once

#include "defs.h"
#include "Platform/Window/Window.h"
#include "Platform/Input/InputCodes.h"
#include "Platform/Input/InputSystem.h"

#include <memory>

namespace Engine {

class ENG_API Application
{
  friend class InputSystem;
public:
  explicit Application(const Platform::WindowParams& windowParams);
  virtual ~Application() = default;

public:
  [[nodiscard]]
  bool shouldClose() const;

protected:
  virtual void start();
  virtual void update();

  virtual void onKeyboardInput(const EKeyCode& keyCode);

private:
  void p_initializeSystems();

private:
  std::shared_ptr<Platform::Window> m_window;
  std::shared_ptr<InputSystem> m_inputSystem;
};

} // Engine
