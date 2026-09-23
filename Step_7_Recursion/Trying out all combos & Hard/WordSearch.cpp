/*
Leetcode - 79. Word Search : Medium

Given an m x n grid of characters board and a string word, return true if word exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, 
where adjacent cells are horizontally or vertically neighboring. 
The same letter cell may not be used more than once.

Examples :-

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
Output: true

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
Output: true

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
Output: false

Constraints :- 
• m == board.length
• n = board[i].length
• 1 <= m, n <= 6
• 1 <= word.length <= 15
• board and word consists of only lowercase and uppercase English letters.

Follow up: Could you use search pruning to make your solution faster with a larger board? 
*/

#include<bits/stdc++.h>
using namespace std;

// Core Backtracking Intuition
/*
>> Core intuition 

For Word Search, once we find a character matching the current character of the word, 
we need to recursively search for the next character in all four possible directions:
• up
• down
• left
• right

The important part is that we don't know beforehand which direction will lead to the solution.
For example, suppose we have matched: A B, and now need to find C.
C could be:
        C
        ↑
    A → B ← C
        ↓
        C
So from the current cell, we recursively try all four directions.

But there is another constraint: we cannot use the same cell twice in the same word path.
Therefore, whenever we choose a cell, we mark it as picked/visited.
If that path eventually fails, we need to undo that choice so that the cell can be used by another possible path.

That's exactly why we need backtracking:
    pick current cell
           ↓
    try 4 directions recursively
           ↓
    if successful → return true
           ↓
    if all fail
           ↓
    unpick current cell
           ↓
    return false

So conceptually: DFS explores the possible paths, while backtracking allows us to undo a choice and explore another path.
*/

// My First Solution : Time Complexity : O(mn ∙ 3^L) __ Space Complexity : O(mn + L)
/*
We use `vector<vector<bool>>& picked`, to mark that a cell character has been picked/visited.

When the current character matches, we do 
    `picked[i][j] = true;` 
to mark that this cell has been visited in the current recursive path.

Then we recursively search:
    fun(... ind+1 ... i-1, j ...)
    fun(... ind+1 ... i+1, j ...)
    fun(... ind+1 ... i, j-1 ...)
    fun(... ind+1 ... i, j+1 ...)

If none of those paths works: `picked[i][j] = false;`
So picked[][] represents:
"Is this cell already being used in the current recursive path?"

-- Notice why the unpick is important.
Suppose we tried: A → B → C
and C doesn't lead to the remaining word.
We need to go back to B, unpick C, and potentially try another direction.
Similarly, eventually we may need to unpick B and try another path from A.
This unpick is necessary because even though current B doesn't lead to a complete-word, 
this 'B' may be later needed for some recursive path and thus we need to mark it as not-visited/unpicked for later use.

>> Complexity

Let:
• m × n = board size
• L = length of word
There are m × n possible starting cells.

For each starting cell, in the worst case we can explore up to 4 choices at every step:
    first character → 4 choices
    second character → 4 choices
    third character → 4 choices
    ...

So a rough upper bound is: O(mn ∙ 4^L)

However, because we cannot immediately go back to the cell we just came from, 
after the first move there are at most 3 genuinely new directions.

Therefore, a tighter bound is often written as: O(mn ∙ 4 ∙ 3^(L-1) )
which is asymptotically: O(mn ∙ 3^L)
For interview purposes, we generally use: Time: O(m × n × 3^L)

-> Space

The picked matrix requires: O(mn)
And recursion can go at most L levels deep: O(L)

So: O(mn + L)
Since L cannot exceed the number of cells in a valid path, this can also be bounded by O(mn) in terms of board size.
*/
bool fun(
    vector<vector<char>>& board, string& word, int ind, 
    vector<vector<bool>>& picked, int i, int j, int m, int n
) {

    if (ind == word.size()) return true;

    if (i < 0 || i >= m || j < 0 || j >= n) return false;
    
    // mismatch or already picked character
    if (board[i][j] != word[ind] || picked[i][j])
        return false;
    
    // match .. pick it and recursive call for adjacent cells
    picked[i][j] = true;

    if (
        fun(board, word, ind+1, picked, i-1, j, m, n) ||
        fun(board, word, ind+1, picked, i+1, j, m, n) ||
        fun(board, word, ind+1, picked, i, j-1, m, n) ||
        fun(board, word, ind+1, picked, i, j+1, m, n)
    ) {
        return true;
    }

    // unpick
    picked[i][j] = false;

    return false;
}

bool exist1(vector<vector<char>>& board, string word) {
    int m = board.size();
    int n = board[0].size();

    vector<vector<bool>> picked(m, vector<bool> (n));
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (fun(board, word, 0, picked, i, j, m, n))
                return true;
        }
    }

    return false;
}

// codestorywithMIK's solution : Time Complexity : O(mn ∙ 3^L) __ Space Complexity : O(L)
/*
The backtracking intuition doesn't change here.

The important improvement is: 
We don't necessarily need a separate picked[][] matrix to remember which cells have been visited.

Instead, we can modify the board itself temporarily, by using a placeholder to mark that current cell is visited.
The board can only have lowercase & uppercase letters, so we can use some character other than these like '$' or '_' etc.
and when we find this placeholder in a cell while searching, it means current cell is already visited.

MIK uses: board[i][j] = '$';
So $ means: "This cell is currently part of my path, so don't use it again."

Before:
    A B C
    D E F
    G H I

Suppose we pick E:
    A B C
    D $ F
    G H I

Now when DFS encounters $, it knows:
    if (... || board[i][j] == '$')
        return false;

After finishing that path, we restore the original character.
To do so, we can maybe use a temp variable to store the current cell value, and later use this temp to restore value.

    char temp = board[i][j];
    board[i][j] = '$';
    
    { recursive search logic }

    board[i][j] = temp;

So we're doing exactly the same pick → explore → unpick operation.
The difference is just where the visited information is stored.
I used: 
    board       → original characters
    picked[][]  → visited information

MIK's solution
    board       → original characters + visited information
So we eliminate the separate picked[][].

This optimizes space complexity and it doesn't need another matrix i.e., O(mn) space to store visited information.

-> Direction vector
MIK also avoids manually writing:
    i-1, j
    i+1, j
    i, j-1
    i, j+1

Instead: vector<vector<int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
Each pair represents: {row change, column change}
For example:
    {1, 0}   → down
    {-1, 0}  → up
    {0, 1}   → right
    {0, -1}  → left

Then:
    for (auto& dir : directions) {
        int new_i = i + dir[0];
        int new_j = j + dir[1];

        find(...);
    }
This makes the "try all four directions" logic more compact and reusable.

Although, this just makes the code look clean but doesn't optimizes any time. (just other way of implementation)

>> Complexity Analysis

The search complexity is essentially the same: O(mn ∙ 3^L)

The important difference is auxiliary space.
There is no separate: picked[m][n] matrix.
The board itself is being modified temporarily.
Recursion depth is: O(L)
Therefore auxiliary space is: O(L)
assuming the board itself is considered input storage rather than extra space.
*/

int m, n;
vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool find(vector<vector<char>>& board, int i, int j, string& word, int idx) {
    if (idx == word.size())
        return true;

    if (i < 0 || i >= m || j < 0 || j >= n || board[i][j] == '$') 
        return false;

    if (board[i][j] != word[idx])
        return false;

    char temp = board[i][j];
    board[i][j] = '$';

    for (auto& dir : directions) {
        int new_i = i + dir[0];
        int new_j = j + dir[1];
        if (find(board, new_i, new_j, word, idx+1))
            return true;
    }

    board[i][j] = temp;
    
    return false;
}

bool exist2(vector<vector<char>>& board, string word) {
    m = board.size();
    n = board[0].size();

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == word[0] && find(board, i, j, word, 0)) 
                return true;
        }
    }

    return false;
}

// Updated implementation of my solution : Time Complexity : O(mn ∙ 3^L) __ Space Complexity : O(L)
/*
This solution uses the idea of using board itself to store the visited information, 
by replacing the visited character with a placeholder character ('$').

Therefore, the basic structure is now:
    match character
          ↓
    mark cell as '$'
          ↓
    search 4 directions
          ↓
    if unsuccessful
          ↓
    restore character

Although, we don't actually need to use a temp variable to store the current cell value so it is not lost.

We know that the current cell i.e., board[i][j] == word[ind] (since, we return false in case of mismatch),
Thus, when we mark the current cell using `board[i][j] = '$'`, we already know the original value was `word[ind]`.
So, we can use this to restore the value, so after backtracking we do: board[i][j] = word[ind];

This solution also uses direct four-direction recursion (since I wanted to keep the implementation similar to my solution)
Unlike MIK's direction vector, we kept:
    wordSearch(board, i-1, j, ...)
    wordSearch(board, i+1, j, ...)
    wordSearch(board, i, j-1, ...)
    wordSearch(board, i, j+1, ...)

So the two approaches are simply different ways of expressing the same thing:

Explicit
    up
    down
    left
    right
Direction vector
    for (auto& dir : directions)

There is no meaningful asymptotic complexity difference.
*/
bool wordSearch(vector<vector<char>>& board, int i, int j, string& word, int ind) {
    // Base-Case: Word has been found (all characters are exhausted)
    if (ind == word.size()) 
        return true;

    int m = board.size(), n = board[0].size();
    
    // out-of-bound access
    if (i < 0 || i >= m || j < 0 || j >= n) 
        return false;
    
    // mismatch or already picked character
    if (board[i][j] == '$' || board[i][j] != word[ind]) 
        return false;

    // match .. pick it and do recursive call for adjacent cells
    board[i][j] = '$';             // we are using '$' to mark the picking

    if (
        wordSearch(board, i-1, j, word, ind+1) ||
        wordSearch(board, i+1, j, word, ind+1) ||
        wordSearch(board, i, j-1, word, ind+1) ||
        wordSearch(board, i, j+1, word, ind+1)
    ) {
        return true;
    }

    // word not found.. unpick the current character and return false

    board[i][j] = word[ind];    
    // board[i][j] was equal to word[ind], so we can use that value to place that value again
    
    return false;
}

bool exist3(vector<vector<char>>& board, string word) {
    int m = board.size();
    int n = board[0].size();

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == word[0] && wordSearch(board, i, j, word, 0)) {
                return true;
            }
        }
    }

    return false;
}

/*
Comparison of the three
|                       | 1st            | MIK              | updated           |
| --------------------- | -------------- | ---------------- | ----------------- |
| DFS                   | ✅            | ✅               | ✅                |
| Backtracking          | ✅            | ✅               | ✅                |
| Search 4 directions   | Explicit       | Direction vector | Explicit          |
| Visited tracking      | `picked[][]`   | `$` in board     | `$` in board      |
| Restore after failure | `picked=false` | `board=temp`     | `board=word[ind]` |
| Extra visited matrix  | Yes            | No               | No                |
| Recursion space       | `O(L)`         | `O(L)`           | `O(L)`            |
| Visited matrix space  | `O(mn)`        | None             | None              |
| Time                  | `O(mn·3^L)`    | `O(mn·3^L)`      | `O(mn·3^L)`       |
| Auxiliary space       | `O(mn + L)`    | `O(L)`           | `O(L)`            |
*/

int main() {
    return 0;
}