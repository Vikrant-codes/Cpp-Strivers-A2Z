/*
Leetcode - 1781. Sum of Beauty of All Substrings : Medium

The beauty of a string is the difference in frequencies between the most frequent and least frequent characters.
For example, the beauty of "abaacc" is 3 - 1 = 2.
Given a string s, return the sum of beauty of all of its substrings.

Examples :-
Input: s = "aabcb" __ Output: 5
Input: s = "aabcbaa" __ Output: 17

Constraints :
- 1 <= s.length <= 500
- s consists of only lowercase English letters.
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach :- Time Complexity : O(n * n * 26) ≈ O(n * n) __ Space Complexity : O(26) ≈ O(1)
/*
✅ Intuition 
How to find beauty of a string / substring ?
Beauty is the difference in frequencies between the most frequent and least frequent character.
So, we find the highest & lowest frequency, and by finding the difference we can get the beauty of the string/substring.
We can use a vector of size 26 (lowercase alphabets only) to keep track of frequency count of different alphabets.

Now, we want to find the sum of beauty of all substrings, that is easy. 
We want the frequency arrays of the substrings to get the beauty of the substrings.
While generating substring, instead of creating substrings, we create the frequency vector for the starting index 
and then update that vector.
Ex - "abacb" 
Consider the substrings starting at index 0 :- "a", "ab", "aba", "abac" & "abacb".
We can initialize a empty freq vector for index 0, then while looping through the substrings, we can update this vector.

⚛️ Algorithm :
1. Initialize : sum = 0, n = s.size()
2. For every starting index i from 0 to n-1:
    • Initialize a frequency array freq[26] with zeros
3. For every ending index j from i to n-1:
    • Increment frequency of character s[j]
    • Compute beauty of the current substring:
        • Find maximum frequency mx
        • Find minimum non-zero frequency mn
        • beauty = mx - mn
    • Add beauty to sum : sum += beauty
4. Return sum

⏱ Time Complexity
• Outer loop (i) → O(n)
• Inner loop (j) → O(n)
• Beauty calculation scans 26 characters → O(1)
Overall Time Complexity: O(n ^ 2)

💾 Space Complexity
• Frequency array of size 26 → O(1)
• No extra data structures
Overall Space Complexity: O(1)
*/
int beauty(vector<int>& freq) {
    int mx = 0, mn = 999;
    for (int x : freq) {
        mx = max(mx, x);
        if (x != 0) mn = min(mn, x);
    }
    return mx - mn;
}

int beautySum(string s) {
    int sum = 0;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        vector<int> freq(26);
        for (int j = i; j < n; j++) {
            freq[s[j]-'a']++;
            sum += beauty(freq);
        }
    }
    return sum;
}

int main() {
    return 0;
}