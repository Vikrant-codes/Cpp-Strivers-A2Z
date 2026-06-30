/*
Leetcode - 1358. Number of Substrings Containing All Three Characters : Medium

Given a string s consisting only of characters a, b and c.
Return the number of substrings containing at least one occurrence of all these characters a, b and c.

Examples :-

Input: s = "abcabc" __ Output: 10
Explanation: The substrings containing at least one occurrence of the characters a, b and c are 
"abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again). 

Input: s = "aaacb" __ Output: 3
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "aaacb", "aacb" and "acb". 

Input: s = "abc" __ Output: 1

Constraints :-
- 3 <= s.length <= 5 x 10^4
- s only consists of a, b or c characters.
*/

#include <bits/stdc++.h>
using namespace std;

// Two Pointers & Sliding Window Approach : Time Complexity : O(2*n) __ Space Complexity : O(1)
bool containsAll(vector<int> freq) {
    if (freq[0] > 0 && freq[1] > 0 && freq[2] > 0) 
        return true;
    return false;
}

int numberOfSubstrings(string s) {
    vector<int> freq(3);

    int ans = 0, n = s.size();
    int i = 0, j = 0;

    while (i <= n - 3 && j < n) {
        freq[s[j] - 'a']++;
        if (containsAll(freq)) {
            int k = i;
            while (containsAll(freq)) {
                freq[s[k] - 'a']--;
                k++;
            }

            ans += (k - i) * (n - j);
            i = k;
        }

        j++;
    }

    return ans;
}

int main() {
    return 0;
}