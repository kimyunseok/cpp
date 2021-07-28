/*
* 백준 1697번 숨바꼭질
* https://www.acmicpc.net/problem/1697
* 그래프 탐색 이론
*/
#include <iostream>
#include <queue>
using namespace std;

int n, k;
int visit[100001];
int result = 100000;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> k;
    queue<pair<int, int>> q;
    q.push({ n, 0 });
    visit[n] = true;
    while (!q.empty()) {
        int cur_num = q.front().first;
        int cur_pass = q.front().second;
        q.pop();
        if (cur_num == k) {
            result = result > cur_pass ? cur_pass : result;
        }
        else {
            if (cur_num - 1 >= 0 && !visit[cur_num - 1]) {
                q.push({ cur_num - 1, cur_pass + 1 });
                visit[cur_num - 1] = true;
            }
            if (cur_num + 1 < 100001 && !visit[cur_num + 1]) {
                q.push({ cur_num + 1, cur_pass + 1 });
                visit[cur_num + 1] = true;
            }
            if (cur_num * 2 < 100001 && !visit[2 * cur_num]) {
                q.push({ 2 * cur_num, cur_pass + 1 });
                visit[2 * cur_num] = true;
            }
        }
    }
    cout << result;
}