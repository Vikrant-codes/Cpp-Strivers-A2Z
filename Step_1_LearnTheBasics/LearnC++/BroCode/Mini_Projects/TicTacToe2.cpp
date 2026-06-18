#include <iostream>
#include <cstdlib>   // rand, srand
#include <ctime>     // time
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

bool isValidPos(int pos, int& row, int& col) {
    if (pos < 1 || pos > 9) 
        return false;
    row = (pos - 1) / 3;
    col = (pos - 1) % 3;

    return grid[row][col] == ' ';
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
    srand(time(0));         // to get random moves for computer
    
    cout << "--- Tic-Tac-Toe Game (Against computer) ---\n\n";
    
    cout << "The cell positions for the grid is in following manner --";
    displayGrid(grid_pos);

    char player = 'X';
    char computer = 'O';

    while(true) {
        // Player's turn
        int pos, row, col;
        do {
            cout << "Choose a valid (1-9) & vacant position to place your mark : ";
            cin >> pos;
        } while ( !isValidPos(pos, row, col) );

        grid[row][col] = player;

        cout << "Grid after player's turn \n";
        displayGrid(grid);

        if (checkWin(player)) {
            cout << "You win !! \n";
            break;
        }

        // check for Tie
        bool tie = true;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i][j] == ' ') {
                    tie = false;
                    i = 3;   // force exit outer loop
                    break;
                }
            }
        }
        if (tie) {
            cout << "It's a tie !!";
            break;
        }

        // Computer's turn
        int pos2, row2, col2;
        do {
            pos2 = rand() % 9 + 1;      // to get a random position between 1 to 9
        } while ( !isValidPos(pos2, row2, col2) );
        
        grid[row2][col2] = computer;

        cout << "Grid after computer's turn \n";
        displayGrid(grid);

        if (checkWin(computer)) {
            cout << "You lose !! \n";
            break;
        }
    }

    return 0;
}