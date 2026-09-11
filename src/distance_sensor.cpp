#include "distance_sensor.hpp"
#include <iostream>
#include <chrono>


void DistanceSensor::start()
{
    running.store(true);
    sensorThread = std::thread([this]()
                               {
        while (running.load())
        {
            auto data = getData();
            setData(data.distance * 2, true);
            std::cout << "[Sensor] Distance: "
                    << getData().distance
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

SensorData DistanceSensor::getData()
{
    std::lock_guard<std::mutex> lock(dataMutex);

    return data;
}

void DistanceSensor::setData(double distance, bool valid)
{
    {
        std::lock_guard<std::mutex> lock(dataMutex);

        data.distance = distance;
        data.valid = valid;
        dataReady = true;
    }

    dataCondition.notify_one();
}
