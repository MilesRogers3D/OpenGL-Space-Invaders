#pragma once

#include <string>

namespace Engine::Components {

struct Name
{
  std::string name;

  explicit Name(std::string name = "")
    : name(std::move(name)) {}

  bool operator==(const Name& other) const
  {
    return name == other.name;
  }
};

struct Transform
{
  float x;
  float y;

  explicit Transform(const float x = 0, const float y = 0)
    : x(x), y(y) {}

  bool operator==(const Transform& other) const
  {
    return x == other.x && y == other.y;
  }
};

struct BoxCollider
{
  float width;
  float height;

  explicit BoxCollider(const float width = 0, const float height = 0)
    : width(width), height(height) {}

  bool operator==(const BoxCollider& other) const
  {
    return width == other.width && height == other.height;
  }
};

}