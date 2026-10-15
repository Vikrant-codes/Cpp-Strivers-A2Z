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
 
// My solution: Time Complexity : O(n² ∙ n!) __ Space Complexity : O(n³)

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


// Striver's Naive Solution: Time Complexity : O(n² ∙ n!) __ Space Complexity : O(n²)

/*
>> Intuition

The idea is to place queens column by column, ensuring that every column contains exactly one queen. 
For the current column, we try placing a queen in each row where it is safe, 
and recursively explore the possibilities for the next column. 
Once a recursive call finishes, we remove the queen and try the next row in the current column. 
This allows us to explore different arrangements without permanently affecting other branches.

Before placing a queen, we check whether its position is safe by looking at the 
left row, upper-left diagonal, and lower-left diagonal. 
We only need to check these directions because we process columns from left to right, 
meaning all previously placed queens are in earlier columns. 
The current column and the columns to its right do not contain any queens yet, 
so checking those directions is unnecessary.

>> Complexity Analysis

-> Time Complexity:  O(n² ∙ n!)
At each recursive call, we iterate through up to n rows to find a safe position. 
For each position, isSafeToPlace() takes O(n) time in the worst case because it scans the row and diagonals. 
The search explores up to O(n!) candidate arrangements, giving an overall upper bound of O(n² ∙ n!).

-> Space Complexity: O(n²) auxiliary space
The board occupies O(n²) space, 
while the recursion stack has a maximum depth of O(n), as we place one queen per column. 
Since the board is modified in place and restored during backtracking, 
we do not create separate board copies for each recursive call. 

Hence, the auxiliary space complexity is O(n^2), excluding the output. 
Storing S valid solutions requires an additional O(S ∙ n²) space.
*/

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


// Striver's Optimal Solution: Time Complexity : O(n ∙ n!) __ Space Complexity : O(n²)

/*
>> Intuition

In the previous approach, before placing a queen, 
we traversed the row and both diagonals to check whether the position was safe. 
Each safety check could take O(n) time.

We optimize this by using three hash arrays to track occupied rows and diagonals, 
allowing us to check whether a position is safe in O(1) time.

- leftRow[row]: tells us whether a queen already occupies the given row.
- lowerDiagonal[row + col]: tells us whether a queen occupies the same lower-left to upper-right diagonal.
- upperDiagonal[n - 1 + col - row]: tells us whether a queen occupies the same upper-left to lower-right diagonal.

When placing a queen, we check these three arrays. If all three entries are 0, the position is safe. 
We place the queen, mark the corresponding entries as 1, and recursively try the next column. 
When backtracking, we remove the queen and reset those entries to 0.

This avoids repeatedly traversing the board to check safety, reducing each safety check from O(n) to O(1).

>> Why these diagonal indices?

Consider a 4 x 4 board. Rows and columns are indexed from 0 to 3.

1. Lower diagonal: row + col
Cells on the same diagonal have the same row + column.

     0  1  2  3
    -----------
  0 |0  1  2  3
  1 |1  2  3  4
  2 |2  3  4  5
  3 |3  4  5  6

Each cell shows `row + col`. Equal values identify the same diagonal.
For example, the cells (0,3), (1,2), (2,1), and (3,0) all have a sum of 3. They lie on the same diagonal.
Therefore, row + col uniquely identifies a diagonal of this orientation. 
Its possible values range from 0 to 2n-2, so we need 2n-1 entries.

2. Upper diagonal: n - 1 + col - row
Cells on the same diagonal have the same col − row. We add n − 1 to avoid negative indices.

     0  1  2  3
    -----------
  0 |3  4  5  6
  1 |2  3  4  5
  2 |1  2  3  4
  3 |0  1  2  3

Each cell shows n − 1 + col − row, with n = 4.
For example, the cells (0,0), (1,1), (2,2), and (3,3) all have an index of 3. They lie on the same diagonal.

The expression col - row is constant along this diagonal, but it can be negative. 
Adding n - 1 shifts the range from -(n-1) to (n-1) into valid array indices from 0 to (2n-2).

In short: each diagonal gets a unique index, and every cell belonging to that diagonal uses the same index. 
We can therefore check diagonal conflicts with a simple array lookup instead of scanning the board.

>> Complexity Analysis

-> Time Complexity: O(n ∙ n!)
Since each safety check takes O(1) time using the three hash arrays, we avoid the O(n) traversal required in the previous approach. 
The algorithm explores possible queen placements through backtracking, with at most O(n!) candidate arrangements to explore. 
Each recursive call also iterates through up to n rows, giving an overall upper bound of O(n ∙ n!).

-> Space Complexity: O(n²) auxiliary space
The chessboard occupies O(n²) space. 
The three hash arrays together require O(n) + O(2n-1) + O(2n-1) space, 
and the recursion stack has a maximum depth of O(n). 
Therefore, the auxiliary space complexity is O(n²), dominated by the board. 
Additionally, storing S valid solutions requires O(S ∙ n²) output space.
*/

void recSolve(int col, int n, vector<string>& board, vector<vector<string>>& ans, 
    vector<int>& leftRow, vector<int>& upperDiagonal, vector<int>& lowerDiagonal) {

    if (col == n) {
        ans.push_back(board);
        return;
    }

    for (int row = 0; row < n; row++) {
        // place queen only if it is safe to place
    
        // we can also use the condition: leftRow[row] + lowerDiagonal[row+col] + upperDiagonal[n-1+col-row] == 0 
        if (leftRow[row] == 0 && lowerDiagonal[row + col] == 0 && upperDiagonal[n-1 + col - row] == 0) {
            // place the queen
            board[row][col] = 'Q';
            // update in hash arrays
            leftRow[row] = 1;
            lowerDiagonal[row + col] = 1;
            upperDiagonal[n-1 + col - row] = 1;
    
            // recursive call to place queens in next column
            recSolve(col + 1, n, board, ans, leftRow, upperDiagonal, lowerDiagonal);
    
            // undo the changes (unplace the queen & undo the changes to hash arrays)
            board[row][col] = '.';
            leftRow[row] = 0;
            lowerDiagonal[row + col] = 0;
            upperDiagonal[n-1 + col - row] = 0;
        }
    }
}

vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> ans;

    vector<string> board(n);
    string s(n, '.');
    for (int i = 0; i < n; i++) {
        board[i] = s;
    }
    
    vector<int> leftRow(n), upperDiagonal(2*n-1), lowerDiagonal(2*n-1);
    
    recSolve(0, n, board, ans, leftRow, upperDiagonal, lowerDiagonal);
    
    return ans;
}

// GFG - N-Queen Problem
/*
GFG - N-Queen Problem : Hard

The N-Queens puzzle is the problem of placing N queens on an N * N chessboard such that no two queens attack each other. 
Two queens attack each other if they are placed in the same row, the same column, or the same diagonal.

Given an integer n representing the number of queens, find all distinct solutions to this puzzle. 
Each solution should be represented as an array of size n, where the ith element (1-based indexing) 
denotes the column position of the queen placed in the ith row.

Note: You may return the solutions in any order.

Examples :-

Input: n = 1 __ Output: [1]
Explanation: Only one queen can be placed in the single cell available.

Input: n = 4 __ Output: [[2, 4, 1, 3], [3, 1, 4, 2]]
Explanation: There are 2 possible solutions for n = 4.

Input: n = 3 __ Output: []
Explanation: There are no possible solutions for n = 3.

Constraints :-
• 1 ≤ n ≤ 10
*/

void solvePuzzle(
    int row, int n, vector<vector<int>>& ans, vector<int>& pos,
    vector<int>& btmCol, vector<int>& btmLeftDiagonal, vector<int> btmRightDiagonal
) {
    
    if (row == n) {
        ans.push_back(pos);
        return;
    }
    
    for (int col = 0; col < n; col++) {
        
        if (btmCol[col] == 0 && btmLeftDiagonal[row + col] == 0 && 
        btmRightDiagonal[n - 1 + col - row] == 0) {
            
            pos.push_back(col + 1);     // 1-based indexing, so add 'col+1' as the position
            btmCol[col] = 1;
            btmLeftDiagonal[row + col] = 1;
            btmRightDiagonal[n - 1 + col - row] = 1;
            
            solvePuzzle(row + 1, n, ans, pos, btmCol, btmLeftDiagonal, btmRightDiagonal);
            
            pos.pop_back();
            btmCol[col] = 0;
            btmLeftDiagonal[row + col] = 0;
            btmRightDiagonal[n - 1 + col - row] = 0;
            
        }
    }
}

vector<vector<int>> nQueen(int n) {
    vector<vector<int>> ans;
    vector<int> pos;
    
    vector<int> btmCol(n), btmLeftDiagonal(2*n-1), btmRightDiagonal(2*n-1);
    
    solvePuzzle(0, n, ans, pos, btmCol, btmLeftDiagonal, btmRightDiagonal);
    
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
