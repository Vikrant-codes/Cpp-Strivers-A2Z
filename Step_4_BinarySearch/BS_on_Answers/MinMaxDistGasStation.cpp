/*
GFG - Minimize Max Distance to Gas Station : Hard

We have a horizontal number line. On that number line, we have gas stations at positions stations[0], stations[1], ..., stations[n-1], 
where n is the size of the stations array. Now, we add k more gas stations so that d, the maximum distance between adjacent gas stations, 
is minimized. We have to find the smallest possible value of d. Find the answer exactly to 2 decimal places.

Note: stations is in a strictly increasing order.

Examples :-
Input : n = 10 __ stations[] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10] __ k = 9
Output: 0.50
Explanation: Each of the 9 stations can be added mid way between all the existing adjacent stations.

Input : n = 10 __ stations[] = [3, 6, 12, 19, 33, 44, 67, 72, 89, 95] __ k = 2 
Output: 14.00 
Explanation: Construction of gas stations at 8th(between 72 and 89) and 6th(between 44 and 67) locations.

Constraint : 10 <= n <= 10000 __ 0 <= stations[i] <= 10^9 __ 0 <= k <= 10^5
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach :- Time Complexity : O(n * k) __ Space Complexity : O(n-1) ~ O(n)
/*
We are given n gas stations. Between them, there are n-1 sections where we may insert the new stations to reduce the distance. 
So, we will create an array of size n-1 (vector<int> howMany) and each of its indexes will represent the respective sections b/w the given gas stations.
Like howMany[0] will tell the no of gas_stations placed in the section between stations[0] & stations[1].

We place 1 station at a time and iterate for k gas stations. We use greedy approach to find the maximum distance gas stations to know where to place 
the current gas_station. In each iteration, we will identify the index 'i' where the distance (stations[i+1] - stations[i]) is the maximum. 
Then, we will insert new stations into that section to reduce that maximum distance. 
The number of stations inserted in each section will be tracked using the previously declared array of size n-1. (howMany)
When we identify the maximum Distance section, we will insert the current gas station in that section and update the howMany array accordingly.
i.e. do howMany[maxInd]++ to know the number of gas stations placed in that section.

Finally, after placing all the stations we will find the maximum distance between two consecutive stations. 
To calculate the distance using the previously discussed formula, we will just do as follows for each section:
distance = section_length / (number_of_stations_ inserted+1)

Among all the values of ‘distance’, the maximum one will be our answer.

Complexity Analysis :-

Time Complexity : O(n * k) :- O(k*n) + O(n), n = size of the given array, k = no. of gas stations to be placed.
Reason: O(k*n) for each of the k gas_stations we run a O(n) loop to find the maximum distance section to insert that gas station.
Another O(n) for finding the answer i.e. the maximum distance.

Space Complexity: O(n) as we are using an array to keep track of placed gas stations. size of howMany = n-1 = O(n-1) ~ O(n)
*/

double minimiseMaxDistanceBrute(vector<int> &stations, int k) {
    int n = stations.size();
    vector<int> howMany(n - 1);

    for (int gas_station = 1; gas_station <= k; gas_station++) {
        double maxVal = -1;
        int maxInd = -1;
        for (int i=0; i < n-1; i++) {
            double dist = stations[i+1] - stations[i];
            double sectionLen = dist / (howMany[i] + 1);
            if (maxVal < sectionLen) {
                maxVal = sectionLen;
                maxInd = i;
            }
        }
        // cout << "Adding gas station between " << stations[maxInd] << " and " << stations[maxInd + 1] << endl;
        howMany[maxInd]++;
    }
    // for (int x : howMany) cout << x << " ";
    double ans = 0;
    for (int i=0; i<n-1; i++) {
        double dist = stations[i+1] - stations[i];
        double sectionLen = dist / (howMany[i] + 1);
        ans = max(ans, sectionLen);
    }

    return ans;
}

// Better Approach (Using Priority Queue) : Time Complexity : O(n log n) + O(k log n) __ Space Complexity : O(n-1) ~ O(n)
/*
Better Approach(Using Heap): 
In the previous approach, for every gas station, we were finding the index i for which the distance between arr[i+1] and arr[i] is maximum. 
After that, our job was to place the gas station. 
Instead of using a loop to find the maximum distance, we can simply use the heap data structure i.e. the priority queue.

Priority Queue: Priority queue internally uses the heap data structure. In the max heap implementation, 
the first element is always the greatest of the elements it contains and the rest elements are in decreasing order.

Thus using a priority queue, we can optimize the search for the maximum distance. We will use the max heap implementation and 
the elements will be in the form of pairs i.e. <distance, index> as we want the indices sorted based on the distance. 
As we are using max heap the maximum distance will always be the first element.

Firstly, we need to push all the initial section lengths and their start index into the priority_queue. 
Now we can easily get the maximum distance section to know where to place the gas station.

We run a loop for k gas stations and in each iteration, we get the maximum distance section in a pair named tp from the priority queue (using pq.top()). 
Remove this from the priority_queue (using pq.pop()) since we need to add the updated section length after placing the gas station.
Using tp.second we find the sectionIndex of the maximum distance section. 
Increment the count of gas_stations_placed in the howMany array using howMany[secInd]++ since we are now placing a new gas station in this section.
Now we find the updated section Length of the gas stations at using { stations[secInd+1] - stations[secInd] } / (howMany[secInd] + 1). 
Push this new section length along with its start index back into the priority_queue. 

After all the iteration ends, pq.top still contains the maximum section length after placing k gas stations and we get it as pq.top().first

Complexity Analysis

Time Complexity: O(nlogn + klogn),  n = size of the given array, k = no. of gas stations to be placed.
Reason: Insert operation of priority queue takes logn time complexity. O(nlogn) for inserting all the indices with distance values and 
O(klogn) for placing the gas stations.

Space Complexity: O(n-1)+O(n-1)
Reason: The first O(n-1) is for the array to keep track of placed gas stations and the second one is for the priority queue.
*/

double minimiseMaxDistanceBetter(vector<int> &stations, int k){
	int n = stations.size();
    vector<int> howMany(n-1, 0); 
    priority_queue<pair<double, int>> pq;   // pair {secLen, index} where secLen is the section length of section b/w index & index+1 of section array

    for (int i=0; i<n-1; i++) {
        double len = stations[i+1] - stations[i];
        pq.push({len, i});      // push section length along with start index of that section
    }

    for (int gas_station = 1; gas_station <= k; gas_station++) {
        auto tp = pq.top();         // topmost element of queue i.e. the one with maximum sectionLen
        pq.pop();                   // Remove the top element since placing the gas station will change this section length so new pair will be added
        int secInd = tp.second;     // index of the maximum distance section 
        howMany[secInd]++;    // increment the gas_stations_placed counter at the current secInd in howMany array since we are placing a new gas_station
        double iniDiff = stations[secInd + 1] - stations[secInd];   // initial difference between the two stations according to stations array
        double newSecLen = iniDiff / (double) (howMany[secInd] + 1);   // new section length after placing the gas station
        pq.push({newSecLen, secInd});    // push the new section length along with its start index back into the priority queue
    }

    return pq.top().first; // the topmost length will have the maximum section length after placing k stations
}

// Optimal Approach (Using Binary Search) : Time Complexity : O(n*log(Len)) + O(n) __ Space Complexity : O(1)
/*
We are going to use the Binary Search algorithm to optimize the approach.

The primary objective of the Binary Search algorithm is to efficiently determine the appropriate half to eliminate, 
thereby reducing the search space by half. It does this by determining a specific condition that ensures that the target is not present in that half.

Observations :-
Minimum possible answer: We will get the minimum answer when we place all the gas stations in a single location. 
Now, in this case, the maximum distance will be 0.
Maximum possible answer: We will not place stations before the first or after the last station rather we will place stations in between the 
existing stations. So, the maximum possible answer is the maximum distance between two consecutive existing stations.

From the observations, it is clear that our answer lies in the range [0, max(dist)].

The traditional binary search algorithm used for integer answer space won't be effective in this case. 
As our answer space consists of decimal numbers, we need to adjust some conditions to tailor the algorithm to this specific context. 
The changes are the following :-
1> while(low <= high): The condition 'while(low <= high)' inside the 'while' loop won't work for decimal answers, and using it might lead to a TLE error. 
To avoid this, we can modify the condition to 'while(high - low > 10^(-6))'. This means we will only check numbers up to the 6th decimal place. 
Any differences beyond this decimal precision won't be considered, as the question explicitly accepts answers within 10^-6 of the actual answer.
2> low = mid+1: We have used this operation to eliminate the left half. But if we apply the same here, we might ignore several decimal numbers 
and possibly our actual answer. So, we will use this: low = mid.
3> high = mid-1: Similarly, We have used this operation to eliminate the right half. But if we apply the same here, we might ignore several 
decimal numbers and possibly the actual answer. So, we will use this: high = mid.

We are applying binary search on the answer i.e. the possible values of distances. So, we have to figure out a way to check 
the number of gas stations we can place for a particular value of distance.
How to check the number of gas stations we can place with a particular distance ‘dist’ ? :- We use RequiredStations function for that
-> RequiredStations(vector<int> stations, double dist) :-
For each section between two adjacent stations we check how many gas stations are required to ensure that the distance between any two 
adjacent stations is at most ‘dist’. To do so we find the gap between the two stations and divide it by ‘dist’ to get the number of 
additional stations needed. Now this gap/dist is not necessarily an integer but we only take the integer value. 
But assume for conditions when gap is completely divisible by dist like for section between stations [1,3], gap = 2 and let's say dist = 0.5 
then gap / dist = 2 / 0.5 = 4. But do we actually need 4 stations to maintain the minimum distance dist between stations ? 'NO'
as we can place stations at [1] [1.5, 2, 2.5] [3] so we need only 3 stations. This is becuase gap was totally divisiible by dist and 
thus the 4th placed station is overlapping on the already placed station. 
So, for conditions when dist evenly divides gap we need to decrement 1 from required stations. To do so we add ceil(gap / dist) - 1 to required_count 
since if it doesn't evenly divides ceil will take the upper integer value then -1 or else if it evenly divides it will -1. 

Complexity Analysis

Time Complexity: O(n*log(Len)) + O(n), n = size of the given array, Len = length of the answer space.
Reason: We are applying binary search on the answer space. 
For every possible answer, we are calling the function RequiredStations() that takes O(n) time complexity. 
And another O(n) for finding the maximum distance initially.

Space Complexity: O(1) as we are using no extra space to solve this problem.
*/

int RequiredStations(vector<int> stations, double dist) {
    int cnt = 0;
    int n = stations.size();
    for (int i=0; i<n-1; i++) {
        double gap = stations[i+1] - stations[i];
        cnt += ceil(gap / dist) - 1; 
    }
    return cnt;
}
  
double minMaxDist(vector<int> &stations, int K) {
    int n = stations.size();
    double low = 0, high = 0;

    for (int i=0; i<n-1; i++) {
        high = max (high, (double) (stations[i+1] - stations[i]) );
    }
        
    double diff = 1e-6;         // use 1e-6 for higher precision when upto 6 decimal places is required
    // for gfg problem using 1e-3 is enough since only 2 decimal places is required
        
    while (high - low > diff) {
        double mid = (low + high)/2.0;
        int cnt = RequiredStations(stations, mid);
            
        if (cnt > K) low = mid;
        else high = mid;
    }
        
    return high;
}



int main() {
    vector<int> stations = {3, 6, 12, 19, 33, 44, 67, 72, 89, 95};
    int k = 2;

    double ans = minMaxDist(stations, k);
    cout << "Smallest Maximum Distance after placing the gas stations : " << ans << endl;

    return 0;
}