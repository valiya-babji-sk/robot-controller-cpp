#include "distance_sensor.hpp"
#include <iostream>
#include <chrono>

void DistanceSensor::setDistance(double distance)
{
    this->distance.store(distance);

    {
        std::lock_guard<std::mutex> lock(dataMutex);
        dataReady = true;
    }

    dataCondition.notify_one();
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
    dataCondition.notify_one();
    if (sensorThread.joinable())
    {
        sensorThread.join();
    }
}

DistanceSensor::DistanceSensor()
{
    start();
}

DistanceSensor::~DistanceSensor()
{
    stop();
}

bool DistanceSensor::waitForUpdate()
{
    std::unique_lock<std::mutex> lock(dataMutex);

    dataCondition.wait(lock, [this]()
    {
        return dataReady || !running.load();
    });

    if (!running.load())
        return false;

    dataReady = false;
    return true;
}
