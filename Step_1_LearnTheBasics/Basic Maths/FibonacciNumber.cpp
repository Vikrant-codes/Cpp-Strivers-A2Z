#include <bits/stdc++.h>
using namespace std;

// Leetcode - 509. Fibonacci Number : Easy
/*
The Fibonacci numbers, commonly denoted F(n) form a sequence, called the Fibonacci sequence, 
such that each number is the sum of the two preceding ones, starting from 0 and 1. 
That is,
F(0) = 0, F(1) = 1
F(n) = F(n - 1) + F(n - 2), for n > 1.

Given n, calculate F(n). 

Examples :-

Input: n = 2 __ Output: 1
Explanation: F(2) = F(1) + F(0) = 1 + 0 = 1.

Input: n = 3 __ Output: 2
Explanation: F(3) = F(2) + F(1) = 1 + 1 = 2.

Input: n = 4 __ Output: 3
Explanation: F(4) = F(3) + F(2) = 2 + 1 = 3.

Constraints :-
• 0 <= n <= 30
*/

// Recursive Implementation: Time Complexity : O(2ⁿ) __ Space Complexity : O(n)
/*
>> Time Complexity

Step 1: Observe the recursion

For each call fibonacci(n), two more recursive calls are made:
    f(n)
    ├── f(n-1)
    └── f(n-2)

But notice something important: f(n-2) is calculated multiple times.

Example for n = 5:

    f(5)
    ├── f(4)
    │   ├── f(3)
    │   │   ├── f(2)
    │   │   └── f(1)
    │   └── f(2)
    └── f(3)
        ├── f(2)
        └── f(1)

Here,
    f(3) is computed twice
    f(2) is computed three times
    f(1) is computed five times
    
    Lots of repeated work happens.

Step 2: Write the recurrence

Ignoring the constant work, T(n) = T(n-1) + T(n-2) + O(1)
This recurrence grows almost exactly like the Fibonacci numbers themselves.
The solution is: T(n) = Θ(φⁿ), where ϕ is the golden ratio, i.e., ϕ = ((1 + √5) / 2) ≈ 1.618
Since, (1.618)ⁿ < 2ⁿ
many books simply write O(2ⁿ) because it's easier to remember.

More precise answer
- Exact asymptotic: O(φⁿ)
- Simpler interview answer: O(2ⁿ)

>> Space Complexity

The recursion is depth-first.
Although many recursive calls are made overall, only one path exists on the call stack at a time.
For example,
    f(5)
    |
    f(4)
    |
    f(3)
    |
    f(2)
    |
    f(1)
Maximum depth = n
So the call stack stores at most n function calls.
Therefore O(n)

-> Why isn't space O(2ⁿ)?
A common confusion is:
"If there are 2ⁿ function calls, shouldn't stack also be 2ⁿ?"
No.

The calls are not active simultaneously.
Think of DFS in a tree:
    A
    ├── B
    │   ├── D
    │   └── E
    └── C

The program finishes exploring B completely before starting C.
At any instant, the stack contains only one root-to-leaf path.
Maximum stack:
    A
    B
    D
not
    A
    B
    D
    E
    C
The same happens here.

>> Final Complexity
| Complexity | Value                             |
| ---------- | --------------------------------- |
| Time       | Θ(φⁿ) (commonly written as O(2ⁿ)) |
| Space      | O(n)                              |

This recursive solution has exponential time complexity because it recomputes the same Fibonacci values many times. 
The recurrence is T(n) = T(n-1) + T(n-2) + O(1), which solves to Θ(φⁿ) (approximately O(1.618ⁿ)). 
It's commonly simplified to O(2ⁿ). 
The space complexity is O(n) due to the maximum recursion depth.
*/
int fib(int n) {
    if (n <= 1)
        return n;

    return fib(n-1) + fib(n-2);
}

// Iterative Implementation: Time Complexity : O(n) __ Space Complexity : O(1)
/*
In fibonacci sequence, we know that the ith term i.e., F(i), is equal to the sum of previous two terms.

i.e., F(i) = F(i-1) + F(i-2)

Now, if we can track the last two terms, then we can easily build the current term iteratively and do this to get `nth term`.
So, we use two variable `last` and `slast` which give us the value of the previous two terms.
We can then get the value of current term by adding these two previous value, i.e., curr = last + slast.
Before moving to next iteration, we update last & slast to give them the new previous two values.

When loop ends, the `last` variable stores the value of `nth term` (so does the `curr` or `temp` variable) 
*/
int fibIterative(int n) {
    if (n <= 1)
        return n;

    int last = 1, slast = 0;
    
    for (int i = 2; i <= n; i++) {
        int temp = last + slast;
    
        slast = last;
        last = temp;
    }

    return last;
}

// GFG - First n Fibonacci using Recursion
/*
GFG - First n Fibonacci using Recursion : Basic

Given a number n, return an array containing the first n Fibonacci numbers.

The first two Fibonacci numbers are 0 and 1. 
Each subsequent Fibonacci number is obtained by adding the previous two numbers.

Examples :-

Input: n = 5
Output: [0, 1, 1, 2, 3]
Explanation: The first 5 Fibonacci numbers are 0, 1, 1, 2, 3.

Input: n = 7
Output: [0, 1, 1, 2, 3, 5, 8]
Explanation: The first 7 Fibonacci numbers are 0, 1, 1, 2, 3, 5, 8.

Input: n = 2
Output: [0, 1]
Explanation: The first 2 Fibonacci numbers are 0 and 1.

Constraints :-
• 1 ≤ n ≤ 30
*/

// Recursive Implementation: Time Complexity : O(n ∙ 2ⁿ) __ Space Complexity : O(n)
/*
We want the first `n` fibonacci numbers.
So, for i in range [0, n-1], we need the ith fibonacci term in each iteration.
We can use the recursive method to get the ith fibonacci number each time.
This recursive method takes approximate O(2ⁿ) time to give the nth fibonacci number.
So, over all iterations, the total work done can be expressed by the upper bound: O(n ∙ 2ⁿ)

The recursive method also takes O(n) space for recursive calls, which amounts to the O(n) extra space.
The result vector also takes O(n) space, but is generally not considered as extra space.
*/

vector<int> fibonacciNumbers(int n) {
    vector<int> seq(n);
    
    for (int i = 0; i < n; i++) 
        seq[i] = fib(i);
    
    return seq;
}

// Iterative Implementation (much faster than Recursive) : O(n) __ Space Complexity : O(1)
/*
We know that the first two terms are [0, 1]
we can then build the next terms by adding the last two terms.

So, for each index i in range [2, n-1], we can calculate fibonacci[i] as fibonacci[i-1] + fibonacci[i-2].
No need to explicitly track the previous two values using variables, 
since the output vector itself can be used to get the previous two element values.
*/
vector<int> fibonacciNumbersIterative(int n) {
    vector<int> fib(n);
    
    if (n >= 1)
        fib[0] = 0;
        
    if (n >= 2) 
        fib[1] = 1;
    
    for (int i = 2; i < n; i++)
        fib[i] = fib[i-1] + fib[i-2];
    
    return fib;
}

int main() {
    return 0;
}