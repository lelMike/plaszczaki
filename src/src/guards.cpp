#include "../include/guards.h"
#include <algorithm>

Guards::Guards(const std::unordered_map<int, int>& initialEnergies, const std::unordered_map<int, std::vector<int>>& vacations) //making priority queue that helps to pick guards with highest energy to out timetable
        : energyMap(initialEnergies), vacationMap(vacations) {
    for (const auto& entry : initialEnergies) {
        guardQueue.push({entry.first, entry.second});
        availableGuards.insert(entry.first);
    }
}

Guard Guards::selectGuard(int day) {
    std::priority_queue<Guard> tempQueue;
    Guard selectedGuard = {0, 0};

    for (auto it = restMap.begin(); it != restMap.end();) {
        if (it->second <= day) {
            availableGuards.insert(it->first);
            it = restMap.erase(it);
        } else {
            ++it;
        }
    }

    while (!guardQueue.empty()) {
        Guard topGuard = guardQueue.top();
        guardQueue.pop();

        if (availableGuards.find(topGuard.id) != availableGuards.end() &&
            std::find(vacationMap[topGuard.id].begin(), vacationMap[topGuard.id].end(), day + 1) == vacationMap[topGuard.id].end()) { //checking if guards is good to go, checking if he has vacation or 7-day break
            selectedGuard = topGuard;
            availableGuards.erase(topGuard.id);
            break;
        } else {
            tempQueue.push(topGuard);
        }
    }

    while (!tempQueue.empty()) {
        guardQueue.push(tempQueue.top());
        tempQueue.pop();
    }

    return selectedGuard;
}

void Guards::updateGuard(int id, int stops, int listens, int day) { //updating guard
    int newEnergy = energyMap[id] - stops;
    energyMap[id] = newEnergy > 0 ? newEnergy : 0;
    restMap[id] = day + 7;
    guardQueue.push({id, energyMap[id]});
}