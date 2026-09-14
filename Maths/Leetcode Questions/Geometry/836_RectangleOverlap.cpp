/*
Leetcode - 836. Rectangle Overlap : Easy

An axis-aligned rectangle is represented as a list [x1, y1, x2, y2], 
where (x1, y1) is the coordinate of its bottom-left corner, and (x2, y2) is the coordinate of its top-right corner. 
Its top and bottom edges are parallel to the X-axis, and its left and right edges are parallel to the Y-axis.

Two rectangles overlap if the area of their intersection is positive. 
To be clear, two rectangles that only touch at the corner or edges do not overlap.

Given two axis-aligned rectangles rec1 and rec2, return true if they overlap, otherwise return false.

Examples :-

Input: rec1 = [0,0,2,2], rec2 = [1,1,3,3]
Output: true

Input: rec1 = [0,0,1,1], rec2 = [1,0,2,1]
Output: false

Input: rec1 = [0,0,1,1], rec2 = [2,2,3,3]
Output: false
 
Constraints :-
• rec1.length == 4
• rec2.length == 4
• -10^9 <= rec1[i], rec2[i] <= 10^9
• rec1 and rec2 represent a valid rectangle with a non-zero area.
*/

#include<bits/stdc++.h>
using namespace std;

// *My First Approach

// checks whether rec2 end-points lie inside of rec1 or contain rec1 itself
bool pointsLie(vector<int>& rec1, vector<int>& rec2) {
    int x1 = rec1[0], y1 = rec1[1], x2 = rec1[2], y2 = rec1[3];
    int x3 = rec2[0], y3 = rec2[1], x4 = rec2[2], y4 = rec2[3];

    return ( (x1 <= x3 && x3 < x2) || (x1 < x4 && x4 <= x2) || (x3 <= x1 && x4 >= x2) ) 
                && 
           ( (y1 <= y3 && y3 < y2) || (y1 < y4 && y4 <= y2) || (y3 <= y1 && y4 >= y2) );
}

bool isRectangleOverlap1(vector<int>& rec1, vector<int>& rec2) {
    return pointsLie(rec1, rec2) || pointsLie(rec2, rec1);
}


// *The problem becomes easier to deal with if we think about the non-overlapping cases
bool isRectangleOverlap2(vector<int>& rec1, vector<int>& rec2) {
    int x1 = rec1[0], y1 = rec1[1], x2 = rec1[2], y2 = rec1[3];
    int x3 = rec2[0], y3 = rec2[1], x4 = rec2[2], y4 = rec2[3];
    
    bool notOverlap = (x3 >= x2) || (x4 <= x1) || (y3 >= y2) || (y4 <= y1);

    return !notOverlap;
}

// ChatGPT's solutions

/*
The key observation is: for the intersection to have positive area, 
the rectangles must overlap on both the X-axis and Y-axis.

For two 1D intervals [x1, x2] and [x3, x4], they have positive overlap if:
| max(x1, x3) < min(x2, x4)

We need the same condition for both dimensions.

?>> Why max(x1, x3) < min(x2, x4)
Suppose we have two 1D intervals:
Interval A: [x1 -------- x2]
Interval B: [x3 -------- x4]

The two intervals overlap if the start of the `later-starting` interval comes before the end of the `earlier-ending` interval.

First, consider the two possible starting orders
We don't know which interval starts first, so there are two cases.

Case 1: A starts before B, i.e., x1 <= x3
So:
    A: x1 ---------------- x2
    B:       x3 ---------------- x4
For them to overlap, B must start before A ends: x3 < x2
| Therefore: x1 <= x3 < x2

Case 2: B starts before A, i.e., x3 < x1
So:
    B: x3 ---------------- x4
    A:       x1 ---------------- x2
Now A must start before B ends: x1 < x4
| Therefore: x3 <= x1 < x4

So overall, we could write: `(x1 <= x3 && x3 < x2) || (x3 <= x1 && x1 < x4)`

Now where does max / min come from?
Instead of explicitly asking: "Which interval starts first?"
we can let max() answer that for us.

-> max(x1, x3)
x1 and x3 are the starting points.

Therefore: max(x1, x3) gives us the later starting point.
That is exactly where the intersection starts.

For example:
A: 0 -------- 7
B:     3 -------- 10
max(0, 3) = 3 => The intersection starts at 3.

-> min(x2, x4)
x2 and x4 are the ending points.

Therefore: min(x2, x4) gives us the earlier ending point.
That is exactly where the intersection ends.

A: 0 -------- 7
B:     3 -------- 10
min(7, 10) = 7. The intersection ends at 7.

So: intersection = [max(x1,x3), min(x2,x4)]

And for the intersection to actually have positive length: 
| max(x1,x3) < min(x2,x4)

We can think of max(start) and min(end) independently in terms of four combinations.

>> Case 1: max(x1,x3) = x1
    This means: x1 >= x3. So A starts later.

    B: x3 ---------------- x4
    A:       x1 ---------------- x2

    Now there are two possibilities.
        -> Sub-case 1: min(x2,x4) = x2, i.e, A ends earlier.
            B: x3 ------------------------- x4
            A:       x1 -------- x2

            The intersection is: [x1, x2]
            And since A is a valid interval: x1 < x2
            So they always overlap.
            This is the case where A is completely inside B.

        -> Sub-case 2: min(x2,x4) = x4, i.e., B ends earlier.
            B: x3 ---------------- x4
            A:       x1 ------------------------- x2

            The intersection is:[x1, x4]
            Therefore, they overlap iff: x1 < x4

>> Case 2: max(x1,x3) = x3
    This means: x3 >= x1. So B starts later.

    A: x1 ---------------- x2
    B:       x3 ---------------- x4

    Again, two possibilities.
        -> Sub-case 1: min(x2,x4) = x2, i.e., A ends earlier.
            A: x1 ---------------- x2
            B:       x3 ------------------------- x4

            The intersection is: [x3, x2]
            Therefore: x3 < x2

        -> Sub-case 2: min(x2,x4) = x4, i.e., B ends earlier.
            A: x1 ------------------------- x2
            B:       x3 -------- x4

            The intersection is: [x3, x4]
            And since B is a valid interval: x3 < x4
            So they always overlap.
            This is the case where B is completely inside A.

So the beautiful part is
Instead of writing all those cases: (x1 <= x3 < x2) || (x3 <= x1 < x4)
we can identify two things:
max(x1, x3) → later starting point
min(x2, x4) → earlier ending point

Then simply ask: later start < earlier end ?
If yes → there is some positive-length interval between them → overlap.
If no → the later start is at or after the earlier end → no positive-length overlap.

Therefore: `max(x1, x3) < min(x2, x4)` helps us determine whether the two intervals overlap.
            Much like the condition `(x1 <= x3 < x2) || (x3 <= x1 < x4)`
*/
bool isRectangleOverlap3(vector<int>& a, vector<int>& b) {
    // Two 1D intervals [a,b] & [c,d] overlap if max(a, c) < min(b, d)
    bool xOverlap = max(a[0], b[0]) < min(a[2], b[2]);

    bool yOverlap = max(a[1], b[1]) < min(a[3], b[3]);
    
    return xOverlap && yOverlap;
}

/*
Two rectangles do not overlap if one is completely:
- to the left of the other
- to the right of the other
- above the other
- below the other

So, if two rectangles don't overlap, we return false. Otherwise they overlap, so return true.
*/
bool isRectangleOverlap4(vector<int>& a, vector<int>& b) {
    // one rectangle is completely left/right to the other
    if (a[2] <= b[0] || b[2] <= a[0]) return false;

    // one rectangle is completely abolve/below the other
    if (a[3] <= b[1] || b[3] <= a[1]) return false;
    
    return true;
}

int main() {
    return 0;
}