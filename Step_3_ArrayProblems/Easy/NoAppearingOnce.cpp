// Single Number <Leetcode> : Give a non-empty array of integers where every element appears twice except for one. Find that element.

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Brute Force Approach : Time Complexity : O(n^2) __ Space Complexity : O(1)
// For every element in array count the number of appearances (using linear search) and if the count is 1 then return that element.
int getSingleBrute(vector<int> arr){
    for(int i=0; i<arr.size(); i++){
        int key = arr[i];
        int cnt = 0;
        for(int j=0; j<arr.size(); j++){
            if(arr[j] == key) cnt++;
        }
        if(cnt == 1) return key;
    }
    return -1;          // never executed, added just to remove warnings.
}

// Better Approach (Hashing):-Time Complexity : O(n) __ Space Complexity : O(n/2 + 1)
// unordered_map can be used for hashing since it's complexity is O(1) which is better than O(log n) of map but in worst cases it can become O(n)
// In case of higher collision chances worst case might occur and complexity could becomes O(n ^ 2) so in such cases, better to use map O(n log n).
// Space Complexity : O(n/2 + 1)-> map stores only unique elements and for this twice appearing array of size n the unique elements will be n/2+1.
int getSingleHash(vector<int> arr){
    unordered_map<int, int> mpp;
    for(int i=0; i<arr.size(); i++) mpp[arr[i]]++;
    for(auto x : mpp)
        if(x.second == 1) return x.first;
    return -1;
}

// Optimal Approach (Using XOR) : Time Complexity : O(n) __ Space Complexity : O(1)
// Approach :- The array is such that every element appears twice except for one .. so if we take xor of whole array those twice appearing elements 
// will become 0 since element xor itself is 0, leaving only the single element with 0s. The xor of 0s and the element will return the element.
// ex - arr = {1,2,4,3,1,4,2} => 1^2^4^3^1^4^2 = (1^1)^(2^2)^(3)^(4^4) = 0^0^3^0 = 3
int getSingleXOR(vector<int> arr){
    int x = 0;
    for(int i=0; i<arr.size(); i++) x ^= arr[i];
    return x;
}

int main() {
    vector<int> arr = {6,1,7,2,5,1,7,2,6};
    int ans = getSingleHash(arr);
    cout << ans;

    return 0;
}