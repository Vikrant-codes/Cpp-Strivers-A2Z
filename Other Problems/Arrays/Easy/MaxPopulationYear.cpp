/*
Leetcode - 1854. Maximum Population Year : Easy

You are given a 2D integer array logs where each logs[i] = [birthi, deathi] indicates the birth and death years of the ith person.

The population of some year x is the number of people alive during that year. 
The ith person is counted in year x's population if x is in the inclusive range [birthi, deathi - 1]. 
Note that the person is not counted in the year that they die.

Return the earliest year with the maximum population.

Examples :-

Input: logs = [[1993,1999],[2000,2010]] __ Output: 1993
Explanation: The maximum population is 1, and 1993 is the earliest year with this population.

Input: logs = [[1950,1961],[1960,1971],[1970,1981]] __ Output: 1960
Explanation: 
The maximum population is 2, and it had happened in years 1960 and 1970.
The earlier year between them is 1960.

Constraints :-
- 1 <= logs.length <= 100
- 1950 <= birthi < deathi <= 2050
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(n) __ Space Complexity : O(1)
/*
Given the constraints 1950 <= birthi < deathi <= 2050.
So, the birth & death years are in range [1950, 2050].
We find the population for each year in the range [1950, 2050] and return the earliest year having maximum population.
To find the population of a year, we traverse the logs array and finds the person who were alive during that year.
For a year 'x', 
we can check whether a person was alive during the year 'x' or not by checking the birth & death years of the person
If birth <= x < death, that means the person was alive during year 'x'.

Use this method to count the alive person population for each year.
Keep doing this for all years and return the year with maximum population
*/

int maximumPopulation(vector<vector<int>>& logs) {
    int mx_pop = 0, mx_year = 9999;
    for (int year = 1950; year <= 2050; year++) {
        int pop = 0;

        for (auto& log : logs) {
            if (log[0] <= year && log[1] > year) pop++;
        }
        
        if (pop > mx_pop) {
            mx_year = year;
            mx_pop = pop;
        }
    }
    return mx_year;
}

// PrefixSum approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Core observation
Each person affects the population only during a continuous range of years:
born at b ───────── alive ───────── dies at d
           [ b , d )
Meaning:
• contributes +1 population starting from year b
• stops contributing at year d (death year is excluded)
So the population over years is just the sum of many overlapping ranges.

Prefix-sum mindset
Instead of asking:
| “Who is alive in this year?”
ask:
| “How does the population change when we move from one year to the next?”
Population only changes at birth years and death years.
Nothing else matters.

Think in terms of “events”
Each log [b, d] creates two events:
| Year | Effect                        |
| ---- | ----------------------------- |
|  b   | population   increases by 1   |
|  d   | population   decreases by 1   |


>> Difference array intuition
Imagine an array where: 
yearDiff[y] = change in population AT year y
For one person:
yearDiff[b] += 1,       birth increases that years population
yearDiff[d] -= 1,       death decreases that years population

If 3 people are born in 1960 → +3
If 2 people die in 1970 → -2
So the array might look like:
Year:      1950 1951 1952 1953 ...
Change:      +2    0   -1   +3 ...
This array does NOT store population, only changes.

Prefix sum = reconstructing reality

Now we ask:

“What is the actual population in each year?”
Answer:
👉 Add all previous changes
    population[y] = population[y-1] + yearDiff[y]
That’s exactly what a prefix sum does.
So as you scan year by year:
• keep a running total
• this running total = population that year
• track the maximum

Death year being exclusive (important intuition)
If someone dies in 1970:
• they are alive in 1969
• not alive in 1970
So population must decrease exactly at 1970, hence: diff[d] -= 1

Mental model to remember
|   “Mark where population starts, mark where it ends, then walk forward accumulating changes.”
*/

int maximumPopulation(vector<vector<int>>& logs) {
    vector<int> births(101);
    for (auto& log : logs) {
        births[log[0] - 1950]++;            // increment for birth count
        births[log[1] - 1950]--;            // decrement due to death count
    }

    int mxPop = 0, curr = 0, year = 1950;
    for (int i = 0; i < 101; i++) {
        curr += births[i];
        if (curr > mxPop) {
            mxPop = curr;
            year = 1950 + i;
        }
    }
    return year;
}

int main() {
    return 0;
}