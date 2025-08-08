#pragma once

#include "defs.h"
#include "InputCodes.h"
#include "Platform/Window/Window.h"

namespace Engine {

class Application;

class ENG_API InputSystem
{
public:
  explicit InputSystem(const std::shared_ptr<Platform::Window>& window,
                       Application* application);
  void initialize();

private:
  static void c_keyEvent(GLFWwindow* window,
                         int key,
                         int scancode,
                         int action,
                         int mods);

private:
  std::shared_ptr<Platform::Window> m_window;
  Application* m_application;
};

}
