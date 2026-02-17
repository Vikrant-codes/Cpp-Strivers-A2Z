/*
Leetcode - 3842. Toggle Light Bulbs : Easy

You are given an array bulbs of integers between 1 and 100.
There are 100 light bulbs numbered from 1 to 100. All of them are switched off initially.
For each element bulbs[i] in the array bulbs:
- If the bulbs[i]th light bulb is currently off, switch it on.
- Otherwise, switch it off.
Return the list of integers denoting the light bulbs that are on in the end, sorted in ascending order. 
If no bulb is on, return an empty list.

Examples :-

Input: bulbs = [10,30,20,10]
Output: [20,30]
Explanation:
The bulbs[0] = 10th light bulb is currently off. We switch it on.
The bulbs[1] = 30th light bulb is currently off. We switch it on.
The bulbs[2] = 20th light bulb is currently off. We switch it on.
The bulbs[3] = 10th light bulb is currently on. We switch it off.
In the end, the 20th and the 30th light bulbs are on.

Input: bulbs = [100,100]
Output: []
Explanation:
The bulbs[0] = 100th light bulb is currently off. We switch it on.
The bulbs[1] = 100th light bulb is currently on. We switch it off.
In the end, no light bulb is on.

Constraints :-
- 1 <= bulbs.length <= 100
- 1 <= bulbs[i] <= 100
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> toggleLightBulbs(vector<int>& bulbs) {
    vector<int> Lights(100);
    // 0 means off
    // 1 means on

    for (int& x: bulbs) {
        // if light was off, turn it on
        if (Lights[x-1] == 0) 
            Lights[x-1] = 1;
        // else if light was on, turn it off
        else
            Lights[x-1] = 0;
    }

    vector<int> ans;
    for (int i = 0; i < 100; i++)
        if (Lights[i] == 1) 
            ans.push_back(i+1);
    
    return ans;
}

vector<int> toggleLightBulbs2(vector<int>& bulbs) {
    vector<int> freq(100);
    // if freq is odd, means the bulb is switched on, else off 

    for (int& x: bulbs)
        freq[x-1]++;

    vector<int> ans;
    for (int i = 0; i < 100; i++)
        // if odd frequency, add the bulb to answer 
        if (freq[i] % 2 == 1)   
            ans.push_back(i+1);
    
    return ans;
}

int main() {
    return 0;
}