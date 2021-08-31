/*
* 백준 11729번 하노이 탑 이동 순서
* https://www.acmicpc.net/problem/11729
* 재귀
*/
#include <iostream>
using namespace std;

int n, k;
int dp[101];

void go(int cnt, int from, int by, int to) {
    if (cnt == 1) {
        cout << from << " " << to << "\n";
    }
    else {
        go(cnt - 1, from, to, by);
        cout << from << " " << to << "\n";
        go(cnt - 1, by, from, to);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = (2 * dp[i - 1]) + 1;
    }
    cout << dp[n] << "\n";
    go(n, 1, 2, 3);
    return 0;
}