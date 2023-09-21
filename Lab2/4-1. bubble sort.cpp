#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

typedef int itemType;

void print_array(vector<itemType> &a, int n);
long long Bubble(int sorted, itemType *a);
void bubbleSort(itemType a[], int n, long long &weightMoved);

int main()
{
    int N;
    cout << "Enter the size N of the array (>500): ";
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

    cout << "A" << endl;
    print_array(A, N);
    long long weightBubbleA;
    bubbleSort(A.data(), N, weightBubbleA);
    print_array(A, N);

    cout << "B" << endl;
    print_array(B, N);
    long long weightBubbleB;
    bubbleSort(B.data(), N, weightBubbleB);
    print_array(B, N);

    cout << "Bubble Sort A: " << weightBubbleA << endl;
    cout << "Bubble Sort B: " << weightBubbleB << endl;

    return 0;
}

void print_array(vector<itemType> &a, int n)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}

long long Bubble(int sorted, itemType *a, long long &weightMoved)
{
    int temp;
    if (*(a - 1) > *a)
    {
        if (*a < *(a - 1))
        {
            weightMoved += 2 * (*a);
            temp = *(a - 1);
            *(a - 1) = *a;
            *a = temp;
        }
        else
        {
            weightMoved += 2 * (*(a - 1));
            temp = *(a - 1);
            *(a - 1) = *a;
            *a = temp;
        }
        sorted = 0;
    }
    return sorted;
}

void bubbleSort(itemType a[], int n, long long &weightMoved)
{
    weightMoved = 0;
    int sorted = 1;
    while (sorted)
    {
        sorted = 0;
        for (int i = 1; i < n; i++)
            sorted = Bubble(sorted, &a[i], weightMoved);
        if (!sorted)
            sorted = 1;
        else
            break;
    }
}
