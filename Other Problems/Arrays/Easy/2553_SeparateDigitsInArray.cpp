/*
Leetcode - 2553. Separate the Digits in an Array : Easy

Given an array of positive integers nums, return an array answer that consists of the digits of each integer in nums 
after separating them in the same order they appear in nums.

To separate the digits of an integer is to get all the digits it has in the same order.

For example, for the integer 10921, the separation of its digits is [1,0,9,2,1].
 
Examples :-

Input: nums = [13,25,83,77]
Output: [1,3,2,5,8,3,7,7]
Explanation: 
- The separation of 13 is [1,3].
- The separation of 25 is [2,5].
- The separation of 83 is [8,3].
- The separation of 77 is [7,7].
answer = [1,3,2,5,8,3,7,7]. Note that answer contains the separations in the same order.

Input: nums = [7,1,3,9]
Output: [7,1,3,9]
Explanation: The separation of each integer in nums is itself.
answer = [7,1,3,9].

Constraints :-
- 1 <= nums.length <= 1000
- 1 <= nums[i] <= 10^5
*/

#include <bits/stdc++.h>
using namespace std;

// Approach 1 :- Time Complexity : O(D) __ Space Complexity : O(k)≈O(1)
/*
>> Approach :-
- We need to extract the digits of all the integers and put them in an answer vector.
- For each number, we can extract its digits and insert them into a digits vector.
- While extracting, we get the digits in reverse order, reverse the digits vector to get the digits in the order left -> right.
- Now, we need to add these digits to the answer vector, so we traverse the digits vector and push every digits into ans vector.
- return ans.

>> Intuition :-
For every number in the array, extract its digits one by one using % 10 and / 10.
    - % 10 gives the last digit.
    - /= 10 removes the last digit.
Since digits come out in reverse order, reverse the temporary digit array before adding it to the final answer.
Example: 123 → extract: 3, 2, 1 → reverse → 1, 2, 3
Then append all digits of every number into a single result vector.

>> Complexity Analysis :-
-> Time Complexity : O(D)
Let D be the total number of digits across all numbers.
Extracting digits of each number takes proportional to its digit count.
Reversing also takes proportional time.
Overall: O(D)
Since nums[i] <= 10^5, each number has at most 6 digits, so practically very efficient.

-> Space Complexity
Extra temporary vector for digits: O(k) where k is digits in current number (max 6).
Output vector stores all digits: O(D).
Auxiliary space (excluding output): O(k)≈O(1)
*/

// helper function -- returns a vector of digits of the given number 'n'
vector<int> getDigits(int n) {
    vector<int> digits;
    while (n > 0) {
        digits.push_back(n % 10);
        n /= 10;
    }
    reverse(digits.begin(), digits.end());
    return digits;
}

vector<int> separateDigits1(vector<int>& nums) {
    vector<int> ans;
    int i = 0, j = 0;
    for (int x : nums) {
        vector<int> digits = getDigits(x);      // get digits for each number 'x'
        // push the digits of number 'x' in the ans vector
        for (int d : digits) 
            ans.push_back(d);
    }
    return ans;
}

// Approach 2 :- Time Complexity : O(D) __ Space Complexity : O(1)
/*
When we extract digits, we get them in reversed order and thus we need to reverse the vector to get them in original order.
We need to do so for every number and then put them in the answer vector.
So, what if we try to directly store the digits in the answer vector. 
The digits would be stored in reverse order and we would have to reverse the ans vector to get the actual order digits.
Ex- nums = [13, 25, 83]
if we put the digits of each number directly in ans vector, the digits would be extracted in reversed order.
Processing:
    - 13 → push 3, 1 → ans = [3, 1]
    - 25 → push 5, 2 → ans = [3, 1, 5, 2]
    - 83 → push 3, 8 → ans = [3, 1, 5, 2, 3, 8]
Now, if we reverse it, ans becomes => ans = [8, 3, 2, 5, 1, 3]. 
This corresponds to [83, 25, 13]. But array was [13, 25, 83].

This happens because when we reverse the digits gets reversed along with the position of integers in the array 
so the last integer comes at first position.
So, to get the proper order, we must operate on the integers from right end of the array.
Thus, we must first add the digits of 83 into the ans vector, then 25 and then 13.
Processing:
    - 83 → push 3, 8 → ans = [3, 8]
    - 25 → push 5, 2 → ans = [3, 8, 5, 2]
    - 13 → push 3, 1 → ans = [3, 8, 5, 2, 3, 1]
ans = [3, 8, 5, 2, 3, 1] => reversed_ans = [1, 3, 2, 5, 8, 3].

>> Approach :-
- Traverses the array from right to left.
- Extracts digits from each number using % 10.
- Directly stores extracted digits in a single vector.
Since:
    - numbers are processed in reverse order, and
    - digits are also extracted in reverse order,
a single final reverse() restores the correct overall order.

Example: nums = [13, 25]
Processing:
25 → push 5, 2
13 → push 3, 1
Stored vector: [5, 2, 3, 1]
After reversing: [1, 3, 2, 5]

>> Time Complexity
Let D be the total number of digits across all numbers.
Digit extraction takes O(D)
Final reverse takes O(D)
Overall: O(D)

>> Space Complexity
The result vector stores all digits: O(D)
Auxiliary extra space apart from output is: O(1), since no temporary digit vector is used.
*/
vector<int> separateDigits2(vector<int>& nums) {
    vector<int> digits;
    int n = nums.size();
    for (int i = n-1; i >= 0; i--) {
        int x = nums[i];
        while (x > 0) {
            digits.push_back(x % 10);
            x /= 10;
        }
    }
    reverse(digits.begin(), digits.end());
    return digits;
}

// Approach 3 :- Time Complexity : O(D) __ Space Complexity : O(k)≈O(1)
/*
We need to perform reversals because we can't directly traverse the digits of a integer in left to right manner,
but we could have done so easily if we were given a string representing a number.
So, we get the string representation of the number and traverse it in left to right manner directly to get the digits.

>> Intuition
- Convert each number into a string using to_string().
- Then traverse the characters of the string:
    - each character represents a digit,
    - convert it back to integer using ch - '0',
    - append it to the answer vector.
Example: 123 → "123" → '1', '2', '3' → 1, 2, 3
This avoids manual digit extraction and reversing.

>> Time Complexity
Let D be the total number of digits across all numbers.
- to_string(x) takes proportional to number of digits.
- Traversing the string also takes proportional time.
Overall: O(D)

>> Space Complexity
Output vector: O(D)
Temporary string for each number: O(k) where k is digit count of current number.
Auxiliary space: O(k), where k ≤ 6 due to constraints, so effectively constant extra space.
*/
vector<int> separateDigits(vector<int>& nums) {
    vector<int> digits;

    for (int x : nums) {
        string s = to_string(x);
        for (char ch : s) digits.push_back(ch - '0');
    }

    return digits;
}

// We could also use stringstream to convert integer to string, the code would look like this
vector<int> separateDigits4(vector<int>& nums) {
    vector<int> digits;
    stringstream ss;

    for (int x : nums) {
        ss.clear();
        ss.str("");
        ss << x;
        string num = ss.str();
        
        for (char ch : num) digits.push_back(ch - '0');
    }
    
    return digits;
}

int main() {
    return 0;
}