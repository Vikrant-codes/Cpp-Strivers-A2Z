/*
Leetcode - 160. Intersection of Two Linked Lists : Easy

Given the heads of two singly linked-lists headA and headB, return the node at which the two lists intersect. 
If the two linked lists have no intersection at all, return null.

For example, the following two linked lists begin to intersect at node c1:
A:      a1 → a2 
                \ 
                  c1 → c2 → c3
                /
B: b1 → b2 → b3

The test cases are generated such that there are no cycles anywhere in the entire linked structure.
Note that the linked lists must retain their original structure after the function returns.

Custom Judge:
The inputs to the judge are given as follows (your program is not given these inputs):
• intersectVal - The value of the node where the intersection occurs. This is 0 if there is no intersected node.
• listA - The first linked list.
• listB - The second linked list.
• skipA - The number of nodes to skip ahead in listA (starting from the head) to get to the intersected node.
• skipB - The number of nodes to skip ahead in listB (starting from the head) to get to the intersected node.
The judge will then create the linked structure based on these inputs and pass the two heads, headA and headB to your program. 
If you correctly return the intersected node, then your solution will be accepted.

Examples :-

Input: intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
Output: Intersected at '8'
Explanation: The intersected node's value is 8 (note that this must not be 0 if the two lists intersect).
From the head of A, it reads as [4,1,8,4,5]. From the head of B, it reads as [5,6,1,8,4,5]. 
There are 2 nodes before the intersected node in A; There are 3 nodes before the intersected node in B.
- Note that the intersected node's value is not 1 because the nodes with value 1 in A and B (2nd node in A and 3rd node in B) 
  are different node references. In other words, they point to two different locations in memory, 
  while the nodes with value 8 in A and B (3rd node in A and 4th node in B) point to the same location in memory.


Input: intersectVal = 2, listA = [1,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
Output: Intersected at '2'
Explanation: The intersected node's value is 2 (note that this must not be 0 if the two lists intersect).
From the head of A, it reads as [1,9,1,2,4]. From the head of B, it reads as [3,2,4]. 
There are 3 nodes before the intersected node in A; There are 1 node before the intersected node in B.


Input: intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
Output: No intersection
Explanation: From the head of A, it reads as [2,6,4]. From the head of B, it reads as [1,5]. 
Since the two lists do not intersect, intersectVal must be 0, while skipA and skipB can be arbitrary values.
Explanation: The two lists do not intersect, so return null.

Constraints :-
• The number of nodes of listA is in the m.
• The number of nodes of listB is in the n.
• 1 <= m, n <= 3 * 10^4
• 1 <= Node.val <= 10^5
• 0 <= skipA <= m
• 0 <= skipB <= n
• intersectVal is 0 if listA and listB do not intersect.
• intersectVal == listA[skipA] == listB[skipB] if listA and listB intersect.

Follow up: Could you write a solution that runs in O(m + n) time and use only O(1) memory?
*/

#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// Brute Force Approach : Time Complexity : O(m * n) __ Space Complexity : O(1)
/*
- We know intersection means a common attribute present between two entities. Here, we have linked lists as given entities. 
- We can't consider the common attribute to be a node's value as the multiple nodes with different references can have same value
- So, we must consider the node itself as the attribute.
- To find the common node, we can traverse one list and check whether the current node also exists in second list.
- The first node that exists in both the list is our intersection point.

Steps:-
1. Traverse listA
2. For each node of listA, check if it exists in ListB also, do:
    - Traverse listB and check if current ListB node the same as current listA node.
    - If yes, return this node as the intersection point
3. If loop ends, return NULL as no intersection point is found.
*/
ListNode *getIntersectionNodeBrute(ListNode *headA, ListNode *headB) {
    ListNode* currA = headA;

    // Traverse ListA
    while (currA) {
        // For each node of ListA, check if it exists in ListB also
        ListNode* currB = headB;
        while (currB) {
            if (currA == currB)
                return currA;
            currB = currB->next;        // move current node of listB forward
        }

        currA = currA->next;            // move current node of listA forward
    }

    return NULL;
}

// Better Approach (Using HashSet) : Time Complexity : O(m + n) __ Space Complexity : O(m + n)
/*
- Use a set to check for the intersection point.
- The nodes' value can't be used to check for the intersection point as values can be duplicates also.
- So, we must consider the memory references to check for the intersection point.
- Thus, the set must be defined to store ListNode pointers.
- Traverse ListA and store its nodes in the set.
- Now, traverse the other linked list (ListB) and find the first node which is present in ListA also.
- For every node of ListB, check if it already exists in the set. If yes, it is the intersection node.
- If the traversal of ListB ends and no intersection node is found: return NULL
*/
ListNode *getIntersectionNodeSet(ListNode *headA, ListNode *headB) {
    unordered_set<ListNode *> s;

    ListNode* curr = headA;
    while (curr) {
        s.insert(curr);
        curr = curr->next;
    }

    curr = headB;
    while (curr) {
        if (s.count(curr)) 
            return curr;
        s.insert(curr);
        curr = curr->next;
    }

    return NULL;
}

// Better Approach : Time Complexity : O(m) + O(n) + O( max(m, n) ) __ Space Complexity : O(1)
/*
Core Idea
• If two singly linked lists intersect, they share the same tail part.
• The only reason we may not detect the intersection immediately is because the lists may have different lengths.
• So first, we make both pointers start from an equal distance from the end.

Intuition
1. Intersection means same node, not same value
    We compare t1 == t2 (address comparison), because intersection means both lists point to the exact same memory node.
2. Lengths may be different. Suppose:
    List A length = len1 = 7
    List B length = len2 = 5
    If we start together, the longer list has a 2-node advantage.
3. Cover the extra lead so that the two pointers are at equal distances from the end.
    - Move the pointer of the longer list ahead by diff (= abs( len1 - len2) ) steps.
    - Now both pointers are equally far from the end.
4. Final traversal
    - Move both pointers one step at a time.
    - First time t1 == t2, that node is the intersection.
    - If loop ends → no intersection.

>> Why this works
After alignment:
    -> Remaining nodes in both lists = same count.
    -> If intersection exists, both pointers will enter the common part at the same time.
    -> If no intersection exists, both will reach NULL together.

>> Visualization
A:  a1 → a2 → a3 → c1 → c2
B:       b1 → c1 → c2
Length A = 5
Length B = 3
Diff = abs(length A - length B) = 2
Move A pointer 2 steps ahead since 'A' is the larger list
Now both pointers have 3 nodes left → final traversal starts with list A's node 'a3' and list B's node 'b1'
both traversal pointers move simultaneously -> they meet at c1.

>> Time Complexity Analysis
- O(m) : to calculate length of list1
- O(n) : to calculate length of list2
- Now, we move 'diff' steps ahead in the longer list and then traverse the list from that point to get the common node
    Thus, we are traversing the larger list in this step. So, time complexity of this step = O( max(m, n) ) 
*/

// My Implementation
ListNode *getIntersectionNode1(ListNode *headA, ListNode *headB) {
    int l1 = 0, l2 = 0;
    ListNode *t1 = headA, *t2 = headB;      // pointers to traverse the two lists
    // find length of list1
    while (t1) {
        l1++;
        t1 = t1->next;
    }
    // find length of list2
    while (t2) {
        l2++;
        t2 = t2->next;
    }
    
    int diff = abs(l1 - l2);
    t1 = headA, t2 = headB;
    for (int i = 0; i < diff; i++) {
        // if list1 is longer than list2, t1 should move (l1 - l2) steps ahead
        if (l1 > l2) 
            t1 = t1->next;
        // else t2 should move ahead
        else
            t2 = t2->next;
    }

    // Now, move both t1 & t2 at the same time and we return the first common node encountered
    // both pointers will become NULL at same time so we can use either of the pointer for while condition
    while (t1) {
        if (t1 == t2)
            return t1;
        t1 = t1->next;
        t2 = t2->next;
    }
    
    return NULL;
}

// Striver's Implementation
// helper function which finds the collision/intersection of two linked lists
// assuming that listA is smaller than listB and 'steps' is the difference in length of the two lists
ListNode *collisionPoint(ListNode *listA, ListNode *listB, int steps) {
    ListNode *t1 = listA, *t2 = listB;
    // move the larger list's (which is listB) pointer (t2) 'steps' ahead
    while (steps) {
        t2 = t2->next;
        steps--;
    }
    // now move both pointers together till they become equal
    while (t1 != t2) {
        t1 = t1->next;
        t2 = t2->next;
    }
    // if no intersection point, both t1 & t2 would become NULL and loop will exit and NULL is returned
    return t1;
}

ListNode *getIntersectionNode2(ListNode *headA, ListNode *headB) {
    int l1 = 0, l2 = 0;
    ListNode *t1 = headA, *t2 = headB;      // pointers to traverse the two lists
    // find length of list1
    while (t1) {
        l1++;
        t1 = t1->next;
    }
    // find length of list2
    while (t2) {
        l2++;
        t2 = t2->next;
    }
    // if list1 is smaller
    if (l1 < l2)
        return collisionPoint(headA, headB, l2-l1);
    // else list2 is smaller
    else 
        return collisionPoint(headB, headA, l1-l2);
}

// Optimal Approach (Two Pointer Switching Trick) : Time Complexity : O(m + n) __ Space Complexity : O(1)
/*
✅ Core Idea
• Traverse both lists using two pointers.
• When a pointer reaches the end of its list, redirect it to the other list's head.
• Eventually:
    • Either they meet at the intersection node
    • Or both become NULL (no intersection)
*/
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    ListNode *t1 = headA, *t2 = headB;

    while (t1 != t2) {
        t1 = t1->next;
        t2 = t2->next;
    
        if (t1 == t2) return t1;
        if (t1 == NULL) t1 = headB;
        if (t2 == NULL) t2 = headA; 
    }
    
    return t1;
}

int main() {
    return 0;
}