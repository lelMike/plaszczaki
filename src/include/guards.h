#ifndef GUARDS_H
#define GUARDS_H

#include <vector>

// struct that is representing a guard
struct Guard {
    int energy;         // guard's energy
    char availability;  // 'W' for work, 'F' for free
    int index;          // guard's index
};

Guard selectGuard(const std::vector<Guard>& guards, const std::vector<bool>& available); // function to select the guard with the highest energy who is available to work

#endif