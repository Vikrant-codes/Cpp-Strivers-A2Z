/*
Leetcode - 1886. Determine Whether Matrix Can Be Obtained By Rotation : Easy

Given two n x n binary matrices mat and target, 
return true if it is possible to make mat equal to target by rotating mat in 90-degree increments, 
or false otherwise. 

Examples :-

Input: mat = [[0,1],[1,0]], target = [[1,0],[0,1]]
Output: true
Explanation: We can rotate mat 90 degrees clockwise to make mat equal target.

Input: mat = [[0,1],[1,1]], target = [[1,0],[0,1]]
Output: false
Explanation: It is impossible to make mat equal to target by rotating mat.

Input: mat = [[0,0,0],[0,1,0],[1,1,1]], target = [[1,1,1],[0,1,0],[0,0,0]]
Output: true
Explanation: We can rotate mat 90 degrees clockwise two times to make mat equal target.

Constraints :-
- n == mat.length == target.length
- n == mat[i].length == target[i].length
- 1 <= n <= 10
- mat[i][j] and target[i][j] are either 0 or 1.
*/

#include <bits/stdc++.h>
using namespace std;

void rotate90(vector<vector<int>>& mat) {
    int n = mat.size();
    // transpose
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            swap(mat[i][j], mat[j][i]);
        }
    }

    // reverse each row
    for (int i = 0; i < n; i++) {
        int l = 0, r = n-1;
        while (l < r) {
            swap(mat[i][l], mat[i][r]);
            l++;
            r--;
        } 
    }
}

bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
    if (mat == target) return true;

    for (int i = 0; i < 3; i++) {
        rotate90(mat);
        if (mat == target) return true;
    }
    
    return false;
}

int main() {
    return 0;
}