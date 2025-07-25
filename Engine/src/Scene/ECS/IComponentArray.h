#pragma once

#include <cstdint>
#include <limits>

namespace Engine {

using Entity = uint32_t;
constexpr Entity NULL_ENTITY = std::numeric_limits<uint32_t>::max();

class IComponentArray
{
public:
  virtual ~IComponentArray() = default;
  virtual void onDestroyed(Entity entity) = 0;
};

}