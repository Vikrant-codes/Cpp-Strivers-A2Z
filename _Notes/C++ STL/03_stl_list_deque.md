# STL: list and deque

## list

`list` is a doubly linked list — unlike `vector`, its elements are not stored in one contiguous block of memory, but as individual nodes scattered in memory, each one linking to the node before and after it. This structural difference gives `list` a completely different set of strengths and weaknesses compared to `vector`.

```cpp
#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> l = {1, 2, 3};

    l.push_back(4);
    l.push_front(0);

    for (int val : l) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}
```

This prints `0 1 2 3 4`. `push_back(4)` adds to the end, exactly like a vector, but `push_front(0)` adds to the very beginning — something a `vector` cannot do efficiently, since inserting at the front of a vector requires shifting every existing element over by one. A `list` can insert or remove at the front, back, or anywhere in the middle in constant time, because it only needs to adjust a couple of node links rather than move any actual data around.

The tradeoff is that a `list` does not support direct indexing — there's no `l[2]` for a list, since reaching the third element means following links one by one from the start, rather than jumping straight to a memory address the way a vector can. Because of this, accessing an arbitrary element in a `list` is a slow, linear-time operation, whereas the same access on a `vector` is effectively instant.

```cpp
list<int> l = {1, 2, 3, 4};
l.pop_front();
l.pop_back();

for (int val : l) {
    cout << val << " ";
}
```

`pop_front()` removes the first element and `pop_back()` removes the last, leaving `{2, 3}` and printing `2 3`.

## deque

`deque` (pronounced "deck," short for "double-ended queue") is something of a middle ground between `vector` and `list`. Like a `vector`, it supports fast, constant-time random access by index using `[]`, but like a `list`, it also supports fast insertion and removal at both the front and the back.

```cpp
#include <iostream>
#include <deque>
using namespace std;

int main() {
    deque<int> d = {2, 3, 4};

    d.push_back(5);
    d.push_front(1);

    cout << d[0] << endl;
    cout << d[4] << endl;

    for (int val : d) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}
```

After `push_back(5)` and `push_front(1)`, `d` becomes `{1, 2, 3, 4, 5}`. `d[0]` gives `1` and `d[4]` gives `5`, showing that indexing works just as naturally as it does with `vector`. Internally, a `deque` is typically implemented as a series of fixed-size memory blocks rather than one single contiguous block, which is what allows it to grow efficiently at both ends without needing to shift or reallocate the entire structure the way a vector sometimes must.

## When to Choose Which

If you mostly need fast access by index and mostly add or remove elements at the end, `vector` is almost always the right default choice, since it has the least memory overhead and the best cache performance of the three. If you need to frequently insert or delete elements in the middle of the sequence, `list` becomes more attractive, since those operations don't require shifting other elements. If you specifically need efficient additions and removals at both ends while still keeping indexed access, `deque` fills that gap — it's the underlying container used by both `stack` and `queue` in many implementations, covered in the next file.

| Operation | vector | list | deque |
|---|---|---|---|
| Random access by index | fast | slow | fast |
| Insert/remove at the back | fast | fast | fast |
| Insert/remove at the front | slow | fast | fast |
| Insert/remove in the middle | slow | fast | slow |
