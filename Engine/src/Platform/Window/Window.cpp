#include "Window.h"
#include "Core/Logger/Logger.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <utility>

using namespace Engine::Platform;

Window::Window(WindowParams params)
  : m_windowParams(std::move(params)),
    m_window(nullptr)
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

  p_setupGLFWCallbacks();
  setViewport(0, 0, m_windowParams.width, m_windowParams.height);

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
    static_cast<int>(m_windowParams.width),
    static_cast<int>(m_windowParams.height),
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
      reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    Logger::logError("Failed to initialize GLAD");
    return false;
  }

  return true;
}

void Window::terminate()
{
  glfwTerminate();
}

void Window::clearSurface()
{
  glClearColor(0.2F, 0.3F, 0.3F, 1.0F);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Window::pollInput()
{
  glfwPollEvents();
}

void Window::swapBuffers() const
{
  glfwSwapBuffers(m_window);
}

void Window::c_onFramebufferSizeChanged(GLFWwindow* window,
                                        int width,
                                        int height)
{
  setViewport(0, 0, width, height);
}

void Window::setViewport(
  uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
  glViewport(static_cast<GLint>(x), static_cast<GLint>(y),
             static_cast<GLint>(w), static_cast<GLint>(h));
}

void Window::p_setupGLFWCallbacks()
{
  glfwSetFramebufferSizeCallback(m_window, c_onFramebufferSizeChanged);
}

bool Window::shouldClose()
{
  return glfwWindowShouldClose(m_window);
}
