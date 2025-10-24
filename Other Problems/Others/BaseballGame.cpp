/*
Leetcode - 682. Baseball Game

You are keeping the scores for a baseball game with strange rules. At the beginning of the game, you start with an empty record.
You are given a list of strings operations, where operations[i] is the ith operation you must apply to the record & is one of the following:
> An integer x : Record a new score of x.
> '+' : Record a new score that is the sum of the previous two scores.
> 'D' : Record a new score that is the double of the previous score.
> 'C' : Invalidate the previous score, removing it from the record.
Return the sum of all the scores on the record after applying all the operations.

The test cases are generated such that the answer and all intermediate calculations fit in a 32-bit integer & that all operations are valid.

Examples :-

Input: ops = ["5","2","C","D","+"] __ Output: 30
Explanation:
"5" - Add 5 to the record, record is now [5].
"2" - Add 2 to the record, record is now [5, 2].
"C" - Invalidate and remove the previous score, record is now [5].
"D" - Add 2 * 5 = 10 to the record, record is now [5, 10].
"+" - Add 5 + 10 = 15 to the record, record is now [5, 10, 15].
The total sum is 5 + 10 + 15 = 30.

Input: ops = ["5","-2","4","C","D","9","+","+"] __ Output: 27
Explanation:
"5" - Add 5 to the record, record is now [5].
"-2" - Add -2 to the record, record is now [5, -2].
"4" - Add 4 to the record, record is now [5, -2, 4].
"C" - Invalidate and remove the previous score, record is now [5, -2].
"D" - Add 2 * -2 = -4 to the record, record is now [5, -2, -4].
"9" - Add 9 to the record, record is now [5, -2, -4, 9].
"+" - Add -4 + 9 = 5 to the record, record is now [5, -2, -4, 9, 5].
"+" - Add 9 + 5 = 14 to the record, record is now [5, -2, -4, 9, 5, 14].
The total sum is 5 + -2 + -4 + 9 + 5 + 14 = 27.

Input: ops = ["1","C"] __ Output: 0
Explanation:
"1" - Add 1 to the record, record is now [1].
"C" - Invalidate and remove the previous score, record is now [].
Since the record is empty, the total sum is 0.
 
Constraints :-
1 <= operations.length <= 1000
operations[i] is "C", "D", "+", or a string representing an integer in the range [-3 * 104, 3 * 104].
For operation "+", there will always be at least two previous scores on the record.
For operations "C" and "D", there will always be at least one previous score on the record.
*/

#include <bits/stdc++.h>
using namespace std;

int calPoints(vector<string> &operations) {
    vector<int> records;
    int last = -1;
    for (string op : operations) {
        if (op == "C") {
            records.pop_back();
            last--;
        }
        else {
            int newRec = 0;
            if (op == "+")
                newRec = records[last - 1] + records[last];
            else if (op == "D")
                newRec = 2 * records[last];
            else
                newRec = stoi(op);

            records.push_back(newRec);
            last++;
        }
    }
    int sum = 0;
    for (int x : records) sum += x;

    return sum;
}

int main()
{
    vector<string> ops = {"5", "-2", "4", "C", "D", "9", "+", "+"};
    int sum = calPoints(ops);
    cout << sum << endl;

    return 0;
}