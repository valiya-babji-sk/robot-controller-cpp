#pragma once

#include "robot.hpp"
#include "distance_sensor.hpp"

enum class RobotState
{
    STOPPED,
    MOVING,
    OBSTACLE_DETECTED,
    TURNING_LEFT
};

class Controller
{
public:
    Controller(Robot& robot, DistanceSensor& sensor);

    void moveRobot();

    void run();

    RobotState getState() const;

private:
    Robot& robot;
    DistanceSensor& sensor;

    RobotState state = RobotState::STOPPED;

    static constexpr double SAFE_DISTANCE = 30.0;

    void executeState();

    void changeState(RobotState newState);

    const char* stateToString(RobotState state);
};