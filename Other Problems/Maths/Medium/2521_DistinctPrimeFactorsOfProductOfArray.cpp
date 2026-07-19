/*
Leetcode - 2521. Distinct Prime Factors of Product of Array : Medium

Given an array of positive integers nums, return the number of distinct prime factors in the product of the elements of nums.

Note that:
• A number greater than 1 is called prime if it is divisible by only 1 and itself.
• An integer val1 is a factor of another integer val2 if val2 / val1 is an integer.

Examples :-

Input: nums = [2,4,3,7,10,6] __ Output: 4
Explanation:
The product of all the elements in nums is: 2 * 4 * 3 * 7 * 10 * 6 = 10080 = 25 * 32 * 5 * 7.
There are 4 distinct prime factors so we return 4.

Input: nums = [2,4,8,16] __ Output: 1
Explanation:
The product of all the elements in nums is: 2 * 4 * 8 * 16 = 1024 = 210.
There is 1 distinct prime factor so we return 1.

Constraints :- 
• 1 <= nums.length <= 10^4
• 2 <= nums[i] <= 1000
*/

#include <bits/stdc++.h>
using namespace std;

/*
We can't calculate the product of the whole array to get the count of its distinct prime factors,
Since the constraints suggest that nums array can have around 10^4 numbers in it with each no. having value in range [2,1000].
This would make the product too large to store. 
So, we have to think about getting the count of distinct prime factors of the product of the array 
without actually calculting the product.
*/

// Approach 1 : Time Complexity : O(N * √M) __ Space Complexity : O(1)
/*
We know that the product of array will form by multiplying all the numbers of the array,
so the product will have all the prime factors of the array elements.
So, we can use a set and iterate through the array and for each element 'n', we can put its prime factors in the set.
In this way, the set will store all the distinct prime factors of all array elements.
After array traversal ends, we can simply return the size of set 
as it will represent the count of distinct prime factors the product of array (all array elements) have.

>> Time Complexity Analysis :
- For each number n, we perform prime factorization.
- Checking factor 2 takes O(log n) in the worst case (due to repeated division).
- The loop : for (int i = 3; i * i <= n; i += 2) -> runs up to √n.
    So each number takes O(√n) in the worst case.

Thus, for an array of size N: Time Complexity = O(N * √M) where M is the maximum element in nums
*/
int distinctPrimeFactors1(vector<int>& nums) {
    set<int> factors;

    for (int n : nums) {

        if (n % 2 == 0) {
            factors.insert(2);

            while (n % 2 == 0) n /= 2;
        }

        for (int i = 3; i * i <= n; i+=2) {
            if (n % i == 0) {
                factors.insert(i);

                while (n % i == 0) n /= i;
            }
        }

        if (n != 1) factors.insert(n);

    }

    return factors.size();
}

// Optimal Approach : Time Complexity : O(M log log M) + O(N log M)  __ Space Complexity : O(M)
/*
We can use the concept of Smallest Prime Factor Sieve (SPF Sieve) & Prime Factorization calculation using sieve
to quickly get the prime factors for each element n of the array.

Since, the maximum value of arr[i] can be 1000, so we can create an SPF sieve for elements upto 1000
and then using this sieve, we can quickly get the prime factors for the array elements.

>> Time Complexity Analysis :
- computing SPF Sieve : It takes O(M log log M), where M = 1000
- Prime Factorization of all numbers (N elements) using spf sieve : O(N log M)
    (Using Sieve, we can calculate the prime factorization of a number x in O(log x) time)
So, total time complexity : O(M log log M) + O(N log M)

>> Space Complexity : 
- We are using an extra space to store the spf sieve, since we are computing sieve till M (which is 1000), so O(M).
*/
// Helper method -- returns spf sieve upto n 
vector<int> getSieveSPF(int n) {
    vector<int> spf(n+1);
    // set all values to the index value
    for (int i = 1; i <= n; i++) 
        spf[i] = i;

    for (int i = 2; i * i <= n; i++) {
        // if current element is prime (spf[i] == i)
        if (spf[i] == i) {
            // mark its multiples to have spf = i, only if those multiples aren't previously marked
            for (int j = i * i; j <= n; j += i) {
                // spf[j] == j checks that the current multiple hasn't been previously marked by smaller prime
                if (spf[j] == j) {
                    spf[j] = i;
                } 
            }
        }
    }

    return spf;
}

int distinctPrimeFactors(vector<int>& nums) {
    set<int> factors;
    
    vector<int> spf = getSieveSPF(1000);
    
    for (int n : nums) {
        // get prime factors of n using spf
        while (n != 1) {
            factors.insert(spf[n]);
            n = n / spf[n];
        }
    }

    return factors.size();
}

int main() {
    return 0;
}