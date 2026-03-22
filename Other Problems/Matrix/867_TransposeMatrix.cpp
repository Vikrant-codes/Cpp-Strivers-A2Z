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

// Time Complexity : O(n^2) __ Space Complexity : O(1)
/*
The matrix is not necessarily a square matrix. For a irregular matrix of size m x n. 
The tranpose would be of size n x m, having rows which were columns of original matrix. 
So, if an element was at indices (i, j) in original matrix then it would exist at index (j, i) in transpose. 
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

int main() {

    return 0;
}