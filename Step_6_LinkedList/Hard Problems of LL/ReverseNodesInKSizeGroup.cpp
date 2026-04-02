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
    • data.begin() + i + k → pointer to the next of end of group (k-size group)... 
        since if we want to reverse [i, i+k-1] we need to pass reverse(i, i+k) as it reverses till end - 1.
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
        reverse(data.begin() + i, data.begin() + i + k);
    }

    curr = head;
    for (int x : data) {
        curr->val = x;
        curr = curr->next;
    }

    return head;
}

// Optimal Approach : Time Complexity : O(2*n) __ Space Complexity : O(1)
/*
Approach :-

For reversing nodes in a linked list in groups of size k. Instead of flipping the whole list, 
we break it into groups of k nodes and reverse each group separately. 
If any group at the end has fewer than k nodes, we just leave it as is. 
To make this easier to understand and implement, we use 2 helper functions:-

• reverse: Reverses a linked list segment using the basic 3-pointer method (prev, curr, next).
• getKthNode: Given a starting node, it walks forward k steps and returns the k-th node. 
  If fewer than k nodes exist, it returns null. This helps us slice the list into group of size k.

Main Function:-
- reverseKGroup: The main function that keeps calling getKthNode to find valid k-sized segments, 
reverses them using 'reverse', and connects everything back together.

Example Case :-
List = 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → 10, k = 3.

head = 1
initially, we take temp = 1.
Now, we find the k-sized group by getting the kth node (kthNode) from the starting point of the current group (temp).
We get the kthNode which is at kth position from temp, using the getKthNode helper function.
• We use 'kthNode' variable to store this kthNode.
Now, we have the first and last node of the current k-size group, but to reverse it, it must be a separate list.
So, we do: 'kthNode->next = NULL' to separate this k-sized group from the list so it can be easily reversed.
List becomes: 1 → 2 → 3 → NULL __ 4 → 5 → 6 → 7 → 8 → 9 → 10        (separated into 2 parts)
temp = 1, kthNode = 3.
We reverse this k-sized group using 'reverse(temp)'
List becomes: 3 → 2 → 1 → NULL __ 4 → 5 → 6 → 7 → 8 → 9 → 10
We also have to keep track of the updated head, head should only be updated once when the 1st k-sized group is reversed.
During this 1st k-sized group, temp == head
So, we use condition 'if (temp == head) head = kthNode;' to track the updated head only when 1st group is reversed.
we do head = kthNode because after reversing the 1st kth group, kthNode becomes the newHead so head must point to it.

Now, we have to move to the next k-sized group to do the same functioning on it, but we can't go there as the link was broken.
So, before breaking the link (separating the k-sized group), we need to store the starting node of the next k-sized group.
Thus, we need to store 4 in some variable before breaking its link from 3.
• We use 'nextNode' variable to store this starting node of the next k-sized group
So, we store 'nextNode = kthNode->next' before breaking the link (i.e. before 'kthNode->next = NULL')

List : 1 → 2 → 3 → NULL __  4 → 5 → 6 → 7 → 8 → 9 → 10
       ^       ^            ^
       |       |            |
      temp   kthNode     nextNode
      head

After that we reverse and then, we can move to the next k-sized group by doing temp = nextNode.
List : 3 → 2 → 1 → NULL __  4 → 5 → 6 → 7 → 8 → 9 → 10
       ^                    ^
       |                    |
      head                temp
    (newHead)

We again find the kthNode, nextNode for this new k-sized group and reverse it as well.
List : 1 → 2 → 3 → NULL __  4 → 5 → 6 → NULL __  7 → 8 → 9 → 10
       ^                    ^       ^            ^
       |                    |       |            |
      head                 temp   kthNode     nextNode

Reversing it, list becomes :-
List : 1 → 2 → 3 → NULL __  6 → 5 → 4 → NULL __  7 → 8 → 9 → 10
       ^                    ^       ^            ^
       |                    |       |            |
      head               kthNode   temp       nextNode
    
But, now the list has three separated portions (because we didn't join the 1st k-group to the 2nd k-group).
We have to join them (join 3 to 6 so that the reversed head of current k-group is linked to tail of previous k-group)
For that we need to remember the tail of the previous k-group also, for this prupose we use the 'prevNode' variable.
So, we use 'prevNode' which is initially 'NULL' and 
when temp moves to the next k-group, it comes to temp's position to keep track of the tail of the previous k-group.

List : 1 → 2 → 3 → NULL __  6 → 5 → 4 → NULL __  7 → 8 → 9 → 10
       ^       ^             ^       ^            ^
       |       |             |       |            |
      head   prevNode     kthNode   temp       nextNode

After reversing the current k-sized group, we firstly have to link this reversed k-group to the previous k-group,
i.e., prevNode->next = kthNode.
after that, we move temp to next group and prevNode to temp 
i.e., prevNode = temp;
      temp = nextNode.
List : 1 → 2 → 3 → 6 → 5 → 4 → NULL __  7 → 8 → 9 → 10
       ^                   ^            ^  
       |                   |            |  
      head               prevNode      temp

We keep doing this, till have temp != NULL or till we keep finding k-sized groups.
Now, assume the case when temp reaches 10 (all the previous k-sized groups have been reversed).
List : 1 → 2 → 3 → NULL __  6 → 5 → 4 → 9 → 8 → 7 → NULL __ 10
       ^                                        ^            ^
       |                                        |            |
      head                                    prevNode      temp

Now, there is no k-sized group from this node (10), the getKthNode function will return NULL,
since there is no kth Node, we should leave these remaining nodes (here only 10) as it is.
But, we still need to link this temp to the prevNode, so we do prevNode->next = temp; and then break out of the loop.

Variables used :-
• temp :- starting node of the current k-sized group
• kthNode :- last node of the current k-sized group (kth node from the temp)
• nextNode :- starting node of the next k-sized group (temp will later become equal to it)
• prevNode :- tail of the previous k-sized group (equal to previous temp as temp becomes tail after reversing). 
*/

// this helper function a temp ListNode and return the kth node from the 'temp'
// this 'kthNode' is the last node of the k-sized group and will become the new head of the k-sized group
ListNode* getKthNode(ListNode* temp, int k) {
    while (temp != NULL && k != 1) {
        k--;
        temp = temp->next;
    }
    return temp;        
    // if there is no k-group possible for the 'temp', the loop will make temp reach null and thus return NULL
}

// this helper function takes a separate list (k-sized group) and reverses it
// we don't need to return the reversed head as it is already pointed to by the 'kthNode' pointer
void reverse(ListNode* currHead) {
    ListNode *prev = NULL, *curr = currHead;
    while (curr) {
        ListNode* nextNode = curr->next;
        curr->next = prev;   
        prev = curr;
        curr = nextNode;
    }
}

ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode* temp = head;
    ListNode* prevNode = NULL;

    while (temp) {
        // find the k-th Node (last node of the current k-sized group)
        ListNode* kthNode = getKthNode(temp, k);
        
        // if there are no more possible k-sized groups (when kthNode == NULL), break out of loop
        if (kthNode == NULL) {
            if (prevNode) prevNode->next = temp;    // for condition when k == linked-list.size()
            break;
        }
        
        ListNode* nextNode = kthNode->next;
        kthNode->next = NULL;           // separate the current k-sized group 
    
        reverse(temp);                  // reverse the k-sized group
    
        if (temp == head) head = kthNode;  // if it's the first k-sized group (i.e. temp == head) -> head changes
        else prevNode->next = kthNode;    // if it's later k-sized group, join this to the previous group
        
        prevNode = temp;
        temp = nextNode;
    }
    return head;
}

int main() {
    return 0;
}