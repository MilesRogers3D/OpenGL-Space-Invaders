#pragma once

#include <Engine.h>

class Game final : public Engine::Application
{
public:
  explicit Game(const Engine::Platform::WindowParams& windowParams);
  ~Game() override = default;

private:
  void start() override;
  void update(double deltaTime) override;
  void onInput(const Engine::InputEvent &event) override;
};
