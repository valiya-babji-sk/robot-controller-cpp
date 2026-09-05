#include <iostream>
#include "controller.hpp"

Controller::Controller(Robot& robot, DistanceSensor& sensor)
    : robot(robot), sensor(sensor)
{
}

RobotState Controller::getState() const
{
    return state;
}

void Controller::moveRobot()
{
    double distance = sensor.getDistance();

    if (distance < SAFE_DISTANCE)
    {
        changeState(RobotState::OBSTACLE_DETECTED);
    }
    else
    {
        changeState(RobotState::MOVING);
    }
    executeState();
}

void Controller::run()
{
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "[Controller] Control cycle: " << i + 1 << std::endl;
        moveRobot();
    }
}

const char* Controller::stateToString(RobotState state)
{
    switch(state)
    {
        case RobotState::STOPPED:
            return "STOPPED";

        case RobotState::MOVING:
            return "MOVING";

        case RobotState::OBSTACLE_DETECTED:
            return "OBSTACLE_DETECTED";

        case RobotState::TURNING_LEFT:
            return "TURNING_LEFT";
    }

    return "UNKNOWN";
}

void Controller::changeState(RobotState newState){

     if (state == newState)
        return;

    std::cout << "[Controller] State: "
              << stateToString(state)
              << " -> "
              << stateToString(newState)
              <<std::endl;
              
    state = newState;
}

void Controller::executeState() {
    switch(state)
    {
        case RobotState::MOVING:
            robot.moveForward(50);
            break;

        case RobotState::STOPPED:
            robot.stop();
            break;

        case RobotState::OBSTACLE_DETECTED:
            robot.stop();
            break;

        case RobotState::TURNING_LEFT:
            robot.turn(20,60);
            break;
    }
    robot.printStatus();
}