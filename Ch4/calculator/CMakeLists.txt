# Top-level CMakeLists.txt

cmake_minimum_required(VERSION 3.2...3.15)

project(
  calculator
  VERSION 1.0
  DESCRIPTION "A simple calculator commandline application."
  LANGUAGES C)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

add_compile_options(-W -Wall -Wextra -g -fdiagnostics-color=always)

add_executable(calculator src/main.c src/stack.c src/token.c);
target_include_directories(calculator PRIVATE include)
target_link_options(calculator PRIVATE -lm)

add_library(libbuffer src/buffer.c)
target_include_directories(libbuffer PRIVATE include)

target_link_libraries(calculator PRIVATE libbuffer)
