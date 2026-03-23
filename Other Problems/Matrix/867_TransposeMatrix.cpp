/*
Leetcode - 867. Transpose Matrix

Given a 2D integer array matrix, return the transpose of matrix.
The transpose of a matrix is the matrix flipped over its main diagonal, switching the matrix's row and column indices.

Examples :-

Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[1,4,7],[2,5,8],[3,6,9]]

Input: matrix = [[1,2,3],[4,5,6]]
Output: [[1,4],[2,5],[3,6]]

Constraints :-
m == matrix.length __ n == matrix[i].length
1 <= m, n <= 1000
1 <= m * n <= 10^5
-10^9 <= matrix[i][j] <= 10^9
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(m*n) __ Space Complexity : O(m*n)
/*
The matrix is not necessarily a square matrix. 
For an irregular matrix (rectangular matrix) of size m x n, the transpose matrix would be of size n x m. 
The rows of original matrix becomes columns for the transpose matrix.
So, if an element was at indices (i, j) in original matrix then it would exist at index (j, i) in transpose. 
For the rectangluar matrix, we need to use extra space (new matrix) to store the transposed values. 
So, we simply iterate through each element mat[i][j] and copy its value at transpose[j][i].
*/
vector<vector<int>> transpose(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    vector<vector<int>> transpose(n, vector<int> (m));
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            transpose[j][i] = matrix[i][j];
        }
    } 
    return transpose;
}

// What if the given matrix was square matrix ?
/*
If it was a square matrix of size n x n, then we wouldn't have needed any extra space and 
could've directly get the transpose by changing values in original matrix (in-place).

Idea: Swap elements across the diagonal: a[i][j] ↔ a[j][i]

Since we know that to get transpose, we have to flip the values over its main diagonal (swap values),
we can simply iterate any one triangluar region (above or down the main diagonal) and 
swap its elements (mat[i][j]) values with the mat[j][i] to get the transpose matrix.

The code for that would've been : 

    vector<vector<int>> transpose(vector<vector<int>>& mat) {
        int n = mat.size();
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                swap(mat[i][j], mat[j][i]);
            }
        }
        return mat;
    }
*/

int main() {

    return 0;
}