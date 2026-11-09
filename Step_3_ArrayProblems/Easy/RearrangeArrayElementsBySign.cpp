#include <bits/stdc++.h>
using namespace std;

// Leetcode Variant
/*
Leetcode - 2149. Rearrange Array Elements by Sign : Medium

You are given a 0-indexed integer array nums of even length consisting of 
an equal number of positive and negative integers.

You should return the array of nums such that the array follows the given conditions:
• Every consecutive pair of integers have opposite signs.
• For all integers with the same sign, the order in which they were present in nums is preserved.
• The rearranged array begins with a positive integer.

Return the modified array after rearranging the elements to satisfy the aforementioned conditions.

Examples :-

Input: nums = [3,1,-2,-5,2,-4]
Output: [3,-2,1,-5,2,-4]
Explanation:
The positive integers in nums are [3,1,2]. The negative integers are [-2,-5,-4].
The only possible way to rearrange them such that they satisfy all conditions is [3,-2,1,-5,2,-4].
Other ways such as [1,-2,2,-5,3,-4], [3,1,2,-2,-5,-4], [-2,3,-5,1,-4,2] are incorrect 
because they do not satisfy one or more conditions.  

Input: nums = [-1,1]
Output: [1,-1]
Explanation:
1 is the only positive integer and -1 the only negative integer in nums.
So nums is rearranged to [1,-1].

Constraints :-
• 2 <= nums.length <= 2 * 105
• nums.length is even
• 1 <= |nums[i]| <= 105
• nums consists of equal number of positive and negative integers.

It is not required to do the modifications in-place.
*/

// Naive Approach: Time Complexity : O(2n) __ Space Complexity : O(2n)
/*
>> Naive Approach — Separate Positive and Negative Elements

Traverse the array and store positive and negative elements in two separate vectors, pos and neg. 
Since we traverse the original array from left to right, 
the relative order of elements with the same sign is preserved in both vectors.

Then, iterate through both vectors and alternately append a positive element followed by a negative element to res. 
This ensures that the rearranged array starts with a positive element and every consecutive pair has opposite signs.

>> Complexity Analysis:
-> Time: O(n + n/2)
One O(n) traversal to separate the elements and another O(n/2) to construct the result.

-> Space: O(2n)
The positive and negative vectors together store n elements, and the result vector stores another n elements.
*/
vector<int> rearrangeArrayNaive(vector<int>& nums) {
    int n = nums.size();

    vector<int> pos, neg;
    
    for (int& x : nums) {
        if (x > 0) pos.push_back(x);
        else neg.push_back(x);
    }

    vector<int> res;
    for (int i = 0; i < n / 2; i++) {
        res.push_back(pos[i]);
        res.push_back(neg[i]);
    }
    
    return res;
}

// Optimal Approach: Time Complexity : O(n) __ Space Complexity : O(n)
/*
>> Optimal Approach — Index Placement

Instead of storing positive and negative elements separately, 
we can place them directly into their correct positions in the result array.

- Initialize i = 0 to track the next even index for positive elements.
- Initialize j = 1 to track the next odd index for negative elements.
- Traverse nums while preserving its original order:
  - If an element is positive, place it at res[i] and increment i by 2.
  - If an element is negative, place it at res[j] and increment j by 2.

Since positive elements occupy even indices and negative elements occupy odd indices, 
the array starts with a positive element and consecutive elements have opposite signs. 
Traversing the original array from left to right also preserves the relative order of elements with the same sign.

Important assumption: This approach works because the problem guarantees an equal number of positive and negative elements. 
Therefore, every even index can accommodate a positive element, and every odd index can accommodate a negative element.

>> Complexity Analysis:
- Time: O(n) — A single traversal of the input array.
- Space: O(n) — The result vector stores all n elements. Auxiliary space excluding the output is O(1).
*/
vector<int> rearrangeArray(vector<int>& nums) {
    int n = nums.size();

    int i = 0;      // writer for +ve elements
    int j = 1;      // writer for -ve elements
    
    vector<int> res(n);
    
    for (int& x : nums) {
        if (x > 0) {
            res[i] = x;
            i += 2;
        }
        else {
            res[j] = x;
            j += 2;
        }
    }
    
    return res;
}

// GFG Variant
/*
GFG - Alternate Positive Negative : Easy

Given an unsorted array arr containing both positive and negative numbers. 
Your task is to rearrange the array and convert it into an array of alternate positive and negative numbers 
without changing the relative order.

Note:
Resulting array should start with a positive integer (0 will also be considered as a positive integer).
If any of the positive or negative integers are exhausted, then add the remaining integers in the answer 
as it is by maintaining the relative order.

Examples :-

Input: arr[] = [9, 4, -2, -1, 5, 0, -5, -3, 2]
Output: [9, -2, 4, -1, 5, -5, 0, -3, 2]

Input: arr[] = [-5, -2, 5, 2, 4, 7, 1, 8, 0, -8]
Output: [5, -5, 2, -2, 4, -8, 7, 1, 8, 0]

Input: arr[] = [9, 5, -2, -1, 5, 0, -5, -3, 2]
Output: [9, -2, 5, -1, 5, -5, 0, -3, 2]

Constraints :-
• 1 ≤ arr.size() ≤ 10^6
• -10^6 ≤ arr[i] ≤ 10^6
*/

// Optimal Approach: Time Complexity : O(2n) __ Space Complexity : O(n)
/*
>> Approach: Separate Positives and Negatives, Then Alternate

>> Why can't we use the LeetCode approach?
Unlike LeetCode 2149, this GFG variant does not guarantee an even-sized array 
with equal numbers of positive and negative elements. 
Either group may have leftover elements, so we cannot simply place positives at even indices and negatives at odd indices.

Instead, we use two separate vectors, pos and neg, to preserve the relative order of elements 
within each group before rearranging them.

>> Intuition
First, traverse the array and separate the elements into pos and neg. 
Treat 0 as positive, as specified in the problem.

Next, rewrite the original array by alternately taking one positive element followed by one negative element. 
If either group runs out, append the remaining elements from the other group in their original relative order.

>> Complexity Analysis:
-> Time: O(2n) — Separating the elements and rewriting the array each take linear time.

-> Space: O(n)
The two auxiliary vectors together store all n elements. 
The rearrangement itself is performed in-place in arr, without a separate result vector.
*/
void rearrange(vector<int> &arr) {
    vector<int> pos, neg;
    
    for (int& x : arr) {
        if (x >= 0) pos.push_back(x);       // 0 is considered a positive element
        else neg.push_back(x);
    }
    
    vector<int> res;
    
    int i = 0, j = 0, n = pos.size(), m = neg.size();
    int size = min(n, m);
    
    int k = 0;      // writer to re-write in arr
    
    // re-write values in arr in alternating fashion

    // while (i < size && j < size) {
    //     arr[k++] = pos[i++];
    //     arr[k++] = neg[j++];
    // }
    
    // while (i < n)
    //     arr[k++] = pos[i++];
    
    // while (j < m)
    //     arr[k++] = neg[j++];

    while (k < arr.size()) {
        if (i < n) arr[k++] = pos[i++];
        if (j < m) arr[k++] = neg[j++];
    }
}

int main() {
    return 0;
}