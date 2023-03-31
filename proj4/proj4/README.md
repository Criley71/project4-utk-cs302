USAGE: This assumes that your dijkstras and generate_map.py are in your src directory and your makefile being one hierchary outside the src directory. Essentially how the file structure was set up for the project

To run the grdescripts it is just make test. DO THIS FIRST as it will make the dijkstra executable that is also used by the python script 

To generate a random map of N size and run it, it is make generate_map N=# , # = dimension


Project 04: Path Finding  
========================
- 

Connor Riley and Malika Arifova

This project implements a [Dijkstra's Algorithm] to perform rudimentary path
finding on a 2D tile-based map.

[Dijkstra's Algorithm]: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm


Timing and Memory Usage

| N             | Elapsed Time  |Memory Usage(mb)|
|---------------|---------------|----------------|
| 10            | .226s         | 3.84           |
| 20            | .228s         | 3.89           |
| 50            | .221s         | 4.23           |
| 100           | .275s         | 5.40           |
| 200           | .506s         | 9.99           |
| 500           | 1.81s         | 42.2           |
| 1000          | 6.11s         | 157.36         |

1. How did you represent the map as a graph? Explain which graph representation you used and how you determined the relationship between vertices include the edges and their weights.
Adjacency matrix with a priority queue.

2. What is complexity of your implementation of Dijkstra's Algorithm? Explain this by describing which data structures you used and how you used them to implement path finding.
   The time complexity of our Dijkstra's Algorithm is O(n log n). We made an adjacency matrix of a vector of pairs with the pairs being an integer paired with a priority queue of pairs. It would take N time to fill the matrix and then it would find the total weight of every cell or once it hit n cell. Then we remade the adjacency matrix with the total weights and then backtracked through it which is the log n time. It is being linearly scaled as N got larger but its not as exponentially steeper. 

3.How well does your implementation scale? Explain what effect did N (ie. the size of the map) have on the performance of your dijkstras path finding component in terms of execution time and memory usage?
   As the map gets larger the time it took to ran became longer with an order approximate to (n)log(n) when only a 10x10 map it takes about .226 seconds, but when 1000x1000 it takes about 6 seconds. The memory usage seems to be exponentially used as at a size of 200 it uses 9.99 mb but 500 uses 42.2 mb. This would make sense as the grid is being sized by n^2.

Time Log
-------

Connor Riley and Malika Arifova - 3/26, 7pm -> 10 pm - priority queue research and brainstorming ideas for implementation

Connor Riley and Malika Arifova - 3/27, 5pm -> 9pm - worked on developing an adjacency matrix

Connor Riley and Malika Arifova - 3/28, 5:30pm -> 9:30pm - worked on implementing dijkstras algorithm on our adjacency matrix, 

Connor Riley - 3/28, 12am -> 2:30 am - Worked on refilling the adjacency matrix with the total weights so it can back track

Connor Riley and Malika Arifova - 3/29, 6:30 -> 9pm - Finished the dijkstras.cpp

Connor Riley - 3/29 12am -> 3am - generate_map.py and the MakeFile - DONE!


Input
-----

    TILES_N
    TILE_NAME_0	TILE_COST_0
    ...
    TILE_NAME_N-1	TILE_COST_N-1

    MAP_ROWS MAP_COLUMNS
    TILE_0_0    ...
    ...

    TRAVELER_START_ROW TRAVELER_START_COL
    TRAVELER_END_ROW   TRAVELER_END_COL

Output
------

    Cost
    [(ROW_0, COL_0), ...]
    
