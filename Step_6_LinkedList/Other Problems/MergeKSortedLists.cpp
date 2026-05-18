/*
Leetcode - 23. Merge k Sorted Lists : Hard

You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
Merge all the linked-lists into one sorted linked-list and return it.

Examples :-

Input: lists = [[1,4,5],[1,3,4],[2,6]] __ Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted linked list:
1->1->2->3->4->4->5->6

Input: lists = [] __ Output: []

Input: lists = [[]] __ Output: []

Constraints :-
• k == lists.length
• 0 <= k <= 10^4
• 0 <= lists[i].length <= 500
• -10^4 <= lists[i][j] <= 10^4
• lists[i] is sorted in ascending order.
• The sum of lists[i].length will not exceed 10^4.
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

// Naive Approach : Time Complexity : O(N log N) __ Space Complexity : O(1)
/*
>> Intuition
Each linked list is already sorted, but handling multiple linked lists together directly can feel complicated.
A simpler observation is:
If we collect all node values into one container, then after sorting those values, 
we can rebuild the final sorted linked list easily.
So instead of merging lists one by one, this approach treats the problem like:
- Extract all elements
- Sort them
- Build a new sorted linked list

>> Step-by-step Idea
1. Store all node values in an array
- Traverse every linked list and push each node’s value into a vector.
        for (ListNode* curr : lists)
    Here, curr points to the head of one linked list.
- Then:
        while (temp)
    visits every node of that list and stores its value.
    After this step: lists = [1->4->5, 1->3->4, 2->6], arr = [1,4,5,1,3,4,2,6]

2. Sort the array
- Now all values are present in a single array.
    sort(arr.begin(), arr.end());
- After sorting: arr = [1,1,2,3,4,4,5,6]
- At this point, the linked-list structure no longer matters because the ordering is already correct.

3. Create the final linked list
- Use the sorted array to build a brand-new linked list.
- A dummy node is used to simplify insertion.
    ListNode* dummy = new ListNode(-1);
- Then for every value:
        t->next = new ListNode(x);
    attach a new node and move forward.
- Finally:
        return dummy->next;
    because dummy itself is just a helper node.

>> Complexity Analysis
Let: N = total number of nodes across all linked lists
-> Time Complexity
    Traversing all lists: O(N)
    Sorting array: O(N log N)
    Building final list: O(N)
Overall: O(N log N)

-> Space Complexity
    Array stores all node values → O(N)
    New linked list nodes → O(N)
Extra auxiliary space: O(N)
*/
ListNode* mergeKLists(vector<ListNode*>& lists) {
    vector<int> arr;

    // Step-1 : store the linked list data elements in an array
    for (ListNode* curr : lists) {
        ListNode* temp = curr;
        while (temp) {
            arr.push_back(temp->val);
            temp = temp->next;
        }
    }

    // Step-2 : sort the array
    sort(arr.begin(), arr.end());
    
    // Step-3 : Create a new linked list with the sorted data and return its head
    ListNode* dummy = new ListNode(-1);
    ListNode* t = dummy;
    for (int x : arr) {
        ListNode* newNode = new ListNode(x);
        t->next = newNode;
        t = t->next;
    }

    return dummy->next;
}

int main() {

    return 0;
}