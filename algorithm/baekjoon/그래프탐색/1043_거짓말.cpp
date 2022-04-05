/*
* 백준 1043번 거짓말
* https://www.acmicpc.net/problem/1043
* 그래프 탐색 / 분리 집합
*/
#include <iostream>
#include <vector>
using namespace std;

int peopleCnt, partyCnt;
int trueKnowPeopleCnt;
bool canLieParty[51];
bool trueAdd[51];
vector<int> trueKnowNumVec;
vector<vector<int>> partyPeopleNumVec(51, vector<int>());
vector<vector<int>> peopleJoinPartyVec(51, vector<int>());
int result;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> peopleCnt >> partyCnt;

	for (int i = 1; i <= partyCnt; i++) {
		canLieParty[i] = true;
	}

	cin >> trueKnowPeopleCnt;

	int trueKnowNum;
	while (trueKnowPeopleCnt--) {
		cin >> trueKnowNum;
		trueKnowNumVec.push_back(trueKnowNum);
		trueAdd[trueKnowNum] = true;
	}

	int partyJoinPeopleCnt, joinNum;
	for (int i = 1; i <= partyCnt; i++) {
		cin >> partyJoinPeopleCnt;
		for (int j = 1; j <= partyJoinPeopleCnt; j++) {
			cin >> joinNum;
			partyPeopleNumVec[i].push_back(joinNum);
			peopleJoinPartyVec[joinNum].push_back(i);
		}
	}

	for (int i = 0; i < trueKnowNumVec.size(); i++) {
		trueKnowNum = trueKnowNumVec[i];

		for (int j = 0; j < peopleJoinPartyVec[trueKnowNum].size(); j++) {
			int partyNum = peopleJoinPartyVec[trueKnowNum][j];

			canLieParty[partyNum] = false;

			int tmpCheck;
			for (int k = 0; k < partyPeopleNumVec[partyNum].size(); k++) {
				tmpCheck = partyPeopleNumVec[partyNum][k];

				if (!trueAdd[tmpCheck]) {
					trueKnowNumVec.push_back(tmpCheck);
					trueAdd[tmpCheck] = true;
				}

			}

		}
	}

	for (int i = 1; i <= partyCnt; i++) {
		if (canLieParty[i]) {
			result++;
		}
	}

	cout << result;

	return 0;
}