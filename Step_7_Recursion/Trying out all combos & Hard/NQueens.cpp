#include <bits/stdc++.h>
using namespace std;
 
// 😺 My solution

vector<string> placeQueen(vector<string> curr, int rowNo, int ind, int n) {
    // mark in row
    for (int i = ind + 1; i < n; i++) {
        curr[rowNo][i] = '.';
    }

    // mark in col
    for (int i = rowNo + 1; i < n; i++) {
        curr[i][ind] = '.';
    }
    
    // mark the bottom-left diagonal
    int a = rowNo + 1, b = ind - 1;
    while (a < n && b >= 0) {
        curr[a][b] = '.';
        a++; b--;
    }
    
    // mark the bottom-right diagonal
    a = rowNo + 1, b = ind + 1;
    while (a < n && b < n) {
        curr[a][b] = '.';
        a++; b++;
    }
    
    curr[rowNo][ind] = 'Q';     // place the queen
    
    return curr;
}

void solve(vector<vector<string>>& solutions, vector<string>& curr, int rowNo, int n) {
    
    if (rowNo == n) {
        solutions.push_back(curr);
        return;
    }

    for (int ind = 0; ind < n; ind++) {
        if (curr[rowNo][ind] == '.') continue;
    
        // else string's index position is vacant ('_'), place a queen 
    
        vector<string> queenPlacedGrid = placeQueen(curr, rowNo, ind, n);
    
        solve(solutions, queenPlacedGrid, rowNo + 1, n);
    
        curr[rowNo][ind] = '.'; 
    }
}

vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> solution;

    vector<string> curr(n);

    // initialize all string having n underscore (vacant) characters '_'
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            curr[i].push_back('_');
        }
    }

    solve(solution, curr, 0, n);

    return solution;
}

/*
n = 4

we can maintain some variable `i` which will denote the current row number we are dealing with, 
for string at that index i, (consider 2-d grid)

for each index in row, try to place a queen there (if possible)
if there is some row where no queen could be placed, return immediately

_ _ _ _
_ _ _ _
_ _ _ _
_ _ _ _
*/

int main() {
    int n = 4;

    vector<vector<string>> solution = solveNQueens(n);

    for (int i = 0; i < solution.size(); i++) {
        cout << "-- Solution " << i+1 << " -- \n\n";

        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                cout << solution[i][j][k] << " ";
            }
            cout << "\n";
        } 

        cout << "\n\n";
    }

    return 0;
}
