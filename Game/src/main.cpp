#include "Game.h"

#include <Engine.h>

int main()
{
  Engine::Platform::WindowParams windowParams = {};
  windowParams.title = "OpenGL Space Invaders";
  Game game(windowParams);
}
