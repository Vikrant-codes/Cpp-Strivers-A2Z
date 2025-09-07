/*
Leetcode - 54 : Spiral Matrix : Medium
Given an m x n matrix, return all elements of the matrix in spiral order.

Example - 
Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]  __  Output: [1,2,3,6,9,8,7,4,5]

1 2 3
4 5 6 ----> Spiral Order : 1 2 3 6 9 8 7 4 5
7 8 9
*/
#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(n*m) since each element of the matrix is traversed once
// Space Complexity : O(1) since no extra space is used except for the output vector which is not considered as extra space

vector<int> SpiralTraversal(vector<vector<int>> mat) {
    int n = mat.size();
    int m = mat[0].size();
    int top = 0, bottom = n-1;
    int left = 0, right = m-1;
    vector<int> ans;

    while (left <= right && top <= bottom) {
        // left to right traversal : the top row is traversed left to right --> elements are accessed as mat[top][i]
        for(int i=left; i<=right; i++) {
            ans.push_back(mat[top][i]);
        }
        top++;
        // top to bottom traversal : the right column is traversed top to bottom --> elements are accessed as mat[i][right]
        for(int i=top; i<=bottom; i++) {
            ans.push_back(mat[i][right]);
        }
        right--;
        // right to left traversal : the bottom row is traversed right to left --> elements are accessed as mat[bottom][i]
        // this traversal is done only when top <= bottom i.e. when there is at least a bottom row which isn't traversed yet 
        if (top <= bottom) {
            for(int i=right; i>=left; i--) {
                ans.push_back(mat[bottom][i]);
            }
            bottom--;
        }
        // bottom to top traversal : the left column is traversed bottom to top --> elements are accessed as mat[i][left]
        // this traversal is done only when left <= right i.e. when there is at least a left column which isn't traversed yet
        if (left <= right) {
            for(int i=bottom; i>=top; i--) {
                ans.push_back(mat[i][left]);
            }
            left++;
        }
    }
    return ans;
}

int main() {
    vector<vector<int>> mat = { {1,2,3,4,5,6}, {20,21,22,23,24,7}, {19,32,33,34,25,8}, {18,31,36,35,26,9}, {17,30,29,28,27,10}, {16,15,14,13,12,11}};
    vector<int> spr = SpiralTraversal(mat);
    for(int x : spr) cout << x << " ";
    return 0;
}