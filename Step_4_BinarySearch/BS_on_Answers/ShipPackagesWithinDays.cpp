/*
Leetcode - 1011. Capacity To Ship Packages Within D Days -- Medium

A conveyor belt has packages that must be shipped from one port to another within days days.
The ith package on the conveyor belt has a weight of weights[i]. Each day, we load the ship with packages on the conveyor belt 
(in the order given by weights). We may not load more weight than the maximum weight capacity of the ship.
Return the least weight capacity of the ship that will result in all the packages on the conveyor belt being shipped within days days.

Examples :-

Input: weights = [1,2,3,4,5,6,7,8,9,10], days = 5 __ Output: 15
Explanation: A ship capacity of 15 is the minimum to ship all the packages in 5 days like this:
1st day: 1, 2, 3, 4, 5 _ 2nd day: 6, 7 _ 3rd day: 8 _ 4th day: 9 _ 5th day: 10
Note that the cargo must be shipped in the order given, so using a ship of capacity 14 and splitting the packages into parts 
like (2, 3, 4, 5), (1, 6, 7), (8), (9), (10) is not allowed.


Input: weights = [3,2,2,4,1,4], days = 3 __ Output: 6
Explanation: A ship capacity of 6 is the minimum to ship all the packages in 3 days like this:
1st day: 3, 2 _ 2nd day: 2, 4 _ 3rd day: 1, 4


Input: weights = [1,2,3,1,1], days = 4 __ Output: 3
Explanation:
1st day: 1 _ 2nd day: 2 _ 3rd day: 3 _ 4th day: 1, 1 


Constraints :- 1 <= days <= weights.length <= 5 * 10^4 __ 1 <= weights[i] <= 500
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach : Binary Search
// Time Complexity : O(n * log (sum - max)) , where sum & max are the sum and max of the weights array

/*
Approach :- 
The low of the search space is max(weights) since this is the minimum capacity that can supply the loads .. if the low is lesser than max(weights) 
like for ex consider weights = [1,2,3,4,5,6,7,8,9,10] and suppose low = 7 then the weights like 8, 9 or 10 can never be shipped since these are 
greater than the capacity 7 so that's why the minimum capacity should be max(weights) since only then all the weights could be shipped. 
Also the high is sum(weights) since this much capacity can ship all the weights in a single day so high is sum(weights). 

Start search space with low = max(weights), high = sum(weights). Find mid and check if the weights can be shipped within the given days in mid capacity. 
If they can be shipped, we move our search space towards left using high = mid - 1 to find the minimum capacity. 
Else we move search space towards right using low = mid + 1.
At the end, low points to the minimum capacity required to ship within given days. 

-> How to check whether the weights can be shipped within given days in mid capacity ?
The function canShip returns True if the weights can be shipped within given days with the given capacity (i.e. mid)
If capacity denotes the capacity to take load in one shipment then we check for the total days required to move all weights for that capacity. 
Initialize days_taken as 0 and a sum counter as 0. Iterate through the weights and add the current weight to sum. 
If sum becomes >= capacity then we increment days_taken count since we can't load any more weights on it which makes it one shipment. 
Also reset the sum counter to 0 (if sum was equal to capacity) / current weight (if sum > capacity then current weight would go in next shipment)
After the loop ends check if sum still denotes some weight means we need another shipment to move this weight and hence increment the days_taken. 
At the end return True if the days_taken is less than / equal to the given days meaning the weights can be shipped within given days at given capacity.
*/

vector<int> MaxSum(vector<int>& weights) {
    int sm = 0, mx = 0;
    for(int x : weights) {
        sm += x;
        mx = max(mx, x);
    }
    vector<int> temp = {mx, sm};
    return temp;
}

bool canShip(vector<int>& weights, int days, int capacity) {
    int sm = 0;
    int days_taken = 0;
    for(int x : weights) {
        sm += x;
        if (sm >= capacity) {
            if (sm > capacity) sm = x;
            else sm = 0;
            days_taken++;
        }
    }
    if (sm != 0) days_taken++;
    return days_taken <= days;
}
    
bool canShipStriver(vector<int> &weights, int days, int cap) {
    int days_taken = 1; //First day.
    int load = 0;
    int n = weights.size(); //size of array.
    for (int i = 0; i < n; i++) {
        if (load + weights[i] > cap) {
            days_taken += 1; //move to next day
            load = weights[i]; //load the weight.
        }
        else {
            //load the weight on the same day.
            load += weights[i];
        }
    }
    return days_taken <= days;
}

int shipWithinDays(vector<int>& weights, int days) {
    vector<int> lowHigh = MaxSum(weights);
        
    if (days == 1) return lowHigh[1];
        
    int low = lowHigh[0];
    int high = lowHigh[1];

    // we can also get the maximum and sum of the weights using built-in functions
    // int low = *max_element(weights.begin(), weights.end());
    // int high = accumulate(weights.begin(), weights.end(), 0);
    // max_element returns the iterator to the max element in the vector so it is dereferenced using * to get the value
    // accumulate returns the sum of the elements in the vector. :- accumulate(start_iterator, end_iterator, initial_value) 
    // start_iterator → starting position _ end_iterator → ending position _ initial_value → starting sum (commonly 0 for integers)
        
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (canShip(weights, days, mid)) high = mid - 1;
        else low = mid + 1;
    }
    return low;
}

int main() {
    vector<int> weights = {1,2,3,4,5,6,7,8,9,10};
    int days = 5;
    
    cout << "Minimum ship capacity to ship packages within " << days << " days: " << shipWithinDays(weights, days) << endl;

    return 0;
}