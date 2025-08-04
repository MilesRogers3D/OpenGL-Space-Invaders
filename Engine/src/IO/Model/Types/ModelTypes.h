#pragma once

#include "Core/Math/MathTypes.h"

#include <vector>

namespace Engine::IO {

struct ENG_API Model
{
  std::vector<Vector3> points;
  std::vector<Vector3> normals;
  std::vector<Vector2> texCoords;
  std::vector<uint32_t> indices;
};

}