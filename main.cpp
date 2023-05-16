#include <iostream>
#include <ncurses.h>
#include <random>
using namespace std;
bool gameOver;
const int WIDTH = 20;
const int HEIGHT = 20;
int x, y, foodX, foodY, score;
int tailX[100], tailY[100];
int nTail;
enum Direction {
    STOP = 0, LEFT, RIGHT, UP, DOWN
};
Direction dir;

int kbhit(void)
{
    int ch = getch();
    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    srand(time(NULL));
    foodX = (rand() % WIDTH == 0 || rand() % WIDTH == WIDTH / 2) ? (rand() % WIDTH + 1) : (rand() % WIDTH);
    foodY = (rand() % HEIGHT == 0 || rand() % HEIGHT == HEIGHT / 2) ? (rand() % HEIGHT + 1) : (rand() % HEIGHT);
    score = 0;
}

void Draw()
{
    clear();
    for (int i = 0; i < WIDTH; i++) {
        mvprintw(0, i, "#");
    }

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0 || j == WIDTH - 1) {
                mvprintw(i + 1, j, "#");
            }
            else if (j == x && i == y) {
                mvprintw(i + 1, j, "O");
            }
            else if (j == foodX && i == foodY) {
                mvprintw(i + 1, j, "F");
            }
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        mvprintw(i + 1, j, "o");
                        print = true;
                    }
                }
                if (!print) {
                    mvprintw(i + 1, j, " ");
                }
            }
        }
    }

    for (int i = 0; i < WIDTH; i++) {
        mvprintw(HEIGHT + 1, i, "#");
    }

    mvprintw(HEIGHT + 3, 0, "Score: %d", score);
}

void Input()
{
    if (kbhit()) {
        switch (getch()) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    if (x >= WIDTH) {
        x = 0;
    } else if (x < 0) {
        x = WIDTH - 1;
    } if (y >= HEIGHT) {
        y = 0;
    } else if (y < 0) {
        y = HEIGHT - 1;
    }

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }

    if (x == foodX && y == foodY) {
        score += 10;
        foodX = rand() % WIDTH == 0 ? (rand() % WIDTH + 1) : (rand() % WIDTH);
        foodY = rand() % HEIGHT == 0 ? (rand() % HEIGHT + 1) : (rand() % HEIGHT);
        nTail++;
    }
}

int main() {
    initscr();
    cbreak();
    Setup();

    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
    }
    endwin();
}
