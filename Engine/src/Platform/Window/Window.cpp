#include "Window.h"

using namespace Engine::Platform;

Window::Window(const WindowParams& params)
  : m_windowParams(params) {}

bool Window::create()
{
  p_createWindow();
}

void Window::p_createWindow()
{
  
}