/*
Leetcode - 1456. Maximum Number of Vowels in a Substring of Given Length : Medium

Given a string s and an integer k, return the maximum number of vowel letters in any substring of s with length k.
Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.

Examples :-

Input: s = "abciiidef", k = 3
Output: 3
Explanation: The substring "iii" contains 3 vowel letters.

Input: s = "aeiou", k = 2
Output: 2
Explanation: Any substring of length 2 contains 2 vowels.

Input: s = "leetcode", k = 3
Output: 2
Explanation: "lee", "eet" and "ode" contain 2 vowels.

Constraints :-
• 1 <= s.length <= 10^5
• s consists of lowercase English letters.
• 1 <= k <= s.length
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach: Time Complexity : O(n x k) __ Space Complexity : O(1)
/*
>> Intuition
We can consider every possible substring of length k and count the number of vowels present in it. 
For each starting index, iterate through the next k characters and increment a counter whenever we encounter a vowel. 
Maintain the maximum vowel count (maxCnt) encountered across all possible substrings.

>> Complexity Analysis
- Time Complexity: O(n x k) — For every possible starting index, we traverse k characters to count vowels.
- Space Complexity: O(1) — Only a constant number of variables are used.
*/

// Helper method for vowel check
bool isVowel(char& ch) {
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

int maxVowelsBrute(string s, int k) {
    int n = s.size();
    int maxCnt = 0;

    for(int i = 0; i <= n - k; i++) {
        int cnt = 0;

        for(int j = i; j < i + k; j++) {
            if(isVowel(s[j]))
                cnt++;
        }

        maxCnt = max(maxCnt, cnt);
    }

    return maxCnt;
}

// Optimal Approach (Fixed-Size Sliding Window (Two Pointers)): Time Complexity : O(n) __ Space Complexity : O(1)
/*
>> Intuition
We can maintain a fixed-sized window of k characters and calculate the number of vowels present in it. 
Since we need the maximum number of vowels, we maintain the maximum vowel count (maxCnt) encountered so far.

Instead of recounting all the vowels whenever the window moves, 
we can efficiently update the current vowel count by considering the characters entering and leaving the window. 
When we slide the window one position to the right:
- If the incoming character (s[r]) is a vowel, increment the count.
- If the outgoing character (s[l]) is a vowel, decrement the count.

After updating the window, we maintain the maximum vowel count and continue sliding 
until all possible substrings of length k have been considered.

>> Complexity Analysis
- Time Complexity: O(n) — Both pointers traverse the string at most once. 
  Each character is checked for being a vowel a constant number of times.
- Space Complexity: O(1) — Only a constant number of variables are used.
*/

int maxVowels1(string s, int k) {
    int n = s.size();

    int cnt = 0, maxCnt = 0;
    int l = 0, r = 0;

    while(r < n) {
        if(isVowel(s[r])) cnt++;

        if(r - l + 1 == k) {
            maxCnt = max(maxCnt, cnt);

            if(isVowel(s[l])) cnt--;
            l++;
        }

        r++;
    }

    return maxCnt;
}

int maxVowels2(string s, int k) {
    int n = s.size();

    int cnt = 0;
    for (int i = 0; i < k; i++) {
        if (isVowel(s[i]))
            cnt++;
    }

    int maxCnt = cnt;
        
    for (int i = k; i < n; i++) {
        if (isVowel(s[i])) cnt++;           // character entering the window
        if (isVowel(s[i - k])) cnt--;       // character leaving the window

        maxCnt = max(maxCnt, cnt);
    }

    return maxCnt;
}

int main() {
    return 0;
}