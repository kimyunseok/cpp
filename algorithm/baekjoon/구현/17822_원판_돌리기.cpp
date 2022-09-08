/*
* 백준 17822번 원판 돌리기
* https://www.acmicpc.net/problem/17822
* 구현 / 시뮬레이션
*/
#include <iostream>

using namespace std;

struct Point {
	int i;
	int j;
};

bool currentSameCheck;
bool foundSameNum;
int boardCnt, numberCnt, turnCnt;
int board[51][51];
bool visit[51][51];
Point directions[4] = {
	{-1, 0},
	{1, 0},
	{0, -1},
	{0, 1}
};

void updateByAverage() {
	double numCnt = 0;
	double currentSum = 0;
	for (int boardIdx = 1; boardIdx <= boardCnt; boardIdx++) {
		for (int j = 1; j <= numberCnt; j++) {
			if (board[boardIdx][j] != 0) {
				numCnt++;
				currentSum += board[boardIdx][j];
			}
		}
	}

	double avg = currentSum / numCnt;

	for (int boardIdx = 1; boardIdx <= boardCnt; boardIdx++) {
		for (int j = 1; j <= numberCnt; j++) {
			if (board[boardIdx][j] != 0) {
				if (board[boardIdx][j] > avg) board[boardIdx][j]--;
				else if (board[boardIdx][j] < avg) board[boardIdx][j]++;
			}
		}
	}

}

void dfs(int boardIdx, int j, int num) {
	if (visit[boardIdx][j]) return;

	visit[boardIdx][j] = true;

	if (num == board[boardIdx][j]) {
		currentSameCheck = true;
		foundSameNum = true;
		board[boardIdx][j] = 0;
	}

	for (Point point : directions) {
		int nxtBoard = boardIdx + point.i;
		int nxtNumber = j + point.j;
		if (nxtBoard < 1 || nxtBoard > boardCnt) continue;

		if (nxtNumber < 1) nxtNumber = numberCnt;
		else if (nxtNumber > numberCnt) nxtNumber = 1;

		if (!visit[nxtBoard][nxtNumber] && board[nxtBoard][nxtNumber] == num) {
			dfs(nxtBoard, nxtNumber, num);
		}
	}
}

void findSameNum() {
	for (int boardIdx = 1; boardIdx <= boardCnt; boardIdx++) {
		for (int j = 1; j <= numberCnt; j++) {


			for (int r = 1; r <= boardCnt; r++) {
				for (int c = 1; c <= numberCnt; c++) {
					visit[r][c] = false;
				}
			}

			if (board[boardIdx][j] == 0) continue;

			currentSameCheck = false;

			for (Point point : directions) {
				int nxtBoard = boardIdx + point.i;
				int nxtNumber = j + point.j;
				if (nxtBoard < 1 || nxtBoard > boardCnt) continue;

				if (nxtNumber < 1) nxtNumber = numberCnt;
				else if (nxtNumber > numberCnt) nxtNumber = 1;

				if (!visit[nxtBoard][nxtNumber] && board[nxtBoard][nxtNumber] == board[boardIdx][j]) {
					dfs(nxtBoard, nxtNumber, board[boardIdx][j]);
				}
			}

			if (currentSameCheck) board[boardIdx][j] = 0;

		}
	}
}

void turnClockWise(int boardIdx) {
	int prevSave = board[boardIdx][1];
	
	for (int i = 2; i <= numberCnt; i++) {
		int tmpSave = board[boardIdx][i];
		board[boardIdx][i] = prevSave;
		prevSave = tmpSave;
	}

	board[boardIdx][1] = prevSave;
}

void turnClockReverseWise(int boardIdx) {
	int prevSave = board[boardIdx][numberCnt];

	for (int i = numberCnt - 1; i >= 1; i--) {
		int tmpSave = board[boardIdx][i];
		board[boardIdx][i] = prevSave;
		prevSave = tmpSave;
	}

	board[boardIdx][numberCnt] = prevSave;
}

int main() {
	cin >> boardCnt >> numberCnt >> turnCnt;
	
	for (int i = 1; i <= boardCnt; i++) {
		for (int j = 1; j <= numberCnt; j++) {
			cin >> board[i][j];
		}
	}

	int num, direction, goCnt;
	while (turnCnt--) {
		cin >> num >> direction >> goCnt;

		for (int i = 1; i <= boardCnt; i++) {
			if (i % num == 0) {
				for (int j = 1; j <= goCnt; j++) {
					if (direction == 0) {
						turnClockWise(i);
					}
					else {
						turnClockReverseWise(i);
					}
				}
			}
		}

		//cout << "\TURN\n";
		//for (int i = 1; i <= boardCnt; i++) {
		//	for (int j = 1; j <= numberCnt; j++) {
		//		cout << board[i][j] << " ";
		//	}
		//	cout << "\n";
		//}
		//cout << "\n";

		foundSameNum = false;

		findSameNum();

		if (!foundSameNum) {
			updateByAverage();
		}

		//cout << "\FINAL\n";
		//for (int i = 1; i <= boardCnt; i++) {
		//	for (int j = 1; j <= numberCnt; j++) {
		//		cout << board[i][j] << " ";
		//	}
		//	cout << "\n";
		//}
		//cout << "\n";
	}

	int result = 0;

	for (int i = 1; i <= boardCnt; i++) {
		for (int j = 1; j <= numberCnt; j++) {
			//cout << board[i][j] << " ";
			result += board[i][j];
		}
		//cout << "\n";
	}

	cout << result;

	return 0;
}