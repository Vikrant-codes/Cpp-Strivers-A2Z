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
Let N = total no. of nodes (considering nodes count in main list and sub linked list)
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

// Optimal Approach :- Time Complexity :- O(n * m) __ Space Complexity : O(1)
// n = no. of head nodes (horizontal length), m = average no. of nodes in bottom linked list
/*
We know how to merge two sorted linked lists, but here we are supposed to merge multiple sorted linked lists into one.
So, we can use the merge function to add the sorted linked lists two at a time into a final linked list, and return its head.

Since the given linked list contains head nodes in sorted order, the final flattened linked list will have root as its head.
So, we can traverse the head linked lists and merge each one of them in the root linked list, 
this way all linked list will be merged.

Assume, linked list = [a] -> [b] -> [c] -> [d] -> ... -> [z]
where, [a], [b], etc are all head nodes of bottom linked lists,
then the a, b, c, etc nodes are also sorted. So, a will be the smallest value node and thus head node of flattened linked list.
We iterate from [b] to [z] and merge the curr linked list to the root linked list ([a]), 
this way, all the linked list will be merged into one single list [a] and this is our flattened list.
We use merge function to merge the bottom linked lists, since root will always remain the head of the flattened list, 
we don't need to explicitly return the head of merged list after each merging, hence return type of merge is void.
*/
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

/*
In the previous approach we were merging each list with the root linked list and comparison starts from root every time.
But, we know that when we iteratively traverse from root, all the head nodes are also in sorted order, 
so assume for linked list [a] -> [b] -> [c] -> [d] -> [e] -> ... -> [z]
say, we merged [b] with [a] which is root node, now in next iteration we need to merge [c].
We merge it comparing it with [a] (root node), but that means we need to traverse all bottom nodes of root node again,
we know that [c] is definitely greater than (or equal to) [b], thus, instead of merging [c] with [a], 
we can compare its nodes with nodes of [b] and get their positions early.

Assume [a] was linked to [a] -> a1 -> a2 -> a3
Similarly, [b], [c], etc are also linked to their respective bottom linked lists,
now assume after merging of [a] & [b], merged list became [a] -> a1 -> a2 -> [b] -> b1 -> a3 -> b2,
Now, when [c] comes, in the previous approach, we passed, [a] & [c] to merge function, 
so [c] will be compared to ([a], a1, a2) nodes, but we know for sure that c is at least equal to [b],
so the linked list [c] nodes, must comes after [b] and hence this traversal of ([a] -> a1 -> a2 -> ) nodes will be in vain, 
as [c] nodes will only come after [b].
So, we use two pointers to track the positions of previous linked list and curr linked list and merge the two.

This is small optimization over the previous approach.
*/
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

// Recursive Approach :- Time Complexity : O(N x (2M)) ~ O(2N x M) __ Space Complexity : O(N)
/*
Algorithm :-
- Establish base case conditions by checking if the head is null or has no next pointer. 
  If either condition is met, return the head, as there is no further flattening or merging required.
- Recursively initiate the flattening process by calling flattenLinkedList on the next node (head -> next). 
  The result of this recursive call will be the head of the flattened and merged linked list.
- Within the recursive call, perform merge operations by calling a merge function. 
  This function merges the current list with the already flattened and merged list based on their data values. 
  The merged list is then updated in the head and returned as the result of the flattening process.

>> Complexity Analysis

-> Time Complexity: O(N x (2M)) ~ O(2N x M), 
where N is the length of the linked list along the next pointer and M is the length of the linked list along the child pointers.

The merge operation in each recursive call takes time complexity proportional to the length of the linked lists being merged, 
as they have to iterate over the entire lists. 
Since the vertical depth of the linked lists is assumed to be M, 
the time complexity for a single merge operation is proportional to O(2M).
This operation is performed N number of times (to each and every node along the next pointer list), 
hence the resultant time complexity becomes O(N x 2M).

Space Complexity: O(1), as this code uses no external space or additional data structures to store values. 
But a recursive stack uses O(N) space to build the recursive calls for each node along the next pointer list.
*/
Node* mergeRec(Node* head1, Node* head2) {
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
    
    return dummy->bottom;
}

Node *flatten(Node *root) {
    if (root == NULL || root->next == NULL) return root;

    Node* mergedHead = flatten(root->next);
    
    return mergeRec(root, mergedHead);
}

int main() {
    return 0;
}