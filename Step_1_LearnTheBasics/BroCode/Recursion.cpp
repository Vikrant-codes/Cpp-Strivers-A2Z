#include <iostream>
using namespace std;

/*
Recursion: A Programming technique where a function invokes itself from within. 

advantages - less code & is cleaner, useful for sorting & searching algorithms
disadvantages - uses more memory, slower

>> Base Condition 
Base condition (or base case) in a recursive function is the condition where the function stops calling itself.
In simple words:
👉 it tells recursion “when to stop”.

What happens in recursion
A recursive function has two parts:
- Base condition – stopping condition
- Recursive call – function calls itself with a smaller/simpler input

>> Why base condition is important
1. Prevents infinite recursion
Without a base condition, the recursive function would keep calling itself forever → stack overflow → program crashes.

2. Defines the smallest solvable problem
Recursion works by breaking a problem into smaller subproblems.
The base condition defines the smallest version that can be solved directly.
Example:
- Factorial of 0 is known → 1
- Fibonacci of 0 or 1 is known

3. Allows recursion to return results
Once the base case is reached:
- Function starts returning values
- Call stack unwinds
- Final answer is built step-by-step
Without base case → no return → no answer.

----------------------------------------------
Base condition = stopping point
Mandatory in every recursive function
Without it → infinite calls → stack overflow
----------------------------------------------

>> What is stack overflow in infinite recursion?
A stack overflow happens when the program uses more stack memory than allowed, 
usually because a function keeps calling itself without stopping.

First: what is the call stack?
- Every time a function is called, a stack frame is created
- This frame stores:
    - function parameters
    - local variables
    - return address
- These frames are stored in stack memory
When a function finishes, its frame is popped from the stack.

What goes wrong in infinite recursion?
    void f() {
        f();   // no base condition
    }
What happens step-by-step:
1. f() is called → stack frame created
2. Inside f(), it calls f() again → another frame
3. This keeps repeating…
4. No function ever returns → no frame is removed

So the stack keeps growing:
f()
f()
f()
f()
f()
...

Why does it crash?
- Stack memory is limited (a few MB usually)
- Infinite recursion keeps pushing stack frames
- Eventually:
    - stack memory fills up
    - OS detects overflow
    - program crashes → Stack Overflow

Typical error messages -> C/C++: Segmentation fault / Stack overflow

----------------------------------------------
Infinite recursion = no base condition
No base condition = no return
No return = stack keeps growing
Stack grows beyond limit → stack overflow
----------------------------------------------
*/

int factorialIterative(int n) {
    if (n == 0 || n == 1) return 1;
    int fact = 1;
    for (int i = 2; i <= n; i++) 
        fact *= i;
    return fact;
}

int factorialRecursive(int n) {
    if (n == 0 || n == 1) return 1;
    return n * factorialRecursive(n - 1);
}

void infiniteRecursion() {
    cout << "Hello World \n";
    infiniteRecursion();

    // no base condition
}

int main() {
    int n = 7;
    
    int f1 = factorialIterative(n);
    int f2 = factorialRecursive(n);

    cout << f1 << " - " << f2;

    // infiniteRecursion();

    return 0;
}