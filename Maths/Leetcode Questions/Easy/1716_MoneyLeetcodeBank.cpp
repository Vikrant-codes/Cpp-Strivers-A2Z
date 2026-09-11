/*
Leetcode - 1716. Calculate Money in Leetcode Bank : Easy

Hercy wants to save money for his first car. He puts money in the Leetcode bank every day.
He starts by putting in $1 on Monday, the first day. 
Every day from Tuesday to Sunday, he will put in $1 more than the day before. 
On every subsequent Monday, he will put in $1 more than the previous Monday.

Given n, return the total amount of money he will have in the Leetcode bank at the end of the nth day.

Examples :-

Input: n = 4 __ Output: 10
Explanation: After the 4th day, the total is 1 + 2 + 3 + 4 = 10.

Input: n = 10 __ Output: 37
Explanation: After the 10th day, the total is (1 + 2 + 3 + 4 + 5 + 6 + 7) + (2 + 3 + 4) = 37. 
Notice that on the 2nd Monday, Hercy only puts in $2.

Input: n = 20 __ Output: 96
Explanation: 
After the 20th day, the total is (1 + 2 + 3 + 4 + 5 + 6 + 7) + (2 + 3 + 4 + 5 + 6 + 7 + 8) + (3 + 4 + 5 + 6 + 7 + 8) = 96.
 
Constraints :- 1 <= n <= 1000
*/

#include <bits/stdc++.h>
using namespace std;

// Mathematical Formula Approach :- Time Complexity : O(1) __ Space Complexity : O(1)
/*
🧠 Intuition & Observations
The problem describes a pattern of daily deposits:
- On Monday of the 1st week, you deposit $1.
- Each next day of the same week, you deposit 1 more than the previous day (i.e., Tue = $2, Wed = $3, …).
- On each new week, the starting amount increases by $1 (2nd week starts with $2, 3rd with $3, etc.).
Example deposits:
| Week | Daily Deposits      | Weekly Total |
| ---- | ------------------- | ------------ |
| 1st  | 1, 2, 3, 4, 5, 6, 7 | 28           |
| 2nd  | 2, 3, 4, 5, 6, 7, 8 | 35           |
| 3rd  | 3, 4, 5, 6, 7, 8, 9 | 42           |

Notice that each week’s total increases by 7 (an arithmetic pattern).
So weekly totals also form an arithmetic progression (A.P.): 28, 35, 42, 49, …

Also notice that daily deposits for a week forms an arithmetic progression starting with start_day_price of week same 
as week no. and incrementing by 1 every day till week ends. (so a = start_day_price, d = 1, n = no_of_remaining_days)

We can convert the total given days 'n' into weeks and days as weeks = n / 7, days = n % 7.
Example -- n = 38 days, weeks = 38 / 7 = 5, days = 38 % 7 = 3... So, 38 days = 5 weeks 3 days
Since weekly total & remaining_days_price forms A.P., we can find the sum of weeks & remaining days easily using sum formula.
--> Sum of A.P. is given by the formula S = n * [2*a + (n-1) * d] / 2 <-- 

Sum of weekly total A.P. ==> n = weeks, a = 28 (sum total of 1st week), d = 7 (each week total increments by 7)
Thus, sum of weeks total = weeks * [2 * 28 + (weeks - 1) * 7] / 2;

Sum of remaining days ==> remaining days also form A.P. starting with start_day_price = weeks + 1 
Ex- for n = 38, weeks = 5, days = 3, on the remaining days 6th week starts and thus monday price would be 6 = weeks + 1
So, remaining days forms A.P. with start_days = weeks + 1 and A.P. elements = days, d = 1
So, sum = days * [2 * sdp + days - 1] / 2; where sdp = weeks + 1

⚙️ Algorithm (Step-by-Step)
1. Convert total days (n) into full weeks and remaining days: int weeks = n / 7; int days = n % 7;
2. Compute money from all full weeks: int weeks_price = weeks * (2 * 28 + (weeks - 1) * 7) / 2;
3. Compute start_day_price for the remaining days of partial (incomplete) week: int sdp = weeks + 1; 
4. Compute money for remaining days of partial week : int days_price = days * (2 * sdp + days - 1) / 2;
5. Return total = weeks_price + days_price

✨ Summary of Key Observations
- Weekly totals form an arithmetic sequence: 28, 35, 42, …
- Each week’s start deposit = week_number.
- Remaining days (if any) also form an arithmetic sequence.
- Therefore, the entire sum can be computed using A.P. formula without simulation.
*/
int totalMoney(int n) {
    int weeks = n / 7;
    int days = n % 7;
    
    int weeks_price = weeks * (2 * 28 + (weeks - 1) * 7 ) / 2;

    // sdp = start day price for the remaining days
    int sdp = weeks + 1;
    int days_price = days * (2 * sdp + days - 1) / 2;

    return weeks_price + days_price;
}

int main() {
    return 0;
}