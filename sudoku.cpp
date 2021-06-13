#include <iostream>
#include <string>
#include <iomanip>

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
    int columnCounter = 1;
    int rowCounter = 0;
    for(int i = 0; i < rows; i++) {
        cout << "["<< "";
        for(int j = 0; j < cols; j++) {
            if(j == cols-1) {
                cout << setw(3) << sudoBoard[index].val<< "";
                columnCounter = 0;
            }
            else if(columnCounter == 3) {
                cout << setw(3) << sudoBoard[index].val<< setw(2) << "]" << setw(2) << "[";
                columnCounter = 0;
            }
            else {
                cout << setw(3) << sudoBoard[index].val<< ",";
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


int verifySolutionRowsAndColumns(twoDArray *sudokuBoard, int *sudokuNumbers, verifyRowsAndColumns *dict) {
    //TODO, verify that the columns and rows has unique numbers(sudokuboard)
    int solutionStatus = 1;
    for(int i = 0; i < 9; i++) {
        
        //check rows
        if(solutionStatus == 1) {
            solutionStatus = 0; //if the number is in sudokuNumbers, then solutionStatus will be set to 1
            for(int j = 0; j < 9; j++) {
                if((sudokuBoard[i].val > 0) && (sudokuBoard[i].val == dict[j].num) && (dict[j].taken == 0)) {
                    dict[j].taken = 1;
                    solutionStatus = 1;
                }
            }
            if(solutionStatus == 0) {
                cout << "something wrong with the row verifier" << endl;
                return 0;
            }
            for(int k = 0; k < 9; k++) {
                    dict[k].taken = 0;
            }
        }
    }

    for(int j = 0; j < 81; j+=9) {
        //check columns
        if(solutionStatus == 1) {
            solutionStatus = 0; //if the number is in sudokuNumbers, then solutionStatus will be set to 1
            for(int k = 0; k < 9; k++) {
                if((sudokuBoard[j].val > 0) && (sudokuBoard[j].val == dict[k].num) && (dict[k].taken == 0)) {
                    dict[k].taken = 1;
                    solutionStatus = 1;
                }
            }
            if(solutionStatus == 0) {
                cout << "something wrong with the column verifier" << endl;
                return 0;
            }
            for(int l = 0; l < 9; l++) {
                    dict[l].taken = 0;
            }


        }
    }
    return 1;
    //TODO, verify each subboard (i.e. 3x3)
}

int verifySolution(twoDArray *sudokuBoard) {
    verifyRowsAndColumns *dict = new verifyRowsAndColumns[rows];
    int sudokuNumbers[] = {1,2,3,4,5,6,7,8,9};

    //put all possible sudokunumbers to the array and set taken to 0 which is equal to false (not taken)
    for(int i = 0; i < 9; i++) {
        dict[i].num = sudokuNumbers[i];
        dict[i].taken = 0;
    }
    //TODO, verify that the columns and rows has unique numbers(sudokuboard)
    return verifySolutionRowsAndColumns(sudokuBoard, sudokuNumbers, dict);
    //TODO, verify each subboard (i.e. 3x3)
}

int main() {

    cout << "Sudoku"<< "\n";
    twoDArray *sudokuBoard = createBoard();
    displayBoard(9, 9, sudokuBoard);
    for(;;){ // same meaning as while(true){, think of for(statement1; statement2; statement3) = for(;;) is without statements
        int x;
        int y;
        int num;

        cout << "Enter Y coordinate:  " << "\n";
        cin >> x; // or std::getline(std::cin, str);

        cout << "Enter X coordinate:  " << "\n";
        cin >> y; // or std::getline(std::cin, str);

        cout << "Enter a number between 1-9:  " << "\n";
        cin >> num; // or std::getline(std::cin, str);

        addNumberToBoard(x, y, sudokuBoard, num);
        displayBoard(9, 9, sudokuBoard);

        int sudokuBoard[] = {9,8,3,2,1,7,6,4,5,6,1,5,4,3,9,8,7,2,4,7,2,6,8,5,1,9,3,
                                7,6,4,5,2,3,9,1,8,1,5,8,9,4,6,3,2,7,3,2,9,8,7,1,5,6,4,
                                5,3,1,7,9,2,4,8,6,8,9,7,3,6,4,2,5,1,2,4,6,1,5,8,7,3,9};

        twoDArray  *sudoBoard = new twoDArray[9*9]; //9*9 (rows*columns)

        int sudokuBoardInit[] = {-1,-1,-1,2,-1,-1,-1,4,5,6,1,-1,4,3,-1,8,7,-1,-1,7,2,-1,-1,5,-1,-1,-1,
                                -1,6,4,5,-1,-1,9,-1,-1,-1,5,-1,-1,-1,6,3,-1,7,-1,-1,9,-1,7,1,-1,-1,4,
                                5,-1,1,-1,9,-1,4,-1,-1,8,-1,7,3,6,-1,2,-1,1,-1,-1,-1,-1,-1,8,-1,-1,9};

        int index = 0;
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                sudoBoard[index].x = i;
                sudoBoard[index].y = j;
                sudoBoard[index].val = sudokuBoard[index];
                if(sudokuBoard[index] == -1) {
                    sudoBoard[index].interchangeable = 1;
                }
                index++;
            }
        }
        int solution = verifySolution(sudoBoard);
        cout << solution << endl;
        // based on the input, do something.
    }


}


