#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

class Item {
public:
    int value;
    int weight;
    int index;
};

bool compare(Item a, Item b) {
    if ((double)a.value / a.weight == (double)b.value / b.weight) {
        return a.index < b.index;
    }
    return (double)a.value / a.weight > (double)b.value / b.weight;
}

void knapsack(int W, vector<Item>& items, vector<vector<double>>& dp) {
    int n = items.size();

    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= W; ++w) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (items[i - 1].weight <= w) {
                dp[i][w] = max(dp[i - 1][w], items[i - 1].value + dp[i - 1][w - items[i - 1].weight]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
}

vector<int> fptas(int W, vector<Item>& items, double epsilon,vector<vector<double>>& dp, ostream& print ) {
    int n = items.size();
    sort(items.begin(), items.end(), compare);
       knapsack(W, items, dp);

         int originalInstance=dp[n][W];

    long double maxValue = 0;
    for (int i = 0; i < n; ++i) {
        maxValue = max(maxValue, (long double)(items[i].value));
    }

    long double t = epsilon * maxValue / (2 * n);
    print << "Theta : " <<setprecision(17)<< t << endl;

    vector<Item> reducedItems = items;

    for (int i = 0; i < n; i++) {
        reducedItems[i].value = ceil(reducedItems[i].value / t);
    }
    
    knapsack(W, reducedItems, dp);

    long double totalW_reduced = W;
    vector<int> reducedIndices;
    long double i = n;

    while (i > 0 && totalW_reduced > 0) {
        if (dp[i][totalW_reduced] != dp[i - 1][totalW_reduced]) {
            reducedIndices.push_back(reducedItems[i - 1].index);
            totalW_reduced -= reducedItems[i - 1].weight;
        }
        --i;
    }
    sort(reducedIndices.begin(), reducedIndices.end());
            double reduceInstance= dp[n][W]+2;
            print << "Answer of the reduced instance: " << reduceInstance << endl;
            print << "Answer of reduced instance multiplied by theta: " <<(double)( reduceInstance * t) << endl;
            print << "Indices: "; 
            for (int  i = reducedIndices.size()-1; i >=0; i--)
            print << reducedIndices[i] + 1 << " ";
            print << endl;

       long double totalValue = 0;
        for (int idx : reducedIndices) {
            for(auto i : items){
                if(i.index==idx){
                    totalValue += i.value; 
                }
            }
        }

            print << "Answer of original instance (rounded up): " << totalValue << endl;
            print << "Used Weight: " << W - totalW_reduced<< endl;
            print << "Ratio: "<<(double) originalInstance/totalValue<<endl;

    return reducedIndices;
}

int main() {

    ifstream input("in.txt");
    ofstream output("output.txt");

    int n, W;
    input >> n >> W;

    vector<Item> items(n);

    for (int i = 0; i < n; ++i) {
        input >> items[i].value >> items[i].weight;
        items[i].index = i;
    }
    sort(items.begin(), items.end(), compare);
    vector<vector<double>> dp(n + 1, vector<double>(W + 1, 0));

    knapsack(W, items, dp);


         int originalInstance=dp[n][W];

         output<<"Original Instance: "<<endl;
    output<<"Answer: "<<originalInstance<<endl;

    int totalW = W;
    vector<int> indices;
    int i = n;
    while (i > 0 && totalW > 0) {
        if (dp[i][totalW] != dp[i - 1][totalW]) {
            indices.push_back(items[i - 1].index);
            totalW -= items[i - 1].weight;
        }
        --i;
    }
    output<<"Used Weight: "<<W-totalW<<endl;
    

    sort(indices.begin(), indices.end());

    output << "Indices : ";
    for (int  i = indices.size()-1; i >=0; i--)
    output << indices[i] + 1 << " ";
    output << endl;

    vector<double>epsilons;
   epsilons.push_back(0.5);
   epsilons.push_back(0.2);
   epsilons.push_back(0.1);
   epsilons.push_back(0.05);
    for (double eps : epsilons) {
        output<< "-------------------------------------" << endl;
        output << "Rounded Instance with Eps: " << setprecision(3) << (double)eps << endl;

        vector<int> indices = fptas(W, items, eps,dp,output);
    }

    return 0;
}

