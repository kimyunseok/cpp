/*
* 백준 5014번 스타트링크
* https://www.acmicpc.net/problem/5014
* 그래프 탐색 이론 - 너비 우선 탐색
*/
#include <iostream>
#include <queue>
using namespace std;

int topFloor, startFloor, destinationFloor, upFloor, downFloor;
bool visit[1000001];
bool checkArrive;
int ans;

void bfs(int startFloor) {
	queue<pair<int, int>> q;
	q.push({ 0, startFloor });
	visit[startFloor] = true;

	while (!q.empty()) {
		int curFloor = q.front().second;
		int moveCnt = q.front().first;
		q.pop();

		if (curFloor == destinationFloor) {
			checkArrive = true;
			ans = moveCnt;
			return;
		}

		int goUpFloor = curFloor + upFloor;
		if (goUpFloor <= topFloor && !visit[goUpFloor]) {
			q.push({ moveCnt + 1, goUpFloor });
			visit[goUpFloor] = true;
		}

		int goDownFloor = curFloor - downFloor;
		if (goDownFloor >= 1 && !visit[goDownFloor]) {
			q.push({ moveCnt + 1, goDownFloor });
			visit[goDownFloor] = true;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> topFloor >> startFloor >> destinationFloor >> upFloor >> downFloor;

	bfs(startFloor);

	if (checkArrive) {
		cout << ans;
	}
	else {
		cout << "use the stairs";
	}

	return 0;
}
