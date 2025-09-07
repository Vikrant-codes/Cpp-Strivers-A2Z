/*
GFG - Number of occurrence : Easy
Given a sorted array, arr[] and a number target, you need to find the number of occurrences of target in arr[]. 

Examples :-
Input: arr[] = [1, 1, 2, 2, 2, 2, 3], target = 2 __ Output: 4
Input: arr[] = [1, 1, 2, 2, 2, 2, 3], target = 4 __ Output: 0
Input: arr[] = [8, 9, 10, 12, 12, 12], target = 12 __ Output: 3

Constraints :- 1 ≤ arr.size() ≤ 10^6 __ 1 ≤ arr[i] ≤ 10^6 __ 1 ≤ target ≤ 10^6
*/

#include <bits/stdc++.h>
using namespace std;

/*
Approaches :- 
1. Brute Force Approach (Linear Search) :- O(n) time complexity and O(1) space complexity. 

There are two optimal approaches to this problem both with Time complexity of O(log n)

2. Optimal Approach 1 :- Find the first and last occurrence of target in arr[]. Count of occurrences will be last_index - first_index + 1.
If the target element is not present then first and last will both be -1 but then count = last - first + 1 will return 1 so we need to handle this 
case by returning 0 if first (or last) is -1.

3. Optimal Approach 2 :- Find the lower bound and upper bound of target in arr[]. Count of occurrences will be upper_bound - lower_bound. 

Que ) Why Optimal Approach 2 works ? 
There can be two cases - 
>> If target is present in arr[], then lower_bound will point to the first occurrence of target and 
upper_bound will point to the position just after the last occurrence of target. 
So, count of occurrences = upper_bound - lower_bound = (last_index + 1) - first_index = last_index - first_index + 1.

>> If target is not present in arr[], then both lower_bound and upper_bound will point to the first element which is greater than target and thus 
upper_bound - lower_bound will result in zero. 
*/

// Optimal Approach 1 :- Count of Occurrences using last occurrence and first occurrence
int firstOccurrence(vector<int> &arr, int target) {
    int n = arr.size();
    int first = -1;
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] >= target) {
            if (arr[mid] == target) first = mid;
            high = mid - 1; // search in left half
        }
        else low = mid + 1; // search in right half
    }
    return first;
}

int lastOccurrence(vector<int> &arr, int target) {
    int n = arr.size();
    int low = 0, high = n - 1;
    int last = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] <= target) {
            if (arr[mid] == target) last = mid;
            low = mid + 1; // search in right half
        }
        else high = mid - 1; // search in left half
    }
    return last;
}

int countFreq1(vector<int> &arr, int target) {
    int first = firstOccurrence(arr, target);
    int last = lastOccurrence(arr, target);

    int cnt = last == -1 ? 0 : last - first + 1; // if element is not present then count will be 0
    return cnt;
}

// Optimal Approach 2 :- Count of Occurrences using upper bound and lower bound
int upperBound(vector<int> &arr, int target) {
    int n = arr.size();
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] <= target) low = mid + 1;
        else high = mid - 1;
    }
    return low;
}

int lowerBound(vector<int> &arr, int target) {
    int n = arr.size();
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return low;
}

int countFreq2(vector<int> &arr, int target) {
    int ub = upperBound(arr, target);
    int lb = lowerBound(arr, target);

    return ub - lb;
}

int main() {
    vector<int> arr = {1,2,2,3,3,3,4,4,4,4};
    int x = 3;
    int cnt = countFreq2(arr, x);
    cout << "Count of Occurrences of " << x << " is : " << cnt << endl;

    return 0;
}