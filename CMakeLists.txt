cmake_minimum_required(VERSION 3.10)
project(AoC)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Include directories
include_directories(include/common)
include_directories(include/runner)
include_directories(include/solutions)

# Solutions library
add_library(solutions STATIC
    src/solutions/aoc_day.cpp
    src/solutions/aoc_days.cpp
    src/solutions/aoc_day_0.cpp
    src/solutions/aoc_day_1.cpp
    src/solutions/aoc_day_2.cpp
    src/runner/file_utils.cpp
)

# Include directories for solutions
target_include_directories(solutions PUBLIC
    include/solutions
)

# Main executable
add_executable(aoc
    src/aoc.cpp
)

# Link libraries for the main executable
target_link_libraries(aoc PRIVATE solutions)

# Set default build target
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT aoc)

# Clean target
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_SOURCE_DIR}/clean-all.cmake
)

enable_testing()

add_executable(
  tests
  src/tests.cpp
)
target_link_libraries(
  tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)