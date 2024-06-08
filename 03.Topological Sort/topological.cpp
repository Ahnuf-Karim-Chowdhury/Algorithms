#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int,int>>> v; //adjacency list that stores pairs of vertices and weights
vector <string> color;
vector<int> dist;
vector<int> prev_node;
deque <int> topo;

void DFS(int source)
{
    int u = source;
    color[u] = "gray";

    for (int i = 0; i < v[u].size(); i++)
    {
        int x = v[u][i].first;
        if (color[x] == "white")
        {
            DFS(x);
        }
    }
    color[u] = "black";
    topo.push_front(u);
}

void initialize(int n, int source)
{
    dist.resize(n+1, INT_MAX);
    prev_node.resize(n+1, -1);
    dist[source] = 0;
}

void relax(int u, int v, int w)
{
    if (dist[u] != INT_MAX && dist[v] > dist[u] + w)
    {
        dist[v] = dist[u] + w;
        prev_node[v] = u;
    }
}

void printPath(int source, int dest)
{
    if (dist[dest] == INT_MAX)
    {
        cout << "No path from " << source << " to " << dest << endl;
        cout << "Cost: infinity" << endl;
        exit(0);
    }

    if (source != dest)
    {
        printPath(source, prev_node[dest]);
    }
    cout << dest << " ";
}

void shortestPath(int n, int source, int dest)
{
    initialize(n, source);

    for (int i = 0; i < topo.size(); i++)
    {
        int u = topo[i];
        for (int j = 0; j < v[u].size(); j++)
        {
            relax(u, v[u][j].first, v[u][j].second);
        }
    }
    cout << "Shortest path: ";
    printPath(source, dest);
    cout << "\nCost of path: " << dist[dest];
}

int main(void)
{
    int n,e;
    cin >> n >> e;

    v.resize(n+1);
    color.resize(n+1, "white");


    int nodeA, nodeB, weight;
    for (int i = 0; i < e; i++)
    {
        cin >> nodeA >> nodeB >> weight;
        v[nodeA].push_back(make_pair(nodeB,weight));
    }

    for (int i = 1; i <= n; i++)
    {
        if (color[i] == "white")
            DFS(i);
    }

    cout << "Topologically sorted: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << topo[i] << " ";
    }

    cout << "\nEnter a source and destination: " << endl;
    int source,dest;
    cin >> source >> dest;

    shortestPath(n, source, dest);

    return 0;
}



/*

6 10
1 3 3
1 2 5
2 3 2
2 4 6
3 4 7
3 5 4
3 6 2
4 5 -1
4 6 1
5 6 -2

*/