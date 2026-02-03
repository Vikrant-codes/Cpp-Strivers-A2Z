/*
Leetcode - 1436. Destination City : Easy

You are given the array paths, 
where paths[i] = [cityAi, cityBi] means there exists a direct path going from cityAi to cityBi. 
Return the destination city, that is, the city without any path outgoing to another city.

It is guaranteed that the graph of paths forms a line without any loop, 
therefore, there will be exactly one destination city.

Examples :-

Input: paths = [["London","New York"],["New York","Lima"],["Lima","Sao Paulo"]] __ Output: "Sao Paulo" 
Explanation: Starting at "London" city you will reach "Sao Paulo" city which is the destination city. 
Your trip consist of: "London" -> "New York" -> "Lima" -> "Sao Paulo".

Input: paths = [["B","C"],["D","B"],["C","A"]] __ Output: "A"
Explanation: All possible trips are: 
"D" -> "B" -> "C" -> "A". 
"B" -> "C" -> "A". 
"C" -> "A". 
"A". 
Clearly the destination city is "A".

Input: paths = [["A","Z"]] __ Output: "Z"

Constraints :-
- 1 <= paths.length <= 100
- paths[i].length == 2
- 1 <= cityAi.length, cityBi.length <= 10
- cityAi != cityBi
- All strings consist of lowercase and uppercase English letters and the space character.
*/

#include<bits/stdc++.h>
using namespace std;

// Hashing Approach : Time Complexity : O(n) __ Space Complexity : O(n)
/*
🧠 Intuition
Each path is of the form: [from, to]
You are guaranteed that :
• There is exactly one destination city
• The destination city is never a source city
So the problem reduces to :
| Find the city that never appears as a starting point (from).

💡 Key Observation
• Every city except the destination appears at least once as a source
• The destination city appears only as a destination, never as a source
So:
1. Collect all source cities
2. Find the city that appears as a destination but not in the source set

🧩 Algorithm
1. Create an empty hash set source_cities
2. Traverse all paths:
    • Insert route[0] (source city) into the set
3. Traverse all paths again:
    • If route[1] (destination city) is not in the set, return it
4. Return empty string (fallback, though problem guarantees one destination)

⏱️ Complexity Analysis
Let n = number of paths

⏳ Time Complexity
• First loop (collect sources): O(n)
• Second loop (find destination): O(n)
• Hash set operations: O(1) average
✅ Total Time → O(n)

💾 Space Complexity
Hash set stores up to n cities → O(n)
*/
string destCity(vector<vector<string>>& paths) {
    unordered_set<string> source_cities;
    for (auto& route : paths) {
        string cityA = route[0];
        string cityB = route[1];
        source_cities.insert(cityA);
    }
    for (auto& route : paths) {
        if (source_cities.count(route[1]) == 0)
            return route[1];
    }
    return "";
}

int main() {
    return 0;
}