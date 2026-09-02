/*
GFG - Unoccupied Computers : Easy

A cafe has n computers. 
The customer events are represented by a string s of uppercase English letters, 
where each distinct letter appears exactly twice:
• The first occurrence denotes the customer's arrival.
• The second occurrence denotes the customer's departure.

A customer is assigned a computer only if one is available at the time of arrival, 
otherwise the customer is rejected and does not use a computer.

Return the number of customers who could not be assigned a computer upon arrival.

Examples :-

Input: n = 3, s = "GACCBDDBAGEE"
Output: 1
Explanation: Only D will not be able to get any computer. So the answer is 1.

Input: n = 1, s = "ABCBAC"
Output: 2
Explanation: B and C will not be able to get any computers. So the answer is 2.

Constraints :-
• 1 ≤ n ≤ 26
• 1 ≤ |s| ≤ 52
• s consists of uppercase English letters and each letter occurs exactly 2 times.
*/

#include <bits/stdc++.h>
using namespace std;

// Using Sets: Time Complexity : O(|s|)  __ Space Complexity : O(1)
/*
>> Thought process
We need to process the events in the order they happen, 
so the natural starting point is to simulate the cafe from left to right.

At any point, the main thing we care about is:
| Which customers are currently occupying computers?
So let's maintain a set assigned containing those customers.

Then, when a customer arrives, we can simply check:
| assigned.size() < n ?
If yes, we give them a computer and put them in assigned. Otherwise, they are rejected.

But there's a subtle problem.
Every customer appears exactly twice, so when we encounter a character, it could be either their arrival or their departure.

How can we tell the difference?
If the customer is already in assigned, then we've previously seen their arrival and given them a computer. 
Therefore, this occurrence must be their departure.

So:
    customer ∈ assigned
            ↓
    this is their departure
            ↓
    remove them from assigned

Now consider a customer who arrived when all computers were occupied.
They go into a different state: rejected.
We need to remember these customers too, because when their second occurrence appears, 
that's their departure — but since they never had a computer, nothing needs to be freed.

This suggests a second set:
assigned → customers currently using a computer
rejected → customers who arrived but couldn't get a computer

Now every event becomes easy to classify:

    Is customer already in assigned?
            │
           YES → departure → remove from assigned
            │
           NO
            ↓
    Is customer already in rejected?
            │
           YES → departure of rejected customer → ignore
            │
           NO
            ↓
          arrival
            │
            ├── computer available → add to assigned
            │
            └── no computer → add to rejected

>> The key intuition
The important observation is that we don't actually need to track arrival and departure separately.
Because every customer appears exactly twice, we only need to remember their current status:
assigned — "this customer has a computer right now"
rejected — "this customer already arrived, but never got a computer"
Once we maintain these two states, the second occurrence automatically tells us that the customer is leaving.
That's what leads naturally to using two hash sets and processing the string in a single pass.

>> Complexity: O(|s|) time and O(1) space, since there are only 26 possible customers.
*/
int solve(int n, string s) {
    unordered_set<char> assigned;
    unordered_set<char> rejected;
    
    for (char& c : s) {
        // customer's departure
        
        // if the customer was assigned a computer, free the computer            
        if (assigned.count(c)) 
            assigned.erase(c);
        // if customer was not assigned, move to the next customer event
        else if (rejected.count(c)) 
            continue;
        
        // customer's arrival
        
        // if there are free computers, assign a computer to customer
        else if (assigned.size() < n) {
            assigned.insert(c);   
        }
        // else, reject the customer
        else rejected.insert(c);
    }
    
    return rejected.size();
}

// Using Hasharrays : Time Complexity : O(|s|)  __ Space Complexity : O(1)
// We can also use two hashArrays along with occupied count & rejected count to implement the solution
int solveX(int n, string s) {
    bool assigned[26] = {};
    bool rejected[26] = {};
    
    int occupied = 0;
    int rejectedCount = 0;
    
    for (char c : s) {
        int ind = c - 'A';
        
        if (assigned[ind]) {
            assigned[ind] = false;
            occupied--;
        }
        else if (rejected[ind]) {
            continue;
        }
        
        else if (occupied < n) {
            assigned[ind] = true;
            occupied++;
        }
        else {
            rejected[ind] = true;
            rejectedCount++;
        }
    }
    
    return rejectedCount;
} 

int main() {
    return 0;
}