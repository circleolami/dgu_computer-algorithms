#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void dfs(int v, vector<bool> &visited, vector<vector<int>> &graph)
{
    visited[v] = true;
    cout << v << " ";

    for (int u : graph[v])
    {
        if (!visited[u])
        {
            dfs(u, visited, graph);
        }
    }
}

void bfs(int start, vector<vector<int>> &graph)
{
    vector<bool> visited(graph.size(), false);
    queue<int> q;

    q.push(start);
    visited[start] = true;

    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        cout << v << " ";

        for (int u : graph[v])
        {
            if (!visited[u])
            {
                q.push(u);
                visited[u] = true;
            }
        }
    }
}

int main()
{
    int n, m, start;
    cin >> n >> m >> start;

    vector<vector<int>> graph(n + 1);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for (int i = 1; i <= n; i++)
    {
        sort(graph[i].begin(), graph[i].end());
    }

    vector<bool> visited(n + 1, false);

    cout << "DFS: ";
    dfs(start, visited, graph);
    cout << endl;

    cout << "BFS: ";
    bfs(start, graph);
    cout << endl;

    return 0;
}
