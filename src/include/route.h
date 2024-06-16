#ifndef ROUTE_H
#define ROUTE_H

#include <vector>

class Route {
public:
    Route(const std::vector<int>& brightnessLevels, int maxSteps);
    std::pair<int, int> calculateStops(int start);


private:
    std::vector<int> brightness;
    int max_steps;

};

#endif // ROUTE_H

