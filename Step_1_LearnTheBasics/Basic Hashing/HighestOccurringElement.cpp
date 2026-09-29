/*
TUF - 296. Highest Occurring Element in an Array

Given an array nums of n integers, find the most frequent element in it i.e., 
the element that occurs the maximum number of times. 
If there are multiple elements that appear a maximum number of times, find the smallest of them.

Examples :-

Input: nums = [1, 2, 2, 3, 3, 3]
Output: 3
Explanation: The number 3 appears the most (3 times). It is the most frequent element.

Input: nums = [4, 4, 5, 5, 6]
Output: 4
Explanation: Both 4 and 5 appear twice, but 4 is smaller. So, 4 is the most frequent element.

Input: nums = [2, 4, 3, 2, 5, 4]
Output: 2

Constraints :-
• 1 <= n <= 10^5
• 1 <= nums[i] <= 10^4
*/

#include <bits/stdc++.h>
using namespace std;

/*
>> Intuition
We can use an unordered_map to store the frequency of every element in the array.
    `unordered_map<int, int> freq;`

Once we have the frequencies, we can traverse the map and keep track of the element with the maximum frequency
Initially, we consider the first array element as the maximum-frequency element.

Then, while traversing the map, for every (num, count) pair (for every key-value pair of map):
• If the current element's frequency count is greater than the frequency of maxFreqEle, we update maxFreqEle to num.
• If count is equal to the frequency of maxFreqEle, then both elements have the same frequency, 
    so we need to apply the tie-breaking condition: the smaller value should be chosen. 
    Therefore, we update maxFreqEle only if num < maxFreqEle.

>> Complexity Analysis
Let n be the size of the array and k be the number of distinct elements.

Time: O(n) average — O(n) to build the frequency map + O(k) to traverse it, where k ≤ n.
Space: O(k) — the frequency map stores each distinct element and its frequency.
*/

// My solution
int mostFrequentElement(vector<int>& nums) {
    unordered_map<int, int> freq;

    for (int x : nums)
        freq[x]++;
    
    int ans = nums[0];

    for (auto& p : freq) {
        /*
        if (p.second > freq[ans])
            ans = p.first;
        
        else if (p.second == freq[ans])
            ans = min(ans, p.first);
        */

        if (p.second > freq[ans] || (p.second == freq[ans] && p.first < ans))
            ans = p.first;
    }

    return ans;
}

// ChatGPT solution
int mostFrequentElement_(vector<int>& nums) {
    unordered_map<int, int> freq;
    
    for (int x : nums)
        freq[x]++;

    int ans = INT_MAX;
    int maxFreq = 0;
    
    /*
    for (auto& it : freq) {
        int element = it.first;
        int count = it.second;
        
        if (count > maxFreq || (count == maxFreq && element < ans)) {
            ans = element;
            maxFreq = count;
        }
    }
    */

    for (auto& [num, count] : freq) {
        if (count > maxFreq || (count == maxFreq && num < ans)) {
            ans = num;
            maxFreq = count;
        }
    }

    return ans;
}

int main() {
    return 0;
}