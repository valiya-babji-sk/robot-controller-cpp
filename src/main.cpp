#include <memory>
#include "controller.hpp"
#include "distance_sensor.hpp"
#include "motor.hpp"
#include "robot.hpp"
#include <thread>
#include <chrono>
#include <csignal>
#include <atomic>

std::atomic<bool> shutdownRequested{false};


void handleSignal(int signal)
{
    if (signal == SIGINT)
    {
        shutdownRequested.store(true);
    }
}

int main()
{
    std::signal(SIGINT, handleSignal);
    auto leftMotor = std::make_unique<Motor>(1);
    auto rightMotor = std::make_unique<Motor>(2);

    Robot robot(std::move(leftMotor), std::move(rightMotor));
    DistanceSensor sensor;
    Controller controller(robot, sensor);

    controller.run(shutdownRequested);

    sensor.stop();

    return 0;
}
