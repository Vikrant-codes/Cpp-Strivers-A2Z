# STL: unordered_set and unordered_map

`unordered_set` and `unordered_map` are the hash-table-based counterparts to `set` and `map`. They store the same kind of data — unique values, or unique keys paired with values — but organize them internally using a hash table rather than a sorted tree. This trade sorted ordering for typically faster average-case performance.

## unordered_set

```cpp
#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
    unordered_set<int> s;

    s.insert(5);
    s.insert(2);
    s.insert(8);
    s.insert(2);

    for (int val : s) {
        cout << val << " ";
    }
    cout << endl;

    cout << s.count(8) << endl;
    return 0;
}
```

Just like a regular `set`, duplicate insertions are ignored, so inserting `2` twice still leaves only one copy of it. However, the order elements are printed in is not guaranteed to be sorted, or even consistent between runs — it depends entirely on the internal hash table's layout, which is determined by the hash function and how values happen to be distributed into buckets. `s.count(8)` still works the same way as with `set`, returning `1` since `8` is present.

## unordered_map

```cpp
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    unordered_map<string, int> ages;

    ages["Alice"] = 25;
    ages["Bob"] = 30;

    for (auto pair : ages) {
        cout << pair.first << ": " << pair.second << endl;
    }

    cout << ages["Alice"] << endl;
    return 0;
}
```

This behaves almost identically to `map` in terms of usage — the same `[]` syntax, the same `.first`/`.second` pair access when iterating — but again, the order the entries print in is unspecified and shouldn't be relied upon. Whether `Alice` or `Bob` prints first depends on the hash table's internal layout, not the order they were inserted.

## Why Choose the Unordered Versions?

The main appeal of `unordered_set` and `unordered_map` is performance: in the typical case, insertion, deletion, and lookup all run in constant time on average, compared to the logarithmic time that `set` and `map` require due to their tree-based structure. For very large collections where you're doing a huge number of lookups and don't care about sorted order, this can make a meaningful difference in speed.

The tradeoffs are twofold. First, you lose sorted iteration entirely — if you need to process entries in sorted order, `set` or `map` remain the right choice. Second, the "average-case" constant time performance is not a guarantee — in rare worst-case scenarios (for example, if many keys happen to hash to the same bucket), performance can degrade toward the same logarithmic or even linear time that a tree-based container would provide reliably. In practice, this worst case is uncommon with a well-behaved hash function, but it's worth knowing it exists.

## Choosing Between the Ordered and Unordered Versions

| Situation | Better choice |
|---|---|
| Need elements in sorted order | `set` / `map` |
| Only care about fast lookup, order doesn't matter | `unordered_set` / `unordered_map` |
| Need guaranteed worst-case performance bounds | `set` / `map` |
| Working with very large data, lookup speed is critical | `unordered_set` / `unordered_map` |

As a simple rule of thumb: reach for the unordered versions by default when all you need is "does this exist" or "what value is paired with this key" without caring about order, and switch to the ordered versions the moment you need sorted traversal or predictable worst-case timing.
