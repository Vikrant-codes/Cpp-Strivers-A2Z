/*
Problem Statement :-
You're given an sorted array arr of n integers and an integer x. Find the floor and ceiling of x in the array.
Floor of x is the largest element which is smaller than or equal to x. Floor of x doesn’t exist if x is smaller than smallest element of arr[].
Ceil of x is the smallest element which is greater than or equal to x. Ceil of x doesn’t exist if x is greater than greatest element of arr[].
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach (Binary Search) : Time Complexity : O(log n) __ Space Complexity : O(1)
/*
Observations :- 
> If x is present in the array, then both floor and ceil of x are equal to x.
> If x is not present in the array then certain conditions might arise
>> If elements less than x and greater than x both exist, then floor will be largest smaller element and ceil will be smallest greater element.
>> If x is smaller than the smallest element of array, then floor won't exist and ceil will be the smallest element of array.
>> If x is greater than the greatest element of array, then ceil won't exist and floor will be the greatest element of array.

Since array is sorted, we can use binary search to find the floor and ceil of x. While doing so 
> If arr[mid] == x : means x exists in the array, so both floor and ceil are x and thus return {x, x}
__
In binary search the low pointer will point to the smallest greater element (i.e. ceil) and 
the high pointer will point to the largest smaller element (i.e. floor). 
So after the loop ends, low will point to the ceil and high will point to the floor.
If Floor exists then the high pointer would be greater than or equal to 0 after loop ends.
Similarly, if Ceil exists then the low pointer would be less than size of array after loop ends.
__
> If both floor and ceil exists then floor = arr[high], ceil = arr[low]
> In case one of them doesn't exist then we return -1 for that value.
*/ 
vector<int> floorCeil(vector<int> arr, int x) {
    int low = 0, high = arr.size() - 1;
    int floor = -1, ceil = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == x) return {x, x}; // If x exists in the array then both floor and ceil are x. 
        else if (arr[mid] > x) high = mid - 1;
        else low = mid + 1;
    } 

    if (high >= 0) floor = arr[high];           // If floor exists then high pointer would point to it, so floor = arr[high]
    if (low <= arr.size() - 1) ceil = arr[low]; // If ceil exists then low pointer would point to it, so ceil = arr[low]
    return {floor, ceil}; 
}

int main() {
    vector<int> arr = {10, 20, 30, 40, 50};
    int x = 25;
    vector<int> result = floorCeil(arr, x);
    cout << "Floor : " << result[0] << " __ Ceil : " << result[1] << endl;

    return 0;
}