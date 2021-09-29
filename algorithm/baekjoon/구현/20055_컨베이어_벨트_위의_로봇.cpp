/*
* 백준 20055번 컨베이어 벨트 위의 로봇
* https://www.acmicpc.net/problem/20055
* 구현 / 시뮬레이션
*/
#include <iostream>
using namespace std;

int beltLength, maxZeroCnt;
int remainDurability[3][101]; // 1 : 위(->), 2 : 아래(<-)
bool isOnRobot[101]; // 로봇이 반대편에서는 이동하지 않음.
int zeroCnt, ans;

void spinBelt() {
	int prevDurability = remainDurability[1][1];
	int prevRobotCheck = isOnRobot[1];
	for (int i = 2; i <= beltLength; i++) {
		int tmp = remainDurability[1][i];
		int tmpRobot = isOnRobot[i];

		remainDurability[1][i] = prevDurability;
		isOnRobot[i] = prevRobotCheck;

		prevDurability = tmp;
		prevRobotCheck = tmpRobot;

		if (i == beltLength && isOnRobot[i]) {
			//N번째에서는 로봇 내림(사라짐.)
			isOnRobot[i] = false;
		}
	}

	//2번째라인은 로봇은 필요없다.
	for (int i = beltLength; i >= 1; i--) {
		int tmp = remainDurability[2][i];
		remainDurability[2][i] = prevDurability;
		prevDurability = tmp;
	}

	remainDurability[1][1] = prevDurability;
	isOnRobot[1] = false;
}

void moveRobot() {
	for (int i = beltLength - 1; i >= 1; i--) {
		int nxtIdx = i + 1;
		if (isOnRobot[i] && remainDurability[1][nxtIdx] > 0 && !isOnRobot[nxtIdx]) {
			isOnRobot[i] = false;
			remainDurability[1][nxtIdx]--;
			isOnRobot[nxtIdx] = true;

			if (nxtIdx == beltLength && isOnRobot[nxtIdx]) {
				isOnRobot[nxtIdx] = false;
			}
		}
	}
}

void go(int idx) {
	//1. 회전
	spinBelt();

	//2. 벨트 회전 방향으로 로봇이동
	moveRobot();

	//3. 로봇 올리기
	if (remainDurability[1][1] > 0) {
		remainDurability[1][1]--;
		isOnRobot[1] = true;
	}

	//4. 내구도 0칸 K개 이상 체크
	zeroCnt = 0;
	for (int i = 1; i <= beltLength; i++) {
		if (remainDurability[1][i] == 0) { zeroCnt++; }
		if (remainDurability[2][i] == 0) { zeroCnt++; }
	}

	if (zeroCnt >= maxZeroCnt) { ans = idx; return; }
	else { go(idx + 1); }
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> beltLength >> maxZeroCnt;

	for (int i = 1; i <= beltLength; i++) {
		cin >> remainDurability[1][i];
	}

	for (int i = beltLength; i >= 1; i--) {
		cin >> remainDurability[2][i];
	}

	go(1);

	cout << ans;

	return 0;
}