#include <iostream>

#include <Engine.h>

struct Transform
{
  float x;
  float y;
  explicit Transform(const float x = 0, const float y = 0)
    : x(x), y(y) {}
};

int main() {
  Engine::World world;

  const Engine::Entity player = world.createEntity();
  world.addComponent(player, Transform(10, 10));

  std::cout << "Player has Transform: " <<
    world.hasComponent<Transform>(player) << "\n";

  const auto playerTransform = world.getComponent<Transform>(player);
  std::cout << "Player Transform: [" << playerTransform.x <<
    ", " << playerTransform.y << "]\n";

  world.removeComponent<Transform>(player);

  std::cout << "Player has Transform: " <<
    world.hasComponent<Transform>(player) << "\n";
}
