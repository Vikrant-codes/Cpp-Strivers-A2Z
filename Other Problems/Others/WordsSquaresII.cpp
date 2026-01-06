/*
Leetcode - 3799. Word Squares II : Medium

You are given a string array words, consisting of distinct 4-letter strings, each containing lowercase English letters.

A word square consists of 4 distinct words: top, left, right and bottom, arranged as follows:
• top forms the top row.
• bottom forms the bottom row.
• left forms the left column (top to bottom).
• right forms the right column (top to bottom).

It must satisfy:
• top[0] == left[0], top[3] == right[0]
• bottom[0] == left[3], bottom[3] == right[3]

Return all valid distinct word squares, sorted in ascending lexicographic order by the 4-tuple (top, left, right, bottom)​​​​​​​.

Examples :-

Input: words = ["able","area","echo","also"]
Output: [["able","area","echo","also"],["area","able","also","echo"]]
Explanation:
There are exactly two valid 4-word squares that satisfy all corner constraints:
"able" (top), "area" (left), "echo" (right), "also" (bottom)
top[0] == left[0] == 'a'
top[3] == right[0] == 'e'
bottom[0] == left[3] == 'a'
bottom[3] == right[3] == 'o'
"area" (top), "able" (left), "also" (right), "echo" (bottom)
All corner constraints are satisfied.
Thus, the answer is [["able","area","echo","also"],["area","able","also","echo"]].

Input: words = ["code","cafe","eden","edge"]
Output: []
Explanation:
No combination of four words satisfies all four corner constraints. Thus, the answer is empty array [].

Constraints :-
• 4 <= words.length <= 15
• words[i].length == 4
• words[i] consists of only lowercase English letters.
• All words[i] are distinct.
*/

#include <bits/stdc++.h>
using namespace std;

// BruteForce Approach : Time Complexity : O(n^4) __ Space Complexity : O(1)

vector<vector<string>> wordSquares(vector<string>& words) {
    vector<vector<string>> ans;
    
    for (string& top : words) {
        // serach for left
        for (string& left : words) {
            // if left is found
            if (left[0] == top[0] && left != top) {
                // search for right
                for (string &right : words) {
                    // if right is found
                    if (right[0] == top[3] && right != left && right != top) {
                        // search for bottom 
                        for (string &bottom : words) {
                            // if bottom is found
                            if (bottom[0] == left[3] && bottom[3] == right[3] && bottom != left && bottom != right && bottom != top) {
                                ans.push_back({top, left, right, bottom});
                            }
                        }
                    }
                }
            }
        }
    }

    sort(ans.begin(), ans.end());
    
    return ans;
}


int main() {
    return 0;
}