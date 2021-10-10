/*
* 백준 1167번 트리의 지름
* https://www.acmicpc.net/problem/1167
* 그래프 탐색 이론 - 깊이 우선 탐색(DFS)
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int vertexCnt;
vector<pair<int, int>> adjVec[100001];
vector<int> distVec[100001];
bool visit[100001];
int ans;

int dfs(int vertexNum) {
	visit[vertexNum] = true;

	for (pair<int, int> p : adjVec[vertexNum]) {
		int nextVertexNum = p.first;
		int distance = p.second;

		if (!visit[nextVertexNum]) {
			int checkDist = distance + dfs(nextVertexNum);
			distVec[vertexNum].push_back(checkDist);
		}
	}

	sort(distVec[vertexNum].begin(), distVec[vertexNum].end());

	if (distVec[vertexNum].size() == 0) {
		return 0;
	}
	else if (distVec[vertexNum].size() == 1) {
		ans = max(ans, distVec[vertexNum][0]);
		return distVec[vertexNum][0];
	}
	else {
		int firstBigIdx = distVec[vertexNum].size() - 1;
		int secondBigIdx = distVec[vertexNum].size() - 2;

		int checkDiameter = distVec[vertexNum][firstBigIdx] + distVec[vertexNum][secondBigIdx];
		ans = max(ans, checkDiameter);

		return distVec[vertexNum][firstBigIdx];
	}

}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> vertexCnt;

	int vertexNum, adjVertexNum, distance;
	for (int i = 1; i <= vertexCnt; i++) {
		cin >> vertexNum;
		while (true) {
			cin >> adjVertexNum;
			if (adjVertexNum == -1) { break; }
			cin >> distance;
			adjVec[vertexNum].push_back({ adjVertexNum, distance });
		}
	}

for (int i = 1; i <= 100000; i++) {
	if (!visit[i] && adjVec[i].size() > 0) {
		dfs(i);
		break;
	}
}
 

	cout << ans;

	return 0;
}
