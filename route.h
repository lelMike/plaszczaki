#ifndef ROUTE_H
#define ROUTE_H

#include <vector>

class Route {
public:
    Route(const std::vector<int>& brightnessLevels, int maxSteps);
    int calculateStops();
    int calculateListens();

private:
    std::vector<int> brightness;
    int max_steps;
};

#endif // ROUTE_H
