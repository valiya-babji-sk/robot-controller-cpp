#include "robot.hpp"

Robot::Robot(std::unique_ptr<Motor> left,
             std::unique_ptr<Motor> right)
    : leftMotor(std::move(left)),
      rightMotor(std::move(right))
{
}

void Robot::setSpeed(double speed)
{
    leftMotor->setSpeed(speed);
    rightMotor->setSpeed(speed);
}

void Robot::moveForward(double speed)
{
    setSpeed(speed);
}

void Robot::stop()
{
    setSpeed(0);
}

void Robot::turn(double leftSpeed, double rightSpeed)
{
    leftMotor->setSpeed(leftSpeed);
    rightMotor->setSpeed(rightSpeed);
}

void Robot::printStatus() const
{
    leftMotor->printStatus();
    rightMotor->printStatus();
}
