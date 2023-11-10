#include <iostream>
#include <vector>
#include <climits>

using namespace std;

pair<int, vector<int>> cut_rod(const vector<int> &prices, int n, int cost_per_cut)
{
    vector<int> r(n + 1, INT_MIN);
    vector<int> s(n + 1, 0);

    r[0] = 0;

    for (int j = 1; j <= n; ++j)
    {
        int q = INT_MIN;
        for (int i = 1; i <= j; ++i)
        {
            int current_price = (i < prices.size()) ? prices[i] : 0;
            int cost = (i < j) ? cost_per_cut : 0;
            if (q < current_price + r[j - i] - cost)
            {
                q = current_price + r[j - i] - cost;
                s[j] = i;
            }
        }
        r[j] = q;
    }

    vector<int> solution;
    int temp_n = n;
    while (temp_n > 0)
    {
        solution.push_back(s[temp_n]);
        temp_n -= s[temp_n];
    }

    return make_pair(r[n], solution);
}

int main()
{
    vector<int> prices = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int cost_per_cut = 2;
    int n;

    cin >> n;

    pair<int, vector<int>> result = cut_rod(prices, n, cost_per_cut);
    int max_revenue = result.first;
    vector<int> solution = result.second;

    cout << "길이: " << n << ", 최대 가격: " << max_revenue << endl;
    cout << "방법: ";
    for (size_t i = 0; i < solution.size(); ++i)
    {
        cout << solution[i];
        if (i < solution.size() - 1)
            cout << ", ";
    }
    cout << endl;

    return 0;
}
