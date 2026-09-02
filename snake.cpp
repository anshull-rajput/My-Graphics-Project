#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
using namespace std;

const int WIDTH = 40;
const int HEIGHT = 20;

bool gameOver;
int score;
int headX, headY;
int directionX, directionY;
pair<int, int> food;
vector<pair<int, int>> snake;

void setup() {
    gameOver = false;
    score = 0;
    headX = WIDTH / 2;
    headY = HEIGHT / 2;
    directionX = 1;
    directionY = 0;

    snake.clear();
    snake.push_back({headX, headY});

    srand(static_cast<unsigned>(time(nullptr)));
    food = {rand() % WIDTH, rand() % HEIGHT};
}

void draw() {
    system("cls");

    for (int i = 0; i < WIDTH + 2; i++) cout << '#';
    cout << '\n';

    for (int y = 0; y < HEIGHT; y++) {
        cout << '#';

        for (int x = 0; x < WIDTH; x++) {
            bool printed = false;

            if (x == food.first && y == food.second) {
                cout << 'F';
                printed = true;
            } else {
                for (size_t i = 0; i < snake.size(); i++) {
                    if (snake[i].first == x && snake[i].second == y) {
                        cout << (i == 0 ? 'O' : 'o');
                        printed = true;
                        break;
                    }
                }
            }

            if (!printed) cout << ' ';
        }

        cout << "#\n";
    }

    for (int i = 0; i < WIDTH + 2; i++) cout << '#';
    cout << "\nScore: " << score << '\n';
    cout << "W A S D = Move | X = Quit\n";
}

void input() {
    if (!_kbhit()) return;

    char key = _getch();

    if ((key == 'w' || key == 'W') && directionY != 1) {
        directionX = 0;
        directionY = -1;
    } else if ((key == 's' || key == 'S') && directionY != -1) {
        directionX = 0;
        directionY = 1;
    } else if ((key == 'a' || key == 'A') && directionX != 1) {
        directionX = -1;
        directionY = 0;
    } else if ((key == 'd' || key == 'D') && directionX != -1) {
        directionX = 1;
        directionY = 0;
    } else if (key == 'x' || key == 'X') {
        gameOver = true;
    }
}

void moveSnake() {
    headX += directionX;
    headY += directionY;

    if (headX < 0) headX = WIDTH - 1;
    if (headX >= WIDTH) headX = 0;
    if (headY < 0) headY = HEIGHT - 1;
    if (headY >= HEIGHT) headY = 0;

    snake.insert(snake.begin(), {headX, headY});

    if (headX == food.first && headY == food.second) {
        score += 10;

        do {
            food = {rand() % WIDTH, rand() % HEIGHT};
        } while (find(snake.begin(), snake.end(), food) != snake.end());
    } else {
        snake.pop_back();
    }

    for (size_t i = 1; i < snake.size(); i++) {
        if (snake[i] == snake[0]) {
            gameOver = true;
            break;
        }
    }
}

int main() {
    setup();

    while (!gameOver) {
        draw();
        input();
        moveSnake();
        Sleep(120);
    }

    cout << "\nGame Over! Final Score: " << score << '\n';
    cout << "Press any key to exit...";
    _getch();

    return 0;
}
