/*
Leetcode - 2149 : Rearrange Array Elements by Sign : Medium
Variant 1 :- There’s an array ‘A’ of size ‘N’ with an equal number of positive and negative elements. 
Without altering the relative order of positive and negative elements, you must return an array of alternating positive and negative values.
The relative order of positive and negative elements should be maintained.

Variant 2 :- There’s an array ‘A’ of size ‘N’ with an having positive and negative elements (may be unequal in number). Rearrange the elements 
in the array such that the positive and negative elements are in alternate positions. The ramaining elements should be at the end of the array.
The relative order of positive and negative elements should be maintained.

Note: Start the array with positive elements.
*/
#include <iostream>
#include <vector>
using namespace std;

// Brute Force Approach : O(2N) time and O(N) space
/*
We make two separate arrays for storing +ve and -ve elements. Since array contains equal no of +ve & -ve elements so the two array sizes would be n/2.
Iterate through the array and store +ve values into +ve array and -ve to -ve array. After that again iterate through the array and this time store 
the +ve & -ve array elements to the original array in an alternate fashion.
*/
vector<int> rearrangeArrayBrute(vector<int> &A) {
    vector<int> pos;    // Array to store positive elements
    vector<int> neg;    // Array to store negative elements
    int n = A.size();   // Size of the array
    // Segregate the array into positives and negatives.
    for(int i=0;i<n;i++){
        if(A[i]>0) pos.push_back(A[i]);     // if element is +ve store it to pos array
        else neg.push_back(A[i]);           // if element is -ve store it to neg array
    }
    // Positives on even indices, negatives on odd.
    for(int i=0;i<n/2;i++){
        // for each i store the +ve element at 2*i index and -ve element at 2*i+1 index
        A[2*i] = pos[i];
        A[2*i+1] = neg[i];
    }
    return A;  
}

// Optimal Approach (Variant 1) : O(N) time and O(N) space
/*
Define a res array to return the answer and iterate through the given array. We know that the +ve elements will go on indexes 0,2,4,... and the 
-ve elements will go on indexes 1,3,5,... so we define a positive index (pi) = 0 and negative index (ni) = 1. Then we iterate through the array 
and if the current element is +ve we initialize res[pi] = arr[i] and increment pi by 2. If the current element is -ve we initialize
res[ni] = arr[i] and increment ni by 2. Finally we return the res array.
*/
vector<int> rearrangeArray(vector<int>& nums) {
    int n = nums.size();
    vector<int> res(n,0);   // resultant array of size n and initially all elements 0
    int pi = 0, ni = 1;     // positive index & negative index
    for(int i=0; i<n; i++) {
        if(nums[i] >= 0) {
            res[pi] = nums[i];
            pi += 2;
        }
        else {
            res[ni] = nums[i];
            ni += 2;
        }
    }
    return res;
}

// Variant 2 
// Here since the array has unequal number of +ves and -ves so we use the Brute Force approach to segregate the +ve & -ve elements.
vector<int> RearrangebySign(vector<int>A, int n){
    vector<int> pos;
    vector<int> neg;
    for(int i=0;i<n;i++){
        if(A[i]>0) pos.push_back(A[i]);
        else neg.push_back(A[i]);
    }

    if(pos.size() < neg.size()){
        // First, fill array alternatively till the point where positives and negatives ar equal in number.
        for(int i=0;i<pos.size();i++){
            A[2*i] = pos[i];
            A[2*i+1] = neg[i];
        }
        // Fill the remaining negatives at the end of the array.
        int index = pos.size()*2;
        for(int i = pos.size();i<neg.size();i++){
            A[index] = neg[i];
            index++;
        }
    }
    // If negatives are lesser than the positives.
    else{ 
        // First, fill array alternatively till the point where positives and negatives ar equal in number.
        for(int i=0;i<neg.size();i++){
            A[2*i] = pos[i];
            A[2*i+1] = neg[i];
        }
        // Fill the remaining positives at the end of the array.
        int index = neg.size()*2;
        for(int i = neg.size();i<pos.size();i++){
            A[index] = pos[i];
            index++;
        }
    }
    return A;
}

int main() {
    vector<int> arr = {1,2,-3,-1,-2,3};
    vector<int> ans = rearrangeArray(arr);
    for(int x : ans) cout << x << " ";

    return 0;
}