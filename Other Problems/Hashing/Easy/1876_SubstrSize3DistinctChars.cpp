/*
Leetcode - 1876. Substrings of Size Three with Distinct Characters : Easy

A string is good if there are no repeated characters.
Given a string s​​​​​, return the number of good substrings of length three in s​​​​​​.
Note that if there are multiple occurrences of the same substring, every occurrence should be counted.
A substring is a contiguous sequence of characters in a string.

Examples :-

Input: s = "xyzzaz"
Output: 1
Explanation: There are 4 substrings of size 3: "xyz", "yzz", "zza", and "zaz". 
The only good substring of length 3 is "xyz".

Input: s = "aababcabc"
Output: 4
Explanation: There are 7 substrings of size 3: "aab", "aba", "bab", "abc", "bca", "cab", and "abc".
The good substrings are "abc", "bca", "cab", and "abc".

Constraints :-
- 1 <= s.length <= 100
- s​​​​​​ consists of lowercase English letters.
*/

#include <bits/stdc++.h>
using namespace std;

// Sliding Window + HashMap Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Intuition 

We need to count substrings of length 3 where all characters are distinct.
Brute force thinking would be:
- Take every substring of length 3
- Check if all characters are different
This works, but checking distinctness repeatedly can be inefficient if done poorly.

>> Key observation
The substring length is fixed (3).
So instead of creating a new substring every time, we can:
- Maintain a window of size 3
- Move it one step at a time.
Example:-
s = "xyzzaz"
xyz  → check
 yzz → check
  zza → check
   zaz → check
Each step only changes:
- one new character enters
- one old character leaves
So we reuse previous work instead of recomputing from scratch.

# Why sliding window?
Because:
- consecutive substrings overlap heavily
- only one character changes between windows
Sliding window lets us update information in O(1) time instead of recomputing.

# Why a map?
We need to know:
| how many distinct characters exist in the current window.
The map stores: character → frequency inside current window

Example window: "yzz"
mpp = {
  'y': 1,
  'z': 2
}
Now, mpp.size() tells how many distinct characters exist.
If size becomes 3 → all characters are different.
So the map gives us:
- frequency tracking
- distinct count automatically

### Intuition of the algorithm step-by-step

Step 1 — Build initial partial window
You insert first two characters: mpp[s[0]]++; mpp[s[1]]++;
Now the window is ready to grow to size 3.

Step 2 — Expand window
At index i (for i in range 2 to s.size()): mpp[s[i]]++;
Now window size becomes 3.

Step 3 — Check condition
If: mpp.size() == 3
means all three characters are distinct.
So increment answer.

Step 4 — Slide the window
Now we move forward:
remove the leftmost character -- mpp[s[i-2]]--;
If its frequency becomes zero:
remove it from the substring window -- mpp.erase(s[i-2]);
This keeps the map representing only the current window.

### Time Complexity
Let n = s.size().
• The loop runs from index 2 to n-1 → O(n) iterations.
• In each iteration you perform:
    - insertion in unordered_map
    - decrement operation
    - possible erase
    - size check
All these operations in an unordered_map take O(1) average time.
Also,
• each character is inserted once and removed once from the map.
✅ Overall time complexity = O(n) (average case)

Note: In theory, unordered_map can degrade to O(n) per operation due to hash collisions, 
      but in practice and in interview analysis we consider it O(1) average.

### Space Complexity
• The sliding window size is fixed at 3.
• So the map can contain at most 3 keys at any time.
✅ Space complexity = O(1) (constant space)

Complexity Analysis
| Metric              | Complexity   |
| ------------------- | ------------ |
| Time                | O(n) average |
| Space               | O(1)         |
| Extra work per step | Constant     |
*/
int countGoodSubstringsMap(string s) {
    if (s.size() < 3)
        return 0;

    unordered_map<char, int> mpp;
    mpp[s[0]]++;
    mpp[s[1]]++;
    int cnt = 0;
    for (int i = 2; i < s.size(); i++) {
        mpp[s[i]]++;

        if (mpp.size() == 3)
            cnt++;
        
        mpp[s[i-2]]--;
        if (mpp[s[i-2]] == 0)
            mpp.erase(s[i-2]);
    }

    return cnt;
}

// Sliding Window + Frequency Array Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Here the idea is the same sliding window of size 3. The only change is how we track characters inside the window.

>> Why frequency array instead of map
Since characters are lowercase English letters ('a' to 'z'), we know:
• total possible characters = 26
• each character can be mapped directly to an index

So instead of storing: char → frequency (like, 'a' → count) in a hash map, we use a frequency array
freq[0] → count of 'a'
freq[1] → count of 'b'
...
freq[25] → count of 'z'
This avoids hashing and makes updates faster and simpler.

>> Role of the frequency array
The frequency array tells:
| how many times each character exists in the current window.
Example window "aba":-
freq['a'] = 2
freq['b'] = 1
So we always know whether a character is:
• entering the window for the first time
• still present
• completely removed

>> How to keep track of distinct chars in the sliding substring window
We want to know:
| how many different characters are currently in the window.
Instead of scanning the entire freq array every time, we maintain this count dynamically.

-- When adding a character
    if (freq[ch] == 0) distinct++;
    freq[ch]++;
 If its frequency was zero, it means this character was not present before → a new distinct character appeared.

-- When removing a character
    freq[ch]--;
    if (freq[ch] == 0) distinct--;
 If frequency becomes zero, that character no longer exists in the window → distinct count decreases.

Intuition in short
• freq[] keeps track of how many times each character exists.
• distinct keeps track of how many different characters exist.
• Because updates happen when characters enter or leave the window, we always know the distinct count in O(1) time.
So instead of recomputing distinct characters every step, we maintain the answer incrementally while sliding the window.
*/
int countGoodSubstrings(string s) {
    if (s.size() < 3) return 0;

    vector<int> freq(26, 0);
    int cnt = 0, distinct = 0;

    // for the first two characters of string
    for (int i = 0; i < 2; i++) {
        if (freq[s[i] - 'a'] == 0) distinct++;
        freq[s[i] - 'a']++;
    }

    for (int i = 2; i < s.size(); i++) {
        if (freq[s[i] - 'a'] == 0) distinct++;
        freq[s[i] - 'a']++;

        if (distinct == 3) cnt++;
            
        // remove leftmost char (the starting element of the current 3-sized substring)
        freq[s[i - 2] - 'a']--;
        if (freq[s[i - 2] - 'a'] == 0) distinct--;
    }
    return cnt;
}

int main() {
    return 0;
}