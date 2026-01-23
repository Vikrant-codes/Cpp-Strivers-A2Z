#include <iostream>
using namespace std;

int main() {
    /*
    <-- Array-to-pointer Decay --> 

    In C/C++, the name of an array (arr) does NOT represent the whole array as a value.
    Instead:
    • arr automatically converts (decays) to a pointer to its first element
    • So arr becomes equivalent to &arr[0]
    Thus, the array name references to the memory location of its first element.
    | the array name acts like a 'constant pointer' (its value can't be changed) which points to its 1st element.
    | so, array name points to its 1st element and we can't change this reference like we can re-initialize pointers.

    This behavior is called: " Array-to-pointer decay "
    👉 Definition: When an array name is used in an expression, it decays into a pointer to its first element.

    Formally: arr → int*, &arr[0] → int*

    Important clarification
    • arr is not a pointer variable
    • But in most expressions, it behaves like constant pointer which can't be re-assigned.

    We can access the memory addresses of individual elements using address-of operator ( &arr[i] ).
    */

    int arr[] = {1, 2, 3, 4, 5};
    cout << "Address of array --> &arr : " << &arr << " _ arr : " << arr << " _ &arr[0] : " << &arr[0] << "\n\n";
    
    for (int& x : arr) {
        // the &x in statement &x : arr is for reference variables, and to print the address we are accessing that using &x
        cout << "Element : " << x << " _ Address : " << &x << '\n';
    }
    // Integers are of 4 bytes, so integer array elements are stored in contiguous memory blocks of size 4 bytes

    /*
    <-- Pointer Arithmetic -->
    We can perform some limited arithmetic operations on pointers like :
    • ++ : Increments the pointer, the pointer will then point to the next memory block
    • -- : Decrements the pointer, the pointer will then point to the pevious memory block
    • + / += : adding an 'integer' to a pointer will increment the pointer to the specified no. of blocks
    • - / -= : subtracting an 'integer' from a pointer will decrement the pointer to the specified no. of blocks
    
    These operation doesn't make sense for normal pointers as incrementing/decrementing them will then make them 
    point to memory location which are worthless to us (as those locations would be holding garbage values).
    But we can use these operations on arrays, as arrays are like a collection of multiple variables so 
    we can access the next/previous array elements through pointer arithmetic.
    */
    cout << "\n<-- Pointer Arithmetic --> \n\n";

    int a[] = {10, 20, 30, 40, 50};
    int *ptr = a;
    for (int i = 0; i < 5; i++) {
        cout << ptr << " __ Data : " << *ptr << '\n';
        ptr += 1;
    }
    // when we are doing ptr += 1, it is actually moving 4 locations ahead (because integer arrays having 4 byte blocks)

    // arr[i] is equivalent to *(ptr + i) .... this is how compiler breaks down the array[i] syntax
    // Accessing ith element through pointer to an array and array_name_pointer
    ptr = a;
    for (int i = 0; i < 5; i++) {
        cout << "a[" << i << "] = " << *(ptr + i) << " _ a + " << i << " = " << *(a + i) << '\n'; 
    }

    /*
    Addition / Subtraction of two pointers
    • ptr1 + ptr2 doesn't make any sense as the two sum of two addresses is not meaningful.
    Thus, addition operation is invalid and gives error: "invalid operands of types 'int*' and 'int*' to binary 'operator+' "
    • ptr1 - ptr2 ?
    This operation might make sense for arrays,
    Assume two pointers ptr1 = arr + 0 (pointing to 1st element)
    ptr2 = arr + 4 (pointing to 4th element)

    Now, ptr2 - ptr1 = (arr + 4) - (arr + 0) = 4, this is the difference between the indices of the two locations
    */
    int *ptr1 = a;
    int *ptr2 = a+4;
    // cout << "ptr1 + ptr2 : " << ptr1 + ptr2 << '\n';         // Error
    cout << "ptr2 - ptr1 = " << ptr2 << " - " << ptr1 << " = " << ptr2 - ptr1 << '\n';
    cout << "ptr1 - ptr2 = " << ptr1 << " - " << ptr2 << " = " << ptr1 - ptr2 << '\n';

    return 0;
}