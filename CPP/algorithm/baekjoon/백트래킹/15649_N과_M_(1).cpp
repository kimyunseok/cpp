/*
* 백준 15649번 N과 M (1)
* https://www.acmicpc.net/problem/15649
* 백트래킹
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<int> v;
bool check[10];
void find(int idx) {
    if (idx == m) {
        for (int i = 0; i < v.size(); i++) {
            cout << v[i] << " ";
        }
        cout << "\n";
        return;
    }
    else {
        for (int i = 1; i <= n; i++) {
            if (check[i] == false) {
                v.push_back(i);
                check[i] = true;
                find(idx + 1);
                check[i] = false;
                v.pop_back();
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        v.push_back(i);
        check[i] = true;
        find(1);
        check[i] = false;
        v.pop_back();
    }

    return 0;
}