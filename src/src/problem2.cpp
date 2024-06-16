// #include <iostream>
// #include <vector>
// #include <cstdlib>
// #include <ctime>
// #include "../include/guards.h"
// #include "../include/patrol.h"
//
// using namespace std;
//
// int main() {
//     int n, m, k, max_steps; // n goes for number of points, m goes for number of guards, k goes for number of days
//     cin >> n >> m >> k >> max_steps;
//
//     vector<int> brightness(n);   // reading brightness of the points
//     for (int i = 0; i < n; ++i) {
//         cin >> brightness[i];
//     }
//     srand(time(nullptr)); // initialisation of random energy
//
//     vector<Guard> guards(m); // checking guards' availability and energy
//     for (int i = 0; i < m; ++i) {
//         guards[i].energy = rand() % 11;
//         cin >> guards[i].availability;
//         guards[i].index = i + 1;
//     }
//
//     vector<bool> available(m, true); // tracking the availability
//     vector<int> lastPatrol(m, -1);
//
//     for (int day = 0; day < k; ++day) { //assigning guards for work
//         for (int i = 0; i < m; ++i) {
//             if (lastPatrol[i] != -1 && day - lastPatrol[i] < 7) {
//                 available[i] = false; // because guard must rest for a week after patrolling
//             } else {
//                 available[i] = true;
//             }
//         }
//
//         Guard guard = selectGuard(guards, available);  // selecting the guard with the highest energy who is available
//         cout << "Day " << day + 1 << ": Guard " << guard.index << " with energy " << guard.energy << endl;
//
//         int restPoints = calculateMinRestPoints(brightness, max_steps); // this step is to calculate the minimum number of rest points for the selected guard
//         cout << "Minimum rest points: " << restPoints << endl;
//
//         lastPatrol[guard.index - 1] = day; //updating the last patrol day for the selected guard
//     }
//
//     return 0;
// }
// //computational complexity: O(k⋅(m+n))