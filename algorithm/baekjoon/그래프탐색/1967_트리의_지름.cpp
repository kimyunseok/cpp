/*
* 백준 1967번 트리의 지름
* https://www.acmicpc.net/problem/1967
* 그래프 탐색 이론 - 깊이 우선 탐색
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int nodeCnt;
vector<pair<int, int>> adjList[10001];
bool visit[10001];
vector<int> childDistanceVec[10001];
int ans;

int dfs(int nodeNum) {

	if (visit[nodeNum]) {
		if (childDistanceVec[nodeNum].empty()) {
			return 0;
		}
		int bigIdx = childDistanceVec[nodeNum].size() - 1;
		return childDistanceVec[nodeNum][bigIdx];
	}

	visit[nodeNum] = true;

	for (pair<int, int> p : adjList[nodeNum]) {
		int nextNodeNum = p.first;
		int nextNodeDistance = p.second;

		int childDistance = nextNodeDistance + dfs(nextNodeNum);
		childDistanceVec[nodeNum].push_back(childDistance);
	}

	sort(childDistanceVec[nodeNum].begin(), childDistanceVec[nodeNum].end());

	if (childDistanceVec[nodeNum].empty()) {
		return 0;
	}
	else if (childDistanceVec[nodeNum].size() == 1) {
		int bigIdx = childDistanceVec[nodeNum].size() - 1;
		ans = max(ans, childDistanceVec[nodeNum][bigIdx]);
		return childDistanceVec[nodeNum][bigIdx];
	}
	else {
		int firstBig = childDistanceVec[nodeNum].size() - 1;
		int secondBig = childDistanceVec[nodeNum].size() - 2;
		ans = max(ans, childDistanceVec[nodeNum][firstBig] + childDistanceVec[nodeNum][secondBig]);
		return childDistanceVec[nodeNum][firstBig];
	}

}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> nodeCnt;

	int parNode, childNode, distance;
	for (int i = 1; i < nodeCnt; i++) {
		cin >> parNode >> childNode >> distance;
		adjList[parNode].push_back({ childNode, distance });
	}

	dfs(1);

	cout << ans;

	return 0;
}
