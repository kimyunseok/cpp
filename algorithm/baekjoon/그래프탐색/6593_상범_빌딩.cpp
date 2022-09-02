/*
* 백준 6593번 상범 빌딩
* https://www.acmicpc.net/problem/6593
* 그래프 탐색 이론 - 너비 우선 탐색(BFS)
*/
#include <iostream>
#include <string>
#include <queue>

using namespace std;

struct Point {
	int l;
	int r;
	int c;
};

Point startPoint;
int buildingFloor, height, width;
char building[31][31][31];
bool visit[31][31][31];
int result = -1;

Point directions[6] = {
	{-1, 0, 0},
	{1, 0, 0},
	{0, -1, 0},
	{0, 1, 0},
	{0, 0, -1},
	{0, 0, 1}
};

void bfs() {

	result = -1;

	for (int i = 1; i <= buildingFloor; i++) {
		for (int j = 1; j <= height; j++) {
			for (int k = 1; k <= width; k++) {
				visit[i][j][k] = false;
			}
		}
	}

	queue<pair<Point, int>> q;
	q.push({ startPoint, 0 });
	visit[startPoint.l][startPoint.r][startPoint.c] = true;

	while (!q.empty()) {
		Point point = q.front().first;
		int idx = q.front().second;
		q.pop();

		if (building[point.l][point.r][point.c] == 'E') {
			result = idx;
			return;
		}

		for (Point direction : directions) {
			int nxtL = point.l + direction.l;
			int nxtR = point.r + direction.r;
			int nxtC = point.c + direction.c;

			if(nxtL < 1 || nxtL > buildingFloor || 
				nxtR < 1 || nxtR > height ||
				nxtC < 1 || nxtC > width || 
				visit[nxtL][nxtR][nxtC] ||
				building[nxtL][nxtR][nxtC] == '#') {
				continue;
			}

			visit[nxtL][nxtR][nxtC] = true;
			q.push({ {nxtL, nxtR, nxtC}, idx + 1 });
		}
	}
}

int main() {
	while (true) {
		cin >> buildingFloor >> height >> width;

		if (buildingFloor == 0 && height == 0 && width == 0) break;

		for (int i = 1; i <= buildingFloor; i++) {
			for (int j = 1; j <= height; j++) {
				for (int k = 1; k <= width; k++) {
					cin >> building[i][j][k];
					if (building[i][j][k] == 'S') {
						startPoint.l = i;
						startPoint.r = j;
						startPoint.c = k;
					}
				}
			}
		}

		bfs();

		if (result != -1) {
			cout << "Escaped in " << result << " minute(s).\n";
		}
		else {
			cout << "Trapped!\n";
		}
	}

	return 0;
}
