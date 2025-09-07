/*
Leetcode - 31 : Next Permutation : Medium

A permutation of an array of integers is an arrangement of its members into a sequence or linear order.
For example, for arr = [1,2,3], the following are all the permutations of arr: [1,2,3], [1,3,2], [2, 1, 3], [2, 3, 1], [3,1,2], [3,2,1].
The next permutation of an array of integers is the next lexicographically greater permutation of its integer. 
More formally, if all the permutations of the array are sorted in one container according to their lexicographical order, 
then the next permutation of that array is the permutation that follows it in the sorted container. 
If such arrangement is not possible, the array must be rearranged as the lowest possible order (i.e., sorted in ascending order).

For example, the next permutation of arr = [1,2,3] is [1,3,2].
Similarly, the next permutation of arr = [2,3,1] is [3,1,2].
While the next permutation of arr = [3,2,1] is [1,2,3] because [3,2,1] does not have a lexicographical larger rearrangement.

Given an array of integers nums, find the next permutation of nums.

The replacement must be in place and use only constant extra memory.
*/

#include <bits/stdc++.h>
using namespace std;

// There is a built-in function next_permutation in STL which can be used to find the next permutation of an array.
// The function takes two iterators as input and returns true if the next permutation is found, otherwise false.

/*
Brute Force Approach :- Generate all possible permutations for the array and store those in a lexicographically sorted fashion in a 2D array
Search for the given permutation in that array and return the next permutation in the array. In case the given permutation is last return the 
first permutation in the array. 
Time Complexity : O(n! * n) where n is the size of the array. , Space Complexity : O(n! * n) where n is the size of the array.
This approach is not feasible for large inputs as the time and space complexity is very high.
*/

// Optimal Approach
/*
We check for a dip or breakpoint in the graph of elements .. we are interested in the increasing part which is closest to the array end.
This break point occurs when we encounter an array element arr[i] such that arr[i] < arr[i+1].  
So start iterating from the array end and check for an element arr[i] such that arr[i] < arr[i+1]. This element arr[i] is the breakpoint element
because we can find element bigger than arr[i] and re-arrange them to get the next permutation. 
Ex-> consider [3, 1, 4, 2, 0] while iterating from end we see 0 < 2 & 2 < 4 so we can't choose them as we can't possibly arrange these elements to get 
the lexicographically next permutation since any combination of 0, 2 & 4 will only be previous permutations. 
But we then see that 1 < 4 so the elements 1, 4, 2 & 0 can be re-arranged to get the next permutation but how to arrange them that's the question. 
We arrange them by firstly finding the least greatest element to 1 which is 2 here (3 & 4 are also larger but not the nearest to 1). 
Now we swap 1 & 2 so array becomes [3, 2, 4, 1, 0] but still this is not the next permutation so to find it we sort the array afterwards that index.
so here we sort the array elements after of 2. array becomes -> [3, 2, 0, 1, 4]
*/
void nextPermutation(vector<int>& nums) {
    int n = nums.size();
    int ind = -1;           // index of break-point or dip
    for(int i=n-2; i>=0; i--) {
        if (nums[i] < nums[i+1]) {
            ind = i;
            break;
        }
    }
    // if ind is -1 that means the whole array is in decreasing order or is already at the maximum permutation. So to find the next permutation 
    // we get the first permutation which is the sorted array itself. But since the array is reverse sorted so to sort it we just reverse it.
    // ex-> [4,3,2,1,0] after reversing it becomes [0,1,2,3,4].
    if (ind == -1) {
        reverse(nums.begin(), nums.end());      // reversal can be done in O(n/2) while sorting needs O(n log n)
        return;
    }
    
    // find the least max element in the range ind+1 - end and swap it with ind element 
    // since we know that the elements from ind+1 to end are in decreasing order so to get the least maximum element to ind element we traverse 
    // from end and check for an element greater than arr[ind], break out of traversal once such element is encountered.
    for(int i=n-1; i>ind; i--) {
        if (nums[i] > nums[ind]) {
            swap(nums[ind], nums[i]);
            break;
        }
    }

    // sort the right half of array from the ind index + 1 to end , since this right half is reverse sorted we simply reverse it to sort it
    reverse(nums.begin() + ind + 1, nums.end());
}

int main() {
    vector<int> arr = {3, 1, 4, 2, 0};
    vector<int> arr2 = {3, 1, 4, 2, 0, 5, 6, 9, 8, 7};
    int n = arr.size();

    // Using STL function to find the next permutation
    // next_permutation(arr.begin(), arr.end());
    nextPermutation(arr);

    cout << "Next permutation is: ";
    for(int x : arr) cout << x << " ";
    return 0;
}

/*
1234 1243 1324 1342 1423 1432
2134 2143 2314 2341 2413 2431
3124 3142 3214 3241 3412 3421
4123 4132 4213 4231 4312 4321
*/