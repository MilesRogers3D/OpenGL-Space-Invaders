#include "InputSystem.h"

#include "Core/Logger/Logger.h"
#include "Core/Application/Application.h"

#include <GLFW/glfw3.h>

using namespace Engine;

#define KEY_PRESS_EVENT(gltfKeyCode, engineKeyCode) if (key == gltfKeyCode && \
  action == GLFW_PRESS) { static_cast<InputSystem*>(glfwGetWindowUserPointer(window))-> \
    m_application->onKeyboardInput(engineKeyCode); }

InputSystem::InputSystem(const std::shared_ptr<Platform::Window>& window,
                         Application* application)
  : m_window(window),
    m_application(application)
{
}

void InputSystem::initialize()
{
  auto* glfwWindow = m_window->getGLFWWindowHandle();
  glfwSetKeyCallback(glfwWindow, c_keyEvent);
  glfwSetWindowUserPointer(glfwWindow, this);

  Logger::logInfo("InputSystem initialized");
}

void InputSystem::c_keyEvent(GLFWwindow* window,
                             const int key,
                             const int scancode,
                             const int action,
                             const int mods)
{
  // Special
  KEY_PRESS_EVENT(GLFW_KEY_SPACE,       EKeyCode::Space);
  KEY_PRESS_EVENT(GLFW_KEY_ENTER,       EKeyCode::Enter);
  KEY_PRESS_EVENT(GLFW_KEY_LEFT_SHIFT,  EKeyCode::LeftShift);
  KEY_PRESS_EVENT(GLFW_KEY_RIGHT_SHIFT, EKeyCode::RightShift);
  KEY_PRESS_EVENT(GLFW_KEY_ESCAPE,      EKeyCode::Escape);

  // Alphabet
  KEY_PRESS_EVENT(GLFW_KEY_A, EKeyCode::A);
  KEY_PRESS_EVENT(GLFW_KEY_B, EKeyCode::B);
  KEY_PRESS_EVENT(GLFW_KEY_C, EKeyCode::C);
  KEY_PRESS_EVENT(GLFW_KEY_D, EKeyCode::D);
  KEY_PRESS_EVENT(GLFW_KEY_E, EKeyCode::E);
  KEY_PRESS_EVENT(GLFW_KEY_F, EKeyCode::F);
  KEY_PRESS_EVENT(GLFW_KEY_G, EKeyCode::G);
  KEY_PRESS_EVENT(GLFW_KEY_H, EKeyCode::H);
  KEY_PRESS_EVENT(GLFW_KEY_I, EKeyCode::I);
  KEY_PRESS_EVENT(GLFW_KEY_J, EKeyCode::J);
  KEY_PRESS_EVENT(GLFW_KEY_K, EKeyCode::K);
  KEY_PRESS_EVENT(GLFW_KEY_L, EKeyCode::L);
  KEY_PRESS_EVENT(GLFW_KEY_M, EKeyCode::M);
  KEY_PRESS_EVENT(GLFW_KEY_N, EKeyCode::N);
  KEY_PRESS_EVENT(GLFW_KEY_O, EKeyCode::O);
  KEY_PRESS_EVENT(GLFW_KEY_P, EKeyCode::P);
  KEY_PRESS_EVENT(GLFW_KEY_Q, EKeyCode::Q);
  KEY_PRESS_EVENT(GLFW_KEY_R, EKeyCode::R);
  KEY_PRESS_EVENT(GLFW_KEY_S, EKeyCode::S);
  KEY_PRESS_EVENT(GLFW_KEY_T, EKeyCode::T);
  KEY_PRESS_EVENT(GLFW_KEY_U, EKeyCode::U);
  KEY_PRESS_EVENT(GLFW_KEY_V, EKeyCode::V);
  KEY_PRESS_EVENT(GLFW_KEY_W, EKeyCode::W);
  KEY_PRESS_EVENT(GLFW_KEY_X, EKeyCode::X);
  KEY_PRESS_EVENT(GLFW_KEY_Y, EKeyCode::Y);
  KEY_PRESS_EVENT(GLFW_KEY_Z, EKeyCode::Z);

  // Arrows
  KEY_PRESS_EVENT(GLFW_KEY_UP,    EKeyCode::UpArrow);
  KEY_PRESS_EVENT(GLFW_KEY_DOWN,  EKeyCode::DownArrow);
  KEY_PRESS_EVENT(GLFW_KEY_LEFT,  EKeyCode::LeftArrow);
  KEY_PRESS_EVENT(GLFW_KEY_RIGHT, EKeyCode::RightArrow);

  // Num
  KEY_PRESS_EVENT(GLFW_KEY_0,     EKeyCode::Num0);
  KEY_PRESS_EVENT(GLFW_KEY_1,     EKeyCode::Num1);
  KEY_PRESS_EVENT(GLFW_KEY_2,     EKeyCode::Num2);
  KEY_PRESS_EVENT(GLFW_KEY_3,     EKeyCode::Num3);
  KEY_PRESS_EVENT(GLFW_KEY_4,     EKeyCode::Num4);
  KEY_PRESS_EVENT(GLFW_KEY_5,     EKeyCode::Num5);
  KEY_PRESS_EVENT(GLFW_KEY_6,     EKeyCode::Num6);
  KEY_PRESS_EVENT(GLFW_KEY_7,     EKeyCode::Num7);
  KEY_PRESS_EVENT(GLFW_KEY_8,     EKeyCode::Num8);
  KEY_PRESS_EVENT(GLFW_KEY_9,     EKeyCode::Num9);
  KEY_PRESS_EVENT(GLFW_KEY_MINUS, EKeyCode::Minus);
  KEY_PRESS_EVENT(GLFW_KEY_EQUAL, EKeyCode::Equal);

  // Special/modifiers
  KEY_PRESS_EVENT(GLFW_KEY_BACKSPACE, EKeyCode::Backspace);
  KEY_PRESS_EVENT(GLFW_KEY_DELETE, EKeyCode::Delete);
  KEY_PRESS_EVENT(GLFW_KEY_GRAVE_ACCENT, EKeyCode::Tilde);
  KEY_PRESS_EVENT(GLFW_KEY_LEFT_CONTROL, EKeyCode::LCtrl);
  KEY_PRESS_EVENT(GLFW_KEY_RIGHT_CONTROL, EKeyCode::RCtrl);
  KEY_PRESS_EVENT(GLFW_KEY_COMMA, EKeyCode::Comma);
  KEY_PRESS_EVENT(GLFW_KEY_PERIOD, EKeyCode::Period);

  // TODO: Implement rest of modifiers
}