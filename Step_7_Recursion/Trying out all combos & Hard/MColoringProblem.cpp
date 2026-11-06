/*
GFG - M-Coloring Problem : Medium

Given an undirected graph consisting of V vertices and 
edges represented as a 2d array edges[][], along with an integer m. 
Find if it is possible to color the graph using at most m different colors 
such that no two adjacent vertices share the same color. 

Note: The graph is indexed with 0-based indexing.

Examples :-

Input: V = 4, edges[][] = [[0, 1], [1, 3], [2, 3], [3, 0], [0, 2]], m = 3
Output: true
Explanation: It is possible to color the given graph using 3 colors, 
for example, one of the possible ways vertices can be colored as follows:
Vertex 0: Color 1
Vertex 1: Color 2
Vertex 2: Color 2
Vertex 3: Color 3

Input: V = 3, edges[][] = [[0, 1], [1, 2], [0, 2]], m = 2
Output: false
Explanation: It is not possible to color the given graph using only 2 colors because vertices 0, 1, and 2 form a triangle.

Constraints :-
• V ≤ 10
• 1 ≤ edges.size() ≤ V*(V+1)/2
• 0 ≤ edges[i][j] ≤ V-1
• 1 ≤ m ≤ V
*/

#include <bits/stdc++.h>
using namespace std;

/*
>> Intuition – M-Coloring (Recursion + Backtracking)

We need to assign one of the m available colors to each of the v vertices such that 
no two adjacent vertices have the same color.

We maintain a color vector of size v, where color[i] represents the color assigned to vertex i. 
Initially, all elements are initialized to 0, indicating that no vertex has been colored yet. 
We use colors from 1 to m. This vector keeps track of the current coloring of the graph throughout the recursion.

We use recursion to process the vertices one by one, starting from vertex 0.

For the current vertex, we try all available colors (1 to m). 
Before assigning a color, we check whether any of its adjacent vertices has already been assigned that same color. 

If the color is valid (not been assigned to any adjacent vertex), 
we assign it to the current vertex by updating color[node] = col in the color vector, 
and then make a recursive call for the next vertex (node + 1).

If that recursive call returns true, it means we have successfully colored all the vertices, 
so we return true without making any further changes.

However, if the recursive call returns false, it means the current color choice eventually led to a dead end. 
We therefore undo our previous assignment by resetting color[node] = 0, 
and try the next available color for the current vertex.

If none of the available colors works for the current vertex, we return false, 
allowing the previous recursive call to backtrack and try a different color for its vertex.

This process continues until we either find a valid coloring or exhaust all possibilities.

Base case: When node == v, it means all vertices have been successfully assigned a valid color, so we return true.

-->> Adjacency Matrix – getAdjacencyMatrix()

Since the given graph is represented as an edge list, we first convert it into an adjacency matrix for convenient access.

We initialize a v × v matrix with all zeros. Then, for every edge (u, v) in the given edge list, 
we mark both mat[u][v] and mat[v][u] as 1, indicating that these two vertices are connected.
We mark both directions because the graph is undirected.

This representation allows us to check whether any two vertices are adjacent in O(1) time using mat[u][v].

-->> Checking whether a color is valid – isPossible()

Before assigning a color col to the current vertex node, 
we need to ensure that none of its adjacent vertices has already been assigned the same color.

We iterate through all vertices and check two conditions:
- mat[node][i] == 1: Vertex i is adjacent to the current vertex.
- color[i] == col: Vertex i already has the color we're trying to assign.
If both conditions hold, assigning this color would violate the coloring constraint, so we return false.

Otherwise, if we finish checking all vertices without finding a conflict, 
we return true, meaning the color can safely be assigned.

>> Complexity Analysis

Let:
- V = Number of vertices.
- E = Number of edges.
- M = Number of available colors.

1. Building the adjacency matrix:

- Initializing the matrix takes O(V²).
- Processing all edges takes O(E).

Total: O(V² + E) time.
Space: O(V²) for the adjacency matrix.

2. isPossible():

We iterate through all V vertices to check whether any adjacent vertex already has the given color.

Time: O(V) per call.

3. Recursive solve():

For every vertex, we try at most M colors. In the worst case, we explore all possible color assignments.
Therefore, the number of possible assignments is M^V.
For every attempted color assignment, isPossible() takes O(V) time.

Time: O(V × M^V).

The recursion depth is at most V, and the color array takes O(V) space.

-> Overall Complexity

Complexity       | Value
Time	         | (O(V^2 + E + V × M^V)
Auxiliary space	 | (O(V^2 + V) = O(V^2)

The auxiliary space includes the adjacency matrix, color array and recursion stack.
One important observation: The M^V factor comes from exploring all possible color assignments in the worst case. 
Backtracking helps us prune invalid choices early, but the worst-case exponential complexity remains.
Also, since we stop immediately when a valid coloring is found, 
we might explore considerably fewer possibilities in practice.
*/

// return the adjacency matrix for the graph, which will help us check adjacent vertices easily
vector<vector<int>> getAdjacencyMatrix(int v, vector<vector<int>>& edges) {
    vector<vector<int>> mat(v, vector<int>(v, 0));
    
    for (auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        
        mat[u][v] = 1;
        mat[v][u] = 1;      // since it's an undirected graph, mark an edge for v -> u as well
    }
    
    return mat;
}

// check if it is possible to color the vertex `node` with `col` color
bool isPossible(int node, int v, vector<vector<int>>& mat, vector<int>& color, int col) {
    // for all nodes, check the color of the ones which are adjacent to `node`
    for (int i = 0; i < v; i++) {
        if (i != node && mat[node][i] == 1 && color[i] == col) {
            return false;
        }
    }
    
    return true;
}

// recursive method to color the vertices
bool solve(int node, int v, int m, vector<vector<int>>& mat, vector<int>& color) {
    if (node == v) 
        return true;
        
    for (int col = 1; col <= m; col++) {
        if (isPossible(node, v, mat, color, col)) {
            color[node] = col;
                
            if (solve(node + 1, v, m, mat, color) == true) 
                return true;
            
            color[node] = 0;        // undo the change
        }
    }
    
    return false;
}

bool graphColoring(int v, vector<vector<int>>& edges, int m) {
    vector<vector<int>> mat = getAdjacencyMatrix(v, edges);
    vector<int> color(v, 0);
    
    return solve(0, v, m, mat, color);
}

int main() {
    return 0;
}