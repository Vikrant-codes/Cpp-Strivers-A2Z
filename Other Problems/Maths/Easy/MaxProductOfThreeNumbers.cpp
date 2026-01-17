/*
Leetcode - 628. Maximum Product of Three Numbers : Easy

Given an integer array nums, find three numbers whose product is maximum and return the maximum product.

Examples :-
Input: nums = [1,2,3] __ Output: 6
Input: nums = [1,2,3,4] __ Output: 24
Input: nums = [-1,-2,-3] __ Output: -6

Constraints :-
• 3 <= nums.length <= 10^4
• -1000 <= nums[i] <= 1000
*/
#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach : Time Complexity : O(n^3) __ Space Complexity : O(1)
// Approach - Check the product of all possible triplets of num array and return the maximum product
// ⚠️ This approach won't work for this problem as O(n^3) is too large ⚠️ 

/*
Math Observations
We want the maximum product of any 3 numbers. The tricky part is negative numbers.

Key observation
After sorting:
• Largest three numbers → a = nums[n-1], b = nums[n-2], c = nums[n-3]
• Smallest two numbers → z = nums[0], y = nums[1]

Let a, b, c be 3 largest numbers & z, y be the two smallest numbers (-ves)

There are only two candidates for the maximum product:
1) Three largest numbers: a * b * c
2) Largest number + two smallest numbers: a * z * y .... (becuase tthe product of 2 -ve numbers become +ve)
Why?

Why check 3 maximums?
• If all numbers are positive, the product grows by picking the largest values.
• So the best choice is simply: largest × second largest × third largest

Why check 2 minimums?
• Two negative numbers multiplied together give a positive.
• If z and y are large-magnitude negatives, then: z * y = large positive
• Multiplying this with the largest positive number a can beat a*b*c.
Example - 
nums = [-10, -10, 5, 2]
a*b*c = 5*2*(-10) = -100
a*z*y = 5*(-10)*(-10) = 500 ✅
So the best product may involve the two smallest (most negative) numbers.

Why no other combinations?
In general case we only need the 3 maximums, but the product of 2 most negative might become a large magnitude +ve.
We can't choose all 3 most negatives because their product would be -ve and hence minimum product not maximum.
We will choose the largest number 'a' for sure, but choosing the two other largest or two smallest depends on their value.
If z * y > b * c, then we will choose a * y * z as the maximum product.
But what happens if all numbers are -ves. [-5, -4, -3, -2, -1].
Now here a = -1, b = -2, c = -3, y = -4, z = -5.
Now, we see that y * z = 20 & b * c = 6.... but since all numbers are negative and a = -1,
then a * b * c = -6 & a * y * z = -20... and clearly -6 > -20. 
So, if all numbers are negative we don't pick y, z even if their value is more

So, we only need to return a * b * c or a * y * z. depending if y * z > b * c and a is non-negative.
*/

// Better Approach (Sorting + Math observations) : Time Complexity : O(n * log n) __ Space Complexity : O(1)
// We can get a, b, c, y, z easily after sorting becuase a,b,c would be the last 3 elements and y,z would be the first two
int maximumProduct(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();

    int a = nums[n-1], b = nums[n-2], c = nums[n-3];
    int z = nums[0], y = nums[1];

    // if nums contains both +ve and -ve numbers
    // check if we should consider the first two numbers (z & y).. if z * y product becomes a high +ve
    // if (z * y > b * c && a >= 0) 
    //     return a * y * z;
        
    // return a * b * c;

    return max(a*b*c, a*y*z);
}

// Optimal Approach : Time Complexity : O(n) __ Space Complexity : O(1)
// We sorted to easily get the 3 maximums and 2 minimums 
// but we can do so by manually keeping track of the 3 maximums and 2 minimums while traversing the array.
int maximumProduct(vector<int>& nums) {
    int n = nums.size();
    int a = -9999, b = -9999, c = -9999, y = 9999, z = 9999;
    for (int& x : nums) {
        // consider x for the 3 maximums
        if (x > a) {
            c = b;
            b = a;
            a = x;
        }
        else if (x > b) {
            c = b;
            b = x;
        }
        else if (x > c) {
            c = x;
        }
        // consider x for the 2 minimums
        if (x < z) {
            y = z;
            z = x;
        }
        else if (x < y) {
            y = x;
        }
    }

    return max (a * b * c, a * y * z);
}

int main() {

    return 0;
}