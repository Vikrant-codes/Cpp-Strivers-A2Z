# STL: set and multiset

`set` is an associative container that stores unique elements, automatically kept in sorted order at all times. Internally, it's typically implemented as a self-balancing binary search tree, which is why insertion, deletion, and lookup all run in logarithmic time, and why iterating over a set always visits elements in sorted order without you having to sort anything yourself.

## Declaration and Basic Operations

```cpp
#include <iostream>
#include <set>
using namespace std;

int main() {
    set<int> s;

    s.insert(5);
    s.insert(2);
    s.insert(8);
    s.insert(2);

    for (int val : s) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}
```

This prints `2 5 8`. Notice two things: the elements come out in sorted order even though they were inserted as `5, 2, 8, 2`, and the second insertion of `2` was simply ignored, since a `set` never allows duplicate values — attempting to insert a value that already exists has no effect at all.

## Searching and Removing

```cpp
set<int> s = {10, 20, 30, 40};

if (s.find(20) != s.end()) {
    cout << "Found!" << endl;
}

cout << s.count(30) << endl;
cout << s.count(99) << endl;

s.erase(20);
for (int val : s) {
    cout << val << " ";
}
```

`s.find(20)` searches for the value `20` and returns an iterator pointing to it if found, or `s.end()` if it isn't present — this is the standard pattern for checking membership, much like `string::find` returning `npos` when nothing matches. `s.count(30)` returns `1`, since `30` exists in the set, while `s.count(99)` returns `0`, since it doesn't — because a `set` never holds duplicates, `count` can only ever return `0` or `1`, which makes it a convenient shortcut for a simple existence check. `s.erase(20)` removes `20` entirely, leaving `{10, 30, 40}`.

## Why Use a set?

A `set` is the natural choice whenever you need to store a collection of values with two guarantees at once: that no value appears more than once, and that iterating over them always gives you a sorted sequence. A common example is removing duplicates from a list of numbers while also sorting them in the same step — simply inserting every value from a vector into a set achieves both at once, with no extra sorting code required.

```cpp
#include <vector>
#include <set>

vector<int> nums = {5, 3, 5, 1, 3, 2};
set<int> unique(nums.begin(), nums.end());

for (int val : unique) {
    cout << val << " ";
}
```

This prints `1 2 3 5` — every duplicate has been dropped, and the remaining values are automatically in sorted order, simply as a side effect of using a `set` to store them.

## multiset

`multiset` behaves almost identically to `set`, with one key difference: it allows duplicate values to be stored.

```cpp
#include <iostream>
#include <set>
using namespace std;

int main() {
    multiset<int> ms;

    ms.insert(5);
    ms.insert(2);
    ms.insert(5);

    for (int val : ms) {
        cout << val << " ";
    }
    cout << endl;

    cout << ms.count(5) << endl;
    return 0;
}
```

This prints `2 5 5`, showing that both copies of `5` were kept, still in sorted order alongside `2`. `ms.count(5)` now returns `2`, reflecting how many copies of that value are currently present — unlike with a regular `set`, where `count` could only ever be `0` or `1`.

## set vs multiset

| Feature | set | multiset |
|---|---|---|
| Duplicate values | not allowed | allowed |
| Sorted order | yes | yes |
| `count(x)` result | 0 or 1 | any non-negative number |
| Typical use | unique sorted collection | sorted collection where repeats matter |
