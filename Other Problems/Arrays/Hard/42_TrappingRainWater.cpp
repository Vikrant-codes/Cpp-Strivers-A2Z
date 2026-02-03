/*
Leetcode - 42. Trapping Rain Water

Given n non-negative integers representing an elevation map where the width of each bar is 1, 
compute how much water it can trap after raining.

Examples :-  

Input: height = [0,1,0,2,1,0,1,3,2,1,2,1] __ Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. 
In this case, 6 units of rain water (blue section) are being trapped.

Input: height = [4,2,0,3,2,5] __ Output: 9

Constraints :-
- n == height.length
- 1 <= n <= 2 * 10^4
- 0 <= height[i] <= 10^5
*/

#include <bits/stdc++.h>
using namespace std;

// Approach1 :- Time Complexity : O(3n) __ Space Complexity : O(2n)
/*
To be able for a building to trap water, it must have two buildings bigger than it on both sides (left & right), then only 
it can trap water. So, A building will trap water only if it has bigger building to its left and right. 
If there is no bigger building on the left or on the right or both, 
then the current building won't trap water and the water will run to edges. 

So, if we are at some building height[i], then we can find how much water it will trap, by checking for the maximum building 
on its left and on its right. Assume the maximum buildings are leftMax & rightMax. 
Now to trap water, the current building i.e. height[i], must be smaller than both leftMax & rightMax. 

Now say it's smaller than leftMax & rightMax, now how to know how much water it will trap.
The current builiding is bounded between leftMax & rightMax. Water will fill upto the point till 
it reaches the peak of either leftMax or rightMax. After reaching that peak water will overflow to the edges.
So, we need to check for the minimum of leftMax & rightMax, since water will fill only upto this point  
and then the trapped water will be equal to that minimum - current building height. 
i.e. :- trapped_water = min(leftMax, rightMax) - height[i]

So, to get the total trapped water, we can use these conditions to get water trapped by current building and then sum it up.
i.e. 
for (i -> 0 to n-1) {
    if (height[i] < leftMax && height[i] < rightMax) {
            total_water += min(leftMax, rightMax) - height[i];
        }
}

Now, how to figure out leftMax & rightMax ?
For this we can use two arrays, PrefixMax & SuffixMax, which will keep track of the maximum building 
from the left end (PrefixMax) & from the right end (SuffixMax). 
PrefixMax[i] will tell us the maximum building from height[0] to height[i] i.e. the left Maximum, i.e. leftMax
and SuffixMax[i] will tell us the maximum building from height[i] to height[n-1] i.e. the right Maximum, i.e. rightmax.
*/
int trap1(vector<int>& height) {
    int n = height.size();

    vector<int> PrefixMax(n), SuffixMax(n);
    PrefixMax[0] = height[0];
    for (int i=1; i<n; i++) {
        PrefixMax[i] = max(PrefixMax[i-1], height[i]);
    }
    
    SuffixMax[n-1] = height[n-1];
    for (int i=n-2; i>=0; i--) {
        SuffixMax[i] = max(SuffixMax[i+1], height[i]);
    }
    
    int total_water = 0;
    for (int i=0; i<n; i++) {
        int leftMax = PrefixMax[i], rightMax = SuffixMax[i];
        if (height[i] < leftMax && height[i] < rightMax) {
            total_water += min(leftMax, rightMax) - height[i];
        }
    }
    
    return total_water;
}

// Modified Approach1 :- Time Complexity : O(2n) __ Space Complexity : O(n)
/*
We want to optimize the space complexity and if we think about PrefixMax, we don't actually need a dedicated array to keep 
track of leftMaximum since this can be done during traversal. 
We can use a variable named leftMax which will store the height of maximum building upto current building.
This way, we can save O(n) space by not using PrefixSum array & O(n) time as we won't have to build the PrefixSum array beforehand. 
*/
int trap2(vector<int>& height) {
    int n = height.size();

    vector<int> SuffixMax(n);
    SuffixMax[n-1] = height[n-1];
    for (int i=n-2; i>=0; i--) {
        SuffixMax[i] = max(SuffixMax[i+1], height[i]);
    }
    
    int total_water = 0, leftMax = 0;
    for (int i=0; i<n; i++) {
        int leftMax = max(leftMax, height[i]);
        int rightMax = SuffixMax[i];
        if (height[i] < leftMax && height[i] < rightMax) {
            total_water += min(leftMax, rightMax) - height[i];
        }
    }
    
    return total_water;
}

// Optimal Approach (Two Pointers) :- Time Complexity : O(n) __ Space Complexity : O(1)
/*
🌧️ Trapping Rain Water — Intuition (Two-Pointer Approach)

“Water above a bar = min(max_left, max_right) – height[i]”
This formula is correct BUT computing max_left and max_right for each bar is either:
• O(n²) brute force, or
• O(n) space if using prefix/suffix arrays.
There is a better way.

✅ The Key Intuition (Why Two Pointers Work)
Imagine standing at the left end and right end of the bars:
• You know that the shorter side always limits the water.
• Because water spills from the shorter boundary, not the taller boundary.
We move the two pointers l & r, in such way that the pointer pointing at smaller building moves first.
So, if l building is smaller than r, we move l and before moving we check for trapped water. 
Similarly, if r is smaller, then we move r and check for trapped water there.
So:
👉 If left bar is smaller, water on the left depends only on leftMax.
👉 If right bar is smaller, water on the right depends only on rightMax.

You do not need the max on the opposite side yet because:
    As long as one side (left or right) is strictly shorter,
    that side’s max determines the trapping capacity,
    since the other side is guaranteed to have a bar ≥ current height.
This is the entire heart of the solution.

🧠 Visual Intuition
Think like this:

Case 1: height[l] < height[r]

• Right boundary is taller → it cannot be the limiting boundary right now.
• Only left side matters.

There are two possibilities:
1. height[l] < leftMax
→ Water can be trapped here.
→ Add leftMax - height[l]. (trapped water)
2. height[l] >= leftMax
→ No water here; update leftMax.

Then move left pointer rightwards.

Case 2: height[r] <= height[l]

• Left boundary is taller → it cannot be the limiting boundary.
• Only right side matters.

Check with the rightMax:
1. height[r] < rightMax
→ Water trapped = rightMax - height[r].
2. height[r] >= rightMax
→ Update rightMax.

Move the right pointer leftwards.

🧩 Why This Works (Core Logic)

The side with the smaller height always decides the trapped water, because:
• Water level cannot be higher than where it leaks.
• The shorter side is the bottleneck.
Thus:
• When height[l] < height[r], right side is irrelevant → left side is safe to evaluate.
• When height[r] <= height[l], left side is irrelevant → right side is safe to evaluate.
This allows a single sweep with two pointers.

⏱️ Time & Space Complexity
| Method                | Time  | Space |
| --------------------- | ----- | ----- |
| Two-pointer (optimal) | O(n)  | O(1)  |
| Prefix/suffix arrays  | O(n)  | O(n)  |
| Brute force           | O(n²) | O(1)  |
*/
int trap(vector<int>& height) {
    int n = height.size();
    int total = 0, leftMax = 0, rightMax = 0;
    int l = 0, r = n-1; 

    while (l < r) {
        if (height[l] < height[r]) {
            if (leftMax > height[l]) {
                total += leftMax - height[l];
            }
            else leftMax = height[l];
            l++;
        }
        else {
            if (rightMax > height[r]) {
                total += rightMax - height[r];
            }
            else rightMax = height[r];
            r--;
        }
    }

    return total;
}

int main() {
    return 0;
}