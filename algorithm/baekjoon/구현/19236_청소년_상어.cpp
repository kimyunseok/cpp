/*
* 백준 19236번 청소년 상어
* https://www.acmicpc.net/problem/19236
* - 구현 / 시뮬레이션
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Fish {
	bool isAlive = true;
	int x = 0;
	int y = 0;
	int direction = 0;
	int number = 0;
};

struct Shark {
	int x = 1;
	int y = 1;
	int direction = 0;
};

struct CurrentState {
	int score = 0;
	Shark shark;
	Fish fishArr[17][17];
	pair<int, int> fishPosition[17];
};

// 1부터 반시계방향
pair<int, int> directions[9] = {
	{0, 0},
	{-1, 0},
	{-1, -1},
	{0, -1},
	{1, -1},
	{1, 0},
	{1, 1},
	{0, 1},
	{-1, 1}
};

int result = 0;
queue<CurrentState> stateQueue;

void go() {
	while (!stateQueue.empty()) {
		CurrentState currentState = stateQueue.front();
		stateQueue.pop();

		result = max(result, currentState.score);

		//cout << currentState.shark.x << " , " << currentState.shark.y << "-" << currentState.score << "\n\n";

		//for (int x = 1; x <= 4; x++) {
		//	for (int y = 1; y <= 4; y++) {
		//		cout << "{" << currentState.fishArr[x][y].number << " , " << currentState.fishArr[x][y].direction << " , ";
		//		cout << currentState.fishArr[x][y].isAlive << "} ";
		//	}
		//	cout << "\n";
		//}
		//cout << "\n";

		//1. 물고기 이동
		for (int i = 1; i <= 16; i++) {
			int x = currentState.fishPosition[i].first;
			int y = currentState.fishPosition[i].second;

			//cout << i << " = " << x << " , " << y << "\n";
			//cout << "direction = " << currentState.fishArr[x][y].direction << "\n";

			if (!currentState.fishArr[x][y].isAlive) continue;

			int moveIdx = 9;
			while (moveIdx--) {
				int nxtX = x + directions[currentState.fishArr[x][y].direction].first;
				int nxtY = y + directions[currentState.fishArr[x][y].direction].second;

				if (nxtX < 1 || nxtX > 4 || nxtY < 1 || nxtY > 4 ||
					(nxtX == currentState.shark.x && nxtY == currentState.shark.y)) {
					currentState.fishArr[x][y].direction++;
					if (currentState.fishArr[x][y].direction > 8) currentState.fishArr[x][y].direction = 1;
					continue;
				}


				Fish tmpFish = currentState.fishArr[nxtX][nxtY];
				currentState.fishPosition[currentState.fishArr[x][y].number] = { nxtX, nxtY };
				currentState.fishPosition[currentState.fishArr[nxtX][nxtY].number] = { x, y };
				currentState.fishArr[nxtX][nxtY] = currentState.fishArr[x][y];
				currentState.fishArr[x][y] = tmpFish;

				break;
				
			}
		}


		// 2. 상어 이동
		int sharkNxtX = currentState.shark.x + directions[currentState.shark.direction].first;
		int sharkNxtY = currentState.shark.y + directions[currentState.shark.direction].second;

		while (sharkNxtX > 0 && sharkNxtX < 5 && sharkNxtY > 0 && sharkNxtY < 5) {
			if (currentState.fishArr[sharkNxtX][sharkNxtY].isAlive) {
				CurrentState nxtState = currentState;
				nxtState.fishArr[sharkNxtX][sharkNxtY].isAlive = false;
				nxtState.score += currentState.fishArr[sharkNxtX][sharkNxtY].number;
				nxtState.shark.direction = nxtState.fishArr[sharkNxtX][sharkNxtY].direction;
				nxtState.shark.x = sharkNxtX;
				nxtState.shark.y = sharkNxtY;

				stateQueue.push(nxtState);
			}
			sharkNxtX = sharkNxtX + directions[currentState.shark.direction].first;
			sharkNxtY = sharkNxtY + directions[currentState.shark.direction].second;
		}
	}
}

int main() {

	CurrentState firstState;
	
	int number, direction;
	for (int x = 1; x <= 4; x++) {
		for (int y = 1; y <= 4; y++) {
			cin >> number >> direction;
			firstState.fishArr[x][y].number = number;
			firstState.fishArr[x][y].direction = direction;
			firstState.fishPosition[number] = { x, y };
		}
	}

	firstState.fishArr[1][1].isAlive = false;
	firstState.score += firstState.fishArr[1][1].number;
	result += firstState.score;
	firstState.shark.direction = firstState.fishArr[1][1].direction;

	stateQueue.push(firstState);

	go();

	cout << result;

	return 0;
	
}