#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

typedef int itemType;
void print_array(vector<itemType> &a, int n);
int Bubble(int sorted, itemType *a, long long *compare, long long *datamove);
void bubbleSort(itemType a[], int n, long long *compare, long long *datamove);
long long compareA, datamoveA;
long long compareB, datamoveB;

int main()
{
    int N;
    cin >> N;

    vector<itemType> A(N), B(N);
    vector<pair<int, int>> a(N);

    for (int i = 0; i < N; i++)
    {
        A[i] = N - i;
    }

    srand(static_cast<unsigned>(time(nullptr)));
    for (int i = 0; i < N; i++)
    {
        a[i].first = (1 + rand() % N);
        a[i].second = i + 1;
    }

    sort(a.begin(), a.end());

    for (int i = 0; i < N; i++)
    {
        B[i] = a[i].second;
    }

    compareA = 0;
    datamoveA = 0;
    compareB = 0;
    datamoveB = 0;
    bubbleSort(A.data(), N, &compareA, &datamoveA);
    bubbleSort(B.data(), N, &compareB, &datamoveB);

    cout << "Sorted_Data_A: ";
    print_array(A, N);
    cout << "Sorted_Data_B: ";
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

int Bubble(int sorted, itemType *a, long long *compare, long long *datamove)
{
    if (a[0] > a[1])
    {
        (*compare)++;
        (*datamove) += 3;
        swap(a[0], a[1]);
        sorted = 0;
    }
    return sorted;
}

void bubbleSort(itemType a[], int n, long long *compare, long long *datamove)
{
    int sorted = 0;
    while (!sorted)
    {
        sorted = true;
        for (int i = 1; i < n; i++)
        {
            sorted = Bubble(sorted, &a[i - 1], compare, datamove);
        }
    }
}