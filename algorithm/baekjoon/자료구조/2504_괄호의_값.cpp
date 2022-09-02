/*
* 백준 2504번 괄호의 값
* https://www.acmicpc.net/problem/2504
* 구현 / 자료구조 - 스택
*/
#include <iostream>
#include <stack>

using namespace std;

struct CalcStructure {
	int num;
	char c;
};

stack<CalcStructure> calcStack;
bool isInvalid;
int result = 0;

int main() {
	string input;
	cin >> input;

	for (int i = 0; i < input.length(); i++) {

		if (input[i] == '(') {
			calcStack.push({ -1, '(' });
		}
		else if (input[i] == ')') {
			if (calcStack.empty()) {
				isInvalid = true;
				break;
			}
			else {
				if (!calcStack.empty() && calcStack.top().num != -1) {
					int num = 0;
					while (!calcStack.empty() && calcStack.top().num != -1) {
						num += calcStack.top().num;
						calcStack.pop();
					}
					if (!calcStack.empty() && calcStack.top().c == '(') {
						num *= 2;
						calcStack.pop();
						calcStack.push({ num, '-' });
					}
					else {
						isInvalid = true;
						break;
					}
				}
				else {
					if (!calcStack.empty() && calcStack.top().c == '(') {
						calcStack.pop();
						calcStack.push({ 2, '-' });
					}
					else {
						isInvalid = true;
						break;
					}
				}
			}
		}
		else if (input[i] == '[') {
			calcStack.push({ -1, '[' });
		}
		else if (input[i] == ']') {
			if (calcStack.empty()) {
				isInvalid = true;
				break;
			}
			else {
				if (!calcStack.empty() && calcStack.top().num != -1) {
					int num = 0;
					while (!calcStack.empty() && calcStack.top().num != -1) {
						num += calcStack.top().num;
						calcStack.pop();
					}
					if (!calcStack.empty() && calcStack.top().c == '[') {
						num *= 3;
						calcStack.pop();
						calcStack.push({ num, '-' });
					}
					else {
						isInvalid = true;
						break;
					}
				}
				else {
					if (!calcStack.empty() && calcStack.top().c == '[') {
						calcStack.pop();
						calcStack.push({ 3, '-' });
					}
					else {
						isInvalid = true;
						break;
					}
				}
			}
		}
		else {
			isInvalid = true;
			break;
		}
	}

	while (!calcStack.empty()) {
		if (calcStack.top().num != -1) result += calcStack.top().num;
		else {
			isInvalid = true;
			break;
		}
		calcStack.pop();
	}

	if (isInvalid) {
		cout << 0;
	} else if (!isInvalid) {
		cout << result;
	}

	return 0;
}
