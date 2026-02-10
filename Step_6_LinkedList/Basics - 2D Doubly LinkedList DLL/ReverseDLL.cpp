#include <bits/stdc++.h>
using namespace std;

class Node{
public:
    Node* prev;
    int data;
    Node* next;

    Node(int val) : Node(nullptr, val, nullptr){}

    Node(Node* p, int val, Node* n) {
        prev = p;
        data = val;
        next = n;
    }
};

Node* createDLL(vector<int>& arr) {
    if (arr.empty()) return NULL;
    Node* head = new Node(arr[0]);
    Node* temp = head;
    for (int i = 1; i < arr.size(); i++) {
        Node* newNode = new Node(temp, arr[i], nullptr);
        temp->next = newNode;
        temp = newNode;
    }
    return head;
}

void traverseDLL(Node* head) {
    Node* temp = head;
    while (temp) {
        cout << " <- " << temp->data << " -> ";
        temp = temp->next;
    }
    cout << '\n';
}

Node* reverseDLL(Node* head) {
    if (head == NULL || head->next == NULL)
        return head;
    Node* curr = head;

    while (true) {
        // swap the next & prev of curr Node
        Node* temp = curr->next;
        curr->next = curr->prev;
        curr->prev = temp;

        if (curr->prev)
            curr = curr->prev;
        else
            return curr;
    }
}

Node* reverseDLL2(Node* head) {
    if (head == NULL || head->next == NULL)
        return head;
    Node* curr = head;

    while (curr->next) {
        // swap the next & prev of curr Node
        Node* temp = curr->next;
        curr->next = curr->prev;
        curr->prev = temp;

        curr = curr->prev;
    }

    // now curr is pointing to the last node (whose next is NULL) and this would become newHead (prev will become NULL)
    curr->next = curr->prev;
    curr->prev = nullptr;

    return curr;
}


int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    Node* head = createDLL(arr);
    traverseDLL(head);

    head = reverseDLL2(head);
    traverseDLL(head);

    return 0;
}