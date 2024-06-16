
/*
#include <fstream>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <string>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include "../include/route.h"
#include "../include/guards.h"


int main() {
    std::string filePath1 = "txt/p3_vacation1.txt";
    std::string filePath2 = "txt/p3_path1.txt";
    int y = 1;
    while(std::filesystem::exists(filePath1) && std::filesystem::exists(filePath2)){ //automated tests
        std::cout << "Test number: " << y <<std::endl;
        std::cout << std:: endl;
        int days, points, max_steps;
        std::ifstream input(filePath1); //file with guards' vacation days and maximum number of steps
        std::ifstream border(filePath2); //file with number of points and their brightness connected with borders from problem1
        if (!input.is_open()) {
            std::cerr << "Error opening input file." << std::endl;
            return 1;
        }
        if (!border.is_open()) {
            std::cerr << "Error opening input file." << std::endl;
            return 1;
        }
        border >> points; //reading number of points and their brightness
        std::vector<int> brightness(points);
        for (int i = 0; i < points; ++i) {
            border >> brightness[i];
        }

        input >> days >> max_steps; //reading number of dayd and maximum number of steps
        Route route(brightness, max_steps);
        //initializing maps for guards' energies and vacation days
        std::unordered_map<int, int> guardEnergy;
        std::unordered_map<int, std::vector<int>> guardVacations;
        int guardCount;
        input >> guardCount;
        //giving random numbers of energies
        srand(time(nullptr));
        for (int i = 0; i < guardCount; ++i) {
            int id = i + 1;
            int energy = rand() % 10 + 1;
            guardEnergy[id] = energy;
            std::cout << "Guard " << id << " initial energy: " << energy << std::endl; //writing guards' energy so we can se how it was randomised
        }
        std::cout << std:: endl;
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
        //first - number of stops
        //second - number of listens to the melody
        std::pair<int, int> pair;
        std::pair<int, int> bestPair;
        bestPair.first = INT_MAX;
        bestPair.second = INT_MAX;
        for (int day = 0; day < days; ++day) {
            auto selectedGuard = guards.selectGuard(day);
            if (selectedGuard.id != 0) {
                for (int j = 0; j < brightness.size(); j++) {
                    pair = route.calculateStops(j); //finding the best pair of stops & listens
                    if (bestPair.second >= pair.second) {
                        bestPair = pair;
                    }
                }

                guards.updateGuard(selectedGuard.id, bestPair.first, bestPair.second, day);
                std::cout << "Day " << day + 1 << ": Guard " << selectedGuard.id << std::endl;
            } else {
                std::cout << "Day " << day + 1 << ": No available guard.\n";
            }
        }
        std:: cout << "Guards' path goes with " << bestPair.first << " stops and " << bestPair.second << " listens to the melody.\n";
        y++;
        filePath1 = "txt/p3_vacation" + std::to_string(y) + ".txt";
        filePath2 = "txt/p3_path" + std::to_string(y) + ".txt";
        border.close();
        input.close();
    }
    return 0;
}
*/