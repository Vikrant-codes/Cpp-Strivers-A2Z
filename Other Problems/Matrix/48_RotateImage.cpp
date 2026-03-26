/*
Leetcode - 48. Rotate Image : Medium

You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).
You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. 
DO NOT allocate another 2D matrix and do the rotation. 

Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[7,4,1],[8,5,2],[9,6,3]]

Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]

Constraints:

n == matrix.length == matrix[i].length
1 <= n <= 20
-1000 <= matrix[i][j] <= 1000
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach : Time Complexity : O(n^2) __ Space Complexity : O(1)
/*
💡 Idea (In-place, O(1) space)
Rotate matrix 90° clockwise in 2 steps:
1. Transpose the matrix
2. Reverse each row
*/
void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();
    // transpose the matrix

    for(int i=0; i<n; i++){
        for(int j=0; j<i; j++){
            swap(matrix[i][j], matrix[j][i]);
        }
    }
    
    // reverse each row
    for(int i=0; i<n; i++){
        reverse(matrix[i].begin(), matrix[i].end());
    }
}

// Same Approach (without using built-in reverse method)
void rotate(vector<vector<int>>& mat) {
    int n = mat.size();

    // transpose the matrix
    for(int i=0; i<n; i++){
        for(int j=0; j<i; j++){
            swap(mat[i][j], mat[j][i]);
        }
    }
    
    // reverse each row
    for(int i=0; i<n; i++){
        int l = 0, r = n-1;     // left & right pointers for swapping
        while (l < r) {
            swap(mat[i][l], mat[i][r]);
            l++; r--;
        }
    }
}

/*
Using this transpose + reverse row approach, we can derive a formula for rotated matrix.

In general =>
- transpose : T[i][j] = M[j][i]
- reverse row : R[i][j] = M[i][n-j-1]

Now, suppose M[i][j] is the actual element, then
- tranpose :- M[j][i]
- Reverse row :- M[j][n-i-1]          (columns are reversed, the element at jth position get swapped with the (n-j-1)th element)

Thus, mapping is: (i, j) → (j, n - 1 - i)
where, (i, j) is the mapping position in original matrix and 
       (j, n - 1 - i) is the corresponding position of (i, j) in rotated matrix.
This mapping is in respect to the original matrix element, i.e. original matrix (i, j) → rotated (j, n - i - 1).

Thus, rotated[j][n-i-1] = matrix[i][j]
    => rotated[a][n-b-1] = matrix[b][a]
or, rotated[i][j] = matrix[n-j-1][i]                (by putting, i = a and j = n-b-1 i.e. b = n-j-1)
So, in respect to rotated matrix element, element (i, j) → (n - j - 1, i).
Thus, mapping for rotated matrix element is : (i, j) → (n - j - 1, i).
*/

int main() {
    return 0;
}