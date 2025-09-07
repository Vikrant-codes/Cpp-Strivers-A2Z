/*
Leetcode - 4. Median of Two Sorted Arrays 

Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.
The overall run time complexity should be O(log (m+n)).

Examples :-

Input: nums1 = [1,3], nums2 = [2] __ Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.

Input: nums1 = [1,2], nums2 = [3,4] __ Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
 

Constraints :- 
nums1.length == m __ nums2.length == n
0 <= m <= 1000 __ 0 <= n <= 1000 __ 1 <= m + n <= 2000
-10^6 <= nums1[i], nums2[i] <= 10^6
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach :- Time Complexity : O(m + n) __ Space Complexity : O(m + n)
/*
The extremely naive approach is to merge the two sorted arrays and then find the median in that merged array.

How to merge two sorted arrays ? 
We can use the merge approach used in merge Sort to merge two sorted arrays. Use two pointers one for each array 
Run a loop find the smaller element from both of the arrays and add it to the third array. Increment the respective pointers while doing so.

How to find Median ?
Once we get the merged array finding the median is very easy. Let n = n1 + n2 be the size of the merged array, then
If n is odd : median is at index n / 2.. ex- for a sorted array of size 7 median is at index (int) 7/2 = (int) 3.5 = 3
If n is even : median is the average of elements at index n/2 & n/2 - 1. So median = (arr3[n/2] + arr3[n/2-1]) / 2
*/

double findMedianBrute(vector<int>& nums1, vector<int>& nums2) {
    int m = nums1.size();
    int n = nums2.size();
    vector<int> arr;

    int i=0, j=0;
    while (i < m && j < n) {
        if (nums1[i] <= nums2[j]) arr.push_back(nums1[i++]);
        else arr.push_back(nums2[j++]);
    }
    while (i < m) arr.push_back(nums1[i++]);
    while (j < n) arr.push_back(nums2[j++]);

    int s = m + n; 

    if (s % 2 != 0) return arr[s / 2];
    return ((double) (arr[s / 2 - 1] + arr[s / 2]) ) / 2.0;
}

// Better Approach :- Time Complexity : O(m + n) __ Space Complexity : O(1)
/*
To optimize the space used in the previous approach, we can eliminate the third array used to store the final merged result. 
After closer examination, we realize that we only need the two middle elements at indices (n1+n2)/2 and ((n1+n2)/2)-1, 
rather than the entire merged array, to solve the problem effectively.

We will stick to the same basic approach, but instead of storing elements in a separate array, we will use a counter 'k' to represent the imaginary 
third array's index. As we traverse through the arrays, when 'k' reaches either index (n1+n2)/2 or ((n1+n2)/2)-1, we will store that particular element. 
This way, we can achieve the same goal without using any extra space.

Algorithm :-

> We will call the required indices as ind2 = (n1+n2)/2 and ind1 = ((n1+n2)/2)-1. Now we will declare the counter 'k' and initialize it with 0.
> Now, as usual, we will take two pointers i and j, where i points to the first element of arr1[] and j points to the first element of arr2[].
> Next, using a while loop( while(i < n1 && j < n2)), we will select two elements i.e. arr1[i] and arr2[j], and consider the smallest one among the two. 
Then, we will increase that specific pointer by 1.
> In addition to that, in each iteration, we will check if the counter ‘k’ hits the indices ind1 or ind2. when 'k' reaches either index ind1 or ind2, 
we will store that particular element. We will also increase the k by 1 every time regardless of matching the conditions.
> If arr1[i] <= arr2[j]: Check ‘k’ to perform necessary operations and increase i and ‘k’ by 1.
> Otherwise: Check ‘k’ to perform necessary operations and increase j and ‘k’ by 1.
> After that, the left-out elements from both arrays will be copied as it is into the third array. 
While copying we will again check the above-said conditions for the counter ‘k’ and increase it by 1.
> This way we can get the elements at the required indices and return the median value considering the total size is even or odd. 
*/

double findMedianBetter(vector<int>& nums1, vector<int>& nums2) {
    int m = nums1.size(), n = nums2.size();

    int s = m+n;
    int ind2 = s/2, ind1 = s/2 - 1;
    int ele2 = 0, ele1 = 0;
    int i=0, j=0, k=0;

    while (i < m && j < n) {
        if (nums1[i] <= nums2[j]) {
            if (k == ind1) ele1 = nums1[i];
            if (k == ind2) {
                ele2 = nums1[i];
                break;
            }
            i++;
        }
        else {
            if (k == ind1) ele1 = nums2[j];
            if (k == ind2) {
                ele2 = nums2[j];
                break;
            }
            j++;
        }
        k++;
    }
    while (i < m && k <= ind2) {
        if (k == ind1) ele1 = nums1[i];
        if (k == ind2) {
            ele2 = nums1[i];
            break;
        }
        i++; k++;
    }
    while (j < n && k <= ind2) {
        if (k == ind1) ele1 = nums2[j];
        if (k == ind2) {
            ele2 = nums2[j];
            break;
        }
        j++; k++;
    }
    if (s % 2 != 0) return ele2;
    return (double) (ele2 + ele1) / 2.0;
}

// Optimal Approach (Binary Search) :- Time Complexity : O( log( min(n1,n2) ) ) __ Space Complexity : O(1)
/*
We are going to use the Binary Search algorithm to optimize the approach.

The primary objective of the Binary Search algorithm is to efficiently determine the appropriate half to eliminate, 
thereby reducing the search space by half. It does this by determining a specific condition that ensures that the target is not present in that half.

Now, let’s learn through the following observations how we can apply binary search to this problem. 
First, we will try to solve this problem where n1+n2 is even and then we will consider the odd scenario.

Observations :-
Assume, n = n1+n2 i.e. the total length of the final merged array.

> Median creates a partition on the final merged array: Upon closer observation, we can easily show that the median divides the final merged array 
into two halves.

> Characteristics of each half:
>> Each half contains (n/2) elements.
>> Each half also contains x elements from the first array i.e. arr1[] and (n/2)-x elements from the second array i.e. arr2[]. 
The value of x might be different for the two halves.

> The unique configuration of halves: Considering different values of x, we can get different left and right halves
(x = the number of elements taken from arr1[] for a particular half). 

How to solve the problem using the above observations ?

> Try to form the unique left half: 
>> For a valid merged array, the configurations of the two halves are unique. So, we can try to form the halves with different values of x, where 
x = the number of elements taken from arr1[] for a particular half.
>> There's no need to construct both halves. Once we have the correct left half, the right half is automatically determined, consisting of the 
remaining elements not yet considered. Therefore, our focus will solely be on creating the unique left half.
>> How to form all configurations of left half: We know that the left half will surely contain x elements from arr1[] and (n/2)-x elements from arr2[]. 
Here the only variable is x. The minimum possible value of x is 0 and the maximum possible value is n1(i.e. The length of the considered array).

For all the values,[0, n1] of x, we will try to form the left half and then we will check if that half’s configuration is valid.

> Check if the formed left half is valid: For a valid left half, the merged array will always be sorted. So, if the merged array containing the 
formed left half is sorted, the formation is valid.
>> How to check if the merged array is sorted without forming the array: In order to check we will consider 4 elements, i.e. l1, l2, r1, r2.
--> l1 = the maximum element belonging to arr1[] of the left half.
--> l2 = the maximum element belonging to arr2[] of the left half.
--> r1 = the minimum element belonging to arr1[] of the right half.
--> r1 = the minimum element belonging to arr2[] of the right half.

How to apply Binary search to form the left half ?

> We will check the formation of the left half for all possible values of x. Now, we know that the minimum possible value of x is 0 and the maximum is 
n1(i.e. The length of the considered array). Now the range is sorted. So, we will apply the binary search on the possible values of x i.e. [0, n1].

> How to eliminate the halves based on the values of x: Binary search works by eliminating the halves in each step. Upon closer observation, 
we can eliminate the halves based on the following conditions:
>> If l1 > r2: This implies that we have considered more elements from arr1[] than necessary. So, we have to take less elements from arr1[] and 
more from arr2[]. In such a scenario, we should try smaller values of x. To achieve this, we will eliminate the right half (high = mid-1).
>> If l2 > r1: This implies that we have considered more elements from arr2[] than necessary. So, we have to take less elements from arr2[] and 
more from arr1[]. In such a scenario, we should try bigger values of x. To achieve this, we will eliminate the left half (low = mid+1).

Until now, we have learned how to use binary search but with the assumption that (n1+n2) is even. Let’s generalize this.
If (n1+n2) is odd: In the case of even, we have considered the length of the left half as (n1+n2) / 2. In this case, that length will be (n1+n2+1)/2. 
This much change is enough to handle the case of odd. The rest of the things will be completely the same.
As in the code, division refers to integer division, this modified formula (n1+n2+1) / 2 will be valid for both cases of odd and even.

What will be the answer i.e. the median ?

> If l1 <= r2 && l2 <= r1: This condition assures that we have found the correct elements. 
>> If (n1+n2) is odd: The median will be max(l1, l2).
>> Otherwise, median = (max(l1, l2) + min(r1, r2)) / 2.0

Note: We are applying binary search on the possible values of x i.e. [0, n1]. Here n1 is the length of arr1[]. 
Now, to further optimize it, we will consider the smaller array as arr1[]. So, the actual range will be [0, min(n1, n2)].
*/

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int n1 = nums1.size();
    int n2 = nums2.size();
    // we will write code assuming that nums1 is smaller in size than num2 
    if (n1 > n2) return findMedianSortedArrays(nums2, nums1);   // swap nums1 & nums2 if nums1 is bigger in size
    int n = n1 + n2;
    int required_on_left = (n + 1) / 2;
    int low = 0, high = n1;

    while (low <= high) {
        int mid1 = (low + high) / 2;
        int mid2 = required_on_left - mid1;
        int l1 = INT_MIN, l2 = INT_MIN;
        int r1 = INT_MAX, r2 = INT_MAX;
        // assign values to l1,l2,r1,r2 only if the corresponding indices exists in arrays
        if (mid1 < n1) r1 = nums1[mid1];
        if (mid2 < n2) r2 = nums2[mid2];
        if (mid1 - 1 >= 0) l1 = nums1[mid1 - 1];
        if (mid2 - 1 >= 0) l2 = nums2[mid2 - 1];
            
        if (l1 <= r2 && l2 <= r1) {
            if (n % 2 == 1) return max(l1, l2);
            return (double) (max(l1, l2) + min(r1, r2)) / 2.0;
        }
        else if (l1 > r2) high = mid1 - 1;
        else low = mid1 + 1;
    }
    return 0;       // dummy return statement... never actually run
}

int main() {
    vector<int> nums1 = {1,4,5,7,9};
    vector<int> nums2 = {2,3,6,8};
    double median = findMedianSortedArrays(nums1, nums2);
    cout << median;

    return 0;
}