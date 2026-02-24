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
    // Step-1 extract data from nodes
    ListNode* curr = head;
    while (curr) {
        data.push_back(curr->val);
        curr = curr->next;
    }
    // Step-2 sort the data
    sort(data.begin(), data.end());
    // Step-3 re-write nodes data according to sorted data
    curr = head;
    for (int x : data) {
        curr->val = x;
        curr = curr->next;
    }
    return head;
}

// Optimal Approach (Merge Sort) : Time Complexity : O(log n * (n + n/2)) ~ O(n log n) __ Space Complexity : O(1)
/*
This is Merge Sort on a linked list. It is divide → sort → merge

Step 1️⃣ Divide the list into two halves
- Use slow & fast pointer to find middle.
- Cut the list into: Left half & Right half
- Example: 4 → 2 → 1 → 3, Becomes: 4 → 2 (left half)     1 → 3 (right half)

Step 2️⃣ Recursively sort both halves
- Now sortList() is called on both halves.
- Each half again gets divided:
    4 → 2                       1 → 3
    ↓                           ↓
    4    2                      1    3
- Recursion stops when list has: 0 node OR 1 node (Because single node is already sorted)

Step 3️⃣ Merge two sorted halves.
( We already know how to merge two sorted lists (see MergeTwoSortedLists.cpp) )
- Now merging starts bottom-up.
4 & 2 becomes: 2 → 4, 1 & 3 becomes: 1 → 3
Then final merge: 2 → 4 & 1 → 3 Becomes: 1 → 2 → 3 → 4

<-- Recursion Tree Diagram -->
Recursion tree for: 4 → 2 → 1 → 3

🌳 Recursion Tree (Top → Down Splitting)
            4 → 2 → 1 → 3
           /               \
    4 → 2                     1 → 3
   /     \                   /     \
 4        2                 1       3
👉 Splitting continues until single nodes.

🔼 Now Merging Starts (Bottom → Up)

Step 1: Merge single nodes
4   2   →   2 → 4
1   3   →   1 → 3
Tree becomes:
        4 → 2 → 1 → 3
       /               \
  2 → 4               1 → 3

Step 2: Final Merge
Merge: 2 → 4 (left half) and 1 → 3 (right half)
Result: 1 → 2 → 3 → 4

 4        2                1       3
   \     /                  \     /
    2 → 4                    1 → 3
           \               /
            1 → 2 → 3 → 4

🔎 What to Notice
- Splitting happens top-down
- Merging happens bottom-up
- Every level processes all n nodes
- Total levels = log n
That’s why: Time = n × log n

✅ Time Complexity
- At each level of recursion:
    We split the list → O(n/2) (to find middle)
    We merge two halves → O(n)
So per level work = O(n + n/2)

How many levels?
Each time we divide list into half
So number of levels = log n

Therefore: T(n) = O(n + n/2) × O(log n) = O(log n * (n + n/2)) ~ O(n log n) , since n + n/2 ~ n

✅ Space Complexity

1️⃣ Auxiliary (Extra) Space Used Explicitly
- No extra array
- Only few pointers
So auxiliary space = O(1)

2️⃣ Recursive Stack Space
- Each recursive call splits list into half.
- Depth of recursion: log n
- At each level, only constant memory is used.
So recursive stack space: O(logn)
*/

// findMiddle returns the middle node of the linked list (first middle in case of even length linked lists)
ListNode* findMiddle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

// merge two sorted linked lists (helps to merge the left half & right half)
ListNode* merge(ListNode* head1, ListNode* head2) {
    ListNode *t1 = head1, *t2 = head2;
    ListNode *dummy = new ListNode(-1);
    ListNode *temp = dummy;

    while (t1 && t2) {
        if (t1->val <= t2->val) {
            temp->next = t1;
            t1 = t1->next;
        }
        else {
            temp->next = t2;
            t2 = t2->next;
        }
        temp = temp->next;
    }
    if (t1) temp->next = t1;
    if (t2) temp->next = t2;

    return dummy->next;
}

// actual mergeSort code
ListNode* sortList(ListNode* head) {
    if (head == NULL || head->next == NULL)
        return head;

    // find the middle (first middle for even length) 
    ListNode* mid = findMiddle(head);
        
    ListNode* left = head;           // left = head of left half
    ListNode* right = mid->next;     // right = head of right half
    // second half (right half) starts from the next node after the middle

    // detach the two halves (left & right) to get two separate halves
    mid->next = NULL;      // mid is the last node of 1st half, mid->next = NULL detaches the two halves 

    left = sortList(left);
    right = sortList(right);
    return merge(left, right); 
}

int main() {
    return 0;
}