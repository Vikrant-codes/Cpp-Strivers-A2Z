/*
Leetcode - 29. Divide Two Integers : Medium

Given two integers dividend and divisor, divide two integers without using multiplication, division, and mod operator.
The integer division should truncate toward zero, which means losing its fractional part. 
For example, 8.345 would be truncated to 8, and -2.7335 would be truncated to -2.

Return the quotient after dividing dividend by divisor.

Note: Assume we are dealing with an environment that could only store integers 
within the 32-bit signed integer range: [−2^31, 2^31 − 1]. 
For this problem, if the quotient is strictly greater than 2^31 - 1, then return 2^31 - 1, 
and if the quotient is strictly less than -2^31, then return -2^31.

Examples :-

Input: dividend = 10, divisor = 3 __ Output: 3
Explanation: 10/3 = 3.33333.. which is truncated to 3.

Input: dividend = 7, divisor = -3 __ Output: -2
Explanation: 7/-3 = -2.33333.. which is truncated to -2.

Constraints :-
• -2^31 <= dividend, divisor <= 2^31 - 1
• divisor != 0
*/

#include <bits/stdc++.h>
using namespace std;

// Intuition
/*
# LeetCode 29 – Divide Two Integers

The central idea is:

We know that `dividend = divisor * quotient`.

We can break the quotient into a sum of powers of 2 and use that to subtract larger chunks of the dividend at once.

---

## Naive Approach – Repeated Subtraction

Let's first understand how we can obtain the quotient without using the division operator.

Suppose:

`dividend = 43, divisor = 5`

We know:

`43 = 5 * 8 + 3`

The quotient is 8, and the remainder is 3.

How can we obtain this without division?

We repeatedly subtract the divisor from the dividend until the remaining value becomes smaller than the divisor.

```
43 - 5 = 38    quotient = 1
38 - 5 = 33    quotient = 2
33 - 5 = 28    quotient = 3
28 - 5 = 23    quotient = 4
23 - 5 = 18    quotient = 5
18 - 5 = 13    quotient = 6
13 - 5 = 8     quotient = 7
 8 - 5 = 3     quotient = 8
```

Now, `3 < 5`, so we cannot subtract anymore. Our quotient is 8.

The basic code would be:

```
while (dividend >= divisor) {
    dividend -= divisor;
    quotient++;
}
```

*Complexity: O(dividend / divisor).

This approach is inefficient when the dividend is very large compared to the divisor.
For example, in a case like `dividend = 10^9, divisor = 2`, repeated subtraction would require 5 * 10^8 iterations.

---

## Optimization – Subtract Larger Chunks Using Powers of 2

Now let's see how we can improve this.

We know:

`dividend = divisor * quotient + remainder`

We also know that any positive integer can be represented as a sum of powers of 2.

Example:

`13 = 2^3 + 2^2 + 2^0 = 8 + 4 + 1`

Consider that we need to find `67 / 5`.

We know:

`67 = 5 * 13 + 2`

So, the quotient is 13.

This 13 can be represented as `8 + 4 + 1`.

Therefore:

`67 = 5 * (8 + 4 + 1) + 2`

Now we can calculate the quotient by subtracting the divisor in chunks of powers of two:

| Operation    | Remaining dividend | Quotient |
|--------------|--------------------|----------|
| 67 - (5 * 8) | 27                 | 8        |
| 27 - (5 * 4) | 7                  | 12       |
| 7 - (5 * 1)  | 2                  | 13       |

So we obtain:
`67 = 5 * (8 + 4 + 1) + 2`

Our quotient is 13!

This is the fundamental idea behind the optimized solution.

Instead of repeatedly subtracting the divisor, we subtract `divisor * powers of 2` to obtain the quotient faster.

---

## Using Bit Manipulation

We know that multiplying a number by a power of 2 can be achieved using left shifting.

```
5 << 0 = 5
5 << 1 = 10
5 << 2 = 20
5 << 3 = 40
```

Essentially: 

`d * 2^i = d << i`

Now we need to figure out how to find the largest possible power of 2 such that:

`divisor * 2^i <= dividend`

There are two ways to do this.

### Approach 1 – Find the Highest Possible Power of 2 Dynamically

We start from the 0th bit and gradually increase the shift 
until the next power of 2 multiplied by the divisor exceeds the remaining dividend.

In other words, we keep increasing `cnt` as long as:

`n >= d * 2^(cnt + 1)` or `n >= d << (cnt + 1)`

Once the condition becomes false, we have found the largest possible power of 2 that can be multiplied 
by the divisor without exceeding the remaining dividend.

We then:
- Add `2^cnt` or `1 << cnt` to the quotient.
- Subtract `d * 2^cnt` or `d << (cnt + 1)` from the remaining dividend.
- Repeat the process until the remaining dividend becomes smaller than the divisor.

### Approach 2 – Check From the 31st Bit to the 0th Bit

Instead of dynamically finding the highest possible power of 2, 
we can start from the largest possible power and gradually move towards smaller powers.

Why? Because we want to subtract the largest possible chunk first.

For example, with `dividend = 67` and `divisor = 5`:

- First, we check whether `5 * 2^31` fits inside 67.
- Then `5 * 2^30`.
- Continue until we find a power that fits.
- Once we find one, subtract it and update the quotient.
- Continue checking smaller powers.

We can perform this using a single loop, checking each bit from 31 down to 0.

---

## Important Edge Cases

There are two things we must be careful about.

### 1. Handling Negative Numbers

The given integers can be negative. We keep our logic based on positive numbers and work with absolute values.

We can maintain a sign flag to know whether the answer should be negative or positive, 
work with the absolute values of the dividend and divisor, and compute the quotient.

We can then return the quotient or -quotient, depending on the sign.

`dividend / divisor` would be negative if either the dividend or divisor is negative (but not both).

If both integers are positive or both are negative, the quotient will be positive.

- Both positive or both negative → Positive result.
- One negative → Negative result.

We can use if conditions to check whether exactly one of the dividend or divisor is negative:

```
bool negative = false;

if ((dividend >= 0 && divisor < 0) ||
    (dividend < 0 && divisor > 0))
    negative = true;
```

Or, we can use XOR:

```
bool negative = (dividend < 0) ^ (divisor < 0);
```

XOR returns true when exactly one of the two conditions is true.

### 2. Handling INT_MIN

The minimum 32-bit integer is:

`-2^31 = -2147483648`

Its positive counterpart, `2147483648`, cannot fit inside an `int`.

That's why we need to convert to `long long` before taking the absolute value.

We can also explicitly handle the case:

`-2147483648 / -1 = 2147483648`

This value doesn't fit in an `int`, and we are supposed to return `INT_MAX`, which is 2147483647.

```
if (dividend == INT_MIN && divisor == -1)
    return INT_MAX;
```
*/

// Approach 1 (Dynamic Highest Power of 2): Time Complexity : O(log n)^2 __ Space Complexity : O(1)
/*
Time Complexity: O(log^2 n)

- The outer while loop repeatedly subtracts the largest possible power-of-2 multiple of the divisor.
- The inner while loop searches for the highest possible power of 2.
- Both loops take at most O(log n) iterations.
- Therefore, the overall complexity is O(log^2 n).

Space Complexity: O(1)

- Only a constant number of variables are used.
*/

int divide1(int dividend, int divisor) {

    if (dividend == divisor)
        return 1;

    bool sign = true;

    if (dividend >= 0 && divisor < 0) sign = false;
    else if (dividend < 0 && divisor > 0) sign = false;

    long n = abs((long) dividend);      
    // `long` is 64-bit on platforms like Leetcode, we can use `long long` for more portability
    long d = abs((long) divisor);

    long quotient = 0;

    while (n >= d) {

        int cnt = 0;

        while (n >= (d << (cnt + 1))) {
            cnt += 1;
        }

        quotient += (1LL << cnt);

        n -= (d << cnt);
    }

    if (quotient == (1LL << 31)) {
        return sign ? INT_MAX : INT_MIN;
    }

    return sign ? quotient : -quotient;
}

// Approach 2 (Check From the 31st Bit to the 0th Bit): Time Complexity : O(1) __ Space Complexity : O(1)
/*
Time Complexity: O(1)

- We iterate through the bits from 31 down to 0.
- Therefore, we perform at most 32 iterations.
- Since the integer size is fixed at 32 bits, the time complexity is O(1).

Space Complexity: O(1)

- Only a constant number of variables are used.
*/
int divide(int dividend, int divisor) {

    if (dividend == INT_MIN && divisor == -1)
        return INT_MAX;

    bool negative = (dividend < 0) ^ (divisor < 0);
    // XOR helps keep the sign as negative only if any one of the two conditions is true, but not both

    long long a = llabs((long long)dividend);
    long long b = llabs((long long)divisor);

    long long quotient = 0;

    for (int i = 31; i >= 0; i--) {

        // Check whether b * 2^i can be subtracted from the remaining dividend (a).
        // Right shifting a by i is equivalent to checking whether a >= b * 2^i, without directly multiplying.

        if ((a >> i) >= b) {    // equivalent to (a / 2^i) >= b

            // Subtract this chunk (b * 2^i) from the remaining dividend.
            a -= (b << i);

            // Since we subtracted b * 2^i, add 2^i to the quotient.
            quotient += (1LL << i);
        }
    }

    if (negative)
        quotient = -quotient;

    return (int)quotient;
}

int main() {
    return 0;
}