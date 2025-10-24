/*
Leetcode - 771. Jewels and Stones : Easy

You're given strings jewels representing the types of stones that are jewels, and stones representing the stones you have. 
Each character in stones is a type of stone you have. You want to know how many of the stones you have are also jewels.
Letters are case sensitive, so "a" is considered a different type of stone from "A".

Examples :-

Input: jewels = "aA", stones = "aAAbbbb" __ Output: 3

Input: jewels = "z", stones = "ZZ" __ Output: 0

Constraints :-
1 <= jewels.length, stones.length <= 50
jewels and stones consist of only English letters.
All the characters of jewels are unique.
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach : Time Complexity : O(m * n) __ Space Complexity : O(1) -- m = jewels.size(), n = stones.size()
int numJewelsInStonesBrute(string jewels, string stones) {
    int cnt = 0;
    // for each jewel count the stones that are jewels
    for (int i=0; i<jewels.size(); i++) {
        for (int j=0; j<stones.size(); j++) {
            if (jewels[i] == stones[j]) cnt++;
        }
    }
    return cnt;
}

// Hashmap approach : Time Complexity : O(m+n) __ Space Complexity : O(m) -- m = jewels.size(), n = stones.size()
int numJewelsInStones(string jewels, string stones) {
    // store the jewels in a hashmap (unordered_map)
    unordered_set<char> jwls (jewels.begin(), jewels.end());
    int cnt = 0;
    // loop through the stones string and for each stone check whether it is present in jewels hasmap (i.e. check if it is a jewel)
    for(char c : stones) {
        if (jwls.find(c) != jwls.end()) cnt++;
    }
    return cnt;    
}

int main() {
    return 0;
}