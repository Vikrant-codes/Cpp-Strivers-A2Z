// Get the nth term of Fibonacci Series using Recursion
// Fibonacci Series: 0 1 1 2 3 5 8 13 21 34 55
// 0 is often considered as the 0th term of fibonacci series

// Leetcode - 509. Fibonacci Number
/*
Leetcode - 509. Fibonacci Number : Easy

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

#include <bits/stdc++.h>
using namespace std;

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
- Exact asymptotic: Θ(φⁿ)
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

int fibonacci(int n) {
    if (n <= 1)
        return n;

    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    cout << "Fibonacci Series: ";

    for (int i = 0; i <= 20; i++)
        cout << fibonacci(i) << " ";

    return 0;    
}