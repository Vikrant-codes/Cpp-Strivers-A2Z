/*
Leetcode - 202. Happy Number : Easy

Write an algorithm to determine if a number n is happy.
A happy number is a number defined by the following process:
- Starting with any positive integer, replace the number by the sum of the squares of its digits.
- Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1.
- Those numbers for which this process ends in 1 are happy.
Return true if n is a happy number, and false if not.

Examples :-

Input: n = 19 __ Output: true
Explanation:
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1

Input: n = 2 __ Output: false

Constraints :-
- 1 <= n <= 2^31 - 1
*/

#include <bits/stdc++.h>
using namespace std;

/*
Observations :- 

To check whether a number is happy or not, 
we replace the number with the sum of sqaures of its digit. 
Like, for ex -> n = 19. n becomes : n = 1^2 + 9^2 = 1 + 81 = 82.
Now, we keep repeating this process until the number becomes 1 or it loops enlessly in a cycle. 
Like 19 transforms in the way: 19 → 82 → 68 → 100 → 1.
So, 19 is a happy number as it became 1, but not all numbers reach 1, others might loop in a endless cycle (unhappy numbers).

Ex -> for n = 2, the transformations are :- 2 → 4 → 16 → 37 → 58 → 89 → 145 → 42 → 20 → 4
after this, the cycle of 4 → 16 → 37 → 58 → 89 → 145 → 42 → 20 gets repeated endlessly and 2 never reaches 1.

So, with these transformation, either a number reaches 1 or loops in a endless cycle.

>> The Interesting Math
The constraints allow: n <= 2^31 - 1
Largest possible integer has 10 digits.
Even if we consider n = 9999999999 (which is beyond int limit), it has 10 digits.
even for this case, the sum of squares of digits will be 9^2 + 9^2 + .... + 9^2 (10 times) = 10 * 81 = 810.
Therefore: maximum sum of squares = 810.
It means: Even if we start with a 10-digit number,
after ONE transformation, n will become < 810 : n ≤ 810 
Example: 2147483647 becomes some value ≤ 810.
After that, all future values stay relatively small.
So, all the future transformations will result in values in range [1, 810).
Now, if the happy number is happy, it will end in 1, but if it's not, it will loop endlessly in a cycle 
where the same transformed numbers keeps re-appearing like we saw for the case n = 2, 
since the transformation values are limited, thus by pigeon-hole principle, it is guaranteed that same numbers will re-appear.

So, to check whether a number is happy or not, we just need to keep transforming the number until it becomes 1 or 
we see a number that we have already seen before (which means it is looping endlessly in a cycle and will never reach 1).
*/

// HashSet Approach : Time Complexity : O(k) __ Space Complexity : O(k)
/*
While doing the transformations, we need to check whether a transformed number has already been seen or not (to detect cycle).
Like for n = 2, the chain of transformations are 2 → 4 → 16 → 37 → 58 → 89 → 145 → 42 → 20 → 4. 
When we get 4, we stop as 4 has already been seen previously.
We can use a hash-set to check for re-occurrence of a number so to know whether a loop exists or not.

## Algorithm :-
1. Use a set to store the transformations.
2. Transform n using the helper method to get the sum of squares of digit. 
3. If the transformed value is 1, return true.
4. Else, check whether the transformed value has already been seen, if yes, return false.
5. Insert the transformed value into the hashset.

>> Complexity Analysis :-
Let k = number of transformations needed to reach 1 or to detect a cycle.
Time Complexity: O(k)
Space Complexity: O(k)
*/

// helper function -> returns sum of squares of digits of the number 'x'
int getDigitSqSum(int x) {
    int sum = 0;
    while (x) {
        int dig = x % 10;
        sum += dig * dig;
        x /= 10;
    }
    return sum;
}

bool isHappy1(int n) {
    if (n == 1) return true;
    set<int> s;
    while (true) {
        n = getDigitSqSum(n);
        if (n == 1) return true;
        if (s.count(n)) return false;
        s.insert(n);
    }
}

// Floyd's Cycle Detection (Tortoise and Hare) (Two Pointers) : Time Complexity : O(k) __ Space Complexity : O(1)
/*
When a number is transformed, it either becomes 1 or loops endlessly in a cycle.
when it becomes 1, the next transformations will remain 1. 
So, the transformation chain for some number would be of form 
Happy number A :- A → B → C → 1      (endless loop on 1, but we return true since 1 is reached)
Unhappy number J :- J → K → L → M → X → Y → L → ..... (cycle repeats)

So, we just need to check whether a loop exists or not, instead of using hashing for that, we can use the 
Floyd's Cycle Detection (also used to detect loops in a linked list).

>> Idea
Treat transformation as: f(n) = sum of squares of digits.
Example: 19 → 82 → 68 → 100 → 1
This forms a sequence just like moving through nodes of a linked list.

Use:
    slow = f(slow)
    fast = f(f(fast))

If: fast == 1 => happy number.
If: slow == fast => cycle found.

Visualization

For unhappy numbers, like for n = 2:
2 → 4 → 16 → 37 → 58 → 89 → 145 → 42 → 20 → 
    ↑                                     ↓
    ←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←

We can use two pointers fast & slow, move slow by 1 step at a time (move to the next transformation)
and fast moves by 2 step (moves to the next of next transformation). If loop exists, 
both fast and slow will eventually met inside the loop, i.e., become equal at some point.
If the number is happy, then both slow and fast will become 1, as transforming 1 creates a cycle of 1s.
*/

// helper function -> returns sum of squares of digits of the number 'x'
int nextNumber(int x) {
    int sum = 0;
    while (x) {
        int dig = x % 10;
        sum += dig * dig;
        x /= 10;
    }
    return sum;
}

bool isHappy2(int n) {
    int slow = n, fast = n;

    do {
        slow = nextNumber(slow);
        fast = nextNumber(fast);
    } while (slow != fast);

    return slow == 1;
}

// Mathematical Shortcut : Time Complexity : O(k) __ Space Complexity : O(1)
/*
There is a famous observation: Every unhappy number eventually reaches '4'.
Specifically the cycle: 4 → 16 → 37 → 58 → 89 → 145 → 42 → 20 → 4.
Therefore, if a number is happy, it will become 1 or 
else it will become 4 during transformations and then loop in the endless cycle.

So, we can simply do the transformations until we either get 1 (happy number) or 4 (unhappy number).
*/

bool isHappy3(int n) {
    while (n != 1 && n != 4) {
        n = getDigitSqSum(n);
    }
    return n == 1;
}

int main() {

    return 0;
}