/*
Leetcode - 451. Sort Characters By Frequency : Medium

Given a string s, sort it in decreasing order based on the frequency of the characters. 
The frequency of a character is the number of times it appears in the string.
Return the sorted string. If there are multiple answers, return any of them.

Examples :-

Input: s = "tree" __ Output: "eert"
Explanation: 'e' appears twice while 'r' and 't' both appear once.
So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.

Input: s = "cccaaa" __ Output: "aaaccc"
Explanation: Both 'c' and 'a' appear three times, so both "cccaaa" and "aaaccc" are valid answers.
Note that "cacaca" is incorrect, as the same characters must be together.

Input: s = "Aabb" __ Output: "bbAa"
Explanation: "bbaA" is also a valid answer, but "Aabb" is incorrect.
Note that 'A' and 'a' are treated as two different characters.
 
Constraints :-
1 <= s.length <= 5 * 10^5
s consists of uppercase and lowercase English letters and digits.
*/

#include<bits/stdc++.h>
using namespace std;

// Hashing Approach :- Time Complexity : O(n + k log k) ≈ O(n) (since k ≪ n) __ Space Complexity : O(n)
/*
🧠 Intuition
We want to rearrange the characters of string s so that:
- Characters that appear more frequently come first.
- The relative order among equal frequencies doesn’t matter.
So essentially:- "Sort characters in descending order of their frequency."
This can be easily done if we first count frequencies and then sort by them.

⚙️ Algorithm
1. Count the frequency of each character
2. Store frequency pairs in a vector for sorting (since sorting by value of map can be done through using a vector)
3. Sort the vector in descending order of frequency using a custom comparator 
    comparator = [] (auto &a, auto &b) {return a.second > b.second;}
4. Reconstruct the output string:
    - For each pair (char, freq) in sorted vector:- Append that character freq times to result string.
5. Return the final string.

⏱️ Complexity Analysis
| Step            | Operation              | Time Complexity     | Space Complexity                                           |
| --------------- | ---------------------- | ------------------- | -----------------------------------------------------------|
| Frequency count | Single pass            | **O(n)**            | O(k) — where k <= 62 (52 alphabets (A-Z, a-z) + 10 digits) |
| Sorting         | Sort unique characters | **O(k log k)**      | O(k)                                                       |
| Building output | Appending chars        | **O(n)**            | O(n)                                                       |
| **Total**       |                        | **O(n + k log k)**  | **O(n)**                                                   |
Total Time Complexity :- O(n + k log k) ≈ O(n) (since k ≪ n)

🧩 Intuition Summary
- Map step: Know how many times each character appears.
- Sort step: Bring most frequent ones to the front.
- Build step: Reconstruct string respecting frequencies.
*/
string frequencySort(string s) {
    unordered_map<char, int> freq;
    for (char ch : s) freq[ch]++;

    vector<pair<char, int>> v (freq.begin(), freq.end());

    sort (v.begin(), v.end(), [] (auto &a, auto &b) {
        return a.second > b.second;
    });
    
    string ans = "";
    for (auto ele : v) {
        char x = ele.first;
        int y = ele.second;
        while (y--) {
            ans += x;
        } 
    }
    return ans;
}

int main() {
    return 0;
}