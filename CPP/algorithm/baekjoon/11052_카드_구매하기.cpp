/*
* 백준 11052번 카드 구매하기
* https://www.acmicpc.net/problem/11052
* 다이나믹 프로그래밍
*/
#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> vec;
int dp[1001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;

    vec.push_back(0);

    int tmp;
    for (int i = 1; i <= n; i++) {
        cin >> tmp;
        vec.push_back(tmp);
    }

    dp[1] = vec[1];


    for (int i = 2; i <= n; i++) {
        dp[i] = vec[i];
        for (int j = 1; j < i; j++) {
            dp[i] = dp[i] < dp[i - j] + dp[j] ? dp[i - j] + dp[j] : dp[i];
        }
    }

    cout << dp[n];
    return 0;
}