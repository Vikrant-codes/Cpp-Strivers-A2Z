/*
GFG - Sort a linked list of 0s, 1s and 2s : Medium

Given the head of a linked list where nodes can contain values 0s, 1s, and 2s only. 
Your task is to rearrange the list so that all 0s appear at the beginning, followed by all 1s, and all 2s are placed at the end.

Examples :-

Input: head = 1 → 2 → 2 → 1 → 2 → 0 → 2 → 2
Output: 0 → 1 → 1 → 2 → 2 → 2 → 2 → 2

Input: head = 2 → 2 → 0 → 1
Output: 0 → 1 → 2 → 2

Constraints :-
- 1 ≤ no. of nodes ≤ 10^6
- 0 ≤ node->data ≤ 2
*/

#include <bits/stdc++.h>
using namespace std;

/* Node is defined as
  class Node {
  public:
    int data;
    Node* next;

    Node(int x) {
        data = x;
        next = nullptr;
    }
};
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

/*
Approach :-
- Count the no. of occurrences of 0s, 1s and 2s.
- Let a = count of 0, b = count of 1, c = count of 2
- Re-write the list's nodes' data such that the first 'a' nodes contain 0, the next 'b' nodes have 1 and rest have 2.
- In this way, the 0s are shifted to start and 2 at the end.

Time Complexity : O(2*n)
- O(n) to count the no. of occurrences of 0s, 1s and 2s
- Another traversal O(n) to re-write the node data.

Space Complexity : O(1) 
*/

Node* segregateA(Node* head) {
    int cnt0 = 0, cnt1 = 0, cnt2 = 0;
    
    // count the no. of occurrences of 0, 1 and 2
    Node* curr = head;
    while (curr) {
        if (curr->data == 0) cnt0++;
        else if (curr->data == 1) cnt1++;
        else cnt2++;
        curr = curr->next;
    }
    
    curr = head;
    
    // re-write 0
    while (cnt0) {
        curr->data = 0;
        curr = curr->next;
        cnt0--;
    }
        
    // re-write 1
    while (cnt1) {
        curr->data = 1;
        curr = curr->next;
        cnt1--;
    }
        
    // re-write 2
    while (cnt2) {
        curr->data = 2;
        curr = curr->next;
        cnt2--;
    }
        
    return head;
}

Node* segregateB(Node* head) {
    int cnt0 = 0, cnt1 = 0, cnt2 = 0;
    
    // count the no. of occurrences of 0, 1 and 2
    Node* curr = head;
    while (curr) {
        if (curr->data == 0) cnt0++;
        else if (curr->data == 1) cnt1++;
        else cnt2++;
        curr = curr->next;
    }
    
    curr = head;
    
    while (curr) {
        if (cnt0) {
            curr->data = 0;
            cnt0--;
        }
        else if (cnt1) {
            curr->data = 1;
            cnt1--;
        }
        else {
            curr->data = 2;
            cnt2--;
        }
        curr = curr->next;
    }
        
    return head;
}

Node* segregateC(Node* head) {
    vector<int> freq(3);
        
    // count the no. of occurrences of 0, 1 and 2
    Node* curr = head;
    while (curr) {
        freq[curr->data]++;
        curr = curr->next;
    }
        
    int i = 0;
    curr = head;
    while (curr) {
        if (i < freq[0]) 
            curr->data = 0;
        else if (i < freq[0] + freq[1]) 
            curr->data = 1;
        else 
            curr->data = 2;
        
        curr = curr->next;
        i++;
    }
        
    return head;
}

// Optimal Solution: Time Complexity : O(n) __ Space Complexity : O(1)
/*
- Use three dummy nodes to create 3 chains (0s chain, 1s chain and 2s chain)
- Traverse the linked list and join 0 nodes to 0s-chain, 1 nodes to 1s-chain and 2 nodes to 2s-chain
- At the end link the three chains together such that 0s → 1s → 2s.
- Delete the dummy nodes (optional).
- Return the head (which is the first node of 0s chain i.e. dummy0->next).

>> Edge-Case handling
⚠ What Problem Can Arise?
When we split the list into three chains:
0s: dummy0 → ...
1s: dummy1 → ...
2s: dummy2 → ...
Some chains might be empty.

Example cases:-

Case 1️⃣: No 1s
0s: dummy0 → a → b
1s: dummy1 → NULL
2s: dummy2 → e → f

Problem:
If we blindly connect 0s chain to 1s chain :- t0->next = dummy1->next;
Since dummy1->next = NULL,
the 0-chain would stop there and 2-chain would get disconnected.

Case 2️⃣: No 0s
0s: dummy0 → NULL
1s: dummy1 → c → d
2s: dummy2 → e → f

Problem:
If we return dummy0->next, it would return NULL.
We would lose the entire list.

✅ How Code Handles It
The key is this order:
- t1->next = dummy2->next;
- t0->next = dummy1->next;

🔹 Why connecting 1 → 2 first is important
If 1-chain is empty:
- t1 == dummy1
- So dummy1->next = dummy2->next
That means: dummy1 now directly points to 2-chain
So even though 1-chain is empty, dummy1->next is NOT NULL anymore.

🔹 Then connect 0 → 1
t0->next = dummy1->next;
Now: 
- If 1 exists → 0 → 1
- If 1 does NOT exist → dummy1->next already points to 2
    So: 0 → 2 (automatically handled)
No need to use conditionals to handle edge cases.

🔎 Case: No 0s Present
Initial chains after distribution:
0s: dummy0 → NULL
1s: dummy1 → c → d
2s: dummy2 → e → f

Important pointer positions:
t0 == dummy0
t1 points to last 1
t2 points to last 2

Step 1️⃣: Connect 1 → 2
t1->next = dummy2->next;
Now: 1-chain: dummy1 → c → d → e → f
Even if 1-chain was empty:
- t1 == dummy1
- So dummy1->next = dummy2->next
- Still works.

Step 2️⃣: Connect 0 → 1
t0->next = dummy1->next;
Since: t0 == dummy0
dummy1->next points to first 1 (or first 2 if 1s are empty)
So now: dummy0 → c → d → e → f

Step 3️⃣: Return Head
    return dummy0->next;
dummy0->next now correctly points to:
- First 1 (if no 0s)
- Or first 2 (if no 0s and no 1s)
*/
Node* segregate(Node* head) {
    if (head == NULL || head->next == NULL) return head;
    
    // Create dummy nodes for three lists: 0s, 1s, and 2s
    Node* dummy0 = new Node(-1);        // dummy chain for 0 nodes
    Node* dummy1 = new Node(-1);        // dummy chain for 1 nodes
    Node* dummy2 = new Node(-1);        // dummy chain for 2 nodes
    
    Node *t0 = dummy0, *t1 = dummy1, *t2 = dummy2;
    // traversal pointers for the dummy chains of 0s, 1s & 2s
    
    // Traverse original list and distribute nodes into 0s, 1s, or 2s list
    Node* curr = head;
    while (curr) {
        Node* nextNode = curr->next;    // save next
        curr->next = NULL;              // break old link
        
        if (curr->data == 0) {
            t0->next = curr;
            t0 = curr;
        }
        
        else if (curr->data == 1) {
            t1->next = curr;
            t1 = curr;
        }
        
        else {
            t2->next = curr;
            t2 = curr;
        }
        
        curr = nextNode;
    }
    
    // edge-case handling: in case when either 0-chain or 1-chain or 2-chain is empty
    // we firstly connect the 1-chain to 2-chain 
    // (so if 1-chain is empty, then, 0-chain will automatically get connected to 2-chain)
    
    // connect last node of 1-chain to first node of 2-chain
    t1->next = dummy2->next;            // Connect 1s → 2s
    // if 1-chain is empty, t1 points to dummy1, so dummy1 next becomes dummy2 next
    
    // connect last node of 0-chain to first node of 1-chain
    t0->next = dummy1->next;
    // if 1-chain was empty, then this dummy1->next is actually link to 2-chain
    
    head = dummy0->next;            // head
    
    // delete the dummy nodees
    delete dummy0;
    delete dummy1;
    delete dummy2;
    
    return head;            // head
}

int main() {
    return 0;
}