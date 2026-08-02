# STL: pair and Iterators

## pair

`pair`, from the `<utility>` header (though it's automatically available whenever you include `<map>`), is a simple container that holds exactly two values, which can be of different types. It's the building block behind `map` and `multimap`, where each stored entry is really a `pair` of a key and a value, but it's also useful entirely on its own whenever you need to group two related pieces of data together without writing a whole custom class for it.

```cpp
#include <iostream>
#include <utility>
using namespace std;

int main() {
    pair<string, int> p1("Alice", 25);
    pair<string, int> p2 = make_pair("Bob", 30);

    cout << p1.first << " is " << p1.second << " years old" << endl;
    cout << p2.first << " is " << p2.second << " years old" << endl;
    return 0;
}
```

`p1` and `p2` show two equally common ways to construct a pair — directly through its constructor, or with the helper function `make_pair`, which can often infer the types automatically without you having to spell them out. Both members are accessed with `.first` and `.second`; there's no special naming beyond that, since a `pair` doesn't know or care what its two values conceptually represent.

Pairs can be compared directly, which is handy when sorting a collection of them — the comparison checks `.first` first, and only looks at `.second` to break a tie.

```cpp
pair<int, int> a = {1, 5};
pair<int, int> b = {1, 3};

cout << (a > b) << endl;
```

Since both pairs share the same `.first` value (`1`), the comparison falls through to `.second`, and since `5 > 3`, this prints `1` (`true`).

A common practical use of `pair` is storing two related values together in a `vector`, such as coordinates or an item paired with its associated count:

```cpp
#include <vector>

vector<pair<string, int>> inventory;
inventory.push_back({"Apples", 10});
inventory.push_back({"Bananas", 5});

for (auto item : inventory) {
    cout << item.first << ": " << item.second << endl;
}
```

This prints `Apples: 10` followed by `Bananas: 5`, showing how a vector of pairs can model a simple list of labeled quantities without needing a dedicated class.

## Iterators

An iterator is an object that points to a specific element within a container and knows how to move to the next (or, in some cases, the previous) element — it's a generalized stand-in for a raw pointer, designed to work uniformly across very different kinds of containers. This uniformity is exactly what allows a single `sort` function, for instance, to work on a `vector`, part of an `array`, or elements pulled from other containers, without needing a separate version written for each one.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {10, 20, 30, 40};

    vector<int>::iterator it = v.begin();
    cout << *it << endl;

    it++;
    cout << *it << endl;

    for (it = v.begin(); it != v.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
    return 0;
}
```

`v.begin()` returns an iterator pointing to the very first element, and `v.end()` returns an iterator representing one position past the last element — not the last element itself, but a marker just beyond it, which is why loop conditions typically use `it != v.end()` rather than pointing directly at the final element. Just like a raw pointer, an iterator is dereferenced with `*` to access the value it currently points to, so `*it` gives `10` right after `v.begin()`. Advancing the iterator with `it++` moves it forward by one position, so `*it` then gives `20`.

The loop shown — starting `it` at `begin()`, continuing while it hasn't reached `end()`, and incrementing each time — is the classic manual pattern that a range-based `for (int val : v)` loop actually expands into behind the scenes; the range-based loop is simply a more concise way of writing exactly this.

### auto with Iterators

Writing out `vector<int>::iterator` repeatedly is verbose, so `auto` is almost always used in practice to let the compiler infer the correct iterator type automatically.

```cpp
vector<int> v = {10, 20, 30};

for (auto it = v.begin(); it != v.end(); it++) {
    cout << *it << " ";
}
```

This behaves identically to the explicitly-typed version above, but is far more common in real code, since `auto` saves you from writing out the full, often lengthy iterator type by hand.

### Iterators on Other Containers

The same `begin()`/`end()`/`*`/`++` pattern works consistently across nearly every STL container, which is precisely the point of having a shared iterator interface in the first place.

```cpp
#include <set>
#include <map>

set<int> s = {5, 2, 8};
for (auto it = s.begin(); it != s.end(); it++) {
    cout << *it << " ";
}

map<string, int> m = {{"Alice", 25}, {"Bob", 30}};
for (auto it = m.begin(); it != m.end(); it++) {
    cout << it->first << ": " << it->second << endl;
}
```

For a `set`, dereferencing an iterator gives the value directly, since a set stores plain values. For a `map`, dereferencing gives a `pair`, so `it->first` and `it->second` are used to reach the key and value respectively — the `->` here works the same way it would with a pointer to a struct, reaching into the pair that the iterator currently points to.

### Reverse Iterators

Every container that supports forward iteration through `begin()`/`end()` also typically supports iterating backward, using `rbegin()` and `rend()`.

```cpp
vector<int> v = {1, 2, 3, 4};

for (auto it = v.rbegin(); it != v.rend(); it++) {
    cout << *it << " ";
}
```

This prints `4 3 2 1` — `rbegin()` starts at the last element and `rend()` marks one position before the first, so iterating between them naturally walks through the container in reverse order without needing to manually calculate indices backward.

### Why Iterators Matter

Iterators are what let algorithms like `sort`, `find`, and `reverse` operate identically across completely different underlying data structures — the algorithm itself only ever talks to a pair of iterators, with no knowledge of whether it's working with a `vector`, part of an `array`, or something else entirely. This separation between "how data is stored" (containers) and "how data is processed" (algorithms), connected only through a shared iterator interface, is one of the core design ideas that makes the STL as flexible and reusable as it is.
