/*
Highest / Lowest Frequency Elements

Given an integer array nums, find:
1. The element with the highest frequency.
2. The element with the lowest frequency.

If there are multiple elements that have the highest frequency or lowest frequency, pick the smallest element.

Return the result as: {mostFrequentElement, leastFrequentElement}

Examples :-

Input: nums = [1, 2, 3, 1, 1, 4]
Output: [1, 2]
Explanation: The element having the highest frequency is '1', and the frequency is 3. 
The elements with the lowest frequencies are '2', '3', and '4'. 
Since we need to pick the smallest element, we pick '2'. Hence we return [1, 2].

Input: nums = [10, 10, 10, 3, 3, 3]
Output: [3, 3]
Explanation: Since the frequency of '3' and '10' is 3. Therefore, the element with the maximum and minimum frequency is '3'.

Constraints :-
• 2 <=  n <= 10^4
• 1 <= v[i] <= 10^9
• There are at least two distinct elements in the array.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Time Complexity : O(n + k) __ Space Complexity : O(k)
/*
We can use an unordered_map to store the frequency of every element in the array.
    `unordered_map<int, int> freq;`

Once we have the frequencies, we can traverse the map and keep track of the element with the maximum frequency 
and the element with the minimum frequency.

Initially, we consider the first array element as both the maximum-frequency and minimum-frequency element.

Then, while traversing the map, for every (num, count) pair:
• If the current element's frequency count is greater than the frequency of maxFreqEle, we update maxFreqEle to num.
• If count is equal to the frequency of maxFreqEle, then both elements have the same frequency, 
    so we need to apply the tie-breaking condition: the smaller value should be chosen. 
    Therefore, we update maxFreqEle only if num < maxFreqEle.

Similarly, we track the minimum-frequency element:
• If count is less than the frequency of minFreqEle, we update minFreqEle to num.
• If count is equal to the frequency of minFreqEle, we again apply the tie-breaking condition and keep the smaller value.

So, while traversing the frequency map, we are essentially maintaining two candidates:
maxFreqEle → highest frequency, and smallest value in case of a tie
minFreqEle → lowest frequency, and smallest value in case of a tie

This lets us find both required elements in a single traversal of the frequency map.

>> Complexity Analysis
Let n be the size of the array and k be the number of distinct elements.

Time: O(n) average — O(n) to build the frequency map + O(k) to traverse it, where k ≤ n.
Space: O(k) — the frequency map stores each distinct element and its frequency.
*/
vector<int> getFrequencies(vector<int>& nums) {
    unordered_map<int, int> freq;

    for (int& x : nums) 
        freq[x]++;

    int maxFreqEle = nums[0], minFreqEle = nums[0];

    for (auto& it : freq) {
        int num = it.first;
        int count = it.second;

        if (count > freq[maxFreqEle] || (count == freq[maxFreqEle] && num < maxFreqEle)) {
            maxFreqEle = num;
        }

        if (count < freq[minFreqEle] || (count == freq[minFreqEle] && num < minFreqEle)) {
            minFreqEle = num;
        }
    }

    return {maxFreqEle, minFreqEle};
}

int main() {
    return 0;
}