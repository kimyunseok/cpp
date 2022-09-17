/*
* 백준 9466번 텀 프로젝트
* https://www.acmicpc.net/problem/9466
* - 그래프 탐색
*/
#include <iostream>
#include <vector>

using namespace std;

int studentChoice[100001];
int studentLast[100001];
bool visit[100001];
bool visitForResult[100001];
int result;

int go(int curNum) {
	int nxtNum = studentChoice[curNum];

	if (visit[curNum]) return curNum;

	visit[curNum] = true;

	if (studentLast[nxtNum] == -1) {
		return studentLast[curNum] = go(nxtNum);
	}
	else {
		return studentLast[curNum] = studentLast[nxtNum];
	}
}

int checkCycleCnt(int curNum, int curCnt) {
	int nxtNum = studentChoice[curNum];

	if (curNum == nxtNum) return 1;

	visitForResult[curNum] = true;

	if (!visitForResult[nxtNum]) {
		return checkCycleCnt(nxtNum, curCnt + 1);
	}
	else {
		return curCnt;
	}
}

int main() {
	int tCnt;
	cin >> tCnt;

	while (tCnt--) {
		int studentCnt;
		cin >> studentCnt;

		result = studentCnt;

		for (int i = 1; i <= studentCnt; i++) {
			cin >> studentChoice[i];
			studentLast[i] = -1;
			visit[i] = false;
			visitForResult[i] = false;
		}

		for (int i = 1; i <= studentCnt; i++) {
			if (studentLast[i] == -1) {
				go(i);
			}
		}

		for (int i = 1; i <= studentCnt; i++) {
			int num = studentLast[i];
			if (!visitForResult[num]) {
				visitForResult[num] = true;
				result -= checkCycleCnt(num, 1);
			}
		}

		cout << result << "\n";
	}
	return 0;

}