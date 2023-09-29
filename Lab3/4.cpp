#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

typedef int itemType;

class PQ
{
    itemType *a;
    int N;

public:
    PQ(int max)
    {
        a = new itemType[max];
        N = 0;
    }
    ~PQ()
    {
        delete[] a;
    }

    void setData(int index, itemType value) { a[index] = value; }
    void MakeHeap(int Root, int LastNode);
    void heapsort(int N);
    itemType getValueAt(int index) const { return a[index]; }
};

long long compare;

int main()
{
    int N;

    cin >> N;
    PQ pq(N);
    vector<pair<int, int>> a(N);

    srand(static_cast<unsigned>(time(nullptr)));
    for (int i = 0; i < N; i++)
    {
        a[i].first = (1 + rand() % N);
        a[i].second = i + 1;
    }

    sort(a.begin(), a.end());

    for (int i = 0; i < N; i++)
        pq.setData(i, a[i].second);

    compare = 0;
    pq.heapsort(N);

    cout << "SortedData: ";
    for (int i = 0; i < N && i < 20; i++)
        cout << pq.getValueAt(i) << " ";
    cout << endl;

    cout << "Compare_Cnt: " << compare << endl;

    return 0;
}

void PQ::MakeHeap(int Root, int LastNode)
{
    int k = Root;
    int j = 2 * k + 1;

    while (j <= LastNode)
    {
        compare++;
        if (j < LastNode && a[j] < a[j + 1])
            j++;
        if (a[k] >= a[j])
            break;
        swap(a[k], a[j]);
        k = j;
        j = 2 * k + 1;
    }
}

void PQ::heapsort(int N)
{
    for (int i = N / 2 - 1; i >= 0; i--)
        MakeHeap(i, N - 1);
    for (int i = N - 1; i > 0; i--)
    {
        swap(a[0], a[i]);
        MakeHeap(0, i - 1);
    }
}