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

// Optimal Approach (Reversal Algorithm) : Time Complexity : O(2n) __ Space Complexity : O(1)
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
void rotateArrReversal(vector<int>& arr, int d) {
    int n = arr.size();
    d = d % n;
    
    reverse(arr, 0, d-1);
    reverse(arr, d, n-1);
    reverse(arr, 0, n-1);
}

// ⚠️ Juggling Algorithm -- Not for beginners

// Most Optimal Approach (Juggling Algo) : Time Complexity : O(n) __ Space Complexity : O(1)
/*
| Juggling Algorithm

>> Intuition
The brute-force approach repeatedly shifts the array one position to the left, which takes O(n × k) time. 
We can do better by observing that every element has a fixed destination after the rotation.

Instead of shifting the array multiple times, we directly move each element to its final position. 
However, moving an element immediately overwrites the value already present at its destination. 
The Juggling Algorithm solves this by processing the array in cycles, ensuring that no value is lost.

The idea behind Juggling Algorithm is that we can rotate all elements of array using cycles. 
Each cycle is independent and represents a group of elements that will shift among themselves during the rotation. 
If the starting index of a cycle is i, then next elements of the cycle will be present at indices 
(i + d) % n, (i + 2d) % n, (i + 3d) % n ... 
and so on till we reach back to index i. 

So for any index i, we know that after rotation we will have arr[(i + d) % n] at index i. 
Now, for every index in the cycle, we will place the element which should be present at that index after the array is rotated.

Each cycle is traversed using a single temporary variable, making the algorithm both in-place and O(n).

>> Key Observation
For a left rotation by k positions:
- The element currently at index i should eventually be replaced by the element at: 
    (i + k) % n
, where n is the size of the array.
Thus, starting from an index i, we repeatedly jump by k positions (modulo n) until we return to the starting index. 
This sequence of indices forms a cycle.

>> Why Do We Need Cycles?
Suppose we have:
arr = [1, 2, 3, 4, 5, 6, 7]
k = 2

If we immediately perform
arr[0] = arr[2]
the value at index 0 (which is 1) is overwritten.
To avoid losing it:
1. Store the first value in a temporary variable.
2. Move each subsequent element into its predecessor's position.
3. Once the cycle returns to the starting index, place the stored value into the last vacant position.
Thus, every element is moved exactly once.

>> Why Does gcd(n, k) Determine the Number of Cycles?
The indices are visited by repeatedly adding k modulo n.
Depending on whether n and k are coprime, two cases arise:
• If gcd(n, k) = 1, every index is reachable from any starting point. 
    The entire array forms a single cycle.
• If gcd(n, k) > 1, the indices split into multiple independent groups. 
    Each group forms its own cycle, so we must process each cycle separately.

Each cycle contains n / gcd(n, k) elements.
Since there are n total elements, the number of disjoint cycles is
    cycle_count = total elements / count of element in each cycle 
                = n / (n / gcd(n, k))
                = gcd(n, k)

>> Example 1 n and k are Coprime
arr = [1, 2, 3, 4, 5, 6, 7] 
n = 7
k = 2
gcd(n, k) = gcd(7, 2) = 1
Only one cycle exists for this example case.

The visited indices are: 0 → 2 → 4 → 6 → 1 → 3 → 5 → 0
Every index is visited exactly once before returning to the start.

Movement of values:
    Store arr[0]

    arr[0] ← arr[2]
    arr[2] ← arr[4]
    arr[4] ← arr[6]
    arr[6] ← arr[1]
    arr[1] ← arr[3]
    arr[3] ← arr[5]
    arr[5] ← stored value

Final array: [3, 4, 5, 6, 7, 1, 2]
Since every index belongs to the same cycle, processing this single cycle rotates the entire array.

>> Example 2: n and k are Not Coprime
arr = [1, 2, 3, 4, 5, 6, 7, 8]
n = 8
k = 2
gcd(8,2) = 2
Now there are two independent cycles.

Cycle 1: 0 → 2 → 4 → 6 → 0
Moves:
    Store arr[0]

    arr[0] ← arr[2]
    arr[2] ← arr[4]
    arr[4] ← arr[6]
    arr[6] ← stored value

Cycle 2: 1 → 3 → 5 → 7 → 1
Moves:
    Store arr[1]

    arr[1] ← arr[3]
    arr[3] ← arr[5]
    arr[5] ← arr[7]
    arr[7] ← stored value

Final array: [3, 4, 5, 6, 7, 8, 1, 2]
Notice that starting from index 0, we never visit any odd index.
Likewise, starting from index 1, we never visit any even index.
Therefore, the array naturally splits into two disjoint cycles, and both must be processed.

>> Algorithm
1. Compute k %= n.
2. Compute cycles = gcd(n, k).
3. For each cycle:
    • Store the starting element in a temporary variable.
    • Repeatedly jump by k positions (modulo n), shifting elements one step backward in the cycle.
    • Stop when the traversal returns to the starting index.
    • Place the stored element into the final vacant position.
4. After processing all cycles, every element has reached its correct position.

>> Correctness
The algorithm works because:
• Every index belongs to exactly one cycle.
• Every cycle is processed independently.
• Within a cycle, one temporary variable prevents data from being overwritten.
• Every element is moved exactly once.
• The union of all cycles covers every index in the array.
Therefore, the array is correctly rotated in-place.

>> Complexity Analysis

| Time Complexity: O(n)
• Every element is visited and moved exactly once.

| Space Complexity: O(1)
• Only one temporary variable is used regardless of the array size.
*/

// Helper method to get the gcd of two elements
int gcd(int a, int b) {
    if (b == 0)
        return a;
        
    return gcd(b, a % b);
}

// My Implementation
void rotateArr1(vector<int>& arr, int k) {
    int n = arr.size();
    k = k % n;
    
    if (k == 0) return;
    
    int cycles = gcd(n, k);
    
    for (int i = 0; i < cycles; i++) {
        int temp = arr[i];
        
        int j = i;
        
        do {
            int next = (j + k) % n;
            
            if (next != i) arr[j] = arr[next];
            else arr[j] = temp;
            
            j = next;
        } while(j != i);
    }
}

// Other Implementation
void rotateArr2(vector<int>& arr, int k) {
    int n = arr.size();
    k = k % n;
    
    if (k == 0) return;
    
    int cycles = gcd(n, k);
    
    for (int i = 0; i < cycles; i++) {
        int startEle = arr[i];
        
        int currIdx = i, nextIdx;
        
        while (true) {
            nextIdx = (currIdx + k) % n;
            
            if (nextIdx == i) {
                arr[currIdx] = startEle;
                break;
            }
            
            arr[currIdx] = arr[nextIdx];
            currIdx = nextIdx;
        }
    }
}

// ------------------------------------------------------------------------------------------------------------------------------

// Right Rotate Array by K places
// The similar approaches can be applied for right rotation as well
// See "Other Similar Problems -> 189_RotateArray"

int main() {
    return 0;
}