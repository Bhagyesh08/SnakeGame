// Snake Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<Windows.h>
using namespace std;

bool game;
enum set{MAIN,START};
int menu = 0;
set mode;
const int width = 25;
const int height = 25;
int x, y,speed=1;
int tailX[100], tailY[100],length;
int fx, fy, sx, sy;
int targetX, targetY;
int negativeX, negativeY;
int score;
enum u{STOP=0,UP,DOWN,LEFT,RIGHT};
u dr;
void Gameover() {
    length = 0;
    score = 0;
    mode = MAIN;
}
void game_setup() {
    game = true;
    mode = MAIN;
}
void MainMenu() {
    system("cls");
    cout << "This is the Main Menu.." << endl;
    if (menu == 0) {
        cout << ">> Play the Game." << endl;
        cout << "End Game" << endl;
    }
    else if (menu == 1) {
        cout << "Play the Game." << endl;
        cout << ">> End Game" << endl;
    }
    if (GetAsyncKeyState(VK_RETURN)) {
        switch (menu) {
        case 0:
            mode = START;
            break;
        case 1:
            exit(0);
            break;
        }
    }
    else if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) {
        dr = STOP;
    }
    else if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')) {
        dr = STOP;
    }
    else if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')) {
        dr = STOP;
        menu++;
        Sleep(50);
    }
    else if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')) {
        dr = STOP;
        menu--;
        Sleep(50);
    }

    if (menu <= -1) {
        menu = 1;
    }
    else if (menu >= 3) {
        menu = 0;
    }

}
void setup() {
   
    dr = STOP;
    x = rand() % width;
    y = rand() % height;
    targetX = rand() % width;
    targetY = rand() % height;
    negativeX = rand() % width;
    negativeY = rand() % height;
    while (x == targetX==negativeX && y == targetY==negativeY) {
        x = rand() % width;
        y = rand() % height;
        targetX = rand() % width;
        targetY = rand() % height;
        negativeX = rand() % width;
        negativeY = rand() % height;
    }
    score = 0;

}
void window() {
    system("cls");
    for (int i = 0; i < width; i++) {
        cout << "*";
    }
    cout << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0 || j == width - 1) {
                cout << "*";
            }
            else if (i == y && j == x) {
                cout << "S";
            }
            else if (targetX == j && targetY == i) {
                cout << "0";
            }
            else if (negativeX == j && negativeY == i) {
                cout << "X";
            }
            else {
                bool tail = false;
                for (int k = 0; k < length; k++) {
                    if (j == tailX[k] && i == tailY[k]) {
                        cout << "s";
                        tail = true;
                    }
                }
                if (tail == false) cout << " ";
            }
        }
        cout << endl;
    }
    for (int i = 0; i < width; i++) {
        cout << "*";
    }
    cout << endl;
    cout << "Score:" << score;
}
void input() {
    if (mode == START) {
        if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A') && dr != RIGHT) {
            dr = LEFT;
        }
        else if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D') && dr != LEFT) {
            dr = RIGHT;
        }
        else if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S') && dr != UP) {
            dr = DOWN;
        }
        else if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W') && dr != DOWN) {
            dr = UP;
        }
        else if (GetAsyncKeyState(VK_RETURN)) {
            return;
        }
    }
    
}
void program() {
    fx = tailX[0];
    fy = tailY[0];
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < length; i++) {
        sx = tailX[i];
        sy = tailY[i];
        tailX[i] = fx;
        tailY[i] = fy;
        fx = sx;
        fy = sy;
        while (tailX[i] == targetX && tailY[i] == targetY) {
            targetX = rand() % width;
            targetY = rand() % height;
        }
        while (tailX[i] == negativeX && tailY[i] == negativeY) {
            negativeX = rand() % width;
            negativeY = rand() % height;
        }
        }
    switch (dr)
    {
    case UP:
        y -= speed;
        break;
    case DOWN:
        y += speed;
        break;
    case LEFT:
        x -= speed;
        break;
    case RIGHT:
        x += speed;
        break;
    }
    if (x <= 0 || x >= width - 1 || y < 0 || y > height - 1) {
        game = false;
    }
    for (int i = 0; i < length; i++) {
        if (x == tailX[i] && y == tailY[i]) {
            Gameover();
        }
    }
    if (x == targetX && y == targetY) {
        targetX = rand() % width;
        targetY = rand() % height;
        score += 1;
        length++;
    }
    if (x == negativeX && y == negativeY) {
        negativeX = rand() % width;
        negativeY = rand() % height;
        score -= 1;
        length--;
        if (score < 0) Gameover();
       
    }
}
int main()
{
        game_setup();
        while (game == true) {
            if (mode == MAIN) {
                MainMenu();
            }
            else if (mode == START) {
                setup();
                while (mode == START) {
                    window();
                    input();
                    program();
                    Sleep(10);
                }
            }
          
        }
        
        return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
