/*
Leetcode - 1288. Remove Covered Intervals : Medium

Given an array intervals where intervals[i] = [li, ri] represent the interval [li, ri), 
remove all intervals that are covered by another interval in the list.
The interval [a, b) is covered by the interval [c, d) if and only if c <= a and b <= d.
Return the number of remaining intervals.

Examples :-

Input: intervals = [[1,4],[3,6],[2,8]]
Output: 2
Explanation: Interval [3,6] is covered by [2,8], therefore it is removed.

Input: intervals = [[1,4],[2,3]]
Output: 1

Constraints :-
• 1 <= intervals.length <= 1000
• intervals[i].length == 2
• 0 <= li < ri <= 10^5
• All the given intervals are unique.
*/

#include <bits/stdc++.h>
using namespace std;

// returns true if intervalB can cover intervalA
bool canCover(vector<int>& intervalA, vector<int>& intervalB) {
    return intervalB[0] <= intervalA[0] && intervalA[1] <= intervalB[1];
}

int removeCoveredIntervals(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());

    vector<vector<int>> ans;
    ans.push_back(intervals[0]);
    int lastInd = 0;
    
    for (vector<int> interval : intervals) {
        if (interval[0] == ans[lastInd][0]) 
            ans[lastInd][1] = interval[1];

        else {
            if (!canCover(interval, ans[lastInd])) {
                ans.push_back(interval);
                lastInd++;
            }
        }
    }

    return ans.size();
}

// returns true if intervalB can cover intervalA
bool canCover2(vector<int>& intervalA, vector<int>& intervalB) {
    // since all given intervals are unique, two equal interval means we are checking the same interval
    if (intervalA == intervalB) return false;

    return intervalB[0] <= intervalA[0] && intervalA[1] <= intervalB[1];
}

int removeCoveredIntervals(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());
    int n = intervals.size();

    int cnt = 0;
    
    for (int i = 0; i < n; i++) {
        int j = 0;
    
        while (j < n) {
            if (canCover2(intervals[i], intervals[j])) break;
    
            if (intervals[j][0] > intervals[i][0]) {
                cnt++;
                break;
            }
    
            j++;
        }
    
        if (j == n) cnt++;
    }
    
    return cnt;
}

int main() {
    return 0;
}