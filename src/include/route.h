/*#ifndef ROUTE_H
#define ROUTE_H

#include <vector>

/*class Route {
public:
    Route(const std::vector<int>& brightnessLevels, int maxSteps);
    int calculateStops();
    int calculateListens();
    static int findOptimalStartPoint(const std::vector<int>& brightnessLevels, int maxSteps);
    static int bestPoint(const std::vector<int> &brightnessLevels, int &energy, int start);


private:
    std::vector<int> brightness;
    int max_steps;

    int calculateStops(int guardEnergy);
};





#endif // ROUTE_H*/



#ifndef ROUTE_H
#define ROUTE_H

#include <vector>

class Route {
public:
    Route(const std::vector<int>& brightnessLevels, int maxSteps);
    std::pair<int, int> calculateStops(int start);
    int calculateListens();


private:
    std::vector<int> brightness;
    int max_steps;

};

#endif // ROUTE_H

