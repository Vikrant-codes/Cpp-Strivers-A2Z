/*
Leetcode - 3643. Flip Square Submatrix Vertically : Easy

You are given an m x n integer matrix grid, and three integers x, y, and k.
The integers x and y represent the row and column indices of the top-left corner of a square submatrix and 
the integer k represents the size (side length) of the square submatrix.
Your task is to flip the submatrix by reversing the order of its rows vertically.
Return the updated matrix.

Examples :-

Input: grid = [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]], x = 1, y = 0, k = 3
Output: [[1,2,3,4],[13,14,15,8],[9,10,11,12],[5,6,7,16]]
Explanation:
The diagram above shows the grid before and after the transformation.

Input: grid = [[3,4,2,3],[2,3,4,2]], x = 0, y = 2, k = 2
Output: [[3,4,4,2],[2,3,2,3]]
Explanation:
The diagram above shows the grid before and after the transformation.
 

Constraints:-
- m == grid.length
- n == grid[i].length
- 1 <= m, n <= 50
- 1 <= grid[i][j] <= 100
- 0 <= x < m
- 0 <= y < n
- 1 <= k <= min(m - x, n - y)
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(k/2 * k) __ Space Complexity : O(1)
/*
Use two pointers at the block's (sub-matrix's) top and bottom rows and swap their k columns pairwise until the pointers meet.
Use a pointer i to point to the top row and j to point to the bottom row.
Now traverse the k columns starting from column 'y' (columns of square sub-matrix) and swap values of both rows.
After traversal ends, increment i and decrement j to reverse the other rows of square submatrix.
*/
vector<vector<int>> reverseSubmatrix(vector<vector<int>>& grid, int x, int y, int k) {
    int i = x, j = x + k - 1;

    while (i < j) {
        // flip the submatrix rows
        for (int c = y; c < y + k; c++) 
            swap(grid[i][c], grid[j][c]);

        i++;
        j--;
    }

    return grid;
}

int main() {
    return 0;
}