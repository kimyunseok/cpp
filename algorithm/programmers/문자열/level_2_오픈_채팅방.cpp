/*
* 프로그래머스 2019 KAKAO BLIND RECRUITMENT
* Level 2 오픈채팅방
* 문자열, 맵
*/
#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

vector<string> solution(vector<string> record) {
	vector<string> answer;
	map<string, string> idNameMap;
	queue<pair<string, string>> q;

	for (int i = 0; i < record.size(); i++) {

		int idx = 0;
		while (record[i][idx] != ' ') {
			idx++;
		}
		idx++; // 공백 넘김.

		if (record[i][0] == 'E') {
			string id = "";
			while (record[i][idx] != ' ') {
				id += record[i][idx];
				idx++;
			}
			idx++; // 공백 넘김.

			string nickName = "";
			while (idx < record[i].length() && record[i][idx] != ' ') {
				nickName += record[i][idx];
				idx++;
			}

			//idNameMap.insert({ id, nickName });
			//idNameMap.at(id) = nickName;
			if (idNameMap.find(id) == idNameMap.end()) {
				idNameMap.insert({ id, nickName });
			}
			else {
				idNameMap.at(id) = nickName;
			}
			q.push({ id, "님이 들어왔습니다." });
		}
		else if (record[i][0] == 'L') {
			string id = "";
			while (idx < record[i].length() && record[i][idx] != ' ') {
				id += record[i][idx];
				idx++;
			}
			idx++; // 공백 넘김.

			q.push({ id, "님이 나갔습니다." });
		}
		else if (record[i][0] == 'C') {

			string id = "";
			while (record[i][idx] != ' ') {
				id += record[i][idx];
				idx++;
			}
			idx++; // 공백 넘김.

			string nickName = "";
			while (idx < record[i].length() && record[i][idx] != ' ') {
				nickName += record[i][idx];
				idx++;
			}

			idNameMap.at(id) = nickName;
		}
	}

	while (!q.empty()) {
		string id = q.front().first;
		string nickName = idNameMap.at(id);
		string cmd = q.front().second;
		q.pop();
		answer.push_back(nickName + cmd);
	}

	return answer;
}

int main() {
	cout.tie(NULL);
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	vector<string> ans = solution({ "Enter uid1234 Muzi", "Enter uid4567 Prodo","Leave uid1234","Enter uid1234 Prodo","Change uid4567 Ryan" });

	for (string data : ans) {
		cout << data << "\n";
	}

	return 0;
}