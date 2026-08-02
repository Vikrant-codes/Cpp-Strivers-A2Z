# Functions in C++

A function is a self-contained, reusable block of code designed to perform one specific task. Instead of writing the same logic repeatedly throughout a program, you write it once inside a function and simply call that function whenever you need it — which also makes programs far easier to read, test, and fix.

## Basic Function Syntax

```cpp
#include <iostream>
using namespace std;

int add(int a, int b) {
    return a + b;
}

int main() {
    int result = add(5, 3);
    cout << result << endl;
    return 0;
}
```

A function definition has four parts: a return type (`int`, telling us what kind of value comes back out of the function), a name (`add`), a parameter list (`int a, int b`, the inputs the function expects), and a body containing the actual logic. When `add(5, 3)` is called inside `main()`, execution jumps into the function, computes `a + b`, and the `return` statement sends that value — `8` — straight back to wherever the function was called from, where it gets stored in `result`.

## Function Declaration vs Definition

In small programs, a function is often defined once, before it's used. But in larger files, it's common to separate the function's declaration (a short preview of its signature) from its full definition (which can come later in the file, or even in a different file entirely).

```cpp
#include <iostream>
using namespace std;

int add(int a, int b);

int main() {
    cout << add(2, 3) << endl;
    return 0;
}

int add(int a, int b) {
    return a + b;
}
```

The line `int add(int a, int b);` before `main()` is called a function prototype — it tells the compiler "this function exists and looks like this," which allows `main()` to call `add` even though its full body only appears later in the file. Without this prototype, the compiler would complain that it has never heard of `add` by the time it reaches the call inside `main()`.

## void Functions

Not every function needs to send a value back. A function that only performs an action — like printing something — without returning any result is declared with the `void` return type.

```cpp
void greet(string name) {
    cout << "Hello, " << name << "!" << endl;
}

int main() {
    greet("Vikrant");
    return 0;
}
```

Calling `greet("Vikrant")` runs the function's body and prints the greeting, but there's no value to capture afterward — you can't write `int x = greet("Vikrant");`, since `void` means the function produces nothing to assign.

## Default Arguments

You can give a parameter a default value, which is used automatically whenever the caller doesn't explicitly supply one.

```cpp
void printMessage(string msg = "Default message") {
    cout << msg << endl;
}

int main() {
    printMessage();
    printMessage("Custom text");
    return 0;
}
```

The first call, `printMessage()`, doesn't pass anything, so `msg` falls back to `"Default message"`. The second call explicitly supplies `"Custom text"`, which overrides the default entirely. This is handy for functions that usually behave one way but occasionally need to be customized.

## Function Overloading

C++ allows multiple functions to share the same name, as long as their parameter lists differ — either in number or type of parameters. This is called overloading, and the compiler figures out which version to call based on the arguments you actually provide.

```cpp
int add(int a, int b) { return a + b; }
double add(double a, double b) { return a + b; }
int add(int a, int b, int c) { return a + b + c; }

int main() {
    cout << add(2, 3) << endl;
    cout << add(2.5, 3.5) << endl;
    cout << add(1, 2, 3) << endl;
    return 0;
}
```

Even though all three functions are named `add`, the compiler distinguishes between them by looking at what's passed in: `add(2, 3)` matches the two-`int` version and returns `5`; `add(2.5, 3.5)` matches the two-`double` version and returns `6.0`; and `add(1, 2, 3)` matches the three-parameter version, returning `6`. This lets you use one intuitive name for conceptually the same operation, even when the underlying implementation differs slightly by type or argument count.

## Pass by Value

By default, when you pass a variable into a function, C++ makes a completely separate copy of it for the function to work with. Any changes made to that copy inside the function have no effect whatsoever on the original variable back in the caller.

```cpp
void modify(int x) {
    x = 100;
}

int main() {
    int a = 5;
    modify(a);
    cout << a << endl;
    return 0;
}
```

This prints `5`, not `100`. Even though `modify` sets `x` to `100`, `x` is only a local copy that exists inside the function — once `modify` finishes running, that copy is discarded, and the original `a` in `main()` remains completely untouched.

## Pass by Reference

Sometimes you actually want a function to be able to modify the caller's original variable. For that, C++ provides reference parameters, marked with an `&` symbol. Rather than creating a copy, a reference parameter becomes another name — an alias — for the exact same variable the caller passed in.

```cpp
void modify(int &x) {
    x = 100;
}

int main() {
    int a = 5;
    modify(a);
    cout << a << endl;
    return 0;
}
```

This time the output is `100`. Because `x` is a reference to `a` rather than a separate copy, assigning `100` to `x` is really assigning `100` directly to `a` itself.

## Classic Example: swap() using Pass by Reference

A textbook demonstration of why pass-by-reference matters is a function that swaps the values of two variables.

```cpp
#include <iostream>
using namespace std;

void swapByValue(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int x = 10, y = 20;
    swapByValue(x, y);
    cout << "After swapByValue: x=" << x << " y=" << y << endl;
    return 0;
}
```

This prints `x=10 y=20` — completely unchanged. Since `a` and `b` inside `swapByValue` are just local copies of `x` and `y`, swapping them only rearranges those copies; the moment the function returns, those copies vanish, leaving the original `x` and `y` exactly as they were.

Now compare that with a version using references:

```cpp
void swapByReference(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int x = 10, y = 20;
    swapByReference(x, y);
    cout << "After swapByReference: x=" << x << " y=" << y << endl;
    return 0;
}
```

This time the output is `x=20 y=10` — the values have genuinely swapped. Since `a` and `b` are references directly tied to `x` and `y`, any change made to `a` or `b` inside the function is really a change to `x` and `y` themselves. This is exactly why real-world swap implementations always use pass-by-reference (or pointers) rather than pass-by-value — a swap function that only rearranges local copies would be entirely pointless.

C++'s standard library also provides a ready-made `std::swap(x, y)` function (found in `<algorithm>` or `<utility>`), which does precisely this internally using references, so you rarely need to write your own version in real projects.

## Pass by Pointer

Pointers offer a third way to let a function affect the caller's original variable, using explicit address-of (`&`) and dereference (`*`) operators rather than the more implicit reference syntax.

```cpp
void swapByPointer(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 10, y = 20;
    swapByPointer(&x, &y);
    cout << x << " " << y << endl;
    return 0;
}
```

Here, `a` and `b` are pointers that store the memory addresses of `x` and `y`, passed in using `&x` and `&y`. Inside the function, `*a` and `*b` ("dereferencing" the pointers) access the actual values stored at those addresses, so modifying them modifies `x` and `y` directly. The output is `20 10`, just like the reference version — pointers and references achieve the same effect here, but pointers are more explicit about the fact that an address is being passed, and can also be set to `nullptr` to represent "no value," which references cannot.

## Comparing the Three Approaches

| Method | Syntax | Does it modify the original? | Notes |
|---|---|---|---|
| Value | `void f(int x)` | No | Safe, simple, but wastes memory when copying large objects |
| Reference | `void f(int &x)` | Yes | Clean syntax, always refers to a valid variable, no null checks needed |
| Pointer | `void f(int *x)` | Yes | More explicit, requires `&` and `*`, can be `nullptr` |

## Recursion

A function is said to be recursive when it calls itself, typically to break a problem down into smaller versions of the same problem.

```cpp
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int main() {
    cout << factorial(5) << endl;
    return 0;
}
```

This prints `120`. Every recursive function needs a "base case" — a condition simple enough to answer directly without further recursion — which here is `n <= 1`, returning `1`. Without a base case, the function would call itself forever until the program crashes from running out of memory. For every other value, the function expresses the problem in terms of a smaller version of itself: `factorial(5)` is `5 * factorial(4)`, which is `5 * (4 * factorial(3))`, and so on, unwinding back up once the base case is finally reached.
