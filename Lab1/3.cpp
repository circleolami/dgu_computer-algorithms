/* 3.cpp
아래 코드를 기반으로 포인터를 이용하는 스택 자료구조를 완성하고, 이를 통해 postfix 표기의 수식을 계산해주는 프로그램을 작성하시오.
단, +와 *뿐만 아니라 -와 /까지도 연산이 가능해야 한다.
나눗셈(/)시 소수점 이하 값이 있을 경우 이를 출력해야 한다.
*/

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
