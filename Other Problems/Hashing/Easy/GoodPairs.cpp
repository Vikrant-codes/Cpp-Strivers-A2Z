/*
Leetcode - 1512. Number of Good Pairs : Easy

Given an array of integers nums, return the number of good pairs.
A pair (i, j) is called good if nums[i] == nums[j] and i < j.

Examples :-

Input: nums = [1,2,3,1,1,3] __ Output: 4
Explanation: There are 4 good pairs (0,3), (0,4), (3,4), (2,5) 0-indexed.

Input: nums = [1,1,1,1] __ Output: 6
Explanation: Each pair in the array are good.

Input: nums = [1,2,3] __ Output: 0
 
Constraints :- 1 <= nums.length <= 100 __ 1 <= nums[i] <= 100
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach : Time Complexity : O(n^2) __ Space Complexity : O(1)
/*
We need to count total good pairs (i, j) such that i < j and nums[i] == nums[j].
We can do so using two loops.
For an element x at index i, we count how many more 'x' exist to the right of the array. Doing so would tell us about the 
count of good pairs this ith element would make of form (i, j) where i < j < sizeOfArray 
*/
int numIdenticalPairsBrute(vector<int>& nums) {
    int cnt = 0, n = nums.size();
    for(int i=0; i<n-1; i++) {
        for(int j=i+1; j<n; j++) {
            if(nums[i] == nums[j]) cnt++;
        }
    }
    return cnt;
}

// HashMap Approach 
/*
Instead of checking forward equal elements count we can check how many equal element exist to the left of array. 
Doing so would tell us about how many good pairs the current element forms such that in pair(i, j) current element is 
the second one. i.e., 
For each element x at index 'k' we check how many more 'x' exist to the left of array i.e. index range [0, k)
This count of equal elements will tell us about the no of good pairs it will form.

Intuition
- A good pair is defined as (i, j) where nums[i] == nums[j] and i < j.
- For every no. you see, the no. of good pairs it forms equals the no. of times you’ve already seen that same no. before.
- So count the good pairs for each number using this logic and return the final count.
*/

// Implementation 1 (Using Unordered Map) :- Time Complexity : O(n) __ Space Complexity : O(n)
/*
To implement the above logic we use an unordered_map.
1. Maintain a frequency map mpp that tracks how many times each number has appeared.
2. When you see a number x, if it’s already in the map, it can form a pair with each previous occurrence of x.
3. So just add mpp[x] to your count.        (mpp[x] tells the count of previous occurence of x)
4. Then increment mpp[x] to include the current number.
*/
int numIdenticalPairsHash1(vector<int>& nums) {
    unordered_map<int, int> mpp;
    int cnt = 0;
    for (int x : nums) {
        if (mpp.find(x) != mpp.end()) cnt += mpp[x];
        mpp[x]++;
    }
    return cnt;
}

// Implementation 2 (Using Freq Array) :- Time Complexity : O(n) __ Space Complexity : O(1)
/*
Since we know that nums[i] is in the range [1,100] we can use a freq array of size 100 to store the frequency count. 
Using a fixed sized frequency array would mean a O(1) space complexity.
So, we use a freq vector of size 100 which stores the count of previous occurences of element x at the index x-1 in freq array
*/
int numIdenticalPairsHash2(vector<int>& nums) {
    vector<int> freq(100, 0);
    int cnt = 0;
    for (int x : nums) {
        cnt += freq[x-1];  // all pairs that x can form with previous occurrences
        freq[x-1]++;       // record this occurrence
    }
    return cnt;
}

// Combinatorics Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
We count total occurences of each element (using a freq array). 
Suppose an element x appears k times then we can find the no of good pairs (i,j) such that nums[i] = nums[j] = 'x' 
by checking how many pairs these 'k' occurrences of x can make. 
This can be calculated using Permutations & Combinations. Since we need to find how many pairs 'k' occurences of x can make 
(in a way we need to check for total combinations for selecting 2 elements from k occurrences i.e. k C 2)
Now, using combination formula we know that kC2 = k! / (k-2)! * 2! = k * (k-1) * (k-2)! / (k-2)! * 2! = k * (k-1) / 2
So, we firstly store frequency of each element and then apply this formula to find the no of good pairs 'k' occurrences of 
an element x makes on the final frequency count.
We need to apply this formula on freq count so we iterate through the frequency array to do so. 

Intuition :- 
- Instead of using a hash map, you can use a frequency array (like a hash table for small integers).
- First, count how many times each number appears.
- For a number appearing 'x' times, the number of unique pairs it can form is: x * (x-1) / 2
  (That’s the number of ways to choose 2 indices from f identical elements.)
- So after counting all frequencies, just sum this formula across all numbers.

Algorithm :-
1. Create a frequency array hasharr of appropriate size (e.g., 100 for problem constraints).
2. Traverse nums, incrementing hasharr[x - 1] for each element.
3. Initialize cnt = 0.
4. For each frequency f in hasharr, add f * (f - 1) / 2 to cnt.
5. Return cnt.
*/
int numIdenticalPairsHash3(vector<int>& nums) {
    vector<int> hasharr(100);       // keeps frequency count of each element
    for (int x : nums) hasharr[x-1]++; // increase the frequency
    int cnt = 0;
    for (int x : hasharr) {
        // count the no of good pairs 'x' occurrences of a number would make = x C 2 = x * (x-1) / 2
        cnt += x * (x-1) / 2;
    }
    return cnt;
}

int main() {

    return 0;
}