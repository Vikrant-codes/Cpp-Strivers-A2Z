/*
Highest / Lowest Frequency Elements

Given an array of n elements.
Return the highest and lowest frequency elements in a result vector.
If there are multiple elements that have the highest frequency or lowest frequency, pick the smallest element.
The result vector must have the highest frequency element at 0th index and lowest frequency element at 1st index.

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

// Time Complexity : O(n) __ Space Complexity : O(n)
/*
We can use an unordered map to store the frequency of all elements.
    `unordered_map<int, int> freq;`
Then, we can traverse the map and track the maximum and minimum frequency element.

Initially, we consider the first array element to be the maximum and minimum frequency element.
then, we traverse the map and for each (num, count) pair of map,
if the current element's freq (`count`) is greater than the frequency of max_freq_element,
we update our max_freq_element, by re-assigning the value of `num` to it.
Also, in case when count == freq[max_freq_element], we track it such that max_freq_element holds the smaller value.

Similarly, we can also track the minimum frequency element, 
while making sure it holds the smaller value in case of count == freq[min_freq_element].
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