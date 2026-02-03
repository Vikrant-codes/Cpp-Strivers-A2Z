/*
Leetcode - 1250. Check If It Is a Good Array : Hard

Given an array nums of positive integers. 
Your task is to select some subset of nums, multiply each element by an integer and add all these numbers. 
The array is said to be good if you can obtain a sum of 1 from the array by any possible subset and multiplicand.

Return True if the array is good otherwise return False.

Examples :-

Input: nums = [12,5,7,23] __ Output: true
Explanation: Pick numbers 5 and 7 :- 5*3 + 7*(-2) = 1

Input: nums = [29,6,10] __ Output: true
Explanation: Pick numbers 29, 6 and 10 :- 29*1 + 6*(-3) + 10*(-1) = 1

Input: nums = [3,6] __ Output: false
 
Constraints :-
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
*/

#include <bits/stdc++.h>
using namespace std;

/*
Approach :- 
Observations :-
"The array is “good” iff it contains elements that are co-prime (i.e., their GCD is 1)"

We observe that an array is good only if it contains a subset such that the GCD of all the elements of that subset is 1. 
Like for numbers 5 & 7, we see that the array is good because 5 & 7 are co-prime (i.e. their GCD is 1). 
Example - [6, 10, 15].. Even though all the numbers are non - co-primes (6,10), (6,15), (10,15) the array is still good
becuase we can combine all 3 elements 6, 10 & 15 to get 1 like 6 * 1 + 10 * 1 + 15 * (-1) = 6 + 10 - 15 = 1.
This is because all 3 elements (6, 10, 15) combined give us the required GCD 1 thus making the array a good array.
So we can iterate through the array keeping track of the gcd of all the elements encountered and if that gcd == 1 return true.

(I didn't knew about this Bézout’s identity..)

🧠 Intuition
A “good array” means:
There exist integer coefficients such that a linear combination of the elements equals 1.
(Formally: a₁x₁ + a₂x₂ + ... + aₙxₙ = 1 for some integers x₁, x₂, ...)
From Bézout’s identity, this is possible if and only if the greatest common divisor (GCD / HCF) of all elements is 1.
So the array is good ⇢ GCD(nums) == 1

⚙️ Algorithm
1. If the array has one element: Return true only if that element is 1, else false.
2. Find GCD of entire array:
-- Start with GCD of the first two numbers.
-- If at any point the GCD becomes 1, stop early — the array is definitely good.
-- Otherwise, keep combining via gcd(hcf, nums[i]).
3. Return true if final GCD is 1, else false.
*/

// This method of finding HCF is called Euclid’s Algorithm (for GCD or HCF)
// Time Complexity of Euclid's Algorithm : O(log(min(a, b))) __ Space Complexity : O(1)
int getHCF(int n1, int n2) {
    // we assume that n1 < n2 i.e. n2 is the bigger number
    if (n1 > n2) return getHCF(n2, n1);
    int rem = n2 % n1;
    while (rem != 0) { 
        n2 = n1;
        n1 = rem;
        rem = n2 % n1;
    }
    return n1;
}

// Time Complexity : O(n * log(min( nums[i]) ) ) __ Space Complexity : O(1)
bool isGoodArray(vector<int>& nums) {
    if (nums.size() == 1) {
        return nums[0] == 1;
    }
    // find the hcf of the whole array .. if its 1 return true else false
    int hcf = getHCF(nums[1], nums[0]);
    if (hcf == 1) return true;     // if first two are co-primes return true
    for (int i = 2; i < nums.size(); i++) {
        hcf = getHCF(hcf, nums[i]);
        if (hcf == 1) return true;
    }
    return false;
}

int main() {

    return 0;
}