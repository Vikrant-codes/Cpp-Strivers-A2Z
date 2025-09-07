/*
Leetcode - 875. Koko Eating Bananas : Medium

Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. The guards have gone and will come back in h hours.
Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of bananas and eats k bananas from that pile. 
If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.
Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.
Return the minimum integer k such that she can eat all the bananas within h hours.

Examples :- 
Input: piles = [3,6,7,11], h = 8 __ Output: 4
Input: piles = [30,11,23,4,20], h = 5 __ Output: 30
Input: piles = [30,11,23,4,20], h = 6 __ Output: 23
Input: piles = [805306368,805306368,805306368], h = 1000000000 __ Output: 3

Constraints :- 1 <= piles.length <= 10^4 __ piles.length <= h <= 10^9 __ 1 <= piles[i] <= 10^9

The constraint piles.length <= h <= 10^9 shows that the hours given h will always be greater than the piles length so there is always a solution. 
This avoid situations when there are more piles than the given hours so that eating all the piles is possible. 
Ex- if piles = [10,9,8,11,12] and h = 3, then it is impossible to eat all the piles in 3 hours as there are 5 piles and no matter how fast the eating 
rate of Koko is, she won't be able to finish all the piles in the given time (since she can't eat more than a pile in an hour).
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach (Binary Search) : Time Complexity : O (n * log m) where n is the number of piles, m is the maximum number of bananas in a pile.
/*
Approach :- Use binary search to find the minimum eating speed k such that Koko can finish all the piles in h hours.

We know that no of hours h is always greater than the number of piles, so there is always a solution. Also the maximum eating speed k 
that koko can have is thus the maximum number of bananas in a pile since at this rate she can eat piles in 1 hour each pile and thus finish all 
the piles in less than or equal to h hours since h >= piles.length. So we keep the search space for k from 1 to max(piles).

We find mid. Check if koko can eat all the piles in h hours with this mid as the eating speed. If yes then we need to find a smaller speed, so we 
reduce search space towards left by doing high = mid - 1. If no then we need to increase the eating speed, so we reduce search space towards right 
by doing low = mid + 1.
*/

// Function to find the maximum number of bananas in all the piles
int findMax(vector<int>& piles) {
    int maxVal = 0;
    for(int bananas : piles) {
        maxVal = max(maxVal, bananas);
    }
    return maxVal;
}

// Function to check if Koko can eat all piles in h hours with given eating speed rate
int canEat(vector<int>& piles, int h, int rate) {
    int n = piles.size();
    long long time = 0;
    for(int i=0; i<n; i++) {
        time += piles[i] / rate;
        if (piles[i] % rate != 0) time += 1; 
    }
    return time <= h ? 1 : 0;
}

int minEatingSpeed(vector<int>& piles, int h) {
    int low = 1;
    int high = findMax(piles);
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int k = canEat(piles, h, mid);
        if (k == 1) high = mid - 1;
        else low = mid + 1;
    }
    return low;
}

int main() {
    vector<int> piles = {805306368,805306368,805306368};
    int h = 1000000000;
    int minSpeed = minEatingSpeed(piles, h);
    cout << "Minimum eating speed: " << minSpeed << endl;

    return 0;
}