#include "World.h"

using namespace Engine;

Entity World::createEntity()
{
  return m_nextEntityID++;
}

void World::destroyEntity(const Entity entity)
{
  for (auto& [type, componentArray] : m_componentArrays) {
    componentArray->onDestroyed(entity);
  }
}

void World::clear()
{
  m_componentArrays.clear();
  m_nextEntityID = 1;
}