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

    int days, points;
    input >> days >> points;

    std::vector<int> brightness(points);
    for (int i = 0; i < points; ++i) {
        input >> brightness[i];
    }

    Route route(brightness);

    std::unordered_map<int, int> guardEnergy;
    std::unordered_map<int, std::vector<int>> guardVacations;
    int guardCount;
    input >> guardCount;

    srand(time(0));
    for (int i = 0; i < guardCount; ++i) {
        int id = i + 1;
        int energy = rand() % 10 + 1;
        guardEnergy[id] = energy;
        std::cout << "Guard " << id << " initial energy: " << energy << std::endl;
    }

    for (int i = 0; i < guardCount; ++i) {
        int vacationDays;
        input >> vacationDays;
        for (int j = 0; j < vacationDays; ++j) {
            int vacationDay;
            input >> vacationDay;
            guardVacations[i + 1].push_back(vacationDay);
        }
    }

    Guards guards(guardEnergy, guardVacations);

    for (int day = 0; day < days; ++day) {
        auto selectedGuard = guards.selectGuard(day);
        if (selectedGuard.id != 0) {  
            int stops = route.calculateStops(selectedGuard.energy);
            int listens = route.calculateListens(selectedGuard.energy);
            guards.updateGuard(selectedGuard.id, stops, day);
            std::cout << "Day " << day + 1 << ": Guard " << selectedGuard.id << " with " << stops << " stops and " << listens << " listens.\n";
        } else {
            std::cout << "Day " << day + 1 << ": No available guard.\n";
        }
    }

    input.close();
    return 0;
}
