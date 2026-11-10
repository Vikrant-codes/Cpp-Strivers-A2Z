/*
Leetcode - 48. Rotate Image : Medium

You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).

You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. 
DO NOT allocate another 2D matrix and do the rotation.

Examples :-

Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[7,4,1],[8,5,2],[9,6,3]]

Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]

Constraints :-
• n == matrix.length == matrix[i].length
• 1 <= n <= 20
• -1000 <= matrix[i][j] <= 1000
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach (Using an auxiliary matrix): Time Complexity : O(n²) __ Space Complexity : O(n²)
/*
Instead of trying to rearrange elements in the original matrix directly, 
we can create a temporary matrix and place each element at its correct position after rotation.

For a 90-degree clockwise rotation:
- The element at position (i, j) moves to position (j, n-1-i).

So, we can traverse the original matrix and place each element at its new position in the temporary matrix.

>> Complexity Analysis
- Time Complexity: O(n²) — We traverse all `n²` elements once.
- Auxiliary Space: O(n²) — We create a temporary matrix of the same size.
*/
void rotateNaive(vector<vector<int>>& matrix) {
    int n = matrix.size();

    vector<vector<int>> temp(n, vector<int>(n));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            temp[j][n - 1 - i] = matrix[i][j];
        }
    }

    matrix = temp;
}

// Optimal Approach: Time Complexity : O(n²) __ Space Complexity : O(1)
/*
We can achieve the same rotation without using an auxiliary matrix.
The key observation is that a 90-degree clockwise rotation can be performed using two operations:
1. Transpose the matrix.
2. Reverse every row.

Step 1: Transpose the matrix
Transposing means converting rows into columns and columns into rows.
In other words: matrix[i][j] ↔ matrix[j][i]

For example:

Before transpose
1  2  3
4  5  6
7  8  9

After transpose
1  4  7
2  5  8
3  6  9

Notice that we only need to swap elements across the main diagonal.

Step 2: Reverse every row
After transposing, simply reverse each row.

After transpose
1  4  7
2  5  8
3  6  9

After reversing rows
7  4  1
8  5  2
9  6  3

This gives us the required 90-degree clockwise rotation!

Complexity Analysis
-> Time Complexity: O(n²)
  - Transposition takes O(n²).
  - Reversing all rows takes O(n²).
-> Auxiliary Space: O(1) — Both operations modify the original matrix in-place.
*/
void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();

    // Step 1: Transpose the matrix
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }

    // Step 2: Reverse each row
    for(int i = 0; i < n; i++) {
        reverse(matrix[i].begin(), matrix[i].end());
    }
}

// GFG Variant
/*
GFG - Rotate by 90 degree : Medium

Given a square matrix mat[][]. 
The task is to rotate it by 90 degrees in an anti-clockwise direction without using any extra space. 

Examples :-

Input: mat[][] = [[0, 1, 2], [3, 4, 5], [6, 7, 8]] 
Output: [[2, 5, 8], [1, 4, 7], [0, 3, 6]]

Input: mat[][] = [[1, 2], [3, 4]]
Output: [[2, 4], [1, 3]]

Constraints :-
• 1 ≤ mat.size() ≤ 102
• 0 ≤ mat[i][j] ≤ 103
• mat[i].size() = mat.size()
*/

// For anti-clockwise rotation, Transpose the matrix → Reverse each column.
// Time Complexity : O(n²) __ Space Complexity : O(1)
void rotateMatrix(vector<vector<int>>& mat) {
    int n = mat.size();
    
    // Step - 1 : Transpose
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(mat[i][j], mat[j][i]);
        }
    }
    
    // Step - 2 : Reverse each column
    for (int col = 0; col < n; col++) {
        
        int i = 0, j = n - 1;
        
        while (i < j) {
            swap(mat[i][col], mat[j][col]);
            
            i++; j--;
        }
    }
}

int main() {
    return 0;
}