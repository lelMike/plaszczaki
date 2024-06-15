#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "guards.h"
#include "route.h"

int main() {
    std::ifstream input("input.txt");

    if (!input.is_open()) {
        std::cerr << "Error opening input file." << std::endl;
        return 1;
    }

    int days, points, max_steps;  // reading the number of days, points, and max_steps from the input file
    input >> days >> points >> max_steps;

    std::vector<int> brightness(points); // reading the brightness levels from file
    for (int i = 0; i < points; ++i) {
        input >> brightness[i];
    }

    Route route(brightness, max_steps); // initializing the route

    // Read guards' energy and availability
    std::unordered_map<int, int> guardEnergy;
    std::unordered_map<int, std::vector<int>> guardVacations;
    int guardCount;
    input >> guardCount;

    srand(time(0));
    for (int i = 0; i < guardCount; ++i) {
        int id = i + 1;
        int energy = rand() % 10 + 1; // assigning random energy to guards in the range 1-10
        guardEnergy[id] = energy;
        std::cout << "Guard " << id << " initial energy: " << energy << std::endl;
    }

    for (int i = 0; i < guardCount; ++i) { // reading vacation days for each guard
        int vacationDays;
        input >> vacationDays;
        for (int j = 0; j < vacationDays; ++j) {
            int vacationDay;
            input >> vacationDay;
            guardVacations[i + 1].push_back(vacationDay);
        }
    }
    Guards guards(guardEnergy, guardVacations); // initializing Guards object

    for (int day = 0; day < days; ++day) {
        auto selectedGuard = guards.selectGuard(day);
        if (selectedGuard.id != 0) { // ensuring a valid guard is selected
            int optimalStart = route.findOptimalStartPoint();
            std::rotate(brightness.begin(), brightness.begin() + optimalStart, brightness.end()); // Rotate to the optimal start point

            int listens = route.calculateListens();
            guards.updateGuard(selectedGuard.id, 0, day); // updating guard without stops
            std::cout << "Day " << day + 1 << ": Guard " << selectedGuard.id << " with " << listens << " listens.\n";
        } else {
            std::cout << "Day " << day + 1 << ": No available guard.\n";
        }
    }

    input.close();
    return 0;
}
