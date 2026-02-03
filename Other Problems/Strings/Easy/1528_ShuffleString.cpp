/*
Leetcode - 1528. Shuffle String : Easy

You are given a string s and an integer array indices of the same length. 
The string s will be shuffled such that the character at the ith position moves to indices[i] in the shuffled string.
Return the shuffled string.

Examples :-

Input: s = "codeleet", indices = [4,5,6,7,0,2,1,3] __ Output: "leetcode"
Explanation: As shown, "codeleet" becomes "leetcode" after shuffling.

Input: s = "abc", indices = [0,1,2] __ Output: "abc"
Explanation: After shuffling, each character remains in its position.
*/

#include <bits/stdc++.h>
using namespace std;

/*
✅ Intuition
The problem says: The character at position i in string s should be moved to position indices[i] in the result.
This basically means we are given a mapping: i → indices[i]
So character s[i] goes to ans[indices[i]].
To build the shuffled string, we simply need to:
- Create a new string ans of same length.
- For each position i, place the character s[i] into its correct final position.
- Return ans.
Since each character has a unique target position, it's a direct one-to-one mapping.

🎯 Algorithm
1. Let n = s.size().
2. Create a new string ans of size n (you used a copy of s, which is fine).
3. Use a pointer k = 0 to track characters from s.
4. For every value i in indices, place s[k] into ans[i].
5. Increment k.
6. Return the fully built ans.
*/

string restoreString(string s, vector<int>& indices) {
    string ans = s;
    int k = 0;
    for (int i : indices) {
        ans[i] = s[k++];
    }
    return ans;
}

string restoreString2(string s, vector<int>& indices) {
    string ans(s.size(), '-');      
    // creates a new string of length s.size() and fills every position with a given character — here, a dash '-'.
    
    for (int i=0; i<s.size(); i++) {
        ans[indices[i]] = s[i];
    }
    return ans;
}

int main() {
    return 0;
}