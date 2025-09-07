/*
Leetcode - 997. Find the Town Judge : Easy

In a town, there are n people labeled from 1 to n. There is a rumor that one of these people is secretly the town judge.

If the town judge exists, then:

The town judge trusts nobody.
Everybody (except for the town judge) trusts the town judge.
There is exactly one person that satisfies properties 1 and 2.
You are given an array trust where trust[i] = [ai, bi] representing that the person labeled ai trusts the person labeled bi. If a trust relationship does not exist in trust array, then such a trust relationship does not exist.

Return the label of the town judge if the town judge exists and can be identified, or return -1 otherwise.

 

Example 1:

Input: n = 2, trust = [[1,2]]
Output: 2
Example 2:

Input: n = 3, trust = [[1,3],[2,3]]
Output: 3
Example 3:

Input: n = 3, trust = [[1,3],[2,3],[3,1]]
Output: -1
 

Constraints:

1 <= n <= 1000
0 <= trust.length <= 104
trust[i].length == 2
All the pairs of trust are unique.
ai != bi
1 <= ai, bi <= n
*/

#include <bits/stdc++.h>
using namespace std;

int findJudge(int n, vector<vector<int>>& trust) {
    vector<int> trusted_by(n, 0); // keeps cnt of no of people that trust i+1 th person
    vector<int> do_trust(n, 0); // keeps cnt of no of people trusted by i+1 th person

    for (auto x : trust){
        trusted_by[x[1]-1]++;
        do_trust[x[0]-1]++;
    }

    for (int i=0; i<n; i++) {
        if (trusted_by[i] == n-1 && do_trust[i] == 0) return i+1;
    }

    return -1;
}

int main() {
    vector<vector<int>> trust = {{1,3},{2,3}};
    int n = 3;
    int judge = findJudge(n, trust);
    cout << "The town judge is: " << judge << endl;

    return 0;
}