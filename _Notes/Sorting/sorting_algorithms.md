# Sorting Algorithms --- Concepts, Ideas, and How They Work

Sorting is the process of arranging elements into a particular order,
usually ascending or descending.

For example:

``` text
Before:  [5, 2, 8, 1, 3]
After:   [1, 2, 3, 5, 8]
```

Different sorting algorithms solve the same problem in very different
ways. The most useful way to understand them is not just to memorize
their complexity, but to understand **what each algorithm is trying to
accomplish at every step**.

This document focuses on the underlying idea, how the algorithm
approaches the problem, and what makes each technique different.

------------------------------------------------------------------------

# 1. Insertion Sort

## Core Idea

**Take one element from the unsorted part and insert it into the correct
position in the sorted part.**

Insertion Sort works much like arranging playing cards in your hand.

Imagine that you are given cards one at a time. You keep the cards in
your hand sorted, and whenever you receive a new card, you move it left
or right until it reaches its correct position.

The important idea is that the algorithm does not repeatedly search for
the smallest element. Instead, it asks:

> **"Where should this particular element be inserted?"**

## How It Works

At any point, conceptually divide the array into:

``` text
Sorted portion | Unsorted portion
```

Initially, the first element is considered sorted:

``` text
[5] | 3  4  1  2
```

Take `3` from the unsorted portion:

``` text
[5] | 4  1  2
```

Since `3` is smaller than `5`, move `5` to the right and insert `3`:

``` text
[3  5] | 4  1  2
```

Now take `4`:

``` text
[3  5] | 1  2
```

Move `5` to the right and insert `4`:

``` text
[3  4  5] | 1  2
```

Continue until the unsorted portion becomes empty.

Final result:

``` text
[1  2  3  4  5]
```

## What Are We Actually Doing?

For every new element:

1.  Pick the element.
2.  Look backward through the sorted portion.
3.  Shift elements that are larger than it.
4.  Put the element into the empty position created by those shifts.

The key operation is therefore **shifting**, followed by **insertion**.

## Why Is It Good for Nearly Sorted Data?

Consider:

``` text
[1, 2, 3, 5, 4]
```

Only `4` is out of place.

Insertion Sort can simply move `5` one position and insert `4`:

``` text
[1, 2, 3, 4, 5]
```

Very little work is required.

## Characteristics

-   Stable.
-   In-place.
-   Adaptive.
-   Simple.
-   Particularly effective for small or nearly sorted collections.

## Complexity

  Case      Time
  --------- ---------
  Best      `O(n)`
  Average   `O(n²)`
  Worst     `O(n²)`

**Space:** `O(1)`

------------------------------------------------------------------------

# 2. Selection Sort

## Core Idea

**Find the element that belongs at the current position, and put it
there.**

For ascending order, this usually means repeatedly finding the smallest
element in the unsorted portion.

The key question Selection Sort asks is:

> **"Which element should go into the next position?"**

This is different from Insertion Sort, which asks:

> **"Where should this particular element be inserted?"**

## How It Works

Divide the array conceptually into:

``` text
Sorted portion | Unsorted portion
```

Initially:

``` text
[] | 5  3  8  1  2
```

Find the smallest element in the unsorted portion:

``` text
1
```

Place it at the beginning:

``` text
[1] | 3  8  5  2
```

Now find the smallest element in the remaining unsorted portion:

``` text
2
```

Place it next:

``` text
[1  2] | 8  5  3
```

Then:

``` text
[1  2  3] | 5  8
```

Then:

``` text
[1  2  3  5] | 8
```

Finally:

``` text
[1  2  3  5  8]
```

## What Are We Actually Doing?

For position `i`:

1.  Search from `i` to the end.
2.  Find the smallest element.
3.  Swap it with the element at position `i`.
4.  Consider position `i` permanently sorted.
5.  Repeat.

Unlike Insertion Sort, Selection Sort does not care much about the
existing order of the data. It still has to search the remaining portion
for the minimum.

## Why Is It Called Selection Sort?

Because each iteration **selects** the element that should occupy the
next position.

## Characteristics

-   Simple.
-   In-place.
-   Usually not stable.
-   Not adaptive.
-   Performs relatively few swaps compared with many simple quadratic
    sorting algorithms.

## Complexity

  Case      Time
  --------- ---------
  Best      `O(n²)`
  Average   `O(n²)`
  Worst     `O(n²)`

**Space:** `O(1)`

------------------------------------------------------------------------

# 3. Bubble Sort

## Core Idea

**Repeatedly compare neighboring elements and swap them when they are in
the wrong order.**

The name comes from the behavior of large elements: during repeated
passes, larger elements move toward the end of the array.

The key question Bubble Sort asks is:

> **"Are these two neighboring elements in the correct order?"**

## How It Works

Consider:

``` text
[5, 3, 8, 1, 2]
```

Compare neighboring elements:

``` text
5 and 3
```

They are in the wrong order:

``` text
[3, 5, 8, 1, 2]
```

Compare:

``` text
5 and 8
```

Already correct.

Compare:

``` text
8 and 1
```

Swap:

``` text
[3, 5, 1, 8, 2]
```

Compare:

``` text
8 and 2
```

Swap:

``` text
[3, 5, 1, 2, 8]
```

After this pass, the largest element, `8`, has reached its final
position.

The process is repeated for the remaining portion.

## What Are We Actually Doing?

Bubble Sort repeatedly performs:

``` text
Compare neighbors
        ↓
Are they out of order?
        ↓
   Yes → Swap
        ↓
Continue
```

After each full pass, at least one large element is placed into its
final position.

## Early Termination

An optimized Bubble Sort keeps track of whether any swaps occurred
during a pass.

If no swaps occur:

``` text
[1, 2, 3, 4, 5]
```

the array is already sorted, so the algorithm can stop.

This is why the optimized version has a best case of `O(n)`.

## Bubble Sort vs Exchange Sort

Both use swapping, but the defining idea is different.

Bubble Sort specifically focuses on **adjacent comparisons**:

``` text
A[i] vs A[i+1]
```

A typical Exchange Sort implementation can compare an element with
later, non-adjacent elements:

``` text
A[i] vs A[j]    where j > i
```

So:

> **Bubble Sort moves elements through repeated neighboring exchanges.**

## Characteristics

-   Stable.
-   In-place.
-   Adaptive when early termination is used.
-   Simple, but generally inefficient for large collections.

## Complexity

  Case      Time
  --------- -------------------------------
  Best      `O(n)` with early termination
  Average   `O(n²)`
  Worst     `O(n²)`

**Space:** `O(1)`

------------------------------------------------------------------------

# 4. Exchange Sort

## Core Idea

**Compare elements that are out of order and exchange them directly.**

Exchange Sort is a simple comparison-and-swapping strategy. Unlike
Bubble Sort, where the defining operation is comparing adjacent
elements, a typical Exchange Sort implementation can compare an element
with any later element.

The key question is:

> **"Is there a smaller element later that should exchange places with
> this element?"**

## How It Works

Consider:

``` text
[5, 3, 8, 1, 2]
```

Start with the first element, `5`.

Compare it with later elements.

When we encounter `3`:

``` text
5 > 3
```

exchange them:

``` text
[3, 5, 8, 1, 2]
```

Continue comparing the current position with later elements. When a
smaller value is found, exchange it.

Eventually the smallest element reaches the first position.

Then move to the second position and repeat.

## Typical Pattern

``` text
for each position i:
    compare A[i] with later elements
    exchange when they are out of order
```

A representative implementation is:

``` text
for i = 0 to n-1
    for j = i+1 to n-1
        if A[i] > A[j]
            swap(A[i], A[j])
```

## Exchange Sort vs Selection Sort

These two are easy to confuse.

Selection Sort conceptually does:

``` text
Search the entire remaining portion
        ↓
Find the minimum
        ↓
Do one swap
```

A typical Exchange Sort does:

``` text
Compare with a later element
        ↓
If out of order, exchange immediately
        ↓
Continue
```

Both are quadratic and both gradually establish the correct order from
left to right, but their swapping behavior is different.

## Important Terminology Note

"Exchange Sort" is not named as consistently as algorithms such as Merge
Sort or Quick Sort. Some sources use it as a general category for
exchange-based sorting, while others use it for the specific nested-loop
algorithm described above.

For this reason, when implementing it, the definition being used should
be made explicit.

## Characteristics

-   Comparison-based.
-   Uses exchanges/swaps.
-   In-place.
-   Typically not stable.
-   Usually not adaptive.

## Complexity

  Case      Time
  --------- ---------
  Best      `O(n²)`
  Average   `O(n²)`
  Worst     `O(n²)`

**Space:** `O(1)`

------------------------------------------------------------------------

# 5. Merge Sort

## Core Idea

**Break the problem into smaller problems, sort the smaller problems,
and then merge the sorted results.**

Merge Sort uses **Divide and Conquer**.

Its basic strategy is:

``` text
Divide → Solve → Merge
```

The important thing to understand is that Merge Sort does not try to
find the correct position of every element directly. Instead, it makes
the sorting problem easier by repeatedly reducing its size.

## How It Works

Suppose:

``` text
[5, 3, 8, 1, 2, 7]
```

Split it:

``` text
[5, 3, 8]    [1, 2, 7]
```

Split again:

``` text
[5] [3, 8]    [1] [2, 7]
```

Continue until the pieces contain one element:

``` text
[5] [3] [8] [1] [2] [7]
```

A single element is already sorted.

Now merge the pieces.

``` text
[3] + [8] → [3, 8]
[2] + [7] → [2, 7]
```

Then:

``` text
[5] + [3, 8] → [3, 5, 8]
[1] + [2, 7] → [1, 2, 7]
```

Finally:

``` text
[3, 5, 8] + [1, 2, 7]
```

Merge them:

``` text
[1, 2, 3, 5, 7, 8]
```

## The Merge Operation

Merging is the central operation.

Suppose we already have two sorted arrays:

``` text
[2, 5, 8]
[1, 3, 7]
```

Look only at the first remaining element of each:

``` text
2 vs 1 → take 1
2 vs 3 → take 2
5 vs 3 → take 3
5 vs 7 → take 5
8 vs 7 → take 7
```

Then take the remaining `8`.

Result:

``` text
[1, 2, 3, 5, 7, 8]
```

Because both input pieces are already sorted, merging them is efficient.

## What Are We Actually Doing?

The algorithm is not sorting everything at once.

It is creating a guarantee:

> **"If I can sort two smaller arrays, I can efficiently combine them
> into one sorted array."**

It keeps reducing the problem until the individual pieces are trivial to
sort.

## Why Is It `O(n log n)`?

The array is divided approximately in half at each level:

``` text
n
n/2 + n/2
n/4 + n/4 + n/4 + n/4
...
```

There are approximately `log n` levels.

Each level processes all `n` elements during merging.

Therefore:

``` text
O(n) × O(log n) = O(n log n)
```

## Characteristics

-   Divide-and-conquer algorithm.
-   Stable in its standard implementation.
-   Predictable `O(n log n)` time.
-   Requires extra memory for the usual array-based implementation.
-   Particularly useful when stable sorting is important.

## Complexity

  Case      Time
  --------- --------------
  Best      `O(n log n)`
  Average   `O(n log n)`
  Worst     `O(n log n)`

**Space:** `O(n)` for the usual array implementation.

------------------------------------------------------------------------

# 6. Counting Sort

## Core Idea

**Do not compare the elements. Instead, count how many times each value
occurs.**

Counting Sort is fundamentally different from the previous
comparison-based algorithms.

Instead of asking:

``` text
Is 7 smaller than 9?
```

it asks:

``` text
How many 1s are there?
How many 2s are there?
How many 3s are there?
...
```

It can therefore avoid the comparisons that characterize algorithms such
as Quick Sort and Merge Sort.

## Example

Consider:

``` text
[4, 2, 2, 8, 3, 3, 1]
```

The values range from `1` to `8`.

Create a frequency/count array:

``` text
Value:  1  2  3  4  5  6  7  8
Count:  1  2  2  1  0  0  0  1
```

This means:

``` text
1 occurs 1 time
2 occurs 2 times
3 occurs 2 times
4 occurs 1 time
8 occurs 1 time
```

Now reconstruct the sorted result:

``` text
[1, 2, 2, 3, 3, 4, 8]
```

## What Are We Actually Doing?

The algorithm uses the values themselves as information.

For a small integer range:

``` text
Value → Frequency
```

Once the frequencies are known, the sorted order is already implied.

There is no need to compare `1` with `2`, `2` with `3`, and so on.

## Stable Counting Sort

A simple version can reconstruct the array by repeatedly outputting each
value according to its count.

A more sophisticated version uses **cumulative counts** and an output
array.

That version can be stable and is commonly used inside Radix Sort.

## The Important Limitation

Counting Sort needs a manageable range of values.

Consider:

``` text
[2, 3, 5, 8]
```

The range is small, so Counting Sort makes sense.

Now consider:

``` text
[1, 1000000000]
```

Creating counters for every value from `1` to `1,000,000,000` would be
extremely wasteful.

So Counting Sort is not automatically better than comparison-based
sorting. Its performance depends on the value range.

## Characteristics

-   Non-comparison sorting algorithm.
-   Particularly useful for integers with a reasonably small range.
-   Can be stable.
-   Requires additional memory.
-   Performance depends on `n` and the value range.

## Complexity

If `k` represents the range of possible values:

``` text
O(n + k)
```

for the usual implementation.

**Space:** commonly `O(n + k)` for the stable version.

------------------------------------------------------------------------

# 7. Radix Sort

## Core Idea

**Sort values one digit at a time instead of comparing the complete
values.**

Suppose we have:

``` text
170
045
075
090
802
024
002
066
```

Rather than comparing entire numbers, Radix Sort looks at individual
digit positions.

For the common **LSD (Least Significant Digit) Radix Sort**, the order
is:

``` text
Units → Tens → Hundreds → ...
```

## How It Works

Consider:

``` text
[170, 45, 75, 90, 802, 24, 2, 66]
```

Treat shorter numbers as having leading zeros:

``` text
170
045
075
090
802
024
002
066
```

### Pass 1: Units digit

Sort according to the last digit:

``` text
[170, 90, 802, 2, 24, 45, 75, 66]
```

### Pass 2: Tens digit

Now sort according to the tens digit, while preserving the ordering
established by the units digit when the tens digits are equal.

``` text
[802, 2, 24, 45, 66, 170, 75, 90]
```

### Pass 3: Hundreds digit

``` text
[2, 24, 45, 66, 75, 90, 170, 802]
```

Now the numbers are sorted.

## Why Must the Digit Sort Be Stable?

Suppose two numbers have the same current digit.

Their relative order from the previous digit needs to be preserved.

For example, after sorting by units, if two numbers have the same tens
digit, their units-digit ordering must not be destroyed.

This is why LSD Radix Sort commonly uses a **stable Counting Sort** for
each digit.

## What Are We Actually Doing?

The key idea is:

> **Turn one large sorting problem into several smaller sorting problems
> based on digit positions.**

Instead of comparing:

``` text
802 vs 75
```

we process:

``` text
units
tens
hundreds
```

separately.

## Radix and the Meaning of `k`

If:

-   `n` = number of elements
-   `d` = number of digit positions
-   `k` = number of possible digit values/radix

then the common complexity is:

``` text
O(d(n + k))
```

For decimal numbers, `k = 10`.

## Characteristics

-   Non-comparison sorting algorithm.
-   Useful for integers, fixed-format numbers, strings, identifiers,
    etc.
-   Commonly uses Counting Sort for each digit.
-   The internal sort needs to be stable for the standard LSD approach.
-   Performance depends on the number of digits/passes.

## Complexity

``` text
Time: O(d(n + k))
```

**Space:** commonly `O(n + k)`.

------------------------------------------------------------------------

# 8. Bucket Sort

## Core Idea

**Distribute elements into groups called buckets, sort each bucket, and
then combine the buckets.**

Bucket Sort is based on the assumption that elements can be distributed
into meaningful ranges.

Instead of immediately sorting:

``` text
[0.42, 0.32, 0.23, 0.52, 0.25, 0.47, 0.51]
```

we first distribute the elements.

Conceptually:

``` text
Bucket 0 → values around 0.0–0.1
Bucket 1 → values around 0.1–0.2
Bucket 2 → values around 0.2–0.3
...
Bucket 5 → values around 0.5–0.6
```

## Example

Input:

``` text
[0.42, 0.32, 0.23, 0.52, 0.25, 0.47, 0.51]
```

After distribution, we might have:

``` text
Bucket 2 → [0.23, 0.25]
Bucket 3 → [0.32]
Bucket 4 → [0.42, 0.47]
Bucket 5 → [0.52, 0.51]
```

Now sort each bucket individually:

``` text
Bucket 2 → [0.23, 0.25]
Bucket 3 → [0.32]
Bucket 4 → [0.42, 0.47]
Bucket 5 → [0.51, 0.52]
```

Finally, concatenate the buckets in order:

``` text
[0.23, 0.25, 0.32, 0.42, 0.47, 0.51, 0.52]
```

## What Are We Actually Doing?

The algorithm takes advantage of the fact that values belonging to the
same range are already known to be near each other.

The strategy is:

``` text
Large collection
      ↓
Separate into ranges
      ↓
Several smaller collections
      ↓
Sort each small collection
      ↓
Concatenate
```

The buckets do not necessarily need to contain only one value. They
contain **ranges of values**.

## Why Can It Be Fast?

If the data is distributed reasonably evenly, each bucket contains
relatively few elements.

For example:

``` text
1000 elements
      ↓
10 evenly distributed buckets
      ↓
~100 elements per bucket
```

Sorting many small groups can be cheaper than sorting one large group.

## What Happens in the Worst Case?

Suppose all elements go into one bucket:

``` text
Bucket 0 → 1000 elements
Bucket 1 → empty
Bucket 2 → empty
...
```

The advantage of distributing the elements disappears.

If the sorting method used inside the bucket takes `O(n²)`, the whole
algorithm can also become `O(n²)`.

## Characteristics

-   Distribution-based sorting.
-   Particularly useful when the input distribution is reasonably
    uniform.
-   Requires additional memory for buckets.
-   The sorting algorithm used inside the buckets affects the final
    properties.
-   Can be stable if the bucket arrangement and internal sorting are
    stable.

## Complexity

Under suitable distribution assumptions:

``` text
Average: O(n + k)
```

Worst case can be:

``` text
O(n²)
```

depending on the bucket distribution and the sorting algorithm used
inside the buckets.

**Space:** commonly `O(n + k)`.

------------------------------------------------------------------------

# 9. Quick Sort

## Core Idea

**Choose a pivot, partition the array around that pivot, and recursively
sort the two sides.**

Quick Sort is another **Divide and Conquer** algorithm.

But unlike Merge Sort, it does not divide the array simply by taking the
middle.

Instead, it divides the array based on a **pivot**.

## What Is a Pivot?

A pivot is an element chosen to divide the array.

Suppose:

``` text
[5, 3, 8, 1, 2]
```

Choose:

``` text
Pivot = 5
```

Partition the elements around it:

``` text
[3, 1, 2] | 5 | [8]
```

The important property is:

``` text
Everything on the left < pivot
Everything on the right > pivot
```

The pivot is therefore in its final sorted position.

Now we only need to sort:

``` text
[3, 1, 2]
```

and:

``` text
[8]
```

## What Are We Actually Doing?

The key idea is:

> **Put one element into its final position, then use that position to
> divide the remaining problem.**

This is different from Merge Sort.

Merge Sort says:

``` text
"Split first, then figure out the ordering while merging."
```

Quick Sort says:

``` text
"Find a pivot, put it in the right place, then sort what is on either side."
```

## Example

Start:

``` text
[5, 3, 8, 1, 2]
```

Choose `5`:

``` text
[3, 1, 2] | 5 | [8]
```

Sort the left side.

Choose `3`:

``` text
[1, 2] | 3 | []
```

Sort `[1, 2]`:

``` text
[1] | 2 | []
```

Final result:

``` text
[1, 2, 3, 5, 8]
```

## Partitioning Is the Core Operation

The partition operation does not necessarily completely sort the array.

Its job is simply to create a boundary around the pivot:

``` text
smaller values | pivot | larger values
```

Once that is achieved, the two sides can be handled independently.

## Pivot Selection

The choice of pivot matters.

Possible choices include:

-   First element.
-   Last element.
-   Middle element.
-   Random element.
-   Median-of-three.

A poor pivot repeatedly creates very unbalanced partitions.

A good pivot tends to divide the array into reasonably sized parts.

## Best/Average Case

If the partitions are reasonably balanced:

``` text
n
↓
n/2 + n/2
↓
n/4 + n/4 + n/4 + n/4
↓
...
```

There are approximately `log n` levels.

Each level performs approximately `O(n)` partitioning work.

Therefore:

``` text
O(n log n)
```

## Worst Case

If the pivot is always the smallest or largest element:

``` text
n
↓
0 + (n-1)
↓
0 + (n-2)
↓
0 + (n-3)
```

The recursion becomes highly unbalanced.

The total work becomes:

``` text
O(n²)
```

This is one reason pivot selection matters.

## Characteristics

-   Divide-and-conquer algorithm.
-   Often very fast in practice.
-   Can be implemented in-place.
-   Usually not stable.
-   Performance depends on partition quality and pivot selection.

## Complexity

  Case      Time
  --------- --------------
  Best      `O(n log n)`
  Average   `O(n log n)`
  Worst     `O(n²)`

**Space:** typically `O(log n)` recursion stack with balanced
partitions; worst-case recursion depth can be `O(n)`.

------------------------------------------------------------------------

# How the Sorting Techniques Differ Conceptually

The algorithms above can be grouped according to the fundamental
question they ask.

## Insertion Sort

> **"Where should this element be inserted?"**

``` text
Take element → shift larger elements → insert
```

------------------------------------------------------------------------

## Selection Sort

> **"Which element should occupy the next position?"**

``` text
Find minimum → put it in position
```

------------------------------------------------------------------------

## Bubble Sort

> **"Are these neighboring elements in the correct order?"**

``` text
Compare neighbors → swap if necessary
```

------------------------------------------------------------------------

## Exchange Sort

> **"Are these elements out of order? If so, exchange them."**

``` text
Compare elements → exchange when necessary
```

------------------------------------------------------------------------

## Merge Sort

> **"Can I break this large sorting problem into smaller sorted
> problems?"**

``` text
Divide → sort smaller pieces → merge
```

------------------------------------------------------------------------

## Counting Sort

> **"How many times does each value occur?"**

``` text
Count values → reconstruct order
```

------------------------------------------------------------------------

## Radix Sort

> **"Can I establish the order one digit/character position at a
> time?"**

``` text
Sort by digit → next digit → next digit → ...
```

------------------------------------------------------------------------

## Bucket Sort

> **"Can I group nearby values so that each group is easy to sort?"**

``` text
Distribute → sort buckets → concatenate
```

------------------------------------------------------------------------

## Quick Sort

> **"Can I put one pivot into its final position and solve the two sides
> independently?"**

``` text
Choose pivot → partition → recursively sort
```

------------------------------------------------------------------------

# Important Differences Between Similar Algorithms

## Insertion Sort vs Selection Sort

### Insertion Sort

``` text
Take an element
      ↓
Find where it belongs
      ↓
Shift elements
      ↓
Insert it
```

### Selection Sort

``` text
Find the element that belongs here
      ↓
Swap it into position
```

The fundamental difference is:

> **Insertion Sort focuses on the current element. Selection Sort
> focuses on the current position.**

------------------------------------------------------------------------

# Bubble Sort vs Exchange Sort

Both algorithms use comparisons and exchanges, but the defining
operation is different.

### Bubble Sort

Only neighboring elements are compared during the normal pass:

``` text
A[i] vs A[i+1]
```

Large elements gradually move toward the end through repeated adjacent
swaps.

### Exchange Sort

A typical implementation compares:

``` text
A[i] vs A[j]
```

where `j` can be any later position.

If they are out of order, they can be exchanged immediately.

So:

> **Bubble Sort is specifically based on adjacent exchanges; Exchange
> Sort is based on general exchanges between elements.**

------------------------------------------------------------------------

# Selection Sort vs Exchange Sort

These can look very similar.

### Selection Sort

Conceptually:

``` text
Search the entire unsorted section
        ↓
Find the minimum
        ↓
Perform one swap
```

### Exchange Sort

Conceptually:

``` text
Compare current element with later elements
        ↓
Exchange whenever they are out of order
```

The main difference is whether the minimum is deliberately selected
before the swap or whether exchanges happen during the comparisons.

------------------------------------------------------------------------

# Merge Sort vs Quick Sort

Both are Divide-and-Conquer algorithms, but they divide the problem
differently.

## Merge Sort

``` text
Divide into halves
        ↓
Recursively sort
        ↓
Merge sorted halves
```

The important work happens during **merging**.

## Quick Sort

``` text
Choose pivot
        ↓
Partition around pivot
        ↓
Recursively sort both sides
```

The important work happens during **partitioning**.

### Main complexity difference

Merge Sort guarantees:

``` text
O(n log n)
```

worst-case time.

Quick Sort has:

``` text
Average → O(n log n)
Worst   → O(n²)
```

but is often very fast in practice with good pivot selection.

------------------------------------------------------------------------

# Counting Sort vs Radix Sort

## Counting Sort

Works directly with values:

``` text
Value → Frequency
```

It is particularly effective when the range of values is small.

## Radix Sort

Works with individual digit/character positions:

``` text
Units
  ↓
Tens
  ↓
Hundreds
  ↓
...
```

Radix Sort commonly uses Counting Sort to process each digit.

So Counting Sort can be viewed as a **building block**, while Radix Sort
is a larger strategy that performs multiple stable digit-based sorting
passes.

------------------------------------------------------------------------

# Counting Sort vs Bucket Sort

These are both distribution-based ideas, but they distribute information
differently.

## Counting Sort

Creates a count for each possible value:

``` text
Value → Frequency
```

For example:

``` text
1 → 3
2 → 1
3 → 4
4 → 0
```

## Bucket Sort

Creates groups representing ranges:

``` text
Range → Bucket
```

For example:

``` text
0.0–0.1 → Bucket 0
0.1–0.2 → Bucket 1
0.2–0.3 → Bucket 2
...
```

The simplest way to remember the difference:

> **Counting Sort groups by exact value; Bucket Sort groups by value
> range.**

------------------------------------------------------------------------

# Merge Sort vs Insertion Sort

Both can be stable and are useful in different situations.

Insertion Sort works incrementally:

``` text
Sorted part + one new element
```

Merge Sort works by dividing:

``` text
Large problem
      ↓
Smaller problems
      ↓
Sorted pieces
      ↓
Merge
```

Insertion Sort is excellent when the data is small or nearly sorted.

Merge Sort provides predictable `O(n log n)` time even when the input is
poorly ordered.

------------------------------------------------------------------------

# Quick Sort vs Selection Sort

Both can place elements into progressively correct positions, but their
strategies are very different.

Selection Sort explicitly finds the minimum for each position:

``` text
Find minimum → place minimum → repeat
```

Quick Sort places a pivot into its final position and then recursively
handles both sides:

``` text
Place pivot → solve left → solve right
```

Quick Sort can therefore reduce the problem much more aggressively when
the partitions are balanced.

------------------------------------------------------------------------

# Overall Complexity Summary

| Algorithm | Best | Average | Worst | Extra Space | Stable? | Main Technique |
|---|---:|---:|---:|---:|:---:|---|
| Insertion Sort | `O(n)` | `O(n²)` | `O(n²)` | `O(1)` | Yes | Insertion |
| Selection Sort | `O(n²)` | `O(n²)` | `O(n²)` | `O(1)` | No | Selection |
| Bubble Sort | `O(n)`* | `O(n²)` | `O(n²)` | `O(1)` | Yes | Adjacent exchange |
| Exchange Sort | `O(n²)` | `O(n²)` | `O(n²)` | `O(1)` | Usually No | General exchange |
| Merge Sort | `O(n log n)` | `O(n log n)` | `O(n log n)` | `O(n)` | Yes | Divide & Conquer |
| Counting Sort | `O(n+k)` | `O(n+k)` | `O(n+k)` | `O(n+k)` | Yes** | Counting |
| Radix Sort | `O(d(n+k))` | `O(d(n+k))` | `O(d(n+k))` | `O(n+k)` | Yes** | Digit distribution |
| Bucket Sort | `O(n+k)`*** | `O(n+k)`*** | `O(n²)` | `O(n+k)` | Depends | Distribution |
| Quick Sort | `O(n log n)` | `O(n log n)` | `O(n²)` | `O(log n)`**** | No | Divide & Conquer |

`*` With early termination when no swaps occur.

`**` Stable versions are commonly used; stability depends on
implementation.

`***` Under suitable distribution assumptions.

`****` For balanced recursion; worst-case recursion depth can be `O(n)`.

------------------------------------------------------------------------

# A Simple Mental Model

The easiest way to distinguish the algorithms is to remember what each
one is trying to accomplish:

``` text
INSERTION
"Take this element and put it where it belongs."

SELECTION
"Find the element that belongs in this position."

BUBBLE
"Compare neighbors and keep swapping them until larger elements move right."

EXCHANGE
"Compare elements and exchange them when they are out of order."

MERGE
"Break the problem into smaller sorted problems, then merge them."

COUNTING
"Don't compare values; count how many of each value exist."

RADIX
"Don't compare whole values; establish order one digit at a time."

BUCKET
"Group nearby values, sort the groups, then combine them."

QUICK
"Put a pivot in its final position, then solve the two sides."
```

------------------------------------------------------------------------

# Summary

All of these algorithms produce the same end result:

``` text
Unsorted data
      ↓
Sorted data
```

What changes is **how they create order**.

The simple comparison-based algorithms work directly with elements:

``` text
Insertion → insert
Selection → select
Bubble    → adjacent exchange
Exchange  → general exchange
```

The divide-and-conquer algorithms reduce the problem:

``` text
Merge → divide and merge
Quick → partition around a pivot
```

The distribution-based algorithms exploit properties of the values:

``` text
Counting → exact values/frequencies
Radix    → digits or positions
Bucket   → ranges/distribution
```

Understanding these fundamental strategies is more useful than
memorizing their names alone. Once the central idea of an algorithm is
clear, its implementation and complexity become much easier to
understand.