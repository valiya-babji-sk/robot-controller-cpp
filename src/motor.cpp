#include "motor.hpp"

Motor::Motor(int id) : id(id) {}

void Motor::setSpeed(double speed)
{
    this->speed = speed;
}

double Motor::getSpeed() const
{
    return speed;
}

void Motor::printStatus() const
{
    std::cout << "Motor " << id << " | Speed: " << speed << "\n";
}