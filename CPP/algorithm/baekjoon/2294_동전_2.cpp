/*
* 백준 2294번 동전 2
* https://www.acmicpc.net/problem/2294
* 다이나믹 프로그래밍
*/
#include <iostream>
using namespace std;

int coinCnt, wantSum;
int coin[101];
int dp[101][100001];
int result = 100001;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> coinCnt >> wantSum;

    for (int i = 1; i <= coinCnt; i++) {
        for (int j = 1; j <= wantSum; j++) {
            dp[i][j] = 100001;
        }
    }

    for (int i = 1; i <= coinCnt; i++) {
        cin >> coin[i];
    }

    for (int i = coin[1]; i <= wantSum; i += coin[1]) {
        dp[1][i] = i / coin[1];
    }

    for (int i = 2; i <= coinCnt; i++) {
        int addCoin = coin[i];

        for (int j = 1; j < addCoin; j++) {
            dp[i][j] = dp[i - 1][j];
        }

        for (int j = addCoin; j <= wantSum; j++) {
            if (j == addCoin) { dp[i][j] = 1; }
            else {
                dp[i][j] = min(dp[i - 1][j], min(dp[i - 1][j - addCoin] + 1, dp[i][j - addCoin] + 1));
            }
        }
    }

    for (int i = 1; i <= coinCnt; i++) {
        if (dp[i][wantSum] != 100001) {
            result = min(result, dp[i][wantSum]);
        }
    }

    if (result == 100001) {
        cout << "-1";
    }
    else {
        cout << result;
    }

    return 0;
}