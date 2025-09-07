/*
                                                Merge two Sorted Arrays Without Extra Space

Problem statement: Given two sorted arrays arr1[] and arr2[] of sizes n and m in non-decreasing order. Merge them in sorted order. 
Modify arr1 so that it contains the first N elements and modify arr2 so that it contains the last M elements.

Input: arr1[] = [1 4 8 10] __ arr2[] = [2 3 9]
Output: arr1[] = [1 2 3 4] __ arr2[] = [8 9 10]
Explanation: After merging the two non-decreasing arrays, we get, 1,2,3,4,8,9,10.

Input: arr1[] = [1 3 5 7] __ arr2[] = [0 2 6 8 9]
Output: arr1[] = [0 1 2 3] __ arr2[] = [5 6 7 8 9]
Explanation: After merging the two non-decreasing arrays, we get, 0 1 2 3 5 6 7 8 9.
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach : Time Complexity : O(n+m) + O(n+m) __ Space Complexity = O(n+m)
/*
Even though the problem states to solve without using any extra space we still use extra array to solve this using brute force as this approach also
helps to understand the optimal approaches.

Approach :- 
1. We will first declare a third array, arr3[] of size n+m, and two pointers i.e. left and right, one pointing to the first index of arr1[] and the 
other pointing to the first index of arr2[].
2. The two pointers will move like the following:
> If arr1[left] < arr2[right]: We will insert the element arr1[left] into the array and increase the left pointer by 1.
> If arr2[right] < arr1[left]: We will insert the element arr2[right] into the array and increase the right pointer by 1.
> If arr1[left] == arr2[right]: Insert any of the elements and increase that particular pointer by 1.
> If one of the pointers reaches the end, then we will only move the other pointer and insert the rest of the elements of that particular array 
into the third array i.e. arr3[].
If we move the pointer like the above, we will get the third array in the sorted order.
3. Now, from sorted array arr3[], we will copy first n(size of arr1[]) elements to arr1[], and the next m(size of arr2[]) elements to arr2[].
*/
void mergeBrute(vector<int>& arr1, int n, vector<int>& arr2, int m) {
    vector<int> arr3(m+n);
    int i=0, j=0, k=0;
    while (i < n && j < m) {
        arr3[k++] = (arr1[i] <= arr2[j]) ? arr1[i++] : arr2[j++];
    }
    while (i < n) {
        arr3[k++] = arr1[i++];
    }
    while (j < m) {
        arr3[k++] = arr2[j++];
    }
    // copy first n elements of arr3 to arr1
    for(int i=0; i<n; i++) {
        arr1[i] = arr3[i];
    }
    // copy the remaining m elements of arr3 to arr2
    for(int i=0; i<m; i++) {
        arr2[i] = arr3[n+i];
    }
}

// Optimal Approach 1 : Time Complexity : O(min(n, m)) + O(n*logn) + O(m*logm) __ Space Complexity : O(1)
/*
Approach :- We try to place all the smaller elements in arr1 and bigger elements in arr2. This can be done using two pointers.

1. We will declare two pointers i.e. left and right. The left pointer will point to the last index of the arr1[](i.e. the maximum element of the array). 
The right pointer will point to the first index of the arr2[] (i.e. the minimum element of the array).

2. Now, the left pointer will move toward index 0 and the right pointer will move towards the index m-1. 
While moving the two pointers we will face 2 different cases like the following:
> If arr1[left] > arr2[right]: In this case, we will swap the elements and move the pointers to the next positions.
> If arr1[left] <= arr2[right]: In this case, we will stop moving the pointers as arr1[] and arr2[] are containing correct elements.

3. Thus, after step 2, arr1[] will contain all smaller elements and arr2[] will contain all bigger elements. Finally, we will sort the two arrays

Complexity Analysis -->

Time Complexity: O(min(n, m)) + O(n*logn) + O(m*logm), where n and m are the sizes of the given arrays.
Reason: O(min(n, m)) is for swapping the array elements. Even in the worst case when all arr1 elements are greater than arr2 elements the while loop 
will still run for O(min(n,m)) since one of the two pointers will reach end and while loop will end. 
O(n*logn) + O(m*logm) are the time complexity for sorting the two arrays.

Space Complexity: O(1) as we are not using any extra space.
*/
void mergeOpt1(vector<int>& arr1, int n, vector<int>& arr2, int m) {
    int left = n-1;
    int right = 0;
    while (left >= 0 && right < m) {
        if (arr1[left] > arr2[right]) {
            swap(arr1[left], arr2[right]);
            left--;
            right++;
        }
        else break;
    }
    sort(arr1.begin(), arr1.end());
    sort(arr2.begin(), arr2.end());
}

// Optimal Approach 2 (using Gap method) :
/*
This gap method is based on a sorting technique called shell sort. 

Intuition ->

Similar to optimal approach 1, in this approach, we will use two pointers i.e. left and right, and swap the elements if the element at the left pointer 
is greater than the element at the right pointer. 
But the placing of the pointers will be based on the gap value calculated. The formula to calculate the initial gap is the following:
Initial gap = ceil((size of arr1[] + size of arr2[]) / 2)
Assume the two arrays as a single continuous array and initially, we will place the left pointer at the first index 
and the right pointer at the (left+gap) index of that continuous array.
Now, we will compare the elements at the left and right pointers and move them by 1 place each time after comparison. 
While comparing we will swap the elements if the left element > right element. 
After some steps, the right pointer will reach the end and the iteration will be stopped.
After each iteration, we will decrease the gap and will follow the same procedure until the iteration for gap = 1 gets completed. 
Now, after each iteration, the gap will be the following:
gap = ceil( previous gap / 2)

Complexity Analysis ->

Time Complexity: O((n+m)*log(n+m)), where n and m are the sizes of the given arrays.
Reason: The gap is ranging from n+m to 1 and every time the gap gets divided by 2. So, the time complexity of the outer loop will be O(log(n+m)). 
Now, for each value of the gap, the inner loop can at most run for (n+m) times. So, the time complexity of the inner loop will be O(n+m). 
So, the overall time complexity will be O((n+m)*log(n+m)).

Space Complexity: O(1) as we are not using any extra space.
*/

void swapIfGreater(vector<int>& arr1, vector<int>& arr2, int ind1, int ind2) {
    if (arr1[ind1] > arr2[ind2]) {
        swap(arr1[ind1], arr2[ind2]);
    }
}

void mergeOpt2(vector<int>& arr1, int n, vector<int>& arr2, int m) {
    int len = n+m;
    int gap = (len / 2) + (len % 2);        // this is same as ceil(len/2) since we needed to find the ceil value of len/2
    // why (len / 2) + (len % 2) = ceil(len/2) ? 
    // ceil(x/2) will be equal to x/2 when x is even and equal to x/2 + 1 when x is odd. Also for even x%2 = 0 and for odd x%2 = 1. 
    // so adding x%2 to x/2 will work the same as ceil function

    while (gap > 0) {
        int left = 0;
        int right = left + gap;
        // while the right pointer doesn't crosses the two arrays
        while (right < len) {
            // when left pointer is in arr1 and right is in arr2
            if (left < n && right >= n) {
                swapIfGreater(arr1, arr2, left, right - n);
                // since right is in arr2 so the concerned arr2 element will be at index right - n since both arrays are treated as single merged arrays
            }
            // when both left and right are in arr2
            else if (left >= n) {
                swapIfGreater(arr2, arr2, left-n, right - n);
                // both pointers in arr2 so to get the index we subtract length of arr1 which is n
            }
            // when both left and right are in arr1
            else {
                swapIfGreater(arr1, arr1, left, right);
            }
            left++, right++;
        }
        if (gap == 1) break;
        gap = (gap / 2) + (gap % 2);
    }
} 

int main() {
    vector<int> arr1 = {1,4,8,10};
    vector<int> arr2 = {2,3,9};
    mergeOpt2(arr1, 4, arr2, 3);

    cout << "arr1 = ";
    for(int x : arr1) cout << x << " ";
    cout << " __  arr2 = ";
    for(int x : arr2) cout << x << " ";

    return 0;
}