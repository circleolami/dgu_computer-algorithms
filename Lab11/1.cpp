#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const int Nmax = 100;
struct point
{
    char c;
    int x, y;
    float angle;
};

int angleCalcCount = 0; // 각도 계산 횟수
int angleCompCount = 0; // 각도 비교 횟수

float ComputeAngle(point p1, point p2)
{
    angleCalcCount++;
    int dx, dy, ax, ay;
    float t;
    dx = p2.x - p1.x;
    ax = abs(dx);
    dy = p2.y - p1.y;
    ay = abs(dy);
    t = (ax + ay == 0) ? 0 : (float)dy / (ax + ay);
    if (dx < 0)
        t = 2 - t;
    else if (dy < 0)
        t = 4 + t;
    return t * 90.0;
}

void heapify(vector<point>& points, int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n)
    {
        angleCompCount++; // 각도 비교 횟수 증가
        if (points[l].angle > points[largest].angle)
            largest = l;
    }

    if (r < n)
    {
        angleCompCount++; // 각도 비교 횟수 증가
        if (points[r].angle > points[largest].angle)
            largest = r;
    }

    if (largest != i)
    {
        swap(points[i], points[largest]);
        heapify(points, n, largest);
    }
}

void heapSort(vector<point>& points, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(points, n, i);

    for (int i = n - 1; i >= 0; i--)
    {
        swap(points[0], points[i]);
        heapify(points, i, 0);
    }
}

int main()
{
    int N;
    cin >> N;

    vector<point> points(N);
    for (int i = 0; i < N; i++)
    {
        cin >> points[i].c >> points[i].x >> points[i].y;
    }

    // 기준점을 선택 (첫 번째 점)
    point base = points[0];

    // 각도 계산
    for (int i = 0; i < N; i++)
    {
        points[i].angle = ComputeAngle(base, points[i]);
    }

    // 힙 정렬 수행
    heapSort(points, N);
    cout << "다각형이 만들어지는 순서: ";
    // 결과 출력
    for (const auto& p : points)
    {
        cout << p.c << " ";
    }
    cout << endl;

    cout << "수평각 계산 횟수: " << angleCalcCount << endl;
    cout << "각의 비교 횟수: " << angleCompCount << endl;

    return 0;
}
