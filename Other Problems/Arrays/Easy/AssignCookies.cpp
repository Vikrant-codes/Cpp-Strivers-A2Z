/*
Leetcode - 455. Assign Cookies

Assume you are an awesome parent and want to give your children some cookies. 
But, you should give each child at most one cookie.
Each child i has a greed factor g[i], which is the minimum size of a cookie that the child will be content with; 
and each cookie j has a size s[j]. 
If s[j] >= g[i], we can assign the cookie j to the child i, and the child i will be content. 
Your goal is to maximize the number of your content children and output the maximum number.

Examples :-

Input: g = [1,2,3], s = [1,1] __ Output: 1
Explanation: You have 3 children and 2 cookies. The greed factors of 3 children are 1, 2, 3. 
And even though you have 2 cookies, since their size is both 1, you could only make the child whose greed factor is 1 content.
You need to output 1.

Input: g = [1,2], s = [1,2,3] __ Output: 2
Explanation: You have 2 children and 3 cookies. The greed factors of 2 children are 1, 2. 
You have 3 cookies and their sizes are big enough to gratify all of the children, 
You need to output 2.

*/

#include<bits/stdc++.h>
using namespace std;

// Two Pointer Approach (Greedy) :- Time Complexity : O(n log n + m log m) + O(n + m) __ Space Complexity : O(1)
/*
We can sort the arrays and start selecting the smallest greed kids and smallest size cookies to see 
if the child can be satisfied with it. 
If the child can be satisfied we move to the next cookie as well as next child and increment the count of content kids.
If child can't be satisfied with current cookie we then check for next cookie.
This loop will end when either there are no cookies left or there are no children left.

🔍 Intuition
1. Both lists are sorted (smallest greed and smallest cookie first).
2. For each cookie:
- If it can satisfy the current child (s[j] >= g[i]), assign it and move to next child. Increment the content child count.
- Otherwise, try next larger cookie.
3. Continue until either children or cookies run out.
4. Return the count of the content child after the loop terminates.
*/
int findContentChildren(vector<int>& g, vector<int>& s) {
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());
    int i = 0, j = 0, cnt = 0;

    while (i < g.size() && j < s.size()) {
        if (s[j] >= g[i]) { // cookie can satisfy child
            cnt++;
            i++;             // move to next child
        }
        j++;                 // always move to next cookie
    }
    return cnt;
}


int main() {

    return 0;
}