/*
* 백준 1920번 수 찾기
* https://www.acmicpc.net/problem/1920
* 이분 탐색
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> v;
int n, m;
int tmp;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> tmp;
        v.push_back(tmp);
    }
    sort(v.begin(), v.end());

    cin >> m;
    for (int i = 1; i <= m; i++) {
        cin >> tmp;
        if (binary_search(v.begin(), v.end(), tmp)) {
            cout << "1\n";
        }
        else {
            cout << "0\n";
        }
    }
    return 0;
}