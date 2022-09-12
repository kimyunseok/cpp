/*
* 백준 19238번 스타트 택시
* https://www.acmicpc.net/problem/19238
* - 구현 / 시뮬레이션 / 그래프 탐색 : BFS
*/
#include <iostream>
#include <queue>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

struct Customer {
	int startR, startC;
	int destR, destC;
};

struct Taxi {
	int curR, curC;
	int curFuel;
};

Taxi taxi = { 0, 0, 0 };

vector<Customer> customerVec;
int widthHeight, customerCnt;
int map[21][21];
bool cantGo;

pair<int, int> directions[4] = {
	{1, 0},
	{-1, 0},
	{0, 1},
	{0, -1}
};


int getDistanceToDestination(int destR, int destC) {
	bool visit[21][21];

	for (int i = 1; i <= widthHeight; i++) {
		for (int j = 1; j <= widthHeight; j++) {
			visit[i][j] = false;
		}
	}

	visit[taxi.curR][taxi.curC] = true;
	queue<pair<pair<int, int>, int>> q;
	q.push({ {taxi.curR, taxi.curC}, 0 });

	while (!q.empty()) {
		int curR = q.front().first.first;
		int curC = q.front().first.second;
		int curDist = q.front().second;
		q.pop();

		if (curR == destR && curC == destC) {
			return curDist;
		}

		for (pair<int, int> direction : directions) {
			int nxtR = curR + direction.first;
			int nxtC = curC + direction.second;
			int nxtDist = curDist + 1;

			if (nxtR < 1 || nxtR > widthHeight || nxtC < 1 || nxtC > widthHeight
				|| visit[nxtR][nxtC] || map[nxtR][nxtC] == 1) continue;

			visit[nxtR][nxtC] = true;

			q.push({ {nxtR, nxtC}, nxtDist });
		}
	}

	return -1;
}
void go() {
	for (int i = 0; i < customerCnt; i++) {
		Customer selectCustomer = customerVec[i];

		for (int j = i + 1; j < customerCnt; j++) {
			Customer checkCustomer = customerVec[j];
			int c1DistanceFromTaxi = getDistanceToDestination(selectCustomer.startR, selectCustomer.startC);
			int c2DistanceFromTaxi = getDistanceToDestination(checkCustomer.startR, checkCustomer.startC);

			if (c1DistanceFromTaxi == -1) {
				customerVec[i] = checkCustomer;
				customerVec[j] = selectCustomer;
				selectCustomer = checkCustomer;
			}
			else if (c1DistanceFromTaxi != -1 && c1DistanceFromTaxi > c2DistanceFromTaxi) {
				customerVec[i] = checkCustomer;
				customerVec[j] = selectCustomer;
				selectCustomer = checkCustomer;
			}
			else if (c1DistanceFromTaxi == c2DistanceFromTaxi) {
				if (selectCustomer.startR > checkCustomer.startR) {
					customerVec[i] = checkCustomer;
					customerVec[j] = selectCustomer;
					selectCustomer = checkCustomer;
				}
				else if (selectCustomer.startR == checkCustomer.startR) {
					if (selectCustomer.startC > checkCustomer.startC) {
						customerVec[i] = checkCustomer;
						customerVec[j] = selectCustomer;
						selectCustomer = checkCustomer;
					}
				}
			}
		}

		int needFuelToCustomer = getDistanceToDestination(selectCustomer.startR, selectCustomer.startC);

		//cout << "needCustomer : " << customer.startR << " , " << customer.startC << "\n";

		if (taxi.curFuel < needFuelToCustomer || needFuelToCustomer == -1) {
			cantGo = true;
			return;
		}

		taxi.curFuel -= needFuelToCustomer;
		taxi.curR = selectCustomer.startR;
		taxi.curC = selectCustomer.startC;

		int needFuelToDestination = getDistanceToDestination(selectCustomer.destR, selectCustomer.destC);

		if (taxi.curFuel < needFuelToDestination || needFuelToDestination == -1) {
			cantGo = true;
			return;
		}

		taxi.curFuel -= needFuelToDestination;
		taxi.curR = selectCustomer.destR;
		taxi.curC = selectCustomer.destC;

		taxi.curFuel += (2 * needFuelToDestination);

		taxi.curR = selectCustomer.destR;
		taxi.curC = selectCustomer.destC;
	}
}

int main() {
	cin >> widthHeight >> customerCnt >> taxi.curFuel;

	for (int r = 1; r <= widthHeight; r++) {
		for (int c = 1; c <= widthHeight; c++) {
			cin >> map[r][c];
		}
	}

	cin >> taxi.curR >> taxi.curC;

	for (int i = 1; i <= customerCnt; i++) {
		Customer customer = { 0, 0, 0, 0 };
		cin >> customer.startR >> customer.startC >> customer.destR >> customer.destC;

		customerVec.push_back(customer);
	}

	go();

	if (cantGo) {
		cout << -1;
	}
	else {
		cout << taxi.curFuel;
	}

	return 0;
}