// dijsktras.cpp
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <random>
#include <ctime>
using namespace std;
// Main Execution
// r = (i / c);
// c= (i % c);
//need to make a function to access the adjacent cells
int infinity = numeric_limits<int>::max();
void print(vector<pair<int, priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>>> grid){
    
}
void adjTile(vector<pair<int, priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>>> grid, int index){
    cout  << "the adj function adj size"<< grid[index].second.size() << "\n";

}

void dijkstra(vector<pair<int, priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>>> grid, int start, int r, int c, int end){
    vector<int> distances(r*c, infinity);
    vector<bool> visited(r*c, false);
    vector<int> adjacentTiles;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> weightIndexpq;
    int currentTile;
    int newDistance;

    distances[start] = 0;
    weightIndexpq.push(make_pair(0, start));

/*
    for(int i = 0; i < 100; i++){
        cout << "index: "<< grid[i].first;
        while(!grid[i].second.empty()){
            cout << "   adj index: " << grid[i].second.top().second << " weight: " << grid[i].second.top().first;
            grid[i].second.pop();
        }
        cout << "\n";

        
    }
*/


    while(!weightIndexpq.empty()){
        currentTile = weightIndexpq.top().second; // will pick the smallest distance, since we set the start as zero it will pick it first
        weightIndexpq.pop();
        cout << "current Tile: " << currentTile << "\n";
        if(visited[currentTile] == true){
            continue;
        }
        if(currentTile == end){
            break;
        }
        
        //adjweight: indexWithPrioq[i].second.top().first;
        //adjindex : indexWithPrioq[i].second.top().second
       // cout << grid[currentTile].first << " grid.first\n";
       /* while(!grid[currentTile].second.empty()){
            cout << "   adj index: " << grid[currentTile].second.top().second << " weight: " << grid[currentTile].second.top().first;
            cout << "adjacent size: " << grid[currentTile].second.size();
            grid[currentTile].second.pop();
        }
*/
        //cout << grid[currentTile].second.size() << "\n";
        adjacentTiles.resize(grid[currentTile].second.size());
       // cout << adjacentTiles.size() << "\n";
        while(!grid[currentTile].second.empty()){
            newDistance = distances[currentTile] + grid[currentTile].second.top().first;

            if(newDistance < distances[grid[currentTile].second.top().second]){
                distances[grid[currentTile].second.top().second] = newDistance;
                weightIndexpq.push(make_pair(newDistance, grid[currentTile].second.top().second));
            }
            grid[currentTile].second.pop();
        }
        visited[currentTile] == true;
       // cout << "index: "<< weightIndexpq.top().second << "\n";
       // cout << "weight: " << distances[weightIndexpq.top().second] << "\n";
    }
    



    for(int i = 0; i < distances.size(); i++){
        if(distances[i] < 10){
            if(i % 10 == 9){
                cout << "0" << distances[i] << " |\n";
            }
            else
                cout << "0" << distances[i] << " | ";
        }
        else if(i % 10 != 9)
            cout << distances[i] << " | ";
        else    
            cout << distances[i] << " | \n";
    }

}
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
            cout << grid[i] << " | test\n";
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

        }else if((i % c == c - 1) && ((i + c) < (r * c)) && (i < c)){ //top right case
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
        
        }else if((i % c == 0) && ((i + c) >= (r*c)) && i >= c){//bottom left cases
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

  /*  for(int i = 0; i < grid.size(); i++){
        cout << "index: "<< indexWithPrioq[i].first;
        cout << "num of adj cells: " << indexWithPrioq[i].second.size();
        while(!indexWithPrioq[i].second.empty()){
            cout << "   adj index: " << indexWithPrioq[i].second.top().second << " weight: " << indexWithPrioq[i].second.top().first;
            indexWithPrioq[i].second.pop();
        }
        cout << "\n";

        
    }
    */
    cout << "test " << indexWithPrioq[99].second.size() << "\n";
    dijkstra(indexWithPrioq, 0, 10, 10, 99);
    adjTile(indexWithPrioq, 99);
    return 0;
}

for(int i = 0; i < r * c; i++){
        ckc[i].first = i;
        if(i == 0){ //top left/ zero case
            ckc[i].second.push(make_pair(tyt[i+1].second, tyt[i + 1].first));
            ckc[i].second.push(make_pair(tyt[i+c].second, tyt[i + c].first));

        }else if((i % c != c - 1) && (i % c != 0) && ((i + c) < (r * c)) && (i < c)){ //top middle case
            ckc[i].second.push(make_pair(tyt[i+1].second, tyt[i + 1].first));
            ckc[i].second.push(make_pair(tyt[i-1].second, tyt[i - 1].first));
            ckc[i].second.push(make_pair(tyt[i+c].second, tyt[i + c].first));

        }else if((i % c == c - 1) && ((i + c) < (r * c)) && (i < c)){ //top right case
            ckc[i].second.push(make_pair(tyt[i-1].second, tyt[i - 1].first));
            ckc[i].second.push(make_pair(tyt[i+c].second, tyt[i + c].first));

        }else if((i % c == 0) && ((i + c) < (r * c)) && (i >= c)){//middle left cases
            ckc[i].second.push(make_pair(tyt[i+1].second, tyt[i + 1].first));
            ckc[i].second.push(make_pair(tyt[i+c].second, tyt[i + c].first));
            ckc[i].second.push(make_pair(tyt[i-c].second, tyt[i - c].first));   

        }else if((i % c != c - 1) && (i % c != 0) && ((i + c) < (r * c)) && i >= c){ //middle cases
            ckc[i].second.push(make_pair(tyt[i+1].second, tyt[i + 1].first));
            ckc[i].second.push(make_pair(tyt[i-1].second, tyt[i - 1].first));
            ckc[i].second.push(make_pair(tyt[i+c].second, tyt[i + c].first));
            ckc[i].second.push(make_pair(tyt[i-c].second, tyt[i - c].first));  

        }else if((i % c == c - 1) && ((i+c) < r * c) && (i >= c)){//middle right cases
            ckc[i].second.push(make_pair(tyt[i-1].second, tyt[i - 1].first));
            ckc[i].second.push(make_pair(tyt[i+c].second, tyt[i + c].first));
            ckc[i].second.push(make_pair(tyt[i-c].second, tyt[i - c].first)); 
        
        }else if((i % c == 0) && ((i + c) >= (r*c)) && i >= c){//bottom left cases
            ckc[i].second.push(make_pair(tyt[i+1].second, tyt[i + 1].first));
            ckc[i].second.push(make_pair(tyt[i-c].second, tyt[i - c].first)); 

        }else if((i % c != c - 1) && (i % c != 0) && ((i+c)>=(r*c)) && (i > c)){//bottom middle cases
            ckc[i].second.push(make_pair(tyt[i+1].second, tyt[i + 1].first));
            ckc[i].second.push(make_pair(tyt[i-1].second, tyt[i - 1].first));
            ckc[i].second.push(make_pair(tyt[i-c].second, tyt[i - c].first)); 

        }else if((i % c == c -1 ) && (i % c != 0) && ((i+c)>=(r*c)) && (i > c)){//bottom right cases
            ckc[i].second.push(make_pair(tyt[i-1].second, tyt[i - 1].first));
            ckc[i].second.push(make_pair(tyt[i-c].second, tyt[i - c].first));  
        }

    }
