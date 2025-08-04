#include "Game.h"

#include "Core/Logger/Logger.h"
#include "Renderer/Renderer.h"

#include <iostream>

Game::Game(const Engine::Platform::WindowParams& windowParams)
  : Application(windowParams),
    m_clearColor(Engine::ColorUtils::fromPreset(
      Engine::EColor::MediumVermilion)) {}

void Game::start()
{
  std::cout << "Game start\n";

  Engine::IO::OBJParser objParser;
  objParser.loadModel("res/VectorSprites/vspr_alien_01.obj");

  const auto& model = objParser.getModel();

  std::cout << "Loaded model vertices: " << model->points.size() << "\n"
            << "Loaded model indices: "  << model->indices.size() << "\n";
}

void Game::update()
{
  Engine::Renderer::clearScreen(m_clearColor);
  Application::update();
}

void Game::onKeyboardInput(const Engine::EKeyCode& keyCode)
{
  if (keyCode == Engine::EKeyCode::Escape) {
    // TODO: Quit game
  }
}
