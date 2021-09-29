/*
* 백준 2156번 포도주 시식
* https://www.acmicpc.net/problem/2156
* 다이나믹 프로그래밍
*/
#include <iostream>
#include <algorithm>
using namespace std;

int n, result;
int wine[10001];
int dp[10001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> wine[i];
    }

    dp[1] = wine[1];
    dp[2] = wine[1] + wine[2];
    result = dp[2];
    for (int i = 3; i <= n; i++) {
        dp[i] = max(max(dp[i - 2], dp[i - 3] + wine[i - 1]), dp[i - 4] + wine[i - 1]) + wine[i];
        result = result < dp[i] ? dp[i] : result;
    }

    cout << result;
}