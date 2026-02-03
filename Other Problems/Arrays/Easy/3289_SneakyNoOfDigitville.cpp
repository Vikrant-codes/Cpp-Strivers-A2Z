/*
Leetcode - 3289. The Two Sneaky Numbers of Digitville : Easy

In the town of Digitville, there was a list of numbers called nums containing integers from 0 to n - 1. 
Each number was supposed to appear exactly once in the list, however, 
two mischievous numbers sneaked in an additional time, making the list longer than usual.
As the town detective, your task is to find these two sneaky numbers. 
Return an array of size two containing the two numbers (in any order), so peace can return to Digitville.

Examples :-
Input: nums = [0,1,1,0] __ Output: [0,1]
Explanation: The numbers 0 and 1 each appear twice in the array.

Input: nums = [0,3,2,1,3,2] __ Output: [2,3]
Explanation: The numbers 2 and 3 each appear twice in the array.

Input: nums = [7,1,5,4,3,4,6,0,9,5,8,2] __ Output: [4,5]
Explanation: The numbers 4 and 5 each appear twice in the array.

Constraints :-
- 2 <= n <= 100
- nums.length == n + 2
- 0 <= nums[i] < n
- The input is generated such that nums contains exactly two repeated elements.
*/

#include <bits/stdc++.h>
using namespace std;

// HashMap Approach :- Time Complexity : O(n) __ Space Complexity : O(n)
vector<int> getSneakyNumbersHashMap(vector<int>& nums) {
    int n = nums.size() - 2;
    vector<int> hashArr(n);
    vector<int> ans;
    for (int x : nums) 
        hashArr[x]++;
    for (int i=0; i<n; i++)
        if (hashArr[i] == 2) 
            ans.push_back(i);
    return ans;
}

// Optimal Approach (Math based) : Time Complexity : O(n) __ Space Complexity : O(1)
/*
🔍 Problem Insight
Given an array nums of size n + 2.
• The original valid digits are all integers from 0 to n-1
• Exactly two numbers appear twice
• All other numbers appear once
Our task is to find the two duplicated numbers.

🧠 Core Intuition
Instead of tracking frequencies (extra space), we use mathematical invariants:
• Sum of elements
• Sum of squares of elements
Why does this help?
Because:
• The correct set {0, 1, 2, ..., n-1} has a known sum
• Any deviation from that sum must come only from the two repeated numbers

📐 Mathematical Reasoning
1️⃣ Actual sum and square sum
From the input array :
sum   = x₁ + x₂ + ... + xₙ₊₂
sqsum = x₁² + x₂² + ... + xₙ₊₂²
Since two numbers are duplicated, these totals are larger than expected.

2️⃣ Expected values for [0, n-1]
If every number appeared exactly once:
Expected Sum : ex_sum = (n−1)⋅n / 2
Expected Square Sum : ex_sqsum = (n−1)⋅n⋅(2n−1) / 6
----------------------------------------------------------------------------------------------------
This expected sum is calculated using the formulas for sum of integers & sum of squares of integers 
sum of integers in range [0, x] = sum in range [1, x] = x * (x + 1) / 2
sum of squares of integers in range [0, x] = sum in range [1, x] 
----------------------------------------------------------------------------------------------------

3️⃣ Isolate the extra contribution
Let the duplicated numbers be x and y.
Then:
• x + y = sum − ex_sum = a
• x ^ 2 + y ^ 2 = sqsum − ex_sqsum = b

4️⃣ Use algebra to separate x and y
We know : (x+y)^2 = x^2 + y^2 + 2xy                 ----- equation (1)
Also, x+y = a, x^2 + y^2 = b
After substituting the values of x + y & x^2 + y^2, we get : a^2 = b + 2xy
→ xy = (a^2 − b) / 2 ​= c
Now we have :
• x + y = a
• xy = c

5️⃣ Solve the quadratic equation
This becomes : t² - a·t + c = 0
Using the quadratic formula : t = (a + sqrt(a^2 - 4ac) )/ 2    or    (a - sqrt(a^2 - 4ac) )/ 2
These two roots are exactly the two sneaky numbers.
The problem guarantees the discriminant is a perfect square, so this is safe.

🧩 Algorithm
1. Let n = nums.size() - 2
2. Compute:
    • sum = sum of all elements
    • sqsum = sum of squares of all elements
3. Compute expected values for [0, n-1], ex_sum (expected sum) & ex_sqsum (expected square sum)
4. Let :
    • a = sum - ex_sum
    • b = sqsum - ex_sqsum
5. Compute:
    • c = (a*a - b) / 2
6. Solve the quadratic equation : 
    • t² - a·t + c = 0
7. Return the two roots
*/
vector<int> getSneakyNumbers(vector<int>& nums) {
    int n = nums.size() - 2;        // n is the original count of digits
    int sum = 0, sqsum = 0;
    for (int& k : nums) {
        sum += k;
        sqsum += k * k;
    }
    // for integers [1, n], sum = n * (n + 1) / 2, square_sum = n * (n + 1) * (2*n + 1) / 6
    int ex_sum = ((n - 1) * n) / 2;                         // expected sum of numbers in range [0, n-1]
    int ex_sqsum = ( (n - 1) * n * (2 * (n-1) + 1 ) ) / 6;  // expected square_sum of range [0, n-1]
    int a = sum - ex_sum;
    int b = sqsum - ex_sqsum;
    int c = (a * a - b) / 2;
    // discriminant is guaranteed to be a perfect square
    int sq_root = sqrt(a * a - 4 * c);
    return { (a + sq_root) / 2, (a - sq_root) / 2 };
}

int main() {
    return 0;
}