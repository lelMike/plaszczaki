#ifndef ROUTE_H
#define ROUTE_H

#include <vector>
#include <cstddef>

class Route {
public:
    Route(const std::vector<int>& brightnessLevels);
    int calculateStops(int guardEnergy);
    int calculateListens(int guardEnergy);

private:
    std::vector<int> brightness;
};

#endif 
