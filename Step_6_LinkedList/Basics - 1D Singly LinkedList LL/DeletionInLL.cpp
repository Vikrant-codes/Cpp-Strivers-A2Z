#include <bits/stdc++.h>
using namespace std;

// Deletion in Linked List
/*
1. Deletion of Head Node
Logic:
• Check if list is empty → nothing to delete.
• Store current head in a temporary pointer.
• Move head to the next node (head = head->next).
• Delete the old head node.
• New head becomes the first node.

2. Deletion of Tail Node
Logic:
• If list is empty → nothing to delete.
• If only one node exists → delete it and make head NULL.
• Traverse until reaching the second last node.
• Make its next = NULL.
• Delete the last node.

3. Deletion by Value
Logic:
• If list is empty → stop.
• If head contains the value → delete head.
• Traverse while keeping track of:
    - current node
    - previous node
• When value is found:
    - Make previous node point to next of current node.
    - Delete current node.
• If value not found → no deletion.

4. Deletion by Position (k)
Logic:
• If list is empty → stop.
• If k = 1 → delete head.
• Traverse until reaching the (k-1)th node.
• Store the kth node temporarily.
• Link (k-1)th node to (k+1)th node.
• Delete the kth node.
• If position exceeds list size → no deletion.

Core idea behind all deletions:
👉 Change links first, then delete the node, otherwise the list structure breaks.

### Time Complexity Analysis :-
1. Deletion of Head Node : O(1)
    since we have the direct reference to head node
2. Deletion of Tail Node : O(n)
    we need to traverse the entire linked list to delete the last node
3. Deletion by Value : Worst Case : O(n)
    In the worst case, the value may be at the last Node or may not exist.
    In average cases, the loop runs till the value is encountered... (so no fixed no. of steps).
4. Deletion by Position (k) : O(min(k, n))
    the deletion ends when kth node is found.. if k > n, Linked List's end is reached & no deletion happens
*/

class Node {
public:
    int data;
    Node* next;

    Node(int x) {
        data = x;
        next = nullptr;
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

void printLL(Node* head) {
    Node* curr = head;
    while(curr) {
        cout << curr->data << " -> ";
        curr = curr->next;
    }
    cout << '\n';
}

Node* deleteHead(Node* head) {
    // if Linked List is empty ... return NULL as it have nothing to delete
    if (head == NULL) 
        return head;

    Node* temp = head;
    head = head->next;

    delete temp;        // remove the previous head from memory 

    return head;
}

Node* deleteTail(Node* head) {
    // if the Linked List have less than 2 elements (either 0 or 1), then after deleting the tail, it would become empty
    // so return NULL
    if (head == NULL || head->next == NULL)
        return NULL;

    Node* prev = head;          // to track 2nd last node
    Node* curr = head->next;    // to track last node
    // loop runs till curr->next is not null ... loop exits when curr points to last node (curr->next becomes NULL)
    while (curr->next) {
        prev = prev->next;          // prev = curr will also be the same thing      
        curr = curr->next;
    }

    // the loop ends when curr->next becomes null (which means curr curr = last node (tail), prev = second last node)
    delete curr;                // delete the last node from memory                     
    prev->next = NULL;          // make the second last node the new tail

    return head;
}

Node* deleteTailStriver(Node* head) {
    if (head == NULL || head->next == NULL)
        return NULL;

    Node* temp = head;

    // when temp->next->next becomes NULL it means that temp is the 2nd last Node
    // move till second last node
    while (temp->next->next) {
        temp = temp->next;      // move temp forward
    }
    // now temp is the 2nd last Node
    delete temp->next;              // temp->next is the current tail of LL, delete this tail
    temp->next = NULL;              // make the 2nd last element the tail of LL by initializing its next pointer to nullptr

    return head;
}
// what's happening in the lines delete temp->next; and temp->next = NULL;
/*
Assume this structure:
head → [10 | * ] → [20 | * ] → [30 | NULL]
                     ↑
                    temp
Here:
- temp points to node 20
- temp->next points to node 30

1️⃣ delete temp->next;
This means:
👉 Go to the address stored inside temp->next
👉 Free the memory of that node
So: delete temp->next;
- Node 30 is removed from memory.
- The memory is freed.
But important:
✅ The pointer itself is NOT changed yet.
After deletion: temp → [20 | * ] ----X----> (invalid memory)
temp->next still contains the old address, but that address is now invalid (dangling pointer).

2️⃣ temp->next = NULL;
Now we fix the pointer.
We are saying:
👉 "This node no longer has a next node."
So: temp → [20 | NULL]
Now the list safely ends here.

>> Why both are needed
If you only do:  delete temp->next;
then:
- memory is freed ✅
- but pointer still stores old address ❌
- accessing later → undefined behaviour / crash
If you only do:    temp->next = NULL;
then:
- node still exists in memory ❌
- memory leak happens
So both steps are necessary.

>> Simple mental model (very important)
Think of it as:
    
delete X;        // destroy the house
pointer = NULL;  // remove the address from the map
    
First you remove the object, then you remove the reference to it.
*/

Node* deleteByValue(Node* head, int value) {
    if (head == NULL)
        return head;

    // if it is the first Node (head node) itself
    if (head->data == value) 
        return head->next;
    
    // else implement logic accordingly
    Node* prev = head;
    Node* curr = head->next;
    while (curr) {
        if (curr->data == value) {
            // remove the link of current node from previous node
            prev->next = curr->next;
            delete curr;
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    return head;
}

Node* deleteKthNode(Node* head, int k) {
    if (head == NULL)
        return head;

    // if it is the first Node (head node) itself
    if (k == 1) 
        return head->next;  // we could also delete the previous head Node (but that's totally optional and according to need)
    
    int i = 2;              // we start with the 2nd Node
    Node* prev = head;
    Node* curr = head->next;
    while (curr) {
        if (i == k) {
            // remove the link of current node from previous node
            prev->next = curr->next;
            delete curr;
            break;
        }
        prev = curr;
        curr = curr->next;
        i++;
    }

    return head;
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
    
    Node* head = createLL(arr);
    printLL(head);

    // delete the head Node from Linked List
    head = deleteHead(head);
    printLL(head);

    // delete the tail Node of Linked List
    head = deleteTail(head);
    printLL(head);

    // delete by value
    head = deleteByValue(head, 5);
    printLL(head);

    // delete by position
    head = deleteKthNode(head, 3);
    printLL(head);

    return 0;
}