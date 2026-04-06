/*
Leetcode - 657. Robot Return to Origin : Easy

There is a robot starting at the position (0, 0), the origin, on a 2D plane. 
Given a sequence of its moves, judge if this robot ends up at (0, 0) after it completes its moves.

You are given a string moves that represents the move sequence of the robot where moves[i] represents its ith move. 
Valid moves are 'R' (right), 'L' (left), 'U' (up), and 'D' (down).

Return true if the robot returns to the origin after it finishes all of its moves, or false otherwise.

Note: The way that the robot is "facing" is irrelevant. 
'R' will always make the robot move to the right once, 'L' will always make it move left, etc. 
Also, assume that the magnitude of the robot's movement is the same for each move.

Examples :-

Input: moves = "UD"
Output: true
Explanation: The robot moves up once, and then down once. All moves have the same magnitude, 
so it ended up at the origin where it started. Therefore, we return true.

Input: moves = "LL"
Output: false
Explanation: The robot moves left twice. It ends up two "moves" to the left of the origin. 
We return false because it is not at the origin at the end of its moves.

Constraints :-
- 1 <= moves.length <= 2 * 10^4
- moves only contains the characters 'U', 'D', 'L' and 'R'.
*/

#include <bits/stdc++.h>
using namespace std;

bool judgeCircle1(string moves) {
    vector<int> point = {0, 0};     // position of robot (x & y co-ordinates)

    for (char c : moves) {
        if (c == 'R') point[0]++;
        else if (c == 'L') point[0]--;
        else if (c == 'U') point[1]++;
        else point[1]--;
    }
    
    return (point[0] == 0 && point[1] == 0);
}

bool judgeCircle2(string moves) {
    int xD = 0, yD = 0;

    for (char c : moves) {
        if (c == 'R') xD++;
        else if (c == 'L') xD--;
        else if (c == 'U') yD++;
        else yD--;
    }

    return (xD == 0 && yD == 0);
}

int main() {
    return 0;
}