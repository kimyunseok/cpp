/*
* 백준 17298번 오큰수
* https://www.acmicpc.net/problem/17298
* 자료 구조, 스택
*/
#include <iostream>
#include <stack>
using namespace std;

int numCnt, input;
stack<int> inputStack;
stack<int> numSaveStack;
stack<int> resultStack;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> numCnt;

	while (numCnt--) {
		cin >> input;
		inputStack.push(input);
	}

	while (!inputStack.empty()) {
		int findResult = -1;
		int inputTop = inputStack.top();
		inputStack.pop();

		while (!numSaveStack.empty()) {
			int numSaveTop = numSaveStack.top();
			if (numSaveTop > inputTop) {
				findResult = numSaveTop;
				numSaveStack.push(inputTop);
				break;
			}
			else {
				numSaveStack.pop();
			}
		}
		if (findResult == -1) {
			numSaveStack.push(inputTop);
		}
		resultStack.push(findResult);
	}

	while (!resultStack.empty()) {
		int resultTop = resultStack.top();
		resultStack.pop();
		cout << resultTop << " ";
	}

	return 0;
}