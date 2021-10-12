/*
* 백준 1890번 점프
* https://www.acmicpc.net/problem/1890
* 다이나믹 프로그래밍
*/
#include <iostream>
using namespace std;

int widthHeight;
int board[101][101];
long long dp[101][101];
bool visit[101][101];

long long go(int r, int c) {
	if (r == widthHeight && c == widthHeight) { return 1; }
	if (visit[r][c]) { return dp[r][c]; }

	visit[r][c] = true;

	pair<int, int> toRight = { r, c + board[r][c] };
	pair<int, int> toBottom = { r + board[r][c], c };

	if (toRight.second <= widthHeight) {
		dp[r][c] += go(r, toRight.second);
	}

	if (toBottom.first <= widthHeight) {
		dp[r][c] += go(toBottom.first, c);
	}

	return dp[r][c];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> widthHeight;

	for (int i = 1; i <= widthHeight; i++) {
		for (int j = 1; j <= widthHeight; j++) {
			cin >> board[i][j];
		}
	}

	go(1, 1);

	cout << dp[1][1];

	return 0;
}
