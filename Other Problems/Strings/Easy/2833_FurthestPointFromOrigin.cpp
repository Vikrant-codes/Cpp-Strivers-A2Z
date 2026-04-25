/*
Leetcode - 2833. Furthest Point From Origin : Easy

You are given a string moves of length n consisting only of characters 'L', 'R', and '_'. 
The string represents your movement on a number line starting from the origin 0.

In the ith move, you can choose one of the following directions:
- move to the left if moves[i] = 'L' or moves[i] = '_'
- move to the right if moves[i] = 'R' or moves[i] = '_'

Return the distance from the origin of the furthest point you can get to after n moves.

Examples :-
Input: moves = "L_RL__R"
Output: 3
Explanation: The furthest point we can reach from the origin 0 is point -3 through the following sequence of moves "LLRLLLR".

Input: moves = "_R__LL_"
Output: 5
Explanation: The furthest point we can reach from the origin 0 is point -5 through the following sequence of moves "LRLLLLL".

Input: moves = "_______"
Output: 7
Explanation: The furthest point we can reach from the origin 0 is point 7 through the following sequence of moves "RRRRRRR".
 
Constraints :-
- 1 <= moves.length == n <= 50
- moves consists only of characters 'L', 'R' and '_'.
*/

#include <bits/stdc++.h>
using namespace std;

// Greedy Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Let cntL be the number of ’L’ characters in moves, cntR be the number of ’R’ characters in moves, 
and cnt_ be the number '_' characters in moves.

The distance from the current position to the origin, ignoring undescores ('_'), is ∣cntL − cntR∣. 
To maximize the final distance from the origin, all '_' characters should be assigned in the same direction 
as the current movement, resulting in a maximum distance of ∣cntL - cntR∣ + cnt_
*/
/*
Observations --
- 'L' contributes to -1 as L means moving left i.e. moving -1 place back on the number line.
- 'R' contributes to +1 as R means moving right i.e. moving 1 place ahead on the number line.
- '_' can contribute to either 'L' or 'R' depending on our need.
- Movement starts from origin.

So, for a given string, 'L' moves the point to the left and 'R' moves it to the right so
the final position of the point will be equivalent to count of Rs - count of Ls.
Ex- if string was s = "LRLRRLRRRLR", then,
"LRLRRLRRRLR" -> there are 4Ls & 7Rs, so pointer will move to the left 4 times and to the right 7 times.
(move like left -> right -> left -> right -> right -> left -> right -> right -> right -> left -> right)
This would make the final position of pointer at 7 - 4 = 3 units (to the right of origin, since countR > countL).
if count of Ls was greater than count of Rs, then the diff (count of R - count of L) would've been -ve, 
meaning the final position of pointer is abs(diff) units to the left or origin.

We want to reach the furthest point possible which can reached after 'n' moves and behavior of L and R is fixed, but, 
'_' can move either left or right, so we must use it such that the furthest point reachable gets even further.
'_' has flexible movement. Assume the above string had 3 underscores like "LRL_RRLR_RRL_R",
without considering the '_', the pointer would've moved to 4 units to the right, so we should use the 3 underscore to move 
to the right as doing so will maximize this distance from origin.
So, the '_' must be used to move in the direction of the net movement as doing so would help us move even further. 

So, if countL > countR : '_' must behave as 'L' to reach the furthest point
    if countR > countL : '_' must behave as 'R' to reach the furthest point

The net movement magnitude is abs(countR - countL) and direction depends on the diff sign.
'_' must support this net movement so we must add the count of '_' to this net movement.
Thus, furthest point possible = abs(countR - countL) + count of _
*/
int furthestDistanceFromOrigin(string moves) {
    int cntL = 0, cntR = 0, cnt_ = 0;

    for (char ch : moves) {
        if (ch == 'L') cntL++;
        else if (ch == 'R') cntR++;
        else cnt_++;
    }

    return abs(cntL - cntR) + cnt_;
}

int main() {
    return 0;
}