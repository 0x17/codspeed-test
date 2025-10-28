cmake_minimum_required(VERSION 3.12)
include(FetchContent)

project(codspeed-test VERSION 0.0.0 LANGUAGES CXX)

# Enable release mode with debug symbols to display useful profiling data
set(CMAKE_BUILD_TYPE RelWithDebInfo)

set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON)

FetchContent_Declare(
    google_benchmark
    GIT_REPOSITORY https://github.com/CodSpeedHQ/codspeed-cpp # Target the codspeed cpp repository
    SOURCE_SUBDIR google_benchmark # Make sure to target the google_benchmark subdirectory
    GIT_TAG main # Or chose a specific version or git ref, check the releases page on the repository
)

FetchContent_MakeAvailable(google_benchmark)

# Declare your benchmark executable and its sources here
add_executable(my_benchmark_executable main.cpp)

# Link your executable against the `benchmark::benchmark`, the `google_benchmark` library
# Note: the first argument must match the first argument of the `add_executable` call
target_link_libraries(my_benchmark_executable benchmark::benchmark)