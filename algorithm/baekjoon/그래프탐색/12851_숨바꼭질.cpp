/*
* 백준 12851번 숨바꼭질 2
* https://www.acmicpc.net/problem/12851
* 그래프 탐색 이론 - 너비 우선 탐색(BFS)
*/
#include <iostream>
#include <queue>
using namespace std;

int startSubinPoint, broPoint;
bool findBro;
int pointTime[100001];
int ansTime = 100000000;
int ansCnt;

void bfs() {
	queue<pair<int, int>> q;
	q.push({ 0, startSubinPoint });
	while (!q.empty()) {
		int curTime = q.front().first;
		int curPoint = q.front().second;
		q.pop();

		pointTime[curPoint] = curTime;

		if (findBro && curTime > ansTime) {
			continue;
		}

		if (curPoint == broPoint) {
			findBro = true;
			ansTime = curTime;
			ansCnt++;
			continue;
		}

		if (curPoint - 1 >= 0 && (pointTime[curPoint - 1] == 0 || curTime + 1 <= pointTime[curPoint - 1])) {
			q.push({ curTime + 1, curPoint - 1 });
		}

		if (curPoint + 1 <= 100000 && (pointTime[curPoint + 1] == 0 || curTime + 1 <= pointTime[curPoint + 1])) {
			q.push({ curTime + 1, curPoint + 1 });
		}

		if (curPoint * 2 <= 100000 && (pointTime[curPoint * 2] == 0 || curTime + 1 <= pointTime[curPoint * 2])) {
			q.push({ curTime + 1, curPoint * 2 });
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> startSubinPoint >> broPoint;

	bfs();

	cout << ansTime << "\n" << ansCnt;

	return 0;
}
