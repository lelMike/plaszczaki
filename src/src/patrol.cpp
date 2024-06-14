#include "../include/patrol.h"

int calculateMinRestPoints(const std::vector<int>& brightness, int max_steps) { // function to calculate the minimum number of rest points
    int n = brightness.size(); // numbers of points
    int restPoints = 0;
    int current = 0;

    while (current < n) {
        int next = current + 1; // initializing the next point
        while (next < n && next - current <= max_steps && brightness[next] > brightness[current]) {
            ++next; // Here I'm moving to the next point within the max steps limit
        }
        if (next == n || brightness[next] <= brightness[current]) {
            ++restPoints;
            current = next;
        } else {
            current = next - 1; // adjusting current position
        }
    }

    return restPoints;
}