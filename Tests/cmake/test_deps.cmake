include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(Catch2
  GIT_REPOSITORY "https://github.com/catchorg/Catch2.git"
  GIT_TAG "2b60af89e23d28eefc081bc930831ee9d45ea58b"
  GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(Catch2)