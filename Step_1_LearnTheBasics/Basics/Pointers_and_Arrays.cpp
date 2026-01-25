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
    // Accessing ith element through pointer to 0th element of arr and array_name_pointer
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


    /*
    <-- Pointer to an Array (Pointer to an entire array) -->
    When we initialize a pointer with the array name or 0th element address, it points to the 0th element of the array 
    and not the entire array.  
    Thus, when we increment it, it then points to the next element in the array.
    Pointer to entire Array means, 
    a pointer which will point to the entire array (it would still store the address of the 1st array element).
    This pointer, if incremented, would then point to some memory address after the array end (not the next element in array).

    Syntax to create pointer to entire array -> array_data_type (*ptr_name) [array_size]; 
    The two syntaxes 'array_data_type (*ptr_name) [array_size];' and 'array_data_type *ptr_name [array_size];' are different.
    The first syntax would create a pointer to an array of size 'array_size', 
    while the later one declares an array of pointers containing 'array_size' pointer elements.
    This happens because without the braces '()', compiler thinks 'array_data_type *' as pointer data type
    */
    int b[] = {2, 3, 5, 7, 11};
    int (*p1) [5];  // this will create a pointer to an array of size 5
    int *p2[5];     // this will create an array of pointers of size 5... 
    // because compiler interprets this syntax 'int*' as the 'integer pointer' data type of an array named p2 of size 5
    
    // p1 = b;      // this will give error 'error: cannot convert 'int [5]' to 'int (*)[5]' in assignment'
    // to assign pointer to an entire array, we need to use '&' operator to initailize it, else it would give error
    p1 = &b;
    cout << "\nPointer to an entire Array : " << p1 << '\n';
    cout << "Address of array b : " << &b << '\n';
    cout << "Pointer after incrementing : " << p1 + 1 << '\n';
    // if we consider the memory locations the pointer p1 & the incremented pointer (p1 + 1), 
    // they would have a difference equal to hexadecimal '14', this 14 corresponds to decimal number '20', 
    // since array has 5 integer elements, size of array = 5*4 = 20 bytes, thus after incrementing it moves to 20 bytes ahead

    // p2 = &b;    // 'error: incompatible types in assignment of 'int (*)[5]' to 'int* [5]'
    
    // De-referencing pointers to entire Arrays
    cout << "De-referenced value : " << *(p1) << "\n\n";              // will display array address
    // This happens because the pointer points to the entire array, so when de-referenced it returns the whole array itself
    // pointer is pointing to whole array i.e. *ptr = &arr,... so when de-referenced it returns *(&arr) = arr, 
    // This arr is the address of the array's 1st element

    // <-- Pointers & 2D Arrays (Multidimensional Arrays) -->

    // 2D arrays are stored in row-major form inside memory, rows are stored one after another
    int arr2D[3][4] = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12} };
    
    // For 2D arrays, the array_name is a pointer to the 1st row (as it is the 1st element in that array).
    // if we increment it, we can get the next array rows.
    cout << "arr2D : " << arr2D << '\n';
    cout << "&arr2D[0][0] = " << &arr2D[0][0] << " _ &arr2D[0][1] = " << &arr2D[0][1] << " _ &arr2D[1][0] = " << &arr2D[1][0] << '\n';
    cout << "arr2D + 1 : " << arr2D + 1 << '\n';
    // arr2D + 1 is pointing '10' hexadecimal places ahead to arr2D
    // 10 hexadecimal places = 16 in decimal = (4 elements in each row * 4 bytes of int)) 

    cout << "De-referencing 2d Array name : *arr2D = " << *arr2D << '\n';   
    // If we try to de-reference it, it will still return memory location (since it is a pointer to a 1D array)

    // 2D Array names acts as row pointers (pointer to 1D arrays)

    // <-- Row Pointers in 2D Array -->
    int (*rowPtr)[4] = arr2D;
    for (int i = 0; i < 3; i++) {
        cout << "Row pointer to row " << i << " : " << rowPtr << '\n';
        rowPtr++;
    }
    

    return 0;
}