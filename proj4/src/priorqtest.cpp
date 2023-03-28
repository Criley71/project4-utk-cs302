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
    int r = 10, c = 10;
    vector<int> grid(100, 0);
    vector<bool> visited(100, false);
    vector<pair<int, int>> indexWieghtPairs(100);
    vector<pair<int, priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>>> indexWithPrioq(100);
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
    cout << "\n";
    cout << "\n";
    cout << "_________________________________________________\n";
    for(int i = 0; i < grid.size(); i++){
        randomWeight = (rand() % 8) + 1;
        tileWeightpq.push(make_pair(i, randomWeight));
        indexWieghtPairs[i].first = i;
        indexWieghtPairs[i].second = randomWeight;
        if(i % 10 != 9){
            cout << "0" << randomWeight << " | ";
        }else{
            cout << "0" << randomWeight << " | " << "\n";
        }

    }

    for(int i = 0; i < r * c; i++){
        indexWithPrioq[i].first = i;
        if(i == 0){ //top left/ zero case
            indexWithPrioq[i].second.push(make_pair(indexWieghtPairs[i+1].second, indexWieghtPairs[i + 1].first));
            indexWithPrioq[i].second.push(make_pair(indexWieghtPairs[i+c].second, indexWieghtPairs[i + c].first));

        }else if((i % c != c - 1) && (i % c != 0) && ((i + c) < (r * c)) && (i < c)){ //top middle case
            indexWithPrioq[i].second.push(make_pair(indexWieghtPairs[i+1].second, indexWieghtPairs[i + 1].first));
            indexWithPrioq[i].second.push(make_pair(indexWieghtPairs[i-1].second, indexWieghtPairs[i - 1].first));
            indexWithPrioq[i].second.push(make_pair(indexWieghtPairs[i+c].second, indexWieghtPairs[i + c].first));

        }else if((i % c != c - 1) && (i % c == c - 1) && ((i + c) < (r * c)) && (i < c)){ //top right case
            indexWithPrioq[i].second.push(make_pair(indexWieghtPairs[i-1].second, indexWieghtPairs[i - 1].first));
            indexWithPrioq[i].second.push(make_pair(indexWieghtPairs[i+c].second, indexWieghtPairs[i + c].first));

        }else if((i % c == 0) && ((i + c) < (r * c)) && (i >= c)){//middle left cases
            indexWithPrioq[i].second.push(make_pair(indexWieghtPairs[i+1].second, indexWieghtPairs[i + 1].first));
            indexWithPrioq[i].second.push(make_pair(indexWieghtPairs[i+c].second, indexWieghtPairs[i + c].first));
            indexWithPrioq[i].second.push(make_pair(indexWieghtPairs[i-c].second, indexWieghtPairs[i - c].first));   

        }else if((i % c != c - 1) && (i % c != 0) && ((i + c) < (r * c)) && i >= c){ //middle cases
            indexWithPrioq[i].second.push(make_pair(indexWieghtPairs[i+1].second, indexWieghtPairs[i + 1].first));
            indexWithPrioq[i].second.push(make_pair(indexWieghtPairs[i-1].second, indexWieghtPairs[i - 1].first));
            indexWithPrioq[i].second.push(make_pair(indexWieghtPairs[i+c].second, indexWieghtPairs[i + c].first));
            indexWithPrioq[i].second.push(make_pair(indexWieghtPairs[i-c].second, indexWieghtPairs[i - c].first));  

        }else if((i % c == c - 1) && ((i+c) < r * c) && (i >= c)){//middle right cases
            indexWithPrioq[i].second.push(make_pair(indexWieghtPairs[i-1].second, indexWieghtPairs[i - 1].first));
            indexWithPrioq[i].second.push(make_pair(indexWieghtPairs[i+c].second, indexWieghtPairs[i + c].first));
            indexWithPrioq[i].second.push(make_pair(indexWieghtPairs[i-c].second, indexWieghtPairs[i - c].first)); 
        
        }else if((i % c == c - 1) && (i % c == 0) && ((i + c) >= (r*c)) && i >= c){//bottom left cases
            indexWithPrioq[i].second.push(make_pair(indexWieghtPairs[i+1].second, indexWieghtPairs[i + 1].first));
            indexWithPrioq[i].second.push(make_pair(indexWieghtPairs[i-c].second, indexWieghtPairs[i - c].first)); 

        }else if((i % c != c - 1) && (i % c != 0) && ((i+c)>=(r*c)) && (i > c)){//bottom middle cases
            indexWithPrioq[i].second.push(make_pair(indexWieghtPairs[i+1].second, indexWieghtPairs[i + 1].first));
            indexWithPrioq[i].second.push(make_pair(indexWieghtPairs[i-1].second, indexWieghtPairs[i - 1].first));
            indexWithPrioq[i].second.push(make_pair(indexWieghtPairs[i-c].second, indexWieghtPairs[i - c].first)); 

        }else if((i % c == c -1 ) && (i % c != 0) && ((i+c)>=(r*c)) && (i > c)){//bottom right cases
            indexWithPrioq[i].second.push(make_pair(indexWieghtPairs[i-1].second, indexWieghtPairs[i - 1].first));
            indexWithPrioq[i].second.push(make_pair(indexWieghtPairs[i-c].second, indexWieghtPairs[i - c].first));  
        }

    }

   // for(int i = 0; i < grid.size(); i++){
   //     cout << "index: " << tileWeightpq.top().first << " weight: " << tileWeightpq.top().second << "\n";
      //  tileWeightpq.pop();
  //  }

    for(int i = 0; i < grid.size(); i++){
        cout << "index: "<< indexWithPrioq[i].first;
        while(!indexWithPrioq[i].second.empty()){
            cout << "   adj index: " << indexWithPrioq[i].second.top().second << " weight: " << indexWithPrioq[i].second.top().first;
            indexWithPrioq[i].second.pop();
        }
        cout << "\n";
    }
    return 0;
}

