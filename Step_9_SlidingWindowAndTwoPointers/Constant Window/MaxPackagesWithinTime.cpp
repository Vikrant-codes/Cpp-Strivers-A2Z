/*
GFG - Maximum Packages within Time : Easy

A delivery agent has to deliver packages at locations arranged in a line. 
The number of packages at the ith location is given by arr[i].
- The agent can start at any location and can only visit consecutive locations.
- Visiting each location takes 1 unit of time.

Given arr[] and totalTime, find the maximum number of packages the agent can deliver within totalTime.

Examples :-

Input: arr[] = [2, 1, 3, 5, 0, 1, 4], totalTime = 3
Output: 9
Explanation: The agent can visit three consecutive locations. 
Starting from the second location, it delivers arr[1] + arr[2] + arr[3] = 1 + 3 + 5 = 9 packages.

Input: arr[] = [1, 6, 2, 5, 3, 4], totalTime = 2
Output: 8
Explanation: The agent can visit two consecutive locations. 
Starting from the second location, it delivers arr[1] + arr[2] = 6 + 2 = 8 packages. 
Starting from the fourth location gives arr[3] + arr[4] = 5 + 3 = 8 packages. Hence, the maximum is 8 packages.

Constraints :-
• 1 ≤ arr.size(), totalTime ≤ 10^5
• 0 ≤ arr[i] ≤ 10^3
*/

#include <bits/stdc++.h>
using namespace std;

/*
>> Key Observation

To maximize the total number of packages delivered within the given time, 
the agent should choose totalTime consecutive locations that collectively have the highest number of packages. 
Since visiting each location takes 1 unit of time, 
this boils down to finding the maximum sum among all subarrays of size totalTime.
*/

// Brute Force Approach: Time Complexity : O(n x k) __ Space Complexity : O(1)
/*
Try every possible starting location and calculate the sum of the next totalTime locations. Return the maximum sum.

>> Complexity Analysis:
- Time: O(n x k), where k = totalTime.
- Space: O(1)
*/
int maxPackagesBrute(vector<int>& arr, int totalTime) {
    int n = arr.size();

    if(totalTime >= n)
        return accumulate(arr.begin(), arr.end(), 0);

    int maxi = 0;

    for(int i = 0; i <= n - totalTime; i++) {
        int sum = 0;

        for(int j = i; j < i + totalTime; j++) {
            sum += arr[j];
        }

        maxi = max(maxi, sum);
    }

    return maxi;
}

// Optimal (Fixed Size Sliding Window): Time Complexity : O(n) __ Space Complexity : O(1)
/*
We can maintain a fixed-sized window of totalTime elements and calculate its sum. 
Since we need to maximize the total packages delivered, we maintain the maximum window sum (maxi) seen so far.

Instead of recalculating the sum whenever the window moves, 
we can efficiently obtain the current window's sum by considering the elements entering and leaving the window. 
When we slide the window one position to the right, 
we add the newly included element (arr[r]) and subtract the element that is no longer part of the window (arr[l]). 
We then update maxi with the current window sum and continue sliding until we have considered all possible windows.

>> Complexity Analysis:
- Time Complexity: O(n) — Both pointers traverse the array at most once.
- Space Complexity: O(1) — Only a constant number of variables are used.
*/

// My implementation
int maxPackages1(vector<int>& arr, int totalTime) {
    int n = arr.size();
    
    int ind = 0, sum = 0;
    while (ind < n && ind < totalTime) {
        sum += arr[ind]; 
        ind++;
    }
    
    // totalTime >= array size
    if (ind == n) return sum;
    
    int maxSum = sum;
    
    int i = 0, j = ind;
    
    while (j < n) {
        sum = sum + arr[j] - arr[i];
        maxSum = max(maxSum, sum);
        i++; j++;
    }
    
    return maxSum;
}

int maxPackages2(vector<int>& arr, int totalTime) {
    int n = arr.size();

    if(totalTime >= n)
        return accumulate(arr.begin(), arr.end(), 0);

    int l = 0, r = 0;
    int sum = 0, maxi = 0;

    while(r < n) {
        sum += arr[r];

        if(r - l + 1 == totalTime) {
            maxi = max(maxi, sum);
            sum -= arr[l];
            l++;
        }

        r++;
    }

    return maxi;
}

int maxPackages3(vector<int>& arr, int totalTime) {
    int n = arr.size();

    if(totalTime >= n)
        return accumulate(arr.begin(), arr.end(), 0);

    int sum = 0;

    for(int i = 0; i < totalTime; i++) {
        sum += arr[i];
    }

    int maxi = sum;

    for(int i = totalTime; i < n; i++) {
        sum += arr[i] - arr[i - totalTime];
        maxi = max(maxi, sum);
    }

    return maxi;
}

int main() {
    return 0;
}