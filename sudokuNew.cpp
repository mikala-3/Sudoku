#include <iostream>
#include <string>
#include <iomanip>

#include "sudoku.h"

using namespace std;

// N is the size of the 2D matrix   N*N
#define N 9


int sizeOfBoard = 81;
int rows = 9;
int cols = 9;
/* 
    Displays the sudokuboard, currently just in the terminal
*/
void displayBoard(int rows, int cols, int** sudoBoard) {

    int index = 0;
    int columnCounter = 1;
    int rowCounter = 0;
    for(int i = 0; i < rows; i++) {
        cout << "["<< "";
        for(int j = 0; j < cols; j++) {
            if(j == cols-1) {
                cout << setw(3) << sudoBoard[i][j] << "";
                columnCounter = 0;
            }
            else if(columnCounter == 3) {
                cout << setw(3) << sudoBoard[i][j] << setw(2) << "]" << setw(2) << "[";
                columnCounter = 0;
            }
            else {
                cout << setw(3) << sudoBoard[i][j] << ",";
            }


            columnCounter++;
            rowCounter++;
            index++;

        }
        if(rowCounter == 9*3) {
            rowCounter = 0;
            cout << setw(2) << "]" << setw(2) << "\n\n";    
        }
        else {
            cout << setw(2) << "]"<< "\n";    
        }
    } 
}

bool verifyNumInBoard(int row, int col, int** sudoBoard, int num) {


    //row
    for(int i = 0; i < N; i++) {
        if(sudoBoard[row][i] == num) {
            return false;
        }
    }

    //column
    for(int j = 0; j < N; j++) {
        if(sudoBoard[j][col] == num) {
            return false;
        }
    }

    //3x3 box
    int tempCol = 0;
    if(col < 3) {
        tempCol = 0;
    }
    else if(col > 5) {
        tempCol = 6;
    }
    else {
        tempCol = 3;
    }

    //3x3 box
    int tempRow = 0;
    if(row < 3) {
        tempRow = 0;
    }
    else if(row > 5) {
        tempRow = 6;
    }
    else {
        tempRow = 3;
    }

    for(int k = tempRow; k < tempRow+3; k++) {
        for(int l = tempCol; l < tempCol+3; l++) {
            if(sudoBoard[k][l] == num) {
                return false;
            }
        }
    }
    return true;
}

bool solveSudoku(int** sudoBoard, int row, int col) {
    //basecase 1, if we are at the last row(index 8) and column is "outside" from the array, then we stop backtracking
    if(row == 8 && col == 9) {
        return true;
    }

    //basecase 2, if column is at the last index which is 8, then we go to the next row.
    if(col == 9) {
        row++;
        col = 0;
    }

    if (sudoBoard[row][col] > 0) {
        return solveSudoku(sudoBoard, row, col + 1);
    }

    for(int i = 1; i < N+1; i++) {

        if(verifyNumInBoard(row, col, sudoBoard, i)) {
            sudoBoard[row][col] = i;

            if(solveSudoku(sudoBoard, row, col + 1)) {
                return true;
            }
        }
        sudoBoard[row][col] = 0;
    }
    return false;
}
/*
    create sudokuboard, 9x9 and display the board
*/
int** createBoard(int** sudoBoard) {

    
    int grid[N][N] = { { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
                       { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
                       { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
                       { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
                       { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
                       { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
                       { 0, 0, 5, 2, 0, 6, 3, 0, 0 } };
    
    for(int i = 0; i < N; i++) {
            sudoBoard[i] = new int[N];
        for(int j = 0; j < N; j++) {
            sudoBoard[i][j] = grid[i][j];
        }
    }

    return sudoBoard;

}




int main() {

    cout << "Sudoku"<< "\n";
    int** sudoBoard = new int*[N];
    sudoBoard = createBoard(sudoBoard);
    solveSudoku(sudoBoard, 0, 0);
    displayBoard(9, 9, sudoBoard);
}