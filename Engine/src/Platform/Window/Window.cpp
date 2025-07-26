#include "Window.h"
#include "Core/Logger/Logger.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace Engine::Platform;

Window::Window(const WindowParams& params)
  : m_windowParams(params) {}

Window::~Window()
{

}

bool Window::create()
{
  p_initGLFW();

  if (!p_initWindow()) {
    return false;
  }

  if (!p_initGLAD()) {
    return false;
  }

  return true;
}

void Window::p_initGLFW()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

bool Window::p_initWindow()
{
  m_window = glfwCreateWindow(
    m_windowParams.width,
    m_windowParams.height,
    m_windowParams.title.c_str(),
    nullptr, nullptr);

  if (m_window == nullptr) {
    Logger::logError("Failed to create GLFW window");
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(m_window);
  return true;
}

bool Window::p_initGLAD()
{
  if (!gladLoadGLLoader(
      reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
  {
    Logger::logError("Failed to initialize GLAD");
    return false;
  }

  return true;
}