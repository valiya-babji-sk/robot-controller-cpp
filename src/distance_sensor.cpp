#include "distance_sensor.hpp"

void DistanceSensor::setDistance(double distance)
{
    this->distance = distance;
}

double DistanceSensor::getDistance() const
{
    return distance;
}