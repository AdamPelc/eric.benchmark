cmake_minimum_required(VERSION 3.28)
project(eric_benchmark)

set(CMAKE_CXX_STANDARD 20)

find_package(benchmark REQUIRED)

add_library(helper)

add_executable(benchmark_format)
target_link_libraries(benchmark_format
    PRIVATE
    benchmark::benchmark
    benchmark::benchmark_main
    helper
)
target_compile_options(benchmark_format
    PRIVATE
    -Og
    -g
)
target_compile_definitions(benchmark_format
    PRIVATE
    NDEBUG
)

add_subdirectory(benchmark)
add_subdirectory(helper)
