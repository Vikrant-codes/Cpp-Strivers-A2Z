/*
Leetcode - 1275. Find Winner on a Tic Tac Toe Game

Tic-tac-toe is played by two players A and B on a 3 x 3 grid. The rules of Tic-Tac-Toe are:

- Players take turns placing characters into empty squares ' '.
- The first player A always places 'X' characters, while the second player B always places 'O' characters.
- 'X' and 'O' characters are always placed into empty squares, never on filled ones.
- The game ends when there are three of the same (non-empty) character filling any row, column, or diagonal.
- The game also ends if all squares are non-empty.
- No more moves can be played if the game is over.

Given a 2D integer array moves where moves[i] = [rowi, coli] indicates that the ith move will be played on grid[rowi][coli].
return the winner of the game if it exists (A or B). In case the game ends in a draw return "Draw".
If there are still movements to play return "Pending".

You can assume that moves is valid (i.e., it follows the rules of Tic-Tac-Toe), the grid is initially empty, and A will play first.

Examples :-
Input: moves = [[0,0],[2,0],[1,1],[2,1],[2,2]] __ Output: "A"
Input: moves = [[0,0],[1,1],[0,1],[0,2],[1,0],[2,0]] __ Output: "B"
Input: moves = [[0,0],[1,1],[2,0],[1,0],[1,2],[2,1],[0,1],[0,2],[2,2]] __ Output: "Draw"

Constraints :-
- 1 <= moves.length <= 9
- moves[i].length == 2
- 0 <= rowi, coli <= 2
- There are no repeated elements on moves.
- moves follow the rules of tic tac toe.
*/

#include <bits/stdc++.h>
using namespace std;

// return who won when a whole row/col/diagonal is same
// checks the entry of first el of row/col or mid element of diagonal i.e. grid[1][1]
string whoWon(string chr)
{
    if (chr == "X")
        return "A";
    return "B";
}

string tictactoe(vector<vector<int>> &moves)
{
    int n = moves.size();
    vector<vector<string>> grid(3, vector<string>(3));

    for (int i = 0; i < n; i++)
    {
        int posx = moves[i][0], posy = moves[i][1];
        // place 'X'
        if (i % 2 == 0)
            grid[posx][posy] = "X";
        // place 'O'
        else
            grid[posx][posy] = "O";
    }

    // check each row to see who won
    for (int i = 0; i < 3; i++)
    {
        if (grid[i][0] == "")
            continue;
        if ((grid[i][0] == grid[i][1]) && (grid[i][1] == grid[i][2]))
        {
            return whoWon(grid[i][0]);
        }
    }
    // check each col to see who won
    for (int i = 0; i < 3; i++)
    {
        if (grid[0][i] == "")
            continue;
        if ((grid[0][i] == grid[1][i]) && (grid[1][i] == grid[2][i]))
        {
            return whoWon(grid[0][i]);
        }
    }
    // check diagonal to see who won
    if (grid[1][1] != "")
    {
        // check 1st diagonal
        if ((grid[0][0] == grid[1][1]) && (grid[1][1] == grid[2][2]))
            return whoWon(grid[1][1]);
        // check 2nd diagonal
        if ((grid[0][2] == grid[1][1]) && (grid[1][1] == grid[2][0]))
            return whoWon(grid[1][1]);
    }

    if (n == 9)
        return "Draw";
    return "Pending";
}

int main()
{

    return 0;
}
