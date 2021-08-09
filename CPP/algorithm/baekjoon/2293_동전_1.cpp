/*
* 백준 2293번 동전 1
* https://www.acmicpc.net/problem/2293
* 다이나믹 프로그래밍
*/
#include <iostream>
using namespace std;

int n, k;
int value[101];
int dp[10001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> k;

    int input;
    for (int i = 1; i <= n; i++) {
        cin >> input;
        value[i] = input;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = value[i]; j <= k; j++) {
            if (j == value[i]) {
                dp[j] = dp[j] + 1;
            }
            else {
                dp[j] = dp[j] + dp[j - value[i]];
            }
        }
    }

    cout << dp[k];

    return 0;
}