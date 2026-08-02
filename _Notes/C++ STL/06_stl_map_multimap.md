# STL: map and multimap

`map` is an associative container that stores data as key-value pairs, where each key is unique and the collection is automatically kept sorted by key at all times. It's essentially the C++ equivalent of what other languages often call a dictionary — you look things up by a meaningful key (like a name or an ID) rather than by a numeric position.

## Declaration and Insertion

```cpp
#include <iostream>
#include <map>
using namespace std;

int main() {
    map<string, int> ages;

    ages["Alice"] = 25;
    ages["Bob"] = 30;
    ages.insert({"Charlie", 22});

    for (auto pair : ages) {
        cout << pair.first << ": " << pair.second << endl;
    }
    return 0;
}
```

This prints the three names along with their ages, but importantly, in alphabetical order by key — `Alice`, `Bob`, then `Charlie` — regardless of the order they were actually inserted in, since a `map` keeps itself sorted by key automatically. There are two equally valid ways to insert an entry: using square-bracket syntax like `ages["Alice"] = 25`, or calling `.insert()` with a pair explicitly, as shown with `"Charlie"`. Each element of a `map`, when iterated over, is a `pair` object with two accessible members: `.first` holds the key, and `.second` holds the associated value.

## Accessing and Checking for a Key

```cpp
map<string, int> ages = {{"Alice", 25}, {"Bob", 30}};

cout << ages["Alice"] << endl;

if (ages.find("Bob") != ages.end()) {
    cout << "Bob found" << endl;
}

cout << ages.count("Charlie") << endl;
```

`ages["Alice"]` retrieves the value associated with `"Alice"`, giving `25`. `ages.find("Bob")` searches for the key `"Bob"` and returns an iterator to it if it exists, or `ages.end()` otherwise — this is the safe pattern to check for a key's presence. `ages.count("Charlie")` returns `0`, since no such key exists in the map, and since keys in a regular `map` are always unique, `count` can only ever return `0` or `1`.

There's an important subtlety with the `[]` operator worth knowing: if you use `ages["NewKey"]` to simply read a value, but that key doesn't already exist, it will silently create a new entry for that key with a default value (`0` for numeric types), rather than telling you the key was missing. This can accidentally insert unwanted entries if you're not careful, which is exactly why `.find()` is the safer choice when you only want to check for existence without modifying the map.

## Removing Entries

```cpp
map<string, int> ages = {{"Alice", 25}, {"Bob", 30}, {"Charlie", 22}};
ages.erase("Bob");

for (auto pair : ages) {
    cout << pair.first << ": " << pair.second << endl;
}
```

`ages.erase("Bob")` removes the `"Bob"` entry entirely, leaving only `Alice` and `Charlie` in the map, still sorted alphabetically by key.

## Updating a Value

Since keys are unique, assigning to an existing key through `[]` simply overwrites its current value rather than creating a duplicate entry.

```cpp
map<string, int> ages;
ages["Alice"] = 25;
ages["Alice"] = 26;

cout << ages["Alice"] << endl;
cout << ages.size() << endl;
```

The second assignment doesn't add a new entry — it overwrites the existing one, so `ages["Alice"]` now gives `26`, and `ages.size()` still reports just `1` entry total.

## multimap

`multimap` is to `map` what `multiset` is to `set` — it allows the same key to appear more than once, each time paired with a potentially different value.

```cpp
#include <iostream>
#include <map>
using namespace std;

int main() {
    multimap<string, int> scores;

    scores.insert({"Alice", 90});
    scores.insert({"Alice", 85});
    scores.insert({"Bob", 70});

    for (auto pair : scores) {
        cout << pair.first << ": " << pair.second << endl;
    }

    cout << scores.count("Alice") << endl;
    return 0;
}
```

Since `multimap` allows repeated keys, both entries for `"Alice"` are kept side by side, and `scores.count("Alice")` returns `2`, reflecting that two separate entries share that key. Note that `multimap` doesn't support the `[]` operator at all, since assigning through `[]` wouldn't make sense when a key could correspond to more than one value — you always insert with `.insert()` instead.

## map vs multimap

| Feature | map | multimap |
|---|---|---|
| Duplicate keys | not allowed | allowed |
| Sorted by key | yes | yes |
| `[]` operator | supported | not supported |
| `count(key)` result | 0 or 1 | any non-negative number |
| Typical use | one value per unique key | multiple values grouped under the same key |
