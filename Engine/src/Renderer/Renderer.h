#pragma once

#include "defs.h"
#include "Scene/ECS/World.h"
#include "Renderer/Types/Color.h"

namespace Engine {

class ENG_API Renderer
{
public:
  static void clearScreen(const Color& color);
  static void drawSprite(const Entity& entity);
};

} // Engine
