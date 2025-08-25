#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<vector<int>> maxNeed, allocation, need;
vector<int> available;

bool isSafe(vector<int>& safeSequence) {
    vector<int> work = available;
    vector<bool> finish(n, false);
    int count = 0;

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSequence.push_back(i);
                    finish[i] = true;
                    count++;
                    found = true;
                }
            }
        }
        if (!found) return false;
    }
    return true;
}

bool requestResources(int process, vector<int>& request) {
    // Step 1: check if request <= need
    for (int j = 0; j < m; j++) {
        if (request[j] > need[process][j]) {
            cout << "Error: Process requested more than its maximum need!\n";
            return false;
        }
    }

    // Step 2: check if request <= available
    for (int j = 0; j < m; j++) {
        if (request[j] > available[j]) {
            cout << "Process must wait: resources not available.\n";
            return false;
        }
    }

    // Step 3: Pretend allocation
    for (int j = 0; j < m; j++) {
        available[j] -= request[j];
        allocation[process][j] += request[j];
        need[process][j] -= request[j];
    }

    // Step 4: Safety check
    vector<int> safeSequence;
    if (isSafe(safeSequence)) {
        cout << "Request can be granted. Safe sequence: ";
        for (int i = 0; i < safeSequence.size(); i++) {
            cout << "P" << safeSequence[i];
            if (i != safeSequence.size() - 1) cout << " -> ";
        }
        cout << "\n";
        return true;
    } else {
        // rollback
        for (int j = 0; j < m; j++) {
            available[j] += request[j];
            allocation[process][j] -= request[j];
            need[process][j] += request[j];
        }
        cout << "Request cannot be granted: System would be unsafe.\n";
        return false;
    }
}

int main() {
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resources: ";
    cin >> m;

    allocation.assign(n, vector<int>(m));
    maxNeed.assign(n, vector<int>(m));
    need.assign(n, vector<int>(m));
    available.assign(m, 0);

    cout << "\nEnter Allocation Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> allocation[i][j];

    cout << "\nEnter Max Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            cin >> maxNeed[i][j];
            need[i][j] = maxNeed[i][j] - allocation[i][j];
        }

    cout << "\nEnter Available Resources:\n";
    for (int j = 0; j < m; j++) cin >> available[j];

    while (true) {
        int process;
        cout << "\nEnter process number making a request (-1 to exit): ";
        cin >> process;
        if (process == -1) break;

        vector<int> request(m);
        cout << "Enter request vector: ";
        for (int j = 0; j < m; j++) cin >> request[j];

        requestResources(process, request);
    }

    return 0;
}
