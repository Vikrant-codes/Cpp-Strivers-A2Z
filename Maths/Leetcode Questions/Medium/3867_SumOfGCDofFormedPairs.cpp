/*
Leetcode - 3867. Sum of GCD of Formed Pairs : Medium

You are given an integer array nums of length n.

Construct an array prefixGcd where for each index i:
• Let mxi = max(nums[0], nums[1], ..., nums[i]).
• prefixGcd[i] = gcd(nums[i], mxi).

After constructing prefixGcd:
• Sort prefixGcd in non-decreasing order.
• Form pairs by taking the smallest unpaired element and the largest unpaired element.
• Repeat this process until no more pairs can be formed.
• For each formed pair, compute the gcd of the two elements.
• If n is odd, the middle element in the prefixGcd array remains unpaired and should be ignored.

Return an integer denoting the sum of the GCD values of all formed pairs.

The term gcd(a, b) denotes the greatest common divisor of a and b.

Examples :-

Input: nums = [2,6,4]
Output: 2
Explanation:
Construct prefixGcd:
i	nums[i]	mxi	prefixGcd[i]
0	2	2	2
1	6	6	6
2	4	6	2
prefixGcd = [2, 6, 2]. After sorting, it forms [2, 2, 6].
Pair the smallest and largest elements: gcd(2, 6) = 2. The remaining middle element 2 is ignored. Thus, the sum is 2.

Input: nums = [3,6,2,8]
Output: 5
Explanation:
Construct prefixGcd:
i	nums[i]	mxi	prefixGcd[i]
0	3	3	3
1	6	6	6
2	2	6	2
3	8	8	8
prefixGcd = [3, 6, 2, 8]. After sorting, it forms [2, 3, 6, 8].
Form pairs: gcd(2, 8) = 2 and gcd(3, 6) = 3. Thus, the sum is 2 + 3 = 5.

Constraints :-
• 1 <= n == nums.length <= 10^5
• 1 <= nums[i] <= 10​​​​​​​^9
*/

#include <bits/stdc++.h>
using namespace std;

// Simulation approach : Time Complexity : O(n * logϕ(min)) + O(n log n) + O(n * logϕ(min) / 2) __ Space Complexity : O(n)
/*
Approach :-
• Build prefixGCD array 
    • Maintain a running prefix maximum and compute GCD(current element, maximum)
    • Add that GCD to the prefixGCD array
• Sort the prefixGCD array
• Iterate two pointers one from each end to get the pairs of smallest & largest unpaired element, and get their GCD.
• Add this GCD of pair elements to the answer sum

>> Time Complexity Analysis :
- Helper Method GCD : O(logϕ(min(a, b))), where ϕ = golden ratio
- Building prefixGCD array : 
    - for each element 'x' of nums (n elements), we compute GCD(x, max_val), where max_val = max. value till current element
    - This takes O(n * logϕ(min)), where "min" refers to the smaller of the two numbers in each GCD computation.
- Sorting the prefixGCD array : O(n log n)
- Pairing & computing GCD using two pointers : O(n / 2) pairs * O(logϕ(min)) = O(n * logϕ(min) / 2)

-> Total Time Complexity : O(n * logϕ(min)) + O(n log n) + O(n * logϕ(min) / 2)

>> Space Complexity : 
We are using extra space to build prefixGCD array, this will be of size n, so O(n).
*/

// helper method to get the GCD of two elements (we can also use the inbuilt gcd() method)
// Time Complexity of GCD() method : O( log Φ (min(a, b)) )
int GCD(int a, int b) {
    int rem = b % a;

    while (rem != 0) {
        b = a;
        a = rem;
        rem = b % a;
    }

    return a;
}
    
// O(n * log Φ (mn)) + O(n * log n) + O(n * log Φ (mn) / 2)
long long gcdSum(vector<int>& nums) {
    vector<int> prefixGCD;

    // build prefixGCD by maintaining a running prefix maximum and computing GCD(current elemnet, maximum)
    int mx = nums[0];
    for (int& x : nums) {
        mx = max(mx, x);
        prefixGCD.push_back(GCD(x, mx));
    }

    // sort the prefixGCD vector
    sort(prefixGCD.begin(), prefixGCD.end());
    
    // move two pointers one from each end, and for each pair elements, find their GCD and add it to answer sum
    long long sum = 0;
    int i = 0, j = prefixGCD.size()-1;
    while (i < j) {
        sum = sum + GCD(prefixGCD[i], prefixGCD[j]);
        
        i++; j--;
    }

    return sum;
}

int main() {
    return 0;
}