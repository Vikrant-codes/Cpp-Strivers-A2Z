#include <iostream>
#include <unordered_map>

using namespace std;

int main() {
    // same as map but it doesn't store elements in order. Keys are unique but not ordered/sorted.
    // Difference b/w map & unordered_map is same as difference b/w set & unordered_set
    // Time Complexity : O(1) but worst case : O(n)
    unordered_map<int,int> ump;
    // In maps we can even take pairs as keys but in unordered_map we can't take pairs as keys .. only int, double, char, long etc can be used

    // same as multimap but it doesn't store elements in order. Keys are not unique and not ordered/sorted.
    unordered_multimap<int, int> ummp;

}