#include <iostream>
using namespace std;

template <typename itemType>
class Stack1
{
private:
    itemType *stack;
    int p;

public:
    Stack1(int max = 100)
    {
        stack = new itemType[max];
        p = 0;
    }
    ~Stack1()
    {
        delete stack;
    }
    inline void push(itemType v)
    {
        stack[p++] = v;
    }
    inline itemType pop()
    {
        return stack[--p];
    }
    inline int empty()
    {
        return !p;
    }
};

int main()
{
    char c;
    Stack1<double> acc(50);
    double x;

    while ((c = cin.get()) != '\n')
    {
        x = 0;
        double factor = 0.1; // 소수점 아래 위치
        bool flag = 0;       // 소수점 아래자리인지 확인

        while (c == ' ')
            cin.get(c);
        if (c == '+')
            x = acc.pop() + acc.pop();
        else if (c == '*')
            x = acc.pop() * acc.pop();
        while ((c >= '0' && c <= '9') || c == '.')
        {
            // 소수점 아래일 때 flag를 1로 변경
            if (c == '.')
                flag = 1;
            else
            {
                // 소수점 아래 자리수
                if (flag)
                {
                    x = x + factor * (c - '0');
                    factor *= 0.1;
                }
                // 정수 자리수
                else
                    x = 10 * x + (c - '0');
            }
            cin.get(c);
        }
        acc.push(x);
    }
    cout.precision(8); // 소수점 아래 4자리만 출력
    cout << acc.pop() << '\n';
}
