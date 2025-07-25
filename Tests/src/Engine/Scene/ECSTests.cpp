#include "catch2/catch_approx.hpp"

#include <Engine.h>

#include <catch2/catch_test_macros.hpp>

using namespace Engine;

TEST_CASE("SparseSet Basic Operations", "[ECS]")
{
  SparseSet<Components::Transform> sparseSet;

  SECTION("Empty sparse set")
  {
    REQUIRE(sparseSet.size() == 0);
    REQUIRE_FALSE(sparseSet.contains(1));
    REQUIRE_FALSE(sparseSet.contains(100));
    REQUIRE(sparseSet.tryGet(1) == nullptr);
  }

  SECTION("Insert single component")
  {
    Entity entity = 42;
    const auto pos = Components::Transform(10.0F, 20.0F);

    sparseSet.insert(entity, pos);

    REQUIRE(sparseSet.size() == 1);
    REQUIRE(sparseSet.contains(entity));
    REQUIRE(sparseSet.get(entity) == pos);
    REQUIRE(*sparseSet.tryGet(entity) == pos);
    REQUIRE(sparseSet.entities().size() == 1);
    REQUIRE(sparseSet.entities()[0] == entity);
  }

  SECTION("Insert multiple components")
  {
    sparseSet.insert(1,  Components::Transform(1.0F,  1.0F));
    sparseSet.insert(5,  Components::Transform(5.0F,  5.0F));
    sparseSet.insert(10, Components::Transform(10.0F, 10.0F));

    REQUIRE(sparseSet.size() == 3);
    REQUIRE(sparseSet.contains(1));
    REQUIRE(sparseSet.contains(5));
    REQUIRE(sparseSet.contains(10));
    REQUIRE_FALSE(sparseSet.contains(2));
    REQUIRE_FALSE(sparseSet.contains(7));

    REQUIRE(sparseSet.get(1) ==  Components::Transform(1.0F,  1.0F));
    REQUIRE(sparseSet.get(5) ==  Components::Transform(5.0F,  5.0F));
    REQUIRE(sparseSet.get(10) == Components::Transform(10.0F, 10.0F));
  }

  SECTION("Update existing component")
  {
    constexpr Entity entity = 1;
    sparseSet.insert(entity, Components::Transform(1.0F, 1.0F));
    sparseSet.insert(entity, Components::Transform(2.0F, 2.0F)); // Update

    REQUIRE(sparseSet.size() == 1);
    REQUIRE(sparseSet.get(entity) == Components::Transform(2.0F, 2.0F));
  }

  SECTION("Remove component")
  {
    sparseSet.insert(1, Components::Transform(1.0F, 1.0F));
    sparseSet.insert(2, Components::Transform(2.0F, 2.0F));
    sparseSet.insert(3, Components::Transform(3.0F, 3.0F));

    REQUIRE(sparseSet.size() == 3);

    sparseSet.remove(2); // Remove middle element

    REQUIRE(sparseSet.size() == 2);
    REQUIRE(sparseSet.contains(1));
    REQUIRE_FALSE(sparseSet.contains(2));
    REQUIRE(sparseSet.contains(3));
    REQUIRE(sparseSet.tryGet(2) == nullptr);
  }

  SECTION("Remove non-existent component")
  {
    sparseSet.insert(1, Components::Transform(1.0F, 1.0F));
    sparseSet.remove(999); // Non-existent component

    REQUIRE(sparseSet.size() == 1);
    REQUIRE(sparseSet.contains(1));
  }

  SECTION("Large entity IDs")
  {
    constexpr Entity largeEntity = 1000000;
    const auto transform = Components::Transform(100.0F, 200.0F);
    sparseSet.insert(largeEntity, transform);

    REQUIRE(sparseSet.contains(largeEntity));
    REQUIRE(sparseSet.get(largeEntity) == transform);
  }

  SECTION("Clear sparse set")
  {
    sparseSet.insert(1, Components::Transform(1.0F, 1.0F));
    sparseSet.insert(2, Components::Transform(2.0F, 2.0F));

    sparseSet.clear();

    REQUIRE(sparseSet.size() == 0);
    REQUIRE_FALSE(sparseSet.contains(1));
    REQUIRE_FALSE(sparseSet.contains(2));
  }
}

TEST_CASE("SparseSet Iteration", "[ECS]")
{
  SparseSet<Components::Transform> sparseSet;

  SECTION("Iterate over empty set")
  {
    int count = 0;
    for (const auto& c : sparseSet) {
      count++;
    }
    REQUIRE(count == 0);
  }

  SECTION("Iterate over components")
  {
    sparseSet.insert(1, Components::Transform(1.0F, 1.0F));
    sparseSet.insert(3, Components::Transform(3.0F, 3.0F));
    sparseSet.insert(2, Components::Transform(2.0F, 2.0F));

    std::vector<Components::Transform> positions;
    for (const auto& pos : sparseSet) {
      positions.emplace_back(pos);
    }

    REQUIRE(positions.size() == 3);
  }

  SECTION("Iterate with entities")
  {
    sparseSet.insert(10, Components::Transform(10.0F, 10.0F));
    sparseSet.insert(20, Components::Transform(20.0F, 20.0F));

    const auto& entities = sparseSet.entities();
    REQUIRE(entities.size() == 2);

    for (unsigned int entity : entities) {
      const Components::Transform& pos = sparseSet.get(entity);
      REQUIRE(pos.x == static_cast<float>(entity));
      REQUIRE(pos.y == static_cast<float>(entity));
    }
  }
}

TEST_CASE("World Entity Management", "[ECS]")
{
  World world;

  SECTION("Create entities")
  {
    const Entity e1 = world.createEntity();
    const Entity e2 = world.createEntity();
    const Entity e3 = world.createEntity();

    REQUIRE(e1 != e2);
    REQUIRE(e2 != e3);
    REQUIRE(e1 != e3);

    REQUIRE(e1 != NULL_ENTITY);
    REQUIRE(e2 != NULL_ENTITY);
    REQUIRE(e3 != NULL_ENTITY);
  }

  SECTION("Destroy entity removes all components")
  {
    Entity entity = world.createEntity();

    world.addComponent(entity, Components::Name("TestEntity"));
    world.addComponent(entity, Components::Transform(10.0F, 20.0F));

    REQUIRE(world.hasComponent<Components::Name>(entity));
    REQUIRE(world.hasComponent<Components::Transform>(entity));

    world.destroyEntity(entity);

    REQUIRE_FALSE(world.hasComponent<Components::Name>(entity));
    REQUIRE_FALSE(world.hasComponent<Components::Transform>(entity));
  }
}

TEST_CASE("World Component Management", "[ECS]")
{
  World world;
  Entity entity = world.createEntity();

  SECTION("Add and get components")
  {
    Components::Name name("TestEntity");
    Components::Transform transform(1.0F, -2.0F);

    world.addComponent(entity, name);
    world.addComponent(entity, transform);

    REQUIRE(world.hasComponent<Components::Name>(entity));
    REQUIRE(world.hasComponent<Components::Transform>(entity));
    REQUIRE_FALSE(world.hasComponent<Components::BoxCollider>(entity));

    REQUIRE(world.getComponent<Components::Name>(entity) == name);
    REQUIRE(world.getComponent<Components::Transform>(entity) == transform);
  }

  SECTION("Try get component")
  {
    world.addComponent(entity, Components::Transform(1.0F, 2.0F));

    auto* pos = world.tryGetComponent<Components::Transform>(entity);
    auto* vel = world.tryGetComponent<Components::BoxCollider>(entity);

    REQUIRE(pos != nullptr);
    REQUIRE(vel == nullptr);
    REQUIRE(*pos == Components::Transform(1.0F, 2.0F));
  }

  SECTION("Remove component")
  {
    world.addComponent(entity, Components::Name("TestEntity"));
    world.addComponent(entity, Components::Transform(3.0F, 4.0F));

    REQUIRE(world.hasComponent<Components::Name>(entity));
    REQUIRE(world.hasComponent<Components::Transform>(entity));

    world.removeComponent<Components::Name>(entity);

    REQUIRE_FALSE(world.hasComponent<Components::Name>(entity));
    REQUIRE(world.hasComponent<Components::Transform>(entity));
  }

  SECTION("Update component")
  {
    world.addComponent(entity, Components::Transform(1.0F, 1.0F));
    world.addComponent(entity, Components::Transform(2.0F, 2.0F)); // Update

    REQUIRE(world.getComponent<Components::Transform>(entity) ==
      Components::Transform(2.0F, 2.0F));
  }
}

TEST_CASE("World Query System", "[ECS]")
{
  World world;

  SECTION("Get entities with component")
  {
    const Entity e1 = world.createEntity();
    const Entity e2 = world.createEntity();
    const Entity e3 = world.createEntity();

    world.addComponent(e1, Components::Transform(1.0F, 1.0F));
    world.addComponent(e2, Components::Transform(2.0F, 2.0F));
    world.addComponent(e3, Components::Name("TestEntity"));

    const auto& positionEntities = world.findAllOfType<Components::Transform>();
    REQUIRE(positionEntities.size() == 2);

    const auto& velocityEntities = world.findAllOfType<Components::Name>();
    REQUIRE(velocityEntities.size() == 1);
    REQUIRE(velocityEntities[0] == e3);
  }

  SECTION("For-each with single component")
  {
    const Entity e1 = world.createEntity();
    const Entity e2 = world.createEntity();
    const Entity e3 = world.createEntity();

    world.addComponent(e1, Components::Transform(10.0F, 10.0F));
    world.addComponent(e2, Components::Transform(20.0F, 20.0F));
    world.addComponent(e3, Components::Name("TestEntity"));

    std::vector<Entity> visitedEntities;
    std::vector<Components::Transform> visitedTransforms;

    for (const auto& e : world.findAllOfType<Components::Transform>()) {
      visitedEntities.emplace_back(e);
      visitedTransforms.emplace_back(
        world.getComponent<Components::Transform>(e));
    }

    REQUIRE(visitedEntities.size() == 2);
    REQUIRE(visitedTransforms.size() == 2);

    const bool foundE1 = std::find(visitedEntities.begin(),
      visitedEntities.end(), e1) != visitedEntities.end();
    const bool foundE2 = std::find(visitedEntities.begin(),
      visitedEntities.end(), e2) != visitedEntities.end();
    const bool foundE3 = std::find(visitedEntities.begin(),
      visitedEntities.end(), e3) != visitedEntities.end();

    REQUIRE(foundE1);
    REQUIRE(foundE2);
    REQUIRE_FALSE(foundE3);
  }

  SECTION("For-each with multiple components")
  {
    const Entity e1 = world.createEntity();
    const Entity e2 = world.createEntity();
    const Entity e3 = world.createEntity();

    // e1 has both transform and name
    world.addComponent(e1, Components::Transform(1.0F, 1.0F));
    world.addComponent(e1, Components::Name("TestEntity1"));

    // e2 has only transform
    world.addComponent(e2, Components::Transform(2.0F, 2.0F));

    // e3 has both transform and name
    world.addComponent(e3, Components::Transform(3.0F, 3.0F));
    world.addComponent(e3, Components::Name("TestEntity2"));

    std::vector<Entity> visitedEntities;

    for (auto& e : world.findAllOfType<Components::Transform>()) {
      if (world.hasComponent<Components::Name>(e)) {
        visitedEntities.emplace_back(e);

        // Modify components to test reference access
        auto& transform = world.getComponent<Components::Transform>(e);
        transform.x += 2.0F;
      }
    }

    REQUIRE(visitedEntities.size() == 2);

    const bool foundE1 = std::find(visitedEntities.begin(),
      visitedEntities.end(), e1) != visitedEntities.end();
    const bool foundE2 = std::find(visitedEntities.begin(),
      visitedEntities.end(), e2) != visitedEntities.end();
    const bool foundE3 = std::find(visitedEntities.begin(),
      visitedEntities.end(), e3) != visitedEntities.end();

    REQUIRE(foundE1);
    REQUIRE_FALSE(foundE2);
    REQUIRE(foundE3);

    REQUIRE(world.getComponent<Components::Transform>(e1).x
      == Catch::Approx(3.0F));
    REQUIRE(world.getComponent<Components::Transform>(e2).x
      == Catch::Approx(2.0F)); // Unchanged
    REQUIRE(world.getComponent<Components::Transform>(e3).x
      == Catch::Approx(5.0F));
  }

  SECTION ("For-each with no matching entities")
  {
    const Entity entity = world.createEntity();
    world.addComponent(entity, Components::Transform(1.0F, 1.0F));

    int callCount = 0;
    for (const auto& e : world.findAllOfType<Components::Name>()) {
      callCount++;
    }

    REQUIRE(callCount == 0);
  }
}

TEST_CASE("Edge Cases and Error Handling", "[ECS]")
{
  World world;

  SECTION("Large numbers of entities")
  {
    std::vector<Entity> entities;
    constexpr size_t ENTITY_COUNT = 1000;

    // Create N entities
    for (size_t i = 0; i < ENTITY_COUNT; i++) {
      const Entity e = world.createEntity();
      entities.emplace_back(e);

      world.addComponent(e, Components::Transform(
        static_cast<float>(i), static_cast<float>(i)));
      if (i % 2 == 0) {
        world.addComponent(e, Components::BoxCollider(1.0F, 1.0F));
      }
    }

    // Verify transform components exist
    const auto& transformEntities = world.findAllOfType<Components::Transform>();
    REQUIRE(transformEntities.size() == ENTITY_COUNT);

    // Verify that half have BoxColliders
    const auto& boxColliderEntities = world.findAllOfType<Components::BoxCollider>();
    REQUIRE(boxColliderEntities.size() == ENTITY_COUNT / 2);
  }

  SECTION("Sparse entity IDs")
  {
    SparseSet<Components::Transform> sparseSet;

    // Insert components with very sparse entity IDs
    sparseSet.insert(1, Components::Transform(1.0F, 1.0F));
    sparseSet.insert(1000000, Components::Transform(2.0F, 2.0F));
    sparseSet.insert(5, Components::Transform(3.0F, 3.0F));
    sparseSet.insert(999999, Components::Transform(4.0F, 4.0F));

    REQUIRE(sparseSet.size() == 4);
    REQUIRE(sparseSet.contains(1));
    REQUIRE(sparseSet.contains(1000000));
    REQUIRE(sparseSet.contains(5));
    REQUIRE(sparseSet.contains(999999));

    // Remove from the middle of sparse range
    sparseSet.remove(5);

    REQUIRE(sparseSet.size() == 3);
    REQUIRE_FALSE(sparseSet.contains(5));
    REQUIRE(sparseSet.contains(1));
    REQUIRE(sparseSet.contains(1000000));
    REQUIRE(sparseSet.contains(999999));
  }

  SECTION("Component with complex data")
  {
    Entity entity = world.createEntity();

    Components::Name name(
      "Very long component name with special characters: !@#$%^&*()");
    world.addComponent(entity, name);
        
    REQUIRE(world.hasComponent<Components::Name>(entity));
    REQUIRE(world.getComponent<Components::Name>(entity) == name);
  }
}