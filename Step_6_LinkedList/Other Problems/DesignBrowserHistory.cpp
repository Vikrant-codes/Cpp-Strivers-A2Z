/*
Leetcode - 1472. Design Browser History : Medium

You have a browser of one tab where you start on the homepage and you can visit another url, 
get back in the history number of steps or move forward in the history number of steps.

Implement the BrowserHistory class:
    - BrowserHistory(string homepage) Initializes the object with the homepage of the browser.
    - void visit(string url) Visits url from the current page. It clears up all the forward history.
    - string back(int steps) Move steps back in history. 
        If you can only return x steps in the history and steps > x, you will return only x steps. 
        Return the current url after moving back in history at most steps.
    - string forward(int steps) Move steps forward in history. 
        If you can only forward x steps in the history and steps > x, you will forward only x steps. 
        Return the current url after forwarding in history at most steps.

Example:

Input:
["BrowserHistory","visit","visit","visit","back","back","forward","visit","forward","back","back"]
[["leetcode.com"],["google.com"],["facebook.com"],["youtube.com"],[1],[1],[1],["linkedin.com"],[2],[2],[7]]
Output:
[null,null,null,null,"facebook.com","google.com","facebook.com",null,"linkedin.com","google.com","leetcode.com"]

Explanation:
BrowserHistory browserHistory = new BrowserHistory("leetcode.com");
browserHistory.visit("google.com");       // You are in "leetcode.com". Visit "google.com"
browserHistory.visit("facebook.com");     // You are in "google.com". Visit "facebook.com"
browserHistory.visit("youtube.com");      // You are in "facebook.com". Visit "youtube.com"
browserHistory.back(1);                   // You are in "youtube.com", move back to "facebook.com" return "facebook.com"
browserHistory.back(1);                   // You are in "facebook.com", move back to "google.com" return "google.com"
browserHistory.forward(1);                // You are in "google.com", move forward to "facebook.com" return "facebook.com"
browserHistory.visit("linkedin.com");     // You are in "facebook.com". Visit "linkedin.com"
browserHistory.forward(2);                // You are in "linkedin.com", you cannot move forward any steps.
browserHistory.back(2);                   // You are in "linkedin.com", move back two steps to "facebook.com" then to "google.com". return "google.com"
browserHistory.back(7);                   // You are in "google.com", you can move back only one step to "leetcode.com". return "leetcode.com"


Constraints :-
• 1 <= homepage.length <= 20
• 1 <= url.length <= 20
• 1 <= steps <= 100
• homepage and url consist of  '.' or lower case English letters.
• At most 5000 calls will be made to visit, back, and forward.
*/

#include <bits/stdc++.h>
using namespace std;

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */


// Implementation Using Stack

/*
INTUITION:

We simulate real browser navigation using 2 stacks.
1. backStack : Stores pages behind the current page.
2. forwardStack : Stores pages ahead of the current page.
-> current : (string) Stores the currently opened webpage.

---------------------------------------------------
VISIT(url)
---------------------------------------------------

Suppose:
backStack   = [leetcode, google]
current     = facebook
forwardStack= [youtube]

If we visit linkedin:

1. Current page (facebook) becomes part of back history, so push it into backStack.
2. Update current = linkedin.
3. Any forward history becomes invalid because after visiting a new page, browser cannot go forward to old pages anymore.

So clear forwardStack.

Result:
backStack   = [leetcode, google, facebook]
current     = linkedin
forwardStack= []

---------------------------------------------------
BACK(steps)
---------------------------------------------------

When moving back:
1. Current page should become part of forward history, because we may come back to it later using forward().
2. Top page from backStack becomes the new current page.
Repeat this at most 'steps' times or until backStack becomes empty.

---------------------------------------------------
FORWARD(steps)
---------------------------------------------------

When moving forward:
1. Current page should now become part of back history.
2. Top page from forwardStack becomes the new current page.
Repeat this at most 'steps' times or until forwardStack becomes empty.

---------------------------------------------------
WHY STACKS WORK?
---------------------------------------------------

Browser navigation always works with the MOST RECENT previous/next page first.
This is exactly LIFO behavior, which makes stacks a natural fit.

---------------------------------------------------
COMPLEXITIES
---------------------------------------------------

visit()   -> O(1) amortized
back()    -> O(steps)
forward() -> O(steps)

Space -> O(history size)
*/

class BrowserHistory1 {
public:
    string current;
    stack<string> backStack;
    stack<string> forwardStack;

    BrowserHistory1(string homepage) {
        current = homepage;     
    }
    
    void visit(string url) {
        backStack.push(current);
        current = url;
        
        // clear forward Stack
        while(!forwardStack.empty()) {
            forwardStack.pop();
        }
        // we could also use 
        // forwardStack = {};
        // or, fowardStack = stack<string> {};
        // to clear the stack's content 
    }
    
    string back(int steps) {
        while(steps-- && !backStack.empty()) {
            forwardStack.push(current);
            current = backStack.top();
            backStack.pop();
        }
        return current;
    }
    
    string forward(int steps) {
        while(steps-- && !forwardStack.empty()) {
            backStack.push(current);
            current = forwardStack.top();
            forwardStack.pop();
        }
        return current;
    }
};

/*
INTUITION:
Instead of storing current page separately, this approach keeps the CURRENT PAGE always at the TOP of currentBackStack.

So:
currentBackStack -> contains current page + all back history
forwardStack -> contains pages available for forward navigation

---------------------------------------------------
HOW STACKS REPRESENT HISTORY
---------------------------------------------------

Example:
currentBackStack: [leetcode, google, facebook]
TOP = facebook (current page)
This means:
- leetcode -> oldest visited page
- google   -> previous page
- facebook -> current page
If we go back once: Move facebook from currentBackStack to forwardStack.
currentBackStack: [leetcode, google]
forwardStack: [facebook]
Now current page becomes google (top of currentBackStack).

---------------------------------------------------
VISIT(url)
---------------------------------------------------

When visiting a new page:
1. Push new page into currentBackStack. It automatically becomes current page.
2. Clear forwardStack because after visiting a new page, old forward history becomes invalid.

Example:
Before:
currentBackStack = [leetcode, google]
forwardStack     = [facebook]
visit("youtube")
After:
currentBackStack = [leetcode, google, youtube]
forwardStack     = []

---------------------------------------------------
BACK(steps)
---------------------------------------------------

To move back:
1. Current page (top of currentBackStack) should become available for forward navigation, so move it into forwardStack.
2. New top of currentBackStack becomes current page.

We stop when:
- steps become 0
OR
- only one page remains in currentBackStack because homepage cannot be removed.

---------------------------------------------------
FORWARD(steps)
---------------------------------------------------

To move forward:
1. Take top page from forwardStack.
2. Push it into currentBackStack.
That pushed page automatically becomes the new current page.
Repeat this at most 'steps' times or until forwardStack becomes empty.

---------------------------------------------------
IMPORTANT OBSERVATION
---------------------------------------------------

Top of currentBackStack ALWAYS represents the currently opened webpage.
So: currentBackStack.top() directly gives current page at any moment.

---------------------------------------------------
COMPLEXITIES
---------------------------------------------------

visit()   -> O(1)
back()    -> O(steps)
forward() -> O(steps)

Space -> O(total history)
*/
class BrowserHistory2 {
public:
    stack<string> currentBackStack;
    stack<string> forwardStack;

    BrowserHistory2(string homepage) {
        currentBackStack.push(homepage);      
    }
    
    void visit(string url) {
        currentBackStack.push(url);
        forwardStack = {};      // clear forward Stack
    }
    
    string back(int steps) {
        while (steps-- && currentBackStack.size() != 1) {
            string temp = currentBackStack.top();
            currentBackStack.pop();
            forwardStack.push(temp);
        }
        return currentBackStack.top();
    }
    
    string forward(int steps) {
        while(steps-- && !forwardStack.empty()) {
            string temp = forwardStack.top();
            forwardStack.pop();
            currentBackStack.push(temp);
        }
        return currentBackStack.top();
    }
};

// Using Doubly Linked List

/*
INTUITION:

This approach uses a DOUBLY LINKED LIST to simulate browser history navigation.
Each webpage is represented as a node.

Every node contains:
1. data -> webpage URL
2. prev -> previous visited page
3. next -> next visited page

curr pointer always points to the CURRENTLY OPENED webpage.

---------------------------------------------------
WHY DOUBLY LINKED LIST?
---------------------------------------------------

Browser navigation requires movement in BOTH directions:
1. back() -> move to previous page
2. forward() -> move to next page

A doubly linked list naturally supports this using:
- prev pointer
- next pointer

---------------------------------------------------
HOW HISTORY LOOKS
---------------------------------------------------
Example:

leetcode <-> google <-> facebook <-> youtube
                                      ^
                                    curr
Current page = youtube
If we call back(2):
youtube -> facebook -> google
Now: curr points to google.

---------------------------------------------------
VISIT(url)
---------------------------------------------------
When visiting a new page:
1. Create a new node for the URL.
2. Attach it after current node:
      curr->next = newNode
      newNode->prev = curr
3. Move curr to this new node.
So newly visited page becomes current page.

---------------------------------------------------
IMPORTANT OBSERVATION
---------------------------------------------------
Suppose current history is:
leetcode <-> google <-> facebook
                           ^
                          curr
If we now visit youtube:
leetcode <-> google <-> facebook <-> youtube
                                        ^
                                       curr

If there had been any forward history, it gets disconnected automatically 
because curr->next is overwritten with the new node.
So old forward path becomes unreachable.

---------------------------------------------------
BACK(steps)
---------------------------------------------------
To move backward:
Keep moving curr to curr->prev
until:
- steps become 0
OR
- no previous page exists.

After movement, curr points to current webpage.

---------------------------------------------------
FORWARD(steps)
---------------------------------------------------
To move forward:
Keep moving curr to curr->next
until:
- steps become 0
OR
- no next page exists.

After movement, curr points to current webpage.

---------------------------------------------------
WHY THIS WORKS
---------------------------------------------------
Browser history behaves like a chain where each page knows:
- which page came before it
- which page came after it
Doubly linked list models this perfectly.

---------------------------------------------------
COMPLEXITIES
---------------------------------------------------
visit()   -> O(1)
back()    -> O(steps)
forward() -> O(steps)

Space -> O(total history)
*/

class Node {
public:
    string data;
    Node* next;
    Node* prev;

    Node() : data(""), next(nullptr), prev(nullptr) {}
    Node(string url) : data(url), next(nullptr), prev(nullptr) {}
    Node(string url, Node* next, Node* prev) : data(url), next(next), prev(prev) {}
};

class BrowserHistory {
public:
    Node* curr = NULL;

    BrowserHistory(string homepage) {
        curr = new Node(homepage);    
    }
    
    void visit(string url) {
        Node* temp = new Node(url);
        curr->next = temp;
        temp->prev = curr;
        curr = temp;
    }
    
    string back(int steps) {
        while (steps-- && curr->prev != NULL) {
            curr = curr->prev;
        }
        return curr->data;
    }
    
    string forward(int steps) {
        while(steps-- && curr->next != NULL) {
            curr = curr->next;
        }
        return curr->data;
    }
};

int main() {
    return 0;
}