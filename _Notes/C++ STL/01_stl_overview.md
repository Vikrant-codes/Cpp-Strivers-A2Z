# The C++ Standard Template Library (STL) — Overview

## What is the STL?

The Standard Template Library is a collection of ready-made, generic classes and functions that come bundled with C++, designed to handle common data storage and algorithm needs without you having to write them from scratch. Before the STL, a programmer who needed a resizable array, a linked list, or a sorting routine would have to implement it manually. The STL provides all of these as pre-built, thoroughly tested, and highly optimized tools — which is why almost all real-world C++ code leans heavily on it rather than reinventing these structures.

The word "template" in its name refers to the fact that these tools are written using C++ templates, meaning a single implementation of, say, a vector, can store `int`s, `double`s, `string`s, or even your own custom classes, without the library needing a separate version for each type. You simply specify the type you want when you use it, such as `vector<int>` or `vector<string>`.

## What the STL Contains

The STL is generally organized into four major parts, and understanding this breakdown makes it much easier to know where to look for a particular tool:

**Containers** are the data structures themselves — the objects that actually store your data. This includes `vector`, `array`, `list`, `deque`, `set`, `map`, `stack`, `queue`, `priority_queue`, and several others, each suited to different patterns of storing and accessing data.

**Iterators** are objects that let you move through the elements of a container one at a time, in a uniform way, regardless of what kind of container you're actually working with. They act as a generalized version of a pointer, and are the glue that connects containers to algorithms.

**Algorithms** are standalone functions — such as `sort`, `find`, `reverse`, `count`, and `accumulate` — that operate on containers through iterators, rather than being tied to any one specific container type. Because they work through iterators rather than directly on a particular container, the same `sort` function can sort a `vector`, a portion of an `array`, or elements from many other containers.

**Function objects** (sometimes called functors) are objects that behave like functions and can be passed into algorithms to customize their behavior — for instance, telling `sort` to sort in descending order instead of the default ascending order.

## Categories of Containers

Containers themselves are typically grouped into three families based on how they organize data:

**Sequence containers** store elements in a strict linear order, where each element's position is determined by when and where it was inserted, not by its value. This group includes `vector`, `array`, `list`, `deque`, and `forward_list`.

**Associative containers** automatically keep their elements sorted based on value (or key), rather than insertion order, and are typically implemented internally using balanced binary search trees. This group includes `set`, `multiset`, `map`, and `multimap`.

**Unordered associative containers** also organize elements by key, but use a hash table internally instead of a sorted tree, which trades away ordering in exchange for typically faster average-case lookups. This group includes `unordered_set` and `unordered_map`.

There are also **container adapters** — `stack`, `queue`, and `priority_queue` — which aren't full data structures in their own right, but instead restrict or repurpose the interface of an underlying container (usually `deque` or `vector`) to enforce a particular access pattern, like last-in-first-out for a stack.

## A Quick Comparison of the Main Containers

| Container | Ordering | Duplicates allowed? | Typical use case |
|---|---|---|---|
| `vector` | insertion order | yes | dynamic array, fast random access |
| `list` | insertion order | yes | frequent insertion/removal in the middle |
| `deque` | insertion order | yes | fast insertion/removal at both ends |
| `set` | sorted by value | no | unique, automatically sorted elements |
| `multiset` | sorted by value | yes | sorted elements, duplicates allowed |
| `map` | sorted by key | no (unique keys) | key-value pairs, sorted by key |
| `multimap` | sorted by key | yes (keys can repeat) | key-value pairs, duplicate keys allowed |
| `unordered_set` | no defined order | no | unique elements, fast average lookup |
| `unordered_map` | no defined order | no (unique keys) | key-value pairs, fast average lookup |
| `stack` | LIFO access only | yes | undo history, expression evaluation |
| `queue` | FIFO access only | yes | task scheduling, breadth-first search |
| `priority_queue` | highest priority first | yes | always retrieving the maximum (or minimum) element |

## Why Use the STL at All?

Writing your own dynamic array or hash table is a completely reasonable learning exercise, but in real projects the STL is preferred for a few concrete reasons: its implementations are heavily optimized by compiler vendors and battle-tested across huge amounts of production code; using it makes your code instantly understandable to other C++ programmers, since these names and behaviors are effectively universal; and it saves enormous amounts of time that would otherwise go into re-implementing and re-debugging basic data structures.

## How to Read the Rest of These Notes

Each container gets covered in its own dedicated file with full examples: `vector`, `list` and `deque`, the container adapters (`stack`, `queue`, `priority_queue`), `set` and `multiset`, `map` and `multimap`, the unordered containers, and finally `pair` alongside iterators. It's worth reading this overview first, since the vocabulary introduced here — sequence versus associative containers, iterators, algorithms — is used freely throughout the rest of the notes.
