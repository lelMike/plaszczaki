#include "guards.h"

int select_guard(const std::vector<int>& energies, int start, int end) {
    int max_energy = -1;
    int selected_guard = -1;
    for (int i = start; i <= end; ++i) {
        if (energies[i] > max_energy) {
            max_energy = energies[i];
            selected_guard = i;
        }
    }
    return selected_guard;
}
