/*
* 백준 2667번 단지번호붙이기
* https://www.acmicpc.net/problem/2667
* 그래프 이론
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n;
int map[26][26];
int house_count;
bool visit[26][26];
vector<int> house_vec;

void dfs(int x, int y) {
    if (x < 1 || x > n || y < 1 || y > n || map[x][y] == 0 || visit[x][y]) { return; }
    visit[x][y] = true;
    house_count++;

    dfs(x - 1, y);
    dfs(x + 1, y);
    dfs(x, y + 1);
    dfs(x, y - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;

    string input;
    for (int i = 1; i <= n; i++) {
        cin >> input;
        for (int j = 1; j <= n; j++) {
            map[i][j] = input[j - 1] - '0';
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (map[i][j] == 1 && !visit[i][j]) {
                dfs(i, j);
                house_vec.push_back(house_count);
                house_count = 0;
            }
        }
    }

    sort(house_vec.begin(), house_vec.end());

    cout << house_vec.size() << "\n";

    for (int i : house_vec) {
        cout << i << "\n";
    }
}
