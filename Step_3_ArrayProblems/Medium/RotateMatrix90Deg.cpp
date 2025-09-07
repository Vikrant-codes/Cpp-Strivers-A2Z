/*
Leetcode - 48 : Rotate Image : Medium

You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).
Example 1:
Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[7,4,1],[8,5,2],[9,6,3]]

You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. 
DO NOT allocate another 2D matrix and do the rotation.
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach :- Create a new matrix and fill it with the rotated values. Copy the new matrix values back to original matrix.
// Complexity Analysis : O(n^2) for both time and space complexity since we are using an extra matrix of size n*n.

void Rotate90BruteForce(vector<vector<int>> &mat) {
    int n = mat.size();
    vector<vector<int>> ans(n, vector<int>(n, 0)); 

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            ans[j][n-i-1] = mat[i][j];
        }
    }

    mat = ans; // Assign the new matrix to the original matrix
}


// Optimal Approach :- Time Complexity : O(n^2) __ Space Complexity : O(1)
// Approach :- Firstly do transpose of the matrix and then reverse each row of the transposed matrix . 

void Rotate90(vector<vector<int>> &mat) {
    int n = mat.size();

    // Transpose the matrix : swap mat[i][j] and mat[j][i]
    for(int i=0; i<n; i++) {
        for(int j=0; j<i; j++) {
            swap(mat[i][j], mat[j][i]);
        }
    }

    // Reverse each row of the matrix
    for(int i=0; i<n; i++) {
        reverse(mat[i].begin(), mat[i].end());
    }
}

int main() {
    vector<vector<int>> mat = { {1,2,3}, {4,5,6}, {7,8,9} };
    for(auto x : mat) {
        for (int y : x) cout << y << " ";
        cout << endl;
    }
    cout << endl;
    Rotate90(mat);
    for(auto x : mat) {
        for (int y : x) cout << y << " ";
        cout << endl;
    }
    return 0;
}