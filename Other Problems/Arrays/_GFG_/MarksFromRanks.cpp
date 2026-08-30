/*
GFG - Marks from Ranks : Medium

Consider an input where all marks obtained are divided into intervals of consecutive numbers represented as l[] and r[] 
where l[i] and r[i] represent the starting and ending marks (inclusive) of the i-th interval. 

• The intervals are sorted in increasing order and do not overlap.
• The rank of a mark is defined by its position among all valid marks in increasing order, 
  with the smallest mark assigned rank 1, the next smallest rank 2, and so on.

Given an array rank[]. for each value in rank[], find the corresponding mark and return as an array.

Examples :-

Input: l[] = [1, 6, 14], r[] = [3, 9, 15], rank[] = [2, 5, 8]
Output: [2, 7, 14]
Explanation: The valid marks are 1, 2, 3, 6, 7, 8, 9, 14, 15. 
Their corresponding ranks are 1 to 9 as there are 9 distinct marks. 
Therefore, rank 2 corresponds to mark 2, rank 5 corresponds to mark 7, and rank 8 corresponds to mark 14.

Input: l[] = [5, 10], r[] = [7, 12], rank[] = [1, 4, 6]
Output: [5, 10, 12]
Explanation: The valid marks are 5, 6, 7, 10, 11, 12. 
Their corresponding ranks are 1 to 6 in increasing order. 
Hence, rank 1 corresponds to mark 5, rank 4 corresponds to mark 10, and rank 6 corresponds to mark 12.

Constraints :-
• 1 ≤ l.size(), l[i], r.size(), r[i], rank.size(), rank[i] ≤ 10^5
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach (PrefixSum + Binary Search) : Time Complexity : O(n + q log n) __ Space Complexity : O(n)
/*
>> Intuition

The key observation is that the marks are given as non-overlapping consecutive intervals, 
but the queries are given in terms of ranks.

So, instead of trying to find the mark directly, first determine which interval contains the required rank.

For each interval [l[i], r[i]], calculate how many valid marks it contains:
    count = r[i] - l[i] + 1

Now build a prefix sum / cumulative count array, where:
    cumulativeMarksCount[i] = total number of valid marks from interval 0 to i

For example:
    Intervals:       [10,12]   [20,21]   [30,35]
    Marks count:        3         2         6
    Cumulative:         3         5        11

This tells us:
    Ranks 1–3   → interval [10,12]
    Ranks 4–5   → interval [20,21]
    Ranks 6–11  → interval [30,35]

Now for a given rank, we need to find the first cumulative count ≥ rank.
That index is exactly the interval containing the required mark.
Since cumulativeMarksCount is sorted, we can find this index using Binary Search / Lower Bound.

-> Finding the actual mark
Suppose: rank = 7
Binary search finds: ind = 2
because: cumulativeMarksCount[2] = 11 >= 7

The previous interval accounts for the first 5 ranks, so the position of rank 7 inside the current interval is: 
    7 - 5 = 2
The current interval starts at 30, so:
    mark = 30 + 2 - 1
         = 31
The -1 is because the first position in the interval corresponds to l[ind] itself.

| The pattern to remember 🧠
    Convert intervals → counts → prefix/cumulative counts 
    → binary search for the first cumulative count ≥ rank 
    → calculate the offset within that interval.

>> Complexity

Let n = number of intervals and q = count of ranks.

- Build cumulative count: O(n)
- For Each rank: Binary Search → O(log n)
- All ranks: O(q log n)

Therefore:
Time Complexity: O(n + q log n)
Space Complexity: O(n + q) — cumulative array + result array.
                  O(n) — excluding the result array
*/

int findLowerBound(vector<int>& cumulativeMarksCount, int r) {
    int low = 0, high = cumulativeMarksCount.size() - 1;
    
    while (low <= high) {
        int mid = (low + high) / 2;
        
        if (cumulativeMarksCount[mid] >= r) 
            high = mid - 1;
        else 
            low = mid + 1;
    }
    
    return low;
}

vector<int> getMarks(vector<int> &l, vector<int> &r, vector<int> &rank) {
    int n = l.size();
    
    vector<int> cumulativeMarksCount(n);  
    // will tell how many marks till `ith` interval
    
    int sum = 0;
    for (int i = 0; i < n; i++) {
        cumulativeMarksCount[i] = r[i] - l[i] + 1 + sum;
        sum = cumulativeMarksCount[i];
    }
    
    vector<int> res;
    
    for (int r : rank) {
        int ind = findLowerBound(cumulativeMarksCount, r);
        
        if (ind != 0) r -= cumulativeMarksCount[ind - 1];
        
        res.push_back(l[ind] + r - 1);
    }
    
    return res;
}

int main() {
    return 0;
}