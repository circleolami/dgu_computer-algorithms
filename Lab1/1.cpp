/* 1.cpp
다양한 입력 값들을 사용하여 다음 프로그램을 실행해보고, 프로그램의 동작원리를 설명하시오.
*/

#include <iostream>

using namespace std;

class InputNum
{
private:
    int _num; // 클래스 내에서만 접근 가능한 변수 _num 선언

public:
    // InputNum: 사용자에게 숫자를 입력받아 _num에 저장
    InputNum()
    {
        cout << "Enter number";
        cin >> _num;
    }
    // GetValue:  _num을 반환
    int GetValue() const { return _num; }
    // AddInput: _num의 값에 aNum의 값을 더함
    void AddInput()
    {
        InputNum aNum;
        _num = _num + aNum.GetValue();
    }
};

int main()
{
    InputNum num;                                         // InputNum 객체 생성 -> 숫자를 입력받음 (Enter Number)
    cout << "The value is" << num.GetValue() << "\n";     // 현재 num의 값을 출력
    num.AddInput();                                       // 새로운 숫자를 입력받아 AddInput 실행 (num의 값에 새로운 값을 더함)
    cout << "Now the value is" << num.GetValue() << "\n"; // 새로운 num 값을 출력
}
