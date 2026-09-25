/*
TUF - 749. Sum of Highest and Lowest Frequency

Given an array of n integers, find the sum of the frequencies of the highest occurring number and lowest occurring number.

Examples :-

Input: arr = [1, 2, 2, 3, 3, 3]
Output: 4
Explanation: The highest frequency is 3 (element 3), and the lowest frequency is 1 (element 1). Their sum is 3 + 1 = 4.

Input: arr = [4, 4, 5, 5, 6]
Output: 3
Explanation: The highest frequency is 2 (elements 4 and 5), and the lowest frequency is 1 (element 6). Their sum is 2 + 1 = 3.

Constraints :-
• 1 <= n <= 10^5
• 1 <= arr[i] <= 10^4
*/

#include<bits/stdc++.h>
using namespace std;

int sumHighestAndLowestFrequency(vector<int>& nums) {
    unordered_map<int, int> freq;

    for (int x : nums)
        freq[x]++;

    int maxFreq = 0, minFreq = nums.size();
    
    for (auto& [num, count] : freq) {
        if (count > maxFreq)
            maxFreq = count;
            
        if (count < minFreq)
            minFreq = count;
    }

    return maxFreq + minFreq;
}

int main() {
    return 0;
}