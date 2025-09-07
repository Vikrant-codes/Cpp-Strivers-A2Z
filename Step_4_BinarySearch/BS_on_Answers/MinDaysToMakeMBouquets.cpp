/*
Leetcode - 1482. Minimum Number of Days to Make m Bouquets -- Medium

You are given an integer array bloomDay, an integer m and an integer k.
You want to make m bouquets. To make a bouquet, you need to use k adjacent flowers from the garden.
The garden consists of n flowers, the ith flower will bloom in the bloomDay[i] and then can be used in exactly one bouquet.
Return the minimum number of days you need to wait to be able to make m bouquets from the garden. 
If it is impossible to make m bouquets return -1.

Examples :- 

Input: bloomDay = [1,10,3,10,2], m = 3, k = 1 __ Output: 3
Explanation: Let us see what happened in the first three days. x means flower bloomed and _ means flower did not bloom in the garden.
We need 3 bouquets each should contain 1 flower.
After day 1: [x, _, _, _, _]   // we can only make one bouquet.
After day 2: [x, _, _, _, x]   // we can only make two bouquets.
After day 3: [x, _, x, _, x]   // we can make 3 bouquets. The answer is 3.

Input: bloomDay = [1,10,3,10,2], m = 3, k = 2 __ Output: -1
Explanation: We need 3 bouquets each has 2 flowers, that means we need 6 flowers. We only have 5 flowers so it is impossible to get the 
needed bouquets and we return -1.

Input: bloomDay = [7,7,7,7,12,7,7], m = 2, k = 3 __ Output: 12
Explanation: We need 2 bouquets each should have 3 flowers.
Here is the garden after the 7 and 12 days:
After day 7: [x, x, x, x, _, x, x]
We can make one bouquet of the first three flowers that bloomed. We cannot make another bouquet from the last three flowers that bloomed 
because they are not adjacent.
After day 12: [x, x, x, x, x, x, x]
It is obvious that we can make two bouquets in different ways.


Constraints :-
bloomDay.length == n
1 <= n <= 10^5
1 <= bloomDay[i] <= 10^9
1 <= m <= 10^6
1 <= k <= n
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach: Binary Search on Answers
// Time Complexity: O(n * log(max(bloomDay))) where n is the size of bloomDay array and max(bloomDay) is the maximum bloom day.

/*
Approach :- 
1. We need to find the minimum number of days required to make m bouquets, each containing k adjacent flowers.
2. We can use binary search to find the minimum number of days. 
3. All the flowers will be bloomed by a certain day that is max(bloomDay). Since by then all flowers will be bloomed, 
so we can start our binary search from 1 to max(bloomDay).
4. There could be situations where it is impossible to make m bouquets. Such situations includes cases when the total no. of flowers required to 
make m bouquets is more than the total number of flowers available in the garden i.e. the length of bloomDay. 
5. We can calculate the total no. of flowers required to make m bouqets of k flowers each by doing m * k. But while doing this multiplication, we 
need to be careful about integer overflow, so we use long long and cast the multiplication to long long by multiplying with 1LL. 
6. In the search space [1, [max(bloomDay)]], we take mid value and check the feasibility of making m bouquets in mid days. 
7. If it is possible, then we try to find the smaller no. of days by moving the high pointer to mid - 1. 
8. If making m bouquets is not possible in mid days, then we move the low pointer to mid + 1.
9. Return low as the answer, which will be the minimum number of days required to make m bouquets.

--> How to check if we can make m bouquets in mid days ? 
The function canMakeBouquets is used to check the feasility of making m bouquets in mid days.

We can only use adjacent flowers to make a bouquet. Also in each bouquet we need k flowers. So if making bouquets is possible on mid days, then 
we need m groups of k adjacent flowers. 

We keep a bouquets counter and a count of adjacent flowers. While iterating through the bloomDay array, we check if the flower has bloomed by 'mid' days
by checking if bloomDay[i] <= mid (since bloomDay[i] is the day on which the ith flower blooms). If it has bloomed, we increment the count of adjacent 
flowers. Else reset count to 0 since the adjaceny is broken. While counting the adjacent flowers, if count becomes equal to k, we increment the 
bouquets counter and reset the adjacent_count to 0. At the end of iteration, if the bouquets that can be made is >= m then we return true, else false. 


--> Complexity Analysis :-
Time Complexity: O(n * log(max(bloomDay))) where n is the size of bloomDay array and max(bloomDay) is the maximum bloom day.
O(n) is for checking the feasibilty of making m bouquets in mid days i.e. canMakeBouquets function and
log(max(bloomDay)) is for the binary search on the number of days. So the overall time complexity is O(n * log(max(bloomDay))).
*/

int findMax(vector<int>& bloomDay) {
    int mx = 0;
    for(int day : bloomDay) mx = max(mx, day);
    return mx;
}

// Time Complexity : O(n)
bool canMakeBouquets(vector<int>& bloomDay, int m, int k, int days) {
    int bouquets = 0, cnt = 0;   // cnt is used to count the number of adjacent flowers that have bloomed by 'days'
    for(int x : bloomDay) {
        if (x <= days) cnt++;
        else cnt = 0;

        if (cnt == k) {
            bouquets++;
            cnt = 0;
        }
    }
   return bouquets >= m;
}

bool canMakeBouquetsStriver(vector<int>& bloomDay, int m, int k, int days) {
    int bouquets = 0, cnt = 0;
    for(int x : bloomDay) {
        if (x <= days) cnt++;
        else {
            bouquets += cnt / k;    // count how many bouquets can be made with 'cnt' adjacent flowers
            cnt = 0;        // Reset counter
        }
    }
    bouquets += cnt / k;
    return bouquets >= m;
}

int minDays(vector<int>& bloomDay, int m, int k) {
    int n = bloomDay.size();

    // flowers_required to make m bouquets of k flower each ... To make m bouquets of k flower each, we need m*k flowers
    long long flowers_required = 1LL * m * k;    // 1LL is used to make the multiplication safe from overflow by casting to long long
        
    if (flowers_required > n) return -1;         // If flowers required is more than total flowers then its impossible to make bouquets so return -1

    int low = 1;
    int high = findMax(bloomDay);
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (canMakeBouquets(bloomDay, m, k, mid)) high = mid - 1;
        else low = mid + 1;
    }
    return low;
}

int main() {
    vector<int> bloomDay = {7,7,7,7,12,7,7};
    int m = 2, k = 3;
    int result = minDays(bloomDay, m, k);
    int mx = findMax(bloomDay);
    cout << "Maximum bloom day: " << mx << endl;
    bool canMake = canMakeBouquets(bloomDay, m, k, mx);
    cout << canMake << endl;
    cout << "Minimum days to make " << m << " bouquets: " << result << endl;
}