#pragma once

#include "defs.h"
#include "Scene/ECS/World.h"

namespace Engine {

class ENG_API Renderer
{
public:
  static void drawSprite(const Entity& entity);
};

} // Engine
