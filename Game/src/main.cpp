#include <iostream>

#include <Engine.h>

int main() {
  Engine::Platform::WindowParams windowParams = {};
  windowParams.title = "OpenGL Space Invaders";

  Engine::Application app(windowParams);

  while (true) {}
}
