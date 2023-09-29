#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <stack>

using namespace std;

typedef int itemType;

void print_array(vector<itemType> &a, int n);
void swap(vector<itemType> &a, int i, int j, long long *datamove);
int partition(vector<itemType> &a, int left, int right, long long *compare, long long *datamove);
void iterativeQuicksort(vector<itemType> &a, int left, int right, long long *compare, long long *datamove);

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

    iterativeQuicksort(A, 0, N - 1, &compareA, &datamoveA);
    iterativeQuicksort(B, 0, N - 1, &compareB, &datamoveB);

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
        v = a[right];
        i = left - 1;
        j = right;

        while (true)
        {
            while (a[++i] < v && i < right)
                (*compare)++;
            while (a[--j] > v && j > left)
                (*compare)++;
            if (i >= j)
                break;
            swap(a, i, j, datamove);
        }
        swap(a, i, right, datamove);
    }
    return i;
}

void iterativeQuicksort(vector<itemType> &a, int left, int right, long long *compare, long long *datamove)
{
    stack<int> s;
    s.push(left);
    s.push(right);

    while (!s.empty())
    {
        right = s.top();
        s.pop();
        left = s.top();
        s.pop();

        int pivot = partition(a, left, right, compare, datamove);

        if (pivot - 1 > left)
        {
            s.push(left);
            s.push(pivot - 1);
        }

        if (pivot + 1 < right)
        {
            s.push(pivot + 1);
            s.push(right);
        }
    }
}
