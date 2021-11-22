/*
* 백준 15663번 N과 M(9)
* https://www.acmicpc.net/problem/15663
* 백트래킹
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
int numCnt[10001];
int inputNumCnt[10001];
vector<int> vec;
vector<int> outputVec;

void go(int idx) {
    if (idx > m) {
        for (int i = 0; i < outputVec.size(); i++) {
            cout << outputVec[i] << " ";
        }
        cout << "\n";
        return;
    }
    else {
        for (int i = 0; i < n; i++) {
            if (i > 0 && vec[i] == vec[i - 1]) {
                continue;
            }
            int curNum = vec[i];
            if (inputNumCnt[curNum] + 1 > numCnt[curNum]) {
                continue;
            }

            inputNumCnt[curNum]++;
            outputVec.push_back(curNum);
            go(idx + 1);
            outputVec.pop_back();
            inputNumCnt[curNum]--;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;

    int input;
    for (int i = 1; i <= n; i++) {
        cin >> input;
        numCnt[input]++;
        vec.push_back(input);
    }

    sort(vec.begin(), vec.end());

    go(1);

    return 0;
}