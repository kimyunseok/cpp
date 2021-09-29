/*
* 백준 2579번 계단 오르기
* https://www.acmicpc.net/problem/2579
* 다이나믹 프로그래밍
*/
#include <iostream>
using namespace std;

int floor_cnt;
int floor_score[301];
int dp[301];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> floor_cnt;

    for (int i = 1; i <= floor_cnt; i++) {
        cin >> floor_score[i];
    }

    dp[1] = floor_score[1];
    dp[2] = floor_score[1] + floor_score[2];
    for (int i = 3; i <= floor_cnt; i++) {
        dp[i] = max(dp[i - 2] + floor_score[i], dp[i - 3] + floor_score[i - 1] + floor_score[i]);
    }

    cout << dp[floor_cnt];
}
