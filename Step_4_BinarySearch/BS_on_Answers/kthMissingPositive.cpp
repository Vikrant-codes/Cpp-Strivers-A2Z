/*
Leetcode - 1539. Kth Missing Positive Number -- Easy

Given an array arr of positive integers sorted in a strictly increasing order, and an integer k.
Return the kth positive integer that is missing from this array.

Examples :-

Input: arr = [2,3,4,7,11], k = 5 __ Output: 9
Explanation: The missing positive integers are [1,5,6,8,9,10,12,13,...]. The 5th missing positive integer is 9.

Input: arr = [1,2,3,4], k = 2 __ Output: 6
Explanation: The missing positive integers are [5,6,7,...]. The 2nd missing positive integer is 6.

Constraints :- 1 <= arr.length <= 1000 __ 1 <= arr[i] <= 1000 __ 1 <= k <= 1000 __ arr[i] < arr[j] for 1 <= i < j <= arr.length
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Approach :- The array is strictly increasing meaning that it is sorted and doesn't have any duplicates. 
We want to "simulate" counting the missing numbers. Initially, k refers to the position of the missing number we're looking for 
(i.e., the k-th one). The idea is :-

> Start from 1st element and move forward.
> Each time we see a number in the array arr that's ≤ k, it means: 
-> This number is not missing. 
-> So the missing numbers must be after it.
-> Thus, we shift k forward (i.e., k++), because the actual k-th missing number has also moved forward due to this non-missing number.

So we update k each time we encounter a number in arr that is ≤ k.
Once we hit a number in arr that is greater than k, we can stop. At that point, k holds the correct value of the k-th missing number.

-->> Initially we assume that all the first k integers are missing so k-th missing positive is 'k' itself. Now we loop through the array and when we 
encounter an element x such that x <= k that means 1 element is not missing in the range [1,k] so we increment k since now we know that a element is 
present in the array which we assumed to be absent. Similarly, we continue checking the elements and increment k for each element x such that x <= k. 
Once an element is encountered that is greater than k is found we end the loop. After the loop ends return k.

Ex- assume array = [2,5,7,8] and k = 4.. 
Initially we assume that missing = [1,2,3,4] and thus k = 4 is the k-th missing number
while iterating we see that 2 is present so we increment k by 1 since 2 is not missing.. missing = [1,3,4,5] assuming that the 4th missing no. is now 5
next element is 5 itself so 5 is also not missing thus we increment k by 1 (becomes 6) .. missing = [1,3,4,6] 
next element is 7 and 7 > 6 (k) and since the array is sorted we know that all the remaining elements which are less than 7 are missing so this 
assumed missing array is correct and the k-th (i.e. 4th) missing no is 6
*/
int findKthPositiveBrute(vector<int>& arr, int k) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        if (arr[i] <= k) k++; //shifting k
        else break;
    }
    return k;
}

// Optimal Approach (Binary Search): Time Complexity : O(log n) __ Space Complexity : O(1)
/*
Approach :- 
We will try to find the closest neighbors (i.e. Present in the array) for the kth missing number by counting the number of missing numbers 
for each element in the given array.

Let’s understand it using an example. Assume the given array is {2, 3, 4, 7, 11}. Now, if no numbers were missing the given array would look like 
{1, 2, 3, 4, 5}. Comparing these 2 arrays, we can conclude the following:
Up to index 0: Only 1 number i.e. 1 is missing in the given array.
Up to index 1: Only 1 number i.e. 1 is missing in the given array.
Up to index 2: Only 1 number i.e. 1 is missing in the given array.
Up to index 3: 3 numbers i.e. 1, 5, and 6 are missing.
Up to index 4: 6 numbers i.e. 1, 5, 6, 8, 9, and 10 are missing.
For a given value of k as 5, we can determine that the answer falls within the range of 7 to 11. 
Since there are only 3 missing numbers up to index 3, the 5th missing number cannot be before arr[3], which is 7. 
Therefore, it must be located somewhere to the right of 7. Our actual answer i.e. 9 also supports this theory. 
So, by following this process we can find the closest neighbors (i.e. Present in the array) for the kth missing number. 
In our example, the closest neighbors of the 5th missing number are 7 and 11.

-->> How to calculate the number of missing numbers for any index i?
From the above example, we can derive a formula to find the number of missing numbers before any array index, i. The formula is
Number of missing numbers up to index i = arr[i] - (i+1).
The given array, arr, is currently containing the number arr[i] whereas it should contain (i+1) if no numbers were missing. 
The difference between the current and the ideal element will give the result.

-->> How to apply Binary Search?
We will apply binary search on the indices of the given array. For each index, we will calculate the number of missing numbers and based on it, 
we will try to eliminate the halves.

-->> How we will get the answer after all these steps?
After completing the binary search on the indices, the pointer high will point to the closest neighbor(present in the array) that is smaller than the 
kth missing number. i.e. the last element which have the number of missing elements before that less than k.   
So, in the given array, the preceding neighbor of the kth missing number is arr[high]. 

Now, we know, up to index ‘high’, the number of missing numbers = arr[high] - (high+1) = p (say).

But we want to go further and find the kth number. To extend our objective, we aim to find the kth number in the sequence. 
In order to determine the number of additional missing values required to reach the kth position, we can calculate this as
more_missing_numbers = k - (arr[high] - (high+1)) = k - p.
(before high element p elements are already missing so we need to find k-p more missing elements)

Now, we will simply add more_missing_numbers to the preceding neighbor i.e. arr[high] to get the kth missing number.
kth missing number = arr[high] + more_missing_numbers = arr[high] + k - (missing_numbers_upto_arr[high])
    = arr[high] + k - p = arr[high] + k - (arr[high] - (high+1)) =  arr[high] + k - arr[high] + high + 1
    = k + high + 1 = k + low (since low = high + 1 (always))

So return k + high + 1 (or k + low)
*/
int findKthPositive(vector<int>& arr, int k) {
    int n = arr.size();
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        int missing = arr[mid] - mid - 1;   //how many elements are missing upto current element
        if (missing < k) low = mid + 1;
        else high = mid - 1;
    }
    return k + high + 1; // return k + low
}

int main() {
    vector<int> arr = {1,2,3,4,5,6,7,8,9,10};
    int k = 5;
    cout << "Kth Missing Positive Number (Brute Force): " << findKthPositiveBrute(arr, k) << endl;
    return 0;
}