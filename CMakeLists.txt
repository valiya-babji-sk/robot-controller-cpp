cmake_minimum_required(VERSION 3.20)

project(robot_controller)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(robot_controller
    src/main.cpp
    src/motor.cpp
    src/robot.cpp
    src/distance_sensor.cpp
    src/controller.cpp
)