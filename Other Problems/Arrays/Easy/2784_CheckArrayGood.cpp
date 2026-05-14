/*
Leetcode - 2784. Check if Array is Good : Easy

You are given an integer array nums. We consider an array good if it is a permutation of an array base[n].
base[n] = [1, 2, ..., n - 1, n, n] (in other words, it is an array of length n + 1 which contains 1 to n - 1 exactly once, 
plus two occurrences of n). For example, base[1] = [1, 1] and base[3] = [1, 2, 3, 3].
Return true if the given array is good, otherwise return false.

Note: A permutation of integers represents an arrangement of these numbers.

Examples :-

Input: nums = [2, 1, 3] __ Output: false
Explanation: Since the maximum element of the array is 3, 
the only candidate n for which this array could be a permutation of base[n], is n = 3. 
However, base[3] has four elements but array nums has three. 
Therefore, it can not be a permutation of base[3] = [1, 2, 3, 3]. So the answer is false.

Input: nums = [1, 3, 3, 2] __ Output: true
Explanation: Since the maximum element of the array is 3, 
the only candidate n for which this array could be a permutation of base[n], is n = 3. 
It can be seen that nums is a permutation of base[3] = [1, 2, 3, 3] (by swapping the second and fourth elements in nums, 
we reach base[3]). Therefore, the answer is true.

Input: nums = [1, 1] __ Output: true
Explanation: Since the maximum element of the array is 1, 
the only candidate n for which this array could be a permutation of base[n], is n = 1. 
It can be seen that nums is a permutation of base[1] = [1, 1]. Therefore, the answer is true.

Input: nums = [3, 4, 4, 1, 2, 1] __ Output: false
Explanation: Since the maximum element of the array is 4, 
the only candidate n for which this array could be a permutation of base[n], 
is n = 4. However, base[4] has five elements but array nums has six. 
Therefore, it can not be a permutation of base[4] = [1, 2, 3, 4, 4]. So the answer is false.

Constraints :-
- 1 <= nums.length <= 100
- 1 <= num[i] <= 200
*/

#include <bits/stdc++.h>
using namespace std;

void display(vector<int>& nums) {
    for (int i = 0; i < nums.size(); i++) 
        cout << i << " -> " << nums[i] << endl; 
}

bool isGood(vector<int>& nums) {
    vector<int> hashArr(201);

    for (int x : nums) hashArr[x]++;
    
    int i = 200;
    
    while (i > 0 && hashArr[i] == 0)
        i--;
    
    if (hashArr[i] != 2) return false;
    
    i--;
    while (i > 0 && hashArr[i] == 1) i--;
    
    return i == 0;
}

bool isGood(vector<int>& nums) {
        unordered_map<int, int> freq;
        int mx = 0;

        for (int x : nums) {
            freq[x]++;
            if (x > mx) mx = x;
        }

        if (nums.size() != mx + 1) return false;

        for (int x : nums) {
            if (x == mx) {
                if (freq[x] != 2)
                    return false;
            }
            else if (freq[x] != 1)
                return false;

            // if ((x == mx && freq[x] != 2) || (x != mx && freq[x] != 1)) 
            //     return false;
        }

        return true;
    }

// not submitted yet 
bool isGood(vector<int>& nums) {
        unordered_map<int, int> freq;
        int mx = 0;

        for (int x : nums) {
            freq[x]++;
            if (x > mx) mx = x;
        }

        if (nums.size() != mx + 1) return false;
        if (freq[mx] != 2) return false;

        for (int i = 1; i < mx; i++)
            if (freq[i] != 1)
                return false;

        return true;
    }

int main() {
    vector<int> nums = {1, 3, 3, 2};
    cout << isGood2(nums);


    return 0;
}