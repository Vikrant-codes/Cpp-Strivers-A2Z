#include<iostream>
using namespace std;

int globalArr[7];  // global array

// Default Values & Maximum Array Size limits of Global Arrays and Local Arrays
/*
1. Global arrays

- Default value: All elements are initialized to 0.
  This is because global (and static) variables are stored in the data/BSS segment, 
  which the operating system zero-initializes.

- Maximum size: Around 10^7 integers (sometimes even larger) is often possible.
  10^7 integers ≈ 10^7 × 4 = 40 MB.
  This memory comes from the program's global/static memory, not the stack.

2. Local arrays

- Default value: Contains garbage values (indeterminate values) unless explicitly initialized.
    int arr[5];      // Garbage values
    int arr[5] = {}; // All zeros

- Maximum size: Limited by the stack size.
  Many systems have a default stack size of around 1–8 MB (or a bit more).
  An array of 10^6 integers requires about 4 MB, which may fit on some systems.
  An array of 10^7 integers requires about 40 MB, which usually causes a stack overflow.

>> Why the different limits?

Memory layout of a typical C++ program:

+----------------------+
| Code (text)          |
+----------------------+
| Global/Static data   |  <-- Global arrays
+----------------------+
| Heap                 |  <-- new, malloc, vector
|                      |
+----------------------+
| Stack                |  <-- Local variables
+----------------------+

Global arrays use the data/BSS segment, while local arrays use the stack, which is much smaller.
That's why the size limit of global array is much larger than local arrays

-> Important note
The values 10^6 and 10^7 are not C++ language limits. They depend on:
- Operating system
- Compiler
- Stack size settings
- Available memory
- Online judge constraints
For example:
  On one system, a local array of 2 × 10^6 integers may work.
  On another, even 5 × 10^5 integers may cause a stack overflow.

>> Best practice : If you need a large array:
- Use a global array, or
- Use dynamic allocation:

    vector<int> arr(10000000);  // All elements initialized to 0

    or

    int* arr = new int[10000000](); // Zero-initialized
    delete[] arr;

    These allocate memory on the heap, which is typically much larger than the stack.
*/

int main() {
    int arr[7];
    // sizeof operator : determine the size in bytes of a: variable, data type, class, objects, etc.
    // sizeof(arr) -> Total size of array in bytes, sizeof(arr[0]) -> Size of single element in bytes 
    int arr_size = sizeof(arr);
    int arr_ele_size = sizeof(int);         // since elements are of 'int' datatype
    // Length = Total size / Size of single element
    int len = sizeof(arr) / sizeof(arr[0]);

    cout << "Global Array (all elements are set to default value 0) :- \n";
    for (int i = 0; i < 7; i++) {
        cout << globalArr[i] << " ";
    }

    cout << "\nLocal Array (Contains garbage values (indeterminate values)) :- \n";
    for (int i = 0; i < 7; i++) {
        cout << arr[i] << " ";
    }

    cout << "\nInitializing array elements :- \n";
    cout << "Enter 7 elements : ";
    for(int i=0; i<7; i++) {
        cin >> arr[i];
    }
    for(int i=0; i<7; i++) {
        cout << "arr[" << i << "] = " << arr[i] << '\n';
    }
    cout << "Squaring Each element" << '\n';
    for(int i=0; i<7; i++) {
        arr[i] *= arr[i];
        cout << "arr[" << i << "] = " << arr[i] << '\n';
    }

    // 2 D Array
    int twodarr[3][5];
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 5; j++) {
            twodarr[i][j] = i * 10 + j;
            cout << "2D Array[" << i << "][" << j << "] = " << twodarr[i][j] << '\t';
        }
        cout << '\n';
    }

    // fill function: Fills a range of elements with specified value .... fill(begin, end, value)
    // arr having default value as 9
    int exm[10] = {9};          // 9 is assigned to arr[0] only rest others are 0
    for(int x : exm) cout << x << ' '; 
    fill(exm, exm+10, 9); // Fill all elements with 9
    cout << '\n';
    for(int x : exm) cout << x << ' ';
    cout << "\n";
    // filling the array with the values 10, 20, 30 in three halves
    int size = 30;
    int a[size];
    fill(a, a + (size / 3), 10);
    fill(a + (size / 3), a+ (size / 3) * 2, 20);
    fill(a + (size / 3) * 2, a + size, 30);
    for (int& x : a) cout << x << " ";

    return 0;
}