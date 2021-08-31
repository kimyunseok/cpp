/*
* 백준 1932번 정수 삼각형
* https://www.acmicpc.net/problem/1932
* 다이나믹 프로그래밍
*/
#include <iostream>
#include <algorithm>
using namespace std;

int n;
int triangle[501][501];
int dp[501][501];
int result;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            cin >> triangle[i][j];
        }
    }
    dp[1][1] = triangle[1][1];
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            if (j == 1) {
                dp[i][j] = dp[i - 1][j] + triangle[i][j];
            }
            else if (j == i) {
                dp[i][j] = dp[i - 1][j - 1] + triangle[i][j];
            }
            else {
                dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j];
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        result = max(dp[n][i], result);
    }
    cout << result;
}