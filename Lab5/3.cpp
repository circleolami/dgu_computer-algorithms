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
    int compare, deleteCount;

public:
    BST(int max)
    {
        z = new node(0, infoNIL, 0, 0);
        head = new node(itemMIN, infoNIL, z, z);
        compare = 0;
        deleteCount = 0;
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
        {
            p->r = new node(v, info, z, z);
        }
        else
        {
            if (v < t->key)
                BSTinsert(v, info, t, t->l);
            else if (v > t->key)
                BSTinsert(v, info, t, t->r);
        }
    }

    void BSTdelete(itemType v)
    {
        head->r = BSTdelete(v, head->r);
        deleteCount++;
    }

    struct node *BSTdelete(itemType v, struct node *t)
    {
        compare++;
        if (t == z)
            return t;
        if (v < t->key)
        {
            t->l = BSTdelete(v, t->l);
        }
        else if (v > t->key)
        {
            t->r = BSTdelete(v, t->r);
        }
        else
        {
            if (t->l == z || t->r == z)
            {
                struct node *temp = t;
                t = (t->l != z) ? t->l : t->r;
                delete temp;
            }
            else
            {
                struct node *min = t->r;
                while (min->l != z)
                {
                    min = min->l;
                }
                t->key = min->key;
                t->r = BSTdelete(t->key, t->r);
            }
        }
        return t;
    }

    double averageComparison()
    {
        return (double)compare / deleteCount;
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
    int deleteCount = 0;
    for (int i = 0; i < N; i += 10)
    {
        int randomIndex = i + (rand() % 10);
        if (randomIndex < N)
        {
            tree.BSTdelete(nums[randomIndex]);
            deleteCount++;
        }
    }

    cout.precision(2);
    cout << fixed << tree.averageComparison() / deleteCount << " (T2의 평균 비교 횟수)" << endl;

    return 0;
}
