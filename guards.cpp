#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Guard {
    int energy;
    int index;
};

Guard selectGuard(const vector<Guard>& guards, int start, int end) {
    Guard maxGuard = guards[start];
    for (int i = start + 1; i <= end; ++i) {
        if (guards[i].energy > maxGuard.energy) {
            maxGuard = guards[i];
        }
    }
    return maxGuard;
}

int calculateMinRestPoints(const vector<int>& brightness, int max_steps) { //tu potrzebny lepszy algorytm
    int n = brightness.size();
    int restPoints = 0;
    int current = 0;

    while (current < n) {
        int next = current + 1;
        while (next < n && next - current <= max_steps && brightness[next] > brightness[current]) {
            ++next;
        }
        if (next == n || brightness[next] <= brightness[current]) {
            ++restPoints;
            current = next;
        } else {
            current = next - 1;
        }
    }

    return restPoints;
}

int main() {
    int n, m, k, max_steps;
    cin >> n >> m >> k >> max_steps;

    vector<int> brightness(n);
    for (int i = 0; i < n; ++i) {
        cin >> brightness[i];
    }

    vector<Guard> guards(m);
    for (int i = 0; i < m; ++i) {
        cin >> guards[i].energy;
        guards[i].index = i + 1;
    }

    int day = 0;
    int start = 0;
    int end = m - 1;

    while (day < k) {
        Guard guard = selectGuard(guards, start, end);
        cout << "Day " << day + 1 << ": Guard " << guard.index << " with energy " << guard.energy << endl;

        int restPoints = calculateMinRestPoints(brightness, max_steps);
        cout << "Minimum rest points: " << restPoints << endl;

        guards[guard.index - 1].energy = INT_MIN; // This guard needs to rest for a week
        start = (start + 1) % m;
        end = (end + 1) % m;
        ++day;
    }

    return 0;
}
