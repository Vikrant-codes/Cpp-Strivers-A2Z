#include <iostream>
#include <cstdlib>   // rand, srand
#include <ctime>     // time
#include <cctype>    // toupper
using namespace std;

char grid[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
char grid_pos[3][3] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };

void displayGrid(char board[3][3]) {
    cout << '\n';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << " " << board[i][j] << " ";
            if (j < 2) 
                cout << '|';
        }
        cout << '\n';
        if (i < 2) 
            cout << "-----------\n";
    }
    cout << '\n';
}

bool checkWin(char p) {
    // check rows
    if (grid[0][0] == p && grid[0][1] == p && grid[0][2] == p) return true;
    if (grid[1][0] == p && grid[1][1] == p && grid[1][2] == p) return true;
    if (grid[2][0] == p && grid[2][1] == p && grid[2][2] == p) return true;

    // check cols
    if (grid[0][0] == p && grid[1][0] == p && grid[2][0] == p) return true; 
    if (grid[0][1] == p && grid[1][1] == p && grid[2][1] == p) return true; 
    if (grid[0][2] == p && grid[1][2] == p && grid[2][2] == p) return true;
    
    // check diagonals 
    if (grid[0][0] == p && grid[1][1] == p && grid[2][2] == p) return true;
    if (grid[0][2] == p && grid[1][1] == p && grid[2][0] == p) return true;

    return false;
}

int main() {
    cout << "--- Tic-Tac-Toe Game ---\n\n";

    cout << "The cell positions for the grid is in following manner --";
    displayGrid(grid_pos);

    char mark = ' ';

    while (mark != 'X' && mark != 'O') {
        cout << "Who is gonna play first? 'X' or 'O' : ";
        cin >> mark;
        mark = toupper(mark);
    }

    for (int i = 0; i < 9; i++) {
        int pos, row, col;
        do {
            cout << "Player " << mark << " select a valid (1-9) & vacant position : ";
            cin >> pos;
            row = (pos - 1) / 3;
            col = (pos - 1) % 3;
        } while (pos < 1 || pos > 9 || grid[row][col] != ' ' );

        grid[row][col] = mark;

        displayGrid(grid);

        if (checkWin(mark)) {
            cout << "Player " << mark << " won !!\n";
            break;
        }
        else if (i == 8)
            cout << "It's a draw !!\n";
    
        mark = (mark == 'X') ? 'O' : 'X';           // flip the mark for next player's turn
    }

    return 0;
}