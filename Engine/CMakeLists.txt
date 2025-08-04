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
  src/Renderer/Renderer.cpp
  src/Renderer/Renderer.h
  src/Platform/Input/Input.h
  src/Core/Math/MathTypes.h
  src/IO/Model/IModelParser.h
  src/IO/Model/OBJ/OBJParser.cpp
  src/IO/Model/OBJ/OBJParser.h
  src/IO/Model/Types/ModelTypes.h
  src/Renderer/Types/Color.cpp
  src/Renderer/Types/Color.h
  src/Renderer/Types/ColorPresets.h
)

target_include_directories(${ENGINE_LIB_NAME}
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

target_link_libraries(${ENGINE_LIB_NAME}
  PUBLIC
    spdlog
  PRIVATE
    glfw
    glad
    glm
)

target_compile_definitions(${ENGINE_LIB_NAME}
  PRIVATE ENG_DLL_EXPORT=1)