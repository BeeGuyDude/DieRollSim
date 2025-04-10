#0) Configure project directory settings
cmake_minimum_required(VERSION 3.31)
project(DieRollSim)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

#1) Add the test executable
add_executable(drs_main src/die_rolling_simulation.cpp)

#2) Include directories for the test target
target_include_directories(drs_main PRIVATE ${PROJECT_SOURCE_DIR}/include)

#3) Enable testing
enable_testing()
