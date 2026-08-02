# STL: vector

`vector` is the most commonly used STL container — it behaves like a dynamic array, meaning it can grow or shrink at runtime, unlike a plain C-style array whose size is fixed forever once declared. Internally, a vector stores its elements in one contiguous block of memory, just like an array, which is why it supports fast, constant-time access to any element by index.

## Declaration and Initialization

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v1;
    vector<int> v2 = {1, 2, 3, 4};
    vector<int> v3(5, 0);
    vector<int> v4(v2);

    cout << v2[0] << endl;
    return 0;
}
```

`v1` is an empty vector with no elements yet. `v2` is initialized directly with a list of values. `v3(5, 0)` creates a vector of `5` elements, all initialized to `0` — the first argument is the size, the second is the value to fill it with. `v4` is a full copy of `v2`, completely independent of the original. The `<int>` in `vector<int>` specifies the element type; a `vector<string>` or `vector<double>` works exactly the same way with a different type in its place.

## Adding and Removing Elements

```cpp
vector<int> v = {1, 2, 3};

v.push_back(4);
cout << v.size() << endl;

v.pop_back();
cout << v.size() << endl;
```

`push_back(4)` appends a new element to the end, growing the vector to `{1, 2, 3, 4}` and making `size()` return `4`. `pop_back()` removes the last element, shrinking it back to `{1, 2, 3}` and dropping `size()` back down to `3`. These two operations are extremely efficient — adding or removing from the end of a vector is a constant-time operation in the typical case.

Inserting or removing from the middle of a vector is also possible, but is considerably more expensive, since every element after the insertion or removal point has to shift over by one position.

```cpp
vector<int> v = {1, 2, 4, 5};
v.insert(v.begin() + 2, 3);
v.erase(v.begin() + 1);
```

`v.insert(v.begin() + 2, 3)` inserts the value `3` at index `2`, turning `v` into `{1, 2, 3, 4, 5}`. `v.erase(v.begin() + 1)` removes the element at index `1`, turning it into `{1, 3, 4, 5}`. Both operations take an iterator (covered in more depth in the iterators file) to specify the exact position, rather than a plain integer index.

## Accessing Elements

```cpp
vector<int> v = {10, 20, 30};

cout << v[0] << endl;
cout << v.at(1) << endl;
cout << v.front() << endl;
cout << v.back() << endl;
```

`v[0]` and `v.at(1)` both retrieve elements by index, giving `10` and `20` respectively — the difference is that `.at()` performs bounds-checking and throws an exception on an invalid index, while `[]` does not check at all and simply produces undefined behavior if the index is out of range. `.front()` and `.back()` are convenient shortcuts for the very first and very last elements, giving `10` and `30` here.

## Size and Capacity

```cpp
vector<int> v = {1, 2, 3};
cout << v.size() << endl;
cout << v.empty() << endl;
v.clear();
cout << v.empty() << endl;
```

`.size()` returns the current number of elements, `3` here. `.empty()` returns `true` if the vector currently has zero elements — before `clear()` it's `false`, and after `clear()` (which removes every element) it becomes `true`. It's worth noting that a vector's actual allocated memory (its "capacity") is often larger than its current size, since vectors typically over-allocate a bit to avoid reallocating memory on every single `push_back` — this detail is usually invisible to you unless you specifically query `.capacity()`.

## Iterating Over a Vector

```cpp
vector<int> v = {10, 20, 30};

for (int i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
}
cout << endl;

for (int val : v) {
    cout << val << " ";
}
cout << endl;
```

Both loops print `10 20 30`. The index-based loop is useful when you need to know the position of each element, while the range-based loop is more concise and less error-prone when you only need the values themselves.

## 2D Vectors

Vectors can hold other vectors, which is the standard way to represent a grid or matrix whose dimensions might not be known until runtime, unlike a fixed-size 2D array.

```cpp
vector<vector<int>> grid(3, vector<int>(4, 0));
grid[1][2] = 5;

for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
        cout << grid[i][j] << " ";
    }
    cout << endl;
}
```

`vector<vector<int>> grid(3, vector<int>(4, 0));` creates 3 rows, each of which is itself a vector of 4 zeros. Setting `grid[1][2] = 5` changes the element in the second row, third column, to `5`. The nested loop then prints the entire grid, row by row.

## Sorting a Vector

The `sort` algorithm from `<algorithm>` works directly on vectors through iterators.

```cpp
#include <algorithm>

vector<int> v = {5, 2, 8, 1, 9};
sort(v.begin(), v.end());

for (int val : v) {
    cout << val << " ";
}
```

`sort(v.begin(), v.end())` sorts the entire vector in ascending order in place, turning `v` into `{1, 2, 5, 8, 9}`. Sorting in descending order just requires an extra argument:

```cpp
sort(v.begin(), v.end(), greater<int>());
```

## Quick Reference

| Method | Purpose |
|---|---|
| `push_back(x)` | add `x` to the end |
| `pop_back()` | remove the last element |
| `insert(pos, x)` | insert `x` at a given iterator position |
| `erase(pos)` | remove the element at a given iterator position |
| `size()` | number of elements currently stored |
| `empty()` | true if the vector has no elements |
| `clear()` | remove all elements |
| `front()` / `back()` | access the first / last element |
| `at(i)` | bounds-checked access to element `i` |
| `begin()` / `end()` | iterators to the first element / one past the last |
