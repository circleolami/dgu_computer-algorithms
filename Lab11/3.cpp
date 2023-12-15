#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <limits>
#include <queue>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Point
{
    int x, y;
    vector<int> closest; // 인접한 점들의 인덱스
};

// 두 점 사이의 거리 계산
double distance(const Point &a, const Point &b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// N개의 점에 대해 랜덤한 좌표를 생성
vector<Point> generatePoints(int N)
{
    vector<Point> points(N);
    set<pair<int, int>> used;
    for (int i = 0; i < N; ++i)
    {
        int x, y;
        do
        {
            x = rand() % 101;
            y = rand() % 101;
        } while (!used.insert({x, y}).second);
        points[i] = {x, y};
    }
    return points;
}

// 각 점에 대해 가장 가까운 m개의 점을 찾음
void findClosestPoints(vector<Point> &points, int m)
{
    int N = points.size();
    for (int i = 0; i < N; ++i)
    {
        vector<pair<double, int>> dists;
        for (int j = 0; j < N; ++j)
        {
            if (i != j)
            {
                double dist = distance(points[i], points[j]);
                dists.push_back({dist, j});
            }
        }
        sort(dists.begin(), dists.end());
        for (int j = 0; j < m && j < dists.size(); ++j)
        {
            points[i].closest.push_back(dists[j].second);
        }
    }
}

// Dijkstra 알고리즘을 사용하여 최단 경로 찾기
vector<int> dijkstra(const vector<Point> &points, int start, int end)
{
    int N = points.size();
    vector<double> minDist(N, numeric_limits<double>::max());
    vector<int> prev(N, -1);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;

    minDist[start] = 0;
    pq.push({0, start});

    while (!pq.empty())
    {
        int u = pq.top().second;
        double distU = pq.top().first;
        pq.pop();

        if (distU > minDist[u])
            continue;

        for (int i : points[u].closest)
        {
            double dist = distance(points[u], points[i]);
            if (minDist[i] > minDist[u] + dist)
            {
                minDist[i] = minDist[u] + dist;
                prev[i] = u;
                pq.push({minDist[i], i});
            }
        }
    }

    vector<int> path;
    for (int at = end; at != -1; at = prev[at])
    {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    if (path.size() == 1 && path[0] != start)
    {
        return {}; // 경로 없음
    }
    return path;
}

int main()
{
    srand(time(NULL));
    int N, m;
    cin >> N >> m;

    vector<Point> points = generatePoints(N);
    findClosestPoints(points, m);

    vector<int> path = dijkstra(points, 0, N - 1);
    if (path.empty())
    {
        cout << "경로 없음" << endl;
    }
    else
    {
        for (int idx : path)
        {
            cout << "(" << points[idx].x << ", " << points[idx].y << ") ";
        }
        cout << endl;
    }

    return 0;
}
