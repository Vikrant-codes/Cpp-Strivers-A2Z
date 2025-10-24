/*

*/

#include <bits/stdc++.h>
using namespace std;

bool isValidSudoku(vector<vector<char>>& board) {
    unordered_set<int> rows;
    unordered_set<int> cols;
    unordered_set<int> boxes;

    // validate rows
    for (vector<char> row : board) {
        for (char ch : row) {
            if (ch == '.') continue;
            int x = ch - '0';
            if (rows.find(x) != rows.end()) return false;
            rows.insert(x);
        }
        rows.clear();
    }

    // validate columns
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            char ch = board[j][i];
            if (ch == '.') continue;
            int x = ch - '0';
            if (cols.find(x) != cols.end()) return false;
            cols.insert(x);
        }
        cols.clear();
    }

    // vailadte boxes
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            for (int k=0; k<3; k++) {
                for (int l=0; l<3; l++) {
                    char ch = board[k+3*i][l+3*j];
                    if (ch == '.') continue;
                    int x = ch - '0';
                    if (boxes.find(x) != boxes.end()) return false;
                    boxes.insert(x);
                }
            }
            boxes.clear();
        }
    }

        /*
        Chatgpt's box traversal using 2 for loops only
        // validate boxes
        for (int b = 0; b < 9; b++) {              // box index 0..8
        boxes.clear();
        int startRow = (b / 3) * 3;
        int startCol = (b % 3) * 3;

        for (int k = 0; k < 9; k++) {          // 9 cells in the box
            int r = startRow + k / 3;
            int c = startCol + k % 3;

            char ch = board[r][c];
            if (ch == '.') continue;
            int x = ch - '0';
            if (boxes.find(x) != boxes.end()) return false;
            boxes.insert(x);
        }
        }
        */

    return true;
}

bool isValidSudokuChatgpt(vector<vector<char>>& board) {
    vector<unordered_set<int>> rows(9), cols(9), boxes(9);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            char ch = board[i][j];
            if (ch == '.') continue;
            int x = ch - '0';
            
            int boxIndex = (i / 3) * 3 + (j / 3);

            if (rows[i].count(x) || cols[j].count(x) || boxes[boxIndex].count(x))
                return false;

            rows[i].insert(x);
            cols[j].insert(x);
            boxes[boxIndex].insert(x);
        }
    }

    return true;
}


int main() {
    

    return 0;
}