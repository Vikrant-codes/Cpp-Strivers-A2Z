#include <iostream>
#include <vector>
using namespace std;

// Quick Sort

/*
QuickSort is a sorting algorithm based on the Divide and Conquer that picks an element as a pivot 
and partitions the given array around the picked pivot by placing the pivot in its correct position in the sorted array.

>> Intuition

The main idea behind Quicksort is:
Pick one element as a pivot, rearrange the array so that elements smaller than the pivot 
come before it and elements larger than the pivot come after it, 
then recursively do the same thing on the left and right parts.

For example: [8, 3, 7, 4, 9, 2, 6, 5]
Choose pivot = 5

After partition:
    [3, 4, 2]  5  [8, 7, 9, 6]
       <5       ^       >5
              pivot

Now 5 is already in its final sorted position.
So we only need to sort [3, 4, 2] and [8, 7, 9, 6], recursively.
Eventually: [2, 3, 4]  5  [6, 7, 8, 9] and the entire array is sorted.

>> Algorithm
At each recursive call:
1. If the current range contains fewer than 2 elements, stop.
2. Select a pivot.
3. Partition the range around the pivot.
4. Recursively sort the left portion.
5. Recursively sort the right portion.
Base Case: The recursion stops when there is only one element left in the sub-array, as a single element is already sorted.

Conceptually:
|    quickSort(arr, low, high):
|
|        if low >= high:
|            return
|
|        pivotIndex = partition(arr, low, high)
|
|        quickSort(arr, low, pivotIndex - 1)
|        quickSort(arr, pivotIndex + 1, high)
*/

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[low];       // choosing the first element as pivot

    // place 2 pointers at both ends
    int i = low + 1;            // i will find the element > pivot
    int j = high;               // j will find the element <= pivot

    // loop until i & j haven't crossed
    while (i <= j) {
        // Move i till we find the element which is > pivot, make sure to stay within array bounds while moving
        while (i <= high && arr[i] <= pivot) i++;

        // Move j till we find the element which is <= pivot 
        while (j >= low && arr[j] > pivot) j--;

        // if i & j haven't crossed, swap the two elements (smaller/equal goes to left, larger goes to right)
        if (i < j)
            swap(arr[i], arr[j]);
    }

    // what happens when i == j ?, the reason we used while (i <= j), in the while condition:
    /*
    imagine we have certain array like [p, a, b, c, d, e, f, g]
                                        ^           ^
                                        pivot       i,j
    and say, i & j both are pointing to d.
    since we are partitioning, obviously (a, b, c) are all <= pivot p, and (e, f, g) are all > pivot.

    Now, if d > pivot:
        i must point to an element > pivot, which it is already doing, so i won't move ahead
        j must point to a smaller/vale value, so it moves and points at c.
        since i & j has now crossed, i & j values are not swapped.
        Loop ends, with j now pointing at c.
        So, we swap jth value and pivot, giving us: [c, a, b, p, d, e, f, g]
    if d <= pivot:
        i must point to a bigger value, so i moves ahead and stops at e.
        j won't move as it is already pointing to a smaller/equal value.
        since i & j has crossed, no swapping of i & j happens.
        Now, loop ends with j pointing at d.
        We swap jth value with pivot, giving us: [d, a, b, c, p, e, f, g]

    So, in both cases, i & j adjust and pivot is placed accordingly. 
    If we haven't put i <= j, in the while condition, then loop would have terminated the moment i & j became equal
    and it could result in wrong partitioning for case when i & j point at value > pivot.
    */

    swap(arr[low], arr[j]);    // Place pivot at its correct position 
    // now elements <= pivot are on the left, > pivot are on the right

    return j;                  // Return the partition index
}

int partition2(vector<int>& arr, int low, int high) {
    int pivot = arr[high];      // choosing the last element as pivot
    int i = low;                // pointer to mark the place for smaller/equal element

    // iterate from low -> high, and whenever a element <= pivot is found, place it at ith position & increment i
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }

    // now i points at the position where the next smaller element must come
    // since traversal has ended, there are no more smaller elements left, so we place pivot at the ith position
    swap(arr[high], arr[i]);

    return i;       // i is the partition index
}

void quickSort(vector<int>& arr, int low, int high) {
    // Base case: if a single element is remaining or no element at all, return
    if (low >= high) 
        return;

    int p = partition(arr, low, high);      // returns the partition index

    quickSort(arr, low, p-1);               // recursively sort the left half
    quickSort(arr, p+1, high);              // recursively sort the right half

    // we can also implement it like below
    /*
    if (low < high) {
        int p = partition(arr, low, high);

        quickSort(arr, low, p-1);
        quickSort(arr, p+1, high);
    } 
    */
}


// Partition Strategies / Techniques
/*
The interesting part is: partition(...)
There are several ways to implement this.

>> What exactly does "partition" mean?
Partitioning does not necessarily mean completely sorting the array.
Its goal is simply to establish some relationship around a pivot.

For the common Lomuto-style partition:
    elements <= pivot | pivot | elements > pivot
For Hoare partition:
    elements <= pivot | elements >= pivot

Notice something important: Different partition schemes have different guarantees.
This is why Lomuto and Hoare aren't just two syntactic implementations of the same thing. 
They actually define the partition boundary differently.

---------------------------------------------------------------------------------------------------------------------

| Lomuto Partition

Lomuto is probably the easiest partition scheme to understand.
We'll use the last element as pivot.
Example:
    [7, 2, 1, 6, 8, 5, 3]
                       ↑
                     pivot
    Pivot = 3.
We maintain:
    i = boundary of elements <= pivot
    j = scanning pointer

Initially: i = low - 1
Then scan j from low to high - 1.
Whenever: arr[j] <= pivot, we expand the "small elements" region by:
    i++
    swap(arr[i], arr[j])
At the end, put the pivot immediately after the small-elements region: swap(arr[i + 1], arr[high])

Example
    [7, 2, 1, 6, 8, 5, 3]
                       ^
                     pivot
Scan:
7 > 3: nothing.
2 <= 3: move it into the left region: [2, 7, 1, 6, 8, 5, 3]
Then:
1 <= 3: [2, 1, 7, 6, 8, 5, 3]
The remaining elements are > 3.
Finally put pivot after the smaller region:
    [2, 1, 3, 6, 8, 5, 7]
           ^
         pivot
Now: [2, 1]  3  [6, 8, 5, 7]
The pivot is in its final position.

# Lomuto invariant
During scanning:
    [low ........ i]       -> <= pivot
    [i+1 ...... j-1]       -> > pivot
    [j ........ high-1]    -> unexplored
That's the key to understanding Lomuto.

---------------------------------------------------------------------------------------------------------------------

| Hoare Partition

Hoare's scheme is quite different.
Instead of taking a pivot and pushing every smaller element toward it, we use two pointers moving toward each other.
For example:
    [7, 2, 1, 6, 8, 5, 3]
     ↑                 ↑
     i                 j
Choose a pivot value, say: pivot = 6
Now:
• move i from the left until we find an element that should be on the right
• move j from the right until we find an element that should be on the left 
• swap them
So:
    i → find arr[i] >= pivot
    j → find arr[j] <= pivot
Then swap.

Example:
    [7, 2, 1, 6, 8, 5, 3]
     ↑                 ↑
     7 >= 6            3 <= 6
Swap: [3, 2, 1, 6, 8, 5, 7]
Move pointers again.
Eventually the pointers cross, giving us a partition such as:
    [3, 2, 1, 5, 6] [8, 7]
                 ↑
              boundary

The important distinction:
Hoare does NOT necessarily put the pivot into its final sorted position.
That's a major difference from Lomuto.
Instead, it returns a partition boundary.
Therefore recursive calls are typically:
    quickSort(arr, low, p);
    quickSort(arr, p + 1, high);
rather than:
    quickSort(arr, low, p - 1);
    quickSort(arr, p + 1, high);

>> Lomuto vs Hoare
|                               | Lomuto                  | Hoare                      |
| ----------------------------- | ----------------------- | -------------------------- |
| Main idea                     | One boundary + scanning | Two pointers moving inward |
| Pivot usually                 | Often last element      | Often middle/first value   |
| Pivot ends at final position? | **Yes**                 | **Not necessarily**        |
| Returns                       | Pivot's final index     | Partition boundary         |
| Swaps                         | Generally more          | Generally fewer            |
| Simplicity                    | Easier                  | Slightly trickier          |
| Typical recursive calls       | `p-1`, `p+1`            | `p`, `p+1`                 |
| Performance                   | Good                    | Often better in practice   |

---------------------------------------------------------------------------------------------------------------------

| 3-Way Partition

There's another extremely useful partition strategy: Dutch National Flag / 3-way partitioning.
Instead of dividing the array into two groups: < pivot | > pivot
we divide it into three:
    < pivot | == pivot | > pivot

For example: [4, 2, 4, 4, 1, 5, 4, 3]
pivot = 4
After partition:
    [2, 1, 3] | [4, 4, 4, 4] | [5]
        <4          ==4           >4

Now we don't need to recursively process the middle section at all.
This is particularly useful when the array contains many duplicate values.
Why?
Suppose: [5, 5, 5, 5, 5, 5, 5]
A conventional 2-way partition can repeatedly create very unbalanced partitions.
3-way partition immediately recognizes: everything == pivot, and finishes.
This is often called: `3-way Quicksort` and is a very important practical variant.
*/

// Pivot Selection Strategies
/*
>> Pivot Selection
Partition strategy and pivot selection are two separate decisions.
We can think of Quicksort as:
                 QUICKSORT
                    |
          +---------+---------+
          |                   |
     Pivot selection       Partition
          |                   |
      Which element?      How to divide?
For example:
    Pivot = last element
    Partition = Lomuto
or:
    Pivot = middle element
    Partition = Hoare
or:
    Pivot = median-of-three
    Partition = 3-way
These choices can be mixed.

Different pivot choices / selection strategies are 
- First Element
- Last Element
- Middle Element
- Random Element
- Median of Three
- True Median

---------------------------------------------------------------------------------------------------------------------

| First Element

Choose: pivot = arr[low], Very simple.
But there's a huge problem.
Consider an already sorted array: [1, 2, 3, 4, 5, 6, 7]
If we always select the first element: pivot = 1
partition becomes: [] | 1 | [2,3,4,5,6,7]
Then: [] | 2 | [3,4,5,6,7]
and so on.
The recursion tree becomes:
    1
     \
      2
       \
        3
         \
          4
           \
            5
That's essentially: T(n) = T(n-1) + O(n)
giving: O(n²)

---------------------------------------------------------------------------------------------------------------------

| Last Element

Same issue.
If: pivot = arr[high]
and the array is already sorted: [1, 2, 3, 4, 5, 6, 7]
we choose: pivot = 7
and get: [1,2,3,4,5,6] | 7 | []
Again: O(n²)
This is why the choice of pivot matters enormously.

---------------------------------------------------------------------------------------------------------------------

| Middle Element

Choose: pivot = arr[(low + high) / 2];
For: [1, 2, 3, 4, 5, 6, 7]
we get: pivot = 4
which produces roughly: [1,2,3] | 4 | [5,6,7]
This gives a balanced recursion tree:
                 4
              /     \
             2       6
           /  \     /  \
          1    3   5    7
which gives: O(n log n)
assuming the partition is reasonably balanced.

Important subtlety: Choosing the middle index does NOT guarantee the median value.

---------------------------------------------------------------------------------------------------------------------

| Random Pivot

Instead of deterministically choosing a position, choose randomly: 
    pivotIndex = random(low, high);
Then partition around that element.

>> Why is this useful?
Suppose an adversary knows our algorithm always chooses: last element
They can provide an input that causes terrible partitions.

With randomization, the adversary cannot easily predict which element becomes the pivot.
The expected behavior becomes: Expected: O(n log n)
while the theoretical worst case remains: O(n²)
because we can still get unlucky and repeatedly choose terrible pivots.

---------------------------------------------------------------------------------------------------------------------

| Median of Three

A popular practical technique is to choose the median of the first, middle and last element, as the pivot.
For example: first = 10, middle = 3, last = 7
To get their median, we simply find the medium value out of the three (sort the 3 elements and the middle one is median).
The median is: 7, so use 7 as the pivot.
The idea is to avoid obviously bad pivots such as: minimum and/or maximum.
especially on already sorted or nearly sorted data.
This is often used in practical Quicksort implementations.

---------------------------------------------------------------------------------------------------------------------

| True Median

The theoretically ideal pivot is the actual median.
For: [8, 3, 7, 4, 9, 2, 6]
sorted: [2, 3, 4, 6, 7, 8, 9]
median: 6
Then the partition is perfectly balanced: [2,3,4] | 6 | [7,8,9]
This gives the best recursion shape.
But there's a catch:
_ Finding the exact median itself costs work.
So normally we don't explicitly sort the array just to find the median—that would defeat the purpose.

There are selection algorithms that can find the kth smallest element in linear time, 
but using them at every Quicksort recursion level is generally not worth the overhead.
*/

// Complexity Analysis
/*
>> Time Complexity

Let T(n) represent Quicksort's running time.
Partitioning a range of size n takes: O(n), because we inspect the elements.

# Best case
Suppose every pivot divides the array approximately in half:
              n
           /     \
         n/2     n/2
        /  \     /  \
      n/4  n/4  n/4  n/4

Then: T(n) = 2T(n/2) + O(n)
Therefore: O(n log n)

# Average / Expected case
With reasonably good pivot selection: O(n log n)
Randomized Quicksort has: Expected time = O(n log n)

# Worst case
If every partition produces: 0 elements | pivot | n-1 elements
then: T(n) = T(n-1) + O(n)
Therefore: O(n²)
This can happen with poor pivot choices, such as always selecting the first element on an already sorted array.

>> Space Complexity 

Quicksort is interesting because the partition itself can be in-place.
Meaning: No auxiliary array required.
So partitioning requires: O(1) extra space.
However, recursion consumes stack space.
Balanced recursion: O(log n) stack space.
Worst case: O(n) stack space.

Therefore, Auxiliary space:
    Best/Average: O(log n)
    Worst:        O(n)

There are more sophisticated implementations that reduce worst-case stack usage through techniques 
such as tail-recursion elimination / recurse on the smaller partition, 
but the standard recursive implementation has the bounds above.
*/

// Conceptual Picture
/*
                QUICKSORT
                   |
             choose pivot
                   |
                   ↓
              PARTITION
                   |
      +------------+------------+
      |                         |
   smaller                    larger
      |                         |
  quicksort                 quicksort
      |                         |
      +------------+------------+
                   |
                 sorted

And partition itself has multiple interpretations:
# Lomuto
                  pivot
                    ↓
    [ <= pivot ][ pivot ][ > pivot ]
The pivot ends in its final position.

# Hoare
    [ <= pivot ][ >= pivot ]
          ↑
     partition boundary
The pivot itself does not necessarily end in its final position.

# 3-way
[ < pivot ][ == pivot ][ > pivot ]
Especially good when there are many duplicates.

There are really two independent design choices in Quicksort:

Choice 1: How do I choose the pivot?
- First element
- Last element
- Middle element
- Random element
- Median-of-three
- True median

Choice 2: How do I partition?
- Lomuto
- Hoare
- 3-way / Dutch National Flag

So we can have combinations such as:
- Random pivot + Lomuto
- Random pivot + Hoare
- Median-of-three + Hoare
- Middle pivot + 3-way partition
etc.

The fundamental goal remains the same:
Do O(n) work to divide the current range, then recursively solve the resulting subranges.
And the single biggest factor determining whether we get O(n log n) or O(n²) is how balanced those partitions are.

| Quicksort is usually not stable, unlike Merge Sort. 
| But it has the major practical advantage of being in-place and often having excellent cache performance, 
| which is why optimized Quicksort/introsort-style algorithms are so widely used.
*/


// | Lomuto partition Quicksort

// Lomuto Partition: generally uses last element as pivot (we can pick any pivot of our choice)
int partitionLomuto(vector<int>& arr, int low, int high) {
    int pivot = arr[high];

    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);

    return i + 1;
}
void quickSortLomuto(vector<int>& arr, int low, int high) {
    if (low >= high)
        return;
    
    int p = partitionLomuto(arr, low, high);

    quickSortLomuto(arr, low, p);
    quickSortLomuto(arr, p + 1, high);
}

// | Hoare partition Quicksort

// Hoare Partition: The classic Hoare partition uses the first element as the pivot value.
int partitionHoare(vector<int>& arr, int low, int high) {
    int pivot = arr[low];

    int i = low - 1;
    int j = high + 1;

    while (true) {

        // Move i until an element >= pivot is found
        do {
            i++;
        } while (arr[i] < pivot);

        // Move j until an element <= pivot is found
        do {
            j--;
        } while (arr[j] > pivot);

        // Pointers crossed
        if (i >= j)
            return j;

        swap(arr[i], arr[j]);
    }
}
void quickSortHoare(vector<int>& arr, int low, int high) {
    if (low >= high)
        return;
    
    int p = partitionHoare(arr, low, high);

    quickSortHoare(arr, low, p);
    quickSortHoare(arr, p + 1, high);
}

// | 3-way Quicksort / Dutch National Flag Quicksort

// 3-Way Partition
/*
Now we have three regions:
    < pivot | == pivot | unexplored | > pivot
A common implementation uses three pointers: lt, i, gt
with the invariant:
    [low ... lt-1]     < pivot
    [lt ... i-1]       == pivot
    [i ... gt]         unexplored
    [gt+1 ... high]    > pivot
*/
void partition3Way(vector<int>& arr, int low, int high, int& lt, int& gt) {
    int pivot = arr[low];

    lt = low;
    int i = low;
    gt = high;

    while (i <= gt) {

        if (arr[i] < pivot) {
            swap(arr[lt], arr[i]);
            lt++;
            i++;
        }
        else if (arr[i] > pivot) {
            swap(arr[i], arr[gt]);
            gt--;
        }
        else {
            // arr[i] == pivot
            i++;
        }
    }
}
void quickSort3Way(vector<int>& arr, int low, int high) {
    if (low >= high)
        return;

    int lt, gt;

    partition3Way(arr, low, high, lt, gt);

    quickSort3Way(arr, low, lt - 1);
    quickSort3Way(arr, gt + 1, high);

    /*
    Notice that we don't recursively process:
        [lt ... gt]
    because those elements are all equal to the pivot.
    */
}

int main() {
    return 0;
}