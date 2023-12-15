#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Point {
    int x, y;
};

bool onSegment(Point p, Point q, Point r) {
    return q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y);
}

int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // colinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

bool doIntersect(Point p1, Point q1, Point p2, Point q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4) return true;

    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

bool isInside(vector<Point>& polygon, Point p) {
    if (polygon.size() < 3) return false;

    Point extreme = { 10000, p.y };
    int count = 0, i = 0;

    do {
        int next = (i + 1) % polygon.size();
        if (doIntersect(polygon[i], polygon[next], p, extreme)) {
            if (orientation(polygon[i], p, polygon[next]) == 0)
                return onSegment(polygon[i], p, polygon[next]);
            count++;
        }
        i = next;
    } while (i != 0);

    return count % 2 == 1;
}

int main() {
    int N;
    Point p;

    cin >> N >> p.x >> p.y;

    vector<Point> polygon(N);
    string vertexName;
    for (int i = 0; i < N; ++i)
        cin >> vertexName >> polygon[i].x >> polygon[i].y;

    cout << (isInside(polygon, p) ? "True" : "False") << endl;

    return 0;
}
