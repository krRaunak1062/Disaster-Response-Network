#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

class Graph {
public:
    int n;
    vector<vector<pair<int,int>>> adj;
    vector<vector<pair<int,int>>> roads;

    Graph() {
        n = 0;
    }

    Graph(int nodes) : n(nodes) {
        adj.resize(n+1);
        roads.resize(n+1); 
    }

    void addEdge(int u, int v, int w) {
        if (u <= 0 || v <= 0 || u > n || v > n) return;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        
        roads[u].push_back({v, w});
        roads[v].push_back({u, w});
    }

    void blockEdge(int u, int v) {
        for (auto &it : adj[u]) {
            if (it.first == v) it.second = 1e9;
        }
        for (auto &it : adj[v]) {
            if (it.first == u) it.second = 1e9;
        }
    }

    void removeBlock(int u, int v) {
        int origDist = -1;
        for (auto it : roads[u]) {
            if (it.first == v) { origDist = it.second; break; }
        }
        if (origDist != -1) {
            for (auto &it : adj[u]) if (it.first == v) it.second = origDist;
            for (auto &it : adj[v]) if (it.first == u) it.second = origDist;
        }
    }

    pair<vector<long long>, vector<int>> dijkstra(int src) const {
        const long long INF = 1e9;
        vector<long long> dist(n+1, INF);
        vector<int> parent(n+1, -1);
        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;

        dist[src] = 0;
        pq.push({0, src});

        while(!pq.empty()) {
            auto p = pq.top(); pq.pop();
            long long d = p.first;
            int u = p.second;

            if (d != dist[u]) continue;

            for (auto it : adj[u]) {
                int v = it.first;
                int w = it.second;

                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        return {dist, parent};
    }

    static vector<int> reconstructPath(int from, int src, const vector<int> &parent) {
        vector<int> path;
        for (int cur = from; cur != -1; cur = parent[cur]) {
            path.push_back(cur);
            if (cur == src) break;
        }

        if (path.empty() || path.back() != src) return {};
        return path;
    }

    static void printPath(const vector<int> &path) {
        if (path.empty()) {
            cout << "No path available\n";
            return;
        }

        cout << "Path: ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i+1 < path.size()) cout << " -> ";
        }
        cout << "\n";
    }

    bool reachableBFS(int s, int t) const {
        if (s == t) return true;
        vector<bool> vis(n+1, false);
        queue<int> q;
        q.push(s); vis[s] = true;

        while(!q.empty()) {
            int u = q.front(); q.pop();
            for (auto it : adj[u]) {
                int v = it.first;
                if (!vis[v]) {
                    vis[v] = true;
                    if (v == t) return true;
                    q.push(v);
                }
            }
        }
        return false;
    }
};

#endif
