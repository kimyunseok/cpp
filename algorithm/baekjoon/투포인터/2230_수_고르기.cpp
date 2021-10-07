/*
* 백준 2230번 수 고르기
* https://www.acmicpc.net/problem/2230
* 투 포인터
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int numCnt, minDiff;
vector<int> numVec;
int ans = 2100000000; // 틀린이유 3 : 최대 차이가 20억임.

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> numCnt >> minDiff;

	int input;
	for (int i = 1; i <= numCnt; i++) {
		cin >> input;
		numVec.push_back(input);
	}

	sort(numVec.begin(), numVec.end());

	int front = 0;
	int tail = 1;

	while (front <= tail && tail < numCnt) { // 틀린이유 1 : front < tail로 하면 틀림 ex.) 2 0 1 2
		int frontNum = numVec[front];
		int tailNum = numVec[tail];
		int diff = tailNum - frontNum;

		if (diff == minDiff) {
			ans = diff;
			break;
		}
		else if (diff < minDiff) {
			tail++;
		}
		else if (diff > minDiff) {
			ans = min(ans, diff); // 틀린 이유 2 : ans를 항상 더 작은 값으로 갱신해 줘야한다.
			front++;
		}
	}

	cout << ans;

	return 0;
}
