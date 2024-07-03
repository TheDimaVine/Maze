#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <algorithm>

using namespace std;

// Constants for cell types
const int WALL = 0;
const int ROAD = 1;
const int ENTRANCE = 2;
const int EXIT = 3;
const int TRAP = 4;
const int TREASURE = 5;

// Function prototypes
vector<vector<int>> generateMaze(int size);
void printMaze(const vector<vector<int>>& maze, int playerX, int playerY, int trapHits);
bool isValidMove(const vector<vector<int>>& maze, int x, int y);
void setColor(int color);
void clearScreen();
char getInput();

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    int size = 10;  // Change this to adjust the size of the maze
    vector<vector<int>> maze = generateMaze(size);

    // Initialize player position and trap hits
    int playerX, playerY;
    int trapHits = 0;

    // Find initial player position (ENTRANCE)
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (maze[i][j] == ENTRANCE) {
                playerX = i;
                playerY = j;
                break;
            }
        }
    }

    // Game loop
    while (true) {
        // Print maze
        clearScreen();
        printMaze(maze, playerX, playerY, trapHits);

        // Check if player has stepped on too many traps
        if (trapHits >= 3) {
            cout << "You stepped on too many traps and died!" << endl;
            break;  // End the game
        }

        // Check if player reached the exit
        if (maze[playerX][playerY] == EXIT) {
            cout << "Congratulations! You escaped the maze!" << endl;
            break;  // End the game
        }

        // Get player move
        cout << "Enter direction (w/a/s/d) or 'q' to quit: ";
        char move = getInput();

        int newX = playerX, newY = playerY;

        switch (move) {
        case 'w':
            newX--;
            break;
        case 's':
            newX++;
            break;
        case 'a':
            newY--;
            break;
        case 'd':
            newY++;
            break;
        case 'q':
            cout << "Quitting the game...";
            return 0;
        default:
            cout << "Invalid move!" << endl;
            continue;  // Repeat the loop
        }

        // Check if the move is valid
        if (newX >= 0 && newX < size && newY >= 0 && newY < size && maze[newX][newY] != WALL) {
            playerX = newX;
            playerY = newY;

            // Check if the player hits a trap
            if (maze[playerX][playerY] == TRAP) {
                trapHits++;
                cout << "Ouch! You stepped on a trap!" << endl;
            }
        }
        else {
            cout << "Invalid move! Try again." << endl;
        }
    }

    // Wait for user input before exiting
    cout << "Press Enter to exit...";
    cin.ignore();  // Ignore any input
    cin.get();
    return 0;
}

vector<vector<int>> generateMaze(int size) {
    // Initialize the maze with walls
    vector<vector<int>> maze(size, vector<int>(size, WALL));

    // Choose random entrance and exit positions
    int entranceX, entranceY, exitX, exitY;
    switch (rand() % 4) {
    case 0:  // top
        entranceX = 0;
        entranceY = rand() % size;
        exitX = size - 1;
        exitY = rand() % size;
        break;
    case 1:  // bottom
        entranceX = size - 1;
        entranceY = rand() % size;
        exitX = 0;
        exitY = rand() % size;
        break;
    case 2:  // left
        entranceX = rand() % size;
        entranceY = 0;
        exitX = rand() % size;
        exitY = size - 1;
        break;
    case 3:  // right
        entranceX = rand() % size;
        entranceY = size - 1;
        exitX = rand() % size;
        exitY = 0;
        break;
    }

    maze[entranceX][entranceY] = ENTRANCE;
    maze[exitX][exitY] = EXIT;

    // Use DFS to generate paths from entrance to exit
    stack<pair<int, int>> st;
    st.push(make_pair(entranceX, entranceY));
    vector<pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    while (!st.empty()) {
        int currX = st.top().first;
        int currY = st.top().second;
        st.pop();

        if (isValidMove(maze, currX, currY)) {
            maze[currX][currY] = ROAD;

            random_shuffle(directions.begin(), directions.end());

            for (auto& direction : directions) {
                int nextX = currX + direction.first;
                int nextY = currY + direction.second;

                if (nextX >= 0 && nextX < size && nextY >= 0 && nextY < size && maze[nextX][nextY] == WALL) {
                    st.push(make_pair(nextX, nextY));
                }
            }
        }
    }

    // Ensure the entrance and exit are set correctly after path generation
    maze[entranceX][entranceY] = ENTRANCE;
    maze[exitX][exitY] = EXIT;

    // Generate traps and treasure (optional)
    int numTraps = rand() % 6;
    for (int i = 0; i < numTraps; ++i) {
        int trapX, trapY;
        do {
            trapX = rand() % size;
            trapY = rand() % size;
        } while (maze[trapX][trapY] != ROAD);
        maze[trapX][trapY] = TRAP;
    }

    if (rand() % 2 == 0) {
        int treasureX, treasureY;
        do {
            treasureX = rand() % size;
            treasureY = rand() % size;
        } while (maze[treasureX][treasureY] != ROAD);
        maze[treasureX][treasureY] = TREASURE;
    }

    return maze;
}

void printMaze(const vector<vector<int>>& maze, int playerX, int playerY, int trapHits) {
    for (int i = 0; i < maze.size(); ++i) {
        for (int j = 0; j < maze[i].size(); ++j) {
            if (i == playerX && j == playerY) {
                // Print player symbol
                if (trapHits >= 3) {
                    setColor(4);  // Red for dead player
                    cout << "X ";
                }
                else {
                    setColor(2);  // Green for alive player
                    cout << "P ";
                }
            }
            else {
                // Print maze cell based on type
                switch (maze[i][j]) {
                case WALL:
                    setColor(15);  // White
                    cout << "0 ";
                    break;
                case ROAD:
                    setColor(7);  // Gray
                    cout << "1 ";
                    break;
                case ENTRANCE:
                    setColor(2);  // Green
                    cout << "E ";
                    break;
                case EXIT:
                    setColor(4);  // Red
                    cout << "X ";
                    break;
                case TRAP:
                    setColor(14);  // Yellow
                    cout << "T ";
                    break;
                case TREASURE:
                    setColor(11);  // Cyan
                    cout << "$ ";
                    break;
                }
            }
        }
        cout << endl;
        setColor(15);
    }
}

bool isValidMove(const vector<vector<int>>& maze, int x, int y) {
    int size = maze.size();
    int adjacentRoads = 0;
    vector<pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    for (auto& direction : directions) {
        int nx = x + direction.first;
        int ny = y + direction.second;
        if (nx >= 0 && nx < size && ny >= 0 && ny < size && maze[nx][ny] == ROAD) {
            adjacentRoads++;
        }
    }

    return (adjacentRoads <= 1);
}

void setColor(int color) {
    switch (color) {
    case 2:  // Green
        cout << "\033[32m";
        break;
    case 4:  // Red
        cout << "\033[31m";
        break;
    case 14:  // Yellow
        cout << "\033[33m";
        break;
    case 11:  // Cyan
        cout << "\033[36m";
        break;
    case 7:  // Gray
        cout << "\033[38;5;206m";
        break;
    case 15:  // White
        cout << "\033[37m";
        break;
    }
}

void clearScreen() {
    cout << "\033[H\033[J";
}

char getInput() {
    char ch;
    cin >> ch;
    return ch;
}


