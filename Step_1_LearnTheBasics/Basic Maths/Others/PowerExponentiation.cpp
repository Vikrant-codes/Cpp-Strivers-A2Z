// Implement the pow method (pow(x, n))
/*
pow(x, n) :- It is a pre-defined method which returns x ^ n. 
Its return type is double and can work with double x & n.
*/

#include<bits/stdc++.h>
using namespace std;

// For the ease of understanding, let's first try to implement/code the pow function considering x & n are +ve integers

// Naive Approach :- Time Complexity : O(n) __ Space Complexity : O(1)
/*
| x raised to the power n => x ^ n = x * x * x ... n times
So, run a loop n times and multiply for x each iteration to get x ^ n.
Initially keep ans = 1, and for each iteration do ans = ans * x. 
The loop will run n times and when it ends ans will be storing x ^ n. 
*/
int myPowNaive(int x, int n) {
    int ans = 1;
    for (int i = 1; i <= n; i++)
        ans *= x;
    return ans;
}

// Optimal Approach :- Time Complexity : O(log n) __ Space Complexity : O(1)
/*
We want to compute x^n
The naive way is : x * x * x * x * ... (n times)
which takes O(n) multiplications.
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

// What if x is a double value and n can be negative as well ?
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

int main() {
    cout << myPow(5, 2) << endl;
    cout << myPow(5, -2) << endl;
    cout << myPow(1.1, 2) << endl;

    return 0;
}