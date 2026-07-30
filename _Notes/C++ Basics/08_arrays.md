# Arrays in C++

An array is a collection of elements of the **same data type** stored in **contiguous memory**.

## Declaration and Initialization

```cpp
int arr[5];                          // declaration, garbage values initially
int arr2[5] = {1, 2, 3, 4, 5};       // declaration + initialization
int arr3[] = {1, 2, 3};              // size inferred as 3
int arr4[5] = {1, 2};                // remaining elements auto-set to 0 -> {1,2,0,0,0}
int arr5[5] = {0};                   // all elements initialized to 0
```

## Fixed Size Nature — the key rule

**The size of a C-style array must be known at compile time and cannot change afterward.** You can't add or remove elements once declared.

```cpp
int arr[5] = {1, 2, 3, 4, 5};
// arr[5] = 6;      // INVALID - out of bounds, index 5 doesn't exist (valid: 0-4)
// int size = 10;
// int arr2[size];  // INVALID in standard C++ - size must be a constant, not a variable
                     // (some compilers allow this as a non-standard extension - avoid relying on it)

const int SIZE = 5;
int arr3[SIZE];      // VALID - SIZE is a compile-time constant
```

Because size is fixed, resizing means creating a **new** array and copying elements manually:

```cpp
int oldArr[3] = {1, 2, 3};
int newArr[5];  // bigger array

for (int i = 0; i < 3; i++) {
    newArr[i] = oldArr[i];
}
newArr[3] = 4;
newArr[4] = 5;
```

(For dynamic resizing, C++ provides `std::vector` — see note at the end.)

## Accessing and Modifying Elements

```cpp
int arr[5] = {10, 20, 30, 40, 50};

cout << arr[0] << endl;   // 10 - first element (0-indexed)
cout << arr[4] << endl;   // 50 - last element

arr[2] = 99;               // modifying an element
cout << arr[2] << endl;    // 99
```

**Out-of-bounds access is undefined behavior** — C++ does NOT automatically check array bounds like some other languages.

```cpp
int arr[3] = {1, 2, 3};
cout << arr[10] << endl;  // compiles, but reads garbage/unrelated memory - dangerous
```

## Iterating over Arrays

```cpp
int arr[5] = {1, 2, 3, 4, 5};

// classic for loop
for (int i = 0; i < 5; i++) {
    cout << arr[i] << " ";
}
cout << endl;

// range-based for loop
for (int val : arr) {
    cout << val << " ";
}
cout << endl;
```

### Finding array size using sizeof

```cpp
int arr[5] = {1, 2, 3, 4, 5};
int size = sizeof(arr) / sizeof(arr[0]);   // total bytes / bytes per element
cout << size << endl;   // 5
```

**Caution:** this trick only works within the same scope as the array declaration. If the array is passed to a function, it decays to a pointer and `sizeof(arr)` gives the pointer size (usually 8), not the array size.

## Multidimensional Arrays

```cpp
int matrix[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
};

for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
        cout << matrix[i][j] << " ";
    }
    cout << endl;
}
// Output:
// 1 2 3
// 4 5 6
```

## Arrays as Function Parameters

Arrays decay into pointers when passed to functions, so the function needs the size passed separately.

```cpp
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[4] = {5, 10, 15, 20};
    printArray(arr, 4);   // 5 10 15 20
    return 0;
}
```

## Alternative: std::vector (resizable)

Since fixed-size arrays are limiting, C++ offers `vector` for dynamic-size arrays:

```cpp
#include <vector>
using namespace std;

vector<int> v = {1, 2, 3};
v.push_back(4);   // can grow -> {1, 2, 3, 4}
v.pop_back();      // can shrink -> {1, 2, 3}
cout << v.size() << endl;  // 3
```
