/*
Leetcode - 2078. Two Furthest Houses With Different Colors : Easy

There are n houses evenly lined up on the street, and each house is beautifully painted. 
You are given a 0-indexed integer array colors of length n, where colors[i] represents the color of the ith house.
Return the maximum distance between two houses with different colors.
The distance between the ith and jth houses is abs(i - j), where abs(x) is the absolute value of x.

Examples :-

Input: colors = [1,1,1,6,1,1,1] __ Output: 3
Explanation: In the above image, color 1 is blue, and color 6 is red.
The furthest two houses with different colors are house 0 and house 3.
House 0 has color 1, and house 3 has color 6. The distance between them is abs(0 - 3) = 3.
Note that houses 3 and 6 can also produce the optimal answer.

Input: colors = [1,8,3,8,3] __ Output: 4
Explanation: In the above image, color 1 is blue, color 8 is yellow, and color 3 is green.
The furthest two houses with different colors are house 0 and house 4.
House 0 has color 1, and house 4 has color 3. The distance between them is abs(0 - 4) = 4.

Input: colors = [0,1] __ Output: 1
Explanation: The furthest two houses with different colors are house 0 and house 1.
House 0 has color 0, and house 1 has color 1. The distance between them is abs(0 - 1) = 1.

Constraints :-
- n == colors.length
- 2 <= n <= 100
- 0 <= colors[i] <= 100
- Test data are generated such that at least two houses have different colors.
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach : Time Complexity : O(n^2) __ Space Complexity : O(1)
/*
Approach :-
We want the maximum distance between two houses with different colours.
The naive approach is to try out every pairs of houses,
if the houses are of different colours, find the distance between them.
Use a variable to keep track of this maximum distance.

Idea:
- Try every possible pair (i, j) where i < j.
- If colors are different → compute distance j - i.
- Keep track of the maximum distance.
*/
int maxDistanceNaive(vector<int>& colors) {
    int n = colors.size();
    int ans = -1;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (colors[i] != colors[j]) 
                ans = max(ans, j - i);
        }
    }
    
    return ans;
}

// Optimal Approach (Greedy 2 pointers approach) : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Observations :-
We need the maximum distance between two different coloured houses... 
For all pairs, this difference would be maximum when one of the two houses is at the extreme ends (left or right end)
The maximuim distance between any two array elements (house pairs) would be the difference between both extreme ends,
i.e., when i = 0 & j = n - 1... this difference = j - i = n - 1 - 0 = n - 1.

So, if the left end house (0th element) is different coloured than right end house (n-1th element), then we can directly 
return 'n-1' as the maximum required distance, but this is not always the case since the two end houses can be same coloured.

In this case we move inwards from both ends and find the first house which is different coloured than the extreme ends houses.
When we find the first different coloured house, then the maximum distance would be 
the maximum of the difference of position of this house from the two extreme ends. 
We can return this as the answer.

Example -> [1, 1, 1, 2, 3, 1, 1, 1, 1]
The different colours in this array are {1, 2, 3}, there are many possible pairs but the one with the maximum distance is 
pair of indices (3, 8). 
Here, one pair house is situated at the extreme end (right end) and other one is stretched far to it nearer the second end.
Choosing both houses which are closer to center will only decrease the difference, so we should look for houses 
which are closer to opposite end.

Both the left end & right end house are same coloured, so we need to move from both ends simultaneously 
and find the first different coloured house. 

We use two pointers 'i' & 'j' to move inwards from both ends and find the first different coloured house.

While comparing for different coloured house, 
we can take either of the left house or right house for reference as both colours are same.

We are moving from both ends simultaneously because if we just move from one end, 
then the first different coloured house is not guaranteed to be at the optimal answer position. 
So, in that case, we would need to traverse the whole array and find the maximum distance for all different coloured houses.

We know that the maximum distance house would be the one which is nearer to either of the two extreme ends of the array
(since in this way the index difference between it and either the left or right end house would be maximized).
So, we use 2 pointers and find the first different coloured house which is nearer to the end and 
this house would be our pair house.
If this house is closer to right end, then maximum answer = house position - 0 (position of left house)
If this house is closer to left end, then maximum answer = (n-1) (position of right house) - house position
*/

/*
Goal:
We need the maximum distance between two houses having different colors.

Key Observation:
The maximum possible distance between any two indices is:
    n - 1  (i.e., between index 0 and index n-1)

So naturally, we should try to involve the extreme ends of the array.

------------------------------------------------------------

Case 1:
If colors[0] != colors[n-1]:
    → These two endpoints already have different colors
    → Distance = n - 1 (maximum possible)
    → Return immediately

------------------------------------------------------------

Case 2:
If colors[0] == colors[n-1]:
    → Endpoints cannot form a valid pair
    → So we must look for another house with a different color

Now the question becomes:
    Which house should we pair with an endpoint to maximize distance?

------------------------------------------------------------

Key Greedy Insight:
To maximize distance, one index should remain at an extreme (0 or n-1),
and the other should be as far as possible from it.

So we try:
    1. Fix left end (index 0), move from right inward
    2. Fix right end (index n-1), move from left inward

------------------------------------------------------------

Why move from BOTH ends?

Because:
- The optimal answer will come from the house which is
  "closest to either end" but has a different color.
- That ensures maximum stretch with the opposite end.

------------------------------------------------------------

Approach:

Use two pointers:
    i → starts from left (1 → n-1)
    j → starts from right (n-2 → 0)

Since colors[0] == colors[n-1], we can use colors[0] as reference.

------------------------------------------------------------

Check from left side:
    Find first index i such that:
        colors[i] != colors[0]

    Then distance = (n - 1) - i
    (pair this house with right end)

------------------------------------------------------------

Check from right side:
    Find first index j such that:
        colors[j] != colors[0]

    Then distance = j
    (pair this house with left end)

------------------------------------------------------------

Why this works:

- Any pair formed completely inside the array
  will always have smaller distance than using an endpoint.

- So we only need to consider pairs involving index 0 or n-1.

- Among those, the best pair is formed with the
  first different-colored house encountered from either side,
  because it maximizes the index gap.

------------------------------------------------------------

Final Answer:
Return the first valid maximum distance found while scanning
from both ends.

Time Complexity: O(n)
Space Complexity: O(1)
*/

/*
The maximum distance is achieved when we use the endpoints of the array.

- If colors[0] != colors[n-1], return n - 1 directly.
- Otherwise, endpoints are same, so we:
    // - Scan from left to find first index i where colors[i] != colors[0] → distance = n - 1 - i
    // - Scan from right to find first index j where colors[j] != colors[0] → distance = j
    // - Return the maximum of these.
    Instead of scanning for both ends one at a time, we can simultaneously traverse from both ends and find the first 
    different coloured house (as this would be the nearest to either of the two ends and this will be the answer pair house).
- return the difference of this house from the farthest end.

This works because the optimal pair must include at least one endpoint to maximize distance.
*/

int maxDistance(vector<int>& colors) {
    int n = colors.size();
    if (colors[0] != colors[n-1]) return n-1;

    int i = 1, j = n-2;
    while (i <= j) {
        if (colors[i] != colors[0]) return (n-1-i);
        if (colors[j] != colors[0]) return (j);
        i++;
        j--;
    }
    return -1;
}

int main() {
    return 0;
}