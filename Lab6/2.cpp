#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unordered_set>
#include <vector>
#include <list>

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

class HashTable
{
private:
    vector<list<int>> table;
    int size;

    int hash(int key)
    {
        return key % size;
    }

public:
    HashTable(int size) : size(size)
    {
        table.resize(size);
    }

    int insert(int key)
    {
        int hashValue = hash(key);
        int comparisons = 1; // 삽입 위치를 찾기 위한 최소 비교 횟수

        for (int elem : table[hashValue])
        {
            comparisons++;
            if (elem == key)
            {
                return comparisons; // 키가 이미 존재하는 경우
            }
        }

        table[hashValue].push_back(key);
        return comparisons;
    }

    int search(int key)
    {
        int hashValue = hash(key);
        int comparisons = 0;

        for (int elem : table[hashValue])
        {
            comparisons++;
            if (elem == key)
            {
                return comparisons; // 키를 찾은 경우
            }
        }

        return comparisons; // 키가 존재하지 않는 경우
    }
};

int main()
{
    srand(time(nullptr));
    int N;

    cin >> N;

    // BST 및 RB Tree를 위한 무작위 숫자 생성
    auto randomNumbers = generateUniqueRandomNumbers(N);

    // BST 생성 및 삽입
    BST bst;
    int totalBSTComparisons = 0;
    for (int num : randomNumbers)
        totalBSTComparisons += bst.BSTinsert(num);

    cout << (double)totalBSTComparisons / N << " (T3의 구축 시 평균 비교 횟수)" << endl;

    // RB Tree 생성 및 삽입
    RBtree rbTree;
    int totalRBComparisons = 0;
    for (int num : randomNumbers)
        totalRBComparisons += rbTree.insert(num, 0);

    // Hash Table을 위한 무작위 숫자 생성 (검색용)
    auto searchNumbersSet = generateUniqueRandomNumbers(100);                    // 100개의 무작위 숫자
    vector<int> searchNumbers(searchNumbersSet.begin(), searchNumbersSet.end()); // set을 vector로 변환

    vector<int> tableSizes = {11, 101, 1009};

    // Hash Table 구축 시 평균 비교 횟수 계산 및 출력
    for (int size : tableSizes)
    {
        HashTable hashTable(size);
        int totalInsertComparisons = 0;

        for (int num : randomNumbers)
            totalInsertComparisons += hashTable.insert(num);

        cout << (double)totalInsertComparisons / N << " (Hash Table 크기가 " << size << "인 경우의 구축 시 평균 비교 횟수)" << endl;
    }
    cout << endl
         << (double)totalRBComparisons / N << " (T3의 평균 비교 회수)" << endl;
    // Hash Table 검색 시 평균 비교 횟수 계산 및 출력
    for (int size : tableSizes)
    {
        HashTable hashTable(size);
        int totalSearchComparisons = 0;

        // 먼저 데이터를 삽입해야 함
        for (int num : randomNumbers)
            hashTable.insert(num);

        for (int num : searchNumbers)
            totalSearchComparisons += hashTable.search(num);

        cout << (double)totalSearchComparisons / 100 << " (Hash Table 크기가 " << size << "인 경우 평균 비교 회수)" << endl;
    }

    return 0;
}