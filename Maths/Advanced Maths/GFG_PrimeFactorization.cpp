/*
GFG - All Prime Factors in Any Order : Medium

You are given a positive integer n, return its prime factors in any order.
A prime number is a natural number greater than 1 that has no positive divisors other than 1 and itself.

Examples :-

Input: n = 18 
Output: [2, 3, 3]
Explanation: Prime Factorization of 18 is 2 * 3^2.

Input: n = 25
Output: [5, 5]
Explanation: Prime Factorization of 25 is 5^2.

Constraints :-
• 1 <= n <= 10^9
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach :- Time Complexity : O(n) __ Space Complexity : O(1)
/*
- Start a loop from i = 2 up to n.
- For each i, check if n is divisible by i (i.e n % i == 0).
- While n is divisible by i, store i as a factor and divide n by i.
- Continue this process for all i up to n to extract all prime factors.
*/
vector<int> primeFactorsNaive(int n) {
    vector<int> ans;
    
    for (int i = 2; i <= n; i++) {
        while (n % i == 0 && n > 0) {
            ans.push_back(i);
            n = n / i;
        }
    }

    return ans;
}

// Optimal Approach :- Time Complexity : O(√n) __ Space Complexity : O(1)
/*
The intuition behind the optimal approach is based on eliminating prime factors one by one, starting from the smallest.

>> Observation: Every composite number has a prime factor
Suppose: n = 180
Its prime factorization is:- 180 = 2 × 2 × 3 × 3 × 5
If we keep dividing by a prime whenever possible, eventually only prime factors remain.
So the goal is simply:
| Find the smallest prime factor, divide it out completely, then move to the next one.

>> Step 1: Remove all factors of 2
2 is the only even prime.
Instead of checking every even number later, we remove them immediately.
    while (n % 2 == 0) {
        ans.push_back(2);
        n /= 2;
    }
Example: n = 72
72 → 36 → 18 → 9
Factors collected: 2, 2, 2
Now n has become odd.

This means no even number can divide it anymore.
So we never need to check : 4, 6, 8, 10, ...

>> Step 2: Check only odd numbers
Now we do
    for (int i = 3; i * i <= n; i += 2)
Notice: 3, 5, 7, 9, 11, ...
Even though numbers like 9, 15, 21 aren't prime, that's okay.
If they were composite, all their prime factors would already have been removed earlier.

Example: n = 90 -> Remove 2 (90 → 45) -> Now check 3 divides 45 (45 → 15 → 5)
Collected: 2 3 3
Next i = 5 -> 5 divides 5 
Collected: 2 3 3 5

>> Why divide repeatedly?
Suppose: n = 108
108 = 2 × 2 × 3 × 3 × 3
If we divide only once, 108 → 54
we'd miss another 2.
So we keep dividing until that factor disappears.
    while (n % i == 0)
This ensures every occurrence is collected.

>> The most important intuition: Why stop at √n?
This is the key idea.
Suppose: n = 100
Its factors are
    1 × 100
    2 × 50
    4 × 25
    5 × 20
    10 × 10
Notice something:
Every factor greater than √100 (=10) has a corresponding factor smaller than √100.
If a number had a factor larger than √n (like 25) then the other factor is (100 / 25 = 4) which is already below √n.

So if no number up to √n divides n, then there is no smaller partner factor.
That means n cannot be composite.
Therefore: If we've checked every possible divisor up to √n and found none, then n itself must be prime.

So, we loop till i * i <= n instead of i <= n which reduces the work from o(n) to O(√n).

>> Why does i * i <= n use the updated n?
Notice we're continuously dividing n.
Example: n = 360
Remove 2's
360 → 180 → 90 → 45
Now n is only 45.
The square root also shrinks:
√360 ≈ 19
√45 ≈ 6
So instead of checking: 3 5 7 9 11 13 15 17 19
we only check: 3 5
Updating n makes the algorithm even faster because the search space keeps shrinking.

>> Why do we finally write : if (n > 1) ans.push_back(n);
Imagine: n = 78
Remove 2: 78 → 39
Check 3: 39 → 13
Now: i = 5 and 5 * 5 = 25 > 13
The loop stops.
We're left with: n = 13
Since we already checked every possible divisor up to √13, the remaining 13 must be prime.
So we simply add it.

>> One-line intuition to remember
| Repeatedly remove the smallest possible prime factor. 
| First remove all 2's, then try only odd divisors up to √n. 
| Every time a factor is found, divide it out completely. 
| If anything remains after that, it must itself be a prime factor.

>> Complexity Analysis 

In average cases, the program runs in less than O(√n) time because 
the number of iterations is reduced as n gets smaller with each division. 
But, the worst case scenario occurs when n is a prime number, in which case the loop runs until √n.
Ex- n = 101, the program will check for 2 and then for odd numbers 3, 5, 7, 9 and will then exit the loop
Since, n is not divisible by any of these numbers, the loop will run for approx. √n iterations.

The space complexity is O(1) since we are only using a vector to store the prime factors, 
which is proportional to the number of prime factors of n.
*/
vector<int> primeFactors(int n) {
    vector<int> ans;
        
    while (n % 2 == 0) {
        ans.push_back(2);
        n /= 2;
    }
        
    for (int i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            ans.push_back(i);
            n /= i;
        }
    }
    
    if (n > 1) 
        ans.push_back(n);
        
    return ans;
}

int main() {
    return 0;
}