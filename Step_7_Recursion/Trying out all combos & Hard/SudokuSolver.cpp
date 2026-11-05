/*
Leetcode - 37. Sudoku Solver : Hard

Write a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy all of the following rules:

- Each of the digits 1-9 must occur exactly once in each row.
- Each of the digits 1-9 must occur exactly once in each column.
- Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.

The '.' character indicates empty cells.

Constraints :-
• board.length == 9
• board[i].length == 9
• board[i][j] is a digit or '.'.
• It is guaranteed that the input board has only one solution.
*/

#include <bits/stdc++.h>
using namespace std;

/*
The intuition behind Sudoku Solver using Backtracking is:

1. Find an empty cell: Traverse the Sudoku board and find a cell containing '.'.

2. Try possible digits: For that cell, try digits from 1 to 9, 
checking whether each digit is valid according to Sudoku rules:
- It must not already exist in the same row.
- It must not already exist in the same column.
- It must not already exist in the corresponding 3×3 subgrid.

3. Make a choice and explore: If a digit is valid, place it in the cell and 
recursively attempt to solve the remaining board.

4. Backtrack if necessary: If the recursive call fails to find a solution, 
undo the placement (restore '.') and try the next possible digit.

5. Base case: If no empty cells remain, the Sudoku is completely filled and a valid solution has been found.

>> Core intuition:
We solve the Sudoku one cell at a time by trying valid possibilities. 
Whenever a choice leads to a dead end, we undo that choice and explore another possibility.

Essentially, choose → explore → undo if unsuccessful.

The important thing to understand is that we aren't just filling empty cells; we're exploring different 
combinations of valid choices until we find a combination that solves the entire board.
*/

// Complexity Analysis
/*
>> Time Complexity: O(9^81)
- There are at most 81 cells, and for each empty cell, we try up to 9 possible digits.
- For every attempted digit, validity check takes O(1), since the board size is fixed.
- In the theoretical worst case, we could explore up to 9^81 combinations.

However, 9^81 is astronomically large and represents a very loose upper bound. 
In practice, the given Sudoku board is never completely empty; it already contains several pre-filled cells. 
These cells reduce the number of possibilities significantly.

Moreover, we are given that the Sudoku has exactly one valid solution, 
so the backtracking process eventually finds that solution without needing to enumerate every possible combination.

>> Space Complexity: O(81) = O(1)
- The recursion depth can go up to 81, since each recursive call processes one cell.
- No additional data structures are used.
Therefore, Auxiliary Space Complexity: O(81) = O(1) for a fixed 9 × 9 Sudoku board.

Note: If we generalize the board size to N × N, the recursion stack can take O(N²) space.
*/

// My Solution
bool isSafeToPlace(vector<vector<char>>& board, int row, int col, char val) {
    // check row
    for (int i = 0; i < 9; i++)
        if (board[row][i] == val)
            return false;

    // check col
    for (int i = 0; i < 9; i++) 
        if (board[i][col] == val)
            return false;

    // check sub-grid
    int subgrid_row = (row / 3) * 3;
    int subgrid_col = (col / 3) * 3;
    for (int i = subgrid_row; i < subgrid_row + 3; i++) {
        for (int j = subgrid_col; j < subgrid_col + 3; j++) {
            if (board[i][j] == val) {
                return false;
            }
        }
    }

    return true;
}

bool solve(vector<vector<char>>& board, int k) {
    if (k == 81) {
        return true;
    }

    int row = k / 9;
    int col = k % 9;
    
    if (board[row][col] != '.') {
        return solve(board, k + 1);
    }
    
    for (char ch = '1'; ch <= '9'; ch++) {
        if (isSafeToPlace(board, row, col, ch)) {
            board[row][col] = ch;
            if (solve(board, k + 1)) return true;
            
            board[row][col] = '.';      // undo the change
        }
    } 

    return false;
}

void solveSudokuMy(vector<vector<char>>& board) {
    solve(board, 0);
}

// Striver's Solution
bool isValid(vector<vector<char>>& board, int row, int col, char c) {
    for (int i = 0; i < 9; i++) {
        if (board[i][col] == c) 
            return false;

        if (board[row][i] == c)
            return false;
        
        if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c)
            return false;
    }

    return true;
}

bool fun(vector<vector<char>>& board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {

            if (board[i][j] == '.') {

                for (char c = '1'; c <= '9'; c++) {
                    if (isValid(board, i, j, c)) {
                        board[i][j] = c;
                        if (fun(board) == true) 
                            return true;
                        else 
                            board[i][j] = '.';
                    }
                }

                return false;
            }
        }
    }

    return true;
}

void solveSudoku(vector<vector<char>>& board) {
    fun(board);
}

int main() {
    return 0;
}