cmake_minimum_required(VERSION 3.5)

project(FluidSimulation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2 COMPONENTS network audio graphics window system REQUIRED)
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

file(GLOB SRCS *.cpp *.h)

add_executable(FluidSimulation ${SRCS})
target_link_libraries(FluidSimulation sfml-graphics sfml-audio sfml-network sfml-window sfml-system ${GLM_LIBRARIES})
