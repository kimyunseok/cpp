/*
* 백준 1003번 피보나치 함수
* https://www.acmicpc.net/problem/1003
* 다이나믹 프로그래밍
*/
#include <iostream>
using namespace std;

int test_case;
int n;
pair<int, int> dp[41];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> test_case;
    dp[0] = { 1, 0 };
    dp[1] = { 0, 1 };
    while (test_case--) {
        cin >> n;
        for (int i = 2; i <= n; i++) {
            dp[i].first = dp[i - 1].first + dp[i - 2].first;
            dp[i].second = dp[i - 1].second + dp[i - 2].second;
        }

        cout << dp[n].first << " " << dp[n].second << "\n";
    }
}
