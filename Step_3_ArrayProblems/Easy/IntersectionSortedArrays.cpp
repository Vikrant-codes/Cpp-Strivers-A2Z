/*
Given two sorted arrays (can have duplicates) ... Find the Intersection of the arrays in sorted order containing only unique values. 
There can be two versions for this problem one where we strictly consider only unique values in Intersection array , and 
the other where we add even duplicates in the Intersection if it is present in both the arrays.
Ex -> Consider a = [1,1,2,4,5,5,6,6,7,8,9,9], b=[1,2,2,3,5,5,6,9,9]
Intersection can either be [1,2,5,6,9] or [1,2,5,5,6,9,9]
[1,2,5,6,9] when we consider only unique values to be present in Intersection
[1,2,5,5,6,9,9] when we consider common appearances in both arrays (5 appears twice in both arrays but 6 appears twice only in array 2 so it's added once only)
*/ 

#include <iostream>
#include <vector>
using namespace std;

// Brute Force Approach --> Time Complexity : O(n * m) __ Space Complexity : O(m)
vector<int> intersectBrute(vector<int> a, vector<int> b){
    int n = a.size();
    int m = b.size();
    int vis[m] = {0};
    vector<int> res;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(a[i] == b[j] && vis[j] == 0){
                res.push_back(a[i]);
                vis[j] = 1;
                break;
            }
            if(b[j] > a[i]){        // since array b is sorted so the element would've existed before and now only bigger elements exist
                break;
            }
        }
    }
    return res;
}

// Optimal Approach : 2 pointer approach --> Time Complexity : O(n + m) __ Space Complexity : O(1)
/*
Somewhat similar to the approach for Union. Here also we are taking 2 pointers for each array and we add the element to the Common vector only when 
a[i] == b[j] i.e. when it is present in both the arrays ... If a[i] > b[j] we increment j hoping that array b might have the element at higher index
Similarly if a[i] < b[j] then we increment i ... Also even if both a[i] & b[j] are same we check the last element of Common (using Common.back() ) before
adding it to the Common array to avoid duplicacy. Also if any array gets exhausted (when i==n or j==m) we don't further do anything because we needed
both the arrays to find the common elements and since one is traversed fully we can't find any further common elements.
*/
vector<int> intersect(vector<int> a, vector<int> b){
    int n = a.size();
    int m = b.size();
    int i=0, j=0;
    vector<int> Common;
    while(i<n && j<m){
        if(a[i] == b[j]){
            Common.push_back(a[i]);
            i++;
            j++;
        }
        else if(a[i] < b[j]) i++;
        else j++;
    }
    return Common;
}

vector<int> intersectStrict(vector<int> a, vector<int> b){
    int n = a.size();
    int m = b.size();
    int i=0, j=0;
    vector<int> Common;
    while(i<n && j<m){
        if(a[i] == b[j]){
            if(Common.size() == 0 || Common.back() != a[i]) Common.push_back(a[i]);
            i++;
            j++;
        }
        else if(a[i] < b[j]) i++;
        else j++;
    }
    return Common;
}

int main() {
    vector<int> a = {1, 1, 2, 2, 3, 3, 5, 5, 8, 8};
    vector<int> b = {2, 2, 3, 4, 5, 5, 6, 7, 8, 8, 8};
    vector<int> Intersection = intersect(a, b);
    cout << "Intersection : ";
    for(int x : Intersection) cout << x << " ";
    
    vector<int> StrictIntersection = intersectStrict(a, b);
    cout << endl << "Strict Intersection : ";
    for(int x : StrictIntersection) cout << x << " ";

    return 0;
}