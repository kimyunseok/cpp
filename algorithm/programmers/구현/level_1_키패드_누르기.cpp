/*
* 프로그래머스 2020 KAKAO BLIND RECRUITMENT
* Level 1 키패드 누르기
* https://programmers.co.kr/learn/courses/30/lessons/67256
* 구현
*/
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

int curLeft = 10;
int curRight = 11;

pair<int, int> point[12] = {
	{4, 2},
	{1, 1},
	{1, 2},
	{1, 3},
	{2, 1},
	{2, 2},
	{2, 3},
	{3, 1},
	{3, 2},
	{3, 3},
	{4, 1}, // 10 : *
	{4, 3} // 11 : #
};

int pointDistance(int num1, int num2) {
	int rDiff = abs(point[num1].first - point[num2].first);
	int cDiff = abs(point[num1].second - point[num2].second);
	return rDiff + cDiff;
}

string solution(vector<int> numbers, string hand) {
	string answer = "";
	for (int i = 0; i < numbers.size(); i++) {
		int curNum = numbers[i];
		if (curNum == 1 || curNum == 4 || curNum == 7) {
			answer += 'L';
			curLeft = curNum;
		}
		else if (curNum == 3 || curNum == 6 || curNum == 9) {
			answer += 'R';
			curRight = curNum;
		}
		else {
			int leftDistance = pointDistance(curLeft, curNum);
			int rightDistance = pointDistance(curRight, curNum);
			if (leftDistance < rightDistance) {
				answer += 'L';
				curLeft = curNum;
			}
			else if (leftDistance > rightDistance) {
				answer += 'R';
				curRight = curNum;
			}
			else {
				if (hand == "right") {
					answer += 'R';
					curRight = curNum;
				}
				else {
					answer += 'L';
					curLeft = curNum;
				}
			}
		}
	}
	return answer;
}

int main() {
	cout.tie(NULL);
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cout << solution({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 }, "left");

	return 0;
}