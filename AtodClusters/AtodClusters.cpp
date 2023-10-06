#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Data structure to represent a disjoint set
struct DisjointSet {
    vector<int> parent;
    vector<int> rank;

    DisjointSet(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1);

        // Initialize each element as a separate set
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    // Find the root of the set containing the element
    int find(int x) {
        if (x != parent[x]) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // Union two sets by rank
    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) {
            return;
        }

        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        }
        else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        }
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
};

int main() {
    int N, M;
    cin >> N >> M;

    DisjointSet ds(N);

    // Process the magical connections
    for (int i = 0; i < M; i++) {
        int Ai, Bi;
        cin >> Ai >> Bi;
        ds.unionSets(Ai, Bi);
    }

    // Count the number of Atod Clusters
    vector<int> clusterSizes(N + 1, 0);
    int numClusters = 0;

    for (int i = 1; i <= N; i++) {
        int root = ds.find(i);
        clusterSizes[root]++;

        if (root == i) {
            numClusters++;
        }
    }

    // Sort the cluster sizes in non-descending order
    sort(clusterSizes.begin(), clusterSizes.end());

    // Output the results
    cout << numClusters << endl;
    for (int i = 1; i <= N; i++) {
        if (clusterSizes[i] > 0) {
            cout << clusterSizes[i] << endl;
        }
    }

    return 0;
}