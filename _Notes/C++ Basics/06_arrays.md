# Arrays in C++

An array is a collection of elements, all of the same data type, stored together in one continuous block of memory. Instead of creating separate variables for related values — like `score1`, `score2`, `score3` — an array lets you group them under a single name and access each one by its position, called an index.

## Declaration and Initialization

```cpp
int arr[5];
int arr2[5] = {1, 2, 3, 4, 5};
int arr3[] = {1, 2, 3};
int arr4[5] = {1, 2};
int arr5[5] = {0};
```

`int arr[5];` reserves space for 5 integers, but since no values are given, each slot starts out holding an unpredictable "garbage" value until it's explicitly assigned. `arr2` is both declared and fully initialized in one line. When you provide values without specifying a size, as in `arr3`, the compiler simply counts the values and infers the size — here, that's `3`. If you specify a size but provide fewer values than that, as in `arr4`, the remaining slots are automatically filled with `0`, giving `{1, 2, 0, 0, 0}`. Writing `{0}` as the only value, as in `arr5`, is a common shorthand for initializing an entire array to all zeros.

## The Fixed Size Nature of Arrays

The single most important thing to understand about C-style arrays is that their size is fixed at the moment they're created and can never be changed afterward — you can't add a sixth element to a 5-element array, and you can't shrink it either.

```cpp
int arr[5] = {1, 2, 3, 4, 5};
```

This array has valid indices from `0` to `4` only. Attempting `arr[5] = 6;` would compile without error but is actually writing into memory that doesn't belong to the array — a serious bug known as an out-of-bounds write, which can corrupt other data or crash the program unpredictably.

Similarly, in standard C++, the size used to declare an array must be a compile-time constant, not a variable that could change at runtime:

```cpp
int size = 10;
int arr2[size];
```

Some compilers allow this as a non-standard extension (called variable-length arrays), but it isn't part of the official C++ standard and shouldn't be relied on for portable code. The correct approach when you want a named, fixed size is to use `const`:

```cpp
const int SIZE = 5;
int arr3[SIZE];
```

Since `SIZE` is a compile-time constant rather than an ordinary variable, this is fully valid — the compiler knows exactly how much memory to reserve before the program even runs.

Because the size truly cannot grow or shrink, "resizing" an array in practice actually means creating an entirely new, differently-sized array and manually copying over whatever data you want to keep:

```cpp
int oldArr[3] = {1, 2, 3};
int newArr[5];

for (int i = 0; i < 3; i++) {
    newArr[i] = oldArr[i];
}
newArr[3] = 4;
newArr[4] = 5;
```

This copies the three existing values from `oldArr` into the first three slots of the larger `newArr`, then fills in the two new slots manually. If you find yourself needing to grow and shrink a collection frequently, this fixed-size limitation is exactly why C++ also provides `std::vector`, covered at the end of this file.

## Accessing and Modifying Elements

Array indexing in C++ starts at `0`, not `1` — the first element is `arr[0]`, and the last element of an array with `n` elements is `arr[n-1]`.

```cpp
int arr[5] = {10, 20, 30, 40, 50};

cout << arr[0] << endl;
cout << arr[4] << endl;

arr[2] = 99;
cout << arr[2] << endl;
```

`arr[0]` gives `10`, the very first value, while `arr[4]` gives `50`, the fifth and final value in this 5-element array. Assigning `arr[2] = 99;` overwrites the third element (originally `30`), so printing `arr[2]` afterward gives `99`.

A crucial safety note: C++ does not automatically check whether an index is within bounds, unlike some other languages that would immediately throw an error.

```cpp
int arr[3] = {1, 2, 3};
cout << arr[10] << endl;
```

This line compiles perfectly fine, but `arr[10]` reads memory well outside the array's actual bounds — the result is unpredictable "garbage," and in the worst case, this kind of out-of-bounds access can silently corrupt other parts of your program's memory. It's entirely the programmer's responsibility to make sure indices stay within valid range.

## Iterating Over Arrays

```cpp
int arr[5] = {1, 2, 3, 4, 5};

for (int i = 0; i < 5; i++) {
    cout << arr[i] << " ";
}
cout << endl;

for (int val : arr) {
    cout << val << " ";
}
cout << endl;
```

Both loops print `1 2 3 4 5`. The classic indexed loop gives you direct control over the index `i`, which is useful if you need to know the position of each element or want to skip around. The range-based loop is shorter and eliminates any risk of an off-by-one indexing mistake, but doesn't give you direct access to the index itself.

### Finding an Array's Size with sizeof

```cpp
int arr[5] = {1, 2, 3, 4, 5};
int size = sizeof(arr) / sizeof(arr[0]);
cout << size << endl;
```

`sizeof(arr)` gives the total number of bytes the entire array occupies, and `sizeof(arr[0])` gives the number of bytes a single element occupies; dividing the two gives the number of elements, which here is `5`. This trick only works correctly within the same scope where the array was originally declared — if the array is passed into a function, it "decays" into a pointer, and `sizeof` on that pointer would only report the pointer's own size (commonly `8` bytes), not the array's true length.

## Multidimensional Arrays

Arrays can have more than one dimension, which is useful for representing grid-like data such as a matrix or a table.

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
```

`matrix[2][3]` declares an array with 2 rows and 3 columns. The nested loop visits every element: the outer loop moves through each row (`i`), and for every row, the inner loop moves through each column (`j`). This prints:

```
1 2 3
4 5 6
```

## Arrays as Function Parameters

When an array is passed into a function, it doesn't get copied the way a regular variable would — it "decays" into a pointer to its first element. Because of this, the function has no way of knowing the array's length on its own, so the size must be passed in separately as an additional parameter.

```cpp
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[4] = {5, 10, 15, 20};
    printArray(arr, 4);
    return 0;
}
```

Calling `printArray(arr, 4)` passes both the array itself and its length, `4`, since `printArray` has no other way to know where the array ends.

## A More Flexible Alternative: std::vector

Given how restrictive fixed-size arrays can be, C++ provides `std::vector` in the `<vector>` header as a resizable alternative that behaves much like an array but can grow and shrink freely at runtime.

```cpp
#include <vector>
using namespace std;

vector<int> v = {1, 2, 3};
v.push_back(4);
v.pop_back();
cout << v.size() << endl;
```

`push_back(4)` appends a new element onto the end, growing the vector to `{1, 2, 3, 4}`, while `pop_back()` removes the last element, shrinking it back to `{1, 2, 3}`. Unlike a raw array, `v.size()` always tells you exactly how many elements are currently stored, since a vector manages its own size internally. In modern C++ code, `vector` is generally preferred over raw arrays whenever the number of elements might change or isn't known ahead of time.
