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

// Time Complexity : O(n log n) __ Space Complexity : O(n)
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

✅ Core Idea
- Treat each move as a coordinate change.
- Track visited coordinates using a set.
- If a coordinate repeats → path crosses.

⏱ Complexity
Time: O(n log n) (due to set)
Space: O(n)
*/
bool isPathCrossing1(string path) {
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

// Same Approach, we are just using two variables 'x' & 'y' to keep track of current x & y co-ordinates of the point.
bool isPathCrossing2(string path) {
    set<pair<int,int>> points;
    points.insert({0, 0});

    int x = 0, y = 0;               // Initial Co-ordinates (x & y) of origin (0, 0) : x = 0, y = 0
    
    for (char& c : path) {
        if (c == 'N') y++;
        else if (c == 'S') y--;
        else if (c == 'E') x++;
        else x--;
    
        if (points.count({x, y})) return true;

        points.insert({x, y});
    }
    
    return false;
}

/*
<-- Why are we using 'set' and not 'unordered_set' -->

We need to store the points in a set / hash data structure. 
To store the points coordinates, we either use a pair<int, int> or vector<int>.
But, pairs & vectors don't have any defualt hashing functions in standard C++. 
So, we need to create custom hashing functions for them.

- set/map uses balanced BST (Red-Black Tree) → needs ordering (<)
- unordered_set/unordered_map uses hash table → needs hash function

# Data structures like 'set' and 'map' works fine with both or them, i.e.,

    set<vector<int>> points; 
    set<pair<int,int>> points;
    map<pair<int,int>, int> mp;
    map<vector<int>, int> mp;

These works fine because 'map' and 'set' uses ordering (<), not hashing.

# But if we use 'unordered_set' or 'unordered_map', these are troublesome.
unordered_set / unordered_map needs a hash function, 
and pair<int,int> / vector<int> doesn’t have a default hash in standard C++.
So, 
    unordered_set<vector<int>> points; 
    unordered_set<pair<int,int>> points;
    unordered_map<pair<int,int>, int> mp;
    unordered_map<vector<int>, int> mp;
These gives error, as pair<int, int> and vector<int> doesn't have a default hash function.
Why Eror?
- unordered_set / unordered_map → uses hashing
- pair<int,int> / vector<int> → no built-in hash
So, to make it work this way, we need to use a custom hash function.
*/

// Using Custom Hashing + Unordered_Set: Time Complexity : O(n) __ Space Complexity : O(n)
// Read "Step_1_LearnTheBasics/Advanced/CustomHashing_Encoding.cpp" to understand custom hashing and encoding

// custom hash function for pair hash
struct pair_hash {
    size_t operator() (const pair<int, int>& p) const {
        return hash<int>()(p.first) ^ ( (hash<int>()(p.second)) << 1);
    }
};

bool isPathCrossingCustomHash(string path) {
    unordered_set<pair<int, int>, pair_hash> s;
    int x = 0, y = 0;
    s.insert({x, y});           // Insert initial position (origin {0, 0})

    for (char &c : path) {
        if (c == 'N') y++;
        else if (c == 'S') y--;
        else if (c == 'E') x++;
        else x--;
    
        if (s.count({x, y})) return true;
        s.insert({x, y});
    }
    
    return false;
}

// Encoding : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Trick: Encode a pair in a way that it generates a unqiue key for that pair.
Pair (x, y) can be encoded as (x * N + y), where 'N' is a large no. such that N > y.
This encoded number can be directly used for hashing so no need for any custom hash function.

Give the contraints 1 <= path.length <= 10^4. Initially point would be {0, 0} i.e., x = 0, y = 0.
Now, the maximum string length can be 10^4, so even if the path moved only in one direction (like all 'N' or all 'E').
If it had all N's then y would increase 10^4 times, making its final value = 10^4.
So, the maximum value of x & y coordinates can be 10^4 only.
So, we use 1e5 i.e. (10^5) for encoding since (10^5 is always greater than x & y)
*/
bool isPathCrossing(string path) {
    unordered_set<long long> s;
    int x = 0, y = 0;
    s.insert(0);            // encoded value for origin {0, 0} = 0 * N + 0 = 0

    for (char &c : path) {
        if (c == 'N') y++;
        else if (c == 'S') y--;
        else if (c == 'E') x++;
        else x--;

        long long key = 1LL * x * 1e5 + y;      // encode for the current {x,y} pair

        if (s.count(key)) return true;
        s.insert(key);
    }

    return false;
}

int main() {
    return 0;
}