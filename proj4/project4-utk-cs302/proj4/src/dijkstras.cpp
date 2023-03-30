// dijsktras.cpp
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <random>
#include <ctime>
using namespace std;
// Main Execution
int infinity = numeric_limits<int>::max();

vector<int> dijkstra(vector<pair<int, priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>>> grid, int start, int r, int c, int end){
    vector<int> distances(r*c, infinity);
    vector<bool> visited(r*c, false);
    vector<int> adjacentTiles;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> totalWeightIndexpq;
    int currentTile;
    int newDistance;

    distances[start] = 0;
    totalWeightIndexpq.push(make_pair(0, start));


    while(!totalWeightIndexpq.empty()){
        currentTile = totalWeightIndexpq.top().second; // will pick the smallest distance, since we set the start as zero it will pick it first
        totalWeightIndexpq.pop();
      
        if(visited[currentTile] == true){
            continue;
        }
        if(currentTile == end){
            break;
        }
          
        adjacentTiles.resize(grid[currentTile].second.size());
        while(!grid[currentTile].second.empty()){
            newDistance = distances[currentTile] + grid[currentTile].second.top().first;
            if(newDistance < distances[grid[currentTile].second.top().second]){
                distances[grid[currentTile].second.top().second] = newDistance;
                totalWeightIndexpq.push(make_pair(newDistance, grid[currentTile].second.top().second));
            }
            grid[currentTile].second.pop();
        }
        visited[currentTile] == true;
      
    }
    
    return distances;

}


int main(int argc, char *argv[]) {
    int numTiles, tileCost, r, c, startRow, startCol, endRow, endCol, startIndex, endIndex;
    char tileName, tileIn;
    vector<pair<char, int>> charCostVec;
    vector<char> charMap;
    vector<int> costMap;
    vector<pair<int, int>> indexWieghtPairs;//index, weight         first = index        second = weight
    vector<pair<int, priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>>> indexWithPrioq;
    vector<int> totalDistances; //after you run dikstras, remake the indexwithprioq but for total weights, have it start at end, pick lowest
    //cell
    vector<pair<int, int>> totalWeightIndexPairs;// first = index         second = total weight got from total distaces
    vector<pair<int, priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>>> indexTotalWeightWithpq;


    cin >> numTiles;//get number of different tiles, map a vector of pairs to access cost
    charCostVec.resize(numTiles);
    for(int i = 0; i < numTiles; i++){
        cin >> tileName >> tileCost;
        charCostVec[i].first = tileName;
        charCostVec[i].second = tileCost;
    }
    //get amount of rows and columns, then begin to fill in grid, costMap will be mad of ints and will be used primarily.
    //make sure every container are of proper sizes
    cin >> r >> c;
    charMap.resize(r * c);
    costMap.resize(r * c);
    indexWieghtPairs.resize(r * c);
    indexWithPrioq.resize(r * c);
    totalWeightIndexPairs.resize(r * c);
    indexTotalWeightWithpq.resize(r * c);
    for(int i = 0; i < c * r; i++){
        cin >> tileIn;
        charMap[i] == tileIn;
        for(int j = 0; j < charCostVec.size(); j++){
            if(charCostVec[j].first == tileIn){
                costMap[i] = charCostVec[j].second;
            }
        }
    }
    cin >> startRow >> startCol;
    cin >> endRow >> endCol;

    startIndex = (startRow * c) + startCol;
    endIndex = (endRow * c) + endCol;
    costMap[startIndex] = 0;
    costMap[endIndex] = 0;

    for(int i = 0; i < indexWieghtPairs.size(); i++){
        indexWieghtPairs[i].first = i;
        indexWieghtPairs[i].second = costMap[i];
    }

//like superball i used the same logic for pairing an index with its adjacent cells, basically checking if its on the edge of the map
//as that limits it neighbor amount
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
    totalDistances = dijkstra(indexWithPrioq, startIndex, r, c, endIndex);

    for(int i = 0; i < totalWeightIndexPairs.size(); i++){
        totalWeightIndexPairs[i].first = i;
        totalWeightIndexPairs[i].second = totalDistances[i];
    }

    for(int i = 0; i < r * c; i++){
        indexTotalWeightWithpq[i].first = i;
        if(i == 0){ //top left/ zero case
            indexTotalWeightWithpq[i].second.push(make_pair(totalWeightIndexPairs[i+1].second, totalWeightIndexPairs[i + 1].first));
            indexTotalWeightWithpq[i].second.push(make_pair(totalWeightIndexPairs[i+c].second, totalWeightIndexPairs[i + c].first));

        }else if((i % c != c - 1) && (i % c != 0) && ((i + c) < (r * c)) && (i < c)){ //top middle case
            indexTotalWeightWithpq[i].second.push(make_pair(totalWeightIndexPairs[i+1].second, totalWeightIndexPairs[i + 1].first));
            indexTotalWeightWithpq[i].second.push(make_pair(totalWeightIndexPairs[i-1].second, totalWeightIndexPairs[i - 1].first));
            indexTotalWeightWithpq[i].second.push(make_pair(totalWeightIndexPairs[i+c].second, totalWeightIndexPairs[i + c].first));

        }else if((i % c == c - 1) && ((i + c) < (r * c)) && (i < c)){ //top right case
            indexTotalWeightWithpq[i].second.push(make_pair(totalWeightIndexPairs[i-1].second, totalWeightIndexPairs[i - 1].first));
            indexTotalWeightWithpq[i].second.push(make_pair(totalWeightIndexPairs[i+c].second, totalWeightIndexPairs[i + c].first));

        }else if((i % c == 0) && ((i + c) < (r * c)) && (i >= c)){//middle left cases
            indexTotalWeightWithpq[i].second.push(make_pair(totalWeightIndexPairs[i+1].second, totalWeightIndexPairs[i + 1].first));
            indexTotalWeightWithpq[i].second.push(make_pair(totalWeightIndexPairs[i+c].second, totalWeightIndexPairs[i + c].first));
            indexTotalWeightWithpq[i].second.push(make_pair(totalWeightIndexPairs[i-c].second, totalWeightIndexPairs[i - c].first));   

        }else if((i % c != c - 1) && (i % c != 0) && ((i + c) < (r * c)) && i >= c){ //middle cases
            indexTotalWeightWithpq[i].second.push(make_pair(totalWeightIndexPairs[i+1].second, totalWeightIndexPairs[i + 1].first));
            indexTotalWeightWithpq[i].second.push(make_pair(totalWeightIndexPairs[i-1].second, totalWeightIndexPairs[i - 1].first));
            indexTotalWeightWithpq[i].second.push(make_pair(totalWeightIndexPairs[i+c].second, totalWeightIndexPairs[i + c].first));
            indexTotalWeightWithpq[i].second.push(make_pair(totalWeightIndexPairs[i-c].second, totalWeightIndexPairs[i - c].first));  

        }else if((i % c == c - 1) && ((i+c) < r * c) && (i >= c)){//middle right cases
            indexTotalWeightWithpq[i].second.push(make_pair(totalWeightIndexPairs[i-1].second, totalWeightIndexPairs[i - 1].first));
            indexTotalWeightWithpq[i].second.push(make_pair(totalWeightIndexPairs[i+c].second, totalWeightIndexPairs[i + c].first));
            indexTotalWeightWithpq[i].second.push(make_pair(totalWeightIndexPairs[i-c].second, totalWeightIndexPairs[i - c].first)); 
        
        }else if((i % c == 0) && ((i + c) >= (r*c)) && i >= c){//bottom left cases
            indexTotalWeightWithpq[i].second.push(make_pair(totalWeightIndexPairs[i+1].second, totalWeightIndexPairs[i + 1].first));
            indexTotalWeightWithpq[i].second.push(make_pair(totalWeightIndexPairs[i-c].second, totalWeightIndexPairs[i - c].first)); 

        }else if((i % c != c - 1) && (i % c != 0) && ((i+c)>=(r*c)) && (i > c)){//bottom middle cases
            indexTotalWeightWithpq[i].second.push(make_pair(totalWeightIndexPairs[i+1].second, totalWeightIndexPairs[i + 1].first));
            indexTotalWeightWithpq[i].second.push(make_pair(totalWeightIndexPairs[i-1].second, totalWeightIndexPairs[i - 1].first));
            indexTotalWeightWithpq[i].second.push(make_pair(totalWeightIndexPairs[i-c].second, totalWeightIndexPairs[i - c].first)); 

        }else if((i % c == c -1 ) && (i % c != 0) && ((i+c)>=(r*c)) && (i > c)){//bottom right cases
            indexTotalWeightWithpq[i].second.push(make_pair(totalWeightIndexPairs[i-1].second, totalWeightIndexPairs[i - 1].first));
            indexTotalWeightWithpq[i].second.push(make_pair(totalWeightIndexPairs[i-c].second, totalWeightIndexPairs[i - c].first));  
        }

    }


}

