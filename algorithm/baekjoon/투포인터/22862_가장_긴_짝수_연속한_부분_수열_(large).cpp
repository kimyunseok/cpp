/*
* 백준 22862번 가장 긴 짝수 연속한 부분 수열 (large)
* https://www.acmicpc.net/problem/22862
* - 투 포인터
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int result = 0;

	int numCnt, maxDeleteCnt;
	cin >> numCnt >> maxDeleteCnt;

	vector<int> numVec;
	int input;
	for (int i = 1; i <= numCnt; i++) {
		cin >> input;
		numVec.push_back(input);
	}

	int currentDeleteCnt = 0;
	int currentLen = 0;
	int l = 0;
	int r = 0;

	while (r < numCnt) {
		//cout << " L : " << l << " , R : " << r << "\n";
		if (numVec[r] % 2 == 0) {
			currentLen++;
			r++;
			result = max(result, currentLen - currentDeleteCnt);
		}
		else {
			if (currentDeleteCnt + 1 <= maxDeleteCnt) {
				currentDeleteCnt++;
				currentLen++;
				result = max(result, currentLen - currentDeleteCnt);
				r++;
			}
			else {
				if (r > l) {
					if (numVec[l] % 2 == 1) currentDeleteCnt--;
					l++;
					currentLen--;
				}
				else {
					l++;
					r++;
				}
			}
		}
	}

	cout << result;

	return 0;
}