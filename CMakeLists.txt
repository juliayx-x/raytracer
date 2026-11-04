cmake_minimum_required(VERSION 3.16)
project(raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(raytracer src/main.cc
        src/vec3.h)
target_compile_options(raytracer PRIVATE -Wall -Wextra)

find_package(Threads REQUIRED)
target_link_libraries(raytracer PRIVATE Threads::Threads)

option(ENABLE_TSAN "Build with ThreadSanitizer" OFF)
if(ENABLE_TSAN)
    target_compile_options(raytracer PRIVATE -fsanitize=thread -g)
    target_link_options(raytracer PRIVATE -fsanitize=thread)
endif()