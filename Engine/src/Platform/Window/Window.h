#pragma once

#include <cstdint>
#include <string>

class GLFWwindow;

namespace Engine::Platform {

struct WindowParams
{
  uint32_t width    = 1280;
  uint32_t height   = 720;
  bool maximized    = false;
  bool vSync        = false;
  std::string title = "Engine Window";
};

class Window 
{
public:
  explicit Window(const WindowParams& params);
  ~Window();

  bool create();

private:
  static void p_initGLFW();
  bool p_initWindow();
  static bool p_initGLAD();

private:
  WindowParams m_windowParams;
  GLFWwindow* m_window;
};

}
