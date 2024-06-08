#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> v;
vector <int> level;
vector <int> parent;
bool flag = false;

void BFS(int source)
{
    level[source] = 0;
    queue <int> q;
    q.push(source);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int j = 0; j < v[u].size(); j++)
        {
            int x = v[u][j];
            if (level[x] == -1)
            {
                parent[x] = u;
                level[x] = level[u] + 1;
                q.push(x);
            }
            else if (x != parent[u] && parent[x] != u && level[x] != level[u])
            {
                flag = true;
            }
        }
    }
}

void path(int node)
{
    if (node != parent[node])
    {
        path(parent[node]);
    }
    cout << node << endl;
}

int main(void)
{
    int n,e;
    cin >> n >> e;

    v.resize(n+1);
    level.resize(n+1, -1);
    parent.resize(n+1);

    for (int i = 1; i <= n; i++)
    {
        parent[i] = i;
    }

    int nodeA, nodeB;
    for (int i = 0; i < e; i++)
    {
        cin >> nodeA >> nodeB;
        v[nodeA].push_back(nodeB);
        v[nodeB].push_back(nodeA);
    }

    for (int i = 1; i <= n; i++)
    {
        cout << i << "->";
        for (int j = 0; j < v[i].size(); j++)
        {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 1; i <= n; i++)
    {
        if (level[i] == -1)
            BFS(i);
    }

    for (int i = 1; i <= n; i++)
    {
        cout << i << " = " << level[i] << endl;
    }

    //path(5);

    if (flag)
        cout << "Cycle Found!" << endl;
    else
        cout << "No cycle!" << endl;

    return 0;
}


/*

10 12
1 2
1 4
1 3
2 6
6 10
4 7
3 8
7 8
7 9
9 10
8 5
10 5



10 13
1 2
1 4
1 3
2 6
6 10
3 7
4 7
3 8
7 8
7 9
9 10
8 5
10 5

*/


/* 
Input Graph
The input edges represent an undirected graph:

mathematica
Copy code
A B
A C
C D
C E
Step-by-Step Execution
Graph Construction

The graph is represented using an adjacency list.
Nodes are mapped to integers for simplicity. Let's assume:
A = 1
B = 2
C = 3
D = 4
E = 5
Based on these mappings, the edges translate to:

Copy code
1 2
1 3
3 4
3 5
Adjacency List Representation

After reading the edges, the adjacency list v will look like:
css
Copy code
v[1] = [2, 3]
v[2] = [1]
v[3] = [1, 4, 5]
v[4] = [3]
v[5] = [3]
Initialization

level vector is initialized with -1 for each node indicating unvisited:
css
Copy code
level = [-1, -1, -1, -1, -1, -1]
parent vector is initialized with each node being its own parent:
css
Copy code
parent = [0, 1, 2, 3, 4, 5]
BFS Traversal

Let's run BFS starting from node 1 (A).

Initialize BFS:

css
Copy code
level[1] = 0
queue = [1]
First Iteration:

Dequeue node 1:
makefile
Copy code
u = 1
queue = []
Process neighbors of 1 (nodes 2 and 3):
For neighbor 2:
css
Copy code
parent[2] = 1
level[2] = level[1] + 1 = 1
queue = [2]
For neighbor 3:
css
Copy code
parent[3] = 1
level[3] = level[1] + 1 = 1
queue = [2, 3]
Second Iteration:

Dequeue node 2:
makefile
Copy code
u = 2
queue = [3]
Process neighbors of 2 (only node 1):
Node 1 is the parent of 2, no cycle detected.
Third Iteration:

Dequeue node 3:
makefile
Copy code
u = 3
queue = []
Process neighbors of 3 (nodes 1, 4, 5):
For neighbor 1:
Node 1 is the parent of 3, no cycle detected.
For neighbor 4:
css
Copy code
parent[4] = 3
level[4] = level[3] + 1 = 2
queue = [4]
For neighbor 5:
css
Copy code
parent[5] = 3
level[5] = level[3] + 1 = 2
queue = [4, 5]
Fourth Iteration:

Dequeue node 4:
makefile
Copy code
u = 4
queue = [5]
Process neighbors of 4 (only node 3):
Node 3 is the parent of 4, no cycle detected.
Fifth Iteration:

Dequeue node 5:
makefile
Copy code
u = 5
queue = []
Process neighbors of 5 (only node 3):
Node 3 is the parent of 5, no cycle detected.
Cycle Detection

No cycle is detected during the BFS traversal since all neighbors either haven't been visited before or are direct parents in the BFS tree.
Final Output

Levels of nodes:
css
Copy code
level = [-1, 0, 1, 1, 2, 2]
No cycle detected, so the output is "No cycle!".
Conclusion
The BFS correctly traverses the graph, updating levels and parents while checking for cycles. The given input graph doesn't contain any cycles, and the BFS traversal confirms this by ensuring no node is revisited at a different level through a different parent. The final output indicates no cycle is found.
 */


/* 

Recap of BFS Traversal
Given the graph with edges:

mathematica
Copy code
A B
A C
C D
C E
We mapped the nodes to integers:

A = 1
B = 2
C = 3
D = 4
E = 5
The translated edges are:

Copy code
1 2
1 3
3 4
3 5
Adjacency List
The adjacency list representation after reading the edges:

css
Copy code
v[1] = [2, 3]
v[2] = [1]
v[3] = [1, 4, 5]
v[4] = [3]
v[5] = [3]
BFS Traversal and Parent Array Update
Let's walk through the BFS traversal again and see how the parent array is updated.

Initialization

parent vector is initialized with each node being its own parent:
css
Copy code
parent = [0, 1, 2, 3, 4, 5]
BFS from Node 1

Initialize BFS:

css
Copy code
level[1] = 0
queue = [1]
parent = [0, 1, 2, 3, 4, 5]
First Iteration:

Dequeue node 1:
makefile
Copy code
u = 1
queue = []
Process neighbors of 1 (nodes 2 and 3):
For neighbor 2:
css
Copy code
parent[2] = 1
level[2] = 1
queue = [2]
For neighbor 3:
css
Copy code
parent[3] = 1
level[3] = 1
queue = [2, 3]
Updated parent array:

css
Copy code
parent = [0, 1, 1, 1, 4, 5]
Second Iteration:

Dequeue node 2:
makefile
Copy code
u = 2
queue = [3]
Process neighbors of 2 (only node 1):
Node 1 is the parent of 2, no update.
Updated parent array remains the same:

css
Copy code
parent = [0, 1, 1, 1, 4, 5]
Third Iteration:

Dequeue node 3:
makefile
Copy code
u = 3
queue = []
Process neighbors of 3 (nodes 1, 4, 5):
For neighbor 1:
Node 1 is the parent of 3, no update.
For neighbor 4:
css
Copy code
parent[4] = 3
level[4] = 2
queue = [4]
For neighbor 5:
css
Copy code
parent[5] = 3
level[5] = 2
queue = [4, 5]
Updated parent array:

css
Copy code
parent = [0, 1, 1, 1, 3, 3]
Fourth Iteration:

Dequeue node 4:
makefile
Copy code
u = 4
queue = [5]
Process neighbors of 4 (only node 3):
Node 3 is the parent of 4, no update.
Updated parent array remains the same:

css
Copy code
parent = [0, 1, 1, 1, 3, 3]
Fifth Iteration:

Dequeue node 5:
makefile
Copy code
u = 5
queue = []
Process neighbors of 5 (only node 3):
Node 3 is the parent of 5, no update.
Updated parent array remains the same:

css
Copy code
parent = [0, 1, 1, 1, 3, 3]
Final Parent Array
After completing the BFS traversal, the parent array is:

css
Copy code
parent = [0, 1, 1, 1, 3, 3]
Explanation of the Parent Array
parent[1] = 1: Node 1 is its own parent (root of the BFS tree).
parent[2] = 1: Node 2's parent is node 1.
parent[3] = 1: Node 3's parent is node 1.
parent[4] = 3: Node 4's parent is node 3.
parent[5] = 3: Node 5's parent is node 3.
This reflects the BFS traversal starting from node 1 and correctly indicates the parent of each node in the BFS tree.


4o
 */

/* And the mapping of nodes to integers:

A = 1
B = 2
C = 3
D = 4
E = 5
After BFS traversal, the parent array is:

css
Copy code
parent = [0, 1, 1, 1, 3, 3]
Let's find the path from different nodes to the root (assuming BFS started from node 1, which corresponds to A).

Path from Node D (4)
To find the path from node D (4) back to the root:

Call path(4):
Since parent[4] = 3 and 4 != 3, it calls path(3).
Call path(3):
Since parent[3] = 1 and 3 != 1, it calls path(1).
Call path(1):
Since parent[1] = 1 and 1 == 1, it prints 1.
After returning from the recursive calls, it prints 3 and then 4.

So, the output is:

Copy code
1
3
4
This corresponds to the path A -> C -> D.

Path from Node E (5)
To find the path from node E (5) back to the root:

Call path(5):
Since parent[5] = 3 and 5 != 3, it calls path(3).
Call path(3):
Since parent[3] = 1 and 3 != 1, it calls path(1).
Call path(1):
Since parent[1] = 1 and 1 == 1, it prints 1.
After returning from the recursive calls, it prints 3 and then 5.

So, the output is:

Copy code
1
3
5
This corresponds to the path A -> C -> E.

Path from Node B (2)
To find the path from node B (2) back to the root:

Call path(2):
Since parent[2] = 1 and 2 != 1, it calls path(1).
Call path(1):
Since parent[1] = 1 and 1 == 1, it prints 1.
After returning from the recursive call, it prints 2.

So, the output is:

Copy code
1
2
This corresponds to the path A -> B.

Summary
The path function works by recursively following the parent array from the given node back to the root node. It prints the nodes along the path in order from the root to the given node. For the given input graph, the function correctly identifies and prints paths such as A -> C -> D and A -> C -> E based on the BFS traversal and the resulting parent array.
 */