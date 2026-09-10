#include <memory>
#include "controller.hpp"
#include "distance_sensor.hpp"
#include "motor.hpp"
#include "robot.hpp"
#include <thread>
#include <chrono>

int main()
{
    auto leftMotor = std::make_unique<Motor>(1);
    auto rightMotor = std::make_unique<Motor>(2);

    Robot robot(std::move(leftMotor), std::move(rightMotor));
    DistanceSensor sensor;
    Controller controller(robot, sensor);

    for (int i = 0; i < 5; ++i)
    {
        if (!sensor.waitForUpdate())
            break;  // sensor shut down

        controller.moveRobot();
    }

    return 0;
}
