cmake_minimum_required(VERSION 3.5)

project(FluidSimulation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(
  SFML 2
  COMPONENTS network audio graphics window system
  REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB SRCS *.cpp *.hpp)

add_executable(FluidSimulation ${SRCS})
target_link_libraries(FluidSimulation sfml-graphics sfml-audio sfml-network
                      sfml-window sfml-system)