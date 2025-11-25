cmake_minimum_required(VERSION 3.20)
project(
    backtester
    VERSION 0.0.0
    DESCRIPTION "Trading Backtester Written in C++"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Dependencies ----
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(GTest REQUIRED)

include(FetchContent)
FetchContent_Declare(
  glaze
  GIT_REPOSITORY https://github.com/stephenberry/glaze.git
  GIT_TAG v5.7.1
)
FetchContent_MakeAvailable(glaze)

# ---- Library ----
file(GLOB_RECURSE BACKTESTER_SOURCES
    CONFIGURE_DEPENDS
    src/*.cpp
)

add_library(backtester_lib ${BACKTESTER_SOURCES})

target_include_directories(backtester_lib
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_link_libraries(backtester_lib
    PUBLIC fmt::fmt
           spdlog::spdlog
           glaze::glaze
)

target_compile_features(backtester_lib PUBLIC cxx_std_23)

# ---- Executable ----
add_executable(backtester src/main.cpp)
target_link_libraries(backtester PRIVATE backtester_lib)

# ---- Tests ----
enable_testing()
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS tests/*.cpp)
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests PRIVATE backtester_lib GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(tests)
