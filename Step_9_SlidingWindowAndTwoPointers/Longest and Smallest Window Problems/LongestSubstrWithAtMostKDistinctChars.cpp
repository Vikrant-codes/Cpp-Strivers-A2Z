#include <bits/stdc++.h>
using namespace std;

// Longest Substring with At Most K Distinct Characters
/*
Given a string s and an integer k, find the length of the longest substring containing at most k distinct characters.
A substring is a contiguous sequence of characters within a string.

Example:
s = "aaabbccd", k = 2
Output: 5
Explanation:
The longest valid substring is "aaabb".
- It has 5 characters.
- It contains only 2 distinct characters: 'a' and 'b'.
So, the answer is 5.
*/

// Brute Force: Time Complexity : O(N²) __ Space Complexity : O(k)
/*
>> Brute Force — Generate all substrings
- Consider every possible starting index i.
- Extend the substring by moving j towards the right.
- Maintain a frequency map to keep track of distinct characters.
- If the number of distinct characters is at most k, update maxLen.
- If the number of distinct characters exceeds k, break immediately.

Why break?
Once a substring contains more than k distinct characters, extending it further cannot reduce 
the number of distinct characters. So no longer substring starting at the same i can be valid.

>> Complexity Analysis:
- Time: O(N²) average
- Auxiliary Space: O(1), assuming a fixed character set. 
  The map contains at most k + 1 distinct characters before we break. Thus, O(k + 1).
*/
int longestKSubstrBrute(string& s, int k) {
    int n = s.size();
    int maxLen = 0;

    for(int i = 0; i < n; i++) {
        unordered_map<char, int> mp;

        for(int j = i; j < n; j++) {
            mp[s[j]]++;

            if(mp.size() > k)
                break;

            maxLen = max(maxLen, j-i+1);
        }
    }

    return maxLen;
}

// Sliding Window: Time Complexity : O(2N) __ Space Complexity : O(1)
/*
>> Naive Sliding Window -- Intuition
We can optimize the brute-force approach using a sliding window [l, r].
1. Expand the window by moving r to the right.
2. Add s[r] to the frequency map.
3. If the number of distinct characters exceeds k, the window becomes invalid.
4. Shrink the window from the left until the number of distinct characters becomes at most k.
5. Update maxLen using the current valid window length.

We will also have to remove a character from the map when its frequency becomes zero.

>> Complexity:
- Time: O(2N) average. Both pointers traverse the string at most once.
- Auxiliary Space: O(1), assuming a fixed character set.
  The map can contain at most `k + 1` distinct characters, so in worst case, 
  considering each character has frequency 1, the map can store upto `k + 1` elements before window is shifted.
  So, O(k + 1)
*/
int longestKSubstrNaiveSliding(string& s, int k) {
    int n = s.size();
    int l = 0, r = 0;
    int maxLen = 0;

    unordered_map<char, int> mp;

    while(r < n) {
        mp[s[r]]++;

        while(mp.size() > k) {
            mp[s[l]]--;

            if(mp[s[l]] == 0)
                mp.erase(s[l]);

            l++;
        }

        maxLen = max(maxLen, r-l+1);
        r++;
    }

    return maxLen;
}

// Optimized Sliding Window: Time Complexity : O(N) __ Space Complexity : O(1)
/*
>> Intuition
Instead of shrinking down the window till it becomes valid again, we can maintain a fixed window of previous valid length
and expand the size only when the window becomes valid again.
*/
int longestKSubstr(string& s, int k) {
    int n = s.size();
    int l = 0, r = 0;
    int maxLen = 0;

    unordered_map<char, int> mp;

    while(r < n) {
        mp[s[r]]++;

        if(mp.size() > k) {
            mp[s[l]]--;

            if(mp[s[l]] == 0)
                mp.erase(s[l]);

            l++;
        }

        if(mp.size() <= k) {
            maxLen = max(maxLen, r-l+1);
        }

        r++;
    }

    return maxLen;
}

int main() {
    return 0;
}