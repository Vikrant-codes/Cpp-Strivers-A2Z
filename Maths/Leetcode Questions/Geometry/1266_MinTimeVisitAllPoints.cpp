/*
Leetcode - 1266. Minimum Time Visiting All Points : Easy

On a 2D plane, there are n points with integer coordinates points[i] = [xi, yi]. 
Return the minimum time in seconds to visit all the points in the order given by points.

You can move according to these rules:

• In 1 second, you can either:
    • move vertically by one unit,
    • move horizontally by one unit, or
    • move diagonally sqrt(2) units (in other words, move one unit vertically then one unit horizontally in 1 second).
• You have to visit the points in the same order as they appear in the array.
• You are allowed to pass through points that appear later in the order, but these do not count as visits.

Examples :-

Input: points = [[1,1],[3,4],[-1,0]] __ Output: 7
Explanation: One optimal path is [1,1] -> [2,2] -> [3,3] -> [3,4] -> [2,3] -> [1,2] -> [0,1] -> [-1,0]   
Time from [1,1] to [3,4] = 3 seconds 
Time from [3,4] to [-1,0] = 4 seconds
Total time = 7 seconds

Input: points = [[3,2],[-2,2]] __ Output: 5

Constraints :-
• points.length == n
• 1 <= n <= 100
• points[i].length == 2
• -1000 <= points[i][0], points[i][1] <= 1000
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(n) __ Space Complexity : O(1)
/*
Suppose we need to go from point A (1,1) to point B (3, -2).
Now point B is at some distance from point A :-
horizontal distance => dx = abs(x2 - x1) = abs (3 - 1) = 2.
vertical distance => dy = abs(y2 - y1) = abs (-2 -1) = 3.
So, we need to move '2' places horizontally and '3' places vertically to go to point B from A.
But, we can move diagonally also (moving 1 place horizontally and vertically altogether)
Thus, by diaognal movement, we will only need 3 moves (2 moves diagonally (2 horizontal + 2 vertical) + 1 move vertically).
Thus, time taken to move from A to B is 3 units.

Thus, time taken = max ( horizontal_distance, vertical_distance )

we can calculate the total time in this way by traversing the array and finding time to reach between the points.
*/
int minTimeToVisitAllPoints(vector<vector<int>>& points) {
    int ans = 0;

    for (int i = 1; i < points.size(); i++) {
        int dx = abs(points[i][0] - points[i-1][0]);
        int dy = abs(points[i][1] - points[i-1][1]);
        ans += max(dx, dy);
    }

    return ans;
}

int main() {
    return 0;
}