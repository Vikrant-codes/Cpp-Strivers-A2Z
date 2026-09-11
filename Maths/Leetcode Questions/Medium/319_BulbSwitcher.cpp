/*
Leetcode - 319. Bulb Switcher : Medium

There are n bulbs that are initially off. You first turn on all the bulbs, then you turn off every second bulb.
On the third round, you toggle every third bulb (turning on if it's off or turning off if it's on). For the ith round, 
you toggle every i bulb. For the nth round, you only toggle the last bulb.
Return the number of bulbs that are on after n rounds.

Examples :-

Input: n = 3 __ Output: 1
Explanation: At first, the three bulbs are [off, off, off].
After the first round, the three bulbs are [on, on, on].
After the second round, the three bulbs are [on, off, on].
After the third round, the three bulbs are [on, off, off]. 
So you should return 1 because there is only one bulb is on.

Input: n = 0 __ Output: 0
Input: n = 1 __ Output: 1

Constraints :- 0 <= n <= 10^9
*/

#include <bits/stdc++.h>
using namespace std;

// Observations and Logic
/*
### Only the bulbs at position number 'k' such that 'k' has odd count of factors, are left 'ON'

If we read and understand the problem carefully, we can see that in each round 'i', 
the bulbs at position 'multiples of i' are toggled (switched on if previously off, switched off if previously on).
So, the final state of a bulb at position 'k' depends on the number of factors it has, since, 
the bulb 'k' will be toggled as many times as its factors count.
Initially the bulbs were off and for each factor, the bulbs gets toggled, 
so it becomes ON -> OFF -> ON -> OFF ... for each factor it has
Thus, if the bulb is at position 'k' such that 'k' has even number of factors, then the final state of the bulb will be 'OFF'
since we see that for every pair of two factors, the bulb gets switched off.
Only, in the final state, only the bulbs with 'odd' number of factors are switched ON.

### Only perfect squares have odd number of factors
In general, if 'x' is a factor of 'k', i.e., x divides k, then there exists some number 'y' such that x * y = k.
Lets say this 'y' is the complement factor of 'x' for 'k'. 
So, for every factor 'x', there is a complement factor 'y'.. This x & y factor pair makes the factor count of 'k' even.
To make the factor count odd, there must be a condition such that x & y are equal i.e. k / x = y = x, or, x * x = k.

This condition is only possible for perfect squares since rest other numbers have a different complement factor for each factor
which makes its factor count even.

Ex- consider for 15 -> factors : 1, 3, 5, 15 .... factor-pairs : 1 x 15, 3 x 5 ... factor-count = 4
16 -> factors : 1, 2, 4, 8, 16 .... factor-pairs : 1 x 16, 2 x 8, 4 x 4 ... factor-count = 5
16 has an odd factor count because the complement factor of '4' is '4' itself. This happens since 16 is a perfect square.

even prime numbers have even number of factors.

So, only perfect squares have odd number of factors.

### Number of bulbs ON after 'n' rounds = count of perfect squares till 'n'.
Since we know that only the bulbs with positions such that it has odd number of factors will be left ON, and 
only perfect squares have odd number of factors, So, we know that after 'n' rounds, only the bulbs at perfect-square positions
will be left 'ON'. So, count of bulbs ON after n rounds = count of perfect squares till n.
*/


// Naive Approach :- Time Complexity : O(n√n) __ Space Complexity : O(1)
/*
Count the perfect squares till 'n' by checking whether each number is a perfect square or not.
Loop from 1 to n and for each integer 'i' check if i is a perfect square. If yes, increment count.

>> Time Complexity Analysis :-
- isPerfectSquare(x) runs a loop up to √x → O(√x)
- Outer loop runs n times
- Total Time Complexity : O(n√n)
*/

// for numbers less than 1, the loop inside the bulbSwitch function would not run,
// so no need to write extra condition checks for such numbers.
bool isPerfectSquare(int x) {
    for (int i = 1; i * i <= x; i++) 
        if (i * i == x) 
            return true;

    return false;
}
int bulbSwitch1(int n) {
    int cnt = 0;
    for (int i = 0; i <= n; i++) 
        if (isPerfectSquare(i))
            cnt++;
    return cnt;
}

// Better Approach : Time Complexity : O(sqrt(n)) __ Space Complexity : O(1)
/*
There is a better way to count perfect squares upto 'n'.
Asssume we need to print all perfect square upto 'n', then we could do something like 
    for (int i = 1; i * i <= n; i++)
        cout << i;
or, we can use while loop like ->
    int i = 1;
    while (i * i <= n)
        cout << i++;
doing so would display all perfect squares upto 'n',
we can use this logic to get the count of the perfect squares as the count of perfect squares till 'n' 
would be equal to as many times as this loop runs.
So, we could use a counter variable to count the number of times loop runs or we can directly get the count from i.
the while loop exits when 'i' value becomes such that 'i * i'becomes greater than 'n', 
so that the ith perfect square became greater than 'n', so count of perfect squares till n = i - 1.
*/
int bulbSwitch2(int n) {
    int i = 1;
    while (i * i <= n) {
        // cout << i * i << " ";       // ith perfect square
        i++;            // increment i to check for the next perfect square
    }
    return i - 1;       // i - 1 will give us the count of perfect square
}

// Optimal Approach : Time Complexity 
/*
We want to count the perfect squares upto 'n'.
Assume 'k' is the largest integer such that its square (k * k <- perfect square) is less than/equal to 'n'..
i.e. 1^2, 2^2, 3^2, .... (k-1)^2, k^2  <= n
therefore, k * k <= n
we are assuming that the square of k+1 i.e. the (k+1)th perfect square is greater than 'n'.
Now, this count of perfect sqaures [1^2, 2^2, 3^2, .... (k-1)^2, k^2] less than eqaul to n, would be equal to 'k'.
we can get the value of k also, since k * k <= n  →  k <= sqrt(n)   →   k = floor(sqrt(n))
So, the count of perfect squares upto n = sqrt(n) .. 
(we don't need to do floor as it would be handled automatically when converting to integer) 
*/
int bulbSwitch(int n) {
    return sqrt(n);
}

/*
Key Idea:

Each bulb is toggled once for every divisor it has.

Example:
Bulb at position 6 → divisors: 1, 2, 3, 6 → toggled 4 times → OFF
Bulb at position 9 → divisors: 1, 3, 9 → toggled 3 times → ON

So:
- Even number of divisors → bulb ends OFF
- Odd number of divisors → bulb ends ON

----------------------------------------

Important Observation:

Divisors usually come in pairs:
Example:
12 → (1,12), (2,6), (3,4) → total = 6 (even)

But for perfect squares:
16 → (1,16), (2,8), (4,4)

Here, 4 is repeated (paired with itself), so total divisors = 5 (odd)

----------------------------------------

Conclusion:

Only perfect squares have an odd number of divisors.

So after all rounds:
Only bulbs at positions:
1, 4, 9, 16, 25, ... remain ON

----------------------------------------

Final Answer:

Number of bulbs ON = number of perfect squares ≤ n

That is simply:
floor(sqrt(n))
*/


int main() {
    return 0;
}


/*
bool isPerfectSquare(int x, int &st) {
    for (int i = st; i <= x/i; i++) {
        if (i * i == x) {
            return true;
            st++;
        }
    }
    return false;
}

int bulbSwitch(int n) {
    // int cnt = 0;
    // int st = 1;
    // for(int i = 1; i <= n; i++) {
    //     if (isPerfectSquare(i, st)) {
    //         cnt++;
    //         cout << i << " ";
    //     }
    // }
    // return cnt;

    return sqrt(n);

    // we need the count of all perfect squares upto n 
    // now imagine the number is n then say if k ^ 2 is the largest perfect square upto n then k * k <= n --> k <= sqrt(n) i.e. floor(sqrt(n))
    // since k ^ 2 is the largest integer perfect square then all the numbers 1,2,3,....,k all these numbers sqaure lie in the range of n. 
    // so the count of all the perfect sqaures upto n is the count of integers 1,2,3,..,k such that k <= sqrt(n) and this count is k itself
    // so we return sqrt(n) itself as the total count of perfect squares upto n
}
*/