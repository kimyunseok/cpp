/*
* 백준 1005번 ACM Craft
* https://www.acmicpc.net/problem/1005
* 다이나믹 프로그래밍 / 그래프 탐색
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int tCnt, buildingCnt, ruleCnt, goalNum;
int buildTime[1001];
int totalBuildTime[1001];
vector<int> prevBuildingNumVec[1001];

int check(int num) {

    int prevTime = 0;

    for (int num : prevBuildingNumVec[num]) {
        if (totalBuildTime[num] != -1) {
            prevTime = max(prevTime, totalBuildTime[num]);
        }
        else {
            prevTime = max(prevTime, check(num));
        }
    }

    totalBuildTime[num] = buildTime[num] + prevTime;

    return totalBuildTime[num];
}

int main() {
    cin >> tCnt;

    while (tCnt--) {
        cin >> buildingCnt >> ruleCnt;

        for (int i = 1; i <= buildingCnt; i++) {
            cin >> buildTime[i];
            totalBuildTime[i] = -1;
            prevBuildingNumVec[i].clear();
        }

        int prevNum, nxtNum;
        for (int i = 1; i <= ruleCnt; i++) {
            cin >> prevNum >> nxtNum;

            prevBuildingNumVec[nxtNum].push_back(prevNum);
        }

        cin >> goalNum;

        cout << check(goalNum) << "\n";
    }

    return 0;
}
