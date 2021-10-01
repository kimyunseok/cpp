/*
* 백준 17142번 연구소 3
* https://www.acmicpc.net/problem/17142
* 그래프 탐색 이론 - 너비 우선 탐색(BFS)
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

int widthHeight, virusCnt;
int totalEmptySpace;
int board[51][51];
bool visit[51][51];
vector<pair<int, int>> canPutVirusPointVec;
vector<pair<int, int>> currentVirusPointVec;
pair<int, int> direction[4] = {
	{-1, 0},
	{1, 0},
	{0, -1},
	{0, 1}
};
int ans = 100000000;

int spreadVirus() {
	memset(visit, false, sizeof(visit));
	int tmpBoard[51][51];
	int tmpEmpty = totalEmptySpace;
	int retTime = 0;
	for (int i = 1; i <= widthHeight; i++) {
		for (int j = 1; j <= widthHeight; j++) {
			tmpBoard[i][j] = board[i][j];
		}
	}
	queue< pair<int, pair<int, int> > > q;

	for (pair<int, int> point : currentVirusPointVec) {
		int time = 0;
		int r = point.first;
		int c = point.second;
		tmpBoard[r][c] = time;
		q.push({ time, {r,c} });
		visit[r][c] = true;
	}

	while (!q.empty()) {
		bool move = false;
		int curTime = q.front().first;
		int curR = q.front().second.first;
		int curC = q.front().second.second;
		q.pop();

		for (pair<int, int> direc : direction) {
			int nxtTime = curTime + 1;
			int nxtR = curR + direc.first;
			int nxtC = curC + direc.second;
			if (nxtR < 1 || nxtR > widthHeight || nxtC < 1 || nxtC > widthHeight ||
				visit[nxtR][nxtC] == true || tmpBoard[nxtR][nxtC] == '-') {
				continue;
			}

			move = true;
			visit[nxtR][nxtC] = true;
			if (tmpBoard[nxtR][nxtC] == '*') {
				q.push({ nxtTime, {nxtR, nxtC} });
			}
			else {
				tmpEmpty--;
				q.push({ nxtTime, {nxtR, nxtC} });
			}
		}

		if (tmpBoard[curR][curC] != '*') {
			retTime = max(retTime, curTime);
		}
		tmpBoard[curR][curC] = curTime;
	}

	if (tmpEmpty == 0) {
		return retTime;
	}
	else {
		return -1;
	}
}

void go(int idx, int startVecIdx) {
	if (idx > virusCnt) {
		int ret = spreadVirus();
		if (ret != -1) {
			ans = min(ans, ret);
		}
	}
	else {
		for (int i = startVecIdx; i < canPutVirusPointVec.size(); i++) {
			int r = canPutVirusPointVec[i].first;
			int c = canPutVirusPointVec[i].second;
			currentVirusPointVec.push_back({ r, c });
			go(idx + 1, i + 1);
			currentVirusPointVec.pop_back();
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> widthHeight >> virusCnt;

	for (int i = 1; i <= widthHeight; i++) {
		for (int j = 1; j <= widthHeight; j++) {
			cin >> board[i][j];
			if (board[i][j] == 0) { totalEmptySpace++; }
			else if (board[i][j] == 1) {
				board[i][j] = '-';
			}
			else if (board[i][j] == 2) {
				board[i][j] = '*';
				canPutVirusPointVec.push_back({ i, j });
			}
		}
	}

	go(1, 0);

	if (ans != 100000000) {
		cout << ans;
	}
	else {
		cout << "-1";
	}

	return 0;
}