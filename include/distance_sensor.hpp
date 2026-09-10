#pragma once
#include <atomic>
#include <thread>
#include <condition_variable>
#include <mutex>

class DistanceSensor
{
public:
    DistanceSensor();
    ~DistanceSensor();
    void setDistance(double distance);
    double getDistance() const;

    void start();
    void stop();

    bool waitForUpdate();
private:
    std::atomic<double> distance{10.0};
    std::atomic<bool> running{false};
    std::thread sensorThread;

    std::mutex dataMutex;
    std::condition_variable dataCondition;
    bool dataReady{false};
};
