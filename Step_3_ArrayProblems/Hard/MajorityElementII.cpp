/*
Leetcode - 229. Majority Element II : Medium
Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times. ( ⌊ n/3 ⌋ means floor(n/3) )
*/

/*
Observation: How many integers can occur more than floor(N/3) times in the given array:
If we closely observe, in the given array, there can be a maximum of two integers that can occur more than floor(N/3) times. 
Let’s understand it using the following scenario:
Assume there are 8 elements in the given array. Now, if there is any majority element, it should occur more than floor(8/3) = 2 times. 
So, the majority of elements should occur at least 3 times. Now, if we imagine there are 3 majority elements, then the total occurrence of them 
will be 3X3 = 9 i.e. greater than the size of the array. But this should not happen. That is why there can be a maximum of 2 majority elements.
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach :- Time Complexity : O(n^2) __ Space Complexity : O(1)
// Approach :- For each element check if it occurs more than ⌊ n/3 ⌋ times, if it does then add it to the resultant vector.
vector<int> MajorityBrute(vector<int> arr) {
    vector<int> res;
    int n = arr.size();
    for(int i=0; i<n; i++) {
        // Check that the current element is not already present in the res vector .. i.e. loop only when either res is empty or res[0] != arr[i]
        if (res.size()==0 || res[0] != arr[i]) {
            int cnt = 0;                // to store the count of current element in the vector 
            for(int j=0; j<n; j++) {
                if(arr[j] == arr[i]) cnt++;
            }
            if(cnt > n/3) res.push_back(arr[i]);       // if count exceeds n/3 add the element to the res vector
        }
        if (res.size() == 2) break;             // there can be at most two majority elements so if the vector size becomes 2 break out of loop
    }
    return res;
}

// Better Approach (using Hashing) : Time Complexity : O(n) / O(n log n) {depends on map/unordered_map} __ Space Complexity : O(n)
/*
Approach :- use a map to store the frequency of all elements .. loop through the map and add any element which have frequency of more than n/3
This can be further simplified to do the functioning in a single for loop. For each element increment the count of that element in the map and 
if the count becomes equal to the minimum majority limit i.e. ( floor(n/3) + 1 ) add that element to the res vector. 
Also if res count reaches 2 then break out of the loop. 
ex - consider arr = [1,1,1,1,2,3,3,3]
for i = 0: mpp[1] = 1
for i = 1: mpp[1] = 2
for i = 2: mpp[1] = 3 ... now this mpp[arr[i]] becomes equal to minimum frequency required so add it to res vector
for i = 3: mpp[1] = 4 ... since we have already added it, it isn't added again (this is why we used == to check such condition)
for i = 4: mpp[2] = 1
for i = 5: mpp[3] = 1
for i = 6: mpp[3] = 2
for i = 7: mpp[3] = 3 ... now add 3 to res vector
*/
vector<int> MajorityBetter(vector<int> arr) {
    unordered_map<int, int> mpp;
    vector<int> res;
    int n = arr.size();
    int min_freq = n/3 + 1;

    for(int i=0; i<n; i++) {
        mpp[arr[i]]++;
        if (mpp[arr[i]] == min_freq) res.push_back(arr[i]);
        if (res.size() == 2) break;
    }
    return res;
}

// Optimal Approach (Extended Boyer Moore’s Voting Algorithm) : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Approach :- The approach is similar to Moore's Voting Algorithm approach used in Majority Element I. Here since there can be at most 2 majority 
elements so we use two counters (cnt1 & cnt2, initially both 0) and consider two elements to be majority (ele1 & ele2). While iterationg if cnt1 == 0 
means we have to initialize ele1 and we do so only if the current element is not equal to ele2. Similarly we do the same procedure for cnt2 & ele2.
If the current element is equal to either ele1 or ele2 then we increment the respective counter. Also if none of the condition is true i.e. when we 
hace both cnt1 & cnt2 non-zero and the current element is unequal to both ele1 & ele2 then we decrement both the counters. At the end of the loop 
we count the occurences of both ele1 & ele2 to verify whether these two are indeed majority element or not.
*/
vector<int> majorityElement(vector<int>& nums) {
    int n = nums.size();
    int cnt1 = 0, cnt2 = 0, ele1 = INT_MIN, ele2 = INT_MIN;
    for(int i=0; i<n; i++){
        if(cnt1 == 0 && ele2 != nums[i]) {
            cnt1 = 1;
            ele1 = nums[i];
        }
        else if(cnt2 == 0 && ele1 != nums[i]) {
            cnt2 = 1;
            ele2 = nums[i];
        }
        else if(nums[i] == ele1) cnt1++;
        else if(nums[i] == ele2) cnt2++;
        else {
            cnt1--;
            cnt2--;
        }
    }

    // verify whether the two elements ele1 & ele2 are majority or not
    vector<int> res;
    cnt1 = 0, cnt2 = 0;
    for(int i=0; i<n; i++) {
        if (nums[i] == ele1) cnt1++;
        else if (nums[i] == ele2) cnt2++;
    }
    if (cnt1 > n/3) res.push_back(ele1);
    if (cnt2 > n/3) res.push_back(ele2);
    return res;
}

int main() {
    vector<int> arr = {1,1,1,2,2,3,3,3};
    vector<int> majority = majorityElement(arr);
    for(int x : majority) cout << x << " ";
    return 0;
}