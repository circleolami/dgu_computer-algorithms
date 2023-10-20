#include <iostream>
#include <cstdlib>
#include <set>
#include <vector>
using namespace std;

#define infoNIL 0
#define itemMIN -1
typedef int itemType;
typedef double infoType;

class BST
{
private:
    struct node
    {
        itemType key;
        infoType info;
        struct node *l, *r;
        node(itemType k, infoType i, struct node *ll, struct node *rr)
        {
            key = k;
            info = i;
            l = ll;
            r = rr;
        };
    };
    struct node *head, *z;

    int compare;

public:
    BST(int max)
    {
        z = new node(0, infoNIL, 0, 0);
        head = new node(itemMIN, infoNIL, z, z);
        compare = 0;
    }

    ~BST()
    {
    }

    infoType BSTsearch(itemType v)
    {
        return BSTsearch(v, head->r);
    }

    infoType BSTsearch(itemType v, struct node *t)
    {
        if (t == z)
            return infoNIL;
        compare++;
        if (v < t->key)
            return BSTsearch(v, t->l);
        else if (v > t->key)
            return BSTsearch(v, t->r);
        return t->info;
    }

    void BSTinsert(itemType v, infoType info)
    {
        BSTinsert(v, info, head, head->r);
    }

    void BSTinsert(itemType v, infoType info, struct node *p, struct node *t)
    {
        if (t == z)
            p->r = new node(v, info, z, z);
        else
        {
            compare++;
            if (v < t->key)
                BSTinsert(v, info, t, t->l);
            else if (v > t->key)
                BSTinsert(v, info, t, t->r);
        }
    }

    double averageComparison()
    {
        return (double)(compare / 100.0);
    }

    void resetComparisonCount()
    {
        compare = 0;
    }
};

int main()
{
    int N;
    cin >> N;

    BST tree(N);
    set<int> numbers;

    while (numbers.size() < N)
    {
        numbers.insert(rand() % (N * 10));
    }

    for (int num : numbers)
    {
        tree.BSTinsert(num, infoNIL);
    }

    vector<int> nums(numbers.begin(), numbers.end());
    for (int i = 0; i < 100; i++)
    {
        int randomIndex = rand() % N;
        tree.BSTsearch(nums[randomIndex]);
    }

    cout.precision(2);
    cout << fixed << tree.averageComparison() << " (T1의 평균 비교 횟수)" << endl;

    return 0;
}
