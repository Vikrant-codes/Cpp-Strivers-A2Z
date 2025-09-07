/*
GFG - Aggressive Cows : Medium

You are given an array with unique elements of stalls[], which denote the positions of stalls. 
You are also given an integer k which denotes the number of aggressive cows. 
The task is to assign stalls to k cows such that the minimum distance between any two of them is the maximum possible.

Examples :- 

Input: stalls[] = [1, 2, 4, 8, 9], k = 3 __ Output: 3
Explanation: The first cow can be placed at stalls[0], 
the second cow can be placed at stalls[2] and 
the third cow can be placed at stalls[3]. 
The minimum distance between cows in this case is 3, which is the largest among all possible ways.

Input: stalls[] = [10, 1, 2, 7, 5], k = 3 __ Output: 4
Explanation: The first cow can be placed at stalls[0],
the second cow can be placed at stalls[1] and
the third cow can be placed at stalls[4].
The minimum distance between cows in this case is 4, which is the largest among all possible ways.

Input: stalls[] = [2, 12, 11, 3, 26, 7], k = 5 __ Output: 1
Explanation: Each cow can be placed in any of the stalls, as the no. of stalls are exactly equal to the number of cows.
The minimum distance between cows in this case is 1, which is the largest among all possible ways.

Constraints :- 2 ≤ stalls.size() ≤ 10^6 __ 0 ≤ stalls[i] ≤ 10^8 __ 2 ≤ k ≤ stalls.size()
*/

#include <bits/stdc++.h>
using namespace std;

// Binary Search Approach : Time Complexity : O(n log n) + O(n * log(maxDistance)), maxDistance = stalls[n-1] - stalls[0]
/*
Time Complexity Analysis :-
Sorting: O(n log n)
Binary Search: O(log(maxDistance))
Each canPlace: O(n)
Overall: O(n log(maxDistance)) + O(n log n)
*/

/*
Approach :- 
The minimum possible distance is 1 so low = 1, if k is 2 then only 2 cows need to be placed and then the maximum Possible distance would be the 
differnce : max(stalls) - min(stalls) or stalls[n-1] - stalls[0] (when stalls is sorted). 

So we keep low = 1, high = stalls[n-1] - stalls[0] and apply binary Search. 
Find mid and if it's possible to place k cows keeping mid as the min dis between two adjacent cows then we do low = mid + 1 to get maximum possible. 
Else if it's not possible then do high = mid - 1 to reduce search space so to find feasible solutions.

Return high after the loop ends. This high will point to the maximum possible minimum distance between cows. 
*/

/*
canPlace(vector<int>& stalls, int k, int dis) function --> 

checks whether it is possible to place k cows in stalls keeping minimum distance between them as dis. 
To check so we need the stalls array to be sorted so that it is easier to check for the placing of cows in increasingly sorted array.

To do so, we keep a place variable that will store the position/index of the stall in which the last cow was placed. 
Initially, we keep 1st cow in stalls[0] since it's the smallest stall so it the best choice to place the first cow to allow placing other cows efficiently
So intially place = 0 and cnt variable denotes the count of cows that have been assigned stalls. Initially it's 1 since 1st cow is assigned to stalls[0]

We want to place cows in such a way that the minimum distance between adjacent cows is 'dis' so we loop through the stalls and find the first index 
that is at distance greater than / equal to 'dis'. Once such stall is found, we place 1 cow in that stall and increment cow and update the place variable
to current index. Now we will find a stall that is at appropriate distance from this newly updated 'place' stall. 
When cnt becomes equal to k we return True else return False.   
*/
bool canPlace(vector<int>& stalls, int k, int dis) {
    int place = 0;      // place : placement index of the last cow placed, initially 1 cow is placed at 0 index
    int cnt = 1;        // cnt : total no of placed cows, initially 1 cow is placed at 0 so cnt = 1

    for(int i=1; i < stalls.size(); i++) {
        if (stalls[i] - stalls[place] >= dis) {
            cnt++;
            place = i;
        }
        if (cnt == k) return true;      // if cnt becomes equal to k that means placing cows at distance dis is possible
    }
    return false;                       // cows can't be placed with minimum distance 'dis' between placed cows stalls
}

int aggressiveCows(vector<int> &stalls, int k) {
    sort(stalls.begin(), stalls.end());     // sort the stalls vector so it's easier to check for placement of cows 

    int n = stalls.size();   
    // we can also keep low as the min distance b/w two consecutive stalls but it will need to loop through stalls array to find so, so 1 is fine               
    int low = 1, high = stalls[n-1] - stalls[0];    // when k = 2 then the maximum possible distance between stalls is stalls[n-1] - stalls[0] 

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (canPlace(stalls, k, mid)) low = mid + 1;
        else high = mid - 1;
    }

    return high;
}

int main()  {
    vector<int> stalls = {1, 2, 4, 8, 9};
    int k = 3;
    int minDistance = aggressiveCows(stalls, k);
    cout << "Maximum Possible Minimum Distance : " << minDistance;

    return 0;
}