/*
* 백준 13460번 구슬 탈출 2
* https://www.acmicpc.net/problem/13460
* 구현 / 시뮬레이션 / 그래프 탐색
*/

#include <iostream>
#include <queue>

using namespace std;

struct Point {
	int r;
	int c;
};

queue<pair<Point, Point>> ballPointQ[12];
int height, width;
Point redBall, blueBall, holePoint;
Point redBallPointForCheck;
Point blueBallPointForCheck;
char maze[11][11];
bool visit[11][11][11][11];
bool redBallInHole, blueBallInHole;
int result = -1;
Point directions[4] = {
	{-1, 0},
	{0, 1},
	{1, 0},
	{0, -1}
};

void moveRedBallFirst(Point direction, int idx) {

	while (maze[redBallPointForCheck.r + direction.r][redBallPointForCheck.c + direction.c] != '#' &&
		!(redBallPointForCheck.r + direction.r == blueBallPointForCheck.r && redBallPointForCheck.c + direction.c == blueBallPointForCheck.c)
		) {
		redBallPointForCheck.r += direction.r;
		redBallPointForCheck.c += direction.c;

		if (maze[redBallPointForCheck.r][redBallPointForCheck.c] == 'O') {
			redBallPointForCheck.r = -1;
			redBallPointForCheck.c = -1;
			redBallInHole = true;
			break;
		}
	}

	while (maze[blueBallPointForCheck.r + direction.r][blueBallPointForCheck.c + direction.c] != '#' &&
		!(redBallPointForCheck.r == blueBallPointForCheck.r + direction.r && redBallPointForCheck.c == blueBallPointForCheck.c + direction.c)
		) {
		blueBallPointForCheck.r += direction.r;
		blueBallPointForCheck.c += direction.c;

		if (maze[blueBallPointForCheck.r][blueBallPointForCheck.c] == 'O') {
			blueBallInHole = true;
			break;
		}
	}

}

void moveBlueBallFirst(Point direction, int idx) {

	while (maze[blueBallPointForCheck.r + direction.r][blueBallPointForCheck.c + direction.c] != '#' &&
		!(redBallPointForCheck.r == blueBallPointForCheck.r + direction.r && redBallPointForCheck.c == blueBallPointForCheck.c + direction.c)
		) {
		blueBallPointForCheck.r += direction.r;
		blueBallPointForCheck.c += direction.c;

		if (maze[blueBallPointForCheck.r][blueBallPointForCheck.c] == 'O') {
			blueBallPointForCheck.r = -1;
			blueBallPointForCheck.c = -1;
			blueBallInHole = true;
			break;
		}
	}

	while (maze[redBallPointForCheck.r + direction.r][redBallPointForCheck.c + direction.c] != '#' &&
		!(redBallPointForCheck.r + direction.r == blueBallPointForCheck.r && redBallPointForCheck.c + direction.c == blueBallPointForCheck.c)
		) {
		redBallPointForCheck.r += direction.r;
		redBallPointForCheck.c += direction.c;

		if (maze[redBallPointForCheck.r][redBallPointForCheck.c] == 'O') {
			redBallInHole = true;
			break;
		}
	}
}

void moveBall(int idx) {

	while (!ballPointQ[idx].empty()) {
		Point redBallPoint = ballPointQ[idx].front().first;
		Point blueBallPoint = ballPointQ[idx].front().second;

		//cout << idx << "\n";
		//cout << "red : " << redBallPoint.r << ", " << redBallPoint.c << "\n";
		//cout << "blue : " << blueBallPoint.r << ", " << blueBallPoint.c << "\n\n";

		ballPointQ[idx].pop();

		for (int i = 0; i < 4; i++) {
			Point direction = directions[i];
			redBallInHole = false;
			blueBallInHole = false;

			redBallPointForCheck = redBallPoint;
			blueBallPointForCheck = blueBallPoint;

			if (i == 0) {
				if (redBallPointForCheck.r < blueBallPointForCheck.r) {
					moveRedBallFirst(direction, idx);
				}
				else {
					moveBlueBallFirst(direction, idx);
				}
			}
			else if (i == 1) {
				if (redBallPointForCheck.c > blueBallPointForCheck.c) {
					moveRedBallFirst(direction, idx);
				}
				else {
					moveBlueBallFirst(direction, idx);
				}
			}
			else if (i == 2) {
				if (redBallPointForCheck.r > blueBallPointForCheck.r) {
					moveRedBallFirst(direction, idx);
				}
				else {
					moveBlueBallFirst(direction, idx);
				}
			}
			else {
				if (redBallPointForCheck.c < blueBallPointForCheck.c) {
					moveRedBallFirst(direction, idx);
				}
				else {
					moveBlueBallFirst(direction, idx);
				}
			}

			if (redBallInHole && !blueBallInHole) {
				return;
			}
			else if (!blueBallInHole &&
				!visit[redBallPointForCheck.r][redBallPointForCheck.c][blueBallPointForCheck.r][blueBallPointForCheck.c]) {

				visit[redBallPointForCheck.r][redBallPointForCheck.c][blueBallPointForCheck.r][blueBallPointForCheck.c] = true;
				ballPointQ[idx + 1].push({ redBallPointForCheck, blueBallPointForCheck });
			}
		}

	}

}

void go(int idx) {
	if (idx > 10) { return; }

	moveBall(idx);

	if (redBallInHole && !blueBallInHole) {
		result = idx;
		return;
	}
	else {
		go(idx + 1);
	}
}

int main() {
	cin >> height >> width;

	for (int r = 1; r <= height; r++) {
		for (int c = 1; c <= width; c++) {
			cin >> maze[r][c];
			if (maze[r][c] == 'R') {
				redBall.r = r;
				redBall.c = c;
			}
			else if (maze[r][c] == 'B') {
				blueBall.r = r;
				blueBall.c = c;
			}
			else if (maze[r][c] == 'O') {
				holePoint.r = r;
				holePoint.c = c;
			}
		}
	}

	visit[redBall.r][redBall.c][blueBall.r][blueBall.c] = true;
	ballPointQ[1].push({ redBall, blueBall });

	go(1);

	cout << result;

	return 0;
}