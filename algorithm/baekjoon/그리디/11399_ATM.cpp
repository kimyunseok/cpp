/*
* 백준 11399번 ATM
* https://www.acmicpc.net/problem/11399
* 그리디 알고리즘, 정렬
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> per_minute;
int dp[1001];
int result;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;

    per_minute.push_back(0);
    for (int i = 1; i <= n; i++) {
        int input;
        cin >> input;
        per_minute.push_back(input);
    }

    sort(per_minute.begin(), per_minute.end());

    for (int i = 1; i <= n; i++) {
        dp[i] += dp[i - 1] + per_minute[i];
        result += dp[i];
    }
    cout << result;
}
