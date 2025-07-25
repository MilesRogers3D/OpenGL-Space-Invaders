#pragma once

#include "Scene/ECS/IComponentArray.h"

#include <vector>
#include <cassert>

namespace Engine {

template<typename T>
class SparseSet : public IComponentArray
{
public:
  void onDestroyed(Entity entity) override;

  void insert(Entity entity, T component);
  void remove(Entity entity);

  [[nodiscard]]
  bool contains(Entity entity) const;

  T& get(Entity entity);
  const T& get(Entity entity) const;

  T* tryGet(Entity entity);

  auto begin() { return m_components.begin(); }
  auto begin() const { return m_components.begin(); }
  auto end() { return m_components.end(); };
  auto end() const { return m_components.end(); }

  [[nodiscard]]
  const std::vector<Entity>& entities() const { return m_dense; }

  [[nodiscard]]
  size_t size() const { return m_dense.size(); }

  void clear();

private:
  std::vector<uint32_t> m_sparse;
  std::vector<Entity> m_dense;
  std::vector<T> m_components;
};

template<typename T>
void SparseSet<T>::onDestroyed(const Entity entity)
{
  remove(entity);
}

template<typename T>
void SparseSet<T>::insert(const Entity entity, T component)
{
  // TODO: Find a better resizing method (arena allocator etc)
  if (entity >= m_sparse.size()) {
    m_sparse.resize(entity + 1, NULL_ENTITY);
  }

  // If the entity already has this component,
  //  update it
  if (contains(entity)) {
    m_components[m_sparse[entity]] = std::move(component);
    return;
  }

  // Add the component to the entity
  const uint32_t denseIndex = m_dense.size();
  m_sparse[entity] = denseIndex;
  m_dense.emplace_back(entity);
  m_components.push_back(std::move(component));
}

template<typename T>
void SparseSet<T>::remove(const Entity entity)
{
  if (!contains(entity)) {
    return;
  }

  const uint32_t indexToRemove = m_sparse[entity];

  // Move the last element to the removed position
  if (const uint32_t lastIndex = m_dense.size() - 1;
      indexToRemove != lastIndex) {
    const Entity lastEntity = m_dense[lastIndex];

    // Update the sparse array for moved entity
    m_sparse[lastEntity] = indexToRemove;

    // Move data
    m_dense[indexToRemove] = lastEntity;
    m_components[indexToRemove] = std::move(m_components[lastIndex]);
  }

  // Remove last element
  m_dense.pop_back();
  m_components.pop_back();
  m_sparse[entity] = NULL_ENTITY;
}

template<typename T>
bool SparseSet<T>::contains(const Entity entity) const
{
  return entity < m_sparse.size() &&
         m_sparse[entity] != NULL_ENTITY &&
         m_sparse[entity] < m_dense.size() &&
         m_dense[m_sparse[entity]] == entity;
}

template<typename T>
T& SparseSet<T>::get(const Entity entity)
{
  assert(contains(entity));
  return m_components[m_sparse[entity]];
}

template<typename T>
const T& SparseSet<T>::get(const Entity entity) const
{
  assert(contains(entity));
  return m_components[m_sparse[entity]];
}

template<typename T>
T* SparseSet<T>::tryGet(const Entity entity)
{
  return contains(entity) ? &m_components[m_sparse[entity]] : nullptr;
}

template<typename T>
void SparseSet<T>::clear()
{
  m_sparse.clear();
  m_dense.clear();
  m_components.clear();
}

}