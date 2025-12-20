/*
Leetcode - 1365. How Many Numbers Are Smaller Than the Current Number : Easy

Given the array nums, for each nums[i] find out how many numbers in the array are smaller than it. 
That is, for each nums[i] you have to count the number of valid j's such that j != i and nums[j] < nums[i].
Return the answer in an array.

Examples :-

Input: nums = [8,1,2,2,3] __ Output: [4,0,1,1,3]
Explanation: 
For nums[0]=8 there exist four smaller numbers than it (1, 2, 2 and 3). 
For nums[1]=1 does not exist any smaller number than it.
For nums[2]=2 there exist one smaller number than it (1). 
For nums[3]=2 there exist one smaller number than it (1). 
For nums[4]=3 there exist three smaller numbers than it (1, 2 and 2).

Input: nums = [6,5,4,8] __ Output: [2,1,0,3]

Input: nums = [7,7,7,7] __ Output: [0,0,0,0]

Constraints :-
- 2 <= nums.length <= 500
- 0 <= nums[i] <= 100
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force (Naive) Approach :- Time Coomplexity : O(n ^ 2) __ Space Complexity : O(1)
vector<int> smallerNumbersThanCurrentBrute(vector<int>& nums) {
    vector<int> ans;
    for (int i=0; i<nums.size(); i++) {
        int cnt = 0;

        for (int j=0; j<nums.size(); j++)
            if (nums[j] < nums[i]) cnt++;
    
        ans.push_back(cnt);
    }
    return ans;
}

// Better Approach (Sorting + Hashing) :- Time Complexity : O(n log n) __ Space Complexity : O(n)
/*
1️⃣ Better Approach (Sorting + Hashing)
Intuition
- Sorting the array gives us numbers in increasing order.
- In a sorted array, the first index of a number tells you how many numbers are smaller than it.
- Example:
nums = [8,1,2,2,3]
sorted = [1,2,2,3,8]
Map of first indices:
1 -> 0   (no numbers smaller than 1)
2 -> 1   (1 number smaller than 2 → the 1)
3 -> 3   (3 numbers smaller than 3 → 1,2,2)
8 -> 4   (4 numbers smaller than 8 → 1,2,2,3)
- So, for each number in nums, you just need the index of the element in the sorted array to get the answer.
- So, we can use a map to store the index position of each element in the sorted vector and then get the 
count of smaller elements by checking this index position.
- To handle duplicates, we store the first occurrence index of each element in the map.
We use a different array and sort it because we need to preserve the order of elements in the given nums array and 
return the ans array according to that order. So, we use a 2nd array and sort it to get the smaller count.

Que > How to store first occurrence index of each element in the map ?
If we just traverse the sorted array and insert/update the index value for current element then for duplicates 
the map would store the last occurrence index. This would lead to wrong answer as the smaller count is equal to 
the first occurrence index. 
To avoid this we check whether the current element already exists in map & insert the index position only if it don't exist.

Algorithm
1. Copy nums to a new array sorted.
2. Sort sorted.
3. Create a map ind to store the first occurrence index of each number in sorted.
    - This index equals the count of numbers smaller than that number.
4. Iterate through original nums and look up each number in ind to get the answer.
5. Return the answer vector.

Example :- 
nums = [8,1,2,2,3]
sorted = [1,2,2,3,8]
Map (first occurrence):
1 -> 0
2 -> 1
3 -> 3
8 -> 4
Answer = [4,0,1,1,3]

Complexity Analysis :- 
Time Complexity :
- Sorting: O(n log n)
- Building map: O(n)
- Querying map for original array: O(n)
- Overall: O(n log n) time.
Space Complexity : O(n) (for map + sorted array)
*/
vector<int> smallerNumbersThanCurrentBetter(vector<int>& nums) {
    vector<int> ans;
    vector<int> sorted = nums;
    sort(sorted.begin(), sorted.end());

    unordered_map<int, int> ind;

    for (int i=0; i<sorted.size(); i++)
        // check if current element index already exists in the map ind. If don't update it.
        if ( !ind.count(sorted[i]) )
            ind[sorted[i]] = i;
    
    for (int x : nums) 
        ans.push_back(ind[x]);
    
    return ans;
}

/* To get the first occurrence index of we can also traverse the array from the end, so even when duplicates comes, the 
map will update the ind value so that the first occurrence index will be the final value for the element. */
vector<int> smallerNumbersThanCurrentBetter2(vector<int>& nums) {
    vector<int> ans;
    vector<int> sorted = nums;
    sort(sorted.begin(), sorted.end());

    unordered_map<int, int> ind;
    
    for (int i=sorted.size()-1; i>=0; i--)
        ind[sorted[i]] = i;
    
    for (int x : nums) 
        ans.push_back(ind[x]);
    
    return ans;
}
/*
Binary Search Approach :- Sorting + Binary Search
We could've also used binary search instead of map to get the first occurrence index of each element in the sorted array.
To implement this approach we would've to use binary search on sorted_array to get the first occurrence index of every element 
'x' of the original array. This means O(n) * O(log n) time.
Doing so will save us O(n) space of map but will then take O(n * log n) time to get the first occurrence index of each element.
*/


// Optimal Approach (Counting Sort) : Time Complexity : O(n) __ Space Complexity : O(1)
/*
2️⃣ Optimal Approach (Frequency Array + Prefix Sum)

Intuition
- The array elements are bounded: 0 ≤ nums[i] ≤ 100.
- For such small element count we can use the counting sort approach to sort the elements and get the smaller count.
- Use a frequency array of size 101 since elements are in range[0,100] to count how many times each number occurs.
- Count frequencies: freq[i] = how many times number i occurs in nums.
Example for nums = [8,1,2,2,3]:-
freq[0] = 0
freq[1] = 1
freq[2] = 2
freq[3] = 1
freq[8] = 1
(all others = 0)

- In previous approach we had firstly sorted then used the first occurrence index to get the count of smaller elements 
but here we use the counting sort approach to efficiently sort the elements and then to get the count of smaller elements,
we check the sum of frequencies upto current element as this cumulative_sum of frequencies tell the count of smaller elements.
- Build a cumulative frequency array, where cumulative_freq[i] tells you how many numbers are smaller than i.
Build cumulative frequency: cumulative_freq[i] = how many numbers are strictly smaller than i.
Formula :- cumulative_freq[i] = cumulative_freq[i-1] + freq[i-1]
cumulative_freq[0] = 0  // no numbers smaller than 0
cumulative_freq[1] = cumulative_freq[0] + freq[0] = 0
cumulative_freq[2] = cumulative_freq[1] + freq[1] = 0 + 1 = 1
cumulative_freq[3] = cumulative_freq[2] + freq[2] = 1 + 2 = 3
cumulative_freq[4] = cumulative_freq[3] + freq[3] = 3 + 1 = 4
...
cumulative_freq[8] = cumulative_freq[7] + freq[7] = 4 + 0 = 4

- Get the answer: For each number x in nums, cumulative_freq[x] gives how many numbers are smaller than x.
Example :-
nums = [8,1,2,2,3]
freq = [0,1,2,1,0,...,0,1 at index 8]
cumulative_freq = [0,0,1,3,4,...]
Answer = [4,0,1,1,3]

Algorithm
1. Create a freq array of size 101.
2. Count frequency of each number in nums.
3. Build cumulative_freq array: cumulative_freq[i] = cumulative_freq[i-1] + freq[i-1]
4. For each number in nums, cumulative_freq[num] is the answer.

Complexity Analysis :- 
Time Complexity : 
Counting frequency: O(n)
Building cumulative freq: O(101) → O(1)
Querying answers: O(n)
Overall: O(n) time.

Space Complexity : O(101) {since freq & cumulative_freq array are of size 101} → O(1) extra space
*/
vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
    vector<int> ans;
    vector<int> freq(101);

    for (int x : nums) freq[x]++;
    vector<int> cumulative_freq(101);
    cumulative_freq[0] = 0;

    for (int i=1; i<101; i++) {
        cumulative_freq[i] = cumulative_freq[i-1] + freq[i-1];
    }

    for (int x : nums)
        ans.push_back(cumulative_freq[x]);
    
    return ans;
}

int main() {
    return 0;
}