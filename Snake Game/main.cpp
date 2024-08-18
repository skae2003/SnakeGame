// SnakeGame - Version 03
// Samuel Edwards
// Original code by N. Vitanovic
// see his YouTube video here: https://bit.ly/29WZ5Ml
//
// Change log
// 24/1/23
// - Changed format to Google
// - Added more comments above functions
// - Created new function to simplify the code within the advance game function
// 25/1/23
// - added yes or no to continue
// 2/2/23
// - changed nTail to tailSize
// - made fruitX and fruitY into arrays
// - added select difficulty function
// - added a pause button
// - added option for multiple fruits
// - made user input case insensitive
// - added printInstruction function
// - added speed selector (OPTIONAL) allows the user to practice the game at a slower pace and work their way up.

#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, score;
int tailX[100], tailY[100], fruitX[5], fruitY[5];
int tailSize, fruitAmnt, difficulty, speed;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;

// Gets the amount of fruit the user would like to have
// Uses the number to limit the amount of times certain for loops repeat
void getFruitAmount() {
fruitAmnt = 0;
    while((fruitAmnt < 1) || (fruitAmnt > 5)){
        cout << "Please enter the amount of fruit you would like to play with (1-5): ";
        cin >> fruitAmnt;
        cin.clear();
        cin.ignore();
    }
}

void Setup() {
    int i;
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    tailSize = 0;
    for (i = 0; i < fruitAmnt; ++i){
    fruitX[i] = rand() % width;
    fruitY[i] = rand() % height;
    }
    score = 0;
}

// Draws snake position as well as fruit position
// Also draws the border of the game
void DrawSnakeFruit() {

    system("cls"); //system("clear");
    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY[0] && j == fruitX[0])
                cout << "F";
            else if (i == fruitY[1] && j == fruitX[1] && fruitAmnt > 1)
                cout << "F";
            else if (i == fruitY[2] && j == fruitX[2] && fruitAmnt > 2)
                cout << "F";
            else if (i == fruitY[3] && j == fruitX[3] && fruitAmnt > 3)
                cout << "F";
            else if (i == fruitY[4] && j == fruitX[4] && fruitAmnt > 4)
                cout << "F";
            else {
                bool print = false;
                for (int k = 0; k < tailSize; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }


            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
}

void userInput() {

    if (_kbhit()) {

        switch (toupper(_getch())) {
        case 'A':
            dir = LEFT;
            break;
        case 'D':
            dir = RIGHT;
            break;
        case 'W':
            dir = UP;
            break;
        case 'S':
            dir = DOWN;
            break;
        case 'X':
            gameOver = true;
            break;
        case 'P':
            dir = STOP;
            break;
        }

    }

}

// Allows snake tail to follow head
void snakeTailPlacement() {

    int prevX = tailX[0];
    int prevY = tailY[0];

    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < tailSize; i++) {

        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;

    }

}

// Works with user input function to move snake
void moveSnake(){

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

}

// Selects the difficulty or whether u can run into the wall or not
void selectDifficulty(){
difficulty = 0;

    while ((difficulty !=1) && (difficulty !=2)){
        cout << "Please select the difficulty (1 for easy 2 for hard): ";
        cin >> difficulty;
        cin.clear();
        cin.ignore();
    }

}

//if (x > width || x < 0 || y > height || y < 0)
//  gameOver = true;
void detectGameOver() {

if (difficulty == 1){
    if (x >= width) x = 0;
        else if (x < 0) x = width - 1;
        if (y >= height) y = 0;
        else if (y < 0) y = height - 1;

        for (int i = 0; i < tailSize; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }
else if (difficulty == 2){
    if (x >= width) gameOver = true;
        else if (x < 0) gameOver = true;
        if (y >= height) gameOver = true;
        else if (y < 0) gameOver = true;

        for (int i = 0; i < tailSize; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
}

}
// Checks if snake ate fruit
// Awards point and places new fruit if so
// If snake ate a fruit, add to tailSize
void detectFruit() {
int i;
for (i = 0; i < fruitAmnt; ++i){
    if (x == fruitX[i] && y == fruitY[i]) {
            score += 10;
            fruitX[i] = rand() % width;
            fruitY[i] = rand() % height;
            tailSize++;
        }

    }

}

void speedSelection() {
speed = 0;
    while(speed != 1 && speed != 2 && speed != 3){
        cout << "Please select a speed, 1-3 from slow to fast: ";
        cin >> speed;
        cin.clear();
        cin.ignore();
    }

    if (speed == 1) speed = 100;
    else if(speed == 2) speed = 50;
    else if (speed == 3) speed = 0.1;

}

void advanceTheGame() {
    snakeTailPlacement();
    moveSnake();
    detectGameOver();
    detectFruit();
}

bool wantToPlayAgain() {
  char answer;
  cout << "You Lost" << endl;
  cout << "Would you like to play again? (Y or N): ";
  cin >> answer;
  answer = toupper(answer);
  cin.ignore();

  if (answer == 'Y')
    return true;
  else if (answer == 'N')
    return false;
  else
    wantToPlayAgain();
}

void printInstructions(){

    cout << "W and S keys to move up and down respectively" << endl;
    cout << "A and D keys to move left and right respectively" << endl;
    cout << "Each fruit or F is worth 10 points"<< endl;
    cout << "The more fruit you eat, the longer your snake will grow" << endl;
    cout << "Easy mode will only end if you run into your tail" << endl;
    cout << "Hard mode will end if you run into the wall or your tail" << endl;

}

int main() {
    printInstructions();
    selectDifficulty();
    getFruitAmount();
    speedSelection();
    Setup();
    while (!gameOver) {
        DrawSnakeFruit();
        userInput();
        advanceTheGame();
        Sleep(speed); //sleep(10);
    }
    if(wantToPlayAgain()){
      system("cls");
      main();
    }
    else
      cout << "\nOK, thank you for playing.";
    return 0;
}
