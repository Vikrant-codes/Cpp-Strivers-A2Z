#include <iostream>
#include <unordered_set>

using namespace std;

int main() {
    // unoredred_set is similar to set but it does not store elements in ordered manner.
    // It stores only distinct elements.
    // Time Complexity : O(1) for insertion, deletion and searching but can be O(n) in worst case when higher collisions occur.
    unordered_set<int> ust;

    // unoredred_multiset is similar to multiset but it does not store elements in ordered manner.
    unordered_multiset<int> umst;

    // all functions same as set but lower_bound and upper_bound don't work

}