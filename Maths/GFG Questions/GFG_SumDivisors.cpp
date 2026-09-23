/*
GFG - Sum 1 to n Divisors : Easy

Given a positive integer n, The task is to find the value of Σi F(i) where i is from 1 to n and 
function F(i) is defined as the sum of all divisors of i.

Examples :-

Input: n = 4
Output: 15
Explanation:
F(1) = 1
F(2) = 1 + 2 = 3
F(3) = 1 + 3 = 4
F(4) = 1 + 2 + 4 = 7
So, F(1) + F(2) + F(3) + F(4)
    = 1 + 3 + 4 + 7 = 15

Input: n = 5
Output: 21
Explanation:
F(1) = 1
F(2) = 1 + 2 = 3
F(3) = 1 + 3 = 4
F(4) = 1 + 2 + 4 = 7
F(5) = 1 + 5 = 6
So,  F(1) + F(2) + F(3) + F(4) + F(5)
    = 1 + 3 + 4 + 7 + 6 = 21

Input: n = 1
Output: 1
Explanation:
F(1) = 1
So,  F(1) = 1 

Constraints :-
• 1 ≤ n ≤ 10^5
*/

#include<bits/stdc++.h>
using namespace std;

// Naive Approach : Time Complexity : O(n ∙ √n) __ Space Complexity : O(1)
/*
>> Approach
For each integer i in the range [1, n], 
we manually find the value of function F(i), i.e., the sum of all divisors of i.
We can then add this value to a result variable, which will store the sum of all F(i) values.

We can use a helper method to give us this value of F(i), which is `fun(x)` in the code implementation.
Now, the sum of all divisors of a number x can be found in O(x) or O(√x) depending on how we implement it.

The pure brute force approach would be to loop from 1 to x, 
and whenever we find a number that divides x, add it to sum.
This would take O(x) time to find the sum of all divisors of x.

We can optimize this to O(√x) because divisors always come in pairs.
For example, for x = 12, the divisor pairs are: (1, 12), (2, 6) and (3, 4).
So, whenever we find a divisor i, we can also directly get its corresponding divisor as x / i.
Therefore, we only need to loop from 1 to √x, and whenever i divides x, we add both i and x / i.
The only special case is when i == x / i, which happens when x is a perfect square. 
In that case, we add the divisor only once to avoid double-counting it.

>> Time Complexity
fun(x) takes O(√x) time, and since we call fun(i) for every i from 1 to n, the overall complexity is: `O(n ∙ √n)`

-> Space Complexity: O(1)
*/

// helper method: returns the sum of divisors of an integer `x`
long long fun(int x) {
    long long sum = 0;
    
    for (int i = 1; i * i <= x; i++) {
        if (x % i == 0) {
            sum += i;
            
            if (x / i != i) 
                sum += (x / i);
        }
    }
    
    return sum;
} 

long long sumOfDivisorsNaive(long long n) {
    long long sum = 0;
    
    for (int i = 1; i <= n; i++) {
        sum += fun(i);
    }
    
    return sum;
}

// Optimal Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
>> Intuition

Let's consider the case for n = 7

F(1) = 1
F(2) = 1 + 2 = 3
F(3) = 1 + 3 = 4
F(4) = 1 + 2 + 4 = 7
F(5) = 1 + 5 = 6
F(6) = 1 + 2 + 3 + 6 = 12
F(7) = 1 + 7 = 8

Result = F(1) + F(2) + F(3) + F(4) + F(5) + F(6) + F(7) = 1 + 3 + 4 + 7 + 6 + 12 + 8 = 41

Instead of looking at each F(i) individually, we can look at how each number contributes to the overall sum.
Notice that:
- 1 is a divisor of every number, so 1 appears in every F(i).
- 2 is a divisor of every 2nd number: 2, 4, 6, 8, ..., so 2 appears as a divisor for (n / 2) numbers
- 3 is a divisor of every 3rd number: 3, 6, 9, 12, ..., so 3 appears as a divisor for (n / 3) numbers
Similarly, a number i will be a divisor of all its multiples up to n.

Therefore, when we calculate the sum: F(1) + F(2) + F(3) + ∙∙∙ + F(n)
the number i will keep getting added to the resultant sum once for every multiple of i up to n.

For example, if n = 7:
- 1 appears in 10 divisor sums → contribution = 1 × 10
- 2 appears in 5 divisor sums (2,4,6,8,10) → contribution = 2 × 5
- 3 appears in 3 divisor sums (3,6,9) → contribution = 3 × 3
- 4 appears in 2 divisor sums (4,8) → contribution = 4 × 2
and so on.

So, for every number i, we only need to determine how many times i will occur in the overall sum.

The number of multiples of i up to n is: ⌊ n / i ⌋   (floor(n/i), this can be calculated as (int) (n / i) )
Therefore, i contributes `i × ⌊n / i​⌋` to the final answer.
We repeat this for every i from 1 to n and add all these contributions.

So the key observation is:
| Instead of finding the divisors of every number, 
| we find how many times each possible divisor i will occur across all F(1) ... F(n).

We just change the way we look at the problem.
Instead of asking: “For every number i from 1 to n, what are its divisors?”
we ask: “For every possible divisor i, how many numbers from 1 to n contain i as a divisor?”

Hence:

        i=1
Answer = ∑   ( i × ⌊ n / i ⌋ )
         n
*/
/*
a number i will have exactly (int)(n/i) multiples upto 'n',
so it will be a divisor of (int)(n/i) numbers upto n.

Thus while calculating sum of divisors the number `i` will be included (int)(n/i) times in the result.
Thus, contribution of i will be i * (int)(n/i)

Example:- consider n = 4
i = 1: Contribution of 1 = 1 * (int)(4/1) = 4
    (1 has 4 multiples till n, thus it will be a divisor of 4 numbers {1,2,3,4}, and will be added 4 times in result)
i = 2: Contribution of 2 = 2 * (int)(4/2) = 4
    (2 has 2 multiples {2, 4}, thus it will be added 2 times in result)
i = 3: Contribution of 3 = 3 * (int)(4/3) = 3
    (3 has only 1 multiple {3}, thus it will be added just once in result)
i = 4: Contribution of 4 = 4 * (int)(4/4) = 4
    (4 also has only 1 multiple {4}, thus it will be added just once in result)
Total sum = 4 + 4 + 3 + 4 = 15
*/
long long sumOfDivisors(long long n) {
    long long sum = 0;
    
    for (int i = 1; i <= n; i++)
        sum += i * (int) (n / i);
    
    return sum;
}

int main(){   
    return 0;
}