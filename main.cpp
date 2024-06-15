#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include "guards.h"
#include "route.h"

int main() {
    std::ifstream input("input.txt");

    if (!input.is_open()) {
        std::cerr << "Error opening input file." << std::endl;
        return 1;
    }

    // Read the number of days (week), points, and max_steps
    int days, points, max_steps;
    input >> days >> points >> max_steps;

    // Read brightness levels
    std::vector<int> brightness(points);
    for (int i = 0; i < points; ++i) {
        input >> brightness[i];
    }

    // Initialize route
    Route route(brightness, max_steps);

    // Read guards' energy and availability
    std::unordered_map<int, int> guardEnergy;
    std::unordered_map<int, std::vector<int>> guardVacations;
    int guardCount;
    input >> guardCount;

    // Assign random energy to guards in the range 1-10
    srand(time(0));
    for (int i = 0; i < guardCount; ++i) {
        int id = i + 1;
        int energy = rand() % 10 + 1;
        guardEnergy[id] = energy;
        std::cout << "Guard " << id << " initial energy: " << energy << std::endl;
    }

    // Read vacation days for each guard
    for (int i = 0; i < guardCount; ++i) {
        int vacationDays;
        input >> vacationDays;
        for (int j = 0; j < vacationDays; ++j) {
            int vacationDay;
            input >> vacationDay;
            guardVacations[i + 1].push_back(vacationDay);
        }
    }

    // Initialize Guards object
    Guards guards(guardEnergy, guardVacations);

    // Schedule guards for each day
    for (int day = 0; day < days; ++day) {
        auto selectedGuard = guards.selectGuard(day);
        if (selectedGuard.id != 0) { // Ensure a valid guard is selected
            int stops = route.calculateStops();
            int listens = route.calculateListens();
            guards.updateGuard(selectedGuard.id, stops, day);
            std::cout << "Day " << day + 1 << ": Guard " << selectedGuard.id << " with " << listens << " listens to the melody.\n";
        } else {
            std::cout << "Day " << day + 1 << ": No available guard.\n";
        }
    }

    input.close();
    return 0;
}
