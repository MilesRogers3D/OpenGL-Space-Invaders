#pragma once

namespace Engine {

struct ENG_API Vector2
{
  float x;
  float y;

  explicit Vector2(const float x = 0,
                   const float y = 0)
    : x(x), y(y)
  {
  }

  bool operator==(const Vector2& other) const
  {
    return x == other.x && y == other.y;
  }
};

struct ENG_API Vector3
{
  float x;
  float y;
  float z;

  explicit Vector3(const float x = 0,
                   const float y = 0,
                   const float z = 0)
    : x(x), y(y), z(z)
  {
  }

  bool operator==(const Vector3& other) const
  {
    return x == other.x &&
           y == other.y &&
           z == other.z;
  }
};

struct ENG_API Vector4
{
  float x;
  float y;
  float z;
  float w;

  explicit Vector4(const float x = 0,
                   const float y = 0,
                   const float z = 0,
                   const float w = 0)
    : x(x), y(y), z(z), w(w)
  {
  }

  bool operator==(const Vector4& other) const
  {
    return x == other.x &&
           y == other.y &&
           z == other.z &&
           w == other.w;
  }
};

}