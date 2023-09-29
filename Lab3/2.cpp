#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

typedef int itemType;
void print_array(vector<itemType> &a, int n);
void merge(vector<itemType> &a, int l, int mid, int r, long long *compare, long long *datamove);
void mergesort(vector<itemType> &a, int l, int r, long long *compare, long long *datamove);
long long compareA, datamoveA, compareB, datamoveB;

int main()
{
    int N;

    cin >> N;

    vector<itemType> A(N), B(N);
    vector<pair<int, int>> a(N);

    for (int i = 0; i < N; i++)
        A[i] = N - i;

    srand(static_cast<unsigned>(time(nullptr)));
    for (int i = 0; i < N; i++)
    {
        a[i].first = (1 + rand() % N);
        a[i].second = i + 1;
    }

    sort(a.begin(), a.end());

    for (int i = 0; i < N; i++)
        B[i] = a[i].second;

    mergesort(A, 0, N - 1, &compareA, &datamoveA);
    mergesort(B, 0, N - 1, &compareB, &datamoveB);

    cout << "SortedData_A: ";
    print_array(A, N);
    cout << "SortedData_B: ";
    print_array(B, N);
    cout << "Compare_Cnt_A: " << compareA << ", ";
    cout << "DataMove_Cnt_A: " << datamoveA << endl;
    cout << "Compare_Cnt_B: " << compareB << ", ";
    cout << "DataMove_Cnt_B: " << datamoveB << endl;

    return 0;
}

void print_array(vector<itemType> &a, int n)
{
    for (int i = 0; i < n && i < 20; i++)
        cout << a[i] << " ";
    cout << endl;
}

void merge(vector<itemType> &a, int l, int mid, int r, long long *compare, long long *datamove)
{
    vector<itemType> sorted(r - l + 1);
    int i = l, j = mid + 1, k = 0;

    while (i <= mid && j <= r)
    {
        (*compare)++;
        if (a[i] <= a[j])
        {
            (*datamove)++;
            sorted[k++] = a[i++];
        }
        else
        {
            (*datamove)++;
            sorted[k++] = a[j++];
        }
    }
    while (i <= mid)
    {
        sorted[k++] = a[i++];
        (*datamove)++;
    }
    while (j <= r)
    {
        sorted[k++] = a[j++];
        (*datamove)++;
    }

    for (int n = 0; n < sorted.size(); n++)
    {
        (*datamove)++;
        a[l + n] = sorted[n];
    }
}

void mergesort(vector<itemType> &a, int l, int r, long long *compare, long long *datamove)
{
    if (l < r)
    {
        int mid = (l + r) / 2;
        mergesort(a, l, mid, compare, datamove);
        mergesort(a, mid + 1, r, compare, datamove);
        merge(a, l, mid, r, compare, datamove);
    }
}