/*
Leetcode - 54. Spiral Matrix : Medium

Given an m x n matrix, return all elements of the matrix in spiral order.

Examples :-

Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,3,6,9,8,7,4,5]

1 2 3
4 5 6 ----> Spiral Order : 1 2 3 6 9 8 7 4 5
7 8 9

Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]

Constraints :-
• m == matrix.length
• n == matrix[i].length
• 1 <= m, n <= 10
• -100 <= matrix[i][j] <= 100
*/

#include <bits/stdc++.h>
using namespace std;

// Spiral Order Traversal Simulation: Time Complexity : O(mn) __ Space Complexity : O(1)
/*
Spiral Traversal of Matrix elements means: 
1. Traverse the first row from left to right.
2. Traverse the last column from top to bottom.
3. Traverse the last row from right to left.
4. Traverse the first column from bottom to top.
Repeat this process for the remaining inner matrix until all elements have been visited.

>> Approach — Boundary traversal
The simplest way to solve this is to maintain four boundaries:
- top — first unvisited row.
- bottom — last unvisited row.
- left — first unvisited column.
- right — last unvisited column.

Initially:
    top = 0;
    bottom = m - 1;
    left = 0;
    right = n - 1;

We traverse the matrix in four directions, shrinking the boundaries after each traversal.

Traversal order:
1. Left to right: traverse matrix[top][left...right], then increment top.
2. Top to bottom: traverse matrix[top...bottom][right], then decrement right.
3. Right to left: traverse matrix[bottom][right...left], then decrement bottom.
4. Bottom to top: traverse matrix[bottom...top][left], then increment left.
Repeat while top <= bottom and left <= right.

>> Important edge case

After completing the first two traversals, the remaining matrix might have only one row or one column.

Therefore, before traversing right to left, check:
    if(top <= bottom)

And before traversing bottom to top, check:
    if(left <= right)

These checks prevent visiting elements more than once.

>> Complexity Analysis
- Time Complexity: O(m × n) — Every matrix element is visited exactly once.
- Auxiliary Space: O(1) — Only four boundary variables are used, excluding the output vector.
- Output Space: O(m × n) — We store all matrix elements in ans.
*/

vector<int> spiralOrder(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();

    int top = 0, bottom = m - 1;
    int left = 0, right = n - 1;

    vector<int> ans;

    while(top <= bottom && left <= right) {

        // Left to right
        for(int j = left; j <= right; j++) {
            ans.push_back(matrix[top][j]);
        }
        top++;

        // Top to bottom
        for(int i = top; i <= bottom; i++) {
            ans.push_back(matrix[i][right]);
        }
        right--;

        // Right to left
        // this condition helps handle the case when only one row was left for traversal 
        if(top <= bottom) {
            for(int j = right; j >= left; j--) {
                ans.push_back(matrix[bottom][j]);
            }
            bottom--;
        }

        // Bottom to top
        // this condition helps handle the case when only one col was left for traversal 
        if(left <= right) {
            for(int i = bottom; i >= top; i--) {
                ans.push_back(matrix[i][left]);
            }
            left++;
        }
    }

    return ans;
}

int main() {
    return 0;
}