/*
Leetcode - 138. Copy List with Random Pointer : Medium

A linked list of length n is given such that each node contains an additional random pointer, 
which could point to any node in the list, or null.

Construct a deep copy of the list. The deep copy should consist of exactly n brand new nodes, 
where each new node has its value set to the value of its corresponding original node. 
Both the next and random pointer of the new nodes should point to new nodes in the copied list such 
that the pointers in the original list and copied list represent the same list state. 
None of the pointers in the new list should point to nodes in the original list.

For example, if there are two nodes X and Y in the original list, where X.random --> Y, 
then for the corresponding two nodes x and y in the copied list, x.random --> y.

Return the head of the copied linked list.

The linked list is represented in the input/output as a list of n nodes. 
Each node is represented as a pair of [val, random_index] where:
    val: an integer representing Node.val
    random_index: the index of the node (range from 0 to n-1) that the random pointer points to, 
        or null if it does not point to any node.
Your code will only be given the head of the original linked list.

Examples :-

Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]

Input: head = [[1,1],[2,1]]
Output: [[1,1],[2,1]]

Input: head = [[3,null],[3,0],[3,null]]
Output: [[3,null],[3,0],[3,null]]

Constraints :-
• 0 <= n <= 1000
• -10^4 <= Node.val <= 10^4
• Node.random is null or is pointing to some node in the linked list.
*/

#include <bits/stdc++.h>
using namespace std;

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};


/*
Approach :-

It's simpler to create copies (or clones) of nodes while moving forward and connecting them in a chain 
but the tricky part is how to connect the random pointers.
The random pointer could be connected to any other node of the list and if we are constructing the copy list while traversing
then it is not possible to connect random pointers for nodes of the copy list.
Also, connecting next pointers is simple as we need to connect only the previous and next node with the next pointer, 
but for random pointer we need to know which node of the list we must point it to.

To connect random pointer to a node we must know what node the original Node's random pointer is pointing to.
So, we can use position concept, like we consider head to be at 0 or 1 position and then find the position of the Node 
which is pointed by the random pointer.
We can then connect the random pointer of the copy list Node to the copy list Node present at that same position.

Like, if in original list 7's pointer is pointing to the node at 3rd position, then the copy list 7 Node's random pointer 
must also point to the 3rd position node in that list.

Since we are dealing with position based access of Nodes, we can use an array of Nodes to store the cloned Nodes.
So, we firstly traverse the main linked list and create clones of all the Nodes of that list.
We push the cloned Nodes to an array.
Now, we need to connect the next & random pointers of the cloned Nodes.
We again traverse the main list while maintaing an index variable to track the cloned Node corresponding to current main list Node.
Assume 'mover' is the main list current Node and array[index] is the corresponding clone list Node.
Connecting next is simple, for Node at index 'i' in arr, we need to connect it's next to the Node at index (i+1).
If it is the last node, we don't need to connect its next to any node as it is already NULL.

For the current Node we check if its random pointer is pointing to some other node (if it's not NULL).
In case its random pointer is pointing to some Node, we need to calculate the position of that Node.
So, we use an inner loop to traverse the list and find the position of the Node pointed to by the current main list Node's random pointer.
We find the 0-based index. Assume the current main List Node random is pointing to some Node at position 'k', 
then, the random pointer of clone list current Node (cloneArr[index]) must also point to the Node at position 'k' in the array.
This way we can connect the random pointers of the clone List Nodes.

At the end return the Node at the array index '0' as the head of the cloned list.
*/
Node* copyRandomList1(Node* head) {
    if (!head) return NULL;

    vector<Node*> arr;

    Node* mover = head;
    while (mover) {
        Node* newNode = new Node(mover->val);
        arr.push_back(newNode);
        mover = mover->next;
    }

    mover = head;
    int idx = 0;
    while (mover) {
        if (idx != arr.size()-1) 
            arr[idx]->next = arr[idx+1];

        if (mover->random) {
            int pos = 0;
            Node* curr = head;

            while (curr != mover->random) {
                curr = curr->next;
                pos++;
            }

            arr[idx]->random = arr[pos];
        }
            
        idx++;
        mover = mover->next;
    }

    return arr[0];
}

// same logic as above but is more readable as we have defined a function to getPosition which inrease readibility.
int getPosition(Node* head, Node* target) {
    Node* curr = head;
    int pos = 0;

    while (curr != target) {
        pos++;
        curr = curr->next;
    }

    return pos;
}

Node* copyRandomList1x(Node* head) {
    if (!head) return NULL;

    vector<Node*> arr;
    
    Node* mover = head;
    
    while (mover) {
        Node* newNode = new Node(mover->val);
        arr.push_back(newNode);
        mover = mover->next;
    }
    
    mover = head;
    int idx = 0;
    while (mover) {
        if (idx != arr.size()-1) 
            arr[idx]->next = arr[idx+1];
    
        if (mover->random) {
            int pos = getPosition(head, mover->random);
            arr[idx]->random = arr[pos];
        }
        
        idx++;
        mover = mover->next;
    }

    return arr[0];
}

Node* copyRandomList(Node* head) {
    if (!head) return NULL;

    Node* dummy = new Node(-1);
    Node* temp = dummy;
    Node* mover = head;
    
    while (mover) {
        Node* newNode = new Node(mover->val);
        temp->next = newNode;
        temp = temp->next;
        mover = mover->next;
    }
    
    mover = head;
    temp = dummy->next;
    
    while (mover) {
        if (mover->random) {
            Node* t1 = head;
            Node* t2 = dummy->next;

            while (t1 != mover->random) {
                t1 = t1->next;
                t2 = t2->next;
            }

            temp->random = t2;
        }

        mover = mover->next;
        temp = temp->next;
    }
    
    return dummy->next;
}

int main() {
    return 0;
}