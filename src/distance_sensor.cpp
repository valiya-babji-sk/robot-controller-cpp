#include "distance_sensor.hpp"
#include <thread>
#include <iostream>

void DistanceSensor::setDistance(double distance)
{
    this->distance.store(distance);
}

double DistanceSensor::getDistance() const
{
    return distance.load();
}

void DistanceSensor::start()
{
    running.store(true);
    sensorThread = std::thread([this]()
                               {
        while (running.load())
        {
            setDistance(getDistance() * 2);

            std::cout << "[Sensor] Distance: "
                    << getDistance()
                    << std::endl;

            std::this_thread::sleep_for(
                std::chrono::milliseconds(500));
        } });
}

void DistanceSensor::stop()
{
    running.store(false);

    if (sensorThread.joinable())
    {
        sensorThread.join();
    }
}
