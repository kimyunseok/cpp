/*
* 백준 1912번 연속합
* https://www.acmicpc.net/problem/1912
* 다이나믹 프로그래밍
*/
#include <iostream>
#include <algorithm>
using namespace std;

int n;
int arr[100001];
int dp[100001];
int result;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;


    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    dp[1] = arr[1];
    result = dp[1];
    for (int i = 2; i <= n; i++) {
        dp[i] = max(dp[i - 1] + arr[i], arr[i]);
        result = result < dp[i] ? dp[i] : result;
    }

    cout << result;
}