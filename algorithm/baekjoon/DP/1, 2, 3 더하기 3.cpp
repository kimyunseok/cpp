/*
* 백준 15988번 1, 2, 3 더하기 3
* https://www.acmicpc.net/problem/15988
* 다이나믹 프로그래밍
*/
#include <iostream>
using namespace std;

int tc, num;
long long cnt[1000001];

int main() {
	cout.tie(NULL);
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	cin >> tc;

	cnt[1] = 1;
	cnt[2] = 2;
	cnt[3] = 4;

	for (int i = 4; i <= 1000000; i++) {
		cnt[i] = cnt[i - 1];
		cnt[i] = (cnt[i] + cnt[i - 2]) % 1000000009;
		cnt[i] = (cnt[i] + cnt[i - 3]) % 1000000009;
	}

	while (tc--) {

		cin >> num;


		cout << cnt[num] << "\n";

	}
	return 0;
}