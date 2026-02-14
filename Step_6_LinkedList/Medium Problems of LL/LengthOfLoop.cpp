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

int main() {
    return 0;
}