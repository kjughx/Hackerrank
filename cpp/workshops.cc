#include <algorithm>
#include <bits/stdc++.h>
#include <climits>
#include <vector>

using namespace std;

struct Workshop {
    int start_time, end_time;
    Workshop(int start_time, int end_time) : start_time(start_time), end_time(end_time) {}
};

typedef struct _Available_Workshops {
    int n;
    std::vector<Workshop> workshops;
} Available_Workshops;

Available_Workshops* initialize(int start_time[], int duration[], int n) {
    auto available_workshops = new Available_Workshops;
    std::vector<Workshop> tmp;
    int start = -1;

    available_workshops->n = n;
    for (int i = 0; i < n; ++i) {
        tmp.push_back(Workshop(start_time[i], start_time[i] + duration[i]));
    }

    // Sort them by end_times, then we'll filter out those that start at the same time but take
    // longer
    std::sort(tmp.begin(), tmp.end(),
              [](Workshop& a, Workshop& b) { return a.end_time < b.end_time; });

    // No need to keep workshops which start at the same time but take longer
    for (auto& w : tmp) {
        if (w.start_time != start) {
            available_workshops->workshops.push_back(w);
            start = w.start_time;
        }
    }

    return available_workshops;
}

int CalculateMaxWorkshops(Available_Workshops* available_workshops) {
    int maxworkshops = 0;
    std::vector<Workshop>& workshops = available_workshops->workshops;
    std::set<int> attended;

    for (int i = 0; i < workshops.size(); ++i) {
        // Then we've already seen this start_time before and since the list is sorted
        // we have less previously attended workshops so no need to continue checking
        if (attended.find(workshops[i].start_time) != attended.end()) {
            continue;
        }

        // Attend the first one
        int workshop_count = 1;
        int end_time = workshops[i].end_time;
        attended.insert(workshops[i].start_time);

        for (int j = i + 1; j < workshops.size(); ++j) {
            // If it start when the current one ends or later then attend it
            if (workshops[j].start_time >= end_time) {
                workshop_count++;
                end_time = workshops[j].end_time;
            }
        }

        maxworkshops = max(maxworkshops, workshop_count);
    }

    return maxworkshops;
}

int main() {
    int n; // number of workshops
    cin >> n;

    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> start_time[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> duration[i];
    }

    Available_Workshops* ptr;
    ptr = initialize(start_time, duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}
