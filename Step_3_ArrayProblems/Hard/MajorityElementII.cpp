/*
Leetcode - 229. Majority Element II : Medium

Given an integer array of size n, find all elements that appear more than ⌊n / 3⌋ times.

Examples :-

Input: nums = [3,2,3] __ Output: [3]

Input: nums = [1] __ Output: [1]

Input: nums = [1,2] __ Output: [1,2]

Constraints :-
• 1 <= nums.length <= 5 * 10^4
• -10^9 <= nums[i] <= 10^9

Follow up: Could you solve the problem in linear time and in O(1) space?
*/

#include <bits/stdc++.h>
using namespace std;

/*
>> Important observation — There can be at most 2 majority elements

Before solving the problem, there's one important observation:
| There can be at most two elements that appear more than \(n/3\) times.

-> Mathematical reasoning
Suppose there are 3 majority elements.
Each of them must appear more than `n/3` times, i.e. freq > n / 3.
Therefore, their combined frequency would be:
Total Frequency > (n/3 + n/3 + n/3) 
    => Total Frequency > n

But the total number of elements in the array is only n.
This is a contradiction!
Therefore, there can be at most 2 majority elements.

-> Easy way to understand
Imagine an array of 9 elements.
For an element to be a majority element, it must appear more than 3 times, meaning at least 4 times.
Could 3 different elements each appear at least 4 times?
That would require at least 12 positions, but we only have 9.
Hence, at most 2 majority elements are possible.
*/

// Brute Force Approach :- Time Complexity : O(n²) __ Space Complexity : O(1)
/*
>> Intuition — Brute Force (Nested Loops)

The simplest approach is to calculate the frequency of each element and check whether it appears more than n/3 times.

- Traverse the array and consider each element as a potential majority element.

- Before calculating its frequency, check whether it has already been processed. 
  We use ans.empty() || ans[0] != nums[i] for this.
    - If ans is empty, no majority element has been found yet, so we process the current element.
    - Otherwise, we process it only if it is different from ans[0].
    - This avoids recounting an element that has already been identified as a majority element. 
      For example, if 1 has already been added to ans, we skip subsequent occurrences of 1.

- If the element hasn't already been processed, traverse the entire array and count its occurrences.

- If its frequency is greater than n/3, add it to the answer.

- Since there can be at most two majority elements, we stop traversing as soon as ans.size() == 2.

Complexity:
- Time: O(n²) — for each element, we may traverse the entire array to calculate its frequency.
- Auxiliary space: O(1) — the answer vector can contain at most two elements.
*/
vector<int> majorityElement(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans;

    for(int i = 0; i < n; i++) {
        if(ans.empty() || ans[0] != nums[i]) {
            int cnt = 0;

            for(int j = 0; j < n; j++) {
                if(nums[j] == nums[i])
                    cnt++;
            }

            if(cnt > n/3)
                ans.push_back(nums[i]);
        }

        if(ans.size() == 2)
            break;
    }

    return ans;
}

// Better Approach (HashMap): Time Complexity : O(2n) __ Space Complexity : O(n)
/*
We can improve the brute-force approach by using a HashMap to store the frequency of every element.

>> Intuition
- Traverse the array and store the frequency of every element in a HashMap.
- Once the frequency map is ready, iterate through it.
- If an element's frequency is greater than n/3, add it to the answer.

>> Complexity
- Time: O(2n) on average — one traversal to build the map and another to iterate through it.
- Auxiliary space: O(n) — in the worst case, all elements are distinct.
*/
vector<int> majorityElementHashMap1(vector<int>& nums) {
    int n = nums.size();
    unordered_map<int, int> mpp;
    vector<int> ans;

    for (int num : nums)
        mpp[num]++;

    for (auto& [num, freq] : mpp) {
        if (freq > n/3) {
            ans.push_back(num);
        } 
    }

    return ans;
}

// Optimized HashMap Approach: Time Complexity : O(n) __ Space Complexity : O(n)
/*
>> Intuition
We know that an element must appear more than n/3 times to qualify as a majority element.
Therefore, the minimum frequency required is:
    threshold = floor(n / 3) + 1

Instead of waiting until the entire frequency map is constructed, 
we can check the frequency while traversing the array.
- Increment the frequency of the current element.
- Whenever its frequency reaches threshold, add it to the answer.
- Since an element can reach this threshold only once, 
  there is no need to check for duplicates or iterate through the map again.

>> Complexity
- Time: O(n) on average — only one traversal of the array.
- Auxiliary space: O(n) — HashMap storage.
*/
vector<int> majorityElementHashMap2(vector<int>& nums) {
    int n = nums.size();
    int threshold = n/3 + 1;

    unordered_map<int, int> mp;
    vector<int> ans;

    for(int num : nums) {
        mp[num]++;

        if(mp[num] == threshold)
            ans.push_back(num);

        if (ans.size() == 2)
            break;
    }

    return ans;
}

// Optimal Approach (Extended Moore's Voting Algorithm): Time Complexity : O(n) __ Space Complexity : O(1)
/*
>> Optimal — Extended Moore's Voting Algorithm

Let's recall the original Moore's Voting Algorithm used in Majority Element I.
When an element appears more than n/2 times, we can pair it against different elements and cancel those pairs. 
Since the majority element appears more than all other elements combined, it cannot be completely eliminated.

Now, here our threshold is n/3, and we have already established that there can be at most two majority elements.
This gives us the key idea:
We only need two candidates and their respective counts.

We use the following rules while traversing the array:
1. If the current element matches the first candidate, increment its count.
2. Else if it matches the second candidate, increment its count.
3. Else if the first candidate's count is zero, assign the current element as the first candidate.
4. Else if the second candidate's count is zero, assign the current element as the second candidate.
5. Otherwise, decrement both counts.

-> Why do we decrement both counts?
Think of it as cancelling a group of three different elements:
- One occurrence of the first candidate.
- One occurrence of the second candidate.
- The current element.
We eliminate all three because none of them gets an advantage from this group.

>> Important: We need a second traversal!
After the first traversal, the two candidates are only potential majority elements.
We must count their actual occurrences in the original array and 
verify whether their frequencies are greater than n/3.

>> Complexity
- Time: O(2n) — two traversals of the array, each taking linear time.
- Auxiliary space: O(1) — we only maintain two candidates and their counts.
*/
vector<int> majorityElement(vector<int>& nums) {
    int n = nums.size();
    
    int cnt1 = 0, cnt2 = 0;
    int el1 = 0, el2 = 0;

    // First pass: Find potential candidates
    for (int num : nums) {
        if (num == el1) cnt1++;
        else if (num == el2) cnt2++;
        else if (cnt1 == 0) {
            el1 = num;
            cnt1 = 1;
        }
        else if (cnt2 == 0) {
            el2 = num;
            cnt2 = 1;
        }
        else {
            cnt1--; cnt2--;
        }
    }

    vector<int> ans;

    // Second pass: Verify candidates
    cnt1 = 0, cnt2 = 0;

    for (int num : nums) {
        if (num == el1) cnt1++;
        else if (num == el2) cnt2++;
    }

    if (cnt1 > n/3) ans.push_back(el1);
    if (cnt2 > n/3) ans.push_back(el2);
    
    return ans;
}

int main() {
    return 0;
}