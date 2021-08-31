/*
* 백준 11057번 오르막 수
* https://www.acmicpc.net/problem/11057
* 다이나믹 프로그래밍
*/
#include <iostream>
using namespace std;

int n;
long long dp[1001][10];
long long result;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;
    for (int i = 0; i <= 9; i++) {
        dp[1][i] = 1;
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= 9; j++) {
            for (int k = 0; k <= j; k++) {
                dp[i][j] = (dp[i][j] + dp[i - 1][k]) % 10007;
            }
        }
    }

    for (int i = 0; i <= 9; i++) {
        result = (result + dp[n][i]) % 10007;
    }
    cout << result;
    return 0;
}