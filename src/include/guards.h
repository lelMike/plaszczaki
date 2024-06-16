#ifndef GUARDS_H
#define GUARDS_H

#include <unordered_map>
#include <queue>
#include <vector>
#include <set>

struct Guard { //structure that contains guards' id and energy that is random
    int id;
    int energy;

    bool operator<(const Guard& other) const {
        return energy < other.energy;
    }
};

class Guards {
public:
    Guards(const std::unordered_map<int, int>& initialEnergies, const std::unordered_map<int, std::vector<int>>& vacations);
    Guard selectGuard(int day);
    void updateGuard(int id, int stops, int listens, int day);

private:
    std::unordered_map<int, int> energyMap;
    std::unordered_map<int, std::vector<int>> vacationMap;
    std::priority_queue<Guard> guardQueue;
    std::unordered_map<int, int> restMap;
    std::set<int> availableGuards;
};

#endif