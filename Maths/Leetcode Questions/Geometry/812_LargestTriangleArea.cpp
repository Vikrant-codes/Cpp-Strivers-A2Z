/*
Leetcode - 812. Largest Triangle Area : Easy

Given an array of points on the X-Y plane points where points[i] = [xi, yi], return the area of the largest triangle that can be formed by 
any three different points. Answers within 10-5 of the actual answer will be accepted.

Examples :-

Input: points = [[0,0],[0,1],[1,0],[0,2],[2,0]] __ Output: 2.00000
Explanation: The five points are shown in the above figure. The red triangle is the largest.

Input: points = [[1,0],[0,0],[0,1]] __ Output: 0.50000

Constraints: 3 <= points.length <= 50 __ -50 <= xi, yi <= 50 __ All the given points are unique.
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach : Time Complexity : O(n^3) __ Space Complexity : O(1)
/*
Approach :- 
For all triplets calculate the area of triangle formed by the points and return the maximum area.

Use the shoelace / determinant formula to compute the area i.e.
for three points (x1, y1), (x2, y2), (x3, y3) the area of triangle formed by these points is given by
Area = 1/2 * | x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2) |
*/
double getArea(vector<int> &A, vector<int> &B, vector<int> &C) {
    int x1 = A[0], y1 = A[1];
    int x2 = B[0], y2 = B[1];
    int x3 = C[0], y3 = C[1];

    double area = (0.5 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)));
    return (area < 0) ? -1 * area : area; 
}

double largestTriangleArea(vector<vector<int>>& points) {
    double mx_area = 0;
    int n = points.size();
    for (int i = 0; i < n-2; i++) {
        for (int j = i+1; j < n-1; j++) {
            for (int k = j+1; k < n; k++) {
                double area = getArea(points[i], points[j], points[k]);
                mx_area = max (area, mx_area);
            }
        }
    }

    return mx_area;
}

int main() {

    return 0;
}