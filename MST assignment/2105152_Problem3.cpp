#include<bits/stdc++.h>
using namespace std;

class Edge {
public:
    int a, b, w, index;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
    bool operator==(const Edge& other) const {
        return a == other.a && b == other.b && w == other.w;
    }
};

class Union{
    public:

    vector<int> parent;
    vector<int> level;
    Union(int n){
         parent.resize(n);
        level.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }



void initialize(int node) {
    parent[node] = node;
    level[node] = 1;
}

int findRoot(int node) {
    if (node == parent[node]){
        return node;
    }
    else{
    return parent[node] = findRoot(parent[node]);
    }
}

void merge(int a, int b) {
    a = findRoot(a);
    b = findRoot(b);
    if (a != b) {
        if (level[a] < level[b]){
           swap(a, b);
        }
        parent[b] = a;
        if (level[a] == level[b]) {
            level[a]++;
        }
    }
}
};

int mst(int n, vector<Edge>& edges,int removeVertice,int addVertice) {
    int totalWeight= 0;
    Union u(n);
    for (int i = 0; i < n; i++){
       u. initialize(i);
    }

    if (addVertice != -1) {
        u.merge(edges[addVertice].a, edges[addVertice].b);
        totalWeight += edges[addVertice].w;
    }

    for (Edge e : edges) {
        if (e.index != removeVertice && u.findRoot(e.a) !=u.findRoot(e.b)) {
            totalWeight += e.w;
            u.merge(e.a, e.b);
        }
    }

    for (int i = 0; i < n; i++) {
        if (u.findRoot(i) !=u.findRoot(0)) {
            return INT_MAX;
        }
    }


    return totalWeight;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].a >> edges[i].b >> edges[i].w;
        edges[i].index = i;
    }

    sort(edges.begin(), edges.end());

    int minWeight = mst(n, edges,-1,-1);
    vector<int> critical;
    vector<int>  pseudo;

    for (int i = 0; i < m; i++) {
        int weight1=mst(n, edges, i,-1);
        int weight2=mst(n, edges, -1,i);
        if (weight1 > minWeight) {
            critical.push_back(edges[i].index);
        } else if (weight2 == minWeight) {
            pseudo.push_back(edges[i].index);
        }
    }
   
    cout << "Critical edges: [ ";
    for (int i : critical)
        cout << i << " ";
    cout << "] " << endl;

    cout << "Pseudo critical edges: [ ";
    for (int i : pseudo)
        cout << i << " ";
    cout << "]" << endl;
    cout << "Weight of the minimum spanning tree: " << minWeight << endl;


    return 0;
}
