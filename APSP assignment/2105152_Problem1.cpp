#include<bits/stdc++.h>
using namespace std;

#define INF 1e9

int dist[100][100];

void floydWarshall(int n) {
    for(int k=1; k<=n; k++) {
        for(int i=1; i<=n; i++) {
            for(int j=1; j<=n; j++) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            if(i == j) {
                dist[i][j] =0;
              }else{ 
                dist[i][j]=INF;  
           }
        }
    }
    
    int u, v, w;
    for(int i=0; i<m; i++) {
        cin >> u >> v >> w;
        dist[u][v] = w;
        dist[v][u] = w;
    }
    int tCost;
    cin >> tCost;
    floydWarshall(n);
    vector<int> result;
    int minCity;
    for(int i=1; i<=n; i++) {
        int count = 0;
        for(int j=1; j<=n; j++) {
            if(dist[i][j] <= tCost){
                count++;
            }
        }
        if(count <= minCity) {
            minCity = count;
            result.push_back(i);
            }
    }
    for(int i: result) {
        cout <<i<< " ";
    }
    cout << endl;
    return 0;
}
