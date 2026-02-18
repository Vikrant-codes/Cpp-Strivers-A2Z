/*
| Segregate even and odd nodes in LinkedList

Leetcode - 328. Odd Even Linked List : Medium

Given the head of a singly linked list, group all the nodes with odd indices together 
followed by the nodes with even indices, and return the reordered list.
The first node is considered odd, and the second node is even, and so on.
Note that the relative order inside both the even and odd groups should remain as it was in the input.
You must solve the problem in O(1) extra space complexity and O(n) time complexity.

Examples :-
Input: head = [1,2,3,4,5]
Output: [1,3,5,2,4]

Input: head = [2,1,3,5,6,4,7]
Output: [2,3,6,7,1,5,4]

Constraints :-
• The number of nodes in the linked list is in the range [0, 104].
• -10^6 <= Node.val <= 10^6
*/

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Naive Approach : Time Complexity : O(2*n) __ Space Complexity : O(n)
/*
Core Idea :-
Use an array to store the odd nodes’ data first and then the even nodes’ data.
Iterate through the linked list and update each node’s value according to the order stored in the array. 

🔹Basic Steps
- If the linked list contains 0 or 1 node, return it as it is.
- Create an array to store node values.
- Traverse the linked list starting from the head and push all odd-positioned node values into the array.
- Traverse the linked list starting from the second node and push all even-positioned node values into the array.
- Traverse the linked list again and replace each node’s value with values from the array in order.
- Return the head of the linked list.

-> Time Complexity Analysis:
To get the odd Nodes' data, we iterate the odd nodes only: O(n / 2)
To get the even Nodes' data, we iterate the even nodes only: O(n / 2)
O(n) to traverse the linkedlist. 
Total Time complexity = O(n/2) + O(n/2) + O(n) = O(2*n)
*/
ListNode* oddEvenListNaive(ListNode* head) {
    if (head == NULL || head->next == NULL)
        return head;

    vector<int> arr;
    // push the odd nodes' values in the array first
    ListNode* curr = head;
    while (curr != NULL && curr->next != NULL) {
        arr.push_back(curr->val);
        curr = curr->next->next;
    }
    /*
    The while loop runs only when both curr and curr->next exist, because we move two steps ahead (curr = curr->next->next).
    If the linked list has an odd number of nodes, the last odd node will have curr != NULL but curr->next == NULL. 
    In this case, the loop stops before adding this last node.
    */
    if (curr) arr.push_back(curr->val);     
    // This condition is used to add the last node's data that could have been skipped when the loop terminated.

    // now push the even nodes' values in the array... same procedure as for odd, just start the loop from second node this time
    curr = head->next;
    while (curr != NULL && curr->next != NULL) {
        arr.push_back(curr->val);
        curr = curr->next->next;
    }
    if (curr) arr.push_back(curr->val);

    int i = 0;
    curr = head;
    while (curr) {
        curr->val = arr[i];
        i++;
        curr = curr->next;
    }
    return head;
}

// My Code: Time Complexity : O(n) __ Space Complexity : O(1)
/*
| Core Idea
We want to connect odd nodes together and even nodes together by connecting the curr node to 2 nodes further (curr->next->next),
this way an odd node will connect to the next odd node and even node will connect to the next even node. 
This iteration stops when we reach the second last node (because their is no curr->next->next). 
But the second last node still connects to last node (we must change this connection) 
- if this second last node is odd, it must connect to the first even node (initial head->next), or
- if it's even , it must point to null but the last node (tail which is curr->next) must point to the first even node

For any node curr, we want to connect its next to curr->next->next.
At every step we effectively do: 
    curr->next = curr->next->next
which means:
- odd node connects to next odd node
- even node connects to next even node

But, there is one problem, if we do curr->next = curr->next->next, then the original next node becomes unreachable
so, we use a temp variable to store this next nodes address and move to the next node using this temp

So during traversal: 1 → 2 → 3 → 4 → 5 → 6 → 7
becomes logically:
- odd chain : 1 → 3 → 5 → 7
- even chain: 2 → 4 → 6 → 7 (temporarily still linked)
We stop when: curr->next->next == NULL, i.e., at the second last node.
At this point one incorrect link still exists: 
    (second last) → (last) 
and we fix that using parity.
We use a counter variable to know whether the second last node is odd or even.

Case 1 — total nodes odd: Second last node is even
(second last) → (last) => (even) → (odd) → NULL
the second last (even node) points to last (odd node). 
So, we want to firstly make this second last (even node) point to NULL and 
also need to make the last (odd node) point to the first even node (which was initially head->next)

Case 2 — total nodes even: Second last node is odd
(second last) → (last) => (odd) → (even) → NULL
the even node already points to NULL and we just need to make the second last (odd node) point to first even node
*/
ListNode* oddEvenListMyCode(ListNode* head) {
    // if linked list contains 0 / 1 / 2 nodes, return it as it is
    if (head == NULL || head->next == NULL || head->next->next == NULL) 
        return head;
    
    ListNode* curr = head;
    int cnt = 1;
    ListNode* second = head->next;
    while (curr->next->next) {
        ListNode* temp = curr->next;
        curr->next = temp->next;
        curr = temp;
        cnt++;
    }
    // if cnt is even, means the second last node is evenNode, means total nodes are odd in number
    if (cnt % 2 == 0) {
        ListNode* temp = curr->next;
        curr->next = NULL;
        temp->next = second;
    }
    else {
        curr->next = second;
    }
    return head;
}

// Strivers' Code: Time Complexity : O(n) __ Space Complexity : O(1)
/*
The logic is similar -- connect odd nodes and even nodes and at the end connect the last odd node to first even node.
but, the implementation differs.

✅ Intuition (Core Idea)
Maintain two pointers: one building the odd-indexed chain and one building the even-indexed chain.
After separating both chains in-place, attach the even list after the odd list.

🔹 Implementation Explanation
1. Initialization
    ListNode* odd = head;
    ListNode* even = head->next;
    ListNode* evenHead = head->next;
- odd points to the first odd node.
- even points to the first even node.
- evenHead is stored to reconnect later.

2. Main Loop
    while(even && even->next)
- The loop runs while another pair of odd and even nodes exists ahead.
- (In a pair of odd-even nodes, odd node is always followed by even node so we just run till odd-even node pair exists)

3. Connecting Even & Odd nodes 
- We connect the even nodes to the next even and odd nodes to the next odd using curr->next->next
- After that we move the even and odd to the newly added even odd nodes

4. Final Connection
    odd->next = evenHead;
- Attach the even list after the odd list.

✅ Why is the condition while (even && even->next)?
We check only the even pointer because:
- In every iteration, we update odd first, then even.
- If even exists and even->next exists,
    - it guarantees there is a next odd node available.
    - so both connecting steps are safe.
In short: If a valid even node and its next exist, the next odd node must also exist.
So checking even is enough to safely move both pointers.

🔹 How it works for different lengths
🟢 Case 1: Even number of nodes
Example: 1 → 2 → 3 → 4 → 5 → 6
Iteration flow:
    odd: 1 → 3 → 5
    even: 2 → 4 → 6
At node 6:
    even = 6
    even->next = NULL
Condition fails → loop stops.
Now: odd = 5, even = 6
Final step: odd->next = evenHead
Result: 1 → 3 → 5 → 2 → 4 → 6

🟢 Case 2: Odd number of nodes
Example: 1 → 2 → 3 → 4 → 5
Iteration flow:
    odd: 1 → 3 → 5
    even: 2 → 4
At node 4:
    even = 4
    even->next = 5
Loop runs one more time:
    odd becomes 5
    even becomes NULL
Now: even = NULL
Condition fails → loop stops.
Final: odd = 5, even = NULL, odd->next = evenHead
Result: 1 → 3 → 5 → 2 → 4
*/
ListNode* oddEvenList(ListNode* head) {
    if (head == NULL || head->next == NULL)
        return head;

    ListNode* odd = head;
    ListNode* even = head->next;
    ListNode* evenHead = head->next;

    while(even && even->next) {
        odd->next = odd->next->next;
        even->next = even->next->next;

        odd = odd->next;
        even = even->next;
    }
    odd->next = evenHead;

    return head;
}

int main() {
    return 0;
}