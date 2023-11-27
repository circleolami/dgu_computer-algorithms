#include <iostream>
#include <vector>
#include <random>

using namespace std;

vector<vector<int>> generate_symmetric_matrix(int n, double p)
{
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    random_device rd;
    mt19937 gen(rd());
    bernoulli_distribution dist(p);

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (dist(gen))
            {
                matrix[i][j] = 1;
                matrix[j][i] = 1;
            }
        }
    }

    return matrix;
}

vector<vector<int>> matrix_to_adjacency_list(const vector<vector<int>> &matrix)
{
    int n = matrix.size();
    vector<vector<int>> adj_list(n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == 1)
            {
                adj_list[i].push_back(j);
            }
        }
    }

    return adj_list;
}

void dfs(int v, vector<bool> &visited, const vector<vector<int>> &graph)
{
    visited[v] = true;

    for (int u : graph[v])
    {
        if (!visited[u])
        {
            dfs(u, visited, graph);
        }
    }
}

int count_connected_components(const vector<vector<int>> &graph)
{
    int n = graph.size();
    vector<bool> visited(n, false);
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            dfs(i, visited, graph);
            count++;
        }
    }

    return count;
}

int main()
{
    int n;
    double p;
    cin >> n >> p;

    auto matrix = generate_symmetric_matrix(n, p);
    auto adj_list = matrix_to_adjacency_list(matrix);
    int components = count_connected_components(adj_list);

    cout << "연결 성분의 수: " << components << endl;

    return 0;
}
