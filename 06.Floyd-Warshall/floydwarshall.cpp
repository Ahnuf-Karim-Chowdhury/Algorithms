#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> d, p;

void warshall(int n)
{
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (d[i][k] < INT_MAX && d[k][j] < INT_MAX)
                {
                    if (d[i][j] > d[i][k] + d[k][j])
                    {
                        d[i][j] = d[i][k] + d[k][j];
                        p[i][j] = p[k][j];
                    }
                }
            }
        }
    }
}

void printP(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << p[i][j] << "\t";
        }
        cout << "\n\n";
    }
}

void printShortestPaths(int i, int j)
{
    if (i==j)
        cout << i << " ";
    else if (p[i][j] == -1)
        cout << "No Path exists between " << i << " and " << j << endl;
    else
    {
        printShortestPaths(i, p[i][j]);
        cout << j << " ";
    }
}

void printCost(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << d[i][j] << "\t";
        }
        cout << "\n\n";
    }
}

int main(void)
{
    int n,e;
    cin >> n >> e;
    d.resize(n+1);
    p.resize(n+1);

    for (int i = 1; i <= n; i++)
    {
        d[i].resize(n+1, INT_MAX);
        p[i].resize(n+1, -1);

        d[i][i] = 0;
        p[i][i] = i;
    }

    //graph input
    int nodeA, nodeB, w;
    for (int i = 0; i < e; i++)
    {
        cin >> nodeA >> nodeB >> w;
        d[nodeA][nodeB] = w;
        p[nodeA][nodeB] = nodeA;
    }

    warshall(n);
    printCost(n);


    //printP(n);

    /*for (int i = 1; i <= n; i++)
    {
        cout << "\n";
        for (int j = 1; j <= n; j++)
        {
            printShortestPaths(i,j);
            cout << "\n";
        }
    }*/

    return 0;
}

/*

5 9
1 2 3
1 5 -4
1 3 8
2 4 1
2 5 7
3 2 4
4 3 -5
4 1 2
5 4 6

*/