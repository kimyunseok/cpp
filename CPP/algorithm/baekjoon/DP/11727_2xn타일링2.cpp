/*
* 백준 11727번 2xn 타일링2
* https://www.acmicpc.net/problem/11727
* 다이나믹 프로그래밍
*/
#include <iostream>
using namespace std;

int n;
int dp[1001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;
    dp[1] = 1;
    dp[2] = 3;
    for (int i = 3; i <= n; i++) {
        dp[i] = (dp[i - 1] + (2 * dp[i - 2])) % 10007;
    }


    cout << dp[n];

    return 0;
}