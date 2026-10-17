/*
TUF - 886. Sum of Array Elements

Given an array arr of size n, the task is to find the sum of all the elements in the array.

Examples :-

Input: n=5, arr = [1,2,3,4,5]
Output: 15
Explanation: Sum of all the elements is 1+2+3+4+5 = 15

Input: n=6, arr = [1,2,1,1,5,1]
Output: 11
Explanation: Sum of all the elements is 1+2+1+1+5+1 = 11

Constraints :-
• 1 <= n <= 10^5
• 1 <= arr[i] <= 10^4
*/

#include<bits/stdc++.h>
using namespace std;

int sum(int arr[], int n) {
    int ans = 0;

    for (int i = 0; i < n; i++) {
        ans += arr[i];
    }
    
    return ans;
}

int main() {
    return 0;
}