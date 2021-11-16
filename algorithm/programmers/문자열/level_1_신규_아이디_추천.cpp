/*
* 프로그래머스 2021 KAKAO BLIND RECRUITMENT
* Level 1 신규 아이디 추천
* https://programmers.co.kr/learn/courses/30/lessons/72410
* 문자열
*/
#include <iostream>

using namespace std;
/*
* 아이디의 길이 : 3 ~ 15
* 소문자, 숫자, -, _, . 사용 가능.
* 마침표(.)는 처음과 끝에 사용 불가
* 마침표는 연속 사용 불가
*
* 단계를 통해서 규칙에 맞는 새로운 아이디 추천
* 1. 모든 대문자를 소문자로 치환.
* 2. 소문자, 숫자, -, _, .을 제외한 모든 문자 제거
* 3. 마침표가 2번 이상 연속된 부분 하나의 마침표로 변경
* 4. 마침표가 처음이나 끝에 있다면 제거
* 5. 빈 문자열일 경우 "a" 대입
* 6. 길이가 16자 이상일 경우, 처음 15개 제외 나머지를 모두 제거한다.
* 제거 후 마지막에 마침표 존재 시 제거
* 7. 길이가 2자 이하라면, new_id의 마지막 문자를 길이가 3이 될 때까지 반복해서 끝에 붙임.
*/

string solution(string new_id) {
	int diff = 'a' - 'A';
	string answer = new_id;
	//1단계. 모든 대문자 소문자로 치환.
	for (int i = 0; i < answer.length(); i++) {
		if (answer[i] >= 'A' && answer[i] <= 'Z') {
			answer[i] += diff;
		}
	}

	//2단계. 소문자, 숫자, -, _, .을 제외한 모든 문자 제거
	for (int i = 0; i < answer.length(); i++) {
		if (!(answer[i] >= 'a' && answer[i] <= 'z') &&
			!(answer[i] >= '0' && answer[i] <= '9') &&
			answer[i] != '-' && answer[i] != '_' && answer[i] != '.') {
			answer.erase(answer.begin() + i);
			i--;
		}
	}

	int prevPointIdx = -2;
	//3단계 마침표 두 번 이상 연속된 곳 제거.
	for (int i = 0; i < answer.length(); i++) {
		if (answer[i] == '.') {
			if (i - 1 == prevPointIdx) {
				answer.erase(answer.begin() + i);
				i--;
			}
			else {
				prevPointIdx = i;
			}
		}
	}

	//4단계 마침표가 처음이나 끝에 있다면 제거
	while (answer.length() > 0 && answer[0] == '.') {
		answer.erase(answer.begin());
	}
	while (answer.length() > 0 && answer[answer.length() - 1] == '.') {
		answer.erase(answer.begin() + (answer.length() - 1));
	}

	//5단계 빈 문자열일 경우 "a" 대입
	if (answer.length() == 0) {
		answer = "a";
	}

	//6단계 길이가 16자 이상일 경우, 처음 15개 제외 나머지를 모두 제거한다. 제거 후 마지막에 마침표 존재 시 제거
	while (answer.length() > 15) {
		answer.erase(answer.begin() + (answer.length() - 1));
	}
	while (answer.length() > 0 && answer[answer.length() - 1] == '.') {
		answer.erase(answer.begin() + (answer.length() - 1));
	}

	//7단계 길이가 2자 이하라면, new_id의 마지막 문자를 길이가 3이 될 때까지 반복해서 끝에 붙임.
	while (answer.length() <= 2) {
		answer += answer[answer.length() - 1];
	}

	return answer;
}

int main() {
	cout.tie(NULL);
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cout << solution("abcdefghijklmn.p");

	return 0;
}