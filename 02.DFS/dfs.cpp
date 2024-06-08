#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> v;
vector <string> color;
vector <int> parent;

void DFS(int source)
{
    int u = source;
    color[u] = "gray";

    for (int i = 0; i < v[u].size(); i++)
    {
        int x = v[u][i];
        if (color[x] == "white")
        {
            parent[x] = u;
            DFS(x);
        }
    }
    color[u] = "black";
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
    color.resize(n+1, "white");
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
        if (color[i] == "white")
            DFS(i);
    }

    for (int i = 1; i <= n; i++)
    {
        cout << i << " = " << color[i] << endl;
    }

    path(10);

    return 0;
}



/*

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