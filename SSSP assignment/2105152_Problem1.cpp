#include <bits/stdc++.h>

using namespace std;

class Point{
    public:
    int city,gas, cost;

    bool operator>(const Point& other) const {
         return cost > other.cost;
    }
};

vector<pair<int, int>> adj[100];
int cost[100][100];
int gasPrice[100];

void dijkstra(int N, int C, int S, int D) {

    priority_queue<Point, vector<Point>, greater<Point>> pq;
    pq.push({S, 0, 0});
    cost[S][0] = 0;

    while (!pq.empty()) {
        Point p = pq.top();
        pq.pop();

        if (p.city == D) {
            cout << p.cost << endl;
            return;
        }

        if (p.cost > cost[p.city][p.gas]) {
            continue;
        }

        
        for (int i = p.gas + 1; i <= C; i++) {
            int newCost = p.cost + (i - p.gas) * gasPrice[p.city];
            if (newCost < cost[p.city][i]) {
                cost[p.city][i] = newCost;
                pq.push({p.city, i, newCost});
            }
        }

        for (auto &edge : adj[p.city]) {
            int newCity = edge.first;
            int dist = edge.second;
            if (p.gas >= dist && p.cost < cost[newCity][p.gas - dist]) {
                cost[newCity][p.gas - dist] = p.cost;
                pq.push({newCity, p.gas - dist, p.cost});
            }
        }
    }

    cout << "impossible" << endl;
}

int main() {
    int N, M, C, S, D;
    cin >> N >> M >> C;

    for (int i = 1; i <= N; ++i) {
        cin >> gasPrice[i];
    }

    int u, v, d;
    for (int i = 0; i < M; ++i) {
        
        cin >> u >> v >> d;
        adj[u].push_back({v, d});
        adj[v].push_back({u, d});
    }
    cin >> S >> D;

    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j <= C; ++j) {
            cost[i][j] = INT_MAX;
        }
    }

    dijkstra(N, C, S, D);
    return 0;
}
