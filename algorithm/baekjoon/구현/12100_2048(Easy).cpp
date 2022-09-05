/*
* 백준 12100번 2048 (Easy)
* https://www.acmicpc.net/problem/12100
* 구현 / 시뮬레이션
*/

#include <iostream>
#include <queue>

using namespace std;

struct BoardInfo {
	int board[21][21];
	int idx;
};

struct Point {
	int r;
	int c;
};

int widthHeight;
bool already[21][21];
int result;
queue<BoardInfo> q;

void go() {

	while (!q.empty()) {
		BoardInfo currentBoard = q.front();
		q.pop();
		if (currentBoard.idx > 5) { return; }

		//cout << "idx : " << currentBoard.idx << "\n";
		// 최대값 찾기.
		for (int j = 1; j <= widthHeight; j++) {
			for (int k = 1; k <= widthHeight; k++) {
				//cout << currentBoard.board[j][k] << " ";
				if (result < currentBoard.board[j][k]) {
					result = currentBoard.board[j][k];
				}
			}
			//cout << "\n";
		}
		//cout << "\n\n";
		//cout << currentBoard.idx << " , " << result << "\n";

		// 1. 위로 이동
		BoardInfo nextBoard;
		nextBoard.idx = currentBoard.idx + 1;
		for (int j = 1; j <= widthHeight; j++) {
			for (int k = 1; k <= widthHeight; k++) {
				nextBoard.board[j][k] = currentBoard.board[j][k];
				already[j][k] = false;
			}
		}

		for (int c = 1; c <= widthHeight; c++) {
			for (int r = 1; r <= widthHeight; r++) {
				int curR = r;
				int nxtR = r - 1;
				if (nextBoard.board[curR][c] == 0) { continue; }
				while (nxtR >= 1) {
					if (nextBoard.board[nxtR][c] == 0) {
						nextBoard.board[nxtR][c] = nextBoard.board[curR][c];
						nextBoard.board[curR][c] = 0;
						curR -= 1;
						nxtR -= 1;
					}
					else if (nextBoard.board[curR][c] == nextBoard.board[nxtR][c] && !already[nxtR][c]) {
						already[nxtR][c] = true;
						nextBoard.board[curR][c] = 0;
						nextBoard.board[nxtR][c] *= 2;
						break;
					}
					else {
						break;
					}
				}
			}
		}
		q.push(nextBoard);

		// 2. 우로 이동
		BoardInfo nextBoard2;
		nextBoard2.idx = currentBoard.idx + 1;
		for (int j = 1; j <= widthHeight; j++) {
			for (int k = 1; k <= widthHeight; k++) {
				nextBoard2.board[j][k] = currentBoard.board[j][k];
				already[j][k] = false;
			}
		}

		for (int r = 1; r <= widthHeight; r++) {
			for (int c = widthHeight; c >= 1; c--) {
				int curC = c;
				int nxtC = c + 1;
				if (nextBoard2.board[r][curC] == 0) { continue; }

				while (nxtC <= widthHeight) {
					if (nextBoard2.board[r][nxtC] == 0) {
						nextBoard2.board[r][nxtC] = nextBoard2.board[r][curC];
						nextBoard2.board[r][curC] = 0;
						curC += 1;
						nxtC += 1;
					}
					else if (nextBoard2.board[r][curC] == nextBoard2.board[r][nxtC] && !already[r][nxtC]) {
						already[r][nxtC] = true;
						nextBoard2.board[r][curC] = 0;
						nextBoard2.board[r][nxtC] *= 2;
						break;
					}
					else {
						break;
					}
				}
			}
		}
		q.push(nextBoard2);

		// 3. 아래로 이동
		BoardInfo nextBoard3;
		nextBoard3.idx = currentBoard.idx + 1;
		for (int j = 1; j <= widthHeight; j++) {
			for (int k = 1; k <= widthHeight; k++) {
				nextBoard3.board[j][k] = currentBoard.board[j][k];
				already[j][k] = false;
			}
		}

		for (int c = 1; c <= widthHeight; c++) {
			for (int r = widthHeight; r >= 1; r--) {
				int curR = r;
				int nxtR = r + 1;
				if (nextBoard3.board[curR][c] == 0) { continue; }
				while (nxtR <= widthHeight) {
					if (nextBoard3.board[nxtR][c] == 0) {
						nextBoard3.board[nxtR][c] = nextBoard3.board[curR][c];
						nextBoard3.board[curR][c] = 0;
						curR += 1;
						nxtR += 1;
					}
					else if (nextBoard3.board[curR][c] == nextBoard3.board[nxtR][c] && !already[nxtR][c]) {
						already[nxtR][c] = true;
						nextBoard3.board[curR][c] = 0;
						nextBoard3.board[nxtR][c] *= 2;
						break;
					}
					else {
						break;
					}
				}
			}
		}
		q.push(nextBoard3);

		// 4. 좌로 이동
		BoardInfo nextBoard4;
		nextBoard4.idx = currentBoard.idx + 1;
		for (int j = 1; j <= widthHeight; j++) {
			for (int k = 1; k <= widthHeight; k++) {
				nextBoard4.board[j][k] = currentBoard.board[j][k];
				already[j][k] = false;
			}
		}

		for (int r = 1; r <= widthHeight; r++) {
			for (int c = 1; c <= widthHeight; c++) {
				int curC = c;
				int nxtC = c - 1;
				if (nextBoard4.board[r][curC] == 0) { continue; }

				while (nxtC >= 1) {
					if (nextBoard4.board[r][nxtC] == 0) {
						nextBoard4.board[r][nxtC] = nextBoard4.board[r][curC];
						nextBoard4.board[r][curC] = 0;
						curC -= 1;
						nxtC -= 1;
					}
					else if (nextBoard4.board[r][curC] == nextBoard4.board[r][nxtC] && !already[r][nxtC]) {
						already[r][nxtC] = true;
						nextBoard4.board[r][curC] = 0;
						nextBoard4.board[r][nxtC] *= 2;
					}
					else {
						break;
					}
				}
			}
		}
		q.push(nextBoard4);
	}
}

int main() {
	cin >> widthHeight;

	BoardInfo firstBoard;
	firstBoard.idx = 0;

	for (int i = 1; i <= widthHeight; i++) {
		for (int j = 1; j <= widthHeight; j++) {
			cin >> firstBoard.board[i][j];
		}
	}

	q.push(firstBoard);

	go();

	cout << result;
}