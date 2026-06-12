#include<bits/stdc++.h>

using namespace std;

class Edge{
    public: 
    int u,v,capacity,flow;
};


void updatePath(vector<int>& parent,vector<vector<int>>& residual,vector<Edge>& edge, int s, int t, int newMin) {
     int u = t;
    while (u != s) {
     int v = parent[u];
        residual[v][u] -= newMin;
        residual[u][v] += newMin;
        for (Edge& e : edge) {
        if (e.u == v && e.v == u) {
            e.flow +=newMin;
            break;
        }
    }
        u = v;
    }
}

int fordFulkerson(vector<vector<int>>& graph, vector<Edge>& edge, int s, int t,vector<vector<int>>& residual) {
    int n = graph.size();

    for (Edge& e : edge) {
        residual[e.u][e.v] = e.capacity;
    }

    int maxFlow = 0;

    while (true) {
       vector<int> parent(n); 
        for (int i = 0; i < n; ++i) {
        parent[i] = -1;
        }
        queue<pair<int, int>> q; 

        parent[s] = s;
        q.push({s, INT_MAX});

        while (!q.empty()) {
            int curr = q.front().first;
            int minC = q.front().second;
            q.pop();

            for (int i : graph[curr]) {
                if (parent[i] == -1 && residual[curr][i] > 0) {
                    parent[i] = curr;
                    int newMin = min(minC, residual[curr][i]);
                    q.push({i, newMin});

                    if (i == t) {
                        maxFlow += newMin;
                        updatePath(parent,residual,edge,s,t,newMin);
                    }
                }
            }
        }
        if (parent[t] == -1) {
            break;
        }
    }
    return maxFlow;
}


void printSet(vector<bool>& visited, bool val) {
    bool top = true;
    for (int i = 1; i <= visited.size()-1; i++) {
        if (visited[i] == val) {
            if (!top) {
                cout << ", ";
            }
                cout << i;
            top = false;
        }
    }
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> graph(N + 1);
    vector<Edge> edge;

    for (int i = 0; i < M; i++) {
        int u, v, c;
        cin >> u >> v >> c;

        graph[u].push_back(v);
        graph[v].push_back(u);  

        edge.push_back({u, v, c, 0});
    }

    int s, t;
    cin >> s >> t;

    vector<vector<int>> residual(N + 1);
      for (int i = 0; i <= N; ++i) {
         residual[i].resize(N + 1, 0);  
      }

    int maxFlow = fordFulkerson(graph,edge,s,t,residual);
    int node;
    int currMaxFlow = 0;

    for (int i = 1; i <= N; i++) {
        if (i == s || i == t) {
        continue;
        }
        int outflow = 0;
        for (Edge& e : edge) {
            if (e.u == i) {
                outflow += e.flow;
            }
        }  

        int inflow=0;     
        for(Edge& e : edge){    
              if(e.v == i){
                inflow += e.flow;
            }
        }

        if(currMaxFlow < min(inflow, outflow)) {
            currMaxFlow = min(inflow, outflow);
            node = i;
        }
    }
    cout << node <<" "<< currMaxFlow << endl;

    vector<bool> visited(N+1);
    for(int i=0;i<N;i++){
        visited[i]=false;
    }

    queue<int> q;
    q.push(s);
    visited[s] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : graph[u]) {
            if (!visited[v] && residual[u][v] > 0) {
                q.push(v);
                visited[v] = true;
            }
        }
    }
    cout << "[ {";
    printSet(visited, true);
    cout << "}, {";
    printSet(visited, false);
    cout << "} ]" << endl;

    cout << maxFlow << endl;
    return 0;
}
