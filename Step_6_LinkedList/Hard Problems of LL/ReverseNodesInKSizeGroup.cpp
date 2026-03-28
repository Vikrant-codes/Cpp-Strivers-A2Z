/*
Leetcode - 25. Reverse Nodes in k-Group : Hard

Given the head of a linked list, reverse the nodes of the list k at a time, and return the modified list.
k is a positive integer and is less than or equal to the length of the linked list. 
If the number of nodes is not a multiple of k then left-out nodes, in the end, should remain as it is.
You may not alter the values in the list's nodes, only nodes themselves may be changed.

Examples :-

Input: head = [1,2,3,4,5], k = 2
Output: [2,1,4,3,5]

Input: head = [1,2,3,4,5], k = 3
Output: [3,2,1,4,5]

Constraints :-
- The number of nodes in the list is n.
- 1 <= k <= n <= 5000
- 0 <= Node.val <= 1000

Follow-up: Can you solve the problem in O(1) extra memory space?
*/

#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Naive Approach : Time Complexity : O(n + n + n) __ Space Complexity : O(n)
/*
Approach :-
1. Traverse the linked list and store its data in a vector
2. Reverse the vector's data in k-size groups
3. Traverse the linked list again and re-write the data of the nodes according to the reversed data in vector

>> How are we reversing the vector's data in k-size groups ?
    for(int i = 0; i + k <= data.size(); i += k) {
        reverse(data.begin() + i, data.begin() + i + k);
    }
Step-by-step:
1. Start from index i = 0
    • This is the beginning of the first group
2. Check condition i + k <= data.size()
    • Ensures a full group of size k exists
    • If not, we stop (last partial group is ignored)
3. Reverse current group
    • data.begin() + i → start of group
    • data.begin() + i + k → end of group (k-size group)
    • reverse(...) reverses elements in range [i, i+k-1] (reverses elements in the current k-sized window)
4. Move to next group
    • i += k → jump directly to next block of size k

✅ Key Idea:
• Treat vector like blocks of size k
• Reverse each block independently
• Skip incomplete blocks at the end
*/
ListNode* reverseKGroupNaive(ListNode* head, int k) {
    vector<int> data;
    ListNode* curr = head;
    while (curr) {
        data.push_back(curr->val);
        curr = curr->next;
    }

    for(int i = 0; i+k <= data.size(); i+=k) {
        reverse(data.begin()+i, data.begin()+i+k);
    }

    curr = head;
    for (int x : data) {
        curr->val = x;
        curr = curr->next;
    }

    return head;
}



int main() {
    return 0;
}