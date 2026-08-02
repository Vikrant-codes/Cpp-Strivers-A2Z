/*
Leetcode - 1288. Remove Covered Intervals : Medium

Given an array intervals where intervals[i] = [li, ri] represent the interval [li, ri), 
remove all intervals that are covered by another interval in the list.
The interval [a, b) is covered by the interval [c, d) if and only if c <= a and b <= d.
Return the number of remaining intervals.

Examples :-

Input: intervals = [[1,4],[3,6],[2,8]]
Output: 2
Explanation: Interval [3,6] is covered by [2,8], therefore it is removed.

Input: intervals = [[1,4],[2,3]]
Output: 1

Constraints :-
• 1 <= intervals.length <= 1000
• intervals[i].length == 2
• 0 <= li < ri <= 10^5
• All the given intervals are unique.
*/

#include <bits/stdc++.h>
using namespace std;

// Approach-1: Time Complexity : O(n^2) __ Space Complexity : O(1)
/*
>> Intuition
An interval [a, b] can only be covered by another interval that starts at or before a.
So the first thing we do is sort all intervals by their starting point.
    sort(intervals.begin(), intervals.end());
Now, for every interval intervals[i], we ask:
"Is there any interval that started before (or at the same point as) me and also ends after (or at the same point as) me?"
If yes, then intervals[i] is covered and shouldn't be counted.
If no such interval exists, then it must remain and must be counted.

So, after sorting, for each interval, 
we check if it can be covered by any other interval.
For that we iterate through all the intervals to look for a interval which can cover current interval.
If such interval is found, it means current interval can be covered, so it must not be counted, 
so we break out of this iteration and check for next interval whether it can be covered or not.

If no such interval exists which can cover current interval, we must count it as uncovered interval.
When all intervals are considered, we can return count.

>> Early exit condition when looking for interval which can cover current interval
After sorting, once we reach an interval whose start is greater than the current interval's start,
    intervals[j][0] > intervals[i][0]
every interval after j will also start later.
But to cover intervals[i], an interval must satisfy
    cover.start <= current.start
So none of the remaining intervals can possibly cover the current one.
At that point, we already know the current interval survives, so we stop searching.

Sort by starting point. For each interval, search only among intervals that start no later than it. 
If any of them also end no earlier than it, the interval is covered; otherwise, it remains. 
Once we encounter an interval that starts later, we can stop because no subsequent interval can ever cover the current one.

>> Time Complexity
• Sorting: O(n log n)
• for each interval, checking if it can be covered: O(n^2)
Overall: O(n^2)

>> Space Complexity
O(1) (ignoring the space used by sorting algorithm)
*/

// returns true if interval1 can cover interval2
bool canCover(vector<int>& interval1, vector<int>& interval2) {
    // since all given intervals are unique, two equal interval means we are checking the same interval
    if (interval1 == interval2) return false;

    return interval1[0] <= interval2[0] && interval1[1] >= interval2[1];
}

int removeCoveredIntervals1(vector<vector<int>>& intervals) {
    int n = intervals.size();
    int cnt = 0;

    sort(intervals.begin(), intervals.end());
    
    for (int i = 0; i < n; i++) {
        int j = 0;
        while (j < n) {
            if (canCover(intervals[j], intervals[i]))
                break;
            if (intervals[j][0] > intervals[i][0]) {
                cnt++;
                break;
            }
            j++;
        }
        if (j == n) cnt++;
    }
    
    return cnt;
}

// Approach-2: Time Complexity : O(n log n) __ Space Complexity : O(n)
/*
>> Intuition
Instead of asking,
"Can any previous interval cover the current interval?"
for every interval (which requires checking many intervals), 
we maintain a list containing only the intervals that have survived so far 
(i.e., intervals that are not covered by any earlier interval).

When processing a new interval, we only need to compare it with the most recent surviving interval.

Why?
Because after sorting by the start point, 
the last surviving interval's start will definitely be in range to be able to cover the next intervals,
so we just need to check its `end`, 
and the end of this last surviving interval will definitely be the largest among all other surving intervals 
(since intervals have been sorted, so a smaller end interval would have been covered).

>> How this algorithm works?
Initially,
    ans = first interval
This interval is obviously uncovered because nothing has appeared before it.

Now process each new interval.

-> Case 1: Same starting point :- [1,4] and [1,6]
The second interval is strictly better because it starts at the same place but extends farther.
So instead of keeping both, replace [1,4] by [1,6]
The smaller one is effectively discarded because any interval that [1,4] could cover, [1,6] can also cover.
    if (intervals[i][0] == ans[lastInd][0])
        ans[lastInd][1] = intervals[i][1];

-> Case 2: Last surviving interval covers current
Suppose: ans = [1,8], current = [3,5]
Since, 1 <= 3 and 8 >= 5
the current interval is covered.
So simply ignore it.

-> Case 3: Last surviving interval cannot cover current
Suppose: ans = [1,5], current = [3,8]
The current interval extends farther.
It cannot be covered by the last survivor, so it deserves to survive.
Append it.

>> Visual example
Sorted intervals
    [1,4]
    [2,3]
    [2,8]
    [5,7]

Start: ans = [1,4]
Process [2,3]
    [1,4] covers [2,3]
    Ignore.
    ans = [1,4]

Process [2,8]
    [1,4] cannot cover it
    Keep it.
    ans = [1,4]
          [2,8]

Process [5,7]
last survivor = [2,8]
covers [5,7]
Ignore.

Final answer
[1,4]
[2,8]

>> Time Complexity
• Sorting: O(n log n)
• Traversal: O(n)
Overall: O(n log n)

>> Space Complexity
O(n) to maintain the list of uncovered interrvals
*/

// returns true if interval1 can cover interval2
bool canCover(vector<int>& interval1, vector<int>& interval2) {
    return interval1[0] <= interval2[0] && interval1[1] >= interval2[1];
}

int removeCoveredIntervals2(vector<vector<int>>& intervals) {
    int n = intervals.size();
    
    sort(intervals.begin(), intervals.end());

    vector<vector<int>> ans;
    ans.push_back(intervals[0]);
    int lastInd = 0;
    
    for (int i = 1; i < n; i++) {
        if (intervals[i][0] == ans[lastInd][0])
            ans[lastInd][1] = intervals[i][1];
    
        else if (!canCover(ans[lastInd], intervals[i])) {
            ans.push_back(intervals[i]);
            lastInd++;
        }
    }

    return ans.size();
}

// Optimal Approach-1 : Time Complexity : O(n log n) __ Space Complexity : O(1)
/*
If we carefully analyze the last code, 
we will observe that we don't actually need to store all the uncovered intervals in a list.
We just needed the last surviving interval and that was enough to help us conclude whether a current interval survives or not.

So, we sort the intervals and consider the first interval (0th interval) to be a survived interval (uncovered interval).
We initialize count as 1 considering this 0th interval is a surviving interval.
We use a vector which denotes the last surviving interval (lastInterval)

Now, we traverse the intervals from index 1 using a variable i, so intervals[i] gives us the current interval
- If intervals[i]'s start == lastInterval's start, that means their end must be different (since all intervals are unique)
    Since we had previously sorted all the intervals, it means the current interval's end (i.e. intervals[i][1])
    would be greater than lastInterval's end, 
    so in a way, the lastInterval will be swallowed up by this current interval, 
    so, we must replace the end of lastInterval with this larger value to extend its range 
    and accept the fact that this current interval has covered lastInterval.

- Else If intervals[i]'s end > lastInterval's end:
    it means the current interval can't be covered by last interval 
    (we don't need to compare start values since due to sorting, we know that lastInterval's start <= currentInterval's start)
    So, we must increment count to add this newly encountered surviving interval, and update our lastInterval.

Return count when traversal ends.

>>Example: 
intervals = [ [1, 2], [1, 3], [1, 4], [2, 3], [2, 5], [3, 5], [3, 6] ]
Sorted intervals = [ [1, 2], [1, 3], [1, 4], [2, 3], [2, 5], [3, 5], [3, 6] ]

We assume that 0th interval is last surviving interval, lastInterval = [1, 2], and count = 1

Now, process the later intervals from index 1 to end.

- Process [1, 3]
lastInterval = [1, 2]
start of both last interval & current interval is same -> last interval is covered by current interval
so we must update our lastinterval without changing the count (since this [1,3] has replaced [1,2])
lastInterval becomes [1, 3]

- Process [1, 4]
lastInterval = [1, 3]
similar to last step, this time also we update lastInterval without changing count, lastInterval becomes [1, 4]

- Process [2, 3]
lastInterval = [1, 4]
this [2, 3] is covered by [1, 4], so we don't update count and neither make any changes to lastInterval 
as the range of lastInterval is already greater (that's why it is able to cover this current interval)

- Process [2, 5]
lastInterval = [1, 4]
Now, lastInterval can't cover this current interval since 4 < 5,
so we update count (count becomes 2) and lastInterval is also changed to extend its range, it becomes [2, 5]

- Process [3, 5]
[3, 5] is covered by [2, 5]

- Process [3, 6]
It is not covered by last interval, so update count (count becomes 3), and lastInterval becomes [3, 6]

Traversal ends, return count 3. 
*/
int removeCoveredIntervalsOptimal(vector<vector<int>>& intervals) {
    int n = intervals.size();
    
    sort(intervals.begin(), intervals.end());

    vector<int> lastInterval = intervals[0];
    int cnt = 1;           // 0th interval is the 1st surviving interval (or its end will be updated)

    for (int i = 1; i < n; i++) {
        if (intervals[i][0] == lastInterval[0])
            lastInterval[1] = intervals[i][1];
            // update the end of lastInterval becuase its range would be extended 
            // (since due to sorting, intervals[i][1] will be >= lastInterval's end)

        // if lastInterval's end is smaller than current interval's end, 
        // it means last interval can't cover this, so update count and make this interval as last surviving interval
        else if (lastInterval[1] < intervals[i][1]) {
            cnt++;
            lastInterval = intervals[i];
        }
    }

    return cnt;
}


// Optimal Approach : Time Complexity : O(n log n) __ Space Complexity : O(1)
/*
>> The key observation is: 
If we sort the intervals by:
    Starting point in ascending order
    Ending point in descending order (when starts are equal)
then any interval that is covered will always appear after the interval covering it.
thus, while traversing, we only need to keep track of the largest ending point seen so far.
    (since pervious start will always be smaller than current interval start, so only end matters
    if end of current interval is smaller than maxEnd, it will be easily covered by the previous intervals,
    only when end of current interval is greater than maxEnd, that's when we can't cover current interval,
    so we update maxEnd and increment count.)

>> Example: [[1,4], [3,6], [2,8]]
After sorting: [[1,4], [2,8], [3,6]]
Now:
[1,4] → farthest end = 4
[2,8] → end > 4 → not covered, update farthest end = 8
[3,6] → end <= 8 → covered
Remaining intervals = 2.

>> Why descending order for equal starts?
Consider: [1,4] and [1,5]
If we sort endings ascending: [ [1,4], [1,5] ]
we would process [1,4] first and count it, even though it is covered by [1,5].
So we sort as: [ [1,5], [1,4] ]
Now the covered interval comes later and can easily be detected.

The entire trick of this problem is realizing that after the special sort order, 
an interval is covered iff its end is not greater than the maximum end seen so far.

>> Algorithm
• Sort by start ↑, and if starts are equal, end ↓.
• Maintain maxEnd.
• If currentEnd <= maxEnd, the interval is covered.
• Otherwise, it is not covered, so count it and update maxEnd.

>> Time Complexity
• Sorting: O(n log n)
• Traversal: O(n)
Overall: O(n log n)

>> Space Complexity
O(1) (ignoring the space used by sorting algorithm)
*/
int removeCoveredIntervals(vector<vector<int>>& intervals) {
    // sort intervals (sort by start ascending order, if start equal, then end must be sorted descending)
    sort(intervals.begin(), intervals.end(), 
    [] (const vector<int>& a, const vector<int>& b) {
        if (a[0] == b[0])
            return a[1] > b[1];     // larger end first
        return a[0] < b[0];         // smaller start first
    } );

    int cnt = 0;
    int maxEnd = -1;
    
    for (auto& interval : intervals) {
        if (interval[1] > maxEnd) {
            cnt++;
            maxEnd = interval[1];
        }
    }

    return cnt;
}

int main() {
    return 0;
}