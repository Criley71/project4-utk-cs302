// dijsktras.cpp
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <random>
#include <ctime>
using namespace std;
// Main Execution

int main(int argc, char *argv[]) {
    srand(time(nullptr));
    int randomWeight;
    int rows = 10, col = 10;
    vector<int> grid(100, 0);
    vector<bool> visited(100, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> tileWeightpq;
    //priority_queue<pair<weight, index>, vector<pair<weight, index>>, greater<pair<weight, int>>> tileWeightpq;
    for(int i = 0; i < grid.size(); i++){
        grid[i] = i;
    }

    for(int i = 0; i < grid.size(); i++){
        if(i < 10){
            if(i % 10 == 9){
                cout << "0" << grid[i] << " |\n";
            }
            else
                cout << "0" << grid[i] << " | ";
        }
        else if(i % 10 != 9)
            cout << grid[i] << " | ";
        else    
            cout << grid[i] << " | \n";
    }

    for(int i = 0; i < grid.size(); i++){
        randomWeight = (rand() % 8) + 1;
        tileWeightpq.push(make_pair(randomWeight, i));

        if(i % 10 != 9){
            cout << randomWeight << " | ";
        }else{
            cout << randomWeight << " | " << "\n";
        }
    }

    for(int i = 0; i < grid.size(); i++){
        cout << "index: " << tileWeightpq.top().second << " weight: " << tileWeightpq.top().first << "\n";
        tileWeightpq.pop();
    }
    return 0;
}

