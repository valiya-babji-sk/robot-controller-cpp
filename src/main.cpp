#include <memory>
#include "controller.hpp"
#include "distance_sensor.hpp"
#include "motor.hpp"
#include "robot.hpp"

int main()
{
    auto leftMotor = std::make_unique<Motor>(1);
    auto rightMotor = std::make_unique<Motor>(2);

    Robot robot(std::move(leftMotor), std::move(rightMotor));
    DistanceSensor sensor;
    Controller controller(robot, sensor);

    sensor.setDistance(50);
    controller.moveRobot();
    robot.printStatus();

    sensor.setDistance(20);
    controller.moveRobot();
    robot.printStatus();

    return 0;
}