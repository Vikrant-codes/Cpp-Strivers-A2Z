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
    return 2*3*5*7;
}
// Parameterized Void (Takes Something, Returns Nothing)
void printSum(int a, int b) {
    cout << "Sum: " << a + b << endl;
}
// Parameterized Non-Void (Takes Something, Returns Something)
int getMax(int a, int b) {
    return a>=b ? a : b;
}

// Parameter Passing
/*
<-- Pass-by-Value (Copy is passed) -->
> Behavior: The function receives a copy of the argument.
> Effect: Changes inside the function do not affect the original variable.

<-- Pass-by-Reference (Original is passed) -->
> Behavior: The function receives a reference to the argument.
> Effect: Changes inside the function do affect the original variable.
*/

void passByValue(int x) {
    x = x * 2; // Modify the copy
    cout << "Inside passByValue: " << x << endl;
}

void passByReference(int& x) {
    x = x * 2; // Modify the original
    cout << "Inside passByReference: " << x << endl;
}

void displayArray(int arr[], int len) {
    for(int i = 0; i < len; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void modifyArray(int arr[], int len) {
    for(int i=0; i<len; i++) {
        arr[i] *= 2;
    }
    cout << "Inside modifyArray : ";
    displayArray(arr, len);
}

int main() {
    greet();
    int number = getNumber();
    cout << number << endl;
    printSum(2, 3);
    int max = getMax(2, 3);
    cout << max << endl;

    cout << "\nFn Pass by Value & Reference \n\n";
    int a = 5;
    passByValue(a);
    cout << "After passByValue: " << a << endl; // Original remains unchanged
    passByReference(a);
    cout << "After passByReference: " << a << endl; // Original value is changed

    // Arrays are special cases. These are not passed by value. They decay to pointers (acts like pass by reference)
    int arr[5] = {1,2,3,4,5};
    cout << "Before Modifying : ";
    displayArray(arr, 5);
    modifyArray(arr, 5);
    cout << "After modifyArray : ";
    displayArray(arr, 5);

    // vectors are not like arrays in this regard. Vectors can be passed by value or reference just like variables. 

    return 0;
}
