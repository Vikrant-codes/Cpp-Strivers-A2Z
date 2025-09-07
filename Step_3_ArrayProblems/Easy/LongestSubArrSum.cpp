/*
Given an array and a sum k, we need to return the length of the longest subarray that sums to k.
There can be two variations of this problem one where array contains only +ves while the other variation where array contains both +ves & -ves
For array containing both +ves & -ves the better solution given here is actually the optimal one. 
*/ 

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;


// Brute Force Approach : Time Complexity : O(n^2) __ Space Complexity : O(1)
// Generate all subarrays and check their sum ... if it equals k then check the subarray length.
int longestSubArrBrute(vector<int> arr, int k){
    int maxlen = 0;
    for(int i=0; i<arr.size(); i++){
        // subarrays starting from index i and goes till i+1 to n
        int sum = arr[i];
        for(int j=i+1; j<arr.size(); j++){
            // sum of each subarray can be cakucalated by adding the arr[j] while the j is still moving
            sum += arr[j];
            if(sum == k){
                maxlen = max(maxlen, j-i+1);
            }
            else if(sum > k) break;         // since arr contains only +ve then once sum exceeds k it will never become equal to k
        }
    }
    return maxlen;
}

// Optimal Approach (Prefix_sum Approach): Time Complexity : O(n) <- O(n^2) in worst case ->__ Space Complexity : O(n)
// This prefix_sum approach is optimal when the array contains both negatives & positives. 
/* We loop through the entire array and find the cumulative sum from index 0 upto the current element. Say this total sum is equal to s.
Say that a subarray of sum k exists such that the current element is at last of that subarray then another subarray of sum s-k should also exist..
since only if such sub-array exist, we can find the subarray with sum k. To check for this s-k sum subarray we can use hashing and 
store the prefixsums in a hasmap and so we can easily search for this s-k sum subarr using this hashmap
*/
int longestSubArrOptimal(vector<int> arr, int k){
    unordered_map<int, int> mpp;
    int maxLen = 0;
    int sum = 0;
    for(int i=0; i<arr.size(); i++){
        sum += arr[i];
        if(sum == k){
            maxLen = max(maxLen, i+1);
        }
        int rem = sum - k;
        if(mpp.find(rem) != mpp.end()){
            int len = i - mpp[rem];
            maxLen = max(maxLen, len);
        }
        if(mpp.find(sum) == mpp.end()){
            mpp[sum] = i;
        }
    }
    return maxLen;
}

// Most Optimal Approach (Only for array containing +ve numbers): Time Complexity : O(2n) __ Space Complexity : O(1)
/*
Intuition: We are using two pointers i.e. left and right. The left pointer denotes the starting index of the subarray and the right pointer denotes 
the ending index. Now as we want the longest subarray, we will move the right pointer in a forward direction every time adding the element i.e. 
a[right] to the sum. But when the sum of the subarray crosses k, we will move the left pointer in the forward direction as well to shrink the size 
of the subarray as well as to decrease the sum. Thus, we will consider the length of the subarray whenever the sum becomes equal to k.

Time Complexity : O(2n) -> Even though we are using two while loops (one inside of another) it might seem like that the complexity should be O(n^2) 
but it is not the case here.. since we are using a left pointer and it's position is only moved forward so this inner while loop runs at most n times
for the entire code (since array size in n and left pointer can move to n times only) so even in worst case it moved n times (for the entirety of 
outer while loop). This is the reason why the time complexity is O(n+n) and not O(n*n). 
*/

int longestSubArrMostOptimal(vector<int> a, int k){
    int n = a.size(); // size of the array.
    int left = 0, right = 0; // 2 pointers
    long long sum = a[0];
    int maxLen = 0;
    while (right < n) {
        // if sum > k, reduce the subarray from left until sum becomes less or equal to k:
        while (left <= right && sum > k) {
            sum -= a[left];
            left++;
        }
        // if sum = k, update the maxLen i.e. answer:
        if (sum == k) {
            maxLen = max(maxLen, right - left + 1);
        }
        // Move forward thw right pointer:
        right++;
        if (right < n) sum += a[right];
    }

    return maxLen;
}


int main(){
    vector<int> arr = {1,2,3,2,1,1,1,1,1,4,1,3,2,1,1};
    int ans = longestSubArrMostOptimal(arr, 5);
    cout << ans;

    return 0;
}