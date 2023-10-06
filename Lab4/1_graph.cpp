#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream> // 추가

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
    ofstream outFile("results.txt");

    for (int n = 10; n <= 1000; n += 10)
    {
        vector<itemType> dataA(n);
        vector<itemType> dataB(n);
        vector<itemType> dataC(n);
        vector<itemType> sortedDataA(n);
        vector<itemType> sortedDataB(n);
        vector<itemType> sortedDataC(n);

        generateDataA(dataA);
        generateDataB(dataB);
        generateDataC(dataC);

        compareA = compareB = compareC = datamoveA = datamoveB = datamoveC = 0; // 초기화

        CountSort(dataA, sortedDataA, &compareA, &datamoveA);
        CountSort(dataB, sortedDataB, &compareB, &datamoveB);
        CountSort(dataC, sortedDataC, &compareC, &datamoveC);

        outFile << n << " " << compareA << " " << datamoveA << " "
                << compareB << " " << datamoveB << " "
                << compareC << " " << datamoveC << endl;
    }

    outFile.close();
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
    {
        N[a[i]]++;
    }
    for (int i = 1; i <= n; i++)
    {
        N[i] += N[i - 1];
    }
    for (int j = n - 1; j >= 0; j--)
    {
        b[N[a[j]] - 1] = a[j];
        N[a[j]]--;
        (*datamove)++;
    }
}
