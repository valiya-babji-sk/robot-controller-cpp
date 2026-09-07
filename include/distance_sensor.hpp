#pragma once

#include <atomic>

class DistanceSensor
{
public:
    void setDistance(double distance);
    double getDistance() const;

private:
    std::atomic<double> distance{0.0};
};
