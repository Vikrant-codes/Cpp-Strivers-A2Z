# Stable Sort
A sorting algorithm is said to be stable if it preserves the relative order of equal elements in the sorted output.
Insertion Sort & Bubble Sort are stable sort. Selection Sort is not a stable sort.

# In-place Sort
A sorting algorithm is said to be in-place if it requires only a constant amount of extra space.
Insertion, Bubble & Selection Sort are all in-place sorting algorithms.

# Adaptive Sort
A sorting algorithm is said to be adaptive if it takes advantage of existing order in its input.
Insertion Sort is adaptive. Selection and Bubble Sort are not adaptive.

# Online Sort
Online sorting algorithms process and sort data as it arrives, without having the entire input available initially. 
They are useful for streaming or dynamic data where continuous updates occur. Examples include: Insertion Sort
Insertion Sort is online sorting algo as it inserts incoming elements into their correct position in a sorted list.
Selection Sort and Bubble Sort are offline sorting algorithms, as they require the entire input to be available before sorting can begin.

# Sorting Algorithms Comparison
| Algorithm | Best Case | Average Case | Worst Case | Space Complexity | Stable? | Online? | In-Place? | Adaptive? |
|---|---|---|---|---|---|---|---|---|
| Selection Sort | `O(n²)` | `O(n²)` | `O(n²)` | `O(1)` | ❌ No | ❌ No | ✅ Yes | ❌ No |
| Bubble Sort | `O(n)` | `O(n²)` | `O(n²)` | `O(1)` | ✅ Yes | ❌ No | ✅ Yes | ✅ Yes |
| Insertion Sort | `O(n)` | `O(n²)` | `O(n²)` | `O(1)` | ✅ Yes | ✅ Yes | ✅ Yes | ✅ Yes |
| Quick Sort | `O(n log n)` | `O(n log n)` | `O(n²)` | `O(log n)` (recursive) | ❌ No | ❌ No | ✅ Yes | ❌ No |
| Merge Sort | `O(n log n)` | `O(n log n)` | `O(n log n)` | `O(n)` (extra array) | ✅ Yes | ❌ No | ❌ No | ❌ No |
| Heap Sort | `O(n log n)` | `O(n log n)` | `O(n log n)` | `O(1)` (in-place) | ❌ No | ✅ Yes | ✅ Yes | ❌ No |
| Counting Sort | `O(n+k)` | `O(n+k)` | `O(n+k)` | `O(n+k)` | ✅ Yes | ❌ No | ❌ No | ❌ No |
| Radix Sort | `O(nk)` | `O(nk)` | `O(nk)` | `O(n+k)` | ✅ Yes | ❌ No | ❌ No | ❌ No |
| Bucket Sort | `O(n+k)` | `O(n+k)` | `O(n²)` | `O(n+k)` | ✅ Yes | ❌ No | ❌ No | ❌ No |

------------------------------------------------------------------------

# Comparison-Based vs Non-Comparison Sorting

A major conceptual distinction is whether the algorithm relies primarily
on comparing elements.

## Comparison-Based Sorting

These algorithms determine order through comparisons such as:

``` text
A < B
A > B
A == B
```

Examples:

-   Insertion Sort
-   Selection Sort
-   Bubble Sort
-   Exchange Sort
-   Merge Sort
-   Quick Sort

For general comparison-based sorting, there is a theoretical lower bound
of:

``` text
Ω(n log n)
```

comparisons in the general case.

This does not mean every comparison-based algorithm always takes exactly
`n log n` time. Simple algorithms such as Bubble Sort and Insertion Sort
can take `O(n²)`.

------------------------------------------------------------------------

# Non-Comparison Sorting

These algorithms can use properties of the values themselves instead of
relying only on pairwise comparisons.

Examples:

-   Counting Sort
-   Radix Sort
-   Bucket Sort

They can achieve better-than-`O(n log n)` performance under appropriate
assumptions about the input.

However, they are specialized techniques. Their efficiency depends on
properties such as:

-   Range of values.
-   Number of digits.
-   Distribution of values.
-   Available memory.

------------------------------------------------------------------------

# Stable Sorting

A sorting algorithm is **stable** if equal elements retain their
original relative order.

Consider:

``` text
(A, 80)
(B, 90)
(C, 80)
```

If we sort by the second value using a stable algorithm:

``` text
(A, 80)
(C, 80)
(B, 90)
```

`A` remains before `C` because they had equal keys and `A` originally
appeared first.

## Why Does Stability Matter?

Suppose data has multiple properties.

For example:

``` text
Name     Department
Alice    Sales
Bob      Engineering
Carol    Sales
```

If we first sort by name and then perform a stable sort by department,
the ordering within each department can retain information from the
previous sort.

This makes stable sorting useful when sorting structured or multi-key
data.

## Common Stable Algorithms

-   Insertion Sort.
-   Bubble Sort.
-   Merge Sort.
-   Counting Sort, when implemented stably.
-   Radix Sort, when its internal sorting method is stable.
-   Bucket Sort, depending on implementation.

## Commonly Unstable Algorithms

-   Selection Sort.
-   Quick Sort.
-   Heap Sort.

Stability can sometimes depend on the exact implementation, so it is
better to think of stability as a property of a particular sorting
implementation rather than only the algorithm's name.

------------------------------------------------------------------------

# In-Place Sorting

A sorting algorithm is generally called **in-place** when it sorts the
input using only a small amount of additional storage.

Examples:

``` text
Insertion Sort → O(1) extra space
Selection Sort → O(1) extra space
Bubble Sort    → O(1) extra space
```

Quick Sort can also be implemented in-place, although its recursion
requires stack space.

Merge Sort, in its standard array implementation, generally needs an
additional array for merging.

Counting Sort, Radix Sort, and Bucket Sort normally require additional
data structures.

------------------------------------------------------------------------

# Adaptive Sorting

An adaptive sorting algorithm takes advantage of existing order in the
input.

For example:

``` text
[1, 2, 3, 4, 5]
```

is already sorted.

An adaptive algorithm can recognize that very little work is needed.

Insertion Sort is naturally adaptive because the amount of shifting
depends on how far elements are from their final positions.

Optimized Bubble Sort is also adaptive because it can stop if a complete
pass performs no swaps.

Selection Sort is not adaptive in its standard form because it continues
scanning the unsorted portion even when the data is already sorted.
