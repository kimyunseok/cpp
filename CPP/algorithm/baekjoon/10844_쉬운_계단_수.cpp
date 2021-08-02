/*
* 백준 10844번 쉬운 계단 수
* https://www.acmicpc.net/problem/10844ㅁ
* 다이나믹 프로그래밍
*/
#include <iostream>
using namespace std;

int n;
long long dp[101][10];
long long result;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;

    for (int i = 1; i <= 9; i++) {
        dp[1][i] = 1;
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= 9; j++) {
            if (j == 0) {
                dp[i][j] = dp[i - 1][j + 1] % 1000000000;
            }
            else if (j == 9) {
                dp[i][j] = dp[i - 1][j - 1] % 1000000000;
            }
            else {
                dp[i][j] = (dp[i - 1][j + 1] + dp[i - 1][j - 1]) % 1000000000;
            }
        }
    }

    for (int i = 0; i <= 9; i++) {
        result = (result + dp[n][i]) % 1000000000;
    }

    cout << result;

    return 0;
}