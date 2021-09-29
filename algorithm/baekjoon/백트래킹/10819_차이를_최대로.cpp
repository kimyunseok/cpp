/*
* 백준 10819번 차이를 최대로
* https://www.acmicpc.net/problem/10819
* 백트래킹
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

int numCnt;
int arr[9];
bool visit[9];
vector<int> vec;
int answer;

void go(int idx) {
    if (idx > numCnt) {
        int sum = 0;
        for (int i = 0; i < vec.size() - 1; i++) {
            sum = sum + abs(vec[i] - vec[i + 1]);
        }
        answer = max(answer, sum);
        return;
    }
    else {
        for (int i = 1; i <= numCnt; i++) {
            if (!visit[i]) {
                visit[i] = true;
                vec.push_back(arr[i]);
                go(idx + 1);
                vec.pop_back();
                visit[i] = false;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> numCnt;

    for (int i = 1; i <= numCnt; i++) {
        cin >> arr[i];
    }

    for (int i = 1; i <= numCnt; i++) {
        visit[i] = true;
        vec.push_back(arr[i]);
        go(2);
        vec.pop_back();
        visit[i] = false;
    }

    cout << answer;

    return 0;
}