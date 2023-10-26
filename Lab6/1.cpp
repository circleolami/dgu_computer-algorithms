#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unordered_set>
#include <vector>

using namespace std;

struct TreeNode
{
    int data;
    TreeNode *left, *right;
    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BST
{
public:
    TreeNode *root;
    BST() : root(nullptr) {}

    int BSTinsert(int value)
    {
        int comparisons = 0;
        root = insertInternal(root, value, comparisons);
        return comparisons;
    }

    void inorderTraversal() const
    {
        inorderInternal(root);
        cout << endl;
    }

    void collectInorderData(vector<int> &data) const
    {
        collectInorderInternal(root, data);
    }
    int BSTsearch(int value)
    {
        int comparisons = 0;
        TreeNode *current = root;
        while (current != nullptr)
        {
            comparisons++;
            if (current->data == value)
                return comparisons;
            else if (value < current->data)
                current = current->left;
            else
                current = current->right;
        }
        return comparisons;
    }

private:
    TreeNode *insertInternal(TreeNode *node, int value, int &comparisons)
    {
        comparisons++;
        if (node == nullptr)
            return new TreeNode(value);

        if (value < node->data)
            node->left = insertInternal(node->left, value, comparisons);
        else if (value > node->data)
            node->right = insertInternal(node->right, value, comparisons);

        return node;
    }

    void inorderInternal(TreeNode *node) const
    {
        if (node != nullptr)
        {
            inorderInternal(node->left);
            cout << node->data << " ";
            inorderInternal(node->right);
        }
    }

    void collectInorderInternal(TreeNode *node, vector<int> &data) const
    {
        if (node != nullptr)
        {
            collectInorderInternal(node->left, data);
            data.push_back(node->data);
            collectInorderInternal(node->right, data);
        }
    }
};

unordered_set<int> generateUniqueRandomNumbers(int n)
{
    unordered_set<int> numbers;
    while (numbers.size() < n)
    {
        numbers.insert(rand());
    }
    return numbers;
}

typedef int itemType;
typedef int infoType;
#define infoNIL 0
#define itemMIN -1
#define black 0
#define red 1

struct node
{
    itemType key, tag;
    infoType Info;
    struct node *l, *r;
    node(itemType k, infoType i, itemType t, struct node *ll, struct node *rr)
        : key(k), Info(i), tag(t), l(ll), r(rr) {}
};

struct node *head, *tail, *x, *p, *g, *gg, *z;

class RBtree
{
public:
    RBtree()
    {
        z = new node(0, infoNIL, black, 0, 0);
        z->l = z;
        z->r = z;
        head = new node(itemMIN, infoNIL, black, z, z);
    }

    int insert(itemType k, infoType info)
    {
        int comparisons = 0;
        x = head;
        p = head;
        g = head;
        while (x != z)
        {
            comparisons++;
            gg = g;
            g = p;
            p = x;
            x = (k < x->key) ? x->l : x->r;
            if (x->l->tag && x->r->tag)
                split(k);
        }
        x = new node(k, info, red, z, z);
        if (k < p->key)
            p->l = x;
        else
            p->r = x;
        split(k);
        head->r->tag = black;
        return comparisons;
    }

    struct node *rotate(itemType k, struct node *y)
    {
        struct node *high, *low;
        high = (k < y->key) ? y->l : y->r;
        if (k < high->key)
        {
            low = high->l;
            high->l = low->r;
            low->r = high;
        }
        else
        {
            low = high->r;
            high->r = low->l;
            low->l = high;
        }
        if (k < y->key)
            y->l = low;
        else
            y->r = low;
        return low;
    }

    void split(itemType k)
    {
        x->tag = red;
        x->l->tag = black;
        x->r->tag = black;
        if (p->tag)
        {
            g->tag = red;
            if (k < g->key != k < p->key)
                p = rotate(k, g);
            x = rotate(k, gg);
            x->tag = black;
        }
    }

    void inorderTraversal() const
    {
        inorderInternal(head->r);
        cout << endl;
    }
    int RBsearch(itemType k)
    {
        int comparisons = 0;
        struct node *current = head->r;
        while (current != z)
        {
            comparisons++;
            if (current->key == k)
                return comparisons;
            current = (k < current->key) ? current->l : current->r;
        }
        return comparisons;
    }

private:
    void inorderInternal(struct node *node) const
    {
        if (node != z)
        {
            inorderInternal(node->l);
            cout << node->key << " ";
            inorderInternal(node->r);
        }
    }
};

int main()
{
    srand(time(nullptr));
    int N;

    cin >> N;

    auto randomNumbers = generateUniqueRandomNumbers(N);
    BST bst1;
    for (int num : randomNumbers)
        bst1.BSTinsert(num);

    vector<int> inorderData;
    bst1.collectInorderData(inorderData);

    BST bst2;
    for (int data : inorderData)
    {
        bst2.BSTinsert(data);
    }
    RBtree rbTree;
    for (int data : inorderData)
    {
        rbTree.insert(data, infoNIL);
    }

    // 트리 구축 시 평균 비교 횟수 출력
    int totalComparisonsT1 = 0;
    for (int num : randomNumbers)
        totalComparisonsT1 += bst1.BSTinsert(num);

    cout << (double)totalComparisonsT1 / N << " (T1의 구축 시 평균 비교 횟수)" << endl;

    int totalComparisonsT2 = 0;
    for (int data : inorderData)
        totalComparisonsT2 += bst2.BSTinsert(data);

    cout << (double)totalComparisonsT2 / N << " (T2의 구축 시 평균 비교 횟수)" << endl;

    int totalComparisonsT3 = 0;
    for (int data : inorderData)
        totalComparisonsT3 += rbTree.insert(data, infoNIL);

    cout << (double)totalComparisonsT3 / N << " (T3의 구축 시 평균 비교 횟수)" << endl;

    cout << endl;
    // 트리의 평균 탐색 비교 횟수 출력
    auto searchNumbers = generateUniqueRandomNumbers(100);

    int searchComparisonsT1 = 0;
    for (int num : searchNumbers)
        searchComparisonsT1 += bst1.BSTsearch(num);

    cout << (double)searchComparisonsT1 / 100 << " (T1의 평균 탐색 비교 횟수)" << endl;

    int searchComparisonsT2 = 0;
    for (int num : searchNumbers)
        searchComparisonsT2 += bst2.BSTsearch(num);

    cout << (double)searchComparisonsT2 / 100 << " (T2의 평균 탐색 비교 횟수)" << endl;

    int searchComparisonsT3 = 0;
    for (int num : searchNumbers)
        searchComparisonsT3 += rbTree.RBsearch(num);

    cout << (double)searchComparisonsT3 / 100 << "(T3의 평균 탐색 비교 횟수)" << endl;

    return 0;
}
