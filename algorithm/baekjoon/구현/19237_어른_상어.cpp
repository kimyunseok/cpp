/*
* 백준 19237번 어른 상어
* https://www.acmicpc.net/problem/19237
* - 구현 / 시뮬레이션
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Shark {
	int number = -1;
	int r = 0;
	int c = 0;
	int watchingDirection = 0;
	int priorityDirection[5][5];
	bool isRemoved = false;
};

struct SharkMapInfo {
	int sharkCnt = 0;
	int smellNumber = -1;
	int smellIdx = -1;
};

pair<int, int> directions[5] = {
	{-1, -1},
	{-1, 0},
	{1, 0},
	{0, -1},
	{0, 1}
};

int widthHeight, sharkCnt, smellRemainTime;
SharkMapInfo sharkMapInfo[21][21];
vector<Shark> sharkVec;
int result = -1;

bool comp(Shark s1, Shark s2) {
	return s1.number < s2.number;
}

void go(int idx) {
	if (idx > 1000) return;

	//0. 냄새 제거
	for (int r = 1; r <= widthHeight; r++) {
		for (int c = 1; c <= widthHeight; c++) {
			if (sharkMapInfo[r][c].smellIdx > 0) {
				sharkMapInfo[r][c].smellIdx--;
				
				if (sharkMapInfo[r][c].smellIdx == 0) {
					sharkMapInfo[r][c].smellIdx = -1;
					sharkMapInfo[r][c].smellNumber = -1;
				}
			}
		}
	}

	//1. 냄새 남기기
	for (int i = 0; i < sharkCnt; i++) {
		if (!sharkVec[i].isRemoved) {
			sharkMapInfo[sharkVec[i].r][sharkVec[i].c].smellNumber = sharkVec[i].number;
			sharkMapInfo[sharkVec[i].r][sharkVec[i].c].smellIdx = smellRemainTime;
		}
	}

	//2. 이동
	for (int i = 0; i < sharkCnt; i++) {
		if (!sharkVec[i].isRemoved) {
			bool sharkMoved = false;
			// - 1. 냄새가 없는 지 Check
			for (int j = 1; j <= 4; j++) {
				int dir = sharkVec[i].priorityDirection[sharkVec[i].watchingDirection][j];
				int nxtR = sharkVec[i].r + directions[dir].first;
				int nxtC = sharkVec[i].c + directions[dir].second;

				if (nxtR < 1 || nxtR > widthHeight || nxtC < 1 || nxtC > widthHeight || sharkMapInfo[nxtR][nxtC].smellNumber != -1) continue;
				
				sharkMapInfo[sharkVec[i].r][sharkVec[i].c].sharkCnt--;
				sharkVec[i].r = nxtR;
				sharkVec[i].c = nxtC;
				sharkVec[i].watchingDirection = dir;
				sharkMapInfo[nxtR][nxtC].sharkCnt++;
				sharkMoved = true;
				break;
			}

			// - 2. 같은 냄새 있는 지 Check
			if (!sharkMoved) {
				for (int j = 1; j <= 4; j++) {
					int dir = sharkVec[i].priorityDirection[sharkVec[i].watchingDirection][j];
					int nxtR = sharkVec[i].r + directions[dir].first;
					int nxtC = sharkVec[i].c + directions[dir].second;

					if (nxtR < 1 || nxtR > widthHeight || nxtC < 1 || nxtC > widthHeight || sharkMapInfo[nxtR][nxtC].smellNumber != sharkVec[i].number) continue;

					sharkMapInfo[sharkVec[i].r][sharkVec[i].c].sharkCnt--;
					sharkVec[i].r = nxtR;
					sharkVec[i].c = nxtC;
					sharkVec[i].watchingDirection = dir;
					sharkMapInfo[nxtR][nxtC].sharkCnt++;
					break;
				}
			}

		}
	}

	//3. 두 마리 이상 상어 있는 칸에서 제일 작은 번호만 남기기
	for (int r = 1; r <= widthHeight; r++) {
		for (int c = 1; c <= widthHeight; c++) {
			if (sharkMapInfo[r][c].sharkCnt > 1) {
				bool minimumFind = false;
				for (int k = 0; k < sharkCnt; k++) {
					if (!sharkVec[k].isRemoved && sharkVec[k].r == r && sharkVec[k].c == c) {
						if (!minimumFind) minimumFind = true;
						else {
							sharkVec[k].isRemoved = true;
							sharkMapInfo[r][c].sharkCnt--;
						}
					}
				}
			}
		}
	}

	int aliveSharkCnt = 0;
	for (int i = 0; i < sharkCnt; i++) {
		if (!sharkVec[i].isRemoved) aliveSharkCnt++;
	}

	if (aliveSharkCnt == 1) {
		result = idx;
		return;
	}
	else go(idx + 1);
}

int main() {
	cin >> widthHeight >> sharkCnt >> smellRemainTime;

	int input;
	for (int i = 1; i <= widthHeight; i++) {
		for (int j = 1; j <= widthHeight; j++) {
			cin >> input;
			if (input != 0) {
				sharkMapInfo[i][j].sharkCnt++;
				sharkVec.push_back({ input, i, j });
			}
		}
	}

	sort(sharkVec.begin(), sharkVec.end(), comp);

	int watchDir;
	for (int i = 0; i < sharkCnt; i++) {
		cin >> watchDir;
		sharkVec[i].watchingDirection = watchDir;
	}

	for (int i = 0; i < sharkCnt; i++) {
		for (int j = 1; j <= 4; j++) {
			for (int k = 1; k <= 4; k++) {
				cin >> sharkVec[i].priorityDirection[j][k];
			}
		}
	}

	go(1);

	cout << result;

	return 0;

}