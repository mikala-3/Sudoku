#include<iostream>

using namespace std;

/*
    struct for the 2d-array, stores x, y coordinates and the value.
*/
struct twoDArray {
    int x;
    int y;
    int val;
};

/* 
    Displays the sudokuboard, currently just in terminal view
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

/*
    create sudokuboard, 9x9 and display the board
*/
twoDArray* createBoard() {

    twoDArray  *sudoBoard = new twoDArray[9*9]; //9*9 (rows*columns)
    int sudokuBoard[] = {8,2,7,1,5,4,3,9,6,9,6,5,3,2,7,1,4,8,3,4,1,6,8,9,7,5,2,
                    5,9,3,4,6,8,2,7,1,4,7,2,5,1,3,6,8,9,6,1,8,9,7,2,4,3,5,
                    7,8,6,2,3,5,9,1,4,1,5,4,7,9,6,8,2,3,2,3,9,8,4,1,5,6,7};
    int index = 0;
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            sudoBoard[index].x = i;
            sudoBoard[index].y = j;
            sudoBoard[index].val = sudokuBoard[index];
            index++;
        }
    }

    return sudoBoard;

}

int main() {

    cout << "Sudoku"<< "\n";
    twoDArray *sudokuBoard = createBoard();
    displayBoard(9, 9, sudokuBoard);

}


