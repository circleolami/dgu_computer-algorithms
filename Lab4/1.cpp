#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef int itemType;

void print_array(vector<itemType> &a, int n);
void shuffle(vector<itemType> &b);
void generateDataA(vector<itemType> &a);
void generateDataB(vector<itemType> &b);
void generateDataC(vector<itemType> &c);
void CountSort(const vector<itemType> &a, vector<itemType> &b, long long *compare, long long *datamove);

long long compareA, compareB, compareC, datamoveA, datamoveB, datamoveC;

int main()
{
    srand(time(nullptr));

    int n;
    cin >> n;

    vector<itemType> dataA(n);
    vector<itemType> dataB(n);
    vector<itemType> dataC(n);
    vector<itemType> sortedDataA(n);
    vector<itemType> sortedDataB(n);
    vector<itemType> sortedDataC(n);

    generateDataA(dataA);
    generateDataB(dataB);
    generateDataC(dataC);

    CountSort(dataA, sortedDataA, &compareA, &datamoveA);
    CountSort(dataB, sortedDataB, &compareB, &datamoveB);
    CountSort(dataC, sortedDataC, &compareC, &datamoveC);

    cout << "SortedData_A: ";
    print_array(sortedDataA, n);
    cout << "SortedData_B: ";
    print_array(sortedDataB, n);
    cout << "SortedData_C: ";
    print_array(sortedDataC, n);

    cout << "Compare_Cnt_A: " << compareA << ", ";
    cout << "DataMove_Cnt_A: " << datamoveA << endl;
    cout << "Compare_Cnt_B: " << compareB << ", ";
    cout << "DataMove_Cnt_B: " << datamoveB << endl;
    cout << "Compare_Cnt_C: " << compareC << ", ";
    cout << "DataMove_Cnt_C: " << datamoveC << endl;

    return 0;
}

void print_array(vector<itemType> &a, int n)
{
    for (int i = 0; i < n && i < 20; i++)
        cout << a[i] << " ";
    cout << endl;
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

void generateDataA(vector<itemType> &a)
{
    int n = a.size();

    for (int i = 0; i < n; i++)
        a[i] = n - i;
}

void generateDataB(vector<itemType> &b)
{
    int n = b.size();

    for (int i = 0; i < n; i++)
        b[i] = i + 1;

    shuffle(b);
}

void generateDataC(vector<itemType> &c)
{
    int n = c.size();

    for (int i = 0; i < n; i++)
        c[i] = rand() % n + 1;
}

void CountSort(const vector<itemType> &a, vector<itemType> &b, long long *compare, long long *datamove)
{
    int n = a.size();
    vector<itemType> N(n + 1, 0);

    for (int i = 0; i < n; i++)
        N[a[i]]++;
    for (int i = 1; i <= n; i++)
        N[i] += N[i - 1];
    for (int j = n - 1; j >= 0; j--)
    {
        b[N[a[j]] - 1] = a[j];
        N[a[j]]--;
        (*datamove)++;
    }
}