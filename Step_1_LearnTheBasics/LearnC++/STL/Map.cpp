#include <iostream>
#include <map>
#include <utility>

using namespace std;

int main(){
    // Map stores key-value pairs in a sorted order based on the keys. Keys are unique.
    // Time complexity (Best, Worst & Average): O(log n)
    map<int, int> mpp1;
    map<int, pair<int, int>> mpp2;
    map<pair<int, int>, int> mpp3;
    
    // Insertion

    mpp1[1] = 2;        // Stores key : 1 and value : 2
    mpp1.emplace(3,4);  // Stores key : 3 and value : 4 
    mpp1.insert({5,6}); // Stores key : 5 and value : 6
    // mpp1 = { {1, 2}, {3, 4}, {5, 6} }

    mpp2[1] = {2, 3};   // Stores key : 1 and value : {2, 3}
    mpp2.emplace(4, make_pair(5, 6));    // Stores key : 4 and value : {5, 6}
    mpp2.insert({7, {8, 9}});   // Stores key : 7 and value : {8, 9}
    // mpp2 = { {1, {2, 3}}, {4, {5, 6}}, {7, {8, 9}} }
    
    mpp3[{1, 2}] = 3;   // Stores key : {1, 2} and value : 3
    mpp3.emplace(make_pair(4, 5), 6);   // Stores key : {4, 5} and value : 6
    mpp3.insert({{7,8}, 9});    // Stores key : {7, 8} and value : 9
    // mpp3 = { {{1, 2}, 3}, {{4, 5}, 6}, {{7, 8}, 9} }

    cout << "Map 1" << endl;
    for (auto x : mpp1) cout << x.first << " : " << x.second << "\t";
    cout << endl << "Map 2" << endl;
    for (auto x : mpp2) cout << x.first << " : " << x.second.first << " - " << x.second.second << "\t";
    cout << endl << "Map 3" << endl;
    for (auto x : mpp3) cout << x.first.first << " - " << x.first.second << " : " << x.second << "\t";

    // Accessing values using keys : map[key]
    cout << endl << "Map 1 value for key = 3 : " << mpp1[1] << endl;
    cout << "Map 1 value for key = 7 : " << mpp1[7] << endl; // 0 is returned as value if key doesn't exists
    // this is because if key doesn't exist then doing mpp[key] will insert the key with a default value (0 for int) and this value is returned.

    cout << "Map 2 value for key = 4 : {" << mpp2[4].first << "," << mpp2[4].second << "}" << endl;
    cout << "Map 3 value for key = {7,8} : " << mpp3[{7,8}] << endl;

    // Find function :
    // If the key exists: The iterator points to the key-value pair.
    // If the key does not exist: The iterator points to map.end().
    auto it1 = mpp1.find(3);
    auto it2 = mpp2.find(4);
    auto it3 = mpp3.find({7,8});
    /*In a map, each element is stored as a key-value pair. The find function in a map returns an iterator pointing to the element (if the key exists). 
    The element is the key-value pair represented as a std::pair where: first refers to the key, second refers to the value.
    If the element doesn't exist then we can check whether mpp.find(element) == mpp.end() .. if it is true then element doesn't exist.

    When you use it->first & it->second, you are accessing the key and value of the key-value pair that the iterator it is pointing to, 
    because the iterator 'it' points to a std::pair inside the map.
    */
    cout << "Map 1 find 3 : " << it1->first << " - " << it1->second << endl;
    cout << "Map 2 find 4 : " << it2->first << " - " << it2->second.first << " : " << it2->second.second << endl;
    cout << "Map 3 find {7,8} : " << it3->first.first << " - " << it3->first.second << " : " << it3->second << endl;

    // Lower bound and Upper bound
    auto lbit = mpp1.lower_bound(3); // Returns iterator to the first element whose key is not less than 3
    cout << "Lower Bound of 3 in map 1 : " << lbit->first << " - " << lbit->second << endl;
    auto ubit = mpp1.upper_bound(3); // Returns iterator to the first element whose key is greater than 3
    cout << "Upper Bound of 3 in map 1 : " << ubit->first << " - " << ubit->second << endl;
    
    // erase swap size empty are same as others
}