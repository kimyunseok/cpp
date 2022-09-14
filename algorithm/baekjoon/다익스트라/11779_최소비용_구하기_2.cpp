/*
* 백준 11779번 최소비용 구하기 2
* https://www.acmicpc.net/problem/11779
* - 그래프 이론 / 다익스트라
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct CurrentState {
	int curCost = 0;
	vector<int> pathCityVec;
};

int cityCnt, busCnt;
int start, destination;
bool visit[1001];
vector<vector<pair<int, int>>> adjVec(1001, vector<pair<int, int>>());
CurrentState endState;

struct comp {
	bool operator()(pair<CurrentState, int> c1, pair<CurrentState, int> c2) {
		return c1.first.curCost > c2.first.curCost;
	}
};

void go() {
	priority_queue<pair<CurrentState, int>, vector<pair<CurrentState, int>>, comp> pq;
	pq.push({ {0, {start}}, start});
	visit[start] = true;

	while (!pq.empty()) {
		CurrentState currentState = pq.top().first;
		int curNum = pq.top().second;
		pq.pop();
		visit[curNum] = true;

		//cout << curNum << "\n";
		//for (int i = 0; i < currentState.pathCityVec.size(); i++) {
		//	cout << currentState.pathCityVec[i] << ", ";
		//}
		//cout << "\n";

		if (curNum == destination) {
			endState = currentState;
			break;
		}

		for (int i = 0; i < adjVec[curNum].size(); i++) {
			int cost = adjVec[curNum][i].first;
			int nxtNum = adjVec[curNum][i].second;

			if (visit[nxtNum]) continue;

			CurrentState nxtState = currentState;
			nxtState.curCost += cost;
			nxtState.pathCityVec.push_back(nxtNum);
			pq.push({ nxtState, nxtNum });
		}
	}
}

int main() {
	cin >> cityCnt >> busCnt;

	int startCity, destCity, cost;
	for (int i = 1; i <= busCnt; i++) {
		cin >> startCity >> destCity >> cost;
		adjVec[startCity].push_back({ cost, destCity });
	}
	cin >> start >> destination;

	go();

	cout << endState.curCost << "\n";
	cout << endState.pathCityVec.size() << "\n";
	for (int i = 0; i < endState.pathCityVec.size(); i++) {
		cout << endState.pathCityVec[i] << " ";
	}

	return 0;
	
}