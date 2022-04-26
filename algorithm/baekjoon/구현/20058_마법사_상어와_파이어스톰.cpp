/*
* 백준 20058번 마법사 상어와 파이어스톰
* https://www.acmicpc.net/problem/20058
* 구현 / 시뮬레이션 / 그래프 탐색
*/
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int iceMap[65][65];
int saveIce[65][65];
bool visit[65][65];
int n, widthHeight, magicCnt;
int sumOfIce, largeIceCnt;
queue<pair<int, int>> meltingQueue;
pair<int, int> iceDirection[4] = {
	{-1, 0},
	{0, 1},
	{1, 0},
	{0, -1}
};

void fireStorm(int startR, int startC, int _level,int partialIceSize) {

	for (int i = startR; i < startR + partialIceSize; i++) {
		int addR = startR - i;
		int addC = partialIceSize - 1 + addR;
		for (int j = startC; j < startC + partialIceSize; j++) {
			iceMap[i + addR][j + addC] = saveIce[i][j];
			addR++;
			addC--;
		}
	}

}

void bfs(int r, int c) {
	queue<pair<int, int>> q;
	q.push({r, c});
	visit[r][c] = true;
	int currentIceSize = 1;
	while (!q.empty()) {
		int r = q.front().first;
		int c = q.front().second;
		q.pop();

		for (pair<int, int> dir : iceDirection) {
			int nxtR = r + dir.first;
			int nxtC = c + dir.second;

			if (nxtR > widthHeight || nxtR < 1 || nxtC > widthHeight || nxtC < 1 || visit[nxtR][nxtC] || iceMap[nxtR][nxtC] == 0) { continue; }

			currentIceSize++;
			visit[nxtR][nxtC] = true;
			q.push({ nxtR, nxtC });
		}
	}

	largeIceCnt = max(largeIceCnt, currentIceSize);
}

int main() {
	cin >> n >> magicCnt;

	widthHeight = 1;
	for (int i = 1; i <= n; i++) {
		widthHeight *= 2;
	}

	for (int i = 1; i <= widthHeight; i++) {
		for (int j = 1; j <= widthHeight; j++) {
			cin >> iceMap[i][j];
			saveIce[i][j] = iceMap[i][j];
		}
	}

	int level;
	while (magicCnt--) {
		cin >> level;
		int partialIceSize = 1;
		for (int i = 1; i <= level; i++) {
			partialIceSize *= 2;
		}

		for (int i = 1; i <= widthHeight; i++) {
			for (int j = 1; j <= widthHeight; j++) {
				// 얼음량 저장
				saveIce[i][j] = iceMap[i][j];
			}
		}

		for (int i = 1; i <= widthHeight; i += partialIceSize) {
			for (int j = 1; j <= widthHeight; j += partialIceSize) {
				fireStorm(i, j, level - 1, partialIceSize);
			}
		}

		//2. 얼음 인접한 칸 3, 4개와 인정해있지 않은 칸 얼음 양 1 줄어듦
		for (int i = 1; i <= widthHeight; i++) {
			for (int j = 1; j <= widthHeight; j++) {

				int adjIceCnt = 0;
				for (pair<int, int> dir : iceDirection) {
					int nxtR = i + dir.first;
					int nxtC = j + dir.second;

					if (nxtR > widthHeight || nxtR < 1 || nxtC > widthHeight || nxtC < 1 || iceMap[nxtR][nxtC] == 0) {
						continue;
					}
					adjIceCnt++;
				}

				if (adjIceCnt < 3) {
					meltingQueue.push({ i, j });
				}
			}
		}

		while (!meltingQueue.empty()) {
			int r = meltingQueue.front().first;
			int c = meltingQueue.front().second;
			meltingQueue.pop();
			if (iceMap[r][c] > 0) {
				iceMap[r][c]--;
			}
		}

		//cout << "\n";
		//for (int i = 1; i <= widthHeight; i++) {
		//	for (int j = 1; j <= widthHeight; j++) {
		//		cout << iceMap[i][j] << " ";
		//	}
		//	cout << "\n";
		//}

	}

	for (int i = 1; i <= widthHeight; i++) {
		for (int j = 1; j <= widthHeight; j++) {
			sumOfIce += iceMap[i][j];
			if (!visit[i][j] && iceMap[i][j] > 0) {
				bfs(i, j);
			}
		}
	}

	cout << sumOfIce << "\n" << largeIceCnt;

	return 0;
}