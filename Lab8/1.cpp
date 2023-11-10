#include <iostream>
#include <vector>

using namespace std;

int recursive_calls = 0;

int recursiveFib(int n) {
	if (n == 1 || n == 2) {
		recursive_calls++;
		return 1;
	}
	else {
		return recursiveFib(n - 1) + recursiveFib(n - 2);
	}
}

int dynamicFib(int n, vector<int>& f) {
	int dynamic_calls = 0;
	f[1] = f[2] = 1;
	for (int i = 3; i <= n; ++i) {
		dynamic_calls++;
		f[i] = f[i - 1] + f[i - 2];
	}
	return dynamic_calls;
}

int main() {
	int n;
	
	cin >> n;

	recursiveFib(n);
	vector<int> f(n + 1, 0);
	int dynamic_calls = dynamicFib(n, f);

	cout << "재귀함수 호출 횟수: " << recursive_calls << endl;
	cout << "동적알고리즘 호출 횟수: " << dynamic_calls << endl;
}