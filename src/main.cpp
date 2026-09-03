#include <memory>

#include "distance_sensor.hpp"
#include "motor.hpp"
#include "robot.hpp"

int main()
{
    auto leftMotor = std::make_unique<Motor>(1);
    auto rightMotor = std::make_unique<Motor>(2);

    Robot robot(std::move(leftMotor), std::move(rightMotor));

    DistanceSensor sensor;

    sensor.setDistance(50);

    if (sensor.getDistance() >= 30)
        robot.moveForward(60);
    else
        robot.stop();

    robot.printStatus();

    sensor.setDistance(20);

    if (sensor.getDistance() >= 30)
        robot.moveForward(60);
    else
        robot.stop();

    robot.printStatus();

    return 0;
}