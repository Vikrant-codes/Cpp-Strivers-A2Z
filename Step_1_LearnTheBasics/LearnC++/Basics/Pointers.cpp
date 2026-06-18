#include <iostream>
using namespace std;

int main() {
    // <-- address-of operator (&) -->
    /*
    address-of operator helps to get the memory address of a variable. Syntax -> &variable_name
    memory address: a location in memory where data is stored.
    */
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
    /*
    A pointer is a variable that holds the address of another variable. 
    To declare a pointer, we use an asterisk (*) b/w the data type and the variable name.
    syntax to define pointers:  data_type *ptr_name
    this data_type is the data type of the variable that the pointer will point to.
    So, if pointer is pointing to int variable, we declare pointer with int*, for float: float*, ...
    */
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

    // <-- Dereference operator (*) -->
    /*
    Pointers can be used to access the value of the variable they are pointing to. 
    This can be done using derefence operator (*). The operator itself can be read as 'value pointed to by'
    */
    cout << "*pNum1 -> value pointed to by pNum1 pointer : " << *pNum1 << '\n';

    // Quick Summary About Pointers
    /*
    Pointers points to other variables by referencing to the memory locations of those variables.
    They store the memory address of the variables they are pointing to.
    so, if ptr is a pointer pointing to variable var, then,
    ptr will have memory adddress of var (&var) as its value
    &ptr will give us the memory address of the pointer itself (this address will be of pointer bucket)
    we can reference the value the pointer is referencing to (the value of variable var) using dereference operator (*ptr) 
    */


    // <-- Null Pointer -->
    /*
    'null' is a special value that represents absence of any value (i.e. something has no value).
    If we declare a pointer variable and doesn't initialize it, it will still contain some garbage memory address.
    
    So, the correct way to declare a pointer such that it is not pointing to any memory address is through null pointers.

    Null Pointers holds null value (i.e. the memory-address they are pointing to is NULL or 0)
    We can create null pointers by initializing the pointers with '0' or 'NULL' or 'nullptr'.
    'nullptr' is the keyword used to create null pointers.

    null pointers are helpful in determining if an address was successfully assigned to a pointer
    If we dereference a null-pointer, it can lead to undefined behaviour.
    */
    int *ptr;       // Not initialized, but, it will still point to some garbage memory location
    cout << "Even though uninitialized, ptr is still pointing to : " << ptr << " which holds value : " << *ptr << '\n';

    int *nptr1 = 0;
    int *nptr2 = NULL;
    int *nptr3 = nullptr;
    // nptr1, nptr2 & nptr3 are null pointers. They all have '0' as their stored value
    cout << nptr1 << " " << nptr2 << " " << nptr3 << '\n';
    // we can use either either of the value [0, NULL, nullptr] to create / check for null pointers.

    if (nptr1 == nullptr && nptr1 == NULL && nptr1 == 0)
        cout << "no address was assigned to the pointer! \n";
    else
        cout << "The value pointer is referencing to is : " << *nptr1 << '\n';

    
    // <-- Reference Variables -->
    /*
    A reference variable is an alias, i.e., another name for an already existing variable. (Not a new memory)
    Once a reference is initialized with a variable, either the variable name or 
    the reference name may be use to refer to the variable.

    | A reference in C++ is an alias for an existing variable, not a separate variable and not a pointer.

    Declaration of reference variable requires initialization. Reference variables can't be declared without initialization.
    So, initialization is must for reference variables at the time of declaration. 
    Also, once initialized refernce variables can't be changed.
    */
    int x = 10;
    int &y = x;         // Here, y is a refernce variable
    /*
    no new memory location will be used for variable 'y' and it will be sharing the same memory location as 'x'.
    int &y = x; this statement can be understood as a variable 'y' such that address-of y (&y) is same as 'x'.
    So, this means both x & y share the same address and thus are same variables.
    It's like a person has two names 'Jonathan' and 'John'. Both the names refer to same person and thus 
    it doesn't matter if someone asks for 'John' or 'Jonathan' as it is the same thing.    
    */
    cout << "x : " << x << " y : " << y << '\n';
    cout << "&x : " << &x << " &y : " << &y << '\n';
    // Unlike pointers, no new memory address is created for reference variables
    y = 20;             // changing one changes another as both are same buckets just different names
    cout << "x : " << x << " y : " << y << '\n';

    /*
    Reference vs Pointer

    | Reference (`int &b`)               | Pointer (`int *p`)       |
    | ---------------------------------- | ------------------------ |
    | Alias (another name)               | Stores address           |
    | Cannot be NULL                     | Can be NULL              |
    | Cannot be reseated                 | Can point elsewhere      |
    | No `*` needed                      | Needs dereferencing      |
    | Just an alias (no separate memory) | Have address of its own  |
    */


    // when using pointers, be careful that your code is not dereferencing nullptr or pointing to free memory. 
    // As this will cause undefined behaviour.

    return 0;
}