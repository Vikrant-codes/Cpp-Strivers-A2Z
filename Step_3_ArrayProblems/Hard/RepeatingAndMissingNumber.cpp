/*
Leetcode - 645. Set Mismatch : Easy

You have a set of integers s, which originally contains all the numbers from 1 to n. 
Unfortunately, due to some error, one of the numbers in s got duplicated to another number in the set, 
which results in repetition of one number and loss of another number.

You are given an integer array nums representing the data status of this set after the error.

Find the number that occurs twice and the number that is missing and return them in the form of an array.

Examples :-

Input: nums = [1,2,2,4] __ Output: [2,3]

Input: nums = [1,1] __ Output: [1,2]

Constraints :-
• 2 <= nums.length <= 10^4
• 1 <= nums[i] <= 10^4
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach: Time Complexity : O(n²) __ Space Complexity : O(1)
/*
>> Intuition

Since the numbers are in the range [1, n], we know exactly which numbers should be present.

We can check the frequency of every number from 1 to n:
- For each number, traverse the entire array and count its occurrences.
- If its frequency is 2, it is the repeating number.
- If its frequency is 0, it is the missing number.
Once we identify both, we can return the answer.

>> Complexity Analysis
- Time: O(n²) — for every number from 1 to n, we traverse the entire array.
- Auxiliary space: O(1) — we only use a few variables.
*/
vector<int> findErrorNumsBrute(vector<int>& nums) {
    int n = nums.size();

    int repeating = -1;
    int missing = -1;

    for(int i = 1; i <= n; i++) {
        int cnt = 0;

        for(int j = 0; j < n; j++) {
            if(nums[j] == i)
                cnt++;
        }

        if(cnt == 2) repeating = i;
        else if(cnt == 0) missing = i;
    }

    return {repeating, missing};
}

// Better Approach (Hashing): Time Complexity : O(2n) __ Space Complexity : O(n)
/*
>> Intuition

In the brute-force approach, we repeatedly traverse the array to calculate the frequency of each number.
We can avoid this repeated traversal by maintaining a frequency array.

Since the given numbers are in the range [1, n], we can create a frequency array of size n+1.
- Traverse the given array and increment the frequency of each number.
- Now traverse the frequency array from 1 to n.
- If the frequency is 2, that number is repeating.
- If the frequency is 0, that number is missing.

This way, we calculate all frequencies in a single traversal and identify the required numbers in another traversal.

>> Complexity Analysis
- Time: O(2n) — one traversal of the input array and one traversal of the frequency array.
- Auxiliary space: O(n) — the frequency array requires n+1 positions.
*/
vector<int> findErrorNumsHashing(vector<int>& nums) {
    int n = nums.size();

    vector<int> freq(n+1, 0);

    int repeating = -1;
    int missing = -1;

    // Store frequencies
    for(int num : nums)
        freq[num]++;

    // Identify repeating and missing numbers
    for(int i = 1; i <= n; i++) {
        if(freq[i] == 2)
            repeating = i;
        
        else if(freq[i] == 0)
            missing = i;
    }

    return {repeating, missing};
}

// Optimal Approach (Mathematical): Time Complexity : O(n) __ Space Complexity : O(1)
/*
>> Mathematical Approach — Using Sum and Sum of Squares
Let:
- x = repeating number
- y = missing number

We know that the array should originally contain all numbers from 1 to n, but x appears twice and y is missing.
We can use this information to form two equations.

-> Step 1: Find the difference between the repeating and missing numbers.

The expected sum of numbers from 1 to n is: 
    S = n * (n + 1) / 2

Let actualSum be the sum of all elements in the given array.
Since x occurs one extra time and y is missing:
    actualSum = S + x - y

Rearranging:
    x - y = actualSum - S

Let:
    -------------
    | x - y = p |                       -------- (1)
    -------------
where p = actualSum - expectedSum

-> Step 2: Find the sum of the repeating and missing numbers.

The expected sum of squares of numbers from 1 to n is:
    S2 = n * (n + 1) * (2n + 1) / 6

Let actualSquareSum be the sum of squares of all elements in the given array.
Since x occurs one extra time and y is missing:
    actualSquareSum = S2 + x² - y²

Rearranging:
    x² - y² = actualSquareSum - S2

Using the identity: (x² - y²) = (x - y) (x + y)
We get:
    (x - y) (x + y) = actualSquareSum - S2

Substituting value of (x - y) from eqn (1):
    p * (x + y) = actualSquareSum - S2
 => (x + y) = (actualSquareSum - S2) / p

or, 
    -------------
    | x + y = q |                       -------- (2)
    -------------
where q = (actualSquareSum - S2) / p

-> Step 3: Calculate x and y.

We now have two equations:
    x - y = p
    x + y = q

Adding both equations:
    2x = p + q
  => 
    -------------------
    | x = (p + q) / 2 |
    -------------------
And since x - y = p:
    -------------
    | y = x - p |
    -------------

We have successfully found both numbers!

>> Complexity Analysis
- Time: O(n) — one traversal of the array to calculate its sum and sum of squares. 
  All remaining calculations take constant time.
- Auxiliary space: O(1) — we use only a few variables.
*/
vector<int> findErrorNums(vector<int>& nums) {
    long long n = nums.size();

    long long actualSum = 0;
    long long actualSquareSum = 0;

    for(int num : nums) {
        actualSum += num;
        actualSquareSum += 1LL * num * num;
    }

    long long expectedSum = n * (n + 1) / 2;

    long long expectedSquareSum = n * (n + 1) * (2*n + 1) / 6;

    // x - y = p
    long long p = actualSum - expectedSum;

    // x + y = q
    long long q = (actualSquareSum - expectedSquareSum) / p;

    // Calculate x and y
    long long x = (p + q) / 2;
    long long y = x - p;

    return {(int)x, (int)y};
}

// Optimal Approach (Bit Manipulation): Time Complexity : O(n) __ Space Complexity : O(1)
/*
>> Optimal — Bit Manipulation (XOR)

Let:
- x = repeating number
- y = missing number

-> Step 1: Find x ^ y.

If we XOR all the elements of the given array and all the numbers in the range [1, n], we will get:
    xorr = x ^ y

Why?
- Every number other than x and y occurs exactly twice: once in the array and once in the range [1,n].
- Since a ^ a = 0, all those numbers cancel out.
- The repeating number x occurs one extra time, while y is absent from the array, so both remain in the XOR result.

However, this gives us only x ^ y, not the individual values of x and y.

-> Step 2: Find a differentiating bit.

We know that: x ^ y ≠ 0
Why? Because x and y are two different numbers (one is repeating and the other is missing). 
XOR of two different numbers cannot be zero.

Therefore, the binary representation of x ^ y must contain at least one set bit (1).

At any set bit position of (x ^ y), x and y must have different bits:
- One number has 0 at that position.
- The other number has 1 at that position.

So, we can use this bit to separate x and y.

We choose the rightmost set bit of x ^ y.
We can find it either by:
- Using a while loop that keeps shifting until the rightmost set bit is found.
- Directly using the bit manipulation expression:
    bit = xorr & ~(xorr - 1)

-> Step 3: Divide the numbers into two buckets.

We maintain two buckets:
- zero — numbers whose differentiating bit is 0.
- one — numbers whose differentiating bit is 1.

We place both:
- All elements of the given array.
- All numbers from the range [1, n].
into their respective buckets based on that bit (the rightmost set bit of (x ^ y)).

Why does this separate x and y?
Because we selected a bit where x and y differ. Therefore, they must go into different buckets.

-> Step 4: XOR the elements in each bucket.

Now, XOR all elements within each bucket.
Why does this work?
Remember that every number other than x and y occurs twice overall:
- Once in the given array.
- Once in the range [1, n].
Also, the same number always has the same differentiating bit, so both occurrences will go into the same bucket.

Consequently, they cancel each other out (since, a ^ a = 0).
This leaves only one number in each bucket:
- One bucket gives us x.
- The other bucket gives us y.
We cannot determine which bucket contains the repeating number and which contains the missing number yet.

-> Step 5: Identify which one is repeating.

We simply count the occurrences of either candidate in the original array.
- If its frequency is 2, it is the repeating number.
- If its frequency is 0, it is the missing number.

We can then return the two numbers in the required order: [repeating, missing].

>> Complexity Analysis
- Time: O(n) — we traverse the array and the range [1,n] a constant number of times.
- Auxiliary space: O(1) — only a few variables are used.
*/
vector<int> findErrorNums(vector<int>& nums) {
    int n = nums.size();
    int xr = 0;

    // XOR all array elements
    for(int num : nums) {
        xr ^= num;
    }

    // XOR all numbers from 1 to n
    for(int i = 1; i <= n; i++) {
        xr ^= i;
    }

    // xr = x ^ y

    // Find the rightmost set bit

    // int bit = 1;
    // while((xr & bit) == 0) {
    //     bit <<= 1;
    // }

    // Alternatively, directly find the rightmost set bit:
    int bit = xr & ~(xr - 1);

    // Two buckets
    int zero = 0, one = 0;

    // Distribute array elements into buckets
    for(int num : nums) {
        if(num & bit)
            one ^= num;
        else
            zero ^= num;
    }

    // Distribute numbers from 1 to n into buckets
    for(int i = 1; i <= n; i++) {
        if(i & bit)
            one ^= i;
        else
            zero ^= i;
    }

    // These are the two candidates (order unknown)
    int x = zero;
    int y = one;

    // Identify repeating and missing numbers
    int cnt = 0;

    for(int num : nums) {
        if(num == x)
            cnt++;
    }

    if(cnt == 2)
        return {x, y};

    return {y, x};
}

int main() {
    return 0;
}