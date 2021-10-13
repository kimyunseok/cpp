/*
* 백준 5639번 이진 검색 트리
* https://www.acmicpc.net/problem/5639
* 그래프 탐색 / 트리 / 재귀
*/
#include <iostream>
using namespace std;

int rootNodeNum;
pair<int, int> adjNode[1000001]; // first 왼, second 우
int input;

void go(int curNodeNum) {
	if (adjNode[curNodeNum].first != 0) {
		go(adjNode[curNodeNum].first);
	}

	if (adjNode[curNodeNum].second != 0) {
		go(adjNode[curNodeNum].second);
	}

	cout << curNodeNum << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	while (true) {
		cin >> input;
		if (cin.eof()) { break; } // cin의 End Of File 처리

		if (rootNodeNum == 0) {
			rootNodeNum = input;
			continue;
		}

		int curNodeNum = rootNodeNum;
		while (true) {
			if (curNodeNum < input) {
				if (adjNode[curNodeNum].second == 0) {
					adjNode[curNodeNum].second = input;
					break;
				}
				else {
					curNodeNum = adjNode[curNodeNum].second;
				}
			}
			else {
				if (adjNode[curNodeNum].first == 0) {
					adjNode[curNodeNum].first = input;
					break;
				}
				else {
					curNodeNum = adjNode[curNodeNum].first;
				}
			}
		}
	}

	go(rootNodeNum);

	return 0;
}
