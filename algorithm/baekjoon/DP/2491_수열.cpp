/*
* 백준 2491번 수열
* https://www.acmicpc.net/problem/2491
* 다이나믹 프로그래밍
*/
#include <iostream>
using namespace std;

int numLength;
int num[100001];
int dpBig[100001];
int dpSmall[100001];
int ans;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> numLength;

	for (int i = 1; i <= numLength; i++) {
		cin >> num[i];
	}

	dpBig[1] = 1;
	ans = 1;

	for (int i = 2; i <= numLength; i++) {
		if (num[i] >= num[i - 1]) {
			dpBig[i] = dpBig[i - 1] + 1;
		}
		else {
			dpBig[i] = 1;
		}
		ans = max(ans, dpBig[i]);
	}

	dpSmall[1] = 1;

	for (int i = 2; i <= numLength; i++) {
		if (num[i] <= num[i - 1]) {
			dpSmall[i] = dpSmall[i - 1] + 1;
		}
		else {
			dpSmall[i] = 1;
		}
		ans = max(ans, dpSmall[i]);
	}

	cout << ans;

	return 0;
}
