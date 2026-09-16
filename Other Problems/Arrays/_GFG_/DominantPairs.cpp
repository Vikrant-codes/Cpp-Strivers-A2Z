/*
GFG - Dominant Pairs : Easy

Given an even-sized integer array arr[], count the number of dominant pairs. 
A pair of indices (i, j) is called dominant if all of the following conditions hold:
• 0 ≤ i < arr.size() / 2
• arr.size() / 2 ≤ j < arr.size() 
• arr[i] ≥ 5 × arr[j] 

Return the total number of dominant pairs.

Note: 0-based indexing is used.

Examples :-

Input: arr[] = [10, 2, 2, 1]
Output: 2
Explanation: First half: [10, 2], Second half: [2, 1]. So valid two pairs are: 
{0, 2}: 10 >= 5 × 2 
{0, 3}: 10 >= 5 × 1 

Input: arr[] = [10, 8, 2, 1, 1, 2]
Output: 5
Explanation: First half: [10, 8, 2], Second half: [1, 1, 2]. So valid five pairs are: 
{0, 3}: 10 >= 5 × 1
{0, 4}: 10 >= 5 × 1 
{0, 5}: 10 >= 5 × 2
{1, 3}: 8 >= 5 × 1 
{1, 4}: 8 >= 5 × 1 

Constraints :-
• 1 ≤ arr.size() ≤ 10^4
• -10^4 ≤ arr[i] ≤ 10^4
• arr.size() is even.
• The sum of arr.size() over all test cases won't exceed 10^6.
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach (Sorting + Two Pointers) : Time Complexity : O(n log n) __ Space Complexity : O(1)
/*
>> Dominant Pairs — Intuition

We need to count pairs where:
• i belongs to the first half
• j belongs to the second half
• arr[i] >= 5 × arr[j]

    First half       Second half
    [ ... ... ... ]  [ ... ... ... ]
         i                  j

        arr[i] >= 5 * arr[j]

A brute-force thought is: for every element in the first half, check every element in the second half. That's O(n²).

So the next question should be:
| Can we quickly know how many elements in the second half satisfy the condition for a given first-half element?

-> Step 1: Sort the two halves

Consider:
First half:   [2, 8, 10, 20]
Second half:  [1, 2, 4, 6]

Suppose we're considering 10.
Instead of checking every second-half element independently:
    10 >= 5*1  ✓
    10 >= 5*2  ✓
    10 >= 5*4  ✗
    10 >= 5*6  ✗
Because the second half is sorted, once the condition becomes false, everything after it will also be false.
So the valid elements always form a prefix:
    [1, 2 | 4, 6]
    valid invalid
We only need to find that boundary.

-> Step 2: Notice that the boundary never moves backwards

Now consider the first-half elements in sorted order: 2 → 8 → 10 → 20
As arr[i] gets larger, the condition arr[i] >= 5 * arr[j] can only become easier to satisfy.

For example:
    8 >= 5*1   ✓

    10 >= 5*1  ✓
    10 >= 5*2  ✓

Therefore, if the boundary for 8 was after 1, when we move to 10, we don't need to start checking from 1 again.
We can simply continue moving the second pointer forward.
That's where the two-pointer idea comes from.

-> Step 3: Translate that observation into the implementation
We sort each half:
    sort(arr.begin(), arr.begin() + mid);
    sort(arr.begin() + mid, arr.end());
Then:
    int i = 0, j = mid;
- i moves through the sorted first half.
- j moves through the sorted second half and marks how many elements satisfy the condition.

While the current second-half element is valid:
    if (arr[i] >= 5LL * arr[j])
        j++;
Once it becomes invalid, we know:
second half: [ valid valid valid | invalid ... ]
                                 ^
                                 j

So there are exactly: j - mid valid second-half elements for the current arr[i].
Hence: 
    cnt += j - mid;
    i++;
The important part is that j is not reset when i moves forward.

>> Why is that efficient?
Without sorting, we have to ask for every pair: "Does this pair satisfy the condition?"
After sorting, we instead ask: "Where does the valid prefix end?"
And because both halves are sorted, that boundary moves only forward.
So the pair-counting part becomes linear, rather than quadratic.

>> Approach
1. Split the array into its two halves.
2. Sort the first half and the second half independently.
3. Maintain:
    • a pointer moving through the first half
    • a pointer representing the boundary of valid elements in the second half.
4. For each first-half value, advance the second-half pointer while the dominant-pair condition holds.
5. Because the second half is sorted, every element before that pointer forms a valid pair with the current first-half value.
6. Add the number of such elements to the answer.
7. Continue with the next first-half value without resetting the second-half pointer.

>> Why this works
For a fixed x from the first half, the sorted second half looks conceptually like:
    valid elements       invalid elements
    <----------------> | <---------------->
                       ^
                     boundary
Everything before the boundary satisfies: x >= 5y
Everything after it doesn't.

When we move to a larger x, the boundary can only move right, never left.
Therefore, across the entire algorithm, the second pointer moves at most n/2 times, 
rather than restarting from the beginning for every element.

>> Complexity

Let the total array size be n.
Each half contains n/2 elements.

-> Sorting
Sorting both halves takes: O( (n/2) log (n/2) ) + O( (n/2) log (n/2) ) = O(n log n)

-> Two pointers
Each pointer moves only forward:
• first-half pointer → at most n/2 times
• second-half pointer → at most n/2 times
So the scanning phase is: O(n)

-> Overall Time: O(n log n)

The extra space depends on whether the halves are sorted in-place or copied into separate arrays.
O(1) auxiliary space, apart from the sorting algorithm's internal stack/implementation details.
*/
int dominantPairs(vector<int> &arr) {
    int n = arr.size();
    int mid = n / 2;
    
    sort(arr.begin(), arr.begin() + mid);
    sort(arr.begin() + mid, arr.end());
    
    int cnt = 0;
    int i = 0, j = mid;
    
    while (i < mid && j < n) {
        if (arr[i] >= 5 * arr[j]) j++;
        else {
            cnt += (j - mid);
            i++;
        }
    }
    
    if (i < mid) {
        cnt +=  (mid - i) * (j - mid);
    }
    
    return cnt;
}

int main() {
    return 0;
}