/*
Leetcode - 11. Container With Most Water : Medium

You are given an integer array height of length n. 
There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).
Find two lines that together with the x-axis form a container, such that the container contains the most water.
Return the maximum amount of water a container can store.
Notice that you may not slant the container.

Examples :-

Input: height = [1,8,6,2,5,4,8,3,7] __ Output: 49
Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. 
In this case, the max area of water (blue section) the container can contain is 49.

Input: height = [1,1] __ Output: 1
 
Constraints :-
- n == height.length
- 2 <= n <= 10^5
- 0 <= height[i] <= 10^4
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach :- Time Complexity : O(n^2) __ Space Complexity : O(1)
int maxArea(vector<int>& height) {
    int ans = 0;
    int n = height.size();

    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            int width = j - i;
            int h = min(height[i], height[j]);

            int waterAmount = width * h;

            ans = max(ans, waterAmount);
        }
    }

    return ans;
}

// Optimal Approach (Two Pointers) :- Time Complexity : O(n) __ Space Complexity : O(1)
int maxArea(vector<int>& height) {
    int left = 0, right = height.size()-1;
    int ans = 0;

    while (left < right) {
        int width = right - left;                  // width of current container
        int h = min(height[right], height[left]);  // height of current container (min. of both edges)
        
        int waterAmount = width * h;               // water amount capacity of current container 

        if (waterAmount > ans) ans = waterAmount;  // store the max capacity
    
        if (height[left] < height[right]) left++;
        else right--;
    }
    
    return ans;
}

int maxArea2(vector<int>& height) {
    int left = 0, right = height.size()-1;
    int ans = 0;

    while (left < right) {
        int width = right - left;
    
        int h = 0;
        // find the minimum height of container side edge, and move the corresponding pointer ahead
        if (height[left] < height[right]) {
            h = height[left];
            left++;
        }
        else {
            h = height[right];
            right--;
        }
    
        int waterAmount = width * h;
        if (waterAmount > ans) ans = waterAmount;
    }
    
    return ans;
}

int maxArea3(vector<int>& height) {
    int left = 0, right = height.size()-1;
    int ans = 0;
    while (left < right) {
        int width = right - left;
        int h = height[left] < height[right] ? height[left++] : height[right--];
        
        int waterAmount = width * h;
        
        if (waterAmount > ans) ans = waterAmount;
    }

    return ans;
}

int main() {
    return 0;
}