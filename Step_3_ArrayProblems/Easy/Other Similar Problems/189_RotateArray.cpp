// Right Rotate Array by K Places

/*
Leetcode - 189. Rotate Array : Medium

Given an integer array nums, rotate the array to the right by k steps, where k is non-negative.

Examples :-

Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]

Input: nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]
Explanation: 
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]

Constraints :-
• 1 <= nums.length <= 10^5
• -2^31 <= nums[i] <= 2^31 - 1
• 0 <= k <= 10^5

Follow up:
Try to come up with as many solutions as you can. There are at least three different ways to solve this problem.
Could you do it in-place with O(1) extra space?
*/

#include<bits/stdc++.h>
using namespace std;

// The approaches for this problem are similar to that of "Left Rotate Array by K places"
/*
We can't directly over-write the values using nums[i] = nums[(n + (i - k)) % n] 
because doing so will result in losing some values.
During this process, the value of the last k elements will be lost 
(like how the value of last element is lost when doing right rotation by 1 place)

So, we just need to store these last k values into the temporary vector, 
and after that we can directly shift the elements of nums.
We can place the temp vector values at their appropriate place also.

Example:- nums = [1, 2, 3, 4, 5, 6, 7], k = 3
If we start replacing the values by the value at 'k' steps previous, then
At index 6: value = 7, replaced by value at index 3 (4) __ nums = [1, 2, 3, 4, 5, 6, 4]
At index 5: value = 6, replaced by value at index 2 (3) __ nums = [1, 2, 3, 4, 5, 3, 4]
At index 4: value = 5, replaced by value at index 1 (2) __ nums = [1, 2, 3, 4, 2, 3, 4]
At index 6: value = 7, replaced by value at index 0 (1) __ nums = [1, 2, 3, 1, 2, 3, 4]

Now, we want to replace the value at index 2, the value which should come at this place would be k steps to its right
treating nums as circular, this value would be at index (n-1) = index 6.
But, we had already over-written this value previously, so its original value has been lost.
The first k elements value still need to be over-written, but the original values which would be used to over-write them 
has been lost since we over-written them.
*/

// Naive Approach : Time Complexity : O(2n) __ Space Complexity : O(n)
/*
>> Approach
- Build a rotated array by placing the array elements at their correct position in a temp array
- Copy the elements from this temp array back to original array (nums)

>> Time Complexity :-
- Building the temp array (each of the n elements of nums is placed at its correct position in temp): O(n)
- Copying elements from temp to original array: O(n)
Total = O(n) + O(n) = O(2n)

>> Space Complexity :-
- We are using a extra array of size n to store the rotated elements at their correct position, so O(n)
*/
void rotateNaive1(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> temp;

    k = k % n;
    
    for (int i = n - k; i < n; i++)
        temp.push_back(nums[i]);
    
    for (int i = 0; i < n - k; i++) 
        temp.push_back(nums[i]);
    
    for (int i = 0; i < n; i++)
        nums[i] = temp[i];
}

void rotateNaive2(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> temp(n);

    k = k % n;
    
    for (int i = 0; i < n; i++)
        temp[i] = nums[(n + (i - k)) % n];
    
    for (int i = 0; i < n; i++)
        nums[i] = temp[i];
}

// Better Approach : Time Complexity : O(n + k) __ Space Complexity : O(k)
/*
We can store the last k values in a temp vector as these were the values which were lost during direct over-writing.
After storing them in the temp vector, we can directly over-write values to build the rotated array in place.

The last (n-k) elements can be over-written directly using nums[i] = nums[i-k].
The first k elements new values must be get from the temp vector.

>> Time Complexity 
- Building temp vector (stores the last k elements) : O(k)
- Re-writing the values of last n-k elements using nums[i] = nums[i-k]: O(n-k)
- Re-writing the first k values in nums using values from temp vector: O(k)
Total: O(k) + O(n-k) + O(n) = O(n + k)

>> Space Complexity
- We are storing k elements in the temp vector, so O(k)
*/
void rotateBetter(vector<int>& nums, int k) {
    int n = nums.size();
    k = k % n;

    vector<int> temp(k);

    // store the last k elements of nums in a temp vector
    for (int i = 0; i < k; i++)
        temp[i] = nums[n - k + i];

    // right shift the elements of nums

    // the last n-k elements values can be overwritten directly 
    // value at index i will be overwritten by value at index (i-k)
    /*
    int p = n-k;
    int i = n-1;
    while(p--) {
        nums[i] = nums[i-k];
        i--;
    }
    */
    for (int i = n-1; i >= k; i--)
        nums[i] = nums[i - k];
        
    // for the first k elements, we can get their new values from the temp vector
    for (int i = 0; i < k; i++)
        nums[i] = temp[i];
}

// Optimal Approach (Reversal) : Time Complexity : O(2n) __ Space Complexity : O(1)
/*
- Reverse the entire array
- Reverse the first k elements
- Reverse the remaining n-k elements

The rotated array contains the last k elements at the front, 
so we reverse the entire array so that last elements come to front.
But these last k elements which came to front due to reversal, are in reversed order, 
so we again reverse these 'k' elements to get them in proper order
(these last k elements become the first k elements due to reversal, so we now reverse the first k array elements).
Also the order of the remaining elements is also reversed due to the entire array reversal, 
hence we must reverse these remaining elements as well. There are n-k elements remaining so we reverse them as well.

>> Time Complexity Analysis :-
Assume, nums.size() = n

reversing 'x' elements using the reverse method takes O(x) time.
In the code, we are doing 3 reversals 
- Reverse the entire array -> n elements: O(n)
- Reverse the first k elements: O(k)
- Reverse the remaining array elements -> (n-k) elements: O(n-k)
So, total = O(n) + O(k) + O(n-k) = O(2n)
*/
void rotateReversal1(vector<int>& nums, int k) {
    int n = nums.size();
    k = k % n;

    vector<int>::iterator it = nums.begin();
    
    reverse(it, it + n);
    reverse(it, it + k);
    reverse(it + k, it + n);
}

// Without using the built-in reverse method & iterator
void reverseArr(vector<int>& nums, int start, int end) {
    while (start < end) {
        swap(nums[start], nums[end]);
        start++; end--;
    }
}

void rotateReversal2(vector<int>& nums, int k) {
    int n = nums.size();
    k = k % n;

    reverseArr(nums, 0, n-1);      // reverse the whole array
    reverseArr(nums, 0, k-1);      // reverse the first k elements
    reverseArr(nums, k, n-1);      // reverse the next n-k elements
}

// Most Optimal Approach (Juggling Algorithm) : Time Complexity : O(n) __ Space Complexity : O(1)

// Juggling Algorithm for Right Rotation
/*
>> Intuition

A straightforward way to rotate an array is to repeatedly move elements one step at a time or use an extra array. 
However, both approaches do unnecessary work or require additional space.

Observe that during a right rotation by k, every element moves to exactly one new position:
    newIndex=(currentIndex+k)modn
Instead of thinking about where each element should go, we can think in the reverse direction:
| Which element should come to the current position?
For an index currIdx, the required element comes from
    (currIdx − k + n) mod n
This is exactly the index computed in the solution.

>> Cyclic Movement
If we keep following this mapping repeatedly,
    curr -> curr-k -> curr-2k -> curr-3k -> ...
we eventually return to the starting index, forming a cycle.

For example, n = 6, k = 2
the movements of values will happen in the following index cycles
    0 <- 4 <- 2 <- 0
    1 <- 5 <- 3 <- 1
The array is divided into two independent cycles.

Within one cycle, we can rotate all the elements using only a single temporary variable:
- Save the first element.
- Keep pulling the previous element (curr-k) into the current position.
- When we reach the starting index again, place the saved value.
This shifts every element in that cycle to its correct rotated position.

>> Why Multiple Cycles?
A single traversal does not always visit every element.
The number of independent cycles depends on the relationship between n and k.
- If gcd(n, k) = 1, every index belongs to one large cycle, 
    so starting from index 0 visits the entire array.
- If gcd(n, k) > 1, the indices split into multiple disjoint cycles. 
    After completing one cycle, there are still untouched elements belonging to other cycles.

For example, n = 8, k = 2
Cycle 1: 0 → 6 → 4 → 2 → 0
Cycle 2: 1 → 7 → 5 → 3 → 1
Since the cycles never intersect, we must start once from each cycle.

The number of such cycles is exactly
    gcd(n,k)
so iterating from 0 to gcd(n, k)-1 guarantees that every element is processed exactly once.

>> Why This Works
Each index belongs to exactly one cycle, and every cycle is processed independently.

Within a cycle:
- every element is moved exactly once,
- no value is overwritten because the first value is stored in temp,
- and after completing the cycle, all positions contain the values they would have after a right rotation by k.
Since the cycles together cover all n indices, the entire array is rotated in-place.

>> Time Complexity: O(n) — every element is visited exactly once.
>> Space Complexity: O(1) — only a single temporary variable is used.
*/

// Helper method to get gcd of two elements
int gcd(int a, int b) {
    if (b == 0)
        return a;
        
    return gcd(b, a % b);
}

// Implementation 1
void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    k = k % n;

    int cycles = gcd(n, k);
    
    for (int i = 0; i < cycles; i++) {
        int temp = nums[i];
        int currIdx = i;

        do {
            int nextIdx = (n + (currIdx - k)) % n;
            
            if (nextIdx != i)
                nums[currIdx] = nums[nextIdx];
            else
                nums[currIdx] = temp;
            
            currIdx = nextIdx;

        } while (currIdx != i);
    }
}

// Implementation 2
void rotate2(vector<int>& nums, int k) {
    int n = nums.size();
    k = k % n;

    int cycles = gcd(n, k);
    
    for (int i = 0; i < cycles; i++) {
        int temp = nums[i];
        int currIdx = i;

        while(true) {
            int nextIdx = (n + (currIdx - k)) % n;

            if (nextIdx == i) break;
            
            nums[currIdx] = nums[nextIdx];
            currIdx = nextIdx;
        }

        // loop exits when the new value which must come at currIdx is the starting index value (temp)
        nums[currIdx] = temp;
    }
}

int main() {
    return 0;
}