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
A copy of the variable is passed to the function.
> Behavior: The function receives a copy of the argument. 
> Effect: Changes inside the function do not affect the original variable.

<-- Pass-by-Reference (Original is passed) -->
The function receives an alias of the original variable. 
It works on the original variable (passed as argument) through reference variables/pointers.
> Behavior: The function receives a reference to the argument.
> Effect: Changes inside the function do affect the original variable.
*/

/*
Pass by Reference can be done through two ways 
1. Pointers: 
    - Pointers are used to directly access and modify the passed arguments.
    - Pointers are created as int *ptr = &var;
    - So, instead of passing the variables as arguments, we pass their memory addresses.
    - The function parameters contains pointers to accept the memory address being passed to them.
    - We can then directly access & modify the variables' values with the help of dereferencing operator (*)
2. Reference variables:
    - Instead of using pointers to access the variables directly, we can use references & reference variables.
    - Reference variables are created as int &ref = var;
    - So, we use reference variables as the function parameters and pass the variable as arguments.
    - The variables' values can be accessed with the help of reference variable names (ref).

The use of reference variables for pass by reference is much better as-
    - we don't need to pass memory addresses as arguments.
    - no need to use dereferencing operator each time to access the values (can be directly used by reference variable names)
    - no separate memory will be created for refernce variables inside of the function.
*/

void swapPointers(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void swapReferences(int &x, int &y) {
    int temp = x;
    x = y;
    y = temp;
}

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

    // Pass by Value & References
    cout << "\nFn Pass by Value & Reference \n\n";
    int a = 5;
    passByValue(a);
    cout << "After passByValue: " << a << endl; // Original remains unchanged
    passByReference(a);
    cout << "After passByReference: " << a << endl; // Original value is changed

    // Pass by Reference -- through pointers and/or through reference variables
    int x = 10, y = 20;
    swapPointers(&x, &y);
    cout << "After swapping -- x : " << x << " _ y : " << y << '\n';
    swapReferences(x, y);
    cout << "After swapping -- x : " << x << " _ y : " << y << '\n';


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
