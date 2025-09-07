/*
Leetcode - 18 : 4Sum : Medium

Given an array nums of n integers, return an array of all the unique quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:
0 <= a, b, c, d < n
a, b, c, and d are distinct.
nums[a] + nums[b] + nums[c] + nums[d] == target

You may return the answer in any order.

Example 1:
Input: nums = [1,0,-1,0,-2,2], target = 0                 Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
Example 2:
Input: nums = [2,2,2,2,2], target = 8                     Output: [[2,2,2,2]]
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach : Time Complexity: O(n^4) __ Space Complexity:  O(no. of the quadruplets) as we are using a set data structur to store the quads.
// Approach : Same as the one in 3Sum but here using 4 loops since we need to find quadruplets.
vector<vector<int>> fourSumBrute(vector<int>& nums, int target) {
    int n = nums.size(); //size of the array
    set<vector<int>> st;

    //checking all possible quadruplets:
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                for (int l = k + 1; l < n; l++) {
                    // taking bigger data type to avoid integer overflow:
                    long long sum = nums[i];
                    sum += nums[j];
                    sum += nums[k];
                    sum += nums[l];

                    if (sum == target) {
                        vector<int> temp = {nums[i], nums[j], nums[k], nums[l]};
                        sort(temp.begin(), temp.end());
                        st.insert(temp);
                    }
                }
            }
        }
    }
    vector<vector<int>> ans(st.begin(), st.end());
    return ans;
}

// Better Approach : Time Complexity: O(n^3 * log m)  __ Space Complexity:  O(no. of the quadruplets) as we are using a set data structur to store the quads.
// Approach : Same as the one in 3Sum but here using 3 loops and a hashset to store the kth element.
vector<vector<int>> fourSumBetter(vector<int>& nums, int target) {
    int n = nums.size(); //size of the array
    set<vector<int>> st;

    //checking all possible quadruplets:
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            set<long long> hashset;
            for (int k = j + 1; k < n; k++) {
                // taking bigger data type to avoid integer overflow:
                long long sum = nums[i];
                sum += nums[j];
                sum += nums[k];
                long long fourth = target - sum;
                if (hashset.find(fourth) != hashset.end()) {
                    vector<int> temp = {nums[i], nums[j], nums[k], (int)(fourth)};
                    sort(temp.begin(), temp.end());
                    st.insert(temp);
                }
                // put the kth element into the hashset:
                hashset.insert(nums[k]);
            }
        }
    }
    vector<vector<int>> ans(st.begin(), st.end());
    return ans;
}

// Optimal Approach : Time Complexity: O(n^3) __ Space Complexity:  O(1)
// Approach : Using 2 pointers approach. Same as the one used for 3sum problem.
vector<vector<int>> fourSum(vector<int>& nums, int target) {
    int n = nums.size();
    vector<vector<int>> res;
    // sort the vector to implement two pointer approach and also skip duplicates
    sort(nums.begin(), nums.end());

    for(int i=0; i<n; i++) {
        // avoid the duplicates while moving i
        if (i > 0 && nums[i] == nums[i-1]) continue;

        for(int j=i+1; j<n; j++) {
            // avoid the duplicates while moving j
            if (j > i+1 && nums[j] == nums[j-1]) continue;

            // two pointer approach for the remaining two numbers
            int k = j+1;
            int l = n-1;
            while(k < l) {
                /*
                Why sum used as long long? 
                Even though the individual elements are within integer range, the sum can stretch beyond the range. So to be able to store the sum 
                we define the sum as long long. 

                Que) Why aren't the elements added in one go?
                Reason: To Prevent Integer Overflow 
                If nums[i], nums[j], etc. are of type int, then all four values are added together using int arithmetic first, and only then is the 
                result promoted to long long. So if the sum overflows the int range before being assigned, the result will be incorrect.
                To prevent this, we can add the numbers one by one to a long long variable. This way, the addition is done in long long arithmetic.
                The moment you assign nums[i] to a long long variable sum, the entire expression becomes long long arithmetic. 
                Each subsequent addition is safely within long long, avoiding overflow.
                */
                long long sum = nums[i];
                sum += nums[j];
                sum += nums[k];
                sum += nums[l];

                if (sum > target) l--;
                else if (sum < target) k++;
                else {
                    vector<int> temp = {nums[i], nums[j], nums[k], nums[l]};
                    res.push_back(temp);
                    k++;
                    l--;
                    //skip the duplicates
                    while (k < l && nums[k] == nums[k-1]) k++;
                    while (k < l && nums[l] == nums[l+1]) l--;
                }
            }
        }
    }
    return res;
}

int main() {
    vector<int> nums = {1,0,-1,0,-2,2};
    int target = 0;
    vector<vector<int>> quadruplets = fourSum(nums, target);
    for(auto quadruplet : quadruplets) {
        cout << "Quadruplet -> ";
        for(int x : quadruplet)
            cout << x << " ";
        cout << endl;
    }
}