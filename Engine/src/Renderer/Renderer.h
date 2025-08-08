#pragma once

#include "defs.h"
#include "Scene/ECS/World.h"
#include "Renderer/Types/Color.h"
#include "Scene/ECS/Components/Components.h"

namespace Engine {

class ENG_API Renderer
{
public:
  static void clearScreen(const Color& color);
  static void drawSprite(const Entity& entity);
  static void drawLines(const Components::LineRenderer& lineRenderer);

  static void createLineRendererDrawLists(
    Components::LineRenderer& lineRenderer);
};

} // Engine
