#pragma once

class DistanceSensor
{
public:
    void setDistance(double distance);
    double getDistance() const;

private:
    double distance = 0.0;
};