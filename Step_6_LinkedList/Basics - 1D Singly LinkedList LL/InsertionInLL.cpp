#include <bits/stdc++.h>
using namespace std;

// Insertion in Linked List
/*

1. Insertion at Head (Beginning)
Logic:
• Create a new node.
• Store data in the new node.
• Make new node’s next point to current head.
• Move head to the new node.
• New node becomes the first node.

2. Insertion at Tail (End)
Logic:
• Create a new node.
• If list is empty → make new node as head.
• Otherwise, traverse till the last node.
• Make last node’s next point to new node.
• New node’s next becomes NULL.

3. Insertion at Position (k)
Logic:
• Create a new node.
• If list is empty and k ≠ 1 → no insertion.
• If k = 1 → insert at head.
• Traverse till the (k−1)th node.
• Make new node’s next point to kth node.
• Link (k−1)th node to new node.
• If position exceeds list size → no insertion.

4. Insertion Before a Given Node / Value
Logic:
• Create a new node.
• If list is empty → no insertion.
• If target node is head → insert at head.
• Otherwise, traverse the list to find the previous node of the target node.
• If target node is not found → no insertion.
• Make new node’s next point to target node.
• Link previous node’s next to the new node.
• New node gets inserted before the target node.
• Insertion before head is same as head insertion.

5. Insertion After a Given Node / Value
Logic:
• Create a new node.
• Traverse the list to find the target node (node after which insertion is required).
• If target node is not found → no insertion.
• Make new node’s next point to target node’s next.
• Link target node’s next to the new node.
• New node gets inserted immediately after the target node.
• If target node is the last node → new node becomes the new tail.

Core idea behind all insertions:
👉 First connect the new node with existing nodes, then change links of the previous node.
    Otherwise, remaining part of the list may get lost.

### Time Complexity Analysis :-
1. Insertion at Head : O(1)
    Direct access to head, no traversal needed.
2. Insertion at Tail : O(n)
    Need to traverse the entire list to reach last node 
    (O(1) if tail pointer is maintained).
3. Insertion at Position (k) : O(min(k, n))
    Traversal continues until (k−1)th node or end of list is reached.
4. Insertion Before a Given Node / Value : O(n)
    O(n) in worst case (need to search for the node and its previous node).
5. Insertion After a Given Node / Value : O(n)
    O(n) in worst case (need to search for the node).
*/

class Node{
public:
    int data;
    Node* next;

    Node(int x) {
        data = x;
        next = nullptr;
    }
    Node(int x, Node* n) {
        data = x;
        next = n;
    }
};

Node* createLL(vector<int>& arr) {
    Node* head = new Node(arr[0]);
    Node* curr = head;

    for (int i = 1; i < arr.size(); i++) {
        Node* temp = new Node(arr[i]);
        curr->next = temp;
        curr = temp;
    }

    return head;
}

void traverseLL(Node* head) {
    Node* curr = head;
    while (curr) {
        cout << curr->data << " -> ";
        curr = curr->next;
    }
    cout << '\n';
}

Node* insertHead(Node* head, int el) {
    // Node* temp = new Node(val, head);
    // return temp;

    return new Node(el, head);     
    // a new Node with data = val and next pointing to head is created and the pointer to this newNode is returned as new_head
}

Node* insertTail(Node* head, int el) {
    if (head == NULL)
        return new Node(el);

    Node* curr = head;
    while (curr->next) {
        curr = curr->next;
    }

    Node* temp = new Node(el);         // create the new node
    curr->next = temp;                  // link the new node to the tail of linked list

    return head;
}

Node* insertAtK(Node* head, int el, int k) {
    // if head is NULL, then insertion is not possible at any other position except 1st position (k == 1)
    if (head == NULL && k != 1)
        return NULL;
    
    if (k == 1) 
        return new Node(el, head);

    Node* curr = head;
    int cnt = 0;
    while(curr) {
        cnt++;
        // we need to link the (k-1)th node to the newly created node
        if (cnt == k - 1) {
            Node* temp = new Node(el); // newNode to be inserted
            temp->next = curr->next;    // we firstly link the nextNode to the newly created node
            curr->next = temp;          // now, we can link the newly created Node to the current Node
            break;
        }
        curr = curr->next;
    }
    return head;
}

Node* insertBeforeValue(Node* head, int el, int val) {
    // if head == NULL (i.e. linked list is empty), then there is no value to add the element before to
    if (head == NULL)
        return NULL;
    
    if (head->data == val) 
        return new Node(el, head);

    Node* curr = head;
    while(curr->next) {
        // we need to link the (k-1)th node to the newly created node
        if (curr->next->data == val) {
            Node* temp = new Node(el); // newNode to be inserted
            temp->next = curr->next;    // we firstly link the nextNode to the newly created node
            curr->next = temp;          // now, we can link the newly created Node to the current Node
            break;
        }
        curr = curr->next;
    }
    return head;
}

Node* insertAfterValue(Node* head, int el, int val) {
    if(head == NULL)
        return NULL;
    
    Node* curr = head;
    while (curr) {
        if (curr->data == val) {
            Node* temp = new Node(el);
            temp->next = curr->next;
            curr->next = temp;
            break;
        }
        curr = curr->next;
    }
    return head;
}

int main() {
    vector<int> arr = {2, 3, 4, 6};

    Node* head = createLL(arr);
    traverseLL(head);

    head = insertHead(head, 1);
    traverseLL(head);

    head = insertTail(head, 7);
    traverseLL(head);

    head = insertAtK(head, 5, 5);
    traverseLL(head);

    head = insertBeforeValue(head, 0, 1);
    traverseLL(head);

    head = insertAfterValue(head, 8, 7);
    traverseLL(head);

    return 0;
}