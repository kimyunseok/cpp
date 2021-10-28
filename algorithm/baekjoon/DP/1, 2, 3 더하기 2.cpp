/*
* 백준 12101번 1, 2, 3 더하기 2
* https://www.acmicpc.net/problem/12101
* 다이나믹 프로그래밍
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int num, idx;
vector<string> vec[11];
string ans;

int main() {
	cout.tie(NULL);
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> num >> idx;

	vec[1].push_back("1");
	vec[2].push_back("1+1");
	vec[2].push_back("2");
	vec[3].push_back("1+1+1");
	vec[3].push_back("1+2");
	vec[3].push_back("2+1");
	vec[3].push_back("3");

	for (int i = 4; i <= num; i++) {
		for (int j = i - 3; j < i; j++) {
			char addNum = '0' + (i - j);
			for (int k = 0; k < vec[j].size(); k++) {
				string input = vec[j][k] + "+" + addNum;
				vec[i].push_back(input);
			}
		}
	}

	sort(vec[num].begin(), vec[num].end());

	if (idx - 1 >= vec[num].size()) {
		cout << "-1";
	}
	else {
		cout << vec[num][idx - 1];
	}


	return 0;
}