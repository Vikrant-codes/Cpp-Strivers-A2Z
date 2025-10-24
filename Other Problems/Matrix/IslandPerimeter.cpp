/*
Leetcode - 463. Island Perimeter

You are given row x col grid representing a map where grid[i][j] = 1 represents land and grid[i][j] = 0 represents water.
Grid cells are connected horizontally/vertically (not diagonally). The grid is completely surrounded by water, and there 
is exactly one island (i.e., one or more connected land cells).
The island doesn't have "lakes", meaning the water inside isn't connected to the water around the island. 
One cell is a square with side length 1. The grid is rectangular, width and height don't exceed 100. 
Determine the perimeter of the island.

Examples :- 

Input: grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]] __ Output: 16

Input: grid = [[1]] __ Output: 4

Input: grid = [[1,0]] __ Output: 4

Constraints :- 
row == grid.length __ col == grid[i].length
1 <= row, col <= 100
grid[i][j] is 0 or 1.
There is exactly one island in grid.
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(n) __ Space Complexity : O(1)
/*
If a side is connected to another land cell then that side won't contribute to the perimeter. 
For each land area we check whether it shares it boundaries with other cells (top, left, bottom & right). 
Since the more boundaries it shares the less it contributes to the perimeter. Or, we can say 
we need to count the no of water connected sides current land cell has, since this tell us its contribution to perimeter. 
For each land cell we check whether its top, left, bottom and right cell is water. If so we increment the perimeter.
For a disconnected landcell, all 4 sides would be connected to water so it would contribute 4 as perimeter. 
*/
int islandPerimeter(vector<vector<int>>& grid) {
    int perimeter = 0;
    int rows = grid.size(), cols = grid[0].size();
    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            if (grid[i][j] == 1) {
                // check top element
                if (i == 0 || grid[i-1][j] == 0) perimeter++;
                // check left element 
                if (j == 0 || grid[i][j-1] == 0) perimeter++;
                // check bottom element
                if (i == rows-1 || grid[i+1][j] == 0) perimeter++;
                // check right element
                if (j == cols-1 || grid[i][j+1] == 0) perimeter++;
            }
        }
    }
    return perimeter;
}

int main() {

    return 0;
}