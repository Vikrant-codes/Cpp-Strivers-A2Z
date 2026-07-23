/*
GFG - First and Second Smallests : Easy

Given an array, arr[] of integers, your task is to return the smallest and second smallest element in the array. 
If the smallest and second smallest do not exist, return -1.

Examples :-

Input: arr[] = [2, 4, 3, 5, 6]
Output: [2, 3] 
Explanation: 2 and 3 are respectively the smallest and second smallest elements in the array.

Input: arr[] = [1, 1, 1]
Output: [-1]
Explanation: Only element is 1 which is smallest, so there is no second smallest element.

Constraints :-
• 1 ≤ arr.size ≤10^5
• 1 ≤ arr[i] ≤ 10^5
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach (Using Sorting) : Time Complexity : O(n log n) __ Space Complexity : O(1)
/*
>> Approach
• Sort the array.
• After sorting, smaller elements come to the start of the array with arr[0] becomes the smallest value (min.) of the array.
• So, we get the minimum = arr[0]
• Now, we need to find the second minimum, which should come at index 1, but since array can have duplicates,
    we need to find the first element in this sorted array whose value is not equal to the smallest (arr[0])
    This first element found while traversing the sorted array from left end, will be our second Smallest value.
• So, we iterate from left end and find the first element whose value is not equal to smallest (arr[0]) 
    and assign that value to second smallest and stop iteration.
• There might be cases when second minimum doesn't exists, for those cases, second smallest variable value would not change
    and remain same as the value we initialized, so return {-1}
• Else, return {smallest, second_smallest}
*/
vector<int> minAnd2ndMinNaive(vector<int> &arr) {
    sort(arr.begin(), arr.end());
    
    int min = arr[0];
    int secMin = INT_MAX;
    
    for (int& x : arr) {
        if (x != min) {
            secMin = x;
            break;
        }
    }
    
    if (secMin == INT_MAX) return {-1};
    
    return {min, secMin};
}

// Better Approach (Two Pass solution) : Time Complexity : O(2n) __ Space Complexity : O(1)
/*
>> Approach
• Use two pass search
• Find the minimum element of the array in 1st traversal, store that value in some variable (min)
• Do another traversal and find the smallest value of the array such that the value is not equal to min
• Such smallest value will be our second Smallest (SecMin)
• If secMin doesn't exists, then its value would remain same as what we initialized, for that case, return {-1}
• else return {min, secMin}
*/
vector<int> minAnd2ndMinBetter(vector<int> &arr) {
    int n = arr.size();
    
    int min = arr[0];
    
    for (int i = 0; i < n; i++)
        if (arr[i] < min)
            min = arr[i];
            
    int secMin = 100001;
    // constraints guarantee that arr[i] <= 10^5, so we can initialize secMin with a value greater than 10^5 i.e., 10^5+1
    
    for (int i = 0; i < n; i++)
        if (arr[i] < secMin && arr[i] != min)
            secMin = arr[i];
            
    if (secMin == 100001) return {-1};
    
    return {min, secMin};
}


// Optimal Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
• We can find both the smallest and second smallest value of the array in a single traversal.
• Declare two variables min & secMin to store the smallest and second smallest values of arr.
• We can initialize them as follows :
    • min : 
        This would store the minimum value of the array so it can be initialized as either arr[0] or
        values greater than the maximum value arr[i] can have (arr[i] <= 10^5), like 10^5, 10^5+1, or INT_MAX
    • secMin : 
        If we initialize secMin with any value in range [1, 100000] (1 <= arr[i] <= 10^5), 
        then there could be cases that the initialized value itself is the smallest, 
        so we would not be able to find the secondSmallest with such wrong initialization.
        Thus, we need to initialize secMin with a greater value outside of this range, like 10^5 + 1 or INT_MAX.
• We traverse the array and the current element arr[i] can have following comparisons
    • arr[i] < min: arr[i] is smaller than minimum itself
        • we need to update min as we have found a new smallest value, which means current min has become secondMinimum
        • so we update secMin with the min value, and then update min with current element value
            secMin = min
            min = arr[i]
    • arr[i] < secMin: we need to update secMin but we also check that this smaller value must not be equal to 'min'
        • so condition becomes: if (arr[i] < secMin && arr[i] != min)
        • we update secMin = arr[i]
• If the array doesn't have a secondSmallest value, then secMin will keep holding the initialized value after traversal ends
• So, we check if secMin == initialized_value -> if true, we return {-1}
• Else return {min, secMin}
*/
vector<int> minAnd2ndMin(vector<int> &arr) {
    int min = arr[0];
    int secMin = 100001;        
    // the max. value of arr[i] can be 10^5, so we initialize secMin with 10^5 + 1
    
    for (int& x : arr) {
        if (x < min) {
            secMin = min;
            min = x;
        }
        else if (x < secMin && x != min) {
            secMin = x;
        }
    }
    
    if (secMin == 100001) return {-1};
    
    return {min, secMin};
}

int main() {
    return 0;
}