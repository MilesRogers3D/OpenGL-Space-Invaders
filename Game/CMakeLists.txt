set(GAME_EXECUTABLE_NAME "OpenGL_Space_Invaders")

add_executable(${GAME_EXECUTABLE_NAME}
  src/main.cpp
)

target_link_libraries(${GAME_EXECUTABLE_NAME}
  PRIVATE Engine
)