// GFG - GCD of two numbers : Basic

/*
>> Greatest Common Divisor (GCD) or Highest Common Factor (HCF)
The Greatest Common Divisor (GCD), also known as the Highest Common Factor (HCF), of two numbers 
is the largest positive integer that divides both numbers evenly without leaving a remainder.

So, for two numbers a & b, the GCD of a and b is the largest integer x such that x divides both a & b.
*/

/*
GFG - GCD of two numbers : Basic

Given two positive integers a and b, find GCD of a and b.
Note: Don't use the inbuilt gcd function

Examples :-

Input: a = 20, b = 28 __ Output: 4
Input: a = 60, b = 36 __ Output: 12

Constraints:- 1 ≤ a, b ≤ 10^9
*/

#include <iostream>
using namespace std;

// Naive Approach : Time Complexity : O(min(a, b)) __ Space Complexity : O(1)
/*
For each number in range 1 to min(a, b), 
we find the number which is a common divisor to both a & b. 
Keep track of the maximum such common divisor found.
We go only till min(a, b) since assume a = 9, b = 12, 
then checking for numbers greater than 10 would make no sense as they will obviously not divide the smaller number 9.
*/ 
int gcdNaive(int a, int b) {
    int gcd = 1;
    int m = min(a, b);
    
    for (int i = 1; i <= m; i++) 
        if ( (a % i == 0) && (b % i == 0) )
            gcd = i;
            
    return gcd;
}

/*
Since we need the greatest common factor 
instead of checking from 1 to min(a, b) and storing the common divisor as gcd each time
we can directly check from min(a, b) to 1 in decreasing order, 
in this way, the first common factor found will be the maximum (greatest).
So, we won't have to store / track the maximum common divisor and return only the first found divisor.
But, in worst cases, this solution will also run for O(min(a, b)) for ex- a = 11, b = 17
*/
int gcdNaive2(int a, int b) {
    int m = min(a, b);
        
    for (int i = m; i >= 1; i--) 
        if ( (a % i == 0) && (b % i == 0) )
            return i;
            
    return -1;
}

// Euclidean Algorithm & Subtraction Property of GCD
/*
The Euclidean Algorithm is an ancient, highly efficient method used to compute the Greatest Common Divisor (GCD) of two integers.
Mathematically :- 
|       gcd(a, b) = gcd(b, a (mod b)),      where a > b

>> Step 1: The fundamental idea (Subtraction Property)
Suppose a>b. Then, if a number divides both a and b, then it also divides a−b.
For example:
18 and 12 have common divisors 1,2,3,6.
18 − 12 = 6.
12 and 6 also have common divisors 1,2,3,6.
So:
    | gcd(a,b) = gcd(a−b,b)
This means we can keep replacing the larger number by the difference:
    gcd(48, 18) 
    = gcd(30, 18)
    = gcd(12, 18)
    = gcd(12, 6)
    = gcd(6, 6)
    = 6
This is the original Euclidean idea.

>> Step 2: The inefficiency
Notice what happened from 48 to 12: 48 -> 30 -> 12. 
We subtracted 18 twice.
What if instead of doing many subtractions one by one, we directly ask:
    How much is left after removing as many 18s as possible from 48?
That's exactly: 48 % 18 = 12
So: gcd(48,18) = gcd(30,18) = gcd(12,18)
can be compressed into: gcd(48,18) = gcd(48 % 18, 18) = gcd(12,18)

>> Step 3: Euclidean Algorithm
The modulo version is therefore just a shortcut for repeated subtraction: gcd(a,b) = gcd(a mod b, b)
or equivalently gcd(a,b) = gcd(b, a mod b)

This modulus is equivalent to performing multiple subtraction-property steps at once.

Subtraction Property
    ↓
Repeated Subtraction Algorithm
    ↓ (optimize many subtractions into one modulo)
Euclidean Algorithm

Steps :-
1) Given two numbers a and b (a > b), compute a mod b
2) Replace a with b and b with a mod b
3) Repeat until b becomes zero at which a is the gcd
Ex - gcd(12,9) = gcd(9, 12%9) = gcd(9,3) = gcd(3, 9%3) = gcd(3,0) = 3
*/

// Euclidean Algorithm : Time Complexity : O( log Φ (min(a, b)) ), base of log is Φ (which is golden ratio), Φ ≈ 1.618
int gcd(int a, int b) {
    while (a > 0 && b > 0) {
        if (a > b) 
            a = a % b;          // equivalent to doing a = a - b multiple times till a > b
        else 
            b = b % a;          // equivalent to doing b = b - a multiple times till b > a
    }
    
    if (a == 0) return b;
    return a;
}

// my implementation
int myGCD(int a, int b) {
    int rem = b % a;
    while (rem != 0) {
        b = a;
        a = rem;
        rem = b % a;
    }
    return a;
}

// Code using Subtraction property of GCD (Not as efficient as the above approach)
int gcdSubtraction(int a, int b) {
    while (a > 0 && b > 0) {
        if (a > b)
            a = a - b;
        else 
            b = b - a;
    }
    
    if (a == 0) return b;
    return a;
}

int main() {
    return 0;
}