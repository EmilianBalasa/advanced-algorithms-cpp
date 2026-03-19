#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stack>
#include <algorithm>
#include <functional>
using namespace std;

void generateCombinations(int n, int k, string current, vector<string>& nodes) {
    if ((int)current.size() == n-1) {
        nodes.push_back(current);
        return;
    }
    for (int d = 0; d < k; ++d)
        generateCombinations(n, k, current + char('0' + d), nodes);
}

int main() {
    int n, k;
    cout << "Enter n and k: ";
    cin >> n >> k;
    if (n < 1 || k < 1) {
        cout << "Invalid input\n";
        return 1;
    }

    vector<string> nodes;
    generateCombinations(n, k, "", nodes);

    unordered_map<string, vector<string>> adj;
    for (const string& s : nodes) {
        for (int d = 0; d < k; ++d) {
            string next = s.substr(1) + char('0' + d);
            adj[s].push_back(next);
        }
    }

    stack<string> st;
    string start = string(n-1, '0');
    st.push(start);
    string path;
    unordered_map<string, int> outEdgeUsed;
    for (const auto& p : adj)
        outEdgeUsed[p.first] = 0;

    while (!st.empty()) {
        string u = st.top();
        if (outEdgeUsed[u] < (int)adj[u].size()) {
            string v = adj[u][outEdgeUsed[u]++];
            st.push(v);
        } else {
            path += u.back(); // Only the last character
            st.pop();
        }
    }
    reverse(path.begin(), path.end());

    string result = start.substr(0, n-1) + path;

    cout << "Shortest universal sequence: " << result << "\n";
    cin.get(); cin.get(); // Wait for user to press Enter
    return 0;
}