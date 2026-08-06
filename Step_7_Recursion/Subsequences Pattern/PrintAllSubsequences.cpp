// Print all subsequeneces of an array
/*
A subsequence is a sequence derived from a string or an array by deleting zero or more elements 
without changing the relative order of the remaining elements. 
Crucially, the elements do not need to be consecutive or contiguous in the original structure.

Consider the string/array: "ABCDE"
-> Valid Subsequences: "ACE", "BD", "ABD", "ABCDE" (the sequence itself), and "" (the empty sequence).
-> Invalid Subsequences: "CEA" (order is broken), "BX" ('X' is not in the original sequence).

>> Properties of Subsequence:
- A sequence is a subsequence of itself.
- The empty sequence is a subsequence of every sequence.
- The relative order of characters is unchanged.
- The number of possible subsequences of a sequence of length n is 2^n.
- A subsequence of a subsequence is also a subsequence of the original sequence. (X_X)

>> Mathematical Formula: 
A sequence of length n contains exactly 2^n total subsequences (including the sequence itself and the empty sequence).
Ex-> For arr = {1, 2, 3}, the total subsequences are 8, which are {}, {1}, {2}, {3}, {1,2}, {1,3}, {1,2,3}.
*/

#include<bits/stdc++.h>
using namespace std;

/*
>> Intuition

Suppose the array is, 
    arr = [1, 2, 3]
Think about the first element (1).
For every element, you have exactly two choices:
- Include it in the current subsequence.
- Exclude it from the current subsequence.
There are no other possibilities.

So for 1, we split into two worlds:
               []
             /    \
         take 1   don't take 1
          [1]          []

Now, in each world, we again reach element 2.
Again we have two choices.
                    []
                 /      \
              [1]         []
             /   \       /   \
        [1,2]   [1]   [2]     []

Then we do the same for 3.
Eventually every possible combination is generated.
The recursion is simply exploring this decision tree.

>> Why do we need ds?
ds (data structure) stores the subsequence we are currently building.
For example,
Suppose we're currently following
    Take 1
    Take 2
    Don't take 3
Then
    ds = [1,2]
When recursion reaches the end,
    ind == n
this becomes one complete subsequence. So we print it.

>> Why push before recursive call?
Suppose current element is
    arr[ind]
If we decide to include it,
then it must become part of the current subsequence.
So
    ds.push_back(arr[ind]);
adds it.
Now recursion continues with this updated subsequence.
    fun(..., ind+1, ds);

>> Why pop after coming back?
This is the heart of backtracking.
Suppose
    ds = [1]
Now we decide to include 2.
    push 2
    ds = [1,2]
We recursively explore every subsequence beginning with
    [1,2]
When recursion finishes, we return.
Now we're about to explore the case
    Take 1
    Don't take 2
But currently
    ds = [1,2]
This is wrong.
We don't want 2 anymore.
So we remove it.
    ds.pop_back();
Now
    ds = [1]
which correctly represents the state before we made the "take" decision.
Then we explore
    fun(...);
without 2.
This is why the pattern is
    Choose
    Explore
    Undo choice
    Explore another choice
This "undo" step is exactly what backtracking means.

>> Recursion Tree
For [1,2,3]

                          []
                       (ind=0)
                     /          \
                 Take1        Not Take1
                 [1]             []
               /     \        /      \
          Take2      NT2    Take2     NT2
          [1,2]      [1]     [2]       []
         /   \      /  \    /  \      /  \
       T3    NT3   T3  NT3 T3  NT3   T3  NT3

Leaves:
[1,2,3]
[1,2]
[1,3]
[1]
[2,3]
[2]
[3]
[]

There are: 2 × 2 × 2 = 2³ = 8 subsequences.

>> Time Complexity
Let the array size be n.

-> Number of recursive calls
Each element has 2 choices
Therefore, Total leaves = 2^n
The recursion tree is a complete binary tree.
Total nodes = 1 + 2 + 4 + ... + 2^n = 2^(n+1) - 1
So recursive calls are: O(2^n)

-> Printing cost
At every leaf, we print a subsequence.
A subsequence can contain at most n elements.
Worst-case printing cost per leaf: O(n)
There are 2^n leaves.
Hence, Printing cost = O(n × 2^n)
This dominates the recursion overhead.

-> Overall Time Complexity : O(n * 2^n)

>> Space Complexity
There are two contributors:
1. Recursion stack
Maximum recursion depth: n
So, O(n)

2. Auxiliary vector (ds)
At worst, ds stores every element.
Maximum size = n
So, O(n)
This is not additional to the recursion depth in terms of asymptotic auxiliary space because both grow linearly with n.

Overall Auxiliary Space: O(n)

>> Key Insight
The recursive pattern is:

    For every element:
        ├── Include it
        │     ↓
        │  Solve remaining problem
        │
        └── Exclude it
              ↓
           Solve remaining problem

and the backtracking pattern is always:

    choose();      // push_back()
    recurse();
    undo();        // pop_back()
    recurse();

Once you recognize this "choose → recurse → undo → recurse" structure, 
you'll see it repeatedly in problems involving subsequences, subsets, combinations, permutations, 
N-Queens, Sudoku solvers, and many other backtracking algorithms.
*/

// Time Complexity : O(n * 2^n) __ Space Complexity : O(n)

// Time complexity to get the subsequences is O(2^n), the extra O(n) is due to printing each subsequence.

// helper method -> prints the passed subsequence. Takes O(n), where n = length of subsequence
void print(const vector<int>& list) {
    cout << "[ ";

    for (int x : list)
        cout << x << " ";
    
    cout << "]" << endl;
}

// print all subsequences
void fun(int arr[], int n, int ind, vector<int>& ds) {
    if (ind >= n) {
        print(ds);
        return;
    }

    // take / pick the current element (will be added to subsequence) ,push it into the data structure list
    ds.push_back(arr[ind]);         
    fun(arr, n, ind + 1, ds);

    // not take/pick the current element (will not be added to subsequence), so remove it from the data structure list
    ds.pop_back();                  
    fun(arr, n, ind + 1, ds);
}

int main() {
    int arr[] = {1, 2, 3};

    vector<int> ds = {};

    fun(arr, 3, 0, ds);
}