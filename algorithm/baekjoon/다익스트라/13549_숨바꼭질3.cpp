/*
* 백준 13549번 숨바꼭질3
* https://www.acmicpc.net/problem/13549
* 그래프 탐색 이론 - 다익스트라
* 다익스트라에서는 정점 방문을 먼저 하면 안된다. 해당 정점에 도착했을 때 정점 방문을 해야함.
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int startSubinPoint, broPoint;
int ans;
bool visit[100001];

void dijikstra() {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
	pq.push({ 0, startSubinPoint });
	while (!pq.empty()) {
		int curTime = pq.top().first;
		int curPoint = pq.top().second;
		pq.pop();

		if (visit[curPoint]) { continue; }

		visit[curPoint] = true;

		if (curPoint == broPoint) {
			ans = curTime;
			return;
		}

		if (curPoint + 1 <= 100000) {
			pq.push({ curTime + 1, curPoint + 1 });
		}

		if (curPoint - 1 >= 0) {
			pq.push({ curTime + 1, curPoint - 1 });
		}

		if (curPoint * 2 <= 100000) {
			pq.push({ curTime, curPoint * 2 });
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> startSubinPoint >> broPoint;

	dijikstra();

	cout << ans;

	return 0;
}
