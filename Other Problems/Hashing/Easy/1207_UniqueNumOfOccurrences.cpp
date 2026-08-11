/*
Leetcode - 1207. Unique Number of Occurrences : Easy

Given an array of integers arr, 
return true if the number of occurrences of each value in the array is unique or false otherwise.

Examples :-

Input: arr = [1,2,2,1,1,3] __ Output: true
Explanation: The value 1 has 3 occurrences, 2 has 2 and 3 has 1. No two values have the same number of occurrences.

Input: arr = [1,2] __ Output: false

Input: arr = [-3,0,1,-3,1,1,1,-3,10,0] __ Output: true

Constraints :-
• 1 <= arr.length <= 1000
• -1000 <= arr[i] <= 1000
*/

#include <bits/stdc++.h>
using namespace std;

/*
>> Find the number of occurrences of each value in the array.
To find these, we can either use a map or a frequency array of size 2001 (since -1000 <= arr[i] <= 1000).

>> Check for any duplicacy in the occurrences by using a set/map.
We can store these occurrences in a set/map to check for no duplicacy of these occurrences.
*/

bool uniqueOccurrences1(vector<int>& arr) {
    unordered_map<int, int> freq;

    for (int& x : arr)
        freq[x]++;
    
    unordered_set<int> st;
    
    for (auto p : freq) {
        if (st.count(p.second))
            return false;
        st.insert(p.second);
    }

    return true;
}

bool uniqueOccurrences2(vector<int>& arr) {
    vector<int> freq(2001);

    for (int& x : arr)
        freq[x+1000]++;
    
    set<int> st;
    
    for (int& f : freq) 
        if (f != 0) {
            if (st.count(f))
                return false;
            st.insert(f);
        }
    
    return true;
}

int main() {
    return 0;
}