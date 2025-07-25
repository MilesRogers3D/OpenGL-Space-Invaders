#pragma once

#include <cstdint>
#include <string>

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
  ~Window() = default;

  bool create();

private:
  void p_createWindow();

private:
  WindowParams m_windowParams;
};

}
