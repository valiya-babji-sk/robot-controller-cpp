#pragma once
#include <atomic>
#include <thread>
#include <condition_variable>
#include <mutex>

struct SensorData
{
    double distance;
    bool valid;
};

class DistanceSensor
{
public:
    DistanceSensor();
    ~DistanceSensor();

    void start();
    void stop();

    bool waitForUpdate();

    void setData(double distance, bool valid);
    SensorData getData();
private:
    SensorData data{10.0, true};
    std::atomic<bool> running{false};
    std::thread sensorThread;

    std::mutex dataMutex;
    std::condition_variable dataCondition;
    bool dataReady{false};
};
