/*
Count the number of subarrays with given xor K

Problem Statement: Given an array of integers and an integer k. Find the total number of subarrays having bitwise XOR of all elements equal to k.

Example 1:
Input Format: A = [4, 2, 2, 6, 4] , k = 6
Result: 4
Explanation: The subarrays having XOR of their elements as 6 are  [4, 2], [4, 2, 2, 6, 4], [2, 2, 6], [6]

Example 2:
Input Format: A = [5, 6, 7, 8, 9], k = 5
Result: 2
Explanation: The subarrays having XOR of their elements as 5 are [5] and [5, 6, 7, 8, 9]
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach : Time Complexity : O(n ^ 2) __ Space Complexity : O(1)
// Approach : Find XOR of all possible subarrays and update the count if it matches 'k'
int subarrXORBrute(vector<int> arr, int k) {
    int n = arr.size();
    int count = 0;
    for(int i=0; i<n; i++) {
        int x = 0;
        for(int j=i; j<n; j++) {
            x ^= arr[j];
            if (x == k) count++;
        }
    }
    return count;
}

// Optimal Approach (Prefix XOR approach): Time Complexity : O(n) / O(n log n) / O(n * n) {depends on map} __ Space Complexity : O(n) 
/*
XOR Properties :- XOR is reversible i.e. , a ^ b = c => a = b ^ c.
Proof :- 
a ^ b = c
Take XOR of both sides with b => (a ^ b) ^ b = c ^ b
a ^ (b ^ b) = c ^ b                     (since XOR is associative and commutative)
a ^ 0 = c ^ b                   (since of a number with itself is 0 i.e. b ^ b = 0)
a = c ^ b                       (since xor of any number with 0 is the number itself i.e. a ^ 0 = a)
Thus, a ^ b = c => a = b ^ c

Same as Prefix Sum approach for subarray sum problem but since we are using XOR, we need to consider the properties of XOR.
In this prefix sum approach, suppose the total sum upto current index was 'x' and we are interesed in subarray sum 'k' then we checked for the 
existence of a subarray with sum 'y' in the map such that y + k = x. or y = x - k. Now here we need to check for xor so suppose xor upto current 
index is 'x' and we are interested in subarray xor 'k' then we need to check for the existence of a subarray with xor 'y' in the map such that 
y ^ k = x. or y = x ^ k. (since xor is reversible so a ^ b = c => a = b ^ c)
*/ 

int subarrXOR(vector<int> arr, int k) {
    int n = arr.size();
    unordered_map<int, int> mpp;
    int x = 0;
    mpp[x] = 1; // to handle the case when the prefix xor itself is equal to k
    int cnt = 0;
    for(int i=0; i<n; i++) {
        x ^= arr[i];
        int y = x ^ k;
        cnt += mpp[y]; //check if there exists a prefix xor 'y' such that y ^ k = x, add the count of such prefix xor to the result (default is 0 count)
        mpp[x]++;
    }
    return cnt;
}

int main() {
    vector<int> arr = {4, 2, 2, 6, 4};
    vector<int> arr2 = {5, 6, 7, 8, 9};
    int k = 6;
    int k2 = 5;
    int count = subarrXOR(arr, k);
    cout << count;

    return 0;
}