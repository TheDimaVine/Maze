# Maze
Testing task for company

How to run this project? You should download all files and run Website Analytics.sin by using Visual Studio. If you havent Visual Studio, copy and paste code from main.cpp in your IDE.

Efficiency Analysis
1. Maze Generation with DFS:

The maze generation uses a Depth-First Search (DFS) algorithm to create a path from the entrance to the exit.
Time Complexity: The time complexity of DFS is O(V+E), where V is the number of vertices (cells) and E is the number of edges (connections between cells). Since the maze is a grid,  V is size^2 and E is also size^2 (each cell has 4 possible edges).
Space Complexity: The space complexity is O(V) due to the stack used in DFS, which in the worst case can store all vertices. Here, it is O(size^2).

2. Maze Printing:
Printing the maze involves iterating over each cell and printing its content with the appropriate color.
Time Complexity: The time complexity of printing the maze is O(size^2), as it involves iterating over all cells.
Space Complexity: This is negligible for printing since it uses only a constant amount of additional space for coloring and displaying.

3. Player Movement and Game Loop:
Each iteration of the game loop involves reading player input, updating the player's position, and checking conditions for traps and exits.
Time Complexity: In each move, the algorithm checks a constant number of cells around the player (4 cells). Therefore, the time complexity for each move is O(1).
Space Complexity: This involves only a constant amount of space, O(1), for storing the player position and trap hit count.

Combined Complexity
Considering all parts together:
Time Complexity:
Maze generation: O(size^2)
Printing maze: O(size^2)
Player movement per iteration: O(1)
Since maze generation and printing dominate, the overall time complexity for initializing and one-time printing is O(size^2).
Space Complexity:
The space complexity is dominated by the storage of the maze grid, which is O(size^2).

Big O Notation
The overall time complexity of the program, considering maze generation, printing, and player movement, can be classified as:O(size^2)
This is because the maze generation and printing dominate the runtime, and both are O(size^2).
The space complexity is also:O(size^2)
due to the storage of the maze grid itself.
