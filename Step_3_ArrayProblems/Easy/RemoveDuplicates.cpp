/*
Leetcode - 26. Remove Duplicates from Sorted Array : Easy

Given an integer array nums sorted in non-decreasing order, 
remove the duplicates in-place such that each unique element appears only once. 
The relative order of the elements should be kept the same.

Consider the number of unique elements in nums to be k​​​​​​​​​​​​​​. 
After removing duplicates, return the number of unique elements k.

The first k elements of nums should contain the unique numbers in sorted order. 
The remaining elements beyond index k - 1 can be ignored.

Custom Judge:

The judge will test your solution with the following code:
|    int[] nums = [...]; // Input array
|    int[] expectedNums = [...]; // The expected answer with correct length
|
|    int k = removeDuplicates(nums); // Calls your implementation
|
|    assert k == expectedNums.length;
|    for (int i = 0; i < k; i++) {
|        assert nums[i] == expectedNums[i];
|    }
If all assertions pass, then your solution will be accepted.

Examples :-

Input: nums = [1,1,2]
Output: 2, nums = [1,2,_]
Explanation: Your function should return k = 2, with the first two elements of nums being 1 and 2 respectively.
It does not matter what you leave beyond the returned k (hence they are underscores).

Input: nums = [0,0,1,1,1,2,2,3,3,4]
Output: 5, nums = [0,1,2,3,4,_,_,_,_,_]
Explanation: Your function should return k = 5, with the first five elements of nums being 0, 1, 2, 3, and 4 respectively.
It does not matter what you leave beyond the returned k (hence they are underscores).

Constraints :-
• 1 <= nums.length <= 3 * 10^4
• -100 <= nums[i] <= 100
• nums is sorted in non-decreasing order.
*/
#include <iostream>
#include <set>
#include <vector>
using namespace std;

// Naive Approach : Time Complexity : O(N log N) + O(N) __ Space Complexity : O(1)
/*
Since we need to remove duplicates and get the unique values only, the first thing that comes to mind is using a set.
As set have the property to store only distinct values and automatically keeps them in sorted order.
- Use a set which will store the unique values: set<int> uniqueValues
- Traverse the array & insert its elements in a set (which will not store duplicate values, only 1 occurrence of each value).
- Now, we need to retrieve the unique values from the set and re-write them into nums array.
- To do so, we place a pointer k at index 0, 
  and start traversing in the set to get the unique elements one by one in sorted order.
- For each unique element, we re-write the value at kth index of nums array, and increment k to move pointer to the next position.
- When traversal ends, we have re-written the nums array such that 
  the elements before current position of pointer k are unique.
  i.e., the elements at indices 0 to k-1, are unique.
  We need to return the count of these unique elements which will be equal to k itself.
- So, we can simply return k.

>> Approach

>>> Step 1: Store only unique elements
        set<int> uniqueValues;    
    A set in C++ stores only unique values and automatically keeps them in sorted order.

>>> Step 2: Insert every array element into the set
        for (int &x : nums)
            uniqueValues.insert(x);

    Example: nums = [1, 1, 2, 2, 3, 4, 4]
    | Current Element | Set Contents |
    | --------------- | ------------ |
    | 1               | {1}          |
    | 1               | {1}          |
    | 2               | {1,2}        |
    | 2               | {1,2}        |
    | 3               | {1,2,3}      |
    | 4               | {1,2,3,4}    |
    | 4               | {1,2,3,4}    |

>>> Step 3: Rewrite the original array
        int k = 0;
        for (int x : uniqueValues)
            nums[k++] = x;
        
    Example: nums = [1, 1, 2, 2, 3, 4, 4]
    Initially: k = 0
    Array: 1 1 2 2 3 4 4
           ^ (k pointer position)

    Iteration 1: x = 1 __ nums[0] = 1 __ k becomes 1 (after incrementing)
        Array: 1 1 2 2 3 4 4
                 ^
    Iteration 2: x = 2 __ nums[1] = 2 __ k becomes 2
        Array: 1 2 2 2 3 4 4
                   ^

    Iteration 3: x = 3 __ nums[2] = 3 __ k becomes 3
        Array:  1 2 3 2 3 4 4
                      ^
    
    Iteration 4: x = 4 __ nums[3] = 4 __ k becomes 4
        Array: 1 2 3 4 3 4 4
                       ^
    The first 4 elements now contain all unique values.
    The remaining elements don't matter because the problem only checks the first k positions.

    How nums[k++] = x works ? k++ is the post-increment operator. It means:
        - Use the current value of k.
        - Assign x to nums[k].
        - Increase k by 1.

>>> Step 4: Return the count of distinct elements
        return k;
    When re-writing ends, the value of k equals the couunt of distinct elements, so we can return k
    We can also return set.size() as it also tells us the count of distinct elements

>> Time and Space Complexity
>>> Time Complexity: O(n log n) + O(n)
    - Inserting each of the n elements into a set takes O(log n) time. So: O(n) * O(log n) = O(n log n)
    - Re-writing the values of arr takes another traversal which could be O(n) in worst case (when all values are unique)
    - So, total: O(n log n) + O(n)
>>> Space Complexity: O(n)
    The set stores up to n unique elements.
*/
int removeDuplicatesSet(vector<int>& nums) {
    set<int> uniqueValues;

    // forEach loop runs n times .... log n for each insertion in set. So, total : O(n log n)
    for (int& x : nums) 
        uniqueValues.insert(x);

    int k = 0;
    // say set contains only m distinct elements so loop runs m times ... k is incremented each time so at the end k = m
    for (int x : uniqueValues) {
        // nums[k] = x;
        // k++;

        nums[k++] = x;
    }

    return k;       // we can also return the size of set as it also denotes the count of unique elements
}

// Better (Using Frequency Array) : Time Complexity : O(n) + O(201) ~ O(n) __ Space Complexity : O(201) ~ O(1)
/*
If we look at the constraints, -100 <= nums[i] <= 100, we will observe that the range of values of array is very small.
We can use a frequency vector for such small range to store the frequencies of all elements and 
using that frequency vector, we can also get the unique elements in sorted order.

The range of values is [-100, 100], this means total 201 distinct values.
So, we can use a frequency vector of size 201.
The index to corresponding value mapping for this frequency vector can be done as:
For val x of nums, index i corresponding to x is :- i = x - (-100) = x + 100
For index i of freq, val x corresponding to i is :- x = i - 100

So we traverse the array nums, and store the frequencies of all elements x using freq[x + 100]++.
Now, we need to get the distinct values of the array in sorted order.
If we traverse the freq vector, then it might contain 0s or count of occurrences at some index i.
This freq[i] tells us whether the corresponding value (i - 100) exists in the nums array or not. 

We maintain a pointer k (initialized at 0), to re-write the distinct values in nums.
We tarverse the freq vector and for non-zero values of freq (freq[i] != 0), we re-write value in nums at kth position.

When traversal of freq vector ends, k denotes the count of distinct values of nums.
*/
int removeDuplicatesBetter(vector<int>& nums) {
    vector<int> freq(201);
    // -100 <= nums[i] <= 100 => total elements: 201

    // we can map a val of nums 'x' to index i of freq in this way: i = x - (-100) = x + 100
    for (int& x : nums) 
        freq[x + 100]++;
    
    int k = 0;
    for (int i = 0; i < 201; i++)
        if (freq[i] != 0)
            // for index i of freq, the corresponding element value is i - 100 
            // since i = x + 100 => x = i - 100
            nums[k++] = (i - 100);

    return k;
}

// Optimal Approach (Two Pointers) : Time Complexity : O(n) __ Space Complexity : O(1) 
/*
>> Intuition

The array is already sorted.
That means: All duplicate values are adjacent.
Example: 1 1 2 2 3 3 4 5 5
So instead of storing elements in another data structure like a set, we can simply keep one copy of each unique element.

Think of it like this:
Original Array: 
1 1 2 2 3 3 4 5 5
^
i

We maintain two pointers:
- i → points to the last unique element found.
- j → scans the array to find new unique elements.
Whenever nums[j] is different from nums[i], we've found a new unique value. We move i forward and copy that value there.

>> Dry Run
Consider: nums = [1,1,2,2,3,4,4]
Initially: i = 0
1 1 2 2 3 4 4
i 

j = 1: i = 0 __ nums[i] = 1, nums[j] = 1 => Same element => Do Nothing. Move j
j = 2: i = 0 __ nums[i] = 1, nums[j] = 2 => Different! => Move i ahead (i becomes 1), do nums[i] = nums[j] => nums[1] = 2
       nums = [1, 2, 2, 2, 3, 4, 4]
                  i  j   
j = 3: i = 1 __ nums[i] = 2, nums[j] = 2 => Same element => Do Nothing. Move j
j = 4: i = 1 __ nums[i] = 2, nums[j] = 3 => Different! => Move i ahead (i becomes 2), do nums[i] = nums[j] => nums[2] = 3
       nums = [1, 2, 3, 2, 3, 4, 4]
                     i     j 
j = 5: i = 2 __ nums[i] = 3, nums[j] = 4 => Different! => Move i ahead (i becomes 3), do nums[i] = nums[j] => nums[3] = 4
       nums = [1, 2, 3, 4, 3, 4, 4]
                        i     j
j = 6: i = 3 __ nums[i] = 4, nums[j] = 4 => Same element => Do Nothing. Move j
j becomes 7, iteration ends.

Now, i points to the last unique element found which is 4 present at index 3.
The value of i denotes the index of this last unique element, so count of unique elements = i + 1
    Number of unique elements = Last Unique Element Index + 1 = i + 1

>> Key Insight
- j is the reader: it scans every element in the array.
- i is the writer: it marks where the next unique element should be placed (next element position = i + 1).
Since the array is sorted, every time nums[j] != nums[i], we've found a new unique value, 
so we advance the writer and overwrite the next position. 
This lets us remove duplicates in-place without any extra data structure.
*/
int removeDuplicates(vector<int>& arr) {
    int i = 0;
    int n = arr.size();
    for(int j = 1; j < n; j++){
        if(arr[i] != arr[j]){
            i++;
            arr[i] = arr[j];

            // arr[++i] = arr[j];
        }
    }
    return i+1;
}

/*
Similar idea as above but here we are placing i at the index position where the next unique element should come
This below code actually implements i being the writer in better way,
as i here actually points to the position where re-writing must be done.

>> Key Insight
- j is the reader: it scans every element in the array.
- i is the writer: it marks where the next unique element should be placed.
*/
int removeDuplicates2(vector<int>& nums) {
    int n = nums.size();
    int i = 1;

    for (int j = 1; j < n; j++)
        if (nums[j] != nums[i - 1])
            nums[i++] = nums[j];
            // nums[i] = nums[j]; 
            // i++;
    
    return i;
}

int main() {
    vector<int> arr = {1,1,2,2,3,4,5,5,6};
    int dist = removeDuplicates(arr);

    for(int x : arr) 
        cout << x << " ";
    
    cout << "\nUnique Element Count: " << dist;

    return 0;
}
