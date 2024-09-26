#include <iostream>
#include <conio.h> // For _getch()

const int width = 10;
const int height = 10;
char maze[height][width] = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', '#', ' ', '#', ' ', '#', '#', ' ', '#'},
    {'#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', '#', '#', '#', '#', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#'},
    {'#', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

int playerX = 1, playerY = 1;

void drawMaze() {
    system("cls");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == playerY && j == playerX)
                std::cout << 'P';
            else
                std::cout << maze[i][j];
        }
        std::cout << std::endl;
    }
}

void movePlayer(char direction) {
    int newX = playerX, newY = playerY;
    switch (direction) {
    case 'w': newY--; break;
    case 's': newY++; break;
    case 'a': newX--; break;
    case 'd': newX++; break;
    }
    if (maze[newY][newX] == ' ') {
        playerX = newX;
        playerY = newY;
    }
}

int main() {
    while (true) {
        drawMaze();
        char input = _getch();
        movePlayer(input);
    }
    return 0;
}
