#include <iostream>
#include <vector>
#include <algorithm>
#include "guards.h"
#include "patrol.h"

int main() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> brightness(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> brightness[i];
    }

    std::vector<int> energies(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> energies[i];
    }

    int d;
    std::cin >> d;
    std::vector<std::pair<int, int>> ranges(d);
    for (int i = 0; i < d; ++i) {
        std::cin >> ranges[i].first >> ranges[i].second;
    }

    for (int i = 0; i < d; ++i) {
        int guard = select_guard(energies, ranges[i].first, ranges[i].second);
        std::cout << "Day " << i + 1 << ": Guard " << guard << "\n";

        std::vector<int> stops = plan_patrol(brightness);
        std::cout << "Stops: ";
        for (int stop : stops) {
            std::cout << stop << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
