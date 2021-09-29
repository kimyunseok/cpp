/*
* 백준 17140번 이차원 배열과 연산
* https://www.acmicpc.net/problem/17140
* 구현 / 정렬 / 시뮬레이션
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int findR, findC, wantNum;
int row, column;
int curRow, curColumn;
vector<pair<int, int>> numVec; // 첫번째 등장횟수, 두번째 수
int numCnt[101][101];
int board[101][101];
int ans;

void columnSort(int columnIdx) { // 행정렬
    memset(numCnt[columnIdx], 0, sizeof(numCnt[columnIdx]));
    numVec.clear();

    for (int i = 1; i <= row; i++) {
        int num = board[columnIdx][i];
        numCnt[columnIdx][num]++;
    }

    for (int i = 1; i <= 100; i++) {
        if (numCnt[columnIdx][i] != 0) {
            numVec.push_back({ numCnt[columnIdx][i], i });
        }
        board[columnIdx][i] = 0;
    }

    sort(numVec.begin(), numVec.end());

    int rowIdx = 1;
    for (pair<int, int> p : numVec) {
        int cnt = p.first;
        int num = p.second;
        board[columnIdx][rowIdx++] = num;
        board[columnIdx][rowIdx++] = cnt;
        if (rowIdx > 100) { break; }
    }

    curRow = max(curRow, rowIdx - 1);
}

void rowSort(int rowIdx) { // 열정렬
    memset(numCnt[rowIdx], 0, sizeof(numCnt[rowIdx]));
    numVec.clear();

    for (int i = 1; i <= column; i++) {
        int num = board[i][rowIdx];
        numCnt[rowIdx][num]++;
    }

    for (int i = 1; i <= 100; i++) {
        if (numCnt[rowIdx][i] != 0) {
            numVec.push_back({ numCnt[rowIdx][i], i });
        }
        board[i][rowIdx] = 0;
    }

    sort(numVec.begin(), numVec.end());

    int columnIdx = 1;
    for (pair<int, int> p : numVec) {
        int cnt = p.first;
        int num = p.second;
        board[columnIdx++][rowIdx] = num;
        board[columnIdx++][rowIdx] = cnt;
        if (columnIdx > 100) { break; }
    }

    curColumn = max(curColumn, columnIdx - 1);
}

void go(int idx) {
    if (board[findR][findC] == wantNum) { ans = idx; return; }
    if (idx >= 100) { return; }

    if (column >= row) {
        curRow = 0;
        for (int i = 1; i <= column; i++) {
            columnSort(i);
        }
        row = curRow;

    }
    else {
        curColumn = 0;
        for (int i = 1; i <= row; i++) {
            rowSort(i);
        }
        column = curColumn;

    }

    go(idx + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> findR >> findC >> wantNum;

    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            cin >> board[i][j];
        }
    }

    column = 3;
    row = 3;

    go(0);

    if (board[findR][findC] == wantNum) { cout << ans; }
    else { cout << "-1"; }

    return 0;
}