/*
Leetcode - 52. N-Queens II : Hard

The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
Given an integer n, return the number of distinct solutions to the n-queens puzzle.

Examples :-

Input: n = 4 __ Output: 2
Explanation: There are two distinct solutions to the 4-queens puzzle as shown.

Input: n = 1 __ Output: 1

Constraints :-
• 1 <= n <= 9
*/

#include<bits/stdc++.h>
using namespace std;

/*
We can solve this using Backtracking, just like N-Queens (Leetcode 51). 
The difference is that here we don't need to store or return the actual board configurations. 
We only need to count the number of valid arrangements.
*/

// Optimal Approach: Time Complexity : O(n!) __ Space Complexity : O(n)
/*
Complexity of optimized solution:
- Time: O(n!) — There are at most `n!` possible arrangements, 
  and each safety check takes O(1) time (using the three tracking arrays).
- Space: O(n) — three tracking arrays and recursion stack.
*/
int cnt = 0;

void solve(int n, int col, vector<int>& leftRow, vector<int>& upperDiagonal, vector<int>& lowerDiagonal) {
    if (col == n) {
        cnt++;
        return;
    }

    for (int row = 0; row < n; row++) {
        // if safe to place
        if (leftRow[row] == 0 && lowerDiagonal[row + col] == 0 && upperDiagonal[n-1 + col - row] == 0) {
            // place queen... mark in the tracking arrays for further safety checks
            leftRow[row] = 1;
            lowerDiagonal[row + col] = 1;
            upperDiagonal[n-1 + col - row] = 1;

            // recursive call for the next column placement
            solve(n, col + 1, leftRow, upperDiagonal, lowerDiagonal); 

            // undo the choice
            leftRow[row] = 0;
            lowerDiagonal[row + col] = 0;
            upperDiagonal[n-1 + col - row] = 0;
        }
    }
}

int totalNQueens(int n) {
    vector<int> leftRow(n), lowerDiagonal(2*n - 1), upperDiagonal(2*n - 1);
    solve(n, 0, leftRow, upperDiagonal, lowerDiagonal);
    return cnt;
}

int main() {
    return 0;
}