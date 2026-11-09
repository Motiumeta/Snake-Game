#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>

using namespace std;

void clear(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

string space = "   ";
string head = " @ ";
string tail = " X ";
string border = " X ";
string food = " x ";

int row = 17;
int col = 17;
string matrix[17][17]; // The Main Grid

int coor[17*17][2]; // Stores the Coordinates of the tails
int tails = 0;
int score = 0;
int speed = 700;

char input = 77; // Initially the snake starts to go right
int ranNum1;  // x Coordinate for Food
int ranNum2;  // y Coordinate for Food

bool paused = false;


int xCoor = col/2;  // Starting X coordinate Point of The head (The Center)
int yCoor = row/2;  // Starting y coordinate Point of The head (The Center)


void printMatrix(){     // Print the Main Grid or Board
    for(int i = 0; i < col + 2; i++){
        cout << border;
    }
    cout << endl;

    for(int i = 0; i < row; i++){
        cout << border;
        for(int j = 0; j < col; j++){
            cout << matrix[i][j];
        }
        cout << border;
        cout << endl;
    }
    for(int i = 0; i < col + 2; i++){
        cout << border;
    }
    cout << endl;
}

void generateFood(){

    while(true){
        ranNum1 = rand() % col;
        ranNum2 = rand() % row;

        if(matrix[ranNum2][ranNum1] == space){
            matrix[ranNum2][ranNum1] = food;
            break;
        }
    }
}



int main()
{
    srand(time(0));

    for(int i = 0; i < row; i++){       // Fill all the Coordinates with Space
        for(int j = 0; j < col; j++){
            matrix[i][j] = space;
        }
    }

    coor[0][0] = 0;
    coor[0][1] = 0;
    generateFood();
    int in;
    while(true){
        if(kbhit()){ // Take Input from User To assign the Direction

            unsigned char before;
            in = getch();
            if(paused){
                continue;
            }


            if(in == 224 || in == 0){
                before = input;
                in = getch();
                if(in == 72 || in == 80 || in == 75 || in == 77) {
                    if(in == 72 && before == 80 || in == 80 && before == 72 || in == 75 && before == 77 ||in == 77 && before == 75) continue;

                    input = in;
                }
            }
            if(in == 43){
                speed -= 10;
            }
            else if(in == 45){
                speed += 10;
            }

        }

        if(in == 112){
            paused = true;
        }
        if(in == 114){
            paused = false;
        }
        if(paused){
            continue;
        }
        matrix[yCoor][xCoor] = space;
        for(int i = 0; i < tails; i++){
            matrix[coor[i][1]][coor[i][0]] = space;
        }

        for(int i = tails + 1; i >= 0; i--){
            coor[i + 1][0] = coor[i][0];
            coor[i + 1][1] = coor[i][1];
        }
        coor[0][0] = xCoor;
        coor[0][1] = yCoor;

        if(input == 77){
            xCoor += 1;
        }
        else if(input == 80){
            yCoor += 1;
        }
        else if(input == 75){
            xCoor -= 1;
        }
        else if(input == 72){
            yCoor -= 1;
        }

        if(xCoor == ranNum1 && yCoor == ranNum2){   // When The Food is Eaten
            score++;
            tails++;
            matrix[ranNum2][ranNum1] = head;
            speed -= 10;
        }

        if(xCoor < 0 || xCoor >= col){
            cout << "Game Over";
            Sleep(1000);
            break;
        }
        if(yCoor < 0 || yCoor >= row){
            cout << "Game Over";
            Sleep(1000);
            break;
        }
        matrix[yCoor][xCoor] = head;
        for(int i = 0; i < tails; i++){
            matrix[coor[i][1]][coor[i][0]] = tail;
        }
        if(matrix[yCoor][xCoor] == tail){
            cout << "Game Over";
            Sleep(1000);
            break;
        }
        if(xCoor == ranNum1 && yCoor == ranNum2){
            generateFood();
        }

        clear();
        printMatrix();
        cout << "Score: " << score << endl;
        cout << "Speed: " << 700 - speed << endl;
        cout << "-------------------" << endl;
        cout << "Guide Lines" << endl;
        cout << "'+' - To Speed Up" << endl;
        cout << "'-' - To Slow Down" << endl;
        cout << "'p' - To Pause" << endl;
        cout << "'r' - To Resume" << endl;
        Sleep(speed);
    }
    return 0;
}












