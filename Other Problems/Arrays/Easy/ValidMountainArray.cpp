/*
Leetcode - 941. Valid Mountain Array : Easy

Given an array of integers arr, return true if and only if it is a valid mountain array.
Recall that arr is a mountain array if and only if:
    - arr.length >= 3
    - There exists some i with 0 < i < arr.length - 1 such that:
        arr[0] < arr[1] < ... < arr[i - 1] < arr[i] 
        arr[i] > arr[i + 1] > ... > arr[arr.length - 1]

Examples :-
Input: arr = [2,1] __ Output: false
Input: arr = [3,5,5] __ Output: false
Input: arr = [0,3,2,1] __ Output: true

Constraints :-
- 1 <= arr.length <= 10^4
- 0 <= arr[i] <= 10^4
*/

#include <bits/stdc++.h>
using namespace std;

/*
🧠 Problem Intuition
A mountain array must:
1. Strictly increase to a peak,
2. Then strictly decrease after that.
3. The peak cannot be at the first or last position.
So visually, it should look like this : ↑ ↑ ↑ ↑ ↓ ↓ ↓ ↓
and not just ↑↑↑ or ↓↓↓.
*/
bool validMountainArray1(vector<int>& arr) {
    if(arr.size() < 3) return false;
    int i=1;

    if(arr[0]>=arr[1]) return false;        // must start with an increase
    // increasing part
    while (i<arr.size() && arr[i]>arr[i-1]) i++;
    if(i == arr.size()) return false;       // never decreased, so doesn't have a decreasing half

    // decreasing part
    while (i<arr.size() && arr[i]<arr[i-1]) i++;
    if(i == arr.size()) return true;        // perfectly ended after decreasing
    
    return false;     
}

bool validMountainArray2(vector<int>& arr) {
    int n = arr.size();
    if (n < 3) return false;

    int i = 0;
    while (i < n - 1 && arr[i] < arr[i + 1]) i++;

    int k = n - 1;
    while (k > 0 && arr[k] < arr[k - 1]) k--;

    if (i == n - 1 || k == 0) return false;
    return i == k;
}

bool validMountainArrayChatGPT(vector<int>& arr) {
    int n = arr.size(), i = 0;
    if (n < 3) return false;

    // climb up
    while (i + 1 < n && arr[i] < arr[i + 1]) i++;

    // peak cannot be first or last
    if (i == 0 || i == n - 1) return false;

    // go down
    while (i + 1 < n && arr[i] > arr[i + 1]) i++;

    return i == n - 1;
}

int main() {
    return 0;
}