# Hashing Notes

## 1. What is Hashing?

Hashing is a technique used to store and retrieve data efficiently using
a **key**.

Instead of searching every element, a **hash function** converts the key
into an integer called the **hash value**, which determines where the
data should be stored in a hash table.

Average complexity: - Insert: **O(1)** - Search: **O(1)** - Delete:
**O(1)**

Worst case (many collisions): **O(n)**.

------------------------------------------------------------------------

## 2. Keys and Values

Example:

``` cpp
unordered_map<string, int> marks;

marks["Alice"] = 95;
marks["Bob"] = 88;
```

-   Key: `"Alice"`
-   Value: `95`

Searching with

``` cpp
cout << marks["Alice"];
```

does **not** scan every element. The key is hashed to directly locate
its position.

------------------------------------------------------------------------

## 3. How does O(1) searching work?

Imagine a simple hash function:

    A -> 1
    B -> 2
    ...
    Z -> 26

Searching for `E`:

1.  Compute hash(E) = 5
2.  Go directly to index 5
3.  Retrieve the value

No linear search is required.

------------------------------------------------------------------------

## 4. Does hashing waste space?

Not necessarily.

Example:

Stored keys:

    A, C, F, H, K, M, Z

Occupied indices:

    1  -> A
    3  -> C
    6  -> F
    8  -> H
    11 -> K
    13 -> M
    26 -> Z

Other indices remain empty.

Real hash tables resize dynamically and balance memory with speed.

------------------------------------------------------------------------

## 5. What is a Hash Function?

A hash function converts a key into an integer.

Example (simplified):

    hash("ABC") -> 123456

Since the hash table has limited size, we compute

``` text
index = hash(key) % tableSize
```

Example:

    hash("ABC") = 123456

    table size = 20

    index = 123456 % 20 = 16

The element is stored at index 16.

A good hash function: - Deterministic - Fast - Uniformly distributes
keys - Minimizes collisions

------------------------------------------------------------------------

## 6. Why do collisions occur?

Since the table has limited slots, different hash values may map to the
same index.

Example:

    table size = 20

    0 % 20  = 0
    20 % 20 = 0
    40 % 20 = 0

All three map to index 0.

### Pigeonhole Principle

If

    Number of Keys > Number of Slots

then collisions are **guaranteed**.

------------------------------------------------------------------------

## 7. Collision Handling

### A. Chaining

Each table index stores a linked list (or similar structure).

Example:

    Index 5

    +-----------------------+
    | Apple -> Mango -> Cat |
    +-----------------------+

All three keys hashed to index 5.

Searching:

-   Compute index
-   Traverse only that linked list

Average:

    O(1)

Worst:

    O(n)

if every key lands in the same bucket.

------------------------------------------------------------------------

### B. Open Addressing

Instead of a linked list, search for another empty slot.

Examples:

-   Linear Probing
-   Quadratic Probing
-   Double Hashing

------------------------------------------------------------------------

## 8. Why does searching become slower after collisions?

Without collision:

    hash(key)
        ↓
    index
        ↓
    Value

Time:

    O(1)

With chaining:

    hash(key)
        ↓
    Bucket
        ↓
    Node1 -> Node2 -> Node3

Need to traverse the chain.

Hence search becomes O(k), where k is chain length.

------------------------------------------------------------------------

## 9. Load Factor

    Load Factor = Number of Keys / Number of Buckets

Low load factor: - Fewer collisions - Faster search

High load factor: - More collisions - Longer chains

Many implementations resize the table when the load factor becomes too
high.

------------------------------------------------------------------------

## 10. C++ STL

`unordered_map` and `unordered_set` are hash-table based containers with
average O(1) operations.

`map` is tree-based and has O(log n).

## Interview Takeaways

-   Hashing maps keys to indices.
-   Hash function determines storage location.
-   `% tableSize` keeps indices within bounds.
-   Collisions are unavoidable.
-   Collision handling: Chaining and Open Addressing.
-   Pigeonhole principle explains guaranteed collisions.
-   Average complexity is O(1); worst case O(n).
