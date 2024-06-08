#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int,int>>> adj;
vector<int> dist;
vector<int> prev_node;

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

bool bellman_ford(int n, int source)
{
    initialize(n, source);

    for (int i = 1; i <= n-1; i++)
    {
        for (int u = 1; u <= n; u++)
        {
            for (int v = 0; v < adj[u].size(); v++)
            {
                relax(u, adj[u][v].first, adj[u][v].second);
            }
        }
    }

    for (int u = 1; u <= n; u++)
    {
        for (int j = 0; j < adj[u].size(); j++)
        {
            int v = adj[u][j].first;
            int w = adj[u][j].second;

            if (dist[v] > dist[u] + w)
                return false;
        }
    }
    return true;
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

    if (bellman_ford(n, source))
    {
        shortestPath(source, dest);
        cout << "\nCost: " << dist[dest] << endl;
    }
    else
    {
        cout << "Graph contains negative cycle(s)" << endl;
    }

    return 0;
}


/*

5 10
1 2 10
1 4 5
2 4 2
2 3 1
3 5 4
4 2 3
4 3 9
4 5 2
5 1 7
5 3 6

*/