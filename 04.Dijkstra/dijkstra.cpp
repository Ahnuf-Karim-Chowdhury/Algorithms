#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int,int>>> adj;
vector<int> dist;
vector<int> prev_node;
vector<bool> explored;

void initialize(int n, int source)
{
    dist.resize(n+1, INT_MAX);
    prev_node.resize(n+1, -1);
    explored.resize(n+1, false);
    dist[source] = 0;
}

void relax(int u, int v, int w)
{
    if (dist[v] > dist[u] + w)
    {
        dist[v] = dist[u] + w;
        prev_node[v] = u;
    }
}


int extract_min(int n)
{
    int min = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!explored[i] && dist[i] <= dist[min])
        {
            min = i;
        }
    }
    explored[min] = true;
    return min;
}


void dijkstra(int n, int source, int dest)
{
    initialize(n, source);
    for (int i = 0; i < n; i++)
    {
        int u = extract_min(n);

        for (int j = 0; j < adj[u].size(); j++)
        {
            int v = adj[u][j].first;
            int w = adj[u][j].second;
            relax(u, v, w);
        }
    }
}

void shortestPath(int source, int dest)
{
    if (dest != source)
    {
        shortestPath(source, prev_node[dest]);
    }
    cout << dest << " ";
}

int main(void)
{
    int n,e;
    cin >> n >> e;

    adj.resize(n+1);

    int nodeA, nodeB, w;

    for (int i = 0; i < e; i++)
    {
        cin >> nodeA >> nodeB >> w;
        adj[nodeA].push_back(make_pair(nodeB,w));
    }

    int source, dest;
    cout << "Enter source and destination: ";
    cin >> source >> dest;

    dijkstra(n, source, dest);

    shortestPath(source, dest);

    cout << "\nCost: " << dist[dest] << endl;

    return 0;
}


/*

5 7
1 4 5
2 4 2
2 3 1
3 5 4
4 3 9
4 5 2
5 1 7

*/

/* 
4 4
2 3 4
0 2 6
0 1 10
1 3 15
 */