#include <iostream>
using namespace std;

// Functions are set of code which perform something for you.
// Used to modularise code, increase readability snd reusability.

// <-- Categorization of Functions -->
/*
1. Based on Return Type
    Void Functions: No return value.
    Non-Void (Value-Returning) Functions: Return a value of a specific type.

2. Based on Parameters
    Parameterized Functions: Accept parameters.
    Non-Parameterized Functions: No parameters.

3. Based on Scope
    Global Functions: Declared outside any class or namespace, accessible globally.
    Member Functions: Defined inside a class.
    Friend Functions: Can access private and protected members of a class.

4. Based on Invocation
    Call by Value: Passes a copy of the argument.
    Call by Reference: Passes a reference, allowing modification of the original data.
    Call by Pointer: Passes memory addresses.

5. Based on Function Definition
    User-Defined Functions: Defined by the programmer.
    Built-In Functions: Provided by C++ libraries (e.g., sqrt() from <cmath>).

6. Based on Behavior
    Recursive Functions: Call themselves.
    Inline Functions: Suggested for compiler inlining using inline keyword.
    Overloaded Functions: Same name, different parameter lists.
    Virtual Functions: Support runtime polymorphism in inheritance.
    Lambda Functions: Anonymous functions defined using [].
*/

/*
Functions can be categorized as -->
1. Non-Parameterized Void     : takes nothing return nothing
2. Non-Parameterized Non-Void : takes nothing return something
3. Parameterized Void         : takes something return nothing
4. Parameterized Non-Void     : takes something return something
*/

// Non-Parameterized Void (Takes Nothing, Returns Nothing)
void greet() {
    cout << "Hello World !!" << endl;
}
// Non-Parameterized Non-Void (Takes Nothing, Returns Something)
int getNumber() {
    return 21;
}
// Parameterized Void (Takes Something, Returns Nothing)
void printSum(int a, int b) {
    cout << "Sum: " << a + b << endl;
}
// Parameterized Non-Void (Takes Something, Returns Something)
int getMax(int a, int b) {
    return a>=b ? a : b;
}

int main() {
    greet();

    int number = getNumber();
    cout << number << endl;
    
    printSum(2, 3);
    
    int m = getMax(2, 3);
    cout << m << endl;

    return 0;
}