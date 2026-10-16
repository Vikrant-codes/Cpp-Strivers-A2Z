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
• 1 <= s.length <= 5 * 10^5
• s consists of uppercase and lowercase English letters and digits.
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

    for (char& ch : s) freq[ch]++;

    vector<pair<char, int>> v (freq.begin(), freq.end());
    
    // sort the vector (in decreasing order of frequencies)
    sort(v.begin(), v.end(), [] (auto &a, auto &b) {
        return a.second > b.second;
    });
    
    string ans = "";
    
    for (auto& p : v) {
        char ch = p.first;
        int cnt = p.second;
        while (cnt--) {
            ans += ch;
        }
    }
    
    return ans;
}

// Comparators & lambda expressions ? Go to : 'Step_1 > Advanced > LambdaFn_and_Comparators.cpp' to understand them
/*
The comparator used here
    [] (auto &a, auto &b) {
        return a.second > b.second;
    }
This is a lambda function (anonymous function).
Meaning: a and b are two elements from vector v, each element is pair<char, int>.
So:
- a.second  -> frequency of first character
- b.second  -> frequency of second character
The comparator says: return a.second > b.second;
Which means: place the element with higher frequency first.
So sorting becomes descending order of frequency.

>> How sort actually uses it (step-by-step idea)

Suppose vector contains: [('a',3), ('b',1), ('c',2)]
sort repeatedly compares elements:
Example comparison: 
- comparator(('a',3), ('b',1))
  Checks: 3 > 1 → true
  So 'a' stays before 'b'.

- Another comparison: comparator(('c',2), ('a',3))
  Checks:
  2 > 3 → false
  So 'a' should come before 'c'.

After many such comparisons, final order becomes: ('a',3), ('c',2), ('b',1)
*/

// If string had only 'lowercase' characters, we could directly use a freq vector instead of using map. 
/*
string frequencySort(string s) {
    vector<pair<char, int>> freq;

    // initialize the freq pair vector
    for (char ch = 'a'; ch <= 'z'; ch++) {
        freq.push_back({ch, 0});
    } 
    
    // update frequencies
    for (char& ch : s) {
        int ind = ch - 'a';
        freq[ind].second++;
    }

    // sort the frequency vector (in decreasing order of frequencies)
    sort(freq.begin(), freq.end(), [] (auto &a, auto &b) {
        return a.second > b.second;
    });

    string ans = "";
    for (auto& p : freq) {
        char ch = p.first;
        int cnt = p.second;
        while (cnt--) {
            ans += ch;
        }
    }

    return ans;
}
*/

// TUF - 303. Sort Characters by Frequency
/*
TUF - 303. Sort Characters by Frequency

You are given a string s. Return the array of unique characters, sorted by highest to lowest occurring characters.
If two or more characters have same frequency then arrange them in alphabetic order.

Examples :-

Input : s = "tree" __ Output : ['e', 'r', 't' ]
Explanation :
The occurrences of each character are as shown below :
e --> 2
r --> 1
t --> 1.
The r and t have same occurrences , so we arrange them by alphabetic order.

Input : s = "raaaajj" __ Output : ['a' , 'j', 'r' ]
Explanation :
The occurrences of each character are as shown below :
a --> 4
j --> 2
r --> 1

Constraints :-
• 1 <= s.length <= 10^5
• s consist of only lowercase English characters. 
*/

// s can only have lowercase English characters, so we can use a freq vector of pair of char & int, instead of a map.
vector<char> frequencySort(string& s){
	vector<pair<char, int>> freq;

    // initialize the freq pair vector with default frequencies 0 for 'a' to 'z'
    for (char ch = 'a'; ch <= 'z'; ch++) {
        freq.push_back({ch, 0});
    }
    
    // update frequencies 
    for (char& ch : s) {
        int ind = ch - 'a';
        freq[ind].second++;
    }
    
    // sort the freq vector, decr. order of frequencies (alphabetical order for same frequency)
    sort(freq.begin(), freq.end(), [](auto &a, auto &b) {
        // if (a.second == b.second)
        //     return a.first < b.first;       // alphabetical order for same frequency
        // return a.second > b.second;         // decreasing order by frequency
        return (a.second == b.second) ? (a.first < b.first) : (a.second > b.second);
    });
    
    vector<char> ans;
    
    int ind = 0;
    while (ind < 26 && freq[ind].second != 0) {
        ans.push_back(freq[ind].first);
        ind++;
    }
    
    return ans;
}

int main() {
    return 0;
}