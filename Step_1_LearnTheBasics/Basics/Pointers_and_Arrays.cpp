#include <iostream>
using namespace std;

int main() {
    /*
    Arrays have multiple elements of same data types stored in contiguous location. 
    We can't access the array's memory location using the address-of operator (&array_name) like we do with variables.
    This is because the array_name is itself a reference. The array name itself represents the memory address. 
    The array name references to the memory location of its first element. 

    | the array name acts like a 'constant pointer' (its value can't be changed) which points to its 1st element.
    | so, array name points to its 1st element and we can't change this reference like we can re-initialize pointers. 

    We can access the memory addresses of individual elements using address-of operator ( &arr[i] ).
    */

    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    // cout << "Address of array : " << &arr << '\n';       // Error ❌
    cout << "Address of array : " << arr << " _ Address of 1st element i.e. arr[0] : " << &arr[0] << '\n';

    for (int& x : arr) {
        // the &x in statement &x : arr is for reference variables, and to print the address we are accessing that using &x
        cout << "Element : " << x << " _ Address : " << &x << '\n';
    }
    // Integers are of 4 bytes, so integer array elements are stored in contiguous memory blocks of size 4 bytes

    
    
    return 0;
}