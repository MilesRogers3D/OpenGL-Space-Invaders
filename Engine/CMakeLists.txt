set(ENGINE_LIB_NAME "Engine")

add_library(${ENGINE_LIB_NAME} SHARED
  src/Scene/ECS/IComponentArray.h
  src/Scene/ECS/Types/SparseSet.cpp
  src/Scene/ECS/Types/SparseSet.h
  src/Scene/ECS/World.cpp
  src/Scene/ECS/World.h
)

target_include_directories(${ENGINE_LIB_NAME}
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
)