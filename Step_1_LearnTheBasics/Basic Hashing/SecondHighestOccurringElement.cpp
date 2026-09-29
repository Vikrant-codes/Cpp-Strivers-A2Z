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

// Naive Approach: Time Complexity : O(n + 2k) __ Space Complexity : O(k)
/*
>> Intuition

We can use an unordered_map to store the frequency of every element.
Then, we first traverse the map and find the maximum frequency among all elements.
After that, we traverse the map again and look only at elements whose frequency is less than the maximum frequency, 
because an element having the maximum frequency cannot be the second most frequent element.
Among these remaining elements, we track the element with the highest frequency. This gives us the second highest frequency.
While doing this, if two elements have the same frequency, we keep the smaller value.
We also initialize ans to -1. This handles the case where 
no element has a frequency smaller than the maximum frequency — meaning there is no second most frequent element.

So the thought process is:
• Count frequency of every element.
• Find the maximum frequency.
• Ignore all elements having that maximum frequency.
• Among the remaining elements, find the highest frequency.
• If frequencies tie, choose the smaller element.
• If nothing remains, return -1.

>> Complexity Analysis
Let n be the size of the array and k the number of distinct elements.

Time: O(n) average — O(n) to build the frequency map + O(2*k) for the two map traversals.
Space: O(k) — the frequency map stores the distinct elements.
*/
int secondMostFrequentElementNaive(vector<int>& nums) {
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

// Optimal Approach: Time Complexity : O(n + k) __ Space Complexity : O(k)
/*
>> Intuition

Just like the previous approach, we can use an unordered_map to store the frequency of every element.
However, instead of first finding the maximum frequency and then making another traversal to find the second maximum, 
we can try to find secondMaxFreqEle in a single traversal of the frequency map.

To do this, we maintain two elements while traversing:
• maxFreqEle → element having the highest frequency seen so far
• secondMaxFreqEle → element having the second-highest frequency seen so far

Now, for every (num, count) pair:
•   If count > freq[maxFreqEle], then num has become the new maximum-frequency element. 
    Therefore, the old maxFreqEle now becomes the second maximum, 
    so we first move it to secondMaxFreqEle, and then update maxFreqEle.

•   If count == freq[maxFreqEle], both elements have the same maximum frequency. 
    So we keep the smaller value as maxFreqEle.
    
    This tie-breaking is important because the current maxFreqEle might become secondMaxFreqEle later 
    when we encounter an element with an even higher frequency. 
    Therefore, we make sure maxFreqEle itself always contains the smallest value among elements having the maximum frequency.

•   Otherwise, count is smaller than the maximum frequency, so num can potentially become secondMaxFreqEle. 
    We update it if its frequency is greater than the current second maximum frequency. 
    If the frequencies are equal, we keep the smaller value.

Thus, with maxFreqEle and secondMaxFreqEle being maintained together, 
we can find the required answer in one traversal of the frequency map.

>> Complexity Analysis
Let n be the size of the array and k the number of distinct elements.

Time: O(n) average — O(n) to build the frequency map + O(k) for the single map traversal.
Space: O(k) — the frequency map stores each distinct element.
*/

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