/*
Leetcode - 148. Sort List : Medium

Given the head of a linked list, return the list after sorting it in ascending order.

Examples :-
Input: head = [4,2,1,3] __ Output: [1,2,3,4]
Input: head = [-1,5,3,4,0] __ Output: [-1,0,3,4,5]
Input: head = [] __ Output: []

Constraints :-
• The number of nodes in the list is in the range [0, 5 * 10^4].
• -10^5 <= Node.val <= 10^5
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

// Naive Approach : Time Complexity : O(n) + O(n log n) + O(n) __ Space Complexity : O(n)
/*
Naive Approach - We want to sort the linked list in ascending order. We can achieve so by sorting its data.
- Use an array to store the data of linked list nodes
- Sort the array
- Traverse the linked list and replace its data according to the sorted array data.
*/
ListNode* sortListNaive(ListNode* head) {
    vector<int> data;

    ListNode* curr = head;
    while (curr) {
        data.push_back(curr->val);
        curr = curr->next;
    }

    sort(data.begin(), data.end());
        
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