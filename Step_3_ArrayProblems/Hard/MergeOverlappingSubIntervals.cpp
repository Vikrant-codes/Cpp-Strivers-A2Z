/*
Leetcode - 56. Merge Intervals : Medium

Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, and return an array of the non-overlapping 
intervals that cover all the intervals in the input.

Input: intervals = [[1,3],[2,6],[8,9],[9,11],[8,10],[2,4],[15,18],[16,17]] __ Output: [[1,6],[8,11],[15,18]]
Explanation: intervals [1,3],[2,6],[2,4] overlap and merge to [1,6] __ [8,9],[9,11],[8,10] merge to [8,11] __ [15,18],[16,17] merge to [15,18]

Input: intervals = [[1,3],[2,6],[8,10],[15,18]] __ Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].

Input: intervals = [[1,4],[4,5]] __ Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach : Time Complexity : O(n log n) + O(2 * n) __ Space Complexity : O(1)
/*
Approach :- First sort then for each interval make start, end as interval start, end and check for the next intervals of the array. 
If that next interval is overlapping update the end accordingly but if it isn't then we don't need to go any further looking for overlapping intervals
since the array is sorted. So in case the interval isn't overlapping break out of the second loop and after doing so add the {start,end} vector to the 
result vector since this is one of the merged interval. Now do the same for the next interval but while doing so check if the current interval is not
alreay included in the result vector i.e. if it is not already merged. This is done by checking whether the result vector is non-empty and the end 
of current interval is less than equal to the end of the last interval of the result (ans.back()[1]). If it is true that means the current interval 
is already included/merged so we skip the iteration for that interval and move to the next one.

Time Complexity: O(N*logN) + O(2*N), where N = the size of the given array.
Reason: Sorting the given array takes  O(N*logN) time complexity. Now, after that, we are using 2 loops i and j. But while using loop i, 
we skip all the intervals that are merged with loop j. So, we can conclude that every interval is roughly visited twice
(roughly, once for checking or skipping and once for merging). So, the time complexity will be 2*N instead of N2.

Space Complexity: O(1), as we are using an answer list to store the merged intervals. Except for the answer array, we are not using any extra space.
*/
vector<vector<int>> mergeOverlappingIntervalsBrute(vector<vector<int>> &arr) {
    int n = arr.size(); // size of the array
    //sort the given intervals:
    sort(arr.begin(), arr.end());
    vector<vector<int>> ans;

    for (int i = 0; i < n; i++) { // select an interval:
        int start = arr[i][0];
        int end = arr[i][1];

        //Skip all the merged intervals:
        if (!ans.empty() && end <= ans.back()[1]) {
            continue;
        }
        //check the rest of the intervals:
        for (int j = i + 1; j < n; j++) {
            if (arr[j][0] <= end) {
                end = max(end, arr[j][1]);
            }
            else {
                break;
            }
        }
        ans.push_back({start, end});
    }
    return ans;
}

// Optimal Approach : Time Complexity : O(n log n) + O(n) __ Space Complexity : O(1)
/*
Sort the array and start iterating from the first interval. The ans vector is used to store the merged intervals. Initially the ans vector is empty so 
we add the first interval to it. For the next intervals we check if that interval overlaps with the last interval stored in the ans vector. If it does 
overlap then we change the end of the last interval of the ans vector (i.e. ans.back()[1] is updated to max(ans.back()[1], arr[i][1])). If it doesn't
overlaps that means the current interval is a different one so needs to be pushed to the ans vector. 

Algo ->
1. For each interval in array
2. Check if ans is empty or the current interval overlaps with the last interval of the ans vector
3. If condition is true then add that interval to the ans vector
4. Else it means that the current interval overlaps with the last interval of the ans vector 
5. So we update the end of the last interval of the ans vector to extend the range accordingly ans.back()[1] = max(ans.back()[1], arr[i][1])
*/
vector<vector<int>> mergeIntervals(vector<vector<int>> &arr) {
    int n = arr.size(); // size of the array

    //sort the given intervals:
    sort(arr.begin(), arr.end());

    vector<vector<int>> ans;

    for (int i = 0; i < n; i++) {
        // if the current interval does not lie in the last interval:
        if (ans.empty() || arr[i][0] > ans.back()[1]) {
            ans.push_back(arr[i]);
        }
        // if the current interval lies in the last interval:
        else {
            ans.back()[1] = max(ans.back()[1], arr[i][1]);
        }
    }
    return ans;
}

/*
My Approach ->
Sort the array of intervals and use a temp vector to store the merged interval before pushing it to the result vector. The temp vector is initialised
with the first interval of the intervals array. Start the loop from index 1 to end and check whether the current interval can be merged with the temp 
interval. This can be checked by checking the current interval start i.e. interval[i][0] .. whether this lies between the temp interval start and end 
i.e. temp[0] <= interval[i][0] <= temp[1]. Now since the array is sorted then temp[0] <= interval[i][0] is always true. So we need to check only if
interval[i][0] <= temp[1], and if this is true then we can merge the interval by updating the temp interval end cosnidering the max of the temp 
interval end and current interval end i.e. temp[1] = max(temp[1], intervals[i][1]). Merge the overlapping intervals by updating the temp end till a 
non-overlapping interval is found. In that case add the temp vector to the result vector and update the temp vector with the current interval. 
Finally add the temp vector to the result vector after the loop ends. 
Ex-> consider the array intervals = [ [1,3], [1,5], [2,6], [7,9], [2,3] ]
After sorting the array we get -> [ [1,3], [1,5], [2,3], [2,6], [7,9] ]
Now temp vector is initialised with the first interval i.e. [1,3]
Start a loop from index 1 to end
for index 1 : Current interval = [1,5] __ temp = [1,3] since it overlaps we merge them by updating the temp vector ... it becomes temp = [1,5]
for index 2 : Current interval = [2,3] __ temp = [1,5] since it overlaps we merge them by updating the temp vector ... it becomes temp = [1,5]
for index 3 : Current interval = [2,6] __ temp = [1,5] since it overlaps we merge them by updating the temp vector ... it becomes temp = [1,6]
for index 4 : Current interval = [7,9] __ temp = [1,6] since it does not overlap we add the temp vector to the result vector and update the temp
Now the loop ends and after that we again add the temp vector to the result so result becomes [ [1,6], [7,9] ]
*/
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    int n = intervals.size();
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> res;
    vector<int> temp = {intervals[0][0], intervals[0][1]};
    for(int i=1; i<n; i++) {
        if(intervals[i][0] <= temp[1]) {
            temp[1] = max(temp[1], intervals[i][1]);
        }
        else {
            res.push_back(temp);
            temp = intervals[i];
        }
    }
    res.push_back(temp);
    return res;
}

int main() {
    vector<vector<int>> intervals = {{1,3},{2,6},{8,10},{15,18}};
    vector<vector<int>> merged_intervals = merge(intervals);
    for(vector<int> interval : merged_intervals) {
        for(int x : interval) cout << x << " ";
        cout << " __ ";
    }

    return 0;
}