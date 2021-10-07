/*
* 백준 1806번 부분합
* https://www.acmicpc.net/problem/1806
* 투 포인터
*/
#include <iostream>
#include <vector>
using namespace std;

int numCnt, minSum;
vector<int> numVec;
int ans = 2000000000;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> numCnt >> minSum;

	int input;
	for (int i = 1; i <= numCnt; i++) {
		cin >> input;
		numVec.push_back(input);
	}

	int front = 0;
	int tail = 0;
	int curSum = numVec[0];
	while (front <= tail && tail < numCnt) {
		if (curSum >= minSum) {
			ans = min(ans, tail - front + 1);
			curSum -= numVec[front++];
		}
		else {
			tail++;
			if (tail < numCnt) {
				curSum += numVec[tail];
			}
		}
	}

	if (ans == 2000000000) {
		cout << "0";
	}
	else {
		cout << ans;
	}

	return 0;
}
