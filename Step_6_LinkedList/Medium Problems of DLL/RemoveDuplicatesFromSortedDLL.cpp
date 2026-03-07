/*
GFG - Remove duplicates from a sorted doubly linked list : Easy

Given a doubly linked list of n nodes sorted by values, the task is to remove duplicate nodes present in the linked list.

Example 1:

Input:
n = 6
1<->1<->1<->2<->3<->4
Output:
1<->2<->3<->4
Explanation:
Only the first occurance of node with value 1 is 
retained, rest nodes with value = 1 are deleted.

Example 2:

Input:
n = 7
1<->2<->2<->3<->3<->4<->4
Output:
1<->2<->3<->4
Explanation:
Only the first occurance of nodes with values 2,3 and 4 are 
retained, rest repeating nodes are deleted.

Constraint:
1 <= n <= 10^5
*/

#include <bits/stdc++.h>
using namespace std;

/*
struct Node
{
    int data;
    Node * next;
    Node * prev;
    Node (int x)
    {
        data=x;
        next=NULL;
        prev=NULL;
    }

};
*/

struct Node {
    int data;
    Node * next;
    Node * prev;
    Node (int x) {
        data=x;
        next=NULL;
        prev=NULL;
    }
};

// Time Complexity : O(n) __ Space Complexity : O(1)
/*
>> Idea : 
Since the list is sorted, duplicates appear next to each other.
So for every node curr, we check if its nextNode is its duplicate, i.e., if curr->data == curr->next->data.
If yes, we skip all those nodes having the same value.

>> Intuition
The list is sorted, so if duplicates exist, they will always appear next to each other.
Example: 1 ⇄ 2 ⇄ 2 ⇄ 2 ⇄ 3 ⇄ 4
So instead of deleting nodes one by one, the idea is:
  When we encounter duplicates, skip the entire block of duplicates and 
  directly connect the current node to the first different node.
This avoids unnecessary deletions and makes the traversal simpler.

Step-wise Approach
1. Start from the first node
Keep a pointer curr at the head of the list.
Goal: Examine each node and check if duplicates follow it.

2. Check if the next node is a duplicate
For the current node, compare its value with the next node.
If the values are different → move forward normally.
If the values are the same → duplicates exist.

3. Skip all nodes with the same value
Once a duplicate is detected, move another pointer forward until you find the first node whose value is different.

4. Reconnect the list
Now connect the current node directly to this non-duplicate node.

5. Move forward
Now move the current pointer to the next node and repeat the process.

>> Key Idea
The algorithm does two main things:
- Detect duplicate sequence
- Jump over the entire sequence in one step
*/
Node *removeDuplicates(struct Node *head) {
    Node* curr = head;

    while (curr) {
        // if duplicates exist for current node
        if (curr->next != NULL && curr->data == curr->next->data) {
            // traverse till the first node is found whose value is not a duplicate of current node
            Node* nextNode = curr->next;
            
            while (nextNode && nextNode->data == curr->data) 
                nextNode = nextNode->next;
            // Now, nextNode points to the first node after skipping its duplicates 
            
            curr->next = nextNode;                  // link curr's next to nextNode  
            if (nextNode) nextNode->prev = curr;    // link nextNode's prev to curr
        }

        curr = curr->next;   // move curr ahead, it points to the next node after skipping duplicates
    }

    return head;
}

/*
Striver's approach is also same just the implementation is bit different, 
The duplicate nodes are deleted and not just skipped unlike previous approach

Core Idea:
Keep the first occurrence → delete every identical node that follows it.
*/
Node *removeDuplicatesStriver(struct Node *head) {
    Node* temp = head;

    while (temp) {
        Node* nextNode = temp->next;
        
        while (nextNode != NULL && nextNode->data == temp->data) {
            Node* duplicate = nextNode;     // store the duplicate
            nextNode = nextNode->next;      // move nextNode ahead
            delete duplicate;
        }
        
        temp->next = nextNode;
        if (nextNode) nextNode->prev = temp;
        
        temp = temp->next;
    }

    return head;
}

int main() {
    return 0;
}