#include "route.h"
#include <cstddef> 

Route::Route(const std::vector<int>& brightnessLevels) : brightness(brightnessLevels) {}

int Route::calculateStops(int guardEnergy) {
    int stops = 0;
    int lastBrightness = brightness[0];

    for (std::size_t i = 1; i < brightness.size(); ++i) {
        if (brightness[i] < lastBrightness) {
            stops++;
            lastBrightness = brightness[i];
            guardEnergy--; 
            if (guardEnergy <= 0) break; 
        }
    }

    return stops;
}

int Route::calculateListens(int guardEnergy) {
    int listens = 0;
    int lastBrightness = brightness[0];

    for (std::size_t i = 1; i < brightness.size(); ++i) {
        if (brightness[i] < lastBrightness) {
            listens++;
            lastBrightness = brightness[i];
            guardEnergy--; 
            if (guardEnergy <= 0) break; 
        }
    }

    return listens;
}
