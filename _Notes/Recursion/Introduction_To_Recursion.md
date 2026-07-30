# Recursion

| When a function calls itself, it is known as recursion, and the function itself is called a recursive function.

Example:
````````````````````````````````````````````
void fun(int n) {
    if (n == 0)         // Base Condition
        return;

    cout << n << '\n';
    fun(n-1);           // Recursive call
}
````````````````````````````````````````````
- The function 'fun()' is a recursive function as it is invoking (calling) itself inside its body.
- Recursive Call: The recursive call is the statement where the function calls itself.

## Call Stack
- Every function call is stored in memory called the call stack.
- It is the internal memory structure used by systems to track each active function call.
Example: fun(3)
    Stack grows like this
````````````````````````````````````````````````````````
|        |            |        |            | fun(1) |
|        |     =>     | fun(2) |     =>     | fun(2) |     
| fun(3) |            | fun(3) |            | fun(3) |
----------            ----------            ----------
````````````````````````````````````````````````````````

## Base Condition 
- The base condition is the condition that tells the recursive function when to stop calling itself.
- Without a base condition, the function would keep calling itself forever.
- In the above example, the condition (n == 0) is the base condition which stops the recurion when n becomes zero.
 
## Infinite Recursion
- If there is no base case, or the base case is never reached, recursion never stops.
- Such recurion is called Infinite Recursion

Example:
````````````````````````````````
void infiniteFun() {
    cout << "Hello World\n";
    
    infiniteFun();
}
````````````````````````````````
Output: 
````````````````````````````````
Hello World
Hello World
Hello World
Hello World
...
````````````````````````````````
- This fun will just keep calling itself infinitely since there is no stopping condition (base condition).
- Eventually when it keeps calling itself, it will give "Stack Overflow Error"

Example where base condition is present but never reached
````````````````````````````````
void infiniteFun2(int n) {
    if (n == 0) 
        return;

    cout << "Hello World\n";
    infiniteFun2(n + 1);
}
````````````````````````````````
Assume, we are calling this function inside main as : infinteFun2(1) <br>
Since, n is given a initial value of 1 (which is greater than zero), and in each recursive call, n is incremented by 1, <br>
so the base condition will never execute (as n will never become 0) and this will also act as infinte recursion. <br>
Although, this function's base condition will work if we call the function in such way like : infinteFun2(-10) <br>
 
## Stack Overflow 
The error that occurs if a base case is missing, causing infinite loops that exhaust system memory.
 
## Head Recursion
- A recursive function where the recursive call occurs before any processing.
Example:
``````````````````````````
void print(int n) {
    if (n == 0)
        return;

    print(n - 1);

    cout << n << " ";
}
``````````````````````````
Execution:
    Assume main calls print(3)

    print(3) checks Base conidtion (False)  calls print(2)
    print(2) checks Base conidtion (False)  calls print(1)
    print(1) checks Base conidtion (False)  calls print(0)
    print(0) checks Base condition (True)  execution of print(0) is stopped, return

    Now, print(1) gets control again, it prints 1, execution of print(1) finishes
    print(2) gets control, it prints 2, execution of print(2) finishes
    print(3) gets control, it prints 3, execution of print(3) finishes

    Finally, the control gets to the actual caller (main method)

    Output: 1 2 3

Since, print statement "cout" is used after recurive call, output is ascending.
 
## Tail Recursion
- A recursive function where the recursive call is the last statement.
Example:
``````````````````````````
void print(int n) {
    if (n == 0)
        return;

    cout << n << " ";

    print(n - 1);
}
``````````````````````````
Suppose, main calls print(3) <br>
Output: 3 2 1

## Tree Recursion
- When the recursive function calls itself more than once.

Example: Recursive implementation of fibonacci implements tree recursion 
`````````````````````````````````````````````
int fibonacci(int n) {
    if (n == 0 || n == 1) 
        return n;
    
    return fibonacci(n-1) + fibonacci(n-2);
}
`````````````````````````````````````````````

## Linear Recursion
- Each recursive function calls itself only once.

Example:
``````````````````````````````
void fun(int n){
    if (n == 0) return;
    fun(n-1);
}
``````````````````````````````
 
## Direct Recursion
- The function calls itself directly.

Example: 
``````````````````````````
void fun() {
    cout << "Hii\n";
    fun();
}
``````````````````````````
- This is the most generally used form of recursion
 
## Indirect (Mutual) Recursion
- Two or more functions call each other.

Example:
``````````````````````````````
void A(int n);

void B(int n)
{
    if(n<=0)
        return;

    cout << n << " ";
    A(n-1);
}

void A(int n)
{
    if(n<=0)
        return;

    cout << n << " ";
    B(n-1);
}
``````````````````````````````
Calls: A(3) → B(2) → A(1) → B(0)
 
## Nested Recursion
- The recursive call appears inside another recursive call.

Example:
``````````````````````````````````
int fun(int n)
{
    if(n > 100)
        return n - 10;

    return fun(fun(n + 11));
}
``````````````````````````````````
| This is known as the McCarthy 91 function. 

++ Nested recursion is relatively rare in practical programming.
<br> 

# What is Recursion ?

- Recursion is a programming technique where a function calls itself directly or indirectly to solve a problem.
- Instead of solving the whole problem at once, the function solves a smaller part of the problem and 
  keeps doing this until it reaches a stopping point.
- A recursive function has two essential parts:
    1. Base condition (Base case) – stops recursion.
    2. Recursive call – calls itself with a smaller/simpler input.

Example (Factorial) => 5! = 5 × 4 × 3 × 2 × 1

Instead of writing loops, we can use recursion in this way:
````````````````````````````````````````````````````
int factorial(int n) {
    if (n == 1)      // Base condition
        return 1;

    return n * factorial(n - 1); // Recursive call
}
````````````````````````````````````````````````````
````````````````````````````````````````````````````
Execution
    factorial(5)
    = 5 * factorial(4)
          = 4 * factorial(3)
                = 3 * factorial(2)
                      = 2 * factorial(1)
                            = 1
````````````````````````````````````````````````````
 
## Summary

| Concept                         | Meaning                                                                |
| ------------------------------- | ---------------------------------------------------------------------- |
| **Recursion**                   | A function calls itself to solve a smaller version of the problem.     |
| **Base Condition**              | The stopping condition that prevents endless recursion.                |
| **Recursive Case**              | The self-call that reduces the problem size.                           |
| **Infinite Recursion**          | Recursion that never reaches the base case, leading to stack overflow. |
| **Call Stack**                  | Memory structure that stores active function calls.                    |
| **Head Recursion**              | Recursive call happens before any processing.                          |
| **Tail Recursion**              | Recursive call is the last operation in the function.                  |
| **Linear Recursion**            | One recursive call per function invocation.                            |
| **Tree Recursion**              | Multiple recursive calls from one invocation.                          |
| **Direct Recursion**            | A function directly calls itself.                                      |
| **Indirect (Mutual) Recursion** | Two or more functions recursively call one another.                    |
| **Nested Recursion**            | A recursive call is used as an argument to another recursive call.     |
| **Backtracking**                | Recursion combined with undoing choices after returning.               |
| **Recurrence Relation**         | A mathematical equation expressing a recursive solution.               |


## McCarthy 91 function

The McCarthy 91 function is a famous recursive function defined by computer scientist John McCarthy. 
It returns 91 for all integer inputs n ≤ 100 and n - 10 for inputs n > 100. 
Historically, it has served as a primary test case for formal verification and program correctness in computer science.

The function is defined mathematically as:
`````````````````````````````````````````````
            { n - 10        , if n > 100
    f(n) =  {
            { f(f(n + 11)), if n <= 100
`````````````````````````````````````````````

Code: The code for McCarthy 91 function uses Nested Recursion
````````````````````````````````
int f(int n)
{
    if(n > 100)
        return n - 10;

    return f(f(n + 11));
}
````````````````````````````````