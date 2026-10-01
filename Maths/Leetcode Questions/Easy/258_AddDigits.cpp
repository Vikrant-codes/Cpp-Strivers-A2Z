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

Constraints :-
• 0 <= num <= 2^31 - 1

Follow up: Could you do it without any loop/recursion in O(1) runtime?
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach (Simulation Based Approach) : Time Complexity : O( log10 (​n) ) __ Space Complexity : O(1)
/*
Approach :- 
1. We simulate the process of adding the digits until we get a single digit.
2. Firstly add the digits of the number. 
3. If this sum is a single digit number, return it.
4. If not, repeat the process by considering this sum as the new value of num till we get a single digit result.

>> Complexity Analysis

-> sumOfDigits(n): 
|    while (n) {
|        sum += n % 10;
|        n /= 10;
|    }

Finding sum of digits of a number `n` takes O(d) time, 
where d is the count of digits, precisely d = O(log10(n)) + 1.
Thus, sumOfDigits(n) takes O(log n)

-> addDigits():
|    while (num > 9) {
|        num = sumOfDigits(num);
|    }

The important observation is that after summing the digits, num becomes much smaller.
For example:
999999999
   ↓
   81
   ↓
   9

So there are only a few iterations relative to the number of digits. 
More formally, the total work is dominated by the first digit-sum operation.

Therefore:
Time:  O(log n)
Space: O(1), for the iterative solution.
*/

// the code becomes much cleaner if we use a helper method to calculate the sum of digits

// helper method
int sumOfDigits(int n) {
    int sum = 0;
    
    while (n) {
        sum += n % 10;
        n /= 10;
    }

    return sum;
}

// Iterative Implementation for Simulation Approach: Time Complexity : O(log n) __ Space Complexity : O(1)
int addDigitsIterative(int num) {
    while (num > 9) {
        num = sumOfDigits(num);
    }

    return num;
}

// Recursive Implementation for Simulation Approach: Time Complexity : O(log n) __ Space Complexity : O(log log n)
/*
>> Space Complexity Analysis [Recursive Stack Space]

Each call to addDigits() stays on the call stack until the recursive call returns.

For example:
    addDigits(999999999)
        ↓
    addDigits(81)
        ↓
    addDigits(9)
        ↓
    return 9

For a general n, the number of recursive calls is actually O(log log n), 
because each sumOfDigits() reduces the number from roughly n to at most 9 × number_of_digits.

So, more precisely:
- sumOfDigits() → O(log n) time, O(1) space
- addDigits() recursion depth → O(log log n)

Overall space complexity → O(log log n)
*/
int addDigits(int num) {
    if (num < 10) 
        return num;
    
    num = sumOfDigits(num);

    return addDigits(num);
}

/*
int addDigitsNaive(int num) {
    while (num > 9) {
        int sum = 0;
        while (num) {
            sum += num % 10;    // add the last digit
            num /= 10;          // remove the last digit
        }
        num = sum;              // re-assign num as the digits_sum
    }
    
    return num;
}
*/

// Optimal Approach: Time Complexity : O(1) __ Space Complexity : O(1)
/*
>> Intuition
The first approach one can think of is to brute force add the digits of the number until the result has only 1 digit, 
but, the follow up asks for an O(1) approach without using any loops or recursion.
To figure out the O(1) solution, we have to observe a pattern :-

1. We find the digit sum for different numbers and try to observe a pattern.

2. 0 is the only number with digit sum as 0.

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
    like [0] [1,2,3,4,5,6,7,8,9] [10,11,12,13,14,15,16,17,18] [19,...,27] [28,...,36] ... [100,...,108] ... [1009,...,1018] ...

4. We observe that the numbers give the digits sum as 1,2,3,4,5,6,7,8,9 in a repeating pattern,
   and thus the digit sum can be found easily by finding num % 9. 
   Ex - num = 129: we see 129 % 9 = 3 so its digit sum is 3.
   But there is an edge case, when num is a multiple of '9', its modulus with 9 gives us 0, but its digit sum is 9.
   Ex- 9, 81, 117, etc 

>> Approach
1. If num == 0, return 0.
2. If num % 9 == 0:
    Return the digit sum as 9.
3. else, return num % 9.
*/

// `Digital Root`
/*
The digital root is a mathematical shortcut for exactly this problem: repeatedly summing digits until one digit remains.

The formula:- For a non-negative integer num:
    int addDigits(int num) {
        if (num == 0)
            return 0;

        return 1 + (num - 1) % 9;
    }

>> Why does % 9 work?
A number has the same remainder modulo 9 as the sum of its digits.

For example:

    529
    = 5×100 + 2×10 + 9

Since:
100 % 9 = 1
10  % 9 = 1

we get:
    529 % 9
    = (5 + 2 + 9) % 9
    = 16 % 9
    = 7

And 7 is exactly the digital root:
    529
     ↓
    5 + 2 + 9 = 16
     ↓
    1 + 6 = 7

>> Why 1 + (num - 1) % 9 instead of num % 9?
1 + (num - 1) % 9 gives us the expected result `9`, instead of 0, when num is a multiple of 9.
num % 9 would give us 0 in such cases.
*/

int addDigits1(int num) {
    if (num == 0) 
        return 0;

    int x = num % 9;
    return x == 0 ? 9 : x;
}

int addDigits2(int num) {
    /*
    if (num == 0) 
        return 0;

    return 1 + (num - 1) % 9;           // This fomrula is called digital root formula
    */
   
    return (num == 0) ? 0 : 1 + (num - 1) % 9;
}

int main() {

    return 0;
}