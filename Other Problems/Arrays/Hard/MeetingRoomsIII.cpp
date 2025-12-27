/*
Leetcode - 2402. Meeting Rooms III : Hard

You are given an integer n. There are n rooms numbered from 0 to n - 1.

You are given a 2D integer array meetings where meetings[i] = [starti, endi] 
means that a meeting will be held during the half-closed time interval [starti, endi). 
All the values of starti are unique.

Meetings are allocated to rooms in the following manner:
1. Each meeting will take place in the unused room with the lowest number.
2. If there are no available rooms, the meeting will be delayed until a room becomes free. 
   The delayed meeting should have the same duration as the original meeting.
3. When a room becomes unused, meetings that have an earlier original start time should be given the room.

Return the number of the room that held the most meetings. 
If there are multiple rooms, return the room with the lowest number.

A half-closed interval [a, b) is the interval between a and b including a and not including b.

Examples :-

Input: n = 2, meetings = [[0,10],[1,5],[2,7],[3,4]]
Output: 0
Explanation:
- At time 0, both rooms are not being used. The first meeting starts in room 0.
- At time 1, only room 1 is not being used. The second meeting starts in room 1.
- At time 2, both rooms are being used. The third meeting is delayed.
- At time 3, both rooms are being used. The fourth meeting is delayed.
- At time 5, the meeting in room 1 finishes. The third meeting starts in room 1 for the time period [5,10).
- At time 10, the meetings in both rooms finish. The fourth meeting starts in room 0 for the time period [10,11).
Both rooms 0 and 1 held 2 meetings, so we return 0. 

Input: n = 3, meetings = [[1,20],[2,10],[3,5],[4,9],[6,8]]
Output: 1
Explanation:
- At time 1, all three rooms are not being used. The first meeting starts in room 0.
- At time 2, rooms 1 and 2 are not being used. The second meeting starts in room 1.
- At time 3, only room 2 is not being used. The third meeting starts in room 2.
- At time 4, all three rooms are being used. The fourth meeting is delayed.
- At time 5, the meeting in room 2 finishes. The fourth meeting starts in room 2 for the time period [5,10).
- At time 6, all three rooms are being used. The fifth meeting is delayed.
- At time 10, the meetings in rooms 1 and 2 finish. The fifth meeting starts in room 1 for the time period [10,12).
Room 0 held 1 meeting while rooms 1 and 2 each held 2 meetings, so we return 1. 
 
Constraints :-
- 1 <= n <= 100
- 1 <= meetings.length <= 10^5
- meetings[i].length == 2
- 0 <= starti < endi <= 5 * 10^5
- All the values of starti are unique.
*/

#include <bits/stdc++.h>
using namespace std;

// Simulation-based greedy approach : Time Complexity : O(m * log m + m * n) __ Space Complexity : O(n)
/* ⚠️ This approach is not correct apparently. The correct approach uses min-heaps. ⚠️ */
/*
✨🤔 High-level idea (intuition)
We are simulating the meeting process in time order and trying to:
    • Assign a meeting to any room that is free at the current time
    • If no room is free, delay the meeting and assign it to the room that gets free the earliest
    • Track how many meetings each room handles
    • Return the room with the maximum count
This solution is a simulation-based greedy approach.

-- Code Explanation --

Key data structures (what each variable means)
>> meetings
• Sorted by start time
• Ensures meetings are processed chronologically

>> mtRoom[i]
• Stores when room i will become free
• 0 means the room has never been used (free initially)

>> cnt[i]
• Number of meetings assigned to each ith room 

>> time
• Represents the current simulated time
• We try to keep it aligned with meeting start times

✨ Step-by-step intuition 

1. Sort meetings : sort(meetings.begin(), meetings.end());
Why?
Meetings must be handled in increasing order of start time.

2. Initialize tracking arrays
• cnt[i] → meeting count per room
• mtRoom[i] → next free time of room i

3. Process each meeting : for (auto& mt : meetings)
Each mt = [start, end]

4. Sync simulation time with meeting start : if (time < mt[0]) time = mt[0];
Intuition: We cannot start processing a meeting before it starts, so we move time forward if needed.

5. Try to assign a free room
    for (int i = 0; i < n; i++) {
        if (mtRoom[i] == 0 || mtRoom[i] <= time) {
            mtRoom[i] = time + (mt[1] - mt[0]);
            cnt[i]++;
            alloted = true;
            break;
        }
    }
What this does:
• Scan rooms from 0 → n-1
• Assign the first available room
• Update its next free time
• Increment its meeting count

Greedy choice: Lower-index room gets priority when multiple rooms are free.

6. Delay allocation if no room was free : if (!alloted) delayAllot(mt, mtRoom, cnt, time);
Intuition of delayAllot
Idea : Find the room that gets free earliest.
    int ind = 0;
    for (int i = 1; i < mtRoom.size(); i++)
        if (mtRoom[i] < mtRoom[ind])
            ind = i;
    time = mtRoom[ind];
    mtRoom[ind] = time + (mt[1] - mt[0]);
    cnt[ind]++;

What happens :
• Delay the meeting until that room is free
• Schedule it immediately afterward
• Increment that room’s count

7. Final answer : return index of room with max cnt. If counts tie, the smallest index wins naturally.

✓ Complexity Analysis 

→ Time Complexity
Sorting meetings: O(m log m)
For each meeting:
• Room scan: O(n)
• Delay scan: O(n)
Total: O(m * log m + m * n)

→ Space Complexity
• cnt → O(n)
• mtRoom → O(n)
Total: O(n)
*/

void delayAllot(vector<int>& mt, vector<long long>& mtRoom, vector<int>& cnt, long long time) {
    int ind = 0;
    for (int i = 1; i < mtRoom.size(); i++)
        if (mtRoom[i] < mtRoom[ind])
            ind = i;
    time = mtRoom[ind];
    mtRoom[ind] = time + (mt[1] - mt[0]);
    cnt[ind]++;
}

int mostBooked(int n, vector<vector<int>>& meetings) {
    if (n == 1) return 0;
    sort(meetings.begin(), meetings.end());

    long long time = 0;
    vector<int> cnt(n);
    vector<long long> mtRoom(n);

    for (auto& mt : meetings) {
        bool alloted = false;
        if (time < mt[0]) time = mt[0];
        for (int i = 0; i < n; i++) {
            if ( !alloted && (mtRoom[i] == 0 || mtRoom[i] <= time) ) {
                mtRoom[i] = time + mt[1] - mt[0];
                cnt[i]++;
                alloted = true;
                break;
            }
        }
        time++;
        if (!alloted) delayAllot(mt, mtRoom, cnt, time);
    }

    int ind = 0;
    for (int i = 1; i < cnt.size(); i++) {
        if (cnt[i] > cnt[ind]) ind = i;
    }
    return ind;
}

int main() {
    return 0;
}