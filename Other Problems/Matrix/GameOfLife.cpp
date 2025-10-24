/*
Leetcode - 289. Game of Life

According to Wikipedia's article: "The Game of Life, also known simply as Life, is a cellular automaton devised by the British
mathematician John Horton Conway in 1970."

The board is made up of an m x n grid of cells, where each cell has an initial state: live (represented by a 1) or dead (represented by a 0).
Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules
(taken from the above Wikipedia article):
- Any live cell with fewer than two live neighbors dies as if caused by under-population.
- Any live cell with two or three live neighbors lives on to the next generation.
- Any live cell with more than three live neighbors dies, as if by over-population.
- Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

The next state of the board is determined by applying the above rules simultaneously to every cell in the current state of the m x n
grid board. In this process, births and deaths occur simultaneously.
Given the current state of the board, update the board to reflect its next state.
Note that you do not need to return anything.

Examples :-

Input: board = [[0,1,0],[0,0,1],[1,1,1],[0,0,0]] __ Output: [[0,0,0],[1,0,1],[0,1,1],[0,1,0]]
Input: board = [[1,1],[1,0]] __ Output: [[1,1],[1,1]]

Constraints:

m == board.length
n == board[i].length
1 <= m, n <= 25
board[i][j] is 0 or 1.
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(m*n) where m is number of rows and n is number of columns __ Space Complexity : O(1)
/*
Problem is to update the matrix in place as doing so would cause problems in checking neighbours. 
So we first traverse the matrix and for each element find the neighbour count and update the element. 
Modifying the matrix would cause problems in checking neighbours so we don't directly change 1 to 0 or 0 to 1, 
instead we use State encoding (a clever trick) to mark the changes as follows :
- if 1 dies to 0 due to neighbour count change it to -1, and
- if 0 revives as 1 then change it to -2

Doing so helps us in checking the neighbours as we can still identify the original state of the cell (while checking neighbours) 
by checking if the value is 1 or -1 (originally 1) or 0 or -2 (originally 0).
*/
int getNeighbour(int x) {
    return (x == 1 || x == -1) ? 1 : 0;
}

void gameOfLife(vector<vector<int>> &board) {
    int rows = board.size();
    int cols = board[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int cnt = 0; // neighbour count
            int n1 = 0, n2 = 0, n3 = 0, n4 = 0, n5 = 0, n6 = 0, n7 = 0, n8 = 0;
            // check for upper row neighoburs
            if (i - 1 >= 0) { // upper row exists
                if (j - 1 >= 0)
                    n1 = getNeighbour(board[i - 1][j - 1]);
                n2 = getNeighbour(board[i - 1][j]);
                if (j + 1 < cols)
                    n3 = getNeighbour(board[i - 1][j + 1]);
            }

            // check for same row neighbours : left & right neighbours
            if (j - 1 >= 0)
                n4 = getNeighbour(board[i][j - 1]);
            if (j + 1 < cols)
                n5 = getNeighbour(board[i][j + 1]);

            // check for lower row neighbours
            if (i + 1 < rows) { // lower row exists
                if (j - 1 >= 0)
                    n6 = getNeighbour(board[i + 1][j - 1]);
                n7 = getNeighbour(board[i + 1][j]);
                if (j + 1 < cols)
                    n8 = getNeighbour(board[i + 1][j + 1]);
            }
            cnt = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;

            if (board[i][j] == 0 && cnt == 3) board[i][j] = -2;
            if (board[i][j] == 1){
                if (cnt < 2 || cnt > 3) board[i][j] = -1;
            }
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (board[i][j] == -1)
                board[i][j] = 0;
            if (board[i][j] == -2)
                board[i][j] = 1;
        }
    }
}

/*
✅ Improvements
-- Directional array (dirs) 
We can use a directional array to store the relative positions of the 8 neighbours and then iterate through this array to get 
the neighbour positions. This makes the code cleaner and easier to maintain.
We know for a cell (i, j) the relative positions of its 8 neighbours are :
(i-1,j-1), (i-1,j), (i-1,j+1)
(i,j-1),         (i,j+1)
(i+1,j-1), (i+1,j), (i+1,j+1)

so instead of writing separate conditions for each neighbour we can store these relative positions in a vector of pairs
vector<pair<int, int>> dirs = {
    {-1,-1}, {-1,0}, {-1,1}, 
    {0,-1},          {0,1},
    {1,-1},  {1,0},  {1,1}
};
Now for each cell(i, j) we iterate through this dirs array to get each neighbour (total 8 neighbours) 
and check if they are valid (within bounds)
Positions of a neighbour can be found as (i + dx, j + dy) where (dx, dy) is an element from dirs array.
Ex - (i-1, j-1) can be found as (i + (-1), j + (-1)) where (-1, -1) is an element from dirs array.
So we simply loop through the dirs array and for each (dx, dy) we find the neighbour position (ni, nj) as (i + dx, j + dy)
and check if (ni, nj) is valid (within bounds) and if valid we add getNeighbour(board[ni][nj]) to cnt.
This way we avoid writing separate conditions for each neighbour and make the code cleaner.
*/
void gameOfLife2(vector<vector<int>>& board) {
    int rows = board.size();
    int cols = board[0].size();
        
    vector<pair<int, int>> dirs = {
        {-1,-1}, {-1,0}, {-1,1}, 
        {0,-1},          {0,1},
        {1,-1},  {1,0},  {1,1}
    };

    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            int cnt = 0;
            for (auto [dx, dy] : dirs) {
                int ni = i + dx, nj = j + dy;
                if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                    cnt += getNeighbour(board[ni][nj]);
                }
            }
            if (board[i][j] == 0 && cnt == 3) board[i][j] = -2;
            if (board[i][j] == 1) {
                if (cnt < 2 || cnt > 3) board[i][j] = -1;
            }
        }
    }

    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            if (board[i][j] == -1) board[i][j] = 0;
            if (board[i][j] == -2) board[i][j] = 1;
        }
    }
}

int main()
{
    return 0;
}