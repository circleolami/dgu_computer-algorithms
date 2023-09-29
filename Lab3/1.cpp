#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

typedef int itemType;
void print_array(vector<itemType> &a, int n);
void swap(vector<itemType> &a, int i, int j, long long *datamove);
int partition(vector<itemType> &a, int left, int right, long long *compare, long long *datamove);
void quicksort(vector<itemType> &a, int left, int right, long long *compare, long long *datamove);
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

    quicksort(A, 0, N - 1, &compareA, &datamoveA);
    quicksort(B, 0, N - 1, &compareB, &datamoveB);

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

void swap(vector<itemType> &a, int i, int j, long long *datamove)
{
    (*datamove) += 3;
    itemType temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

int partition(vector<itemType> &a, int left, int right, long long *compare, long long *datamove)
{
    int i, j;
    itemType v;

    if (right > left)
    {
        v = a[left];
        i = left;
        j = right + 1;
        while (1)
        {
            while (a[++i] < v)
                (*compare)++;
            while (a[--j] > v)
                (*compare)++;
            if (i >= j)
                break;
            swap(a, i, j, datamove);
        }
        swap(a, j, left, datamove);
    }
    return j;
}

void quicksort(vector<itemType> &a, int left, int right, long long *compare, long long *datamove)
{
    int temp;

    if (right > left)
    {
        temp = partition(a, left, right, compare, datamove);
        quicksort(a, left, temp - 1, compare, datamove);
        quicksort(a, temp + 1, right, compare, datamove);
    }
}