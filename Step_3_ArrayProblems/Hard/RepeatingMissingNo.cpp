/*
Leetcode - 645 : Set Mismatch : Easy

Find the repeating and missing numbers

Problem Statement: You are given a read-only array of N integers with values also in the range [1, N] both inclusive. 
Each integer appears exactly once except A which appears twice and B which is missing. The task is to find the repeating and 
missing numbers A and B where A repeats twice and B is missing.

Input Format:  array[] = {3,1,2,5,3} __ Result: {3,4)
Explanation: A = 3 , B = 4 , Since 3 is appearing twice and 4 is missing

Input Format: array[] = {3,1,2,5,4,6,7,5} __ Result: {5,8)
Explanation: A = 5 , B = 8 , Since 5 is appearing twice and 8 is missing
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach : Time Complexity: O(N^2) and Space Complexity: O(1)
// For each integer in range [1,n] check its occurence if it's 2 then that number is repeating and if 0 then it's missing.
vector<int> repeatingMissingBrute(vector<int> arr) {
    int n = arr.size();
    int repeating = 0, missing = 0;
    for(int i=1; i<=n; i++) {
        int cnt = 0;
        for(int j=0; j<n; j++) {
            if(arr[j] == i) cnt++;
        }
        if (cnt == 2) repeating = i;
        else if (cnt == 0) missing = i; 
        if (repeating != 0 && missing != 0) break; // If both numbers are found, exit the loop
    }
    return {repeating, missing};
}

// Better Approach (using Hashing) : Time Complexity : O(2n) __ Space Complexity : O(n)
// Use a hash arr to keep track of the occurences of different integers.  
vector<int> repeatingMissingHash(vector<int> arr) {
    int n = arr.size();
    int hash[n] = {0};
    int repeating = 0, missing = 0;
    // update the hash array to count the occurence of a particular number.. hash[i] denotes the occurence of integer i+1
    for(int i=0; i<n; i++) {
        hash[arr[i]-1]++;       // the occurence of arr[i] will be stored at arr[i] - 1 index due to 0 based indexing
    }
    // Now to find the repeating and missing number we can proceed in two ways
    // 1. Loop through the hash array and check if any occurence is marked as 0 (for missing number) or 2 (for repeating number)
    // 2. Loop from 1 to N and check the occurence of that number by checking hash[i-1] and find the repeating and missing number that way. 
    for(int i=0; i<n; i++) {
        if (hash[i] == 0) missing = i+1;
        else if (hash[i] == 2) repeating = i+1;
        if (repeating != 0 && missing != 0) break; // If both numbers are found, exit the loop
    }
    return {repeating, missing};
}

// Optimal Approach 1 (using Maths) : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Approach :- The idea is to convert the given problem into mathematical equations. Since we have two variables i.e. missing and repeating, 
we will try to form two linear equations. And then we will find the values of two variables using those equations.
Suppose the two variables are x (repeating) and y (missing)

-> Form equation 1 : To form the first equation find the sum of the array
sum = sum of elements of array
exp_sum = sum of integers from 1 to n = n * (n+1) / 2

Now if we do sum - exp_sum we will get x - y i.e. repeating_no - missing_no. 
For ex - if array was {3,1,2,5,3} so sum - exp_sum will be (3+1+2+5+3) - (1+2+3+4+5) = 3 - 4, 
since the missing number is only in exp_sum and repeating will not get cancelled out. 

# equation 1 : x - y = sum - exp_sum = p (say)

-> Form equation 2 : To form second equation we find the sum of sqaures
square_sum = sum of square of all elements
exp_square_sum = (n*(n+1)*(2n+1))/6

Now square_sum - exp_square_sum = x^2 - y^2 = (similar to how repeating - missing was left earlier, this time repeating square - missing square is left)

now this square_sum - exp_square_sum = x^2 - y^2 = (x-y) * (x+y) ==> x + y = (square_sum - exp_square_sum) / (x - y)

# equation 2 : x + y = (square_sum - exp_square_sum) / (x - y) = q (say)

# Solve the two equations 
We get the value of x + y and x - y using this sum approach .. let x - y = p (say) .... eq1 & x + y = q (say) .... eq2
Now we can using elemination method to solve the equations which will give us 
eq1 + eq2 => (x - y) + (x + y) = p + q ==> 2x = p+q ==> x = (p+q) / 2 .. thus repeating = x = (p+q) / 2
Now x - y = p so y = x - p hence we get y also .. thus missing = y = x - p

Return x & y.
*/ 
vector<int> repeatingMissing1(vector<int> nums) {
    long long n = nums.size();
        long long sum = 0;
        long long sqsum = 0;
        long long exp_sum = (n * (n + 1)) / 2;
        long long exp_sqsum = (n * (n + 1) * (2*n + 1)) / 6;
        for(int i=0; i<n; i++) {
            sum += (long long) nums[i];
            sqsum += (long long) nums[i] * (long long) nums[i];
        }
        int p = sum - exp_sum;
        int q = (sqsum - exp_sqsum) / p;
        int x = (p + q) / 2;
        int y = x - p;
        return {x, y};
}

// Optimal Approach 2 (using XOR) : Time Complexity : O(n) __ Space Complexity : O(1)
vector<int> repeatingMissing1(vector<int> a) {
    int n = a.size(); // size of the array

    int xr = 0;

    //Step 1: Find XOR of all elements:
    for (int i = 0; i < n; i++) {
        xr = xr ^ a[i];
        xr = xr ^ (i + 1);
    }

    //Step 2: Find the differentiating bit number:
    int number = (xr & ~(xr - 1));

    //Step 3: Group the numbers:
    int zero = 0;
    int one = 0;
    for (int i = 0; i < n; i++) {
        //part of 1 group:
        if ((a[i] & number) != 0) {
            one = one ^ a[i];
        }
        //part of 0 group:
        else {
            zero = zero ^ a[i];
        }
    }

    for (int i = 1; i <= n; i++) {
        //part of 1 group:
        if ((i & number) != 0) {
            one = one ^ i;
        }
        //part of 0 group:
        else {
            zero = zero ^ i;
        }
    }

    // Last step: Identify the numbers:
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == zero) cnt++;
    }

    if (cnt == 2) return {zero, one};
    return {one, zero};
}

int main() {
    vector<int> arr = {4,1,2,5,5};
    vector<int> rm = repeatingMissing1(arr);
    cout << "Repeating No. : " << rm[0] << " __ Missing No. : " << rm[1];

    return 0;
}