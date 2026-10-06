/*
GFG - Rat in a Maze : Medium

Given a binary matrix maze[][] of size n × n containing values 0 and 1, 
find all possible paths for a rat to travel from the source cell (0, 0) to the destination cell (n - 1, n - 1). 
The rat can move in four directions: up(U), down(D), left(L), and right(R).

• 1 represents an open cell through which the rat can move.
• 0 represents a blocked cell that cannot be traversed.

The rat can move only through open cells and cannot visit the same cell more than once in a path. 
Return all valid paths as strings consisting of 'U', 'D', 'L', and 'R', representing the sequence of moves taken by the rat.

Note: Return the paths in lexicographically increasing order. 
If no valid path exists, return an empty list.

Examples :-

Input: maze[][] = {{1, 0, 0, 0}, {1, 1, 0, 1}, {1, 1, 0, 0}, {0, 1, 1, 1}}
Output: ["DDRDRR", "DRDDRR"]
Explanation: There are two valid paths from the source cell (0, 0) to the destination cell (3, 3).

Input: maze[][] = [[1, 0], [1, 0]]
Output: []
Explanation: No path exists as the destination cell (1, 1) is blocked.

Constraints :-
• 2 ≤ n ≤ 5
• 0 ≤ maze[i][j] ≤ 1
*/

#include <bits/stdc++.h>
using namespace std;

// Backtracking 

// My-Solution
/*
>> Intuition

We need to generate all valid paths from (0,0) to (n-1,n-1), where:
• We can move only in D, L, R, U directions.
• We cannot move into a blocked cell (0).
• We cannot revisit a cell in the current path, otherwise we could get stuck in cycles.
• The paths should be generated in lexicographical order.

1. Lexicographical order

We can simply explore the directions in sorted order: D → L → R → U
Since D < L < R < U, exploring the directions in this order naturally generates the paths in lexicographical order.

2. Keeping track of visited cells

We need to know whether the current cell has already been visited in the current path.
We could use a separate 2D vector to store this information of visited cells: `vector<vector<bool>> visited;`

But we can also reuse the given maze itself.

Since valid cells contain 1, when we enter a cell, we mark it as visited: `maze[i][j] = -1;`
Then: `if (maze[i][j] == 0 || maze[i][j] == -1) return;`, allows us to reject both blocked and already-visited cells.
When we finish exploring that cell and backtrack, we restore it: `maze[i][j] = 1;`
This is necessary because the cell should be available when exploring another possible path.

3. Representing the four directions

Instead of writing four separate recursive calls, 
we can store the direction characters and their corresponding row/column changes in vectors:
| vector<char> dirChar = {'D', 'L', 'R', 'U'};
| vector<vector<int>> directions = {
|     {1, 0},     // D
|     {0, -1},    // L
|     {0, 1},     // R
|     {-1, 0}     // U
| };

Or, we can also use a map which will gives us the direction character & row/column changes.
| map<char, vector<int>> mpp = { 
|     {'D', {1, 0}}, {'L', {0, -1}}, {'R', {0, 1}}, {'U', {-1, 0}}
| };

Then for every direction, we can calculate the co-ordinates of next cell corresponding to the current direction, 
and recursively move to the next position. 
We need to add the corresponding direction character (D/L/R/U) in the path string and remove it after the recursive call.

-> Why are we using map instead of unordered_map?
We use map instead of unordered_map because we need the directions in lexicographical order: D → L → R → U
map keeps its keys sorted, so: `for (auto& [ch, direction] : mpp)`, will iterate in exactly: D, L, R, U
With unordered_map, the iteration order is not guaranteed, 
so the paths would not necessarily be generated in lexicographical order.

So:
- map → sorted iteration → DLRU order ✅
- unordered_map → arbitrary iteration order → cannot guarantee lexicographical paths ❌
*/

// Complexity Analysis
/*
Let N = n² be the total number of cells in the maze.

-> Time Complexity

At every cell, we try at most 4 directions: D, L, R, U
Because we don't allow revisiting a cell in the current path, a path can contain at most N cells.

In the worst case, the number of possible paths can be exponential. A simple upper bound is: O(4^N)
Since N = n²: O(4^(n²))
This accounts for exploring the possible paths.

Additionally, whenever we find a valid path, we copy the current path into allPaths:
`allPaths.push_back(path);`
Copying a path can take O(N) time.

So, if there are P valid paths, a more informative complexity is: O(4^N + P × N)
where:
- N = n²
- P = number of valid paths
Since P itself can be exponential, 
we generally state the overall worst-case time as: O(4^(n²)) (up to the output-copying factor).

-> Space Complexity

There are three things to consider.

1. Recursion stack
The recursion can go through at most N cells before reaching the destination or getting stuck.
Therefore: O(N) = O(n²)

2. Current path
The longest possible path can visit at most N cells, so it can contain at most N - 1 direction characters.
Therefore: O(N) = O(n²)

3. allPaths
Suppose there are P valid paths and each path can have length O(N).
Then storing the result requires: O(P × N)
This is output space, not auxiliary space.

Therefore:
Auxiliary Space
Ignoring the returned allPaths: O(N) + O(N) = O(2*N) = O(2*n²)
The maze itself is modified in-place, so it does not require an additional O(n²) visited array.

| Complexity          |             |
| ------------------- | ----------- |
| **Time**            | `O(4^(n²))` |
| **Auxiliary Space** | `O(n²)`     |
| **Output Space**    | `O(P × n²)` |
where P is the number of valid paths.
*/

map<char, vector<int>> mpp = { 
    {'D', {1, 0}}, {'L', {0, -1}}, {'R', {0, 1}}, {'U', {-1, 0}}
};
// we are not using `unordered_map` because we want to iterate through directions in order 'DLRU', 
// with unordered_map this ordered traversal of elements is not possible

// vector<char> dirChar = {'D', 'L', 'R', 'U'};
// vector<vector<int>> directions = { {1, 0}, {0, -1}, {0, 1}, {-1, 0} };

void move(vector<vector<int>>& maze, int n, int i, int j, vector<string>& allPaths, string& path) {
    if (i == n - 1 && j == n - 1) {
        allPaths.push_back(path);
        return;
    }
    
    // if out of bounds, return
    if (i < 0 || i >= n || j < 0 || j >= n) return;
    
    // if cell is blocked or already visited, return immediately
    if (maze[i][j] == 0 || maze[i][j] == -1)        // if (maze[i][j] != 1)
        return;
        
    // current cell has '1' value
    
    maze[i][j] = -1;        // mark as visited
    
    for (auto& [ch, direction] : mpp) {
        int new_i = i + direction[0];
        int new_j = j + direction[1];
        
        path.push_back(ch);
        
        move(maze, n, new_i, new_j, allPaths, path);
        
        path.pop_back();
    }

    // for (int t = 0; t < 4; t++) {
    //     int new_i = i + directions[t][0];
    //     int new_j = j + directions[t][1];
    //     char ch = dirChar[t];
    //     path.push_back(ch);
    //     move(maze, n, new_i, new_j, allPaths, path);
    //     path.pop_back();
    // }
        
    maze[i][j] = 1;     // restore the value of current cell (unmark visited) 
}

vector<string> ratInMaze(vector<vector<int>>& maze) {
    int n = maze.size();
    
    if (maze[n-1][n-1] == 0) 
        return {};
    
    vector<string> allPaths;
    string path;
    
    move(maze, n, 0, 0, allPaths, path);
    
    return allPaths;
}


// Striver's solution
/*
Using a separate 2D vector to store information of visited cells.
Before moving to a next cell, we make sure that the movement is possible or not, 
i.e., the cell must not be out of bounds, or already-visited, or blocked.
Only if cell is available for movement, then only we call the recusive function, 
so we don't have to explicitly check if the current movement is valid or not.
*/
void solve(int i, int j, vector<vector<int>>& maze, int n, vector<string>& ans, string move,
    vector<vector<int>>& vis, int di[], int dj[]) {
        
    if (i == n-1 && j == n-1) {
        ans.push_back(move);
        return;
    }
    
    string dir = "DLRU";
    
    for (int ind = 0; ind < 4; ind++) {
        int nexti = i + di[ind];
        int nextj = j + dj[ind];
        
        if (nexti >= 0 && nextj >= 0 && nexti < n && nextj < n && !vis[nexti][nextj] && maze[nexti][nextj] == 1) {
            vis[i][j] = 1;
            solve(nexti, nextj, maze, n, ans, move + dir[ind], vis, di, dj);
            vis[i][j] = 0;
        }
    }
}

vector<string> ratInMazeStriver(vector<vector<int>>& maze) {
    int n = maze.size();
    vector<string> ans;
    vector<vector<int>> vis(n, vector<int> (n, 0));
    int di[] = {1, 0, 0, -1};
    int dj[] = {0, -1, 1, 0};
    
    if (maze[0][0] == 1) solve(0, 0, maze, n, ans, "", vis, di, dj);
    
    return ans;
}

// Main difference between the two solutions
/*
1) My solution — validate inside the recursive function

    make recursive call
           ↓
    check current cell:
      - out of bounds?
      - blocked?
      - visited?
           ↓
    if valid → continue

So the recursive function can receive an invalid cell and immediately return.

Because the base case is checked before validity checks, we must separately ensure that the destination is unblocked:
    if (maze[n-1][n-1] == 0) return {};

2) Striver's solution — validate before the recursive call

    calculate next cell
           ↓
    check next cell:
      - within bounds?
      - not visited?
      - not blocked?
           ↓
    if valid → make recursive call

So solve() is called only with a valid cell.

Therefore, we only need to check the source before the first call:
    if (maze[0][0] == 1)
        solve(...);
The destination doesn't need a separate check because it has already passed the validity check before solve() entered it.

In short
- 1st: call → validate current cell
- 2nd: validate next cell → call
Both approaches are logically valid; they just place the validity check at different points.
*/

int main() {
    return 0;
}