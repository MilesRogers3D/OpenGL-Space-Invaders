include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

set(ENGINE_DEPS_LIST "")
add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/ext)

## GLFW ##
FetchContent_Declare(glfw
  GIT_REPOSITORY "https://github.com/glfw/glfw.git"
  GIT_TAG "7b6aead9fb88b3623e3b3725ebb42670cbe4c579"
  GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(glfw)
list(APPEND ${ENGINE_DEPS_LIST} glfw)

## GLAD ##
list(APPEND ${ENGINE_DEPS_LIST} glad)

## SPDLOG ##
FetchContent_Declare(spdlog
  GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
  GIT_TAG "6fa36017cfd5731d617e1a934f0e5ea9c4445b13"
  GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(spdlog)
list(APPEND ${ENGINE_DEPS_LIST} spdlog)