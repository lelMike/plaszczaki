#include "patrol.h"

std::vector<int> plan_patrol(const std::vector<int>& brightness) {
    std::vector<int> stops;
    int n = brightness.size();
    stops.push_back(0); 

    int last_stop = 0;
    for (int i = 1; i < n; ++i) {
        if (brightness[i] < brightness[last_stop]) {
            stops.push_back(i);
            last_stop = i;
        }
    }

    return stops;
}
