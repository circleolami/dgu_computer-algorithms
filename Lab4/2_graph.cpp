#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

typedef int itemType;
typedef struct node *node_pointer;
typedef struct node {
    itemType value;
    node_pointer next;
} Node;

node_pointer TABLE[10], x, z, temp;

void shuffle(vector<itemType> &b);
void generateDataA(vector<itemType> &a);
void generateDataB(vector<itemType> &b);
void generateDataC(vector<itemType> &c);
void radixSort(itemType *a, int n, long long *compare, long long *datamove);

int main()
{
    srand(time(nullptr));
    ofstream outFile("results.txt");

    for (int n = 10; n <= 1000; n += 10) 
    {
        vector<itemType> dataA(n);
        vector<itemType> dataB(n);
        vector<itemType> dataC(n);

        generateDataA(dataA);
        generateDataB(dataB);
        generateDataC(dataC);

        long long compareA = 0, datamoveA = 0;
        long long compareB = 0, datamoveB = 0;
        long long compareC = 0, datamoveC = 0;

        radixSort(dataA.data(), n, &compareA, &datamoveA);
        radixSort(dataB.data(), n, &compareB, &datamoveB);
        radixSort(dataC.data(), n, &compareC, &datamoveC);

        outFile << n << " " << compareA << " " << datamoveA << " "
                << compareB << " " << datamoveB << " "
                << compareC << " " << datamoveC << endl;
    }

    outFile.close();
    return 0;
}

void print_array(const vector<itemType> &a)
{
    for (int i = 0; i < 20 && i < a.size(); i++)
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
    {
        b[i] = a[i].second;
    }
}

void generateDataA(vector<itemType> &a)
{
    int n = a.size();
    for (int i = 0; i < n; i++)
    {
        a[i] = n - i;
    }
}

void generateDataB(vector<itemType> &b)
{
    int n = b.size();
    for (int i = 0; i < n; i++)
    {
        b[i] = i + 1;
    }
    shuffle(b);
}

void generateDataC(vector<itemType> &c)
{
    int n = c.size();
    for (int i = 0; i < n; i++)
    {
        c[i] = rand() % n + 1;
    }
}

void radixSort(itemType *a, int n, long long *compare, long long *datamove)
{
    z = new node;
    z->value = 0;
    z->next = NULL;
    for (int i = 0; i < 10; i++)
        TABLE[i] = z;

    int cipher = 0, i = n;
    while (i > 0)
    {
        i = i / 10;
        cipher++;
    }
    int radix_mod = 10;
    for (int i = 0; i < cipher; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int radix = (a[j] % radix_mod) / (radix_mod / 10);
            temp = new node;
            temp->value = a[j];
            temp->next = z;
            if (TABLE[radix] == z)
            {
                TABLE[radix] = temp;
            }
            else
            {
                x = TABLE[radix];
                while (x->next != z)
                {
                    x = x->next;
                }
                x->next = temp;
                (*datamove)++;
            }
        }
        int cnt = 0;

        for (int j = 0; j < 10; j++)
        {
            if (TABLE[j] != z)
            {
                x = TABLE[j];
                while (x != z)
                {
                    (*datamove)++;
                    a[cnt++] = x->value;
                    temp = x;
                    x = x->next;
                    delete temp;
                }
            }
            TABLE[j] = z;
        }
        radix_mod *= 10;
    }
    delete z;
}
