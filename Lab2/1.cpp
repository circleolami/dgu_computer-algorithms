#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

typedef int itemType;
void print_array(vector<itemType> &a, int n);
void insertion(vector<itemType> &arr);
long long compare, datamove;

int main()
{
    int N;

    cout << "Enter the size N of the array (>10000): ";
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

    insertion(A);
    cout << "Sorted_Data_A: ";
    print_array(A, N);
    cout << "Compare_Cnt_A: " << compare << endl;
    cout << "DataMove_Cnt_A: " << datamove << endl
         << endl;

    insertion(B);
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

void insertion(vector<itemType> &arr)
{
    int n = arr.size();
    compare = 0;
    datamove = 0;
    for (int i = 1; i < n; i++)
    {
        itemType v = arr[i];
        int j = i;
        while (1)
        {
            compare++;
            if (j > 0 && arr[j - 1] > v)
            {
                datamove++;
                arr[j] = arr[j - 1];
                j--;
            }
            else
                break;
        }
        datamove++;
        arr[j] = v;
    }
}