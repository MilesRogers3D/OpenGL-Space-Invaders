set(TESTS_EXE_NAME "_TESTS")
enable_testing()

include(cmake/test_deps.cmake)

add_executable(${TESTS_EXE_NAME}
  src/Engine/Scene/ECSTests.cpp
  src/Engine/Renderer/Types/ColorTests.cpp
)
target_link_libraries(${TESTS_EXE_NAME}
  PRIVATE
    Engine
    Catch2::Catch2
    Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(${TESTS_EXE_NAME})