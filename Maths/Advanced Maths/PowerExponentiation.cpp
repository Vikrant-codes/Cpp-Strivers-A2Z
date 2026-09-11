// Implement the power method (pow(x, n)) which calculates x ^ n (i.e., x raised to the power n)
/*
pow(x, n) :- It is a pre-defined method which returns x ^ n.

The built-in method signature is somewhat like `double pow(double x, double n)` 
It calculates power of x ^ n, where x and n are of `double` data type.
It returns a `double` value as result of exponentiation.

For now, our goal is to implement the power method which can calculate x ^ n, 
where x is some double variable and n is some integer.
i.e., something like `double pow(double x, int n)`

We are considering that the input will always be valid such that x^n is a valid & mathematically determinate value.
So, inputs like 0 ^ 0, or 0 raised to negative power will never be given.
(0 ^ 0 is indeterminate. 0 raised to -ve power is same as divide by 0.)
*/

#include<bits/stdc++.h>
using namespace std;

// For the ease of understanding, let's first try to implement/code the pow function considering x & n are +ve integers

// Naive Approach :- Time Complexity : O(n) __ Space Complexity : O(1)
/*
| x raised to the power n => x ^ n = x * x * x ... n times
So, we can initialize a result/answer variable as `1` and iterate n times and multiply ans by `x` in each iteration.
*/
int myPowNaive(int x, int n) {
    // Early return statements
    if (x == 0) return 0;   // 0 raised to any power is 0.
    if (n == 0) return 1;   // any value raised to the power 0 is 1.

    int ans = 1;

    for (int i = 1; i <= n; i++)
        ans *= x;
    
    return ans;
}

// *Fast Exponentiation / Binary Exponentiation 
// Optimal Approach :- Time Complexity : O(log n) __ Space Complexity : O(1)
/*
We want to compute x^n
The naive way is : x * x * x * x * ... (n times)
which takes O(n) to perform multiplication iteratively.
Can we somehow reduce the exponent much faster?

>> Observe what happens when n is even
Suppose, x^8
Instead of writing : x * x * x * x * x * x * x * x
group them in pairs: (x * x) * (x * x) * (x * x) * (x * x) 
which is (x²)^4
Even better,
    (x²)^4
    = ((x²)²)^2
    = (x⁴)^2
    = x⁸

So whenever the exponent is even, x^n = (x²) ^ (n/2)
This is the entire optimization.
Instead of doing 8 multiplications, we transform the problem into computing, (x²)^4. 
The exponent becomes half.

>> What if n is odd?
Take x^13
We cannot directly halve 13.
But notice : x^13 = x * x^12
Now 12 is even.
So, x^13 = x * (x²)^6
Therefore, when n is odd, x^n = x * (x ^ n−1)
We first remove one x, making the exponent even.

>> We use a variable ans to store the ans, initially ans = 1.
we try to imititate this above logic:

-> We know that when n is even, x^n = (x²) ^ (n/2)
So, when n is even :
    we do n = n / 2
    but x should now become equal to x^2 since, x^n = (x²) ^ (n/2)
    so, x = x * x           (equal to x²)

-> When n is odd, x^n = x * x ^ (n-1), where n-1 is even
We try to take out one x, so that we can make n even which can then be divided by 2 in next steps.
This x which is taken out must be multiplied to the answer.
So, when n is odd :
    ans = ans * x       (take out one x)
    n = n - 1           (make n even)

>> Complexity analysis :-
We are doing n / 2 repeatedly when n is even and we do n=n-1 when n is odd (making it even for next iteration)
This whole iterations will be done only till n doesn't become 0, which it will become in roughly O(log n) time.
*/
int myPowEff(int x, int n) {
    // Early return statements
    if (x == 0) return 0;   // 0 raised to any power is 0.
    if (n == 0) return 1;   // any value raised to the power 0 is 1.

    int ans = 1;
    while (n > 0) {
        if (n % 2 == 1) {
            ans = ans * x;
            n = n - 1;
        }
        else {
            x = x * x;
            n = n / 2;
        }
    }

    return ans;
}

// Other implementation
int myPowEff2(int x, int n) {
    if (x == 0) return 0;
    if (n == 0) return 1;

    int ans = 1;
    while (n > 0) {
        // n & 1 checks if n is odd
        if (n & 1) 
            ans = ans * x;
            // no need to explicitly do n = n - 1
        
        x = x * x;
        n /= 2;
    }

    return ans;
} 

// *What if x is a double value and n can be negative as well ?
/*
>> If n is -ve :-
Suppose we need to calculate 5 ^ (-2), we know that 5^(-2) is same as 1/(5^2)
since negative power means we have to divide by x instead of multiplying it n times.

So, to calculate x ^ n where n can be a -ve integer as well, we do :
- use a bool variable to denote whether n is negative or positive.
- make 'n' positive so we can run the loop and calculate answer as how we did for +ve values of n.
- After loop ends, check if n was negative (using the bool variable), if yes, ans = 1 / ans.
- Return ans
for cases when n is negative, ans would turn out to be double value since 1/ans will be double.
So, we need to store ans as double as well.

>> What if x is double ?
If x is double, we simply need to declare the ans variable as double instead of int.
*/
double myPow(double x, int n) {
    if (x == 0) return 0.0;
    if (n == 0) return 1.0;

    bool isNegative = (n < 0) ? true : false;
    n = abs(n);

    double ans = 1;
    while (n > 0) {
        if (n % 2 == 1) {
            ans = ans * x;
            n = n - 1;
        }
        else {
            x = x * x;
            n = n / 2;
        }
    }
    
    if (isNegative) ans = 1.0/ans;

    return ans;
}

double myPow2(double x, int n) {
    if (x == 0) return 0.0;
    if (n == 0) return 1.0;

    bool isNegative = (n < 0) ? true : false;
    n = abs(n);

    double ans = 1;
    while (n > 0) {
        if (n & 1) 
            ans *= x;
        
        x *= x;
        n /= 2;
    }
    
    return (isNegative) ? 1.0 / ans : ans;
}

// *Recursive Implementation

// helper method: calculates power considering n is +ve
// it uses `n` as long long for the reason that if initially n == INT_MIN, then its absolute value is outside int range.
double powerHelper(double x, long long n) {
    if (n == 0)
        return 1;
    
    if (n % 2 == 0) 
        return powerHelper(x * x, n / 2);
    
    return x * powerHelper(x * x, n / 2);

    /*
    double half = powerHelper(x, n / 2);
    
    if (n % 2 == 0) 
        return half * half;
    
    return x * half * half;
    */
}

double myPowRecursive(double x, int n) {
    if (x == 0) return 0;
    
    // if n == INT_MIN, for that case, taking abs(n) will be outside int limits, so we store its absolute value in long long
    long long N = n;

    if (N < 0) {
        x = 1.0 / x;
        N = -N;
    }

    return powerHelper(x, N);
}

int main() {
    return 0;
}