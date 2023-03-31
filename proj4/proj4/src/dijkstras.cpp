// dijsktras.cpp
// Malika Arifova, Connor Riley
// 3/31/2023
// GitHub: https://github.com/Criley71/project4-utk-cs302 
// This implements a pathfinding algorithm on a map 
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <random>
#include <stack>
#include <ctime>
using namespace std;


int infinity = numeric_limits<int>::max();
/**
 * The dijkstras algorithm takes in the adjacency matrix, the starting index, map size, end index and a vector of weights for each index.
 * It starts by making a distances vector the size of the board and fills them with the value of infinity, a bool vector to store the visited indices
 * and a prioirity queue to sort the next possible path choice by smallest distance. We start at the starting index and pull its adjacent cells and put 
 * the total weight index pairs into a priority queue. it will do this for the whole grid and return the total distances of each index in a vector.
 */
vector<int> dijkstra(vector<pair<int, priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>>> grid, int start, int r, int c, int end, vector<int> costVec){
    vector<int> distances(r*c, infinity);
    vector<bool> visited(r*c, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> totalWeightIndexpq;
    int currentTile;
    int newDistance;

    distances[start] = costVec[start];
    totalWeightIndexpq.push(make_pair(0, start));


    while(!totalWeightIndexpq.empty()){
        currentTile = totalWeightIndexpq.top().second; // will pick the smallest distance, since we set the start as zero it will pick it first
        totalWeightIndexpq.pop();
      
        if(visited[currentTile] == true){
            continue;
        }
          
       
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
/**
 * the pathfinder algorithm works the same way as dijkstras, but doesnt calculate total weight and instead back tracks until we reach the original starting point
 * It stores the path into a stack that it will return.
 */
stack<int> pathFinder(vector<pair<int, priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>>> grid, int start, int r, int c, int end, vector<int> distances)
{
    int currentTile;
    vector<bool> visited(r * c, false);
    stack<int> path;
    distances[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> weightIndexpq;
    weightIndexpq.push(make_pair(0, start));

    while (!weightIndexpq.empty())
    {
        currentTile = weightIndexpq.top().second; // will pick the smallest distance, since we set the start as zero it will pick it first
        weightIndexpq.pop();
       
        if (visited[currentTile] == true)
        {
            continue;
        }
        if (currentTile == end)
        {
            path.push(currentTile);
            break;
        }

        while (!grid[currentTile].second.empty())
        {
            weightIndexpq.push(make_pair(grid[currentTile].second.top().first, grid[currentTile].second.top().second));
            grid[currentTile].second.pop();
        }
        visited[currentTile] == true;
        grid[currentTile].second.pop();
        path.push(currentTile);
        
    }
    return path;
}


int main(int argc, char *argv[]) {
    int numTiles, tileCost, r, c, startRow, startCol, endRow, endCol, startIndex, endIndex;
    char tileName, tileIn;
    vector<pair<char, int>> charCostVec;
    vector<char> charMap;
    vector<int> costMap;
    stack<int> path;
    vector<pair<int, int>> indexWieghtPairs;//index, weight         first = index        second = weight
    vector<pair<int, priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>>> indexWithPrioq;
    vector<int> totalDistances; //after you run dikstras, remake the indexwithprioq but for total weights, have it start at end, pick lowest
    //cell
    vector<pair<int, int>> totalWeightIndexPairs;// first = index         second = total weight got from total distaces
    vector<pair<int, priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>>> indexTotalWeightWithpq;

    /**
     * We start by reading in the inputs needed to generate a map and resize all containers to be the same size as the grid. 
     * We fill in containers of the map as letters, and of numbers indicating there weight.
     */

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
    costMap[endIndex] = 0;

    for(int i = 0; i < indexWieghtPairs.size(); i++){
        indexWieghtPairs[i].first = i;
        indexWieghtPairs[i].second = costMap[i];
    }
//Next we make the adjacency matrix. we used the set up of vector<pair<int, priority_queue<pair<int, int>>>
//putting names to the ints it would look like vector<pair<index, priority_queue<adjacentCellWeight, adjacentCellIndex>>> 
//Then like superball i used the same logic for pairing an index with its adjacent cells, basically checking if its on the edge of the map
//as that limits it neighbor amount. Once made i run dijkstras and get the total distances in a vector
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
    totalDistances = dijkstra(indexWithPrioq, startIndex, r, c, endIndex, costMap);
    
    //now that we have the total distances we now can remake the adjacency matrix the same way as before, but use the total distance
    //to reach an index instead of the index's personal weight.
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
//we call the pathfinder algorithm and store it in a stack
//we print the total distance and the path it took.
path = pathFinder(indexTotalWeightWithpq, endIndex, r, c, startIndex, totalDistances);
cout << totalDistances[endIndex] << "\n";
while(!path.empty()){
    cout << path.top() / c << " " << path.top() % c << "\n";
    path.pop();
}

}

