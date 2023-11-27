#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <limits>
#include <chrono>

using namespace std;
const int INF = numeric_limits<int>::max();

vector<vector<pair<int, int>>> generate_weighted_graph(int n, double p)
{
    vector<vector<pair<int, int>>> graph(n);
    random_device rd;
    mt19937 gen(rd());
    bernoulli_distribution dist(p);

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (dist(gen))
            {
                int weight = rand() % 10 + 1;
                graph[i].push_back(make_pair(j, weight));
                graph[j].push_back(make_pair(i, weight));
            }
        }
    }

    return graph;
}

vector<pair<int, int>> prim_algorithm(const vector<vector<pair<int, int>>> &graph)
{
    int n = graph.size();
    vector<bool> visited(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;
    vector<pair<int, int>> mst;

    min_heap.push({0, 0});

    while (!min_heap.empty())
    {
        pair<int, int> top = min_heap.top();
        int u = top.second;
        int weight = top.first;
        min_heap.pop();

        if (visited[u])
            continue;
        visited[u] = true;

        if (u != 0)
        {
            mst.push_back({u, weight});
        }

        for (const pair<int, int> &edge : graph[u])
        {
            int v = edge.first;
            int w = edge.second;

            if (!visited[v])
            {
                min_heap.push({w, v});
            }
        }
    }

    return mst;
}

int main()
{
    int n;
    double p;
    cin >> n >> p;

    auto start = chrono::high_resolution_clock::now();

    auto graph = generate_weighted_graph(n, p);
    auto mst = prim_algorithm(graph);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> elapsed = end - start;

    cout << "실행 시간: " << elapsed.count() << " microseconds" << endl;

    for (const pair<int, int> &edge : mst)
    {
        cout << "(" << edge.first << "," << edge.second << ") ";
    }
    cout << endl;

    return 0;
}
