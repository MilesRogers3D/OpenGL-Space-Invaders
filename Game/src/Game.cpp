#include "Game.h"

#include "Core/Logger/Logger.h"
#include "Renderer/Renderer.h"

#include <iostream>

Game::Game(const Engine::Platform::WindowParams& windowParams)
  : Application(windowParams),
    m_clearColor(Engine::ColorUtils::fromPreset(
      Engine::EColor::MediumVermilion))
{
}

void Game::start()
{
  std::cout << "Game start\n";

  m_testSprite = m_world.createEntity();

  Engine::IO::OBJParser objParser;
  objParser.loadModel("res/VectorSprites/vspr_alien_01.obj");

  const auto& model = objParser.getModel();

  m_world.addComponent(m_testSprite, Engine::Components::Name("TestSprite"));
  m_world.addComponent(m_testSprite, Engine::Components::Transform(0.0F, 0.0F));
  m_world.addComponent(m_testSprite, Engine::Components::LineRenderer(model));

  std::cout << "Loaded model vertices: " << model->points.size() << "\n"
            << "Loaded model indices: "  << model->indices.size() << "\n";
}

void Game::update()
{
  Engine::Renderer::clearScreen(m_clearColor);
  Engine::Renderer::drawLines(m_world.getComponent<
    Engine::Components::LineRenderer>(m_testSprite));
  Application::update();
}

void Game::onKeyboardInput(const Engine::EKeyCode& keyCode)
{
  if (keyCode == Engine::UpArrow) {
    std::cout << "Up Arrow\n";
  }
  if (keyCode == Engine::DownArrow) {
    std::cout << "Down Arrow\n";
  }
  if (keyCode == Engine::LeftArrow) {
    std::cout << "Left Arrow\n";
  }
  if (keyCode == Engine::RightArrow) {
    std::cout << "Right Arrow\n";
  }
}
