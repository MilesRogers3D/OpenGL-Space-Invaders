#include <iostream>

#include <Engine.h>

int main() {
  Engine::Application app;

  Engine::Platform::WindowParams windowParams = {};
  windowParams.title = "OpenGL Space Invaders";

  if (!app.createWindow(windowParams)) {
    return -1;
  }

  app.start();
}
