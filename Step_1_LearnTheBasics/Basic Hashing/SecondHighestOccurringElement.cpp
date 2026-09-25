/*
TUF - 742. Second Highest Occurring Element

Given an array of n integers, find the second most frequent element in it.
If there are multiple elements that appear second most frequent times, find the smallest of them.
If second most frequent element does not exist return -1.

Examples :-

Input: arr = [1, 2, 2, 3, 3, 3]
Output: 2
Explanation:
The number 2 appears the second most (2 times) and number 3 appears the most(3 times). 

Input: arr = [4, 4, 5, 5, 6, 7]
Output: 6
Explanation:
Both 6 and 7 appear second most times, but 6 is smaller.

Constraints :-
• 1 <= n <= 10^5
• 1 <= arr[i] <= 10^4
*/

#include <bits/stdc++.h>
using namespace std;

int secondMostFrequentElement(vector<int>& nums) {
    unordered_map<int, int> freq;

    for (int x : nums)
        freq[x]++;
    
    int maxFreq = 0;
    for (auto& [num, count] : freq)
        maxFreq = max(maxFreq, count);

    int ans = -1;
    
    for (auto& [num, count] : freq) {
        if (count < maxFreq) {
            if (ans == -1 || (count > freq[ans]) || (count == freq[ans] && num < ans) ) 
                ans = num;
        }
    }

    return ans;
}

int secondMostFrequentElement(vector<int>& nums) {
    unordered_map<int, int> freq;
    
    for (int x : nums)
        freq[x]++;

    int maxFreqEle = nums[0];
    int secondMaxFreqEle = -1;
    
    for (auto& [num, count] : freq) {
        int mxFq = freq[maxFreqEle];
        int scMxFq = freq[secondMaxFreqEle];
        
        if (count > mxFq) {
            secondMaxFreqEle = maxFreqEle;
            maxFreqEle = num;
        }
        else if (count == mxFq) {
            maxFreqEle = min(num, maxFreqEle);
        }
        // now count is smaller than max_frequency
        else if (count > scMxFq || (count == scMxFq && num < secondMaxFreqEle)) {
            secondMaxFreqEle = num;
        }
    }

    return secondMaxFreqEle;
}

/*
In case of current freq == freq of maxFreqEle, we are making sure that maxFreqEle stores the minimum value.

This is done so that, if in future, someone with higher freq comes up, then current max_frequent_element will become the 
second_most_frequent_element. 
And since we want to keep the smaller value in case of tie in frequency count, 
we need to make sure maxFreqEle also follows this rule.

Ex- consider the array : [3, 4, 1, 5, 5, 9, 7, 2]
If we don't update maxFreqEle to mark the minimum value having maximum frequency, 
then we would get wrong answer for such cases.
(Had to learn this the hard way though 🥲)
*/

// ChatGPT solution (when asked to find the second most frequent element using a single loop after building frequency map)
int secondMostFrequent(vector<int>& arr) {
    unordered_map<int, int> freq;

    // Frequency computation
    for (int num : arr) {
        freq[num]++;
    }

    int highestFreq = 0;
    int highestElement = INT_MAX;

    int secondHighestFreq = 0;
    int secondElement = INT_MAX;

    // Single loop to find the answer
    for (auto& [num, f] : freq) {

        if (f > highestFreq) {
            // Old highest becomes second highest
            secondHighestFreq = highestFreq;
            secondElement = highestElement;

            // Current becomes highest
            highestFreq = f;
            highestElement = num;
        }
        else if (f == highestFreq) {
            // Same highest frequency: keep smallest element
            highestElement = min(highestElement, num);
        }
        else if (f > secondHighestFreq) {
            // New second highest
            secondHighestFreq = f;
            secondElement = num;
        }
        else if (f == secondHighestFreq) {
            // Same second highest frequency: keep smallest
            secondElement = min(secondElement, num);
        }
    }

    if (secondHighestFreq == 0) {
        return -1;
    }

    return secondElement;
}

int main() {
    return 0;
}