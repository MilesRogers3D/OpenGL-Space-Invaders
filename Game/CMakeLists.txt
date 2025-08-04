set(GAME_EXECUTABLE_NAME "OpenGL_Space_Invaders")

add_executable(${GAME_EXECUTABLE_NAME}
  src/main.cpp
  src/Game.cpp
  src/Game.h
)

target_link_libraries(${GAME_EXECUTABLE_NAME}
  PRIVATE Engine
)

add_custom_target(copy_data
  COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/res/"
    "$<TARGET_FILE_DIR:OpenGL_Space_Invaders>/res/"
  COMMENT "Copying game /res/ folder"
)
add_dependencies(${GAME_EXECUTABLE_NAME} copy_data)