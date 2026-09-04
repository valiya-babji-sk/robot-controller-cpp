# 🤖 Robot Controller (C++ Robotics Foundations)

A production-style C++ robotics project built while learning robotics software engineering from first principles.

## Overview

This project simulates the software architecture of a differential-drive mobile robot using modern C++.

Current features include:

* Differential-drive robot architecture.
* Distance Sensor abstraction.
* Finite State Machine (FSM) controller.
* CMake build system.

## Architecture

```text
DistanceSensor
      │
      ▼
 Controller
 ├── moveRobot()
 ├── changeState()
 ├── executeState()
 └── RobotState
      │
      ▼
    Robot
 ├── moveForward()
 ├── stop()
 └── turn()
      │
      ▼
 Motor(1)    Motor(2)
```

**Design principle:** Robot controls hardware. Controller controls behaviour.

## Project Structure

```text
robot-controller-cpp/
├── include/      # Header files
├── src/          # C++ source files
├── build/        # Generated build files (ignored by Git)
├── CMakeLists.txt
├── README.md
└── .gitignore
```

## Build

### Windows (MSVC)

```bash
mkdir build
cd build
cmake ..
cmake --build .
Debug/robot_controller.exe
```

### Ubuntu (GCC)

```bash
mkdir build
cd build
cmake ..
make
./robot_controller
```