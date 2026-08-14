/*
GFG - Pairs with Less Than K Diff : Easy

Given an array arr[] of positive integers and an integer k, 
find the total number of pairs of elements that have an absolute difference strictly less than k.

Note:  Pair (i, j) is considered the same as (j, i).

Examples :-

Input : arr[] = [1, 10, 4, 2], k = 3
Output : 2
Explanation: We have an array arr[] = [1, 10, 4, 2] and k = 3. 
We can make only two pairs with a difference of less than 3. (1, 2) and (4, 2). So, the answer is 2.

Input : arr[] = [2, 3, 4], k = 5
Output : 3
Explanation:  For the given array arr[] = [2, 3, 4] and k = 5, 
there are 3 valid pairs where the absolute difference between the pair's elements is less than 5. 
These pairs are (2, 3), (2, 4), and (3, 4). Hence, the output is 3.

Constraints :-
• 1 ≤ arr.size() ≤ 10^5
• 0 ≤ k ≤ 10^5
• 1 ≤ arr[i] ≤ 10^5
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach : Time Complexity : O(n^2) __ Space Complexity : O(1)
/*
The idea is to check the absolute diff of all pairs and count those with absolute diff. less than k.
We can use two nested loops to get all the pairs of array and count the suitable pairs.
We can maintain a counter initialized with value 0.
If the absolute diff. between the pair elements is less than k, we can increment the counter.
This counter will represent the count of valid pairs.
*/
int countPairsNaive(vector<int>& arr, int k) {
    int n = arr.size();
    int cnt = 0;

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (abs(arr[j] - arr[i]) < k)
                cnt++;

    return cnt;
}

// Better Approach (Using Sorting + Binary Search) : Time Complexity : O(n log n) __ Space Complexity : O(1)

/*
My approach:- 
Firstly sort the array.
Now, for each element arr[i], we need to count how many elements can form valid pairs with arr[i].
Valid pairs are those which have a absolute diff. less than k.
So, we need to count the elements which have value < (arr[i] + k) 
and >= arr[i] (since smaller values would have been previously considered as pairs for smaller elements),
since only these elements will form valid pairs. 

Assume sorted_arr = {1, 2, 4, 4, 5, 10}, k = 4
Now, for i = 0, arr[i] = 1, it can form pairs with all elements which have value < arr[i] + k, i.e, < 5
So, it form pairs with 2, 4 and 4. Pairs are (1, 2), (1, 4), (1, 4)
Instead of manually counting these pairs, we can use binary search 
to find the index of the largest element which is < arr[i] + k (or, <= arr[i] + k - 1)
For current scenario, that index is 3 which belongs to the 2nd occurrence of 4.
So, element arr[i] can form pairs with the elements from i+1 to this index 3.
So, we increment (ind - i) to count.

There could be cases when a certain element arr[i] don't have any elements to pair with.
Like for arr[i] = 5, it doesn't have any bigger elements it can pair with (although it is already paired with smaller elements).
For that case, the binary search would return -1 or start - 1 (as I have used a start to mark the beginning of search space).
We would need to consider these scenarios as well when no such element exists and increment count only when exists.

>> Complexity Analysis 

-> Time Complexity
• Sorting : O(n log n)
• Finding the count of pairs for each element using binary search : O(n) * O(log n) = O(n log n)
Total : O(n log n)

-> Space Complexity : O(1), no extra space used.
*/ 

// returns the max. index `ind` such that arr[index] <= x.
/*
Since, the array is sorted, we know that for arr[i], 
all elements before index `i` will be smaller than x (since x = arr[i] + k - 1)
So, instead of searching in the entire array as search space, we can begin the search with search space [i, end].
Although it is not a big optimization, but this could save some few search space adjustments.
*/ 
int getIndexLesserEqual(vector<int>& arr, int x, int start) {
    int low = start, high = arr.size()-1;
    
    while (low <= high) {
        int mid = (low + high) / 2;
        
        if (arr[mid] <= x) low = mid + 1;
        else high = mid - 1;
    }
    
    return high;
}

int countPairs1(vector<int>& arr, int k) {
    if (k == 0) 
        return 0;
    
    int n = arr.size();
    
    sort(arr.begin(), arr.end());
    
    int cnt = 0;
    
    for (int i = 0; i < n-1; i++) {
        int x = arr[i] + k - 1;
        
        int ind = getIndexLesserEqual(arr, x, i);
        
        if (ind > i)
            cnt += (ind - i);
    }
    
    return cnt;
}

// Using lower bound (other logic for sorting + binary search)
/*
The idea is to first sort the array and process each element one by one. 
For every element, use binary search to find the first element greater than or equal to arr[i] + k, 
and count all elements before it as valid pairs.

This first element greater than or equal to arr[i] + k, is lower bound of arr for value arr[i] + k.

>> Working of Approach:
• Sort the array so that elements with smaller differences are grouped together, enabling binary search.
• For each element arr[i], find the first element greater than or equal to arr[i] + k using lower_bound() (say it returns y).
• All elements between indices i + 1 and y - 1 form valid pairs with arr[i].
• Add these counts for every element and return the total number of valid pairs.
*/
int countPairs2(vector<int> &arr, int k) {
    int n = arr.size();

    // Sort the array in non-decreasing order
    sort(arr.begin(), arr.end());

    int res = 0;

    // Iterate through each index
    for (int i = 0; i < n; i++)
    {
        // val stores the threshold value; elements strictly less
        // than val will have a difference with arr[i] less than k.
        int val = arr[i] + k;

        // Find the index of the first element in the array which is
        // greater than or equal to val.
        int y = lower_bound(arr.begin(), arr.end(), val) - arr.begin();
        // lower_bound returns iterator, so we get corresponding index 
        // by subtracting arr.begin() from returned iterator

        // Add the count of all valid pairs possible for the current arr[i]
        res += (y - i - 1);
    }
    return res;
}

// Optimal Approach (Using Sorting + Sliding Window) : Time Complexity : O(n log n) __ Space Complexity : O(1)
/*
The idea is to sort the array and use two pointers, s and i, to maintain a sliding window. 
As the right pointer i traverses the array, advance the left pointer s forward until arr[i] - arr[s] < k,
i.e., until the difference between arr[i] & arr[s] doesn't get lesser than k. 
When it does, all the elements from index s to i-1, form valid pairs with arr[i], and we add (i - s) to our total count.

>> Complexity Analysis 
-> Time Complexity
• Sorting : O(n log n)
• Sliding window traversal : In the worst case, the two window pointers can traverse the whole array twice.
    So, O(2n) in worst case, which is essentially O(n)
Total: O(n log n) + O(n) ~ O(n log n)

Unlike the binary search approach, this sliding window approach only takes O(n) time once the array is sorted.

-> Space Complexity : O(1)
*/
int countPairs(vector<int> &arr, int k) {
    int n = arr.size();

    // Sort the array in non-decreasing order
    sort(arr.begin(), arr.end());

    int total = 0;
    int s = 0;      // left pointer (start of current window)

    // Iterate with right pointer i
    for (int i = 0; i < n; i++) {
        // Shrink the window from the left until the condition holds, it stops when window becomes valid
        while (arr[i] - arr[s] >= k)
            s++;

        // All elements between's' and 'i-1' form a valid pair with 'arr[i]'
        total += (i - s);
    }

    return total;
}

int main() {
    return 0;
}