/*
Leetcode - 1089. Duplicate Zeros : Easy

Given a fixed-length integer array arr, duplicate each occurrence of zero, shifting the remaining elements to the right.

Note that elements beyond the length of the original array are not written. 
Do the above modifications to the input array in place and do not return anything.

Examples :-

Input: arr = [1,0,2,3,0,4,5,0] __ Output: [1,0,0,2,3,0,0,4]
Input: arr = [1,2,3] __ Output: [1,2,3]

Constraints :-
- 1 <= arr.length <= 10^4
- 0 <= arr[i] <= 9
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach :- Time Complexity : O(n^2) __ Space Complexity : O(1)
/*
Traverse the array, if a zero is encountered, duplicate that zero & shift the elements to the right.

What the code is doing
• Traverse the array from left to right.
• When a 0 is found:
    • Shift all elements to the right by one position (from end to i+1).
    • Increment i to skip the duplicated zero.
• Array size remains fixed (last element may be dropped).
*/
void duplicateZerosBrute(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) {
            for (int j = n-1; j > i; j--)
                arr[j] = arr[j-1];
            i++;
        }
    }
}

// Optimal Approach (Two Pointers) : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Core Intuition (the “why” behind this approach)

The key difficulty in Duplicate Zeros is that:
• You must modify the array in-place
• The array has fixed size
• Duplicating zeros causes right-shifts, which can overwrite elements you haven’t processed yet
👉 If you try to move left-to-right, you’ll destroy future data.

So the main idea is:
|   Simulate the final array first, then fill it from the back.
This is a classic “two pointers from the end” + virtual expansion problem.

Step 1: Count zeros (simulate how much the array wants to grow)
|   int zeros = 0;
|   for (int& x : arr)
|       if (x == 0)
|           zeros++;
Each zero wants to be duplicated → array would grow by zeros.
But since we cannot actually grow the array, we treat it as if it virtually grows.

Step 2: Two pointers — real index vs virtual index
|   int i = n - 1, j = n - 1 + zeros;
• i → points to current element in original array
• j → points to where that element would go in the virtual expanded array 
Think of it like this :
Original array:   [1, 0, 2, 3]
Virtual array:    [1, 0, 0, 2, 3]
                            ↑  ↑
                            i  j
We only write when j < n, because anything beyond n-1 would fall outside the actual array.

Step 3: Copy elements backward (safe direction)
|   if (j < n) arr[j] = arr[i];
We copy arr[i] to its correct final position j.
Doing this from the back ensures that we don't overwrite elements that aren't processed yet.
This mimics how the final array would look.

Step 4: Special handling for zeros (duplication)
|   if (arr[i] == 0) {
|       j--;
|       if (j < n)
|           arr[j] = arr[i];
|   }
If the current element is 0, we must write it twice at the jth element and (j-1)th element because it must be duplicated.
This matches the problem requirement: duplicate every zero

Step 5: Move both pointers
|   i--; j--;
• i moves through the original array
• j moves through the virtual expanded array

Step 6: Safety stop 
| if (i == j) break;
This avoids unnecessary overwriting when both pointers meet.

Think of it like this:
• We pretend the array can grow
• We compute where every element should end up
• We copy backwards so nothing gets lost
• We ignore writes that fall outside the array

This is why no shifting or extra array is needed. Everything works in-place and safely
*/
void duplicateZeros(vector<int>& arr) {
    int zeros = 0, n = arr.size();
    // count zeros
    for (int& x : arr) 
        if (x == 0) 
            zeros++;
    
    int i = n - 1, j = n - 1 + zeros;

    while (i >= 0) {
        if (j < n) 
            arr[j] = arr[i];

        if (arr[i] == 0) {
            j--;
            if (j < n) 
                arr[j] = arr[i];
        }

        i--; j--;
        if (i == j) break;
    }
}

int main() {
    vector<int> arr = {1,0,2,3,0,4,5,0};
    duplicateZerosBrute(arr);
    for (int x : arr) cout << x << " ";

    return 0;
}