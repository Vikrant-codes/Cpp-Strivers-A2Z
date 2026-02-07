#include <bits/stdc++.h>
using namespace std;

class Node{
public:
    int data;
    Node* next;
    Node(int val) {
        data = val;
        next = NULL;
    }
    Node(int val, Node* next_node) {
        data = val;
        next = next_node;
    }
};

// create a Linked List from a vector of integers
Node* createLL(vector<int>& arr) {
    if (arr.empty()) return NULL; 
    Node* head = new Node(arr[0]);
    Node* curr = head;

    for(int i = 1; i < arr.size(); i++) {
        Node* temp = new Node(arr[i]);
        curr->next = temp;
        curr = temp;
    }

    return head;
}

// traverse and print linked list elements
void traverseLL(Node* head) {
    Node* curr = head;
    while (curr) {
        cout << curr->data << " -> ";
        curr = curr->next;
    }
    cout << '\n';
}

// size of linked list
int sizeOfLL(Node* head) {
    Node* curr = head;
    int cnt = 0;
    while(curr) {
        cnt++;
        curr = curr->next;
    }
    return cnt;
}

// delete head node of the linked list
Node* deleteHead(Node* head) {
    if (head == NULL) 
        return head;
    Node* temp = head;
    head = head->next;
    delete temp;
    return head;
}

// delete tail node of the linked list
Node* deleteTail(Node* head) {
    if (head == NULL || head->next == NULL)
        return NULL;

    Node* temp = head;
    while(temp->next->next)
        temp = temp->next;
    delete temp->next;
    temp->next = NULL;
    return head; 
}

// delete the node with a given value
Node* deleteByValue(Node* head, int val) {
    if (head == NULL)
        return NULL;
    if (head->data == val)
        return head->next;
    
    Node* prev = head;
    Node* curr = head->next;
    while (curr) {
        if (curr->data == val) {
            prev->next = curr->next;
            delete curr;
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    return head;
}

// delete the kth position node
Node* deleteKthNode(Node* head, int k) {
    if (head == NULL)
        return NULL;
    if (k == 1)
        return head->next;

    Node* prev = head;
    Node* curr = head->next;
    int cnt = 1;
    while(curr) {
        cnt++;
        if (cnt == k) {
            prev->next = curr->next;
            delete curr;
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    return head;
}

// insert new node at head
Node* insertHead(Node* head, int el) {
    return new Node(el, head);
}

// insert new node at tail
Node* insertTail(Node* head, int el) {
    if (head == NULL)
        return new Node(el);
    Node* curr = head;
    while (curr->next) {
        curr = curr->next;
    }
    curr->next = new Node(el);
    return head;
}

// insert new node at position K
Node* insertAtK(Node* head, int el, int k) {
    if (k == 1) 
        return new Node(el, head);
    else if (head == NULL)
        return NULL;
    
    Node* curr = head;
    int cnt = 0;
    while (curr) {
        cnt++;
        if (cnt == k-1) {
            Node* temp = new Node(el);
            temp->next = curr->next;
            curr->next = temp;
            break;
        }
        curr = curr->next;
    }
    return head;
}

// insert new node before the given value 
Node* insertBeforeValue(Node* head, int el, int val) {
    if (head == NULL)
        return NULL;
    if (head->data == val)
        return new Node(el, head);

    Node* curr = head;
    while(curr->next) {
        if (curr->next->data == val) {
            Node* temp = new Node(el);
            temp->next = curr->next;
            curr->next = temp;
            break;
        }
        curr = curr->next;
    }
    return head;
}

// insert new node after the given value
Node* insertAfterValue(Node* head, int el, int val) {
    if (head == NULL)
        return NULL;
    
    Node* curr = head;
    while(curr) {
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
    return 0;
}