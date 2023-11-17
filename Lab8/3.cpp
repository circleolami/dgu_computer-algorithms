#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// (iii) 두 문자열 X와 Y의 길이가 각각 m과 n일 때, 크기가 최대 min(m, n)인 배열을 사용하여 LCS의 길이를 찾기
int lcs_len(const string &X, const string &Y)
{
    int m = static_cast<int>(X.size()), n = static_cast<int>(Y.size());
    vector<int> prev(n + 1, 0); // 이전 행을 저장할 벡터
    vector<int> curr(n + 1, 0); // 현재 행을 저장할 벡터

    // (i) b[i][j] 배열을 사용하지 않고 O(m+n) 시간에 LCS를 찾기
    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (X[i - 1] == Y[j - 1]) // 문자가 일치하는 경우
                curr[j] = prev[j - 1] + 1;
            else // 일치하지 않는 경우 두 선택지 중 최대값을 취함
                curr[j] = max(prev[j], curr[j - 1]);
        }
        prev.swap(curr); // 다음 반복을 위해 현재 행을 이전 행으로 교체
    }
    return prev[n]; // LCS의 길이 반환
}

// (i) LCS 길이를 찾은 후 실제 LCS 문자열을 복구
string lcs(const string &X, const string &Y)
{
    int m = static_cast<int>(X.size()), n = static_cast<int>(Y.size());
    vector<int> prev(n + 1, 0);
    vector<int> curr(n + 1, 0);
    vector<vector<int>> solution(m + 1, vector<int>(n + 1, 0)); // 방향을 나타내는 배열

    // (ii) 하향식 방법(with memoization)을 사용하여 LCS의 길이를 찾기
    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (X[i - 1] == Y[j - 1])
            {
                curr[j] = prev[j - 1] + 1;
                solution[i][j] = 1; // 대각선 방향
            }
            else if (prev[j] >= curr[j - 1])
            {
                curr[j] = prev[j];
                solution[i][j] = 2; // 위쪽 방향
            }
            else
            {
                curr[j] = curr[j - 1];
                solution[i][j] = 3; // 왼쪽 방향
            }
        }
        prev.swap(curr);
    }

    // 실제 LCS 문자열을 복구
    string lcs_str;
    int i = m, j = n;

    while (i > 0 && j > 0)
    {
        if (solution[i][j] == 1)
        { // 대각선 방향으로 이동
            lcs_str.push_back(X[i - 1]);
            --i;
            --j;
        }
        else if (solution[i][j] == 2) // 위쪽 방향으로 이동
            --i;
        else if (solution[i][j] == 3) // 왼쪽 방향으로 이동
            --j;
    }
    reverse(lcs_str.begin(), lcs_str.end()); // 문자열을 뒤집어 올바른 순서로 만듦
    return lcs_str;                          // LCS 문자열 반환
}

int main()
{
    string str1, str2;

    cout << "string 1: ";
    getline(cin, str1);

    cout << "string 2: ";
    getline(cin, str2);

    int len = lcs_len(str1, str2);    // (iii) LCS 길이 계산
    string lcs_str = lcs(str1, str2); // (i) 실제 LCS 문자열 복구

    cout << "LCS 길이: " << len << endl;
    cout << "LCS: " << lcs_str << endl;

    return 0;
}
