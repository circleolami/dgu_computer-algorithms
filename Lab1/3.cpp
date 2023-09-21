#include <iostream>
#include <sstream>
#include <string>
using namespace std;

typedef double itemType;

class Stack2
{
public:
    Stack2() : head(nullptr) {}
    ~Stack2();

    void push(itemType v);
    itemType pop();
    int empty();

private:
    struct node
    {
        itemType key;
        struct node *next;
    };
    struct node *head;
};

Stack2::~Stack2()
{
    while (!empty())
        pop();
}

void Stack2::push(itemType v)
{
    struct node *newNode = new node;
    newNode->key = v;
    newNode->next = head;
    head = newNode;
}

itemType Stack2::pop()
{
    if (empty())
        exit(1);
    struct node *tempNode = head;
    itemType value = tempNode->key;
    head = head->next;
    delete tempNode;
    return value;
}

int Stack2::empty()
{
    return head == nullptr;
}

double postfix(const string &ex)
{
    Stack2 stack;
    stringstream ss(ex);
    string val;

    while (ss >> val)
    {
        if (isdigit(val[0]) || (val.size() > 1 && isdigit(val[1])))
            stack.push(stod(val));
        else
        {
            double b = stack.pop();
            double a = stack.pop();
            switch (val[0])
            {
            case '+':
                stack.push(a + b);
                break;
            case '-':
                stack.push(a - b);
                break;
            case '*':
                stack.push(a * b);
                break;
            case '/':
                stack.push(a / b);
                break;
            }
        }
    }
    return stack.pop();
}

int main()
{
    string ex;
    getline(cin, ex);

    double result = postfix(ex);
    cout << result << endl;

    return 0;
}
