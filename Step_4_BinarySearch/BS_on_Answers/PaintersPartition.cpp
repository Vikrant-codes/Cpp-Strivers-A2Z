/*
GFG - The Painter's Partition Problem-II -- Hard

Given an array arr[] where each element denotes the length of a board, and an integer k representing the number of painters available. 
Each painter takes 1 unit of time to paint 1 unit length of a board.
Determine the minimum amount of time required to paint all the boards, 
under the constraint that each painter can paint only a contiguous sequence of boards (no skipping or splitting allowed).

Examples :-

Input: arr[] = [5, 10, 30, 20, 15], k = 3 __ Output: 35
Explanation: The optimal allocation of boards among 3 painters is - 
Painter 1 → [5, 10] → time = 15
Painter 2 → [30] → time = 30
Painter 3 → [20, 15] → time = 35
Job will be done when all painters finish i.e. at time = max(15, 30, 35) = 35

Input: arr[] = [10, 20, 30, 40], k = 2 __ Output: 60
Explanation: A valid optimal partition is - 
Painter 1 → [10, 20, 30] → time = 60
Painter 2 → [40] → time = 40
Job will be complete at time = max(60, 40) = 60

Input: arr[] = [100, 200, 300, 400], k = 1 __ Output: 1000
Explanation: There is only one painter, so the painter must paint all boards sequentially. 
The total time taken will be the sum of all board lengths, i.e., 100 + 200 + 300 + 400 = 1000.

Constraints :- 1 ≤ arr.size() ≤ 10^5 __ 1 ≤ arr[i] ≤ 10^4 __ 1 ≤ k ≤ 10^5
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach (Binary Search) :- Time Complexity : O(n * log(sum - max)) __ Space Complexity : O(1)
/*
The solution to this problem is also similar to the Book Allocation (Allocate Minimum Pages) & Split Array Largest Sum problem. 
We keep low as max(arr) and high as sum(arr). These values also connect to cases when no. of painters (k) == 1 & when k == no of boards (arr.size())
When k == 1 : Only painter is available so he must paint all the boards then the time taken will be equal to sum (arr) i.e. high
When k == arr.size() : Each painter can be assigned one board so maximum time taken by any of the painter is max(arr) 

We start search space with low as max(arr) & high as sum(arr). We find mid and check whether it's possible to paint all the boards considering mid as 
the time limit with the available no of painters. The isPossible() function checks this feasibility. If 'mid' time limit is feasible we update high 
to check the feasibility of smaller time limits. If it's not then we update low to find a feasible solution.  

--> isPossible(vector<int>& arr, int k, int lim) 
To check whether it's possible to paint all the boards within time limit 'lim' with k no of painters, we first find the no of painters required to 
paint the all the boards with time limit 'lim'. Assume this no of painters required is x. Then the time limit 'lim' is feasible only if 
the no of painters required <= no of painters available i.e. if x <= k.
*/ 

bool isPossible(vector<int>& arr, int k, int lim) {
    int cnt = 1, sum = 0;
    for(int x : arr) {
        if (sum + x > lim) {
            cnt ++;
            sum = x;
        }
        else sum += x;
    }
    return cnt <= k;
}

int minTime(vector<int>& arr, int k) {
    int low = *max_element(arr.begin(), arr.end());
    int high = accumulate(arr.begin(), arr.end(), 0);

    if (k == 1) return high; // If only one painter then he must paint all boards so time taken will be equal to sum(arr)
    if (k == arr.size()) return low; // Each painter can be assigned one board so maximum time taken by any of the painter is max(arr)

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (isPossible(arr, k, mid)) high = mid - 1;
        else low = mid + 1;
    }
    return low;
}

int main() {
    vector<int> arr = {5, 10, 30, 20, 15};
    int k = 3;
    cout << "Minimum time required to paint all boards: " << minTime(arr, k) << endl;

    return 0;
}