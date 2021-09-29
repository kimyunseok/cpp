/*
* 백준 1074번 Z
* https://www.acmicpc.net/problem/1074
* 재귀 / 분할 정복
*/
#include <iostream>
#include <math.h>
using namespace std;

int n, r, c;
int cnt = 0;
int ans;

void solution(int y, int x, int size) {
    if (y <= r && r < y + size && x <= c && c < x + size) {
        if (size == 2) {
            for (int i = y; i < y + 2; i++) {
                for (int j = x; j < x + 2; j++) {
                    if (r == i && c == j) {
                        ans = cnt;
                    }
                    cnt++;
                }
            }
        }
        else {
            solution(y, x, size / 2);
            solution(y, x + size / 2, size / 2);
            solution(y + size / 2, x, size / 2);
            solution(y + size / 2, x + size / 2, size / 2);
        }
    }
    else {
        cnt += (size * size);
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> r >> c;

    solution(0, 0, pow(2, n));

    cout << ans;

    return 0;
}