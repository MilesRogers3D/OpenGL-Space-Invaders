#pragma once

#include "defs.h"

#include <cstdint>
#include <string>

class GLFWwindow;

namespace Engine::Platform {

struct WindowParams
{
  uint32_t width = 1280;
  uint32_t height = 720;
  bool maximized = false;
  bool vSync = false;
  std::string title = "Engine Window";
};

class ENG_API Window
{
public:
  explicit Window(WindowParams params);
  ~Window() = default;

  bool create();
  void terminate();

  static void clearSurface();
  static void pollInput();
  void swapBuffers() const;

  [[nodiscard]]
  bool shouldClose();

  static void setViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h);

  GLFWwindow* getGLFWWindowHandle() const;

protected:
  static void c_onFramebufferSizeChanged(GLFWwindow* window,
                                         int width,
                                         int height);

private:
  static void p_initGLFW();
  bool p_initWindow();
  static bool p_initGLAD();

  void p_setupGLFWCallbacks();

private:
  WindowParams m_windowParams;
  GLFWwindow* m_window;
};

}
