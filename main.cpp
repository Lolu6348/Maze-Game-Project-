#include <iostream>
#include <ctime>

class Maze {
private:
    const int width = 10;
    const int height = 10;
    char layout[10][10] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', ' ', '#', ' ', '#', '#', ' ', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#'},
        {'#', ' ', '#', '#', '#', '#', ' ', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#'},
        {'#', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#'},
        {'#', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', '#', ' ', ' ', 'E', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
    };

public:
    void draw(int playerX, int playerY) {
        system("clear");  // use "cls" on Windows
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (i == playerY && j == playerX)
                    std::cout << 'P';
                else
                    std::cout << layout[i][j];
            }
            std::cout << '\n';
        }
    }

    bool isWalkable(int x, int y) {
        return layout[y][x] == ' ' || layout[y][x] == 'T' || layout[y][x] == 'E';
    }

    bool isTrap(int x, int y) {
        return layout[y][x] == 'T';
    }

    bool isExit(int x, int y) {
        return layout[y][x] == 'E';
    }

    void placeTrap(int x, int y) {
        if (layout[y][x] == ' ')
            layout[y][x] = 'T';
    }

    bool isInBounds(int x, int y) {
        return x >= 0 && x < width && y >= 0 && y < height;
    }
};

class Game {
private:
    Maze maze;
    int playerX = 1, playerY = 1;
    int moveCount = 0;
    std::clock_t startTime;

public:
    void start() {
        maze.placeTrap(5, 3); // Place a trap
        maze.placeTrap(7, 4);
        startTime = std::clock();

        while (true) {
            maze.draw(playerX, playerY);
            std::cout << "\nMoves: " << moveCount << "\nUse WASD to move: ";
            char input;
            std::cin >> input;
            movePlayer(tolower(input));

            if (maze.isExit(playerX, playerY)) {
                double duration = (std::clock() - startTime) / (double)CLOCKS_PER_SEC;
                std::cout << "\n🎉 You escaped the maze in " << moveCount << " moves and "
                          << duration << " seconds!\n";
                break;
            }

            if (maze.isTrap(playerX, playerY)) {
                std::cout << "\n💥 You stepped on a trap! Game Over.\n";
                break;
            }
        }
    }

private:
    void movePlayer(char direction) {
        int newX = playerX, newY = playerY;
        switch (direction) {
            case 'w': newY--; break;
            case 's': newY++; break;
            case 'a': newX--; break;
            case 'd': newX++; break;
            default: return;
        }

        if (maze.isInBounds(newX, newY) && maze.isWalkable(newX, newY)) {
            playerX = newX;
            playerY = newY;
            moveCount++;
        }
    }
};

int main() {
    Game mazeGame;
    mazeGame.start();
    return 0;
}
