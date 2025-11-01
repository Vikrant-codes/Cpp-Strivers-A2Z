/* 
Leetcode - 268. Missing Number : Easy
Given an array arr containing n distinct numbers in the range [0, n], return the only number in the range that is missing from the array.

Example 1:  Input: arr = [3,0,1]       Output: 2
Explanation: n = size = 3, so all numbers are in the range [0,3]. 2 is the missing number in the range since it does not appear in arr.
Example 2:  Input: arr = [0,1]         Output: 2
Explanation: n = size = 2 , so all numbers are in the range [0,2]. 2 is the missing number in the range since it does not appear in arr.
*/
#include <iostream>
#include <vector>
using namespace std;

// Brute Force Approach : Time Complexity: O(n^2) __ Space Complexity: O(1)
int missingBrute(vector<int>&a) {
    // for every number from 1 to N check if it is present in the array (through linear search) .. if it is not present return it
    int N = a.size();
    for (int i = 1; i <= N; i++) {
        // flag variable to check if an element exists
        int flag = 0;
        // Search the element using linear search:
        for (int j = 0; j < N; j++) {
            if (a[j] == i) {
                // i is present in the array:
                flag = 1;
                break;
            }
        }
        // check if the element is missing i.e flag == 0:
        if (flag == 0) return i;
    }
    // The following line will never execute. It is just to avoid warnings.
    return -1;
}

// Better Approach : Use hashing concept (an array can be used of size n+1 where the element at index i tells us whether the number i is present)
// Time Complexity: O(n) __ Space Complexity: O(n)
int missingBetter(vector<int>& arr) {
    int n = arr.size();
    int freq[n+1] = {0};        // size n+1 is used because the elements in actual array are in range [0,n]
    for(int i=0; i<n; i++) freq[arr[i]] = 1;
    for(int i=0; i<n+1; i++) 
        if(freq[i] == 0) 
            return i;
    return -1;     // this return statement is never executed but is added to remove warning because without it the return would've been inside a 
    // conditional statement and compiler consider that the statment might never be true and raises warning
}


// Optimal Approach : Time Complexity: O(n) __ Space Complexity: O(1)
/*
Approach 1 :-
The sum of the first n natural numbers is given by the formula n*(n+1)/2. Since array contains elements in range [0,n] and has a missing number 
than the actual sum of the array would be x less than the expected sum (since x is missing). So we can find x by expected_sum - actual_sum.

Approach 2 :-
We can use XOR to find the missing number. The XOR of a number with itself is 0 and the XOR of a number with 0 is the number itself.
So if we XOR all the numbers from 0 to n and also XOR all the elements of the array, the result will be the missing number.
ex - consider the array [0,1,4,3] and the missing number is 2 since range is [0,4].
XOR of all numbers from 0 to 4 = 0^1^2^3^4 = 4
XOR of all elements of the array = 0^1^4^3 = 6
So the final XOR will be 4^6 = 2 which is the missing number.
This can be shown as (0^1^2^3^4) ^ (0^1^4^3) = (0^0) ^ (1^1) ^ (2) ^ (3^3) ^ (4^4) = 0 ^ 0 ^ 2 ^ 0 ^ 0 .... since xor of a no. with itself is zero
thus (0^1^2^3^4) ^ (0^1^4^3) = 0 ^ 0 ^ 2 ^ 0 ^ 0 = 2 ... since xor of zero with any number is that number itself
*/
int missingOptimal(vector<int>& arr) {
    int n = arr.size();
    int sum = 0;
    int exp_sum = (n*n + n) /2;
    for(int i=0; i<n; i++)
        sum += arr[i];
    int missing = exp_sum - sum;
    return missing;
}

int missingOptimalXOR(vector<int>& arr) {
    int n = arr.size();
    int xor1 = 0;
    int xor2 = 0;
    // Find xor1 which is XOR of all numbers from 1 to n
    for(int i=0; i<=n; i++) xor1 ^= i;
    // Find xor2 which is XOR of all array elements
    for(int i=0; i<n; i++) xor2 ^= arr[i];

    return xor1 ^ xor2;
}

int main() {
    vector<int> arr = {0,1,2};
    int m = missingBrute(arr);
    cout << m;

    return 0;
}