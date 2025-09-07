/*
Leetcode - 15. 3Sum : Medium

Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, 
and nums[i] + nums[j] + nums[k] == 0. 
i.e. Return all the unique triplets that sum up to zero. 

Notice that the solution set must not contain duplicate triplets.

Example 1: 
Input: nums = [-1,0,1,2,-1,-4] __ Output: [[-1,-1,2],[-1,0,1]]
Explanation: 
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not matter.

Example 1: Input: nums = [0,1,1] __ Output: []
Example 3: Input: nums = [0,0,0] __ Output: [[0,0,0]]
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach :- Time Complexity : O(N3 * log(no. of unique triplets)) __ Space Complexity: O(no. of the unique triplets)
/*
Approach : For each element arr[i] we check for other two elements arr[j] & arr[k] such that arr[i]+arr[j]+arr[k] == 0 where j belongs to i+1 to n-1 
and k belongs to j+1 to n-1. If such a triplet is found then we store the triplet in a temp vector and then sort the temp vector. After that the temp
vector is inserted in the set. Sorting is done to avoid insertion of duplicates in the set. Even though we are using set and set doesn't store duplicates
but still triplets like [-1,0,1], [0,-1,1], [1,0,-1] etc are considered different (because these have different elements at different indexes) 
and will get inserted in the set if not sorted. So to avoid this we first sort the triplet and then insert it in the set. 
Since after sorting such triplets become equal like here [-1,0,1], [0,-1,1], [1,0,-1] all becomes [-1,0,1] after sorting and will be inserted in the set
only once. 

Complexity Analysis --> 
Time Complexity :-  O(N3 * log(no. of unique triplets)), where N = size of the array.
Reason: Here, we are mainly using 3 nested loops. And inserting triplets into the set takes O(log(no. of unique triplets)) time complexity. 
But we are not considering the time complexity of sorting as we are just sorting 3 elements every time.

Space Complexity :-  O(no. of the unique triplets).
Apart from the answer vector of triplets (or list) we are using a set (to store unique triplets) and a temp vector. 
This temp vector will take O(3) space which is constant and thus not considered but the set will take O(no. of unique triplets) space.
*/ 
vector<vector<int>> _3SumBrute(vector<int> arr) {
    int n = arr.size();
    set <vector<int>> st;

    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            for(int k=j+1; k<n; k++) {
                if (arr[i]+arr[j]+arr[k] == 0) {
                    vector<int> temp = {arr[i], arr[j], arr[k]};
                    // sorting the triplet to avoid duplicates
                    // since there are only 3 elements in the triplets so sorting will happen in O(3 log 3) time which is O(1)
                    sort(temp.begin(), temp.end()); 
                    st.insert(temp);                // inserted in a set to avoid duplicates
                }
            }
        }
    }

    vector<vector<int>> ans(st.begin(), st.end());  // all set triplets are inserted in the ans vector
    return ans;
}

// Better Approach (using hashing) :- Time Complexity: O(N^2 * log(no. of unique triplets)) __ Space Complexity: O(no. of unique triplets) + O(N)
/*
Approach :- We try to optimise the complexity by reducing the number of loops required. Since we need to check for the sum of three elements to be 0 
then if the two elements are x & y (say) then the third element should be -(x+y) then only the sum is 0. So while looping we use a hashset to store 
the elements and check for the existence of the third element (here -(arr[i] +  arr[j]) ) in the hashset and if it exists that means a triplet 
(arr[i], arr[j], -(arr[i]+arr[j]) ) exists so we store it in the set (using the same storing approach used earlier). 
Before the second loop we define a hashset and in the loop we start iterating and checking for the third element existence in the hashset. If the third 
element exists in the hashset we simply add the triplet also at the end of each iteartion we add current element to the hashset because the current 
element could be third element for some future element. 
________________________________________________________________________________________________________________________________________________________
Que ) Why we are not inserting all the array elements in the HashSet and then searching for the third element ?

Let’s understand this intuition using an example. Assume the given array is {1, 2, -1, -2, 4, 0, -1} and the target = 0. 
Now, we will notice a situation like the following:-
when i = 3 and j = 4 then arr[i] = -2 and arr[j] = 4.
Therefore, the third element arr[k] = -(arr[i]+arr[j]) = -(-2+4) = -2

Now if we had stored all the elements in the set previously then while searching for -2 we would have picked the same element -2 at index 3 since it 
would've existed in the set but this triplet would have been invalid. So this is why we can't store all the elements into the set data structure.
________________________________________________________________________________________________________________________________________________________

Complexity Analysis

Time Complexity: O(N^2 * log(no. of unique triplets)), where N = size of the array.
Reason: Here, we are mainly using 2 nested loops. And inserting triplets into the set takes O(log(no. of unique triplets)) time complexity. 

Space Complexity: O(no. of unique triplets) + O(N) as we are using a set data structure to store the triplets 
and extra O(N) for storing the array elements in another set.
*/

vector<vector<int>> _3SumBetter(vector<int> arr) {
    int n = arr.size();
    set<vector<int>> st;
    for(int i=0; i<n; i++) {
        set<int> hashset;           // hashset to store the array elements and to check for the existence of third element in the array

        for(int j=i+1; j<n; j++) {
            int third = -(arr[i] + arr[j]);             // third element
            if (hashset.find(third) != hashset.end()) { // if third element exists in the hashset then store that triplet in the set
                vector<int> temp = {arr[i], arr[j], third};
                sort(temp.begin(), temp.end());
                st.insert(temp);
            }

            hashset.insert(arr[j]);
        }
    }

    vector<vector<int>> ans(st.begin(), st.end());              // store the set in the answer
    return ans;
}

// Optimal Approach (Two Pointer Approach) :- Time Complexity: O(NlogN)+O(N^2) __ Space Complexity: O(1)
/*
This is just like the optimal approach for two sum where we used two pointer technique on a sorted array to find a pair with a targeted sum. 
Suppose (x,y,z) is a triplet so x+y+z = 0. Now for every element x in the array we say x is a part of a triplet if a pair (y,z) exists whose sum is -x.
If such a pair exists for the element then we say that (x,y,z) is a triplet and we store it in the answer list. This finding of pair can be done using 
two pointer technique. This will require a target_sum which will be equal to - arr[i] for each element arr[i] and we will check from index i+1 to end 
to find pairs with the target_sum.
Alternatively we can do so without using a target sum .. for each arr[i] we take two pointers j & k and find the sum arr[i]+arr[j]+arr[k]. If sum == 0
we have found the triplet if sum > 0 we need to decrement the sum so we decrement the end pointer j, else if sum < 0 we need to increase the sum so 
we increment the start pointer which is j. This alternative approach is used in getTriplets function.
Both these approaches are similar just a minute difference to check for triplets.
_______________________________________________________________________________________________________________________________________________________
Complexity Analysis

Time Complexity: O(NlogN)+O(N2), where N = size of the array.
Reason: The pointer i, is running for approximately N times. And both the pointers j and k combined can run for approximately N times including the 
operation of skipping duplicates. So the total time complexity will be O(N2). 

Space Complexity: O(1)
*/
vector<vector<int>> getTriplets(vector<int> arr) {
    int n = arr.size();
    sort(arr.begin(), arr.end());
    vector<vector<int>> ans;
    for(int i=0; i<n; i++) {
        if (i>0 && arr[i] == arr[i-1]) continue;

        int start = i+1, end = n-1;
        int target_sum = -(arr[i]);
        while (start < end) {
            int sum = arr[start] + arr[end];
            // if sum > target_sum means we need to lower the sum so we move end pointer towards the left i.e. decrement the end pointer
            if (sum > target_sum) end--;
            // else if when sum < target_sum means we need to increase the sum so we move start pointer to the right i.e. increment the start pointer
            else if (sum < target_sum) start++;
            // else when sum == target_sum means a pair with targeted sum is present so we add it
            else {
                vector<int> temp = {arr[i], arr[start], arr[end]};
                ans.push_back(temp);
                start++;
                end--;
                // for duplicate elements we don't want to store the same triplet again so we move start & end pointers as to avoid taking duplicates
                while (start < end && arr[start] == arr[start-1]) start++;
                while (start < end && arr[end] == arr[end+1]) end--;
            } 
        }
    }
    return ans;
}

vector<vector<int>> threeSum(vector<int>& nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    vector<vector<int>> ans;
    for(int i=0; i<n; i++) {
        // skip the i duplicates 
        if (i>0 && nums[i] == nums[i-1]) continue;
        int j = i+1;
        int k = n-1;
        while (j < k) {
            int sum = nums[i] + nums[j] + nums[k];
            if (sum > 0) k--;       // decrement the end pointer to decrease the sum
            else if (sum < 0) j++;  // increment the start pointer to increase the sum
            else {
                vector<int> temp = {nums[i], nums[j], nums[k]};
                ans.push_back(temp);
                j++;
                k--;
                //skip the duplicates:
                while(j < k && nums[j] == nums[j-1]) j++;
                while(j < k && nums[k] == nums[k+1]) k--;
            }
        }
    }
    return ans;
}

int main() {
    vector<int> arr = {-1,0,1,2,-1,-4};
    vector<vector<int>> triplets = getTriplets(arr);
    cout << "Triplets are: " << endl;
    for(vector<int> triplet : triplets) {
        cout << "Triplet :- ";
        for (int x : triplet) {
            cout << x << " ";
        }
        cout << endl;
    }
    return 0;
}