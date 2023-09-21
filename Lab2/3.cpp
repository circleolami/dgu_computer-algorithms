#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

typedef int itemType;
void print_array(vector<itemType> &a, int n);
int Bubble(int sorted, itemType *a);
void bubbleSort(itemType a[], int n);
long long compare, datamove;

int main()
{
    int N;
    cout << "Enter the size N of the array (>10000): ";
    cin >> N;

    vector<itemType> A(N), B(N);
    vector<pair<int, int>> a(N);

    // Creating array A
    for (int i = 0; i < N; i++)
    {
        A[i] = N - i;
    }

    // Creating array B using hint
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

    // Sorting A and B using bubble sort
    compare = 0;
    datamove = 0;
    bubbleSort(A.data(), N);
    cout << "Sorted_Data_A: ";
    print_array(A, N);
    cout << "Compare_Cnt_A: " << compare << endl;
    cout << "DataMove_Cnt_A: " << datamove << endl
         << endl;

    compare = 0;
    datamove = 0;
    bubbleSort(B.data(), N);
    cout << "Sorted_Data_B: ";
    print_array(B, N);
    cout << "Compare_Cnt_B: " << compare << endl;
    cout << "DataMove_Cnt_B: " << datamove << endl;

    return 0;
}

void print_array(vector<itemType> &a, int n)
{
    for (int i = 0; i < 20; i++)
        cout << a[i] << " ";
    cout << endl;
}

int Bubble(int sorted, itemType *a)
{
    compare++;
    if (a[0] > a[1])
    {
        datamove++;
        swap(a[0], a[1]);
        sorted = 0;
    }
    return sorted;
}

void bubbleSort(itemType a[], int n)
{
    int sorted = 0;
    while (!sorted)
    {
        sorted = true;
        for (int i = 1; i < n; i++)
        {
            sorted = Bubble(sorted, &a[i - 1]);
        }
    }
}