#include <iostream>
using namespace std;

int main() {
    // <-- address-of operator (&) -->

    // address-of operator helps to get the memory address of a variable. Syntax -> &variable_name
    // memory address: a location in memory where data is stored.
    int n = 21;
    cout << "address of 'n' variable: " << &n << '\n';          // The address is displayed in hexadecimal format (Ox)

    // in case of arrays, the array name itself represents the memory address 
    // The array name references the memory address of its first element
    int arr[] = {1,2,3,4,5};
    cout << "address of 'arr' : " << &arr << '\n';
    cout << "address of 'arr' : " << arr << '\n';

    char ch = 'a';
    cout << "address of char variable ch : " << &ch << '\n';        // a
    // doing cout << &char_variable; prints the char value instead of its address. 
    // This is due to some internal functionality of cout method which displays the char value instead of its address
    cout << "address of char variable ch : " << (void *) &ch << '\n';        // this will print address
    // To display character address using cout, we have to typecase &ch to void * before displaying it.


    // <-- Pointers -->
    // A pointer is a variable that holds the address of another variable. 
    // To declare a pointer, we use an asterisk (*) b/w the data type and the variable name.
    // syntax to define pointers:  data_type *ptr_name

    int num1 = 7;
    float num2 = 3.14;

    // common naming convention for pointers is to use first letter 'p' followed by the variable name it is pointing to
    int *pNum1 = &num1;
    float *pNum2 = &num2;

    cout << "Values of variables -- num1 : " << num1 << " and num2 : " << num2 << '\n';
    cout << "Memory Addresses of variables -- &num1 : " << &num1 << " and &num2 : " << &num2 << '\n';
    cout << "Values of pointer variables -- pNum1 : " << pNum1 << " and pNum2 : " << pNum2 << '\n';
    cout << "Memory addresses of pointer variables -- &pNum1 : " << &pNum1 << " and &pNum2 : " << &pNum2 << '\n';
    
    // what if we want to store the memory address of a pointer itself..
    // in that case the variable data type is data_type* (pointer is data_type*) and then we will use another * for pointer
    int ** ptrPNum1 = &pNum1;           // pointer to a pointer
    cout << "ptrPNum1 : " << ptrPNum1 << " , memory address of pointer pNum1 : " << &pNum1 << '\n';


    // pointers points to other variables by referencing to the memory locations of those variables.
    // they store the memory address of the variables they are pointing to.
    // so, if ptr is a pointer pointing to variable var, then,
    // ptr will have memory adddress of var (&var) as its value
    // &ptr will give us the memory address of the pointer itself (this address will be of pointer bucket)
    // we can reference the value the pointer is referencing to (the value of variable var) using dereference operator (*ptr) 
    
    cout << "*pNum -> Value the pNum pointer is pointing to : " << *pNum1 << '\n';

    // Null Pointer
    // null value: a special value that means something has no value
    // When a pointer is holding a null value, that pointer is not pointing at anything (null pointer)
    // 'nullptr' is the keyword for null pointer
    // null pointers are helpful in determining if an address was successfully assigned to a pointer
    int *pointer = nullptr;
    cout << pointer << '\n';
    // If we dereference a null-pointer, it can lead to undefined behaviour

    if (pointer == nullptr)
        cout << "no address was assigned to the pointer! \n";
    else
        cout << "The value pointer is referencing to is : " << *pointer << '\n';

    // when using pointers, be careful that your code is not dereferencing nullptr or pointing to free memory. 
    // As this will cause undefined behaviour.

    return 0;
}