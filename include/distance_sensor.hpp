#pragma once
#include <atomic>
#include <thread>

class DistanceSensor
{
public:
    void setDistance(double distance);
    double getDistance() const;

    void start();
    void stop();

private:
    std::atomic<double> distance{10.0};
    std::atomic<bool> running{false};
    std::thread sensorThread;
    ~DistanceSensor();
};
