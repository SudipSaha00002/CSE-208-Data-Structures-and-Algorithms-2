#include <iostream>
#include <vector>
#include <cmath>
#include<bits/stdc++.h>

using namespace std;

class person{
    public:
    int height;
    int age;
    int divorc;
};

bool marry(person p1,person p2) {
    int heightD = abs(p1.height - p2.height);
    int ageD = abs(p1.age - p2.age);
    bool divMatch = (p1.divorc == p2.divorc);

    return (heightD <= 10) && (ageD <= 5) && divMatch;
}

int find(vector<person>& man , vector<person>& woman) {
    int count = 0;
    for (auto& i :man) {
        for (auto& j: woman) {
            if (marry(i,j)) {
                count++;
                break;
            }
        }
    }

    return count;
}

int main() {
    int m, n;
    cin >> m >> n;

    vector<person> man(m);
    vector<person> woman(n);

    for (auto& M: man) {
        cin >>M.height >>M.age >>M.divorc;
    }

    for (auto& W: woman) {
        cin >> W.height >>W.age >> W.divorc;
    }

    int canMarry = find(man,woman);

    cout << canMarry << endl;

    return 0;
}
