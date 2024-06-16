#include "../include/route.h"
#include <cstddef> // For std::size_t
#include <iostream>


Route::Route(const std::vector<int>& brightnessLevels, int maxSteps)
        : brightness(brightnessLevels), max_steps(maxSteps) {}

std::pair<int, int> Route::calculateStops(int start) { // Calculating the number of stops based on brightness levels and calculating number of listens
    int i = 0;
    // first - steps
    // second - listens
    std::pair<int, int> pair;
    pair.first = 0;
    pair.second = 0;;
    int saved;
    int ctrl;
    while(true){
        saved = 0;
        ctrl = 0;
        for(int j = 0; j < max_steps; j++){

            if(brightness[(start + j) % brightness.size()] > brightness[(start + j + 1) % brightness.size()]){
                saved = (start + j) % brightness.size();
                ctrl = j + 1;
            }
        }

        if(saved != 0){
            pair.first++;
            i += ctrl;
            start += ctrl;
        }
        else{
            pair.second++;
            pair.first++;
            i += max_steps;
            start+= max_steps;
        }


        if(i >= brightness.size()){
            break;
        }

    }
    return pair;
}


