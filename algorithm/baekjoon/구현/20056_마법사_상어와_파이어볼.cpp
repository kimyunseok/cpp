/*
* 백준 20056번 마법사 상어와 파이어볼
* https://www.acmicpc.net/problem/20056
* 구현 / 시뮬레이션
*/
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class FireBall {
public:
	int mass, speed, direction;

	FireBall(int mass, int speed, int direction) {
		this->mass = mass;
		this->speed = speed;
		this->direction = direction;
	}

};

pair<int, int> directionArr[8] = {
	{-1, 0},
	{-1, 1},
	{0, 1},
	{1, 1},
	{1, 0},
	{1,-1},
	{0, -1},
	{-1, -1},
};
int widthHeight, fireBallCnt, cmdCnt;
vector<vector<vector<FireBall>>> fireBallVec(51, vector<vector<FireBall>>(51, vector<FireBall>()));
vector<pair<pair<int, int>, FireBall>> moveVector;
int result;

void moveAllFireBall() {
	moveVector.clear();
	for (int i = 1; i <= widthHeight; i++) {
		for (int j = 1; j <= widthHeight; j++) {
			for (int k = 0; k < fireBallVec[i][j].size(); k++) {
				int dirIdx = fireBallVec[i][j][k].direction;
				int r = i + (directionArr[dirIdx].first * fireBallVec[i][j][k].speed);
				int c = j + (directionArr[dirIdx].second * fireBallVec[i][j][k].speed);

				if (r > widthHeight) {
					r %= widthHeight;
				}

				if (r < 1) {
					r = (r % widthHeight) + widthHeight;
				}

				if (c > widthHeight) {
					c %= widthHeight;
				}

				if (c < 1) {
					c = (c % widthHeight) + widthHeight;
				}

				moveVector.push_back({ {r,c}, fireBallVec[i][j][k] });
				fireBallVec[i][j].erase(fireBallVec[i][j].begin() + k);
				k--;
			}
		}
	}

	for (int i = 0; i < moveVector.size(); i++) {
		int r = moveVector[i].first.first;
		int c = moveVector[i].first.second;
		fireBallVec[r][c].push_back(moveVector[i].second);
	}
}

void divideDuplicatedFireBall() {
	for (int r = 1; r <= widthHeight; r++) {
		for (int c = 1; c <= widthHeight; c++) {
			if (fireBallVec[r][c].size() > 1) {
				int massSum = 0;
				int speedSum = 0;
				int duplicatedCnt = 0;

				bool isOdd = true;
				bool isEven = true;

				for (int i = 0; i < fireBallVec[r][c].size(); i++) {
					massSum += fireBallVec[r][c][i].mass;
					speedSum += fireBallVec[r][c][i].speed;
					duplicatedCnt++;

					if (fireBallVec[r][c][i].direction % 2 == 1) {
						isEven = false;
					}
					else {
						isOdd = false;
					}

					fireBallVec[r][c].erase(fireBallVec[r][c].begin() + i);
					i--;
				}


				if ((massSum / 5) > 0) {
					if (isOdd || isEven) {
						fireBallVec[r][c].push_back(
							FireBall(massSum / 5, speedSum / duplicatedCnt, 0)
						);
						fireBallVec[r][c].push_back(
							FireBall(massSum / 5, speedSum / duplicatedCnt, 2)
						);
						fireBallVec[r][c].push_back(
							FireBall(massSum / 5, speedSum / duplicatedCnt, 4)
						);
						fireBallVec[r][c].push_back(
							FireBall(massSum / 5, speedSum / duplicatedCnt, 6)
						);
					}
					else {
						fireBallVec[r][c].push_back(
							FireBall(massSum / 5, speedSum / duplicatedCnt, 1)
						);
						fireBallVec[r][c].push_back(
							FireBall(massSum / 5, speedSum / duplicatedCnt, 3)
						);
						fireBallVec[r][c].push_back(
							FireBall(massSum / 5, speedSum / duplicatedCnt, 5)
						);
						fireBallVec[r][c].push_back(
							FireBall(massSum / 5, speedSum / duplicatedCnt, 7)
						);
					}
				}
			}
		}
	}

}

void move(int idx) {
	if (idx > cmdCnt) { return; }

	moveAllFireBall();
	divideDuplicatedFireBall();
	move(idx + 1);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> widthHeight >> fireBallCnt >> cmdCnt;

	int r, c, mass, speed, direction;
	for (int i = 1; i <= fireBallCnt; i++) {
		cin >> r >> c >> mass >> speed >> direction;
		fireBallVec[r][c].push_back(FireBall(mass, speed, direction));
	}

	move(1);

	for (int i = 1; i <= widthHeight; i++) {
		for (int j = 1; j <= widthHeight; j++) {
			for (FireBall fireBall : fireBallVec[i][j]) {
				result += fireBall.mass;
			}
		}
	}

	cout << result;

	return 0;
}