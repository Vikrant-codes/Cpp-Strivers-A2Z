/*
GFG - Flattening a Linked List : Medium

Given a linked list containing n head nodes where every node in the linked list contains two pointers:
(i) next points to the next node in the list.
(ii) bottom points to a sub-linked list where the current node is the head.
Each of the sub-linked lists nodes and the head nodes are sorted in ascending order based on their data. 
Flatten the linked list such that all the nodes appear in a single level while maintaining the sorted order.

Note:
1. ↓ represents the bottom pointer and → represents the next pointer.
2. The flattened list will be printed using the bottom pointer instead of the next pointer.

Examples:
Input:
head -> 5 -> 10 -> 19 -> 28
        |    |     |     |
        7    20    22    40
        |                |
        8                45
Output: 5 -> 7 -> 8 -> 10 -> 19 -> 20 -> 22 -> 28 -> 40 -> 45.
Explanation: 
Bottom pointer of 5 is pointing to 7.
Bottom pointer of 7 is pointing to 8.
Bottom pointer of 10 is pointing to 20 and so on.
So, after flattening the linked list the sorted list will be 
5 -> 7 -> 8 -> 10 -> 19 -> 20 -> 22 -> 28 -> 40 -> 45.

Constraints :-
• 0 ≤ n ≤ 100
• 1 ≤ number of nodes in sub-linked list(mi) ≤ 50
• 1 ≤ node->data ≤ 10^5
*/

#include <bits/stdc++.h>
using namespace std;

/*
class Node {
public:
    int data;
    Node* next;
    Node* bottom;

    Node(int x) {
        data = x;
        next = NULL;
        bottom = NULL;
    }
};
*/

class Node {
public:
    int data;
    Node* next;
    Node* bottom;

    Node(int x) {
        data = x;
        next = NULL;
        bottom = NULL;
    }
};

/*
The Linked list is such that it contains 'n' head nodes and each node acts as a 'head node' for a sub-linked list.
The n head nodes are linked through 'next' pointers and the the sub linked lists of each head node is connected to it 
through 'bottom' pointers.
So, we to traverse the n nodes of the given linked list, we use the next pointer and to traverse the sub-linked list of 
a head node, we use the bottom pointer.

Example :- head -> 5 -> 10 -> 19 -> 28
                   |    |     |     |
                   7    20    22    40
                   |                |
                   8                45

    Here, the given linked list is [5] -> [10] -> [19] -> [28].
    All of these nodes act as head nodes for their respective sub-linked lists. 
    These sub linked list are traversed using bottom pointer. Sub-linked lists are --
    [5] :- Sublinked list :- [5] -> 7 -> 8  
    [10] :- Sublinked list :- [10] -> 20  
    [19] :- Sublinked list :- [19] -> 22  
    [28] :- Sublinked list :- [28] -> 40 -> 45
    Each of these sub-linked lists are sorted and the main linked list (containing head nodes) is also sorted.
    
    We want to flatten this whole linked list such a way that the final linked list is a single level linked list having
    data stored in sorted manner.
    i.e. result must be => 5 -> 7 -> 8 -> 10 -> 19 -> 20 -> 22 -> 28 -> 40 -> 45
    This flattened list must be created in such a way that the next pointer of each node is null and nodes are connected 
    using bottom pointers. (The result list would be traversed using bottom pointer).
*/

// Naive Approach : Time Complexity : O(N) + O(N log N) + O(N) __ Space Complexity : O(N)
/*
Traverse the main linked list and all bottom lists to collect node values into an array.
Sort the array.
Create a new flattened linked list using the sorted values by linking nodes via the bottom pointer.
Use a dummy node to simplify list construction.

Time Complexity:
• Traversing all nodes (main + bottom lists): O(N)
• Sorting the array: O(N log N)
• Creating new linked list: O(N)
👉 Overall: O(N) + O(N log N) + O(N)

Space Complexity:
• Array to store all elements: O(N)
• New linked list (output): O(N) (usually not counted as extra space since it's required output)
👉 Auxiliary space: O(N)
*/
Node *flattenNaive(Node *root) {
    Node* curr = root;
    vector<int> arr;
    
    while (curr) {
        Node* temp = curr;
        while (temp) {
            arr.push_back(temp->data);
            temp = temp->bottom;
        }
        curr = curr->next;
    }
    
    sort(arr.begin(), arr.end());
    
    Node* dummy = new Node(-1);
    Node* ptr = dummy;
    
    for (int x : arr) {
        Node* newNode = new Node(x);
        ptr->bottom = newNode;
        ptr = newNode;
    }
    
    return dummy->bottom;
}

// Optimal Approach :- 
// merge function to merge 2 sorted bottom-linked lists
void merge(Node* head1, Node* head2) {
    Node* dummy = new Node(-1);
    Node* temp = dummy;
    Node *t1 = head1, *t2 = head2;
    
    while (t1 && t2) {
        if (t1->data <= t2->data) {
            temp->bottom = t1;
            t1 = t1->bottom;
        }
        else {
            temp->bottom = t2;
            t2 = t2->bottom;
        }
        temp = temp->bottom;
    }
    
    if (t1) temp->bottom = t1;
    if (t2) temp->bottom = t2;
}

Node *flatten1(Node *root) {
    if (root == NULL || root->next == NULL) return root;
    
    Node* mover = root->next;
    
    while (mover) {
        merge(root, mover);
        mover = mover->next;
    }
    
    return root;
}

Node *flatten2(Node *root) {
    if (root == NULL || root->next == NULL) return root;
    
    Node* l1 = root;
    Node* l2 = root->next;
    
    while (l2) {
        merge(l1, l2);
        l1 = l2;
        l2 = l2->next;
    }
    
    return root;
}



int main() {
    return 0;
}