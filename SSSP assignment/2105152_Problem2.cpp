#include<bits/stdc++.h>

using namespace std;


class Edge {
    public :
    int u, v, w;
};

vector<Edge> edges;
int dist[100];

int BellmanFord(int N, int S) {
    Edge edge;

    for (int i = 0; i <= N; ++i) {
        dist[i] = INT_MAX;
    }

    dist[S] = 0;

    bool relax;

    for (int i = 0; i < N - 1; ++i) {
        relax = false;

        for (auto& e :edges) {
            if (dist[e.u] != INT_MAX && dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
                relax = true;
            }
        }

        if (!relax) {
            break; 
        }
    }

    for (auto& e : edges) {
        if (dist[e.u] != INT_MAX && dist[e.u] + e.w < dist[e.v]) {
            return -1; 
        }
    }
   return 0; 
}




int main() {
    int N, M, A, B, L, H, S, D;
    cin >> N >> M;
    Edge edge;
   
    for (int i = 0; i < M; ++i) {
        cin >> edge.u >> edge.v >> edge.w;
        edges.push_back(edge);
    }
    cin >> A >> B >> L >> H >> S >> D;


    if( BellmanFord(N, S)==0){ 
    int start = dist[D];
     int minDist= start;
    int weight;
    for (int i= L; i <= H; i++) {
        Edge new_edge = {A, B, i};
        edges.push_back(new_edge); 
        if (BellmanFord(N, S)==0) { 
            if (dist[D] < minDist) {
                minDist = dist[D];
                weight = i;
            }
        }
        edges.pop_back(); 
    }

    if (minDist < start) {
        cout <<weight << " " << minDist << endl;
    } else {
        cout << "impossible" << endl;
    }
    }

    return 0;
}
