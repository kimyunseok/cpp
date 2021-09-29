/*
* 백준 11660번 구간 합 구하기 5
* https://www.acmicpc.net/problem/11660
* 다이나믹 프로그래밍 / 누적 합
*/
#include <iostream>
using namespace std;

int widthHeight, sumCnt;
int arr[1025][1025];
int dp[1025][1025];
int pointX1, pointY1, pointX2, pointY2;
int ans;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> widthHeight >> sumCnt;

    for (int i = 1; i <= widthHeight; i++) {
        for (int j = 1; j <= widthHeight; j++) {
            cin >> arr[i][j];
            //if (i == 1 && j == 1) {
            //    dp[i][j] = arr[i][j];
            //}
            //else if (j == 1) {
            //    dp[i][j] = dp[i - 1][j] + arr[i][j];
            //}
            //else {
            //    dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + arr[i][j];
            //}
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + arr[i][j];
        }
    }

    while (sumCnt--) {
        cin >> pointX1 >> pointY1 >> pointX2 >> pointY2;

        ans = 0;

        int topMinus = dp[pointX1 - 1][pointY2];
        int leftMinus = dp[pointX2][pointY1 - 1];
        int preventTwiceMinutNum = dp[pointX1 - 1][pointY1 - 1];

        ans = dp[pointX2][pointY2] - topMinus - leftMinus + preventTwiceMinutNum;

        cout << ans << "\n";
    }

    return 0;
}