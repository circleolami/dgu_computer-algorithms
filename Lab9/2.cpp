#include <iostream>
#include <vector>
#include <climits>
#include <random>

using namespace std;

// Brute-force 방법
void maxSubarrayBruteForce(const vector<int> &nums, int &start, int &end, int &maxSum, int &comparisons)
{
    int n = nums.size();
    maxSum = INT_MIN;
    start = 0;
    end = 0;
    comparisons = 0;

    for (int i = 0; i < n; ++i)
    {
        for (int j = i; j < n; ++j)
        {
            int currentSum = 0;
            for (int k = i; k <= j; ++k)
            {
                currentSum += nums[k];
                comparisons++;
            }
            if (currentSum > maxSum || (currentSum == maxSum && (j - i < end - start)))
            {
                maxSum = currentSum;
                start = i;
                end = j;
            }
        }
    }
}

// Divide-and-Conquer 보조 함수
int maxCrossingSum(const vector<int> &nums, int left, int mid, int right, int &start, int &end)
{
    int leftSum = INT_MIN, rightSum = INT_MIN;
    int sum = 0, maxLeft = mid, maxRight = mid;

    for (int i = mid; i >= left; --i)
    {
        sum += nums[i];
        if (sum > leftSum)
        {
            leftSum = sum;
            maxLeft = i;
        }
    }

    sum = 0;
    for (int i = mid + 1; i <= right; ++i)
    {
        sum += nums[i];
        if (sum > rightSum)
        {
            rightSum = sum;
            maxRight = i;
        }
    }
    start = maxLeft;
    end = maxRight;
    return leftSum + rightSum;
}

// 수정된 Divide-and-Conquer 방식
int maxSubarrayDivideConquer(const vector<int> &nums, int left, int right, int &start, int &end)
{
    if (right - left + 1 <= 10)
    {
        int maxSum, comparisons;
        maxSubarrayBruteForce(nums, start, end, maxSum, comparisons);
        return maxSum;
    }

    int mid = left + (right - left) / 2;
    int leftStart, leftEnd, rightStart, rightEnd, crossStart, crossEnd;
    int leftSum = maxSubarrayDivideConquer(nums, left, mid, leftStart, leftEnd);
    int rightSum = maxSubarrayDivideConquer(nums, mid + 1, right, rightStart, rightEnd);
    int crossSum = maxCrossingSum(nums, left, mid, right, crossStart, crossEnd);

    if (leftSum >= rightSum && leftSum >= crossSum)
    {
        start = leftStart;
        end = leftEnd;
        return leftSum;
    }
    else if (rightSum >= leftSum && rightSum >= crossSum)
    {
        start = rightStart;
        end = rightEnd;
        return rightSum;
    }
    else
    {
        start = crossStart;
        end = crossEnd;
        return crossSum;
    }
}

int main()
{
    int N;

    cin >> N;

    vector<int> nums(N);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(-100, 100);

    for (int i = 0; i < N; ++i)
    {
        nums[i] = dis(gen);
    }

    int start, end, maxSum;

    // Divide-and-Conquer 결과
    maxSum = maxSubarrayDivideConquer(nums, 0, N - 1, start, end);
    cout << "Divide-and-Conquer 결과: subarray 위치 = [" << start << ", " << end << "], 합 = " << maxSum << endl;

    return 0;
}
