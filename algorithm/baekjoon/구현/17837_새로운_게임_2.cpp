/*
* 백준 17837번 새로운 게임 2
* https://www.acmicpc.net/problem/17837
* - 구현 / 시뮬레이션
*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Horse {
	int r = 0;
	int c = 0;
	int direction = 0;
	int idxInCurrentBoard = 0;
	int number = 0;
};

struct ChessBoard {
	int color = 0;
	int horseCntInCurrent;
};

int widthHeight, horseCnt;
bool horseOverFour;
int result = -1;
ChessBoard chessBoard[13][13];
vector<Horse> horseVec;
pair<int, int> directions[5] = {
	{-1, -1},
	{0, 1},
	{0, -1},
	{-1, 0},
	{1, 0}
};
int reverseDirections[5] = {-1, 2, 1, 4, 3};

struct compForWhite {
	bool operator()(Horse h1, Horse h2) {
		return h1.idxInCurrentBoard > h2.idxInCurrentBoard;
	}
};

struct compForRed {
	bool operator()(Horse h1, Horse h2) {
		return h1.idxInCurrentBoard < h2.idxInCurrentBoard;
	}
};

void moveForWhite(int idx) {
	priority_queue<Horse, vector<Horse>, compForWhite> pq;
	int curR = horseVec[idx].r;
	int curC = horseVec[idx].c;
	int curIdx = horseVec[idx].idxInCurrentBoard;

	int nxtR = horseVec[idx].r + directions[horseVec[idx].direction].first;
	int nxtC = horseVec[idx].c + directions[horseVec[idx].direction].second;

	for (int i = 0; i < horseVec.size(); i++) {
		if (horseVec[i].r == curR && horseVec[i].c == curC && horseVec[i].idxInCurrentBoard >= curIdx) {
			pq.push(horseVec[i]);
		}
	}

	while (!pq.empty()) {
		Horse curHorse = pq.top();
		pq.pop();

		horseVec[curHorse.number - 1].r = nxtR;
		horseVec[curHorse.number - 1].c = nxtC;
		horseVec[curHorse.number - 1].idxInCurrentBoard = ++chessBoard[nxtR][nxtC].horseCntInCurrent;
		chessBoard[curR][curC].horseCntInCurrent--;
	}

	if (chessBoard[nxtR][nxtC].horseCntInCurrent >= 4) {
		horseOverFour = true;
	}
}

void moveForRed(int idx) {
	priority_queue<Horse, vector<Horse>, compForRed> pq;
	int curR = horseVec[idx].r;
	int curC = horseVec[idx].c;
	int curIdx = horseVec[idx].idxInCurrentBoard;

	int nxtR = horseVec[idx].r + directions[horseVec[idx].direction].first;
	int nxtC = horseVec[idx].c + directions[horseVec[idx].direction].second;

	for (int i = 0; i < horseVec.size(); i++) {
		if (horseVec[i].r == curR && horseVec[i].c == curC && horseVec[i].idxInCurrentBoard >= curIdx) {
			pq.push(horseVec[i]);
		}
	}

	while (!pq.empty()) {
		Horse curHorse = pq.top();
		pq.pop();

		//cout << curHorse.number << " , ";

		horseVec[curHorse.number - 1].r = nxtR;
		horseVec[curHorse.number - 1].c = nxtC;
		horseVec[curHorse.number - 1].idxInCurrentBoard = ++chessBoard[nxtR][nxtC].horseCntInCurrent;
		chessBoard[curR][curC].horseCntInCurrent--;
	}

	if (chessBoard[nxtR][nxtC].horseCntInCurrent >= 4) {
		horseOverFour = true;
	}
}

void go(int idx) {
	if (idx > 1000) return;

	//cout << idx << "\n";
	//for (int i = 1; i <= widthHeight; i++) {
	//	for (int j = 1; j <= widthHeight; j++) {
	//		cout << chessBoard[i][j].horseCntInCurrent << " ";
	//	}
	//	cout << "\n";
	//}

	// 말 이동
	for (int i = 0; i < horseVec.size(); i++) {
		int nxtR = horseVec[i].r + directions[horseVec[i].direction].first;
		int nxtC = horseVec[i].c + directions[horseVec[i].direction].second;
		//cout << i + 1 << "번 말 이동 : " << nxtR << " , " << nxtC << "\n";

		if (nxtR < 1 || nxtR > widthHeight || nxtC < 1 || nxtC > widthHeight || chessBoard[nxtR][nxtC].color == 2) {
			horseVec[i].direction = reverseDirections[horseVec[i].direction];
			nxtR = horseVec[i].r + directions[horseVec[i].direction].first;
			nxtC = horseVec[i].c + directions[horseVec[i].direction].second;

			if (nxtR < 1 || nxtR > widthHeight || nxtC < 1 || nxtC > widthHeight || chessBoard[nxtR][nxtC].color == 2) continue;
			else if (chessBoard[nxtR][nxtC].color == 0) {
				moveForWhite(i);
			}
			else if (chessBoard[nxtR][nxtC].color == 1) {
				moveForRed(i);
			}

		}
		else if (chessBoard[nxtR][nxtC].color == 0) {
			moveForWhite(i);
		}
		else if (chessBoard[nxtR][nxtC].color == 1) {
			moveForRed(i);
		}
	}

	if (horseOverFour) {
		result = idx;
		return;
	}
	else {
		go(idx + 1);
	}
}

int main() {
	cin >> widthHeight >> horseCnt;

	for (int i = 1; i <= widthHeight; i++) {
		for (int j = 1; j <= widthHeight; j++) {
			cin >> chessBoard[i][j].color;
		}
	}

	int r, c, dir;
	for (int i = 1; i <= horseCnt; i++) {
		cin >> r >> c >> dir;
		chessBoard[r][c].horseCntInCurrent++;
		horseVec.push_back({ r, c, dir, 1, i });
	}

	go(1);

	cout << result;

	return 0;
}