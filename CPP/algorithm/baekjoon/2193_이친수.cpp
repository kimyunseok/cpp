/*
* 백준 2193번 이친수
* https://www.acmicpc.net/problem/2193
* 다이나믹 프로그래밍
*/
#include <iostream>
using namespace std;

int n;
long long dp[91];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    dp[1] = 1;
    dp[2] = 1;

    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    cout << dp[n];
}