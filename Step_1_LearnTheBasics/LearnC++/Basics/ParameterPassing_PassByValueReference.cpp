#include <iostream>
using namespace std;

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

Pass by Reference can be done through two ways
1. Pointers: 
    → Pointers are used to directly access and modify the passed arguments.
    → Pointers are created as int *ptr = &var;
    → So, instead of passing the variables as arguments, we pass their memory addresses.
    → The function parameters contains pointers to accept the memory address being passed to them.
    → We can then directly access & modify the variables' values with the help of dereferencing operator (*)
2. Reference variables:
    → Instead of using pointers to access the variables directly, we can use references & reference variables.
    → Reference variables are created as int &ref = var;
    → So, we use reference variables as the function parameters and pass the variable as arguments.
    → The variables' values can be accessed with the help of reference variable names (ref).

The use of reference variables for pass by reference is much better as-
    → we don't need to pass memory addresses as arguments.
    → no need to use dereferencing operator each time to access the values (can be directly used by reference variable names)
    → no separate memory will be created for refernce variables inside of the function.
*/

// Pass by Value
void swap(int x, int y) {
    int temp = x;
    x = y;
    y = temp;
}

// Pass by Reference -- through pointers
void swapPointers(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Pass by Reference -- through reference variables
void swapReferences(int &x, int &y) {
    int temp = x;
    x = y;
    y = temp;
}

// Arrays and their behaviour
void displayArray(int arr[], int len) {
    for(int i = 0; i < len; i++)
        cout << arr[i] << " ";
    cout << '\n';
}
// pass-by-pointers (arrays decay to pointers)
void doubleArray_ptr(int arr[], int len) {
    for(int i=0; i<len; i++)
        arr[i] *= 2;
}
// pass-by-reference
void doubleArray_ref(int (&arr)[5]) {
    for (int i = 0; i < 5; i++)
        arr[i] *= 2;
}

int main() {
    cout << "Fn Pass by Value & Reference \n\n";
    
    int x = 10, y = 20;
    // swapping the two variables
    swap(x, y);
    cout << "x : " << x << " _ y : " << y << '\n';
    // The values are not swapped, because the values are passed as copies so original variables remains unchanged
    
    // Pass by Reference -- through pointers and/or through reference variables
    swapPointers(&x, &y);       // Pass by Reference -- through pointers 
    cout << "x : " << x << " _ y : " << y << '\n';
    swapReferences(x, y);       // Pass by Reference -- through reference variables 
    cout << "x : " << x << " _ y : " << y << '\n';

    // Arrays are special cases. These are not passed by value. They decay to pointers (acts like pass by reference)
    /*
    When you pass an array to a function like this:
        void foo(int arr[]) { // ... }
    what actually happens is:
        void foo(int* arr) { // ... }
    Why?
    Because of array-to-pointer decay.
    • The array decays to a pointer to its first element
    • So the function receives a copy of the pointer
    • Not a reference to the array

    So why do changes affect the original array?
    Because:
    • The pointer points to the same memory
    • Modifying arr[i] modifies the original array’s memory
    This is called 'pass-by-pointer', not pass-by-reference.

    ✅ True pass by reference (no decay)
    void foo(int (&arr)[5])  // reference to entire array
    Now:
    • The array does not decay
    • Size is preserved
    • No pointer involved
    
    | Arrays are passed by pointer due to decay, not by reference.
    | C++ does not support pass-by-reference for arrays unless you explicitly use array references.
    */
    int arr[5] = {1,2,3,4,5};
    cout << "Original Array : ";
    displayArray(arr, 5);

    doubleArray_ptr(arr, 5);            // Array-to-pointer decay
    /*
    What’s happening
    • arr → decays to int*
    • Function receives a copy of the pointer
    • Pointer points to original array memory
    • Elements get modified
    */
    displayArray(arr, 5);

    doubleArray_ref(arr);               // Arrays pass-by-reference
    /*
    What’s happening
    • arr is a reference to the entire array
    • No pointer involved
    • Size (5) is preserved
    • Cannot accidentally pass wrong-sized array
    */

    displayArray(arr, 5);

    // vectors are not like arrays in this regard. Vectors can be passed by value or reference just like variables. 

    return 0;
}