/*
* 백준 9465번 스티커
* https://www.acmicpc.net/problem/9465
* 다이나믹 프로그래밍
*/
#include <iostream>
#include <algorithm>
using namespace std;

int testCaseNum, width;
int sticker[3][100001];
int dp[3][100001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> testCaseNum;
    while (testCaseNum--) {
        int result = 0;
        cin >> width;
        for (int i = 1; i <= 2; i++) {
            for (int j = 1; j <= width; j++) {
                cin >> sticker[i][j];
            }
        }
        dp[1][1] = sticker[1][1];
        dp[2][1] = sticker[2][1];
        dp[1][2] = sticker[2][1] + sticker[1][2];
        dp[2][2] = sticker[1][1] + sticker[2][2];

        result = max(dp[1][2], dp[2][2]);

        for (int i = 3; i <= width; i++) {
            dp[1][i] = max(dp[2][i - 1], dp[2][i - 2]) + sticker[1][i];
            dp[2][i] = max(dp[1][i - 1], dp[1][i - 2]) + sticker[2][i];

            result = max(result, max(dp[1][i], dp[2][i]));
        }
        cout << result << "\n";
    }

    return 0;
}