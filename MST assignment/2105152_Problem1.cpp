#include <bits/stdc++.h>
using namespace std;

class Edge
{
public:
    int a,b,w;
    int miniIndex;
    bool operator<( Edge& other)const {
        if (a != other.a) return a < other.a;
        if (b != other.b) return b < other.b;
        return w < other.w;
    }

    bool operator==(const Edge& other)const{
        return a == other.a && b == other.b && w == other.w;
    }
};
class MSTorder
{
public:
    vector<Edge> edges;
    int MSTweight;

    bool operator==(const MSTorder& other) {
        return edges == other.edges && MSTweight == other.MSTweight;
    }
};

vector<MSTorder> Weight;

void findMST(vector<vector<int>> graph, int n, vector<bool> visited, vector<int> weight, vector<int> parent, int index);

void MST(vector<vector<int>> graph, int n, vector<bool> visited, vector<int> weight, vector<int> parent)
{
    bool k = true;
    for (int i = 0; i < n; i++){
        k &= visited[i];
    }
    if (k){
        MSTorder order;
        order.MSTweight = 0;
        for (int i = 1; i < n; i++)
        {
            Edge edge;
            edge.a = parent[i];
            edge.b = i;
            edge.w = weight[i];
            order.edges.push_back(edge);
            order.MSTweight += weight[i];
        }

    if (find(Weight.begin(), Weight.end(), order) == Weight.end()){
            Weight.push_back(order);
        }
        return;
    }
    int minindex;
    int minWeight =minindex;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && minWeight > weight[i]) {
            minWeight = weight[i];
            minindex = i;
        }
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i] && minWeight == weight[i]) {
            findMST(graph, n, visited, weight, parent, i);
        }
    }
}


void findMST(vector<vector<int>> graph, int n, vector<bool> visited, vector<int> weight, vector<int> parent, int minindex){
    int a = minindex;
    visited[a] = true;
    for (int b = 0; b < n; b++)
    {
        if (graph[a][b] && !visited[b] && weight[b] > graph[a][b])
        {
            weight[b] = graph[a][b];
            parent[b] = a;
        }
    }
    MST(graph, n,visited, weight, parent);
    visited[a] = false; 
    weight[a] = INT_MAX;
}


bool compare( MSTorder a, MSTorder b){
    return a.MSTweight < b.MSTweight;
}


void printEdge(const Edge& edge) {
    cout << " [" << edge.a << ", " << edge.b << ", " << edge.w << "] ";
}

void printMST(){
    sort(Weight.begin(),Weight.end(), compare);
    int minWeight = Weight[0].MSTweight;
    int count = 0;
     cout << "MSTs:" << endl;
    for (auto i : Weight){
        if (i.MSTweight == minWeight){
            cout << ++count << " : [";
            for (auto j : i.edges){
                printEdge(j);  
            }
            cout << "]" << endl;
        }else{
            return;
        }
    }
}



int main(){
    int n, m;
    cin >> n >> m;
    int a, b, w;
    vector<vector<int>> graph(n, vector<int>(n));
    for (int i = 0; i < m; i++){
        cin >> a >> b >> w;
        graph[a][b] = w;
        graph[b][a] = w;
    }
    vector<int> parent(n);
    vector<bool>visited(n);
    vector<int> weight(n, INT_MAX);
    weight[0] = 0;
    MST(graph, n,visited, weight, parent);

    printMST();
}
