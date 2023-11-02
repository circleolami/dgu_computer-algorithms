#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int bruteForceSearch(const vector<vector<char>> &text, const vector<vector<char>> &pattern)
{
    int R = text.size();
    int C = text[0].size();
    int r = pattern.size();
    int c = pattern[0].size();
    int count = 0;

    for (int i = 0; i <= R - r; i++)
    {
        for (int j = 0; j <= C - c; j++)
        {
            bool matchFound = true;
            for (int di = 0; di < r; di++)
            {
                for (int dj = 0; dj < c; dj++)
                {
                    count++;
                    if (text[i + di][j + dj] != pattern[di][dj])
                    {
                        matchFound = false;
                        break;
                    }
                }
                if (!matchFound)
                    break;
            }
        }
    }
    return count;
}

int rabinKarpSearch(const vector<vector<char>> &text, const vector<vector<char>> &pattern, int q)
{
    int R = text.size(), C = text[0].size(), r = pattern.size(), c = pattern[0].size();
    int count = 0, d = 256;

    int p = 0, t = 0, h = 1;

    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            p = (d * p + pattern[i][j]) % q;
            t = (d * t + text[i][j]) % q;
        }
    }

    for (int i = 0; i < c - 1; i++)
    {
        h = (h * d) % q;
    }

    for (int i = 0; i <= R - r; i++)
    {
        for (int j = 0; j <= C - c; j++)
        {
            count++;
            if (p == t)
            {
                bool flag = true;
                for (int di = 0; di < r; di++)
                {
                    for (int dj = 0; dj < c; dj++)
                    {
                        if (text[i + di][j + dj] != pattern[di][dj])
                        {
                            flag = false;
                            break;
                        }
                    }
                    if (!flag)
                        break;
                }
            }
            if (j < C - c)
            {
                t = (d * (t - text[i][j] * h) + text[i][j + c]) % q;
                if (t < 0)
                    t = (t + q);
            }
        }
    }

    return count;
}

int main()
{
    vector<vector<char>> text(100, vector<char>(100, 'A'));
    vector<vector<char>> pattern(10, vector<char>(10, 'A'));
    pattern[9][9] = 'B';

    int bruteForceCount = bruteForceSearch(text, pattern);
    cout << bruteForceCount << " (Brute Force 문자열 비교 횟수) " << endl;

    vector<int> qs = {10, 100, 1000, 10000};
    for (int q : qs)
    {
        int rabinKarpCount = rabinKarpSearch(text, pattern, q);
        cout << rabinKarpCount << " (Rabin-Karp 문자열 비교 횟수 (q=" << q << ")) " << endl;
    }

    return 0;
}
