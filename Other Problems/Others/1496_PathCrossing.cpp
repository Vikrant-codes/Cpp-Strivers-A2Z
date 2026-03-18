/*
Leetcode - 1496. Path Crossing : Easy

Given a string path, where path[i] = 'N', 'S', 'E' or 'W', 
each representing moving one unit north, south, east, or west, respectively. 
You start at the origin (0, 0) on a 2D plane and walk on the path specified by path.

Return true if the path crosses itself at any point, that is, 
if at any time you are on a location you have previously visited. 
Return false otherwise.

Examples :-

Input: path = "NES" __ Output: false 
Explanation: Notice that the path doesn't cross any point more than once.

Input: path = "NESWW" __ Output: true
Explanation: Notice that the path visits the origin twice.

Constraints :-
- 1 <= path.length <= 10^4
- path[i] is either 'N', 'S', 'E', or 'W'.
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(n log n) since using 'set', 'unordered_set would have taken O(n)' __ Space Complexity : O(n)
/*
Idea:
The problem statements includes : 
"Return true if the path crosses itself at any point, 
 that is, if at any time you are on a location you have previously visited. 
 Return false otherwise."

So, if we associate the movements with the points we can check if the paths are crossed by considering if a point re-appears,
i.e., has been previously visited.
Thus, we use a set to store the points while moving North/East/West/South. 
If during movement, any point re-appears, this would mean paths are being crossed.
We can easily check for this re-appearance of a point using set.
If set already contains some point, it means the point is being re-visited.
*/
bool isPathCrossing(string path) {
    set<vector<int>> points;
    points.insert({0, 0});

    vector<int> x = {0, 0};         // Initial Point / Starting Point, Origin 
    
    for (char& c : path) {
        if (c == 'N') x[1]++;       // N -> North -> moves 1 unit upwards (y-coordinate increases)
        else if (c == 'S') x[1]--;  // S -> South -> moves 1 unit downwards (y-coordinate decreases)
        else if (c == 'E') x[0]++;  // E -> East -> moves 1 unit rightwards (x-coordinate increases) 
        else x[0]--;                // W -> West -> moves 1 unit leftwaeds (x-coordinate decreases)
    
        // if set already contains this point, it means this point is being re-visited
        if (points.count(x)) return true;
    
        points.insert(x);           // Insert the current point in the set
    }
    
    return false;
}

int main() {
    return 0;
}