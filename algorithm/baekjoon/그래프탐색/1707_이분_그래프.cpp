/*
* 백준 1707번 이분 그래프
* https://www.acmicpc.net/problem/1707
* 그래프 탐색 이론
*/
#include <iostream>
#include <vector>
using namespace std;

int tc;
int vertexCnt, edgeCnt;
vector<int> adjList[20001];
int color[20001];
bool ans;

void coloring(int num, int colorNum) {
	color[num] = colorNum;

	int nxtColorNum = (colorNum == 1) ? 2 : 1;

	for (int adjNum : adjList[num]) {
		if (color[adjNum] == 0) {
			coloring(adjNum, nxtColorNum);
		}
	}
}

bool checkColor(int num) {
	for (int adjNum : adjList[num]) {
		if (color[adjNum] == color[num]) {
			return false;
		}
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> tc;

	while (tc--) {
		for (int i = 1; i <= vertexCnt; i++) {
			adjList[i].clear();
			color[i] = 0;
		}
		ans = true;

		cin >> vertexCnt >> edgeCnt;

		int num1, num2;
		for (int i = 1; i <= edgeCnt; i++) {
			cin >> num1 >> num2;
			adjList[num1].push_back(num2);
			adjList[num2].push_back(num1);
		}

		for (int i = 1; i <= vertexCnt; i++) {
			if (color[i] == 0) {
				coloring(i, 1);
			}
		}

		for (int i = 1; i <= vertexCnt; i++) {
			if (!checkColor(i)) {
				ans = false;
				break;
			}
		}

		if (ans) {
			cout << "YES\n";
		}
		else {
			cout << "NO\n";
		}
	}

	return 0;
}
