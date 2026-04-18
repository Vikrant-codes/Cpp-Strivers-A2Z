/*
Leetcode - 2515. Shortest Distance to Target String in a Circular Array : Easy

You are given a 0-indexed circular string array words and a string target. 
A circular array means that the array's end connects to the array's beginning.

Formally, the next element of words[i] is words[(i + 1) % n] and 
the previous element of words[i] is words[(i - 1 + n) % n], where n is the length of words.

Starting from startIndex, you can move to either the next word or the previous word with 1 step at a time.
Return the shortest distance needed to reach the string target. If the string target does not exist in words, return -1.

Examples :-

Input: words = ["hello","i","am","leetcode","hello"], target = "hello", startIndex = 1
Output: 1
Explanation: We start from index 1 and can reach "hello" by
- moving 3 units to the right to reach index 4.
- moving 2 units to the left to reach index 4.
- moving 4 units to the right to reach index 0.
- moving 1 unit to the left to reach index 0.
The shortest distance to reach "hello" is 1.

Input: words = ["a","b","leetcode"], target = "leetcode", startIndex = 0
Output: 1
Explanation: We start from index 0 and can reach "leetcode" by
- moving 2 units to the right to reach index 2.
- moving 1 unit to the left to reach index 2.
The shortest distance to reach "leetcode" is 1.

Input: words = ["i","eat","leetcode"], target = "ate", startIndex = 0
Output: -1
Explanation: Since "ate" does not exist in words, we return -1.

Constraints :-
- 1 <= words.length <= 100
- 1 <= words[i].length <= 100
- words[i] and target consist of only lowercase English letters.
- 0 <= startIndex < words.length
*/

#include <bits/stdc++.h>
using namespace std;

// Approach1 (Linear Scan + Circular Distance):- Time Complexity : O(n) __ Space Complexity : O(1)
/*
-- Approach (Optimal – Linear Scan + Circular Distance) --

• Traverse the entire array once to find all indices where words[i] == target.
• For each such index i, compute the minimum distance from startIndex considering the circular nature:
    • Direct distance = abs(startIndex - i)
    • Circular distance = n - abs(startIndex - i)
    • Take the minimum of both.
• Keep track of the smallest distance among all occurrences of target.
• If the target is never found, return -1.

>> Key Idea:
In a circular array, the shortest path between two indices can be either clockwise or counterclockwise, so we take:
    min(|startIndex - i|, n - |startIndex - i|)
*/
int closestTarget1(vector<string>& words, string target, int startIndex) {
    int n = words.size();
    int ans = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (words[i] == target) {
            int dis = abs(startIndex - i);  // direct distance
            dis = min(dis, n - dis);        // minimum distance considering direct distance and circular distance
            ans = min(ans, dis);            // minimum distance so far
        }
    }

    return (ans == INT_MAX) ? -1 : ans;
}

// Approach2 (Two-Pointer Expansion from Start Index) : Time Complexity : O(n) __ Space Complexity : O(1)
/*
-- Approach (Two-Pointer Expansion from Start Index) -- 

• Start from startIndex and expand in both directions simultaneously:
    • l moves left (counterclockwise)
    • r moves right (clockwise)
• At each step, check if either words[l] or words[r] matches the target.
• The first time we encounter the target, return the distance immediately 
  since we’re expanding level by level (like BFS), ensuring the shortest path.
  - when we find a match, we must consider the minimum distance till that location which could be either the direct distance
    or the circular distance. 
    So, we do : 
            int dis = abs(startIndex - l);
            return min(dis, n-dis);
• Use modulo arithmetic to handle circular movement:
    • Left: (l - 1 + n) % n
    • Right: (r + 1) % n
| We can also use the following conditions to handle circular movement:
    if (l == 0) l = n-1;            // move l to right end if it tries to move 1 step backward from 0th position
    else l--;
    if (r == n-1) r = 0;            // move r to left end if it tries to move 1 step forward from last position
    else r++;

• Loop runs up to n/2 steps because beyond that we’d start revisiting positions from the other direction.
  Since l moves left and r moves right in a circular manner, and both pointers move at the same time, the two pointers can 
  cover the array size 'n' in 'n/2' steps, after these n/2 steps, both the pointers would start re-visiting positions
  from other direction (l will move to r's positions and r will move to l's position)
• If target is not found after full expansion, return -1.

>> Key Idea:
Simultaneously explore both directions from the start index, guaranteeing the first match is at the minimum circular distance.
*/
int closestTarget(vector<string>& words, string target, int startIndex) {
    int n = words.size();
    int l = startIndex, r = startIndex;
    
    for (int i = 0; i <= n / 2; i++) {
        if (words[l] == target) {
            int dis = abs(startIndex - l);
            return min(dis, n-dis);
        }
        if (words[r] == target) {
            int dis = abs(startIndex - r);
            return min(dis, n-dis);
        }

        l = (l - 1 + n) % n;
        r = (r + 1) % n;
        
        // if (l == 0) l = n-1;
        // else l--;
        // if (r == n-1) r = 0;
        // else r++;
    }
    return -1;
}

// same logic just using 'while' loop instead of 'for'
int closestTarget(vector<string>& words, string target, int startIndex) {
    int n = words.size();
    int l = startIndex, r = startIndex;
    int steps = 0;
    while (steps <= n/2) {
        if (words[l] == target) {
            int dis = abs(startIndex - l);
            return min(dis, n-dis);
        }
        if (words[r] == target) {
            int dis = abs(startIndex - r);
            return min(dis, n-dis);
        }

        l = (l - 1 + n) % n;
        r = (r + 1) % n;
        
        steps++;
    }
    return -1;
}

int main() {
    return 0;
}