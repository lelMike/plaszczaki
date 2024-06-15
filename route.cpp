#include "route.h"
#include <cstddef> // For std::size_t

Route::Route(const std::vector<int>& brightnessLevels, int maxSteps)
    : brightness(brightnessLevels), max_steps(maxSteps) {}

// Calculate the number of stops based on brightness levels
int Route::calculateStops() {
    int stops = 0;
    int lastBrightness = brightness[0];
    int steps = 0;

    for (std::size_t i = 1; i < brightness.size(); ++i) {
        steps++;
        if (brightness[i] < lastBrightness || steps >= max_steps) {
            stops++; // Increment stops
            if (brightness[i] > lastBrightness) {
                break; // Stop the loop if the stop point is brighter
            }
            lastBrightness = brightness[i]; // Update last brightness
            steps = 0; // Reset step counter
        }
    }

    return stops;
}

// Calculate the number of listens to the melody based on brightness levels
int Route::calculateListens() {
    int listens = 0;
    int lastBrightness = brightness[0];
    int steps = 0;

    for (std::size_t i = 1; i < brightness.size(); ++i) {
        steps++;
        if (brightness[i] < lastBrightness || steps >= max_steps) {
            if (brightness[i] > lastBrightness) {
                listens++; // Increment listens if the stop point is brighter
            }
            lastBrightness = brightness[i]; // Update last brightness
            steps = 0; // Reset step counter
        }
    }

    return listens;
}
