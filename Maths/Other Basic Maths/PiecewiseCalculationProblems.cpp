#include <bits/stdc++.h>
using namespace std;

/*
>> Piecewise Calculation Problems

Piecewise calculation problems in coding require evaluating different mathematical formulas 
or rules depending on which input range or condition is met.

They aren't algorithmically difficult, 
but they require you to think carefully about how to calculate costs for different ranges. 

>> Core Concepts
1. Conditional Logic
Using if, else if, and else statements to check value boundaries.

2. Interval Mapping
Matching an input variable (like income or weight) to a specific domain piece.

3. Boundary Handling
Ensuring edge values (e.g., exactly at 10kg or $10,000) trigger the correct rule without overlapping errors.

>> Common Coding Examples
- Tax Brackets: Applying different tax rates depending on whether income falls into tier 1, tier 2, or tier 3.
- Utility Bills: Charging a lower rate for the first 100 kilowatt-hours and a higher rate for usage above that limit.
- Math Functions: Implementing step functions or the absolute value function f(x) = x if x >= 0 else -x.
*/

// Parking Price Calculator

/*
Assume the parking charges are:
- 1st hour → ₹100
- Next 4 hours (hours 2–5) → ₹50/hour
- Every hour after 5 → ₹20/hour
*/

// Method 1
int parkingCost1(int hours) {
    int cost = 0;

    if (hours >= 1) {
        cost += 100;
        hours--;
    }

    if (hours > 0) {
        int curr = min(hours, 4);
        cost += curr * 50;
        hours -= curr;
    }

    if (hours > 0) {
        cost += hours * 20;
    }

    return cost;
}

// Method 2
int parkingCost2(int hours) {
    if (hours <= 1)
        return hours * 100;

    if (hours <= 5)
        return 100 + (hours - 1) * 50;

    return 100 + 4 * 50 + (hours - 5) * 20;
}

// Method 3 (General Pattern)
int parkingCost(int hours) {
    int cost = 0;

    cost += min(hours, 1) * 100;
    cost += min(max(hours - 1, 0), 4) * 50;
    cost += max(hours - 5, 0) * 20;

    return cost;
}
/*
>> Why does this work?
Suppose hours = 8

Tier 1:
    min(8,1) = 1
    1 × 100 = 100

Tier 2:
    max(8-1,0)=7
    min(7,4)=4
    4 × 50 = 200

Tier 3:
    max(8-5,0)=3
    3 × 20 = 60

Total = 360

No if statements at all.
*/


/*
>> The underlying pattern

Whenever there is something like:
    First A items -> Cost X
    Next B items  -> Cost Y
    Remaining     -> Cost Z

We can code it as:
    cost += min(n, A) * X;
    cost += min(max(n - A, 0), B) * Y;
    cost += max(n - (A + B), 0) * Z;

This generalizes beautifully.

For example:
    First 10 GB      free
    Next 20 GB       ₹5/GB
    Remaining        ₹2/GB

becomes
    cost += min(max(gb - 10, 0), 20) * 5;
    cost += max(gb - 30, 0) * 2;

No case analysis required.
*/

int main() {
    return 0;
}