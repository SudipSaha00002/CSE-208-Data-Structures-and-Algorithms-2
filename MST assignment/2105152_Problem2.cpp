#include <bits/stdc++.h>
using namespace std;

class Edge {
public:
    int a,b,w;
};

int find(int b, vector<int> &parent, vector<int> &level) {
    if (parent[b] != b) {
        parent[b] = find(parent[b], parent, level);
    }
    return parent[b];
}


void pathCompression(int node, int root, vector<int> &parent) {
    while (node != root) {
        int next = parent[node];
        parent[node] = root;
        node = next;
    }
}

void  Union(int a, int b, vector<int> &parent, vector<int> &level, vector<bool> &visited) {
    int U = find(a, parent, level);
    int V = find(b, parent, level);
    if (U != V) {
        if (level[U] >level[V]) {
            parent[V] =U;
            level[U]++;
        } else {
            parent[U] =V;
            level[V]++;
        }
        pathCompression(a,U, parent);
        pathCompression(b,V, parent);
        
        visited[a] = visited[b] = true;
    
    }
}


bool compare(Edge a, Edge b) {
    return a.w < b.w;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].a >> edges[i].b >> edges[i].w;
    }

    vector<Edge> Order(edges);

    sort(edges.begin(), edges.end(), compare);

    vector<int> parent(n + 1);
    for (int i = 0; i <= n; i++){
        parent[i] = i;
    }


    vector<int> level(n + 1, 0);

    vector<int> output(m);
    vector<bool> visited(n + 1);


    Union(edges[0].a, edges[0].b, parent,level, visited);

    int possible_edges = 0;
    for (int i = 1; i < m; i++) {
    if (possible_edges == n - 1) {
        output[i] = 2;
        continue;
    }

    int U = find(edges[i].a, parent, level);
    int V = find(edges[i].b, parent, level);

if (U !=V) {
    Union(edges[i].a, edges[i].b, parent, level, visited);
    output[i] = 0;
} else if (edges[i].w == edges[i - 1].w) {
    output[i] = 1;
    int j = i - 1;
    while (edges[j].w == edges[i].w) {
        output[j--] = 1;
    }
} else {
    output[i] = 2;
}

}

    vector<int> indexMap(m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (edges[i].a==Order[j].a && edges[i].b ==Order[j].b) {
                indexMap[j] = i;
                break;
            }
        }
    }
    for (int i = 0; i < m; i++) {
        int Index = indexMap[i];
        int val = output[Index];

       if(val==0){
        cout<<"any"<<endl;
       }else if(val==1){
        cout<<"at least one"<<endl;
       }
       else{
        cout<<"none"<<endl;
       }
    }

    return 0;
}
