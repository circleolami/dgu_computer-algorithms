#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

typedef int itemType;

void print_array(vector<itemType> &a, int n);
void shellSort(vector<itemType> &a, long long *compare, long long *datamove);
long long compareA, datamoveA;
long long compareB, datamoveB;

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

    shellSort(A, &compareA, &datamoveA);
    shellSort(B, &compareB, &datamoveB);

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

void shellSort(vector<itemType> &a, long long *compare, long long *datamove)
{
    int n = a.size();
    int i, j, h = 1;
    itemType v;

    h = 1;
    *compare = 0;
    *datamove = 0;
    while (h < n / 3)
    {
        h = 3 * h + 1;
    }

    while (h >= 1)
    {
        for (i = h; i < n; i++)
        {
            v = a[i];
            j = i;
            while (1)
            {

                (*compare)++;
                if (j >= h && a[j - h] > v)
                {
                    (*datamove)++;
                    a[j] = a[j - h];
                    j -= h;
                }
                else
                    break;
            }
            (*datamove)++;
            a[j] = v;
        }
        h = h / 3;
    }
}