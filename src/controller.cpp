#include <iostream>
#include <thread>
#include <chrono>
#include "controller.hpp"

Controller::Controller(Robot &robot, DistanceSensor &sensor)
    : robot(robot), sensor(sensor)
{
}

RobotState Controller::getState() const
{
    return state;
}

void Controller::moveRobot()
{
    auto data = sensor.getData();

    if (!data.valid)
    {
        std::cout << "[Controller] Invalid sensor data\n";
        return;
    }

    double distance = data.distance;

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
    const auto cyclePeriod = std::chrono::milliseconds(100);

    auto nextCycle = std::chrono::steady_clock::now();
    auto previousCycle = nextCycle;

    while (true)
    {
        auto cycleStart = std::chrono::steady_clock::now();

        auto actualPeriod =
            std::chrono::duration_cast<std::chrono::microseconds>(
                cycleStart - previousCycle);

        std::cout << "[Controller] Cycle period: "
                  << actualPeriod.count() / 1000.0
                  << " ms"
                  << std::endl;

        previousCycle = cycleStart;

        moveRobot();

        auto cycleEnd = std::chrono::steady_clock::now();

        auto executionTime =
            std::chrono::duration_cast<std::chrono::microseconds>(
                cycleEnd - cycleStart);

        std::cout << "[Controller] Cycle execution: "
                  << executionTime.count() / 1000.0
                  << " ms"
                  << std::endl;

        if(executionTime > cyclePeriod){
            std::cout << "[Controller] WARNING: Cycle deadline missed!"
                  << std::endl;
        }          

        nextCycle += cyclePeriod;

        std::this_thread::sleep_until(nextCycle);
    }
}

const char *Controller::stateToString(RobotState state)
{
    switch (state)
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

void Controller::changeState(RobotState newState)
{
    if (state == newState)
        return;

    std::cout << "[Controller] State: "
              << stateToString(state)
              << " -> "
              << stateToString(newState)
              << std::endl;

    state = newState;
}

void Controller::executeState()
{
    switch (state)
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
        robot.turn(20, 60);
        break;
    }

    robot.printStatus();
}
