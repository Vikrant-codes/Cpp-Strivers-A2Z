/*
Leetcode - 3. Longest Substring Without Repeating Characters : Medium

Given a string s, find the length of the longest substring without duplicate characters.

Examples :-

Input: s = "abcabcbb" __ Output: 3
Explanation: The answer is "abc", with the length of 3. Note that "bca" and "cab" are also correct answers.

Input: s = "bbbbb" __ Output: 1
Explanation: The answer is "b", with the length of 1.

Input: s = "pwwkew" __ Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.

Constraints :-
• 0 <= s.length <= 10^5
• s consists of English letters, digits, symbols and spaces.
*/

#include<bits/stdc++.h>
using namespace std;

// Brute Force Approach: Time Complexity : O(N³) __ Space Complexity : O(N)
/*
Generate all possible substrings and check whether each substring contains any repeating characters. 
If a substring contains only unique characters, calculate its length and update the maximum length encountered so far.

We can use a set to keep track of the characters present in the current substring. 
If we encounter a character that is already in the set, the substring is no longer valid.

>> Complexity Analysis
- Time Complexity: O(N³) — We generate O(N²) substrings and 
  check each substring for duplicate characters, which takes up to O(N).
- Space Complexity: O(N) — The set can store up to N distinct characters.
*/
int lengthOfLongestSubstringBrute(string s) {
    int n = s.size();
    int maxLen = 0;

    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            // check if the substring s[i ... j] contains no repeating characters, if so, update maxLen accordingly

            unordered_set<char> st;

            for(int x = i; x <= j; x++) {
                if(st.count(s[x]))
                    break;

                st.insert(s[x]);
            }

            // if set size == substring length, means no repeating characters in substring
            if(st.size() == j - i + 1)
                maxLen = max(maxLen, j - i + 1);
        }
    }

    return maxLen;
}

// Optimized Brute Force Approach: Time Complexity : O(N²) __ Space Complexity : O(N)
/*
We can avoid checking every substring independently. 
Instead, fix a starting index i and keep extending the substring by moving j towards the end of the string.

Maintain a set containing the characters present in the current substring. 
As we extend the substring, check whether the newly encountered character already exists in the set.
- If the character is not present, insert it and update the maximum length.
- If the character is already present, we know that extending this substring further from the same starting index 
  cannot produce a valid substring, so we stop and move to the next starting index.

This way, we avoid repeatedly checking all characters of every substring.

>> Complexity Analysis
- Time Complexity:O(N²) — We have two nested loops, and set insertion and lookup take O(1) on average.
- Space Complexity: O(min(N, Σ)) — The set stores distinct characters, where Σ is the character-set size.
*/
int lengthOfLongestSubstringBetter(string s) {
    int n = s.size();
    int maxLen = 0;

    for(int i = 0; i < n; i++) {
        // unordered_set<char> st;
        vector<int> hash(256, 0);

        for(int j = i; j < n; j++) {
            // if(st.count(s[j])) break;
            if (hash[s[j]] == 1) break;
            
            // st.insert(s[j]);
            hash[s[j]] = 1;

            maxLen = max(maxLen, j - i + 1);
        }
    }

    return maxLen;
}

// Optimal Approach (Variable-Size Sliding Window (Two Pointers)): Time Complexity : O(2N) __ Space Complexity : O(N)
/*
>> Intuition

Instead of generating substrings with every possible starting index, 
we can maintain a single window using two pointers, l and r.

We expand the window by moving r and include the newly encountered character. 
We maintain a set to keep track of the characters currently present in the window.

If the newly encountered character is already present in the set, 
it means the current window contains a repeating character. 
To make the window valid again, we shrink it from the left by removing characters from the set and 
incrementing l until the duplicate character is removed.

Once the window becomes valid (contains only unique characters), calculate its length and update maxLen.

By doing this, both pointers traverse the string without repeatedly processing the entire window, 
giving us a linear-time solution.

>> Complexity Analysis

- Time Complexity: O(2N) — Both pointers traverse the string at most once. 
  Each character is inserted into and removed from the set at most once.

- Space Complexity: O(min(N, Σ)) — The set stores distinct characters, where Σ is the character-set size.
  If we use hash array, the extra space would be O(256) ~ O(1)
*/
int lengthOfLongestSubstring1(string s) {
    int n = s.size();
    int maxLen = 0;

    unordered_set<char> st;
    // vector<int> hash(256, 0);

    int l = 0, r = 0;

    while(r < n) {
        // if the `r` pointer character is repeating in current substring 
        while(st.count(s[r])) {
            st.erase(s[l]);         // remove the lth character from set as substring is being shrunken
            l++;                    // shrink the substr
        }

        // while (hash[s[r]]) {
            // hash[s[l]] = 0;
            // l++; 
        // }

        st.insert(s[r]);
        // hash[s[r]] = 1;

        maxLen = max(maxLen, r - l + 1);
        r++;
    }

    return maxLen;
}

// Striver's Solution: Time Complexity : O(N) __ Space Complexity : O(1)
/*
>> Intuition

We can further optimize the sliding window approach by using a hash array to store the last seen index of each character, 
instead of maintaining a set of characters currently present in the window.

We initialize the hash array with -1, indicating that a character has not been encountered yet. 
Whenever we encounter a character at index r, we check its last seen index using hash[s[r]].

There are two possibilities:
1. Character has not been seen before: Its stored index will be -1, so we can safely include it in the current window.

2. Character has been seen before: We need to check whether its last seen occurrence actually 
   lies inside our current window. This is important because a character might have appeared earlier in the string 
   but could already be outside the current window.

   - If hash[s[r]] >= l, the previous occurrence is inside the current window, meaning we have a duplicate. 
   We can directly move l to hash[s[r]] + 1, skipping all the characters before and including the previous occurrence.

   - If hash[s[r]] < l, the previous occurrence is outside the current window, so it doesn't cause any repetition. 
   We can safely include the current character.

After ensuring that the current window contains no repeating characters, 
update the character's last seen index to r, calculate the current window length, and update maxLen.

>> Why is this better? 
In the previous set/hasharray-based approach, we shrink the window one character at a time until the duplicate is removed. 
Here, since we already know the previous occurrence's index, we can directly jump l to the position immediately after it.

>> Understanding the hash[s[r]] >= l condition
Consider the following string: s = "abba"

Step 1: Process the first three characters
Index:  0  1  2
String: a  b  b
        └─────┘

When we reach the second b (index 2):
- hash['b'] = 1
- l = 0
- Since 1 >= 0, the previous b is inside the current window.
Therefore, move l = 1 + 1 = 2.

Step 2: Process the final character
Index:  0  1  2  3
String: a  b  b  a
               └───┘

When we reach the final a (index 3):
- hash['a'] = 0
- l = 2
- Since 0 < 2, the previous a is outside the current window.
Therefore, it is not a duplicate within our current substring. We can safely include it.

Final maximum length: 2
The longest valid substrings include "ab", and "ba".

This example demonstrates why simply checking whether a character has appeared before is insufficient. 
We must check whether its previous occurrence is still inside the current window.

>> Complexity Analysis
- Time Complexity: O(N) — The right pointer traverses the string once. 
  The left pointer jumps directly to the required position, and each iteration performs constant-time operations.

- Space Complexity: O(1) — The hash array has a fixed size of 256, assuming an extended ASCII character set.
*/
int lengthOfLongestSubstring(string s) {
    int n = s.size();
    int maxLen = 0;

    vector<int> hash(256, -1);
    int l = 0, r = 0;

    while (r < n) {

        // Check if the character was previously encountered
        if (hash[s[r]] != -1) {

            // Check if its previous occurrence is inside the window
            if (hash[s[r]] >= l) {
                l = hash[s[r]] + 1;
            }
        }

        // Update the last seen index
        hash[s[r]] = r;

        maxLen = max(maxLen, r - l + 1);

        r++;
    }

    return maxLen;
}


int main() {
    return 0;
}