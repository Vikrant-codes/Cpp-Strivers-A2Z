/*
TUF - 745. Check for Perfect Number

You are given an integer n. You need to check if the number is a perfect number or not. 
Return true if it is a perfect number, otherwise, return false.

A perfect number is a number whose proper divisors (excluding the number itself) add up to the number itself.

Examples :-

Input: n = 6 __ Output: true
Explanation: Proper divisors of 6 are 1, 2, 3. 1 + 2 + 3 = 6.

Input: n = 4 __ Output: false
Explanation: Proper divisors of 4 are 1, 2. 1 + 2 = 3.

Input: n = 28 __ Output: true

Constraints :-
• 1 <= n <= 5000
*/

#include<bits/stdc++.h>
using namespace std;

// Naive Approach: Time Complexity : O(n) __ Space Complexity : O(1)
/*
Find the sum of all divisors of `n` in range [1, n-1].
Return true if the sum equals n.
*/
bool isPerfectNaive(int n) {
    int sum = 0;
    
    for (int i = 1; i < n; i++) {
        if (n % i == 0)
            sum += i;
    }

    return sum == n;
}

// Optimal Approach: Time Complexity : O(√n) __ Space Complexity : O(1)
/*
The optimal approach uses the fast method of getting the divisors of a number.
This method uses the fact that divisors always comes in pairs.
If `x` divides `n`, then we can get another divisor `y`, which also divides `n`, such that y = n / x.
This helps us get the divisors in O(√n).

We will need to explicitly handle the case for n = 1.
*/
bool isPerfect(int n) {
    if (n == 1) return false;

    int sum = 1;
    
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (n / i != i) sum += (n / i);
        }
    }
    
    return sum == n;
}

// GFG - Sum of Divisors
/*
GFG - Sum of Divisors : Basic

Given a natural number n, calculate sum of all its proper divisors. 
A proper divisor of a natural number is the divisor that is strictly less than the number.

Examples :-

Input: n = 10 __ Output: 8 
Explanation: Proper divisors 1 + 2 + 5 = 8. 

Input: n = 6 __ Output: 6
Explanation: Proper divisors 1 + 2 + 3 = 6. 

Constraints :-
• 2 <= n <= 10^6
*/
long long int divSumNaive(int n) {
    long long int sum = 0;
    
    for (int i = 1; i < n; i++) 
        if (n % i == 0)
            sum += i;
            
    return sum;
}

// Extracting factors in pairs
long long int divSum(int n) {
    long long int sum = 1;
    
    // why we initilized sum as 1?
    /*
    If we ran the loop from 1 to √n, then we would have to manually handle the condition for factor pair (1, n).
    Since, we don't want to include `n` in the sum of factors of n, so we would need to use handle this using condition 
        if (n / i != i && n / i != n)
            sum += (n / i);

    So, either we need to handle this case using conditions like `if(n/i != i && n/i != n)` or `if(n/i != i && i != 1)`
    or, we can simply run the loop starting from 2.
    For loop starting from 2, we would have no need to handle the case for when the factor pair is `n` itself.
    In this case, we need to initialize sum as `1`, since we are not considering the divisor `1` during loop.
    */

    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            
            if (n / i != i)
                sum += (n / i);
        }
    }
    
    return sum;
}


int main() {
    return 0;
}