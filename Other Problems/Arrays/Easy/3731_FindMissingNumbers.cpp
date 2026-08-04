/*
Leetcode - 3731. Find Missing Elements : Easy

You are given an integer array nums consisting of unique integers.
Originally, nums contained every integer within a certain range. 
However, some integers might have gone missing from the array.
The smallest and largest integers of the original range are still present in nums.
Return a sorted list of all the missing integers in this range. If no integers are missing, return an empty list.

Examples :-

Input: nums = [1,4,2,5] __ Output: [3]
Explanation:
The smallest integer is 1 and the largest is 5, so the full range should be [1,2,3,4,5]. 
Among these, only 3 is missing.

Input: nums = [7,8,6,9] __ Output: []
Explanation:
The smallest integer is 6 and the largest is 9, so the full range is [6,7,8,9]. 
All integers are already present, so no integer is missing.

Input: nums = [5,1] __ Output: [2,3,4]
Explanation:
The smallest integer is 1 and the largest is 5, so the full range should be [1,2,3,4,5]. 
The missing integers are 2, 3, and 4.

Constraints :-
• 2 <= nums.length <= 100
• 1 <= nums[i] <= 100
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach : Time Complexity : O(n * (max - min + 1)) __ Space Complexity : O(1)
/*
>> Algorithm
• Find the maximum and minimum value of nums to get the original range limit. range = [minimum_value, maximum_val]
• Initialize an empty result vector
• For each number in range [min, max]
    • check if it is missing from the array. If missing, add it to result vector
• Return the result vector

>> Time Complexity
• Finding maximum & minimum takes O(n)
• For each element in range [min, max], we check if it is present in nums or not.
    This uses linear search which takes O(n) for each element.
    Since there are total `max - min + 1` elements in range [min, max], 
    thus time = count of elements in range[min, max] * time to search each element = O(n * (max - min + 1))
Thus, time: O(n * (max - min + 1)) + O(n)

>> Space Complexity
No extra space is used apart from the result vector which is required to be returned, so is not considered as extra space.
Thus, space = O(1)
*/
// helper method -> checks if element 'ele' is present in nums or not
bool contains(const vector<int>& nums, int ele) {
    for (int x : nums) 
        if (x == ele)
            return true;

    return false;
}

vector<int> findMissingElementsNaive(vector<int>& nums) {
    vector<int> res;

    int max = nums[0], min = nums[0];
    
    for (int x : nums) {
        if (x > max) max = x;
        if (x < min) min = x;
    }
    
    for (int i = min; i <= max; i++) 
        if (!contains(nums, i))
            res.push_back(i);
    
    return res;
}

// Better Approach (Sorting) : Time Complexity : O(n log n) + O(max - min + 1)__ Space Complexity : O(1)
/*
>> Intuition:
Since we only care about which values are missing, 
first sort the array so the numbers appear in increasing order. 
Then, start from the smallest value (x = nums[0]) and 
try to "match" every expected number with the current array element. 
If x matches nums[i], both pointers move forward. 
Otherwise, x must be missing, so add it to the answer and keep incrementing x until it catches up. 
In this way, every gap in the sorted array is naturally identified as missing elements.

>> Time Complexity: O(n log n)
• Sorting the array takes O(n log n).
• The two-pointer traversal is O(n + m), where m is the number of missing elements added to the answer. 
    Since each increment of x either advances i or outputs a missing element, the total work is linear.
Hence, the overall complexity is O(n log n + n + m). 
This n + m is the total count of elements present in nums and missing ones. 
Since nums contains elements in range [min, max], the elements missing and present in nums lie in this range also.
Thus, n + m = (max - min + 1)
So, total time: O(n log n) + O(max - min + 1)
*/
vector<int> findMissingElementsBetter(vector<int>& nums) {
    int n = nums.size();

    sort(nums.begin(), nums.end());
    
    vector<int> res;
    int x = nums[0], i = 0;
    
    while (i < n) {
        if (x == nums[i]) {
            x++;
            i++;
        }
        else res.push_back(x++);
    }

    return res;
}

// Optimal Approach - 1: Time Complexity : O(n + 101) __ Space Complexity : O(101) ~ O(1)
/*
>> Intuition
Since the values are limited to the range [0, 100], 
we can use a frequency array to directly mark which numbers are present. 
Once we know the minimum and maximum values in the array, 
we simply check every number in between—any value with frequency 0 is missing.

>> Algorithm
• Build a frequency array of size 101 to mark the occurrence of each value.
• Find the smallest (i) and largest (j) values present in the array.
• Traverse the range [i, j] and add every value with freq[value] == 0 to the answer.

We can find the maximum and minimum by traversing the array or also by using the frequency vector.
The first element which has a non-zero frequency is the minimum value, 
which can be found by traversing the freq vector from left end.

Similarly the first element from right end with a non-zero frequency is the maximum value.

>> Complexity Analysis
• Building the frequency array takes O(n).
• Finding the minimum and maximum present values takes O(101).
• Scanning the range [i, j] also takes O(101) in the worst case.
• Overall Time Complexity: O(n + 101) ~ O(n).
• Space Complexity: O(101) = O(1) (excluding the output array).
*/
vector<int> findMissingElements1(vector<int>& nums) {
    vector<int> freq(101);

    for (int x : nums)
        freq[x]++;
    
    vector<int> res;
    
    // find the first appearing character from left end of the array (minimum value of nums)
    int i = 0;
    while (freq[i] == 0) i++;
    
    // find the first appearing character from right end of the array (maximum value of nums)
    int j = 100;
    while (freq[j] == 0) j--;
    
    // now in range [i, j], add those elements to the result vector which are missing
    for (int k = i; k < j; k++) 
        if (freq[k] == 0)
            res.push_back(k);
    
    return res;
}

// Optimal Approach - 2: Time Complexity : O(n + (mx - mn + 1)) __ Space Complexity : O(mx - mn + 1)
/*
>> Intuition
Instead of using a fixed-size frequency array, 
first find the minimum and maximum values in the array. 
Then, create a frequency array only for this range. 
This avoids wasting space on values outside [min, max] 
while still allowing us to directly identify the missing numbers.

>> Algorithm
• Find the minimum (mn) and maximum (mx) values in the array.
• Create a frequency array of size mx - mn + 1 (to hash only the elements in range [mn, mx]).
• Mark the occurrence of each value using `x` the offset `x-mn` (as, value `x` will correspond to index `x-mn` in freq vector).
• Traverse the range [mn, mx] and add every value whose frequency is 0 to the answer.

>> Complexity Analysis
• Finding the minimum and maximum takes O(n).
• Building the frequency array takes O(n).
• Scanning the range [mn, mx] takes O(mx - mn + 1).
• Overall Time Complexity: O(n + (mx - mn + 1)).
• Space Complexity: O(mx - mn + 1) (excluding the output array).

These values mx-mn+1 will always be <= 101, due to the given constraints.
*/
vector<int> findMissingElements2(vector<int>& nums) {
    int mn = nums[0], mx = nums[0];

    for (int x : nums) {
        if (x > mx) mx = x;
        if (x < mn) mn = x;
    }

    vector<int> freq(mx - mn + 1);
    
    for (int x : nums) 
        freq[x - mn]++;
    
    vector<int> res;
    for (int i = mn; i <= mx; i++)
        if (freq[i-mn] == 0)
            res.push_back(i);
    
    return res;
}

int main() {
    return 0;
}