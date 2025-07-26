set(GLAD_LIB_NAME "glad")

add_library(${GLAD_LIB_NAME} STATIC
  src/glad.c
  include/glad/glad.h
  include/KHR/khrplatform.h
)

target_include_directories(${GLAD_LIB_NAME}
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)