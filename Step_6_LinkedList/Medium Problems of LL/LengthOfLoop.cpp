/*
Problem Statement: 
Given the head of a linked list, determine the length of a loop present in the linked list. 
If there's no loop present, return 0.

|| GFG - Find length of Loop : Medium

Given the head of a linked list, determine whether the list contains a loop. 
If a loop is present, return the number of nodes in the loop, otherwise return 0.

Note: Internally, pos(1 based index) is used to denote the position of the node that tail's next pointer is connected to. 
If pos = 0, it means the last node points to null, indicating there is no loop. Note that pos is not passed as a parameter.

Examples :-

Input: pos = 2, head = [1, 2, 3, 4, 5]
Output: 4
Explanation: There exists a loop in the linked list and the length of the loop is 4.

Input: pos = 3, head = [25, 14, 19, 33, 10]
Output: 3
Explanation: The loop is from 19 to 10. So length of loop is 19 → 33 → 10 = 3.

Input: pos = 0, head = [1, 2, 3, 4, 5]    
Output: 0
Explanation: There is no loop.

Constraints :-
- 1 ≤ number of nodes ≤ 10^5
- 1 ≤ node->data ≤ 10^4
- 0 ≤ pos < number of nodes
*/

#include <bits/stdc++.h>
using namespace std;

/*
class Node {
 public:
    int data;
    Node *next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};
*/
class Node {
public:
    int data;
    Node *next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};

// HashMap Approach : Time Complexity : O(n) __ Space Complexity : O(n)
/*
We know that we can use hashing (map / set) to detect whether a loop exists by checking if any node re-appears while traversing.
In case of loop's existence, we can find its length by considering when was the last time we saw the re-appearing node.
Use a map to store Nodes & their index values (1-indexed or 0-indexed) in the map (use a counter variable to do that).
When a node re-appears, we find the difference between the current index/counter value and the value stored in map.
This difference is the length of loop.
*/
int lengthOfLoop(Node *head) {
    unordered_map<Node*, int> mpp;
    Node* curr = head;
    
    int i = 1;
    
    while (curr) {
        if (mpp.find(curr) != mpp.end())
            return (i - mpp[curr]);
        mpp[curr] = i;
        i++;
        curr = curr->next;
    }
    
    return 0;
}

// Optimal Approach (Floyd's Loop Detection + Loop Traversal): Time Complexity : O(n) __ Space Complexity : O(1)
/*
• Use Floyd’s Cycle Detection Algorithm to detect whether a loop exists, using two pointers (slow & fast).
• If the pointers meet, a cycle is confirmed. The meeting point lies somewhere inside the loop.
• To find the loop length:
    - Keep one pointer fixed at the meeting point.
    - Move the other pointer one step at a time through the loop.
    - Count the number of steps taken until it reaches the same collision point again (the other pointer is standing here).
    - The total number of steps counted is the length of the loop.
    - (This is because length of loop = no. of steps required from any node to reach itself after traversing the loop once)
• If the fast pointer reaches NULL, no loop exists, so return 0.
*/
int lengthOfLoop(Node *head) {
    Node* slow = head;
    Node* fast = head;
    
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        // if loop exists
        if (slow == fast) {
            int len = 1;
            slow = slow->next;
            while (slow != fast) {
                len++;
                slow = slow->next;
            }
            return len;
        }
    }
    
    return 0;
}

int main() {
    return 0;
}