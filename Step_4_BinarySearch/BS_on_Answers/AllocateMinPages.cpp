/*
GFG - Allocate Minimum Pages : Medium

Given an array arr[] of integers, where each element arr[i] represents the number of pages in the i-th book. 
You also have an integer k representing the number of students. 

The task is to allocate books to each student such that:
-> Each student receives atleast one book.
-> Each student is assigned a contiguous sequence of books.
-> No book is assigned to more than one student.

The objective is to minimize the maximum number of pages assigned to any student. In other words, out of all possible allocations, 
find the arrangement where the student who receives the most pages still has the smallest possible maximum.

Note: If it is not possible to allocate books to all students, return -1.

Examples :-

Input: arr[] = [12, 34, 67, 90], k = 2 __ Output: 113
Explanation: Allocation can be done in following ways:
=> [12] and [34, 67, 90] Maximum Pages = 191
=> [12, 34] and [67, 90] Maximum Pages = 157
=> [12, 34, 67] and [90] Maximum Pages = 113.
The third combination has the minimum pages assigned to a student which is 113.

Input: arr[] = [15, 17, 20], k = 5 __ Output: -1
Explanation: Since there are more students than total books, it's impossible to allocate a book to each student.

Constraints: 1 ≤ arr.size() ≤ 10^6 __ 1 ≤ arr[i], k ≤ 10^3
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach : Binary Search : Time Complexity : O(n * log (sum - max)) __ Space Complexity : O(1)
/*
We need to assign books to students in such a way that the maximum no. of pages assigned to any student is minimized. 
Also each student must receive at least 1 book and each student is assigned a contiguous sequence of books.
No book should be left unassigned. Each book can be assigned to only one student but a student can have more than 1 book. 

Impossible Case :- When the no. of students is greater than the no. of books i.e. k > arr.size(), it's impossible to allocate books to students.

We use Binary Search to approach this problem. 
We know that the minimum pages that can be assigned to any student in any case is max(arr) and the maximum pages that can be assigned is sum(arr).
So we keep low = max(arr), high = sum(arr) and find mid. Check whether it is possible to allocate books to students with maximum pages as 'mid'. 
If yes, we reduce the search space to the left half (high = mid - 1). If it's not then we reduce search space to the right (low = mid + 1). 
*/

/*
isPossible(vector<int> &arr, int k, int pages) : function that returns true if it's possible to allocate books to students with maximum pages as 'pages'.

initially 1 student is allocated book and when the total pages assigned exceeds 'pages' we increment the no of students. 
Count the total students required and check if this cnt exceeds the available students k. 

We loop through the array and count the no of students that would be needed to allocate books with maximum pages as 'pages'.
Initialize sum as 0 and cnt as 1. Loop through the array and check if sum + current_element > pages. 
If yes, we need a new student to allocate this new book to, so we update the cnt and reset the sum as sum = curr_element. 
Else, we simply add the current_element to sum. 
This way after the loop ends we can check how many students would be needed to allocate books with maximum pages as 'pages'. 
If this count of students is greater than available students k, return false since it's not possible to allocate books. 

Ex -> Consider books = {10,20,30,15,5} and k = 2;
Say we take pages as 40 and check whether it's possible or not. 
x : 10 __ sum + x = 10, cnt = 1, sum = 10 
x : 20 __ sum + x = 30, cnt = 1, sum = 30
x : 30 __ sum + x = 60, cnt = 2, sum = 30
x : 15 __ sum + x = 45, cnt = 3, sum = 15
x : 5 __ sum + x = 20, cnt = 3, sum = 20
The student required is 3 which can be allocated books as [10,20], [30], [15,5]. But since k = 2, it's not possible to allocate books.

Say we take pages as 80 and check whether it's possible or not. Since the whole array sum is 80 all the books can then be assigned to 1 student only. 
so student_required (sr) will be 1 which is sr <= k. So it's possible. 
allocation can be done to 1 student as [10,20,30,15,5] and we have 2 students so it's much easier to allocate 80 pages to 2 students.

Say pages = 50. Then
x : 10 __ sum + x = 10, cnt = 1, sum = 10
x : 20 __ sum + x = 30, cnt = 1, sum = 30
x : 30 __ sum + x = 60, cnt = 2, sum = 30
x : 15 __ sum + x = 45, cnt = 3, sum = 15
x : 5 __ sum + x = 20, cnt = 3, sum = 20
*/

bool isPossible(vector<int> &arr, int k, int pages) {
    int sum = 0;
    int cnt = 1;
    for (int x : arr) {
        if (sum + x > pages) {
            cnt++;
            sum = x;
        }
        else sum += x;
    }
    return cnt <= k;
}

int findPages(vector<int> &arr, int k) {
    int n = arr.size();
    if (n < k) return -1;       // impossible case

    int low = *max_element(arr.begin(), arr.end());
    int high = accumulate(arr.begin(), arr.end(), 0);

    if (k == 1) return high;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (isPossible(arr, k, mid)) high = mid - 1;
        else low = mid + 1;
    }
    return low;
}

int main() {
    vector<int> arr = {12, 34, 67, 90};
    int k = 4;
    cout << "Minimum pages: " << findPages(arr, k) << endl;

    return 0;
}