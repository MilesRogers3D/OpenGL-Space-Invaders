set(ENGINE_LIB_NAME "Engine")
include(cmake/engine_deps.cmake)

add_library(${ENGINE_LIB_NAME} SHARED
  src/Scene/ECS/IComponentArray.h
  src/Scene/ECS/Types/SparseSet.cpp
  src/Scene/ECS/Types/SparseSet.h
  src/Scene/ECS/World.cpp
  src/Scene/ECS/World.h
  src/Core/Application/Application.cpp
  src/Core/Application/Application.h
  src/Platform/Window/Window.cpp
  src/Platform/Window/Window.h
  src/Core/Logger/Logger.cpp
  src/Core/Logger/Logger.h
  src/defs.h
)

target_include_directories(${ENGINE_LIB_NAME}
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

target_link_libraries(${ENGINE_LIB_NAME}
  PRIVATE
    glfw
    glad
    spdlog
    glm
)

target_compile_definitions(${ENGINE_LIB_NAME}
  PRIVATE ENG_DLL_EXPORT=1)