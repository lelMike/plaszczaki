#include "../include/guards.h"
#include <climits>

// function to select the guard with the highest energy who is available to work
Guard selectGuard(const std::vector<Guard>& guards, const std::vector<bool>& available) {
    Guard maxGuard = {INT_MIN, 'F', -1}; // initialising the function with minimum energy and invalid index
    for (int i = 0; i < guards.size(); ++i) {
        if (available[i] && guards[i].availability == 'W' && guards[i].energy > maxGuard.energy) {
            maxGuard = guards[i];
        }
    }
    return maxGuard;
}