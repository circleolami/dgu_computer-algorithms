#include <iostream>
#include <vector>

using namespace std;

typedef int itemType;

void check_insertion(int n);
void check_shell(int n);
void check_bubble(int n);

void print_array(vector<itemType> &a, int n);

void insertion(vector<itemType> &arr);
void shellSort(vector<itemType> &a);
int Bubble(int sorted, itemType *a);
void bubbleSort(itemType a[], int n);
long long weight;

int main()
{
    int N;
    cin >> N;

    check_insertion(N);
    check_bubble(N);
    check_shell(N);

    return 0;
}

void check_insertion(int n)
{
    vector<itemType> A(n);

    for (int i = 0; i < n; i++)
        A[i] = n - i;

    weight = 0;
    insertion(A);
    cout << "Insertion Sort: " << weight << endl;
}

void check_bubble(int n)
{
    vector<itemType> A(n);

    for (int i = 0; i < n; i++)
        A[i] = n - i;

    weight = 0;
    bubbleSort(A.data(), n);
    cout << "Bubble Sort: " << weight << endl;
}

void check_shell(int n)
{
    vector<itemType> A(n);

    for (int i = 0; i < n; i++)
        A[i] = n - i;

    weight = 0;
    shellSort(A);
    cout << "Shell Sort: " << weight << endl;
}

void print_array(vector<itemType> &a, int n)
{
    for (int i = 0; i < n && i < 20; i++)
        cout << a[i] << " ";
    cout << endl;
}

void insertion(vector<itemType> &arr)
{
    int n = arr.size();
    for (int i = 1; i < n; i++)
    {
        itemType v = arr[i];
        weight += arr[i];
        int j = i;
        while (1)
        {
            if (j > 0 && arr[j - 1] > v)
            {
                arr[j] = arr[j - 1];
                j--;
            }
            else
                break;
        }
        weight += arr[j];
        weight += v;
        arr[j] = v;
    }
}

void shellSort(vector<itemType> &a)
{
    int n = a.size();
    int i, j, h = 1;
    itemType v;

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
                if (j >= h && a[j - h] > v)
                {
                    if (v < a[j - h])
                    {
                        weight += (v + a[j - h] + v);
                    }
                    else
                    {
                        weight += (a[j - h] + v + a[j - h]);
                    }
                    a[j] = a[j - h];
                    j -= h;
                }
                else
                    break;
            }
            a[j] = v;
        }
        h = h / 3;
    }
}

int Bubble(int sorted, itemType *a)
{
    if (a[0] > a[1])
    {
        weight += a[1];
        weight += a[0];
        weight += a[1];

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
