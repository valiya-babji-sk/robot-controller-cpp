#include "distance_sensor.hpp"

void DistanceSensor::setDistance(double distance)
{
    this->distance.store(distance);
}

double DistanceSensor::getDistance() const
{
    return distance.load();
}
