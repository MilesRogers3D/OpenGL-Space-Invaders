#include "Renderer.h"

using namespace Engine;

#include <glad/glad.h>

void Renderer::drawSprite(const Entity& entity)
{

}

void Renderer::clearScreen(const Color& color)
{
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}