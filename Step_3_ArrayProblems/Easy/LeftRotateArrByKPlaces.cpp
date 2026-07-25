// Left Rotate an Array by K steps

// GFG - Rotate Array : Medium
/*
GFG - Rotate Array : Medium

Given an array arr[]. 
Rotate the array to the left (counter-clockwise direction) by d steps, 
where d is a positive integer. Do the mentioned change in the array in place.

Note: Consider the array as circular.

Examples :-

Input: arr[] = [1, 2, 3, 4, 5], d = 2
Output: [3, 4, 5, 1, 2]
Explanation: when rotated by 2 elements, it becomes [3, 4, 5, 1, 2].

Input: arr[] = [2, 4, 6, 8, 10, 12, 14, 16, 18, 20], d = 3
Output: [8, 10, 12, 14, 16, 18, 20, 2, 4, 6]
Explanation: when rotated by 3 elements, it becomes [8, 10, 12, 14, 16, 18, 20, 2, 4, 6].

Input: arr[] = [7, 3, 9, 1], d = 9
Output: [3, 9, 1, 7]
Explanation: when we rotate 9 times, we'll get [3, 9, 1, 7] as resultant array.

Constraints :-
• 1 ≤  arr.size(), d ≤  10^5
• 0 ≤  arr[i] ≤  10^5
*/

#include <iostream>
#include <vector>
using namespace std;

// Naive Approach : Time Complexity : O(n * d) __ Space Complexity : O(1)
/*
>> Approach
Rotating an array to the left by k/d steps is the same as left shifting elements 1 place to the left k/d times.

Example: arr = [1, 2, 3, 4, 5, 6, 7], k/d = 3
We need to rotate the array to the left by 3 steps, it means the first 3 elements must go to the end.
Rotated arr = [4, 5, 6, 7, 1, 2, 3]
Now, this is same as left rotating the array by 1 place for total 3 (k) times
1st left shift by 1 place :- arr = [2, 3, 4, 5, 6, 7, 1]
2nd left shift by 1 place :- arr = [3, 4, 5, 6, 7, 1, 2]
3rd left shift by 1 place :- arr = [4, 5, 6, 7, 1, 2, 3]

Also, notice one thing, assume k was 7, then, 
we would need to perform the left rotation by 7 steps, which will gives us the same array back (since its size is also 7).

So, if k was more than size of arr, like if k was 9, then doing 9 rotations is same as doing 2 rotations 
since the frist 7 rotations will give us the same array back.
So, in case k > n, we can do k = k % n, so we don't perform extra rotations.

>> Time Complexity Analysis :-
- Left Rotating array by 1 place takes O(n)
- This leftRotate method is called total k/d times, so O(n * d)
*/
void leftRotate1Place(vector<int>& arr) {
    int n = arr.size();
    int temp = arr[0];
    
    for (int i = 0; i < n-1; i++)
        arr[i] = arr[i+1];
        
    arr[n-1] = temp;
}

void rotateArrNaive(vector<int>& arr, int d) {
    int n = arr.size();
    
    d = d % n;
    
    while (d--) {
        leftRotate1Place(arr);
    }
}


// Better Approach 1 : Time Complexity : O(2n) __ Space Complexity : O(n)
/*
>> Approach 
The idea is to use a temp vector to store the k-left-shifted arr values.
Using the temp vector, we can get the rotated arr elements in a single traversal of arr.

Left rotation by k steps means we need to place the first 'k' elements of arr to the end and 
move the next n-k elements to the start of arr.

So, we use a temp vector and place elements in this vector in rotated order itself, i.e.,
the last n-k elements are stored in the start indices of temp vector, 
and then the first k elements of arr are stored at the later indices of temp vector.

Once we get the temp vector, we can simply copy its value to arr to get the rotated array.

Example : arr = [1, 2, 3, 4, 5, 6, 7], k = 3
We need to left shift array by 3 places (meaning the first 3 elements must move to the end)
We use a temp vector, temp = []
Place the last n-k elements to the start of temp: last n-k elements = 7-3 = last 4 elements => temp = [4, 5, 6, 7]
Now, place the first k elements of arr to the end of temp: temp = [4, 5, 6, 7, 1, 2, 3]
Now, temp contains the elements in the k-rotated order. So, we just copy elements from temp back to arr.
*/
void rotateArrBetter1(vector<int>& arr, int d) {
    int n = arr.size();
    d = d % n;
    
    vector<int> temp(n);
    
    // place the last n-d elements to the start of temp vector
    // for (int i = d; i < n; i++)
    //     temp[i-d] = arr[i];
    
    // place the first d elements of arr to the end of temp vector
    // for (int i = 0; i < d; i++)
    //     temp[n - d + i] = arr[i];

    // If we consider arr as a circular array, 
    // then we can also directly place all the elements of arr to their corresponding places in temp vector

    // store the elements of arr to their correct position in temp (considering arr as a circular array)
    for (int i = 0; i < n; i++)
        temp[i] = arr[(i + d) % n];
    
    // copy the elements from temp vector back to arr
    for (int i = 0; i < n; i++)
        arr[i] = temp[i];
}

// Better Approach 2 : Time Complexity : O(n + d) __ Space Complexity : O(d)
/*
>> Approach
If we try to make the changes in place directly in arr, 
the problem we will face is that the first k elements value will be lost in the process.
When left shifting the array by 1 place, we used a temp variable to store the 1st element (index 0), 
so that its value is not lost and we can then shift the remaining n-1 elements to left.

In a similar way, we can also store the first k elements to a temp array so that the first k values are not lost.
Then we can shift the remaining n-k elements to the left and 
after that we can place the first k values stored in temp to the last k indices of arr.

Example : arr = [1, 2, 3, 4, 5, 6, 7], k = 3
Store the first 3 (k) elements to a temp array or else there values would get lost during left shifting
temp = [1, 2, 3]

Now, left shift the remaining n - k elements of arr to k places each
arr will become, arr = [4, 5, 6, 7, 5, 6, 7]
Now, we just need to place the values from temp array ([1, 2, 3]) to the last k (3) indices of arr
arr = [4, 5, 6, 7, 1, 2, 3]
*/
void rotateArrBetter2(vector<int>& arr, int d) {
    int n = arr.size();
    d = d % n;
    
    vector<int> temp(d);
    
    // store the first d elements of arr to temp array so their values are not lost
    for (int i = 0; i < d; i++)
        temp[i] = arr[i];
        
    // left shift the remaining n-d elements of arr to d positions
    for (int i = d; i < n; i++)
        arr[i-d] = arr[i];
    
    // place the values stored in temp array to the last d indices of arr

    // int p = 0;
    // for (int i = n-d; i < n; i++){
    //     arr[i] = temp[p];
    //     p++;
    // }    
    
    for (int i = n - d; i < n; i++)
        arr[i] = temp[i - (n - d)];
}

// Optimal Approach : Time Complexity : O(2n) __ Space Complexity : O(1)
/*
>> Approach 
The approach is based on some observations using reverse of array portions
Assume, arr = [1, 2, 3, 4, 5, 6, 7], k = 3
We want to left shift/rotate it by k places.
The final array must look like this [4, 5, 6, 7, 1, 2, 3]

If we reverse the first k elements of arr (from index 0 to k-1), then arr would become [3, 2, 1, 4, 5, 6, 7]
Now, we reverse the remaining n-k elements (from index k to n-1), then arr becomes [3, 2, 1, 7, 6, 5, 4]
Now, we reverse the whole array (from index 0 to n-1), arr becomes [4, 5, 6, 7, 1, 2, 3]

Notice, that we got the desired result, so to get the left rotated array we just need to make the following reversals:
- Reverse the first k elements (index 0 to k-1)
- Reverse the next n-k elements (index k to n-1)
- Reverse the whole array (index 0 to n-1)
In this way, we get the required left rotated array.

>> Time Complexity Analysis :-
- Reverse helper method takes O(x) time where x is the no. of elements to be reversed.
- Now, we do the following 3 reversals :
    - Reverse the first k elements : This will take O(k)
    - Reverse the next n-k elements : This will take O(n-k)
    - Reverse the whole array (all n elements) : This takes O(n)
So, total: O(k) + O(n-k) + O(n) = O(k + n - k + n) = O(2n)
*/
void reverse(vector<int>& arr, int start, int end) {
    while (start < end) {
        // swap arr[start], arr[end]
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        
        start++;
        end--;
    }
}
void rotateArr(vector<int>& arr, int d) {
    int n = arr.size();
    d = d % n;
    
    reverse(arr, 0, d-1);
    reverse(arr, d, n-1);
    reverse(arr, 0, n-1);
}



int main() {
    return 0;
}