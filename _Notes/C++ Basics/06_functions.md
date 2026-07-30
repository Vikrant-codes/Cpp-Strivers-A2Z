# Functions in C++

A function is a reusable block of code that performs a specific task.

## Basic Function Syntax

```cpp
#include <iostream>
using namespace std;

int add(int a, int b) {   // return type, name, parameters
    return a + b;
}

int main() {
    int result = add(5, 3);  // function call with arguments
    cout << result << endl;  // 8
    return 0;
}
```

## Function Declaration vs Definition

For larger programs, declare (prototype) before `main()` and define after.

```cpp
#include <iostream>
using namespace std;

int add(int a, int b);   // declaration/prototype

int main() {
    cout << add(2, 3) << endl;  // 5
    return 0;
}

int add(int a, int b) {  // definition
    return a + b;
}
```

## void functions (no return value)

```cpp
void greet(string name) {
    cout << "Hello, " << name << "!" << endl;
}

int main() {
    greet("Vikrant");   // Hello, Vikrant!
    return 0;
}
```

## Default Arguments

```cpp
void printMessage(string msg = "Default message") {
    cout << msg << endl;
}

int main() {
    printMessage();               // Default message
    printMessage("Custom text");  // Custom text
    return 0;
}
```

## Function Overloading

Multiple functions with the same name but different parameter lists.

```cpp
int add(int a, int b) { return a + b; }
double add(double a, double b) { return a + b; }
int add(int a, int b, int c) { return a + b + c; }

int main() {
    cout << add(2, 3) << endl;        // calls int version -> 5
    cout << add(2.5, 3.5) << endl;    // calls double version -> 6.0
    cout << add(1, 2, 3) << endl;     // calls 3-param version -> 6
    return 0;
}
```

## Pass by Value

A **copy** of the argument is passed. Changes inside the function do NOT affect the original variable.

```cpp
void modify(int x) {
    x = 100;   // only changes the local copy
}

int main() {
    int a = 5;
    modify(a);
    cout << a << endl;  // 5 (unchanged)
    return 0;
}
```

## Pass by Reference

The function receives a **reference** (alias) to the original variable using `&`. Changes inside the function DO affect the original.

```cpp
void modify(int &x) {
    x = 100;   // changes the original variable
}

int main() {
    int a = 5;
    modify(a);
    cout << a << endl;  // 100 (changed)
    return 0;
}
```

## Classic Example: swap() using Pass by Reference

```cpp
#include <iostream>
using namespace std;

void swapByReference(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void swapByValue(int a, int b) {  // won't actually swap caller's variables
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int x = 10, y = 20;

    swapByValue(x, y);
    cout << "After swapByValue: x=" << x << " y=" << y << endl;
    // x=10 y=20 -> NO CHANGE, because only copies were swapped

    swapByReference(x, y);
    cout << "After swapByReference: x=" << x << " y=" << y << endl;
    // x=20 y=10 -> actually swapped
    return 0;
}
```

C++ also has `std::swap(x, y)` built-in (`<algorithm>` or `<utility>`) which does this internally using references.

## Pass by Pointer (alternative to reference)

```cpp
void swapByPointer(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 10, y = 20;
    swapByPointer(&x, &y);
    cout << x << " " << y << endl;  // 20 10
    return 0;
}
```

## Pass by Value vs Reference vs Pointer — quick summary

| Method | Syntax | Original modified? | Notes |
|---|---|---|---|
| Value | `void f(int x)` | No | Copy made, safe but wastes memory for large objects |
| Reference | `void f(int &x)` | Yes | Cleaner syntax, no null checks needed |
| Pointer | `void f(int *x)` | Yes | More explicit, but needs `&` and `*`, can be null |

## Recursion

A function calling itself.

```cpp
int factorial(int n) {
    if (n <= 1) return 1;         // base case
    return n * factorial(n - 1);  // recursive case
}

int main() {
    cout << factorial(5) << endl;  // 120
    return 0;
}
```
