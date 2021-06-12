#include <iostream>
#include <string>
#include "sudoku.h"

using namespace std;


/* 
    config for sudoku
*/

int sizeOfBoard = 81;
int rows = 9;
int cols = 9;
/* 
    Displays the sudokuboard, currently just in the terminal
*/
void displayBoard(int rows, int cols, twoDArray *sudoBoard) {

    int index = 0;
    for(int i = 0; i < rows; i++) {
        cout << "["<< "";
        for(int j = 0; j < cols; j++) {
            if(j == cols-1) {
                cout << sudoBoard[index].val<< "";
            }
            else {
                cout << sudoBoard[index].val<< ",";
            }
            index++;

        }
        cout << "]"<< "\n";    
    } 
}

void addNumberToBoard(int x, int y, twoDArray *sudoBoard, int input) {
    int index = 0;
    for(int i = 0; i < sizeOfBoard; i++) {
        if(x == sudoBoard[i].x) {
            if(y == sudoBoard[i].y) {
                if(sudoBoard[i].interchangeable == 1) {
                    cout << "You changed the value at the coordinates x:" << x << " and y:" << y << endl;
                    sudoBoard[i].val = input;
                }
                else {
                    cout << "You cannot change this value!" << endl;
                }
            }
        }
        else {
            i += 8;
        }
    }
}

/*
    create sudokuboard, 9x9 and display the board
*/
twoDArray* createBoard() {

    twoDArray  *sudoBoard = new twoDArray[9*9]; //9*9 (rows*columns)
    // int sudokuBoard[] = {8,2,7,1,5,4,3,9,6,9,6,5,3,2,7,1,4,8,3,4,1,6,8,9,7,5,2,
    //                 5,9,3,4,6,8,2,7,1,4,7,2,5,1,3,6,8,9,6,1,8,9,7,2,4,3,5,
    //                 7,8,6,2,3,5,9,1,4,1,5,4,7,9,6,8,2,3,2,3,9,8,4,1,5,6,7};

    int sudokuBoard[] = {9,8,3,2,1,7,6,4,5,6,1,5,4,3,9,8,7,2,4,7,2,6,8,5,1,9,3,
                            7,6,4,5,2,3,9,1,8,1,5,8,9,4,6,3,2,7,3,2,9,8,7,1,5,6,4,
                            5,3,1,7,9,2,4,8,6,8,9,7,3,6,4,2,5,1,2,4,6,1,5,8,7,3,9};

    int sudokuBoardInit[] = {-1,-1,-1,2,-1,-1,-1,4,5,6,1,-1,4,3,-1,8,7,-1,-1,7,2,-1,-1,5,-1,-1,-1,
                            -1,6,4,5,-1,-1,9,-1,-1,-1,5,-1,-1,-1,6,3,-1,7,-1,-1,9,-1,7,1,-1,-1,4,
                            5,-1,1,-1,9,-1,4,-1,-1,8,-1,7,3,6,-1,2,-1,1,-1,-1,-1,-1,-1,8,-1,-1,9};

    int index = 0;
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            sudoBoard[index].x = i;
            sudoBoard[index].y = j;
            sudoBoard[index].val = sudokuBoardInit[index];
            if(sudokuBoardInit[index] == -1) {
                sudoBoard[index].interchangeable = 1;
            }
            index++;
        }
    }

    return sudoBoard;

}

int main() {

    cout << "Sudoku"<< "\n";
    twoDArray *sudokuBoard = createBoard();
    displayBoard(9, 9, sudokuBoard);
    for(;;){ // same meaning as while(true){, think of for(statement1; statement2; statement3) = for(;;) is without statements
        int x;
        int y;
        int num;

        cout << "Enter X coordinate:  " << "\n";
        cin >> x; // or std::getline(std::cin, str);

        cout << "Enter Y coordinate:  " << "\n";
        cin >> y; // or std::getline(std::cin, str);

        cout << "Enter a number between 1-9:  " << "\n";
        cin >> num; // or std::getline(std::cin, str);

        addNumberToBoard(x, y, sudokuBoard, num);
        displayBoard(9, 9, sudokuBoard);
        // based on the input, do something
    }


}


