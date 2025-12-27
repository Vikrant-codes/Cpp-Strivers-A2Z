/*
Leetcode - 2053. Kth Distinct String in an Array : Easy

A distinct string is a string that is present only once in an array.
Given an array of strings arr, and an integer k, return the kth distinct string present in arr. 
If there are fewer than k distinct strings, return an empty string "".

Note that the strings are considered in the order in which they appear in the array.

Examples :-

Input: arr = ["d","b","c","b","c","a"], k = 2 __ Output: "a"
Explanation:
The only distinct strings in arr are "d" and "a".
"d" appears 1st, so it is the 1st distinct string.
"a" appears 2nd, so it is the 2nd distinct string.
Since k == 2, "a" is returned. 

Input: arr = ["aaa","aa","a"], k = 1 __ Output: "aaa"
Explanation:
All strings in arr are distinct, so the 1st string "aaa" is returned.

Input: arr = ["a","b","a"], k = 3 __ Output: ""
Explanation:
The only distinct string is "b". Since there are fewer than 3 distinct strings, we return an empty string "".

Constraints :-
- 1 <= k <= arr.length <= 1000
- 1 <= arr[i].length <= 5
- arr[i] consists of lowercase English letters.
*/

#include<bits/stdc++.h>
using namespace std;

// Hashing Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Use a hashmap to keep track of occurrence count of each string.
Now traverse the string array and for each distinct string (whose occurrence count is 1), check if it is the kth distinct.
If that string is kth distinct, return it.
return "" empty string at the end if kth distinct doesn't exist.
*/
string kthDistinct(vector<string>& arr, int k) {
    unordered_map<string, int> freq;
    for (string& s : arr) freq[s]++;
    int i = 0;
    for (string& s : arr) {
        if (freq[s] == 1) {
            i++;
            // if kth distinct i.e. when i == k
            if (i == k) return s;
        }
    }
    return "";
}

int main() {
    return 0;
}