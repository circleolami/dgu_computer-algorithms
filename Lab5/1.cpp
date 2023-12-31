#include <iostream>
using namespace std;

struct treeNode
{
    char info;
    struct treeNode *l;
    struct treeNode *r;
};

typedef struct treeNode *itemType;

class Stack
{
public:
    Stack(int max = 100)
    {
        stack = new itemType[max];
        p = 0;
    };

    ~Stack()
    {
        delete[] stack;
    };

    void push(itemType v)
    {
        stack[p++] = v;
    }

    itemType pop()
    {
        return stack[--p];
    }

    int empty()
    {
        return (p == 0);
    }

private:
    itemType *stack;
    int p;
};

itemType z;

void visit(struct treeNode *t);
void traverse(struct treeNode *t);

int main()
{
    char c;
    Stack stack(50);
    z = new treeNode;
    z->l = z;
    z->r = z;
    while ((c = cin.get()) != '\n')
    {
        while (c == ' ')
            cin.get(c);
        itemType x = new treeNode;
        x->info = c;
        x->l = z;
        x->r = z;
        if (c == '+' || c == '*' || c == '-')
        {
            x->r = stack.pop();
            x->l = stack.pop();
        }
        stack.push(x);
    }
    traverse(stack.pop());
    cout << endl;
    return 0;
}

void visit(struct treeNode *t)
{
    cout << t->info << " ";
}

void traverse(struct treeNode *t)
{
    if (t != z)
    {
        traverse(t->l);
        visit(t);
        traverse(t->r);
    }
}
