#include "Game.h"

#include <iostream>

Game::Game(const Engine::Platform::WindowParams& windowParams)
  : Application(windowParams) {}

void Game::start()
{
  std::cout << "Game start\n";
}

void Game::update(double deltaTime)
{
  std::cout << "Update | Delta Time: "
            << deltaTime << "\n";
}

void Game::onInput(const Engine::InputEvent& event) {}
