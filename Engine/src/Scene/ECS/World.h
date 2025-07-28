#pragma once

#include "defs.h"
#include "Scene/ECS/Types/SparseSet.h"

#include <typeindex>
#include <memory>
#include <unordered_map>
#include <functional>

namespace Engine {

class ENG_API World
{
public:
  Entity createEntity();
  void destroyEntity(Entity entity);

  template<typename T>
  void addComponent(Entity entity, T component);

  template<typename T>
  void removeComponent(Entity entity);

  template<typename T>
  T& getComponent(Entity entity);

  template<typename T>
  [[nodiscard]]
  bool hasComponent(Entity entity) const;

  template<typename T>
  T* tryGetComponent(Entity entity);

  template<typename T>
  const std::vector<Entity>& findAllOfType();

  void clear();

private:

  template<typename T>
  SparseSet<T>* p_getComponentArray();

  Entity m_nextEntityID = 1;
  std::unordered_map<
    std::type_index, std::unique_ptr<IComponentArray>>
  m_componentArrays;
};

template<typename T>
SparseSet<T>* World::p_getComponentArray()
{
  const auto typeIndex = std::type_index(typeid(T));
  const auto it = m_componentArrays.find(typeIndex);

  if (it == m_componentArrays.end()) {
    auto sparseSet = std::make_unique<SparseSet<T>>();
    auto* ptr = sparseSet.get();

    m_componentArrays[typeIndex] = std::move(sparseSet);

    return ptr;
  }

  return static_cast<SparseSet<T>*>(it->second.get());
}

template<typename T>
void World::addComponent(Entity entity, T component)
{
  p_getComponentArray<T>()->insert(entity, std::move(component));
}

template<typename T>
void World::removeComponent(Entity entity)
{
  p_getComponentArray<T>()->remove(entity);
}

template<typename T>
T& World::getComponent(Entity entity)
{
  return p_getComponentArray<T>()->get(entity);
}

template<typename T>
bool World::hasComponent(Entity entity) const
{
  auto* componentArray = const_cast<World*>(this)->
    p_getComponentArray<T>();
  return componentArray->contains(entity);
}

template<typename T>
T* World::tryGetComponent(Entity entity)
{
  return p_getComponentArray<T>()->tryGet(entity);
}

template<typename T>
const std::vector<Entity>& World::findAllOfType()
{
  return p_getComponentArray<T>()->entities();
}

}
