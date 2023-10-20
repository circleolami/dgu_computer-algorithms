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

    void InorderTraversal(struct node *t, vector<itemType> &result)
    {
        if (t != z)
        {
            InorderTraversal(t->l, result);
            result.push_back(t->key);
            InorderTraversal(t->r, result);
        }
    }

public:
    BST(int max)
    {
        z = new node(0, infoNIL, 0, 0);
        head = new node(itemMIN, infoNIL, z, z);
        compare = 0;
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

    vector<itemType> getInorderSequence()
    {
        vector<itemType> result;
        InorderTraversal(head->r, result);
        return result;
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

    BST initialTree(N);
    set<int> numbers;

    while (numbers.size() < N)
    {
        numbers.insert(rand() % (N * 10));
    }

    for (int num : numbers)
    {
        initialTree.BSTinsert(num, infoNIL);
    }

    // Construct tree T3 using the inorder sequence from the initial tree
    BST tree3(N);
    vector<int> inorderSeq = initialTree.getInorderSequence();
    for (int num : inorderSeq)
    {
        tree3.BSTinsert(num, infoNIL);
    }

    tree3.resetComparisonCount();

    vector<int> nums(inorderSeq);
    for (int i = 0; i < 100; i++)
    {
        int randomIndex = rand() % N;
        tree3.BSTsearch(nums[randomIndex]);
    }

    cout.precision(2);
    cout << fixed << tree3.averageComparison() << " (T3의 평균 비교 횟수)" << endl;

    return 0;
}
