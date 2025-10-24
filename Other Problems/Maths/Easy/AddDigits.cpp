/*
Leetcode - 258. Add Digits : Easy

Given an integer num, repeatedly add all its digits until the result has only one digit, and return it.

Examples :-

Input: num = 38 __ Output: 2
Explanation: The process is
38 --> 3 + 8 --> 11
11 --> 1 + 1 --> 2 
Since 2 has only one digit, return it.

Input: num = 0 __ Output: 0

Constraints : 0 <= num <= 2^31 - 1

Follow up: Could you do it without any loop/recursion in O(1) runtime?
*/
#include <bits/stdc++.h>
using namespace std;

// Naive Approach : Time Complexity : O() __ Space Complexity : O(1)
/*
Approach :- 
1. We simulate the process of adding the digits until we get a single digit.
2. Firstly add the digits of the number. If this sum is a single digit, return it.
3. If not, repeat the process taking this sum as the new integer till we get a single digit as the result.

We can implement this using 2 while loops, the outer loop will run till num > 9 (i.e. till num is not a single digit)
and the inner loop will calculate the sum of digits of num.

-> How to calculate the sum of digits ?
we can keep taking num % 10 to get the last digit and add it to sum and then do num /= 10 to remove the last digit.

After getting the sum of digits, we assign it to num and repeat the process till num is a single digit.
Finally return num.
*/
int addDigitsNaive(int num) {
    while (num > 9) {
        int sum = 0;
        while (num) {
            sum += num % 10;     // add the last digit
            num /= 10;          // remove the last digit
        }
        num = sum;              // re-assign num as the digits_sum
    }
    return num;
}

// Optimal Approach : Time Complexity : O(1) __ Space Complexity : O(1)
/*
--> Intuition
The first approach one can think of is to brute force add the digits of the number until the result has only 1 digit, but, the follow up 
asks for an O(1) approach without using any loops or recursion that was useful for brute force. 
So, to think about the O(1) we see some observations :-

1. We find the digits sum for different numbers and try to observe a pattern.
2. 0 is the only number with digit sum as 0
3. Lets group the numbers upto 150 based on their digit sum
[1] = [1,10,19,28,37,46,55,64,73,82,91,100,109,118,127,136,145]
[2] = [2,11,20,29,38,47,56,65,74,83,92,101,110,119,128,137,146]
[3] = [3,12,21,30,39,48,57,66,75,84,93,102,111,120,129,136,147]
[4] = [4,13,22,31,40,49,58,67,76,85,94,103,112,121,130,139,148]
[5] = [5,14,23,32,41,50,59,68,77,86,95,104,113,122,131,140,149]
[6] = [6,15,24,33,42,51,60,69,78,87,96,105,114,123,132,141,150]
[7] = [7,16,25,34,43,52,61,70,79,88,97,106,115,124,133,142]
[8] = [8,17,26,35,44,53,62,71,80,89,98,107,116,125,134,143]
[9] = [9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144]

So, we see that the numbers are grouped in a pattern and the pattern repeats after every 9 numbers.
like [0] [1,2,3,4,5,6,7,8,9] [10,11,12,13,14,15,16,17,18] [19,20,...27] [28,...36] ... [100,...108] .... [1009,...1018] ...

4. We observe that the numbers give the digits sum as 1,2,3,4,5,6,7,8,9 in a repeating pattern and thus the digit sum can be found 
easily by finding num % 9. ex for 129 .. we see 129 % 9 = 3 so its digit sum is 3, but for nuumbers like 9,18,27,36,... we see that 
their modulus with 9 is 0 but their digit sum is 9.

--> Approach
1. If num == 0, return 0.
2. Simply find num % 9.
3. Check if num % 9 == 0, if yes return 9, else return num % 9.
*/
int addDigits(int num) {
    if (num == 0) return 0;
    int x = num % 9;
    return x == 0 ? 9 : x;
}

int main() {

    return 0;
}