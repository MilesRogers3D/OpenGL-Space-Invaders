#pragma once

namespace Engine {

enum EEventType
{
  Mouse, Keyboard
};

enum EKeyCode
{
  Space, Enter, LeftShift, RightShift, Escape,
  A, B, C, D, E, F, G, H, I, J, K, L, M,
  N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
  UpArrow, DownArrow, RightArrow, LeftArrow,
  Num0, Num1, Num2, Num3, Num4, Num5, Num6,
  Num7, Num8, Num9, Minus, Plus, Backspace,
  Delete, Tilde, LCtrl, RCtrl, Comma, Period,
  Question, LAlt, RAlt, Slash, Backslash, Function,
  F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12
};

enum EMouseEvent {
  LeftClick, RightClick, MiddleClick
};

struct InputEvent
{
  EEventType type;
  EKeyCode keyCode;
  EMouseEvent mouseEvent;
};

}