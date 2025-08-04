#pragma once

#include <Engine.h>

class Game final : public Engine::Application
{
public:
  explicit Game(const Engine::Platform::WindowParams& windowParams);
  ~Game() override = default;

public:
  void start() override;
  void update() override;
  void onKeyboardInput(const Engine::EKeyCode& keyCode) override;

private:
  Engine::Color m_clearColor;
};
