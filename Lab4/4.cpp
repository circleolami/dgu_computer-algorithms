#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef int itemType;
long long compare = 0;

void shuffle(vector<itemType> &b);
void swap(vector<itemType> &a, int i, int j);
int medianOfMedians(vector<itemType> &a, int l, int r);
int partition_N(vector<itemType> &a, int l, int r, int pivotIndex);
int select_N(vector<itemType> &a, int l, int r, int k);
void generateDataA(vector<itemType> &a);
void generateDataB(vector<itemType> &b);
void generateDataC(vector<itemType> &c);

int main()
{
    srand(time(NULL));

    int n;
    cin >> n;

    vector<itemType> dataA(n), dataB(n), dataC(n);

    generateDataA(dataA);
    generateDataB(dataB);
    generateDataC(dataC);

    compare = 0;
    select_N(dataA, 0, n - 1, 0);
    cout << "Minimum value_A: " << dataA[0] << endl;
    cout << "Maximum value_A: " << dataA[n - 1] << endl;
    cout << "Median value_A: " << dataA[n / 2 - 1] << endl;
    cout << "Compare_A: " << compare << endl
         << endl;

    compare = 0;
    select_N(dataB, 0, n - 1, 0);
    cout << "Minimum value_B: " << dataB[0] << endl;
    cout << "Maximum value_B: " << dataB[n - 1] << endl;
    cout << "Median value_B: " << dataB[n / 2 - 1] << endl;
    cout << "Compare_B: " << compare << endl
         << endl;

    compare = 0;
    select_N(dataC, 0, n - 1, 0);
    cout << "Minimum value_C: " << dataC[0] << endl;
    cout << "Maximum value_C: " << dataC[n - 1] << endl;
    cout << "Median value_C: " << dataC[n / 2 - 1] << endl;
    cout << "Compare_C: " << compare << endl
         << endl;

    return 0;
}

void shuffle(vector<itemType> &b)
{
    int size = b.size();
    vector<pair<int, itemType>> a(size);

    for (int i = 0; i < size; i++)
    {
        a[i].first = rand() % size;
        a[i].second = b[i];
    }
    sort(a.begin(), a.end());

    for (int i = 0; i < size; i++)
        b[i] = a[i].second;
}

void swap(vector<itemType> &a, int i, int j)
{
    itemType temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

int medianOfMedians(vector<itemType> &a, int l, int r)
{
    if (r - l < 5)
    {
        sort(a.begin() + l, a.begin() + r + 1);
        return (l + r) / 2;
    }

    for (int i = l; i <= r; i += 5)
    {
        int right = i + 4;
        if (right > r)
            right = r;
        int medianIndex = (i + right) / 2;
        sort(a.begin() + i, a.begin() + right + 1);
        swap(a, medianIndex, l + (i - l) / 5);
    }

    return select_N(a, l, l + (r - l) / 5, (l + l + (r - l) / 5) / 2);
}

int partition_N(vector<itemType> &a, int l, int r, int pivotIndex)
{
    itemType pivot = a[pivotIndex];
    swap(a, pivotIndex, r);
    int i = l;

    for (int j = l; j < r; j++)
    {
        if (a[j] < pivot)
        {
            swap(a, i, j);
            i++;
        }
        compare++;
    }

    swap(a, i, r);
    return i;
}

int select_N(vector<itemType> &a, int l, int r, int k)
{
    while (l <= r)
    {
        if (l == r)
            return l;

        int pivotIndex = medianOfMedians(a, l, r);
        pivotIndex = partition_N(a, l, r, pivotIndex);

        if (k == pivotIndex)
            return k;
        else if (k < pivotIndex)
            r = pivotIndex - 1;
        else
            l = pivotIndex + 1;
    }
    return l;
}

void generateDataA(vector<itemType> &a)
{
    int n = a.size();
    for (int i = 0; i < n; i++)
    {
        a[i] = n - i;
    }
}

void generateDataB(vector<itemType> &b)
{
    int n = b.size();
    for (int i = 0; i < n; i++)
    {
        b[i] = i + 1;
    }
    shuffle(b);
}

void generateDataC(vector<itemType> &c)
{
    int n = c.size();
    for (int i = 0; i < n; i++)
    {
        c[i] = rand() % n + 1;
    }
}
