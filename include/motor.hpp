#pragma once
#include <iostream>

class Motor
{
public:
    Motor(int id);

    void setSpeed(double speed);
    double getSpeed() const;
    void printStatus() const;

private:
    int id;
    double speed = 0.0;
};
