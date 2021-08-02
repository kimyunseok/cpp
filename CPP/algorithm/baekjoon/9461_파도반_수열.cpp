/*
* 백준 9461번 파도반 수열
* https://www.acmicpc.net/problem/9461
* 다이나믹 프로그래밍
*/
#include <iostream>
using namespace std;

int t, n;
long long dp[101];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> t;
    while (t--) {
        cin >> n;
        dp[1] = 1;
        dp[2] = 1;
        dp[3] = 1;
        for (int i = 4; i <= n; i++) {
            dp[i] = dp[i - 2] + dp[i - 3];
        }

        cout << dp[n] << "\n";
    }

    return 0;
}