/*
Leetcode - 206. Reverse Linked List : Easy

Given the head of a singly linked list, reverse the list, and return the reversed list.

Examples :-

Input: head = [1,2,3,4,5]
Output: [5,4,3,2,1]

Input: head = [1,2]
Output: [2,1]

Input: head = []
Output: []

Constraints :-
• The number of nodes in the list is the range [0, 5000].
• -5000 <= Node.val <= 5000

Follow up: A linked list can be reversed either iteratively or recursively. Could you implement both?
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

// Naive Approach (Using Stack): Time Complexity : O(n) __ Space Complexity : O(n)
/*
If we just reverse the data of each node, we can simulate this reversal of Linked List.
Core idea: We are not changing pointers. Instead we are just storing values and writing them back in reverse order.

So, we can use an appropriate data structure to store the data of all nodes and 
then traverse the list again and update data of each Node.
Stack would be suitable for this use-case as a stack reverses order automatically because it follows LIFO (Last In, First Out).

Step 1: Push all values
• Traverse the linked list and push each node’s value into the stack.
• Now the stack stores elements in reverse order internally.
Example:- 
    List: 1 → 2 → 3 → 4
    Stack (top at right): 1 2 3 4

Step 2: Pop and overwrite
• Traverse the list again and replace each node’s value with st.top().
• Since stack pops from the end:
New values assigned: 4 → 3 → 2 → 1
*/
ListNode* reverseListUsingStack(ListNode *head) {
    stack<int> st;
    ListNode* curr = head;
    while (curr) {
        st.push(curr->val);
        curr = curr->next;
    }
    curr = head;
    while (curr) {
        curr->val = st.top();
        st.pop();
        curr = curr->next;
    }
    return head;
}

// Naive Approach (Using Insertion at Head on another List): Time Complexity : O(n) __ Space Complexity : O(n)
/*
Intuition

Think of building a new linked list, and every time you see a node, you attach it at the front (head) of the new list.
Attaching at the front automatically reverses order.

>> Why inserting at head reverses
Suppose original list: 1 → 2 → 3 → 4
You process nodes one by one:
Step 1: revHead = null — Take 1, Insert at front — 1
Step 2: Take 2, Insert at front — 2 → 1
Step 3: Take 3, Insert at front — 3 → 2 → 1
Step 4: Take 4, Insert at front — 4 → 3 → 2 → 1

Each new node becomes the new head.
So order naturally flips.

>> Core idea in one line
| If you keep inserting elements at the front(head), the final structure becomes reversed.
*/
ListNode* reverseListUsingList(ListNode* head) {
    if (head == NULL)
        return head;
    ListNode* revHead = nullptr;
    ListNode* curr = head;
    
    while (curr) {
        ListNode* newNode = new ListNode(curr->val, revHead);
        revHead = newNode;
        curr = curr->next;
    }

    return revHead;
}

// Optimal Approach (Iterative & Recursive): Time Complexity : O(n) __ Space Complexity : O(1)
/*
Idea (intuition)
At each step:
• take the current node
• make it point to the previous node instead of the next node
• move forward
We keep reversing links one by one until the list ends.

For each node we need its previous node 
so we can reverse the link of curr node by making its next pointer point to prev instead of next node.

So, we use two node pointers prev & curr. curr points at curr node & prev points at the previous node.
*/

ListNode* reverseListIterative(ListNode *head) {
    // if (head == NULL)
    //     return head;
    // This 'head == null' check is optional as even without this the below code would handle NULL safely.
    
    ListNode* prev = nullptr;       // Initially prev is null as there is no previous node to head node
    ListNode* curr = head;
    while (curr) {
        ListNode* temp = curr->next;    // store next so we won't lose it after the next link of curr is reversed
        curr->next = prev;              // reverse link by making the next pointer of curr point to prev instead of next
        prev = curr;                    // move prev forward
        curr = temp;                    // move curr forward
    }
    return prev;
}

// Recursive Approach
/*
In Recursion approaches, we try to divide a bigger problem into smaller subproblems and solve them.
How can we do that here...?
Imagine we are given a big linked list with 'n' nodes, so we could use recursion to solve (i.e. to reverse) 
the next 'n-1' nodes which lie ahead of the head node.
So, for given head, we call the reverse function for head->next to reverse the forward portion first.
We then attach the current node to the last node of the forwarded reverse portion.

>> What's the smallest subproblem case (base-condition) ?
If the passed linked list is empty or has only one element, we don't have to reverse it.. so just return head.
This condition "if (head == NULL || head->next == NULL)" serves as the base condition.

Ex- Assume the linked list was 1 -> 2 -> 3 -> 4
- we call reverse fn for the head node (1) i.e. reverse(1):  | 1 | -> 2 -> 3 -> 4
    - it calls reverse function for the next node ahead of it i.e. reverse(2): 1 -> | 2 | -> 3 -> 4
        - reverse(3): 1 -> 2 -> | 3 | -> 4
            - reverse(4): 1 -> 2 -> 3 -> | 4 |
                - Now, the head node for this fn (reverse(4)) is a single node (base condition)
                  So, we just return it as it is, without doing anything, this will become new head after reversal.
            Now, we have been returned 4 as the newHead, we need to attach the current node which is '3' at the tail of the 
            reversed portion (which is the next node to current node (as 3 is pointing to 4))
            So, we instead of 3 -> 4, we need to turn the link around and make it 4 -> 3 (this way reversal happens)
            We do something like curr->next->next = curr (this way 4 (which is 3->next) will point its next to 3)
            We also need to remove 3's next which is pointing to 4, we make it poin to NULL
            The list becomes: 1 -> 2 -> | 3 | <- 4 .... 3 is pointing to NULL
        4 is returned as the head, the reversed forward portion ahead of the curr node includes : 4 -> 3
        we need to add current node at its tail (at 3's next).. this tail is being pointed to by curr->next 
        as we can see, 1 -> 2 -> | 3 | <- 4, 2 is pointing to 3 which is tail of forward reversed portion
        we simply make 3's next point to 2 and 2's next point to NULL
        list becomes: 1 -> | 2 | <- 3 <- 4 ... 2 is pointing to NULL
    4 is returned as head, 2 is the current tail of reversed portion and also currNode = 1 and 1's next = 2.
    We do 2's next = 1 and 1's next = NULL
    list becomes: | 1 | <- 2 <- 3 <- 4 ... 1 is pointing to NULL

This way the whole list is reversed.
*/
ListNode* reverseLL(ListNode* prev, ListNode* curr) {
    if (curr == NULL)
        return prev;
    ListNode* temp = curr->next;
    curr->next = prev;
    return reverseLL(curr, temp);
}

ListNode* reverseListRecursive(ListNode *head) {
    return reverseLL(nullptr, head);
}

// Striver's Implementation of Recursive Approach
ListNode* reverseList(ListNode* head) {
    if (head == NULL || head->next == NULL)
        return head;

    ListNode* newHead = reverseList(head->next);
    ListNode* nextNode = head->next;
    nextNode->next = head;
    head->next = nullptr;

    return newHead;
}


int main() {

    return 0;
}