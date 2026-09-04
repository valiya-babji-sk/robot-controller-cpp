#pragma once

#include <memory>
#include "motor.hpp"

class Robot
{
public:
    Robot(std::unique_ptr<Motor> left,
          std::unique_ptr<Motor> right);

    void moveForward(double speed);
    void stop();
    void turn(double leftSpeed, double rightSpeed);
    void printStatus() const;

private:
    void setSpeed(double speed);
    std::unique_ptr<Motor> leftMotor;
    std::unique_ptr<Motor> rightMotor;
};