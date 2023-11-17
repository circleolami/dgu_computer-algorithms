#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <numeric>

using namespace std;

struct Activity
{
    int start;
    int finish;
    int index;
};

// Dynamic Programming 방법
vector<int> dynamicProgramming(const vector<Activity> &activities, long long &dpComparisons)
{
    int n = activities.size();
    vector<int> dp(n), last(n, -1);
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);

    sort(order.begin(), order.end(), [&](int i, int j)
         { return activities[i].finish < activities[j].finish; });

    dp[0] = 1;
    dpComparisons = 0;
    for (int i = 1; i < n; ++i)
    {
        dp[i] = 1;
        for (int j = 0; j < i; ++j)
        {
            dpComparisons++;
            if (activities[order[j]].finish <= activities[order[i]].start)
            {
                if (dp[j] + 1 > dp[i])
                {
                    dp[i] = dp[j] + 1;
                    last[i] = j;
                }
            }
        }
    }

    vector<int> selected;
    int maxIndex = max_element(dp.begin(), dp.end()) - dp.begin();
    for (int i = maxIndex; i != -1; i = last[i])
    {
        selected.push_back(order[i]);
    }
    reverse(selected.begin(), selected.end());

    return selected;
}

// Greedy Algorithm 방법
vector<int> greedyAlgorithm(vector<Activity> &activities, long long &greedyComparisons)
{
    sort(activities.begin(), activities.end(), [](const Activity &a, const Activity &b)
         { return a.finish < b.finish; });

    vector<int> selected;
    int lastFinishTime = -1;
    greedyComparisons = 0;

    for (const auto &activity : activities)
    {
        greedyComparisons++;
        if (activity.start >= lastFinishTime)
        {
            selected.push_back(activity.index);
            lastFinishTime = activity.finish;
        }
    }

    return selected;
}

void printVector(const vector<int> &vec)
{
    for (size_t i = 0; i < vec.size(); ++i)
    {
        cout << vec[i];
        if (i < vec.size() - 1)
            cout << ", ";
    }
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    int N;

    cin >> N;

    vector<Activity> activities(N);

    for (int i = 0; i < N; ++i)
    {
        activities[i].start = rand() % (N - 1);
        activities[i].finish = activities[i].start + 1 + (rand() % 9);
        activities[i].index = i;
    }

    long long dpComparisons, greedyComparisons;
    vector<int> dpResult = dynamicProgramming(activities, dpComparisons);
    vector<int> greedyResult = greedyAlgorithm(activities, greedyComparisons);

    cout << "Dynamic Programming 결과: 강좌 = [";
    printVector(dpResult);
    cout << "], 비교횟수 = " << dpComparisons << endl;

    cout << "Greedy Algorithm 결과: 강좌 = [";
    printVector(greedyResult);
    cout << "], 비교횟수 = " << greedyComparisons << endl;

    return 0;
}
