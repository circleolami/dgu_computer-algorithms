#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef int itemType;
int compare = 0;

void swap(vector<itemType> &a, int i, int j);
int partition(vector<itemType> &a, int l, int r);
void select(vector<itemType> &a, int l, int r, int k);

int main()
{
    srand(time(NULL));

    int n;
    cin >> n;

    vector<itemType> data(n);

    for (int i = 0; i < n; i++)
        data[i] = rand() % (5 * n) + 1;

    compare = 0;
    select(data, 0, n - 1, 1);
    cout << "Minimum value: " << data[0] << ", Compare: " << compare << endl;

    compare = 0;
    select(data, 0, n - 1, n);
    cout << "Maximum value: " << data[n - 1] << ", Compare: " << compare << endl;

    compare = 0;
    select(data, 0, n - 1, n / 2);
    cout << "Median value: " << data[n / 2 - 1] << ", Compare: " << compare << endl;

    return 0;
}

void swap(vector<itemType> &a, int i, int j)
{
    itemType temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

int partition(vector<itemType> &a, int l, int r)
{
    int i, j;
    itemType v;

    if (r > l)
    {
        v = a[l];
        i = l;
        j = r + 1;

        while (1)
        {
            while (a[++i] < v)
                compare++;
            while (a[--j] > v)
                compare++;
            if (i >= j)
                break;
            swap(a, i, j);
        }
        swap(a, j, l);
    }
    return j;
}

void select(vector<itemType> &a, int l, int r, int k)
{
    int j;

    if (r > l)
    {
        j = partition(a, l, r);
        if (j > l + k - 1)
            select(a, l, j - 1, k);
        if (j < l + k - 1)
            select(a, j + 1, r, k - j + l - 1);
    }
}
