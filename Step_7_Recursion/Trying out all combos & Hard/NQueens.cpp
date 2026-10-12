/*
Leetcode - 51. N-Queens : Hard

The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order.

Each solution contains a distinct board configuration of the n-queens' placement, 
where 'Q' and '.' both indicate a queen and an empty space, respectively.

Examples :-

Input: n = 4
Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above

Input: n = 1
Output: [["Q"]] 

Constraints :-
• 1 <= n <= 9
*/

#include <bits/stdc++.h>
using namespace std;
 
// 😺 My solution
/*
>> Intuition & Approach

Seeing the problem, it is easy to guess that Backtracking is the only good way to solve this. 
But figuring out how to implement the backtracking solution is quite challenging itself.

We need to place n-queens on a n x n grid, so there must be a queen in every row & every column 
(since placing a queen in a row would block all the other positions in the row & similar for columns).

Since we are dealing with queens and chessboard type setup, we need a board / 2D-grid kind of data-structure 
where we can place the queens and try to recursively find solutions. 
We can thus use a vector/arraylist of strings to act as the 2D grid/chessboard.
I used a vector of string initialized with underscores ('_') to denote vacant characters.

Now, we can try placing queens at different indices of each row of grid 
(i.e. try placing queen at each col in a row) and whenever we place a queen, 
we block all those positions which can be attacked by this queen (in all 8 directions). 
So that when placing the later queens, we can simply check if the cell position is unblocked or not.

After placing a queen, we can recursively call the recursive-function for placing the queens in next row. 
We can use '.' characters to denote the blocked cells (since in the solution we can have either 'Q' or '.', 
we can use these same characters to mark a queen-placed cell or blocked cell).

>> But is it actually necesaary to block all 8 directions when placing a queen ?
The answer is no. Since we are placing the queen row by row, trying all positions from left to right (all column positions), 
so when we try placing a queen at [row, col] position, we don't need to block the positions from the top-left corner till [row, col]. 
We only need to block the remaining portion of the grid which includes the positions at bottom-left & bottom-right diagonal, 
positions to the right of [row, col] and positions to the bottom of [row, col].

When a queen is placed, we can try to place further queens in later rows and if a valid solution is found 
(all n queens placed, i.e., current rowNumber reaches n), we can add that solution to answer.

But there is a problem, when backtracking we must also undo the changes we made to the grid (undo the blocked cells), 
since it's not that easy/straight-forward to undo those changes, 
we can try using a separate grid for current queen placement and pass this grid to the recursive calls. 
This helps us make sure the actual grid passed to the current recusive function is not modified due to queen placement in a column.

>> Complexity

-> Time complexity: O(n² ∙ n!)
We place one queen per row, exploring possible column choices using backtracking. 
In the worst case, the search explores up to O(n!) candidate arrangements. 
For each placement, placeQueen() takes O(n^2) time because it copies the board and marks attacked cells. 
Hence, the overall time complexity is O(n² ∙ n!).

-> Space complexity: O(n³)
The recursion depth is at most O(n), and each recursive call maintains a board of size O(n²). 
Since each branch creates a separate board copy, the auxiliary space complexity is O(n ∙ n²) = O(n³). 
Additionally, storing all S valid solutions requires O(S ∙ n²) output space
*/

vector<string> placeQueen(vector<string> curr, int rowNo, int ind, int n) {
    // mark in row
    for (int i = ind + 1; i < n; i++) {
        curr[rowNo][i] = '.';
    }

    // mark in col
    for (int i = rowNo + 1; i < n; i++) {
        curr[i][ind] = '.';
    }
    
    // mark the bottom-left diagonal
    int a = rowNo + 1, b = ind - 1;
    while (a < n && b >= 0) {
        curr[a][b] = '.';
        a++; b--;
    }
    
    // mark the bottom-right diagonal
    a = rowNo + 1, b = ind + 1;
    while (a < n && b < n) {
        curr[a][b] = '.';
        a++; b++;
    }
    
    curr[rowNo][ind] = 'Q';     // place the queen
    
    return curr;
}

void solve(vector<vector<string>>& solutions, vector<string>& curr, int rowNo, int n) {
    if (rowNo == n) {
        solutions.push_back(curr);
        return;
    }

    for (int ind = 0; ind < n; ind++) {
        if (curr[rowNo][ind] == '.') continue;
    
        // else string's index position is vacant ('_'), place a queen 
    
        vector<string> queenPlacedGrid = placeQueen(curr, rowNo, ind, n);
    
        solve(solutions, queenPlacedGrid, rowNo + 1, n);
    
        curr[rowNo][ind] = '.'; 
    }
}

vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> solution;

    // declare & initialize a vector of string having blank/underscore characters ('_'), this would act as the n x n grid.

    vector<string> curr(n);

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         curr[i].push_back('_');
    //     }
    // }

    string s(n, '_');
    for (int i = 0; i < n; i++) {
        curr[i] = s;
    }

    solve(solution, curr, 0, n);

    return solution;
}


// Striver's Naive Solution

bool isSafeToPlace(int row, int col, vector<string>& board, int n) {
    // check upper diagonal
    int i = row, j = col;
    while (i >= 0 && j >= 0) {
        if (board[i][j] == 'Q') return false;
        i--; j--;
    }

    // check row
    i = row, j = col;
    while (i >= 0 && j >= 0) {
        if (board[i][j] == 'Q') return false;
        j--;
    }
    
    // check lower diagonal
    i = row, j = col;
    while (i < n && j >= 0) {
        if (board[i][j] == 'Q') return false;
        i++; j--;
    }
    
    return true;
}

void fun(int col, vector<string>& board, vector<vector<string>>& ans, int n) {
    if (col == n) {
        ans.push_back(board);
        return;
    }

    for (int row = 0; row < n; row++) {
        if (isSafeToPlace(row, col, board, n)) {
            board[row][col] = 'Q';      // place the queen
            fun(col + 1, board, ans, n);
            board[row][col] = '.';      // restore/undo the change
        }
    }
}

vector<vector<string>> solveNQueensStriver(int n) {
    vector<vector<string>> ans;

    vector<string> board(n);
    string s(n, '.');
    
    for (int i = 0; i < n; i++) {
        board[i] = s;
    }

    fun(0, board, ans, n);
    return ans;
}



int main() {
    int n = 4;

    vector<vector<string>> solution = solveNQueens(n);

    // Print all solutions

    for (int i = 0; i < solution.size(); i++) {
        cout << "-- Solution " << i+1 << " -- \n\n";

        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                cout << solution[i][j][k] << " ";
            }
            cout << "\n";
        } 

        cout << "\n\n";
    }

    return 0;
}
