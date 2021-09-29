/*
* 백준 15683번 감시
* https://www.acmicpc.net/problem/15683
* 구현 / 시뮬레이션 / 브루트포스
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int height, width;
int office[9][9];
int ans;
vector<pair<int, pair<int, int>>> cctvVec;

pair<int, int> direction[4] = {
    {-1, 0}, //상
    {0, 1}, //우
    {1, 0}, //하
    {0, -1} //좌
};

void cctvSetChecked(int y, int x, int dir) {
    if (y < 1 || y > height || x < 1 || x > width) { return; }
    if (office[y][x] == 6) { return; }
    if (1 <= office[y][x] && office[y][x] <= 5) {
        cctvSetChecked(y + direction[dir].first, x + direction[dir].second, dir);
    }
    else if (office[y][x] == 0) {
        office[y][x] = 9;
        cctvSetChecked(y + direction[dir].first, x + direction[dir].second, dir);
    }
    else if (office[y][x] >= 9) {
        office[y][x]++;
        cctvSetChecked(y + direction[dir].first, x + direction[dir].second, dir);
    }
}

void cctvSetUnChecked(int y, int x, int dir) {
    if (y < 1 || y > height || x < 1 || x > width) { return; }
    if (office[y][x] == 6) { return; }
    if (1 <= office[y][x] && office[y][x] <= 5) {
        cctvSetUnChecked(y + direction[dir].first, x + direction[dir].second, dir);
    }
    else if (office[y][x] == 9) {
        office[y][x] = 0;
        cctvSetUnChecked(y + direction[dir].first, x + direction[dir].second, dir);
    }
    else if (office[y][x] >= 9) {
        office[y][x]--;
        cctvSetUnChecked(y + direction[dir].first, x + direction[dir].second, dir);
    }
}

void solve(int idx) {
    if (idx >= cctvVec.size()) {
        int curEmpty = 0;
        for (int i = 1; i <= height; i++) {
            for (int j = 1; j <= width; j++) {
                if (office[i][j] == 0) { curEmpty++; }
            }
        }
        ans = min(ans, curEmpty);
    }
    else {
        int curCCTVNum = cctvVec[idx].first;
        int curCCTVY = cctvVec[idx].second.first;
        int curCCTVX = cctvVec[idx].second.second;
        if (curCCTVNum == 1) {
            cctvSetChecked(curCCTVY, curCCTVX, 0); //1번 상방향먼저
            solve(idx + 1);
            cctvSetUnChecked(curCCTVY, curCCTVX, 0);

            cctvSetChecked(curCCTVY, curCCTVX, 1); //1번 우방향
            solve(idx + 1);
            cctvSetUnChecked(curCCTVY, curCCTVX, 1);

            cctvSetChecked(curCCTVY, curCCTVX, 2); //1번 하방향
            solve(idx + 1);
            cctvSetUnChecked(curCCTVY, curCCTVX, 2);

            cctvSetChecked(curCCTVY, curCCTVX, 3); //1번 좌방향
            solve(idx + 1);
            cctvSetUnChecked(curCCTVY, curCCTVX, 3);
        }
        else if (curCCTVNum == 2) {
            cctvSetChecked(curCCTVY, curCCTVX, 0); //상
            cctvSetChecked(curCCTVY, curCCTVX, 2); //하
            solve(idx + 1);
            cctvSetUnChecked(curCCTVY, curCCTVX, 0);
            cctvSetUnChecked(curCCTVY, curCCTVX, 2);

            cctvSetChecked(curCCTVY, curCCTVX, 1); //우
            cctvSetChecked(curCCTVY, curCCTVX, 3); //좌
            solve(idx + 1);
            cctvSetUnChecked(curCCTVY, curCCTVX, 1);
            cctvSetUnChecked(curCCTVY, curCCTVX, 3);
        }
        else if (curCCTVNum == 3) {
            cctvSetChecked(curCCTVY, curCCTVX, 0); //상
            cctvSetChecked(curCCTVY, curCCTVX, 1); //우
            solve(idx + 1);
            cctvSetUnChecked(curCCTVY, curCCTVX, 0);
            cctvSetUnChecked(curCCTVY, curCCTVX, 1);

            cctvSetChecked(curCCTVY, curCCTVX, 1); //우
            cctvSetChecked(curCCTVY, curCCTVX, 2); //하
            solve(idx + 1);
            cctvSetUnChecked(curCCTVY, curCCTVX, 1);
            cctvSetUnChecked(curCCTVY, curCCTVX, 2);

            cctvSetChecked(curCCTVY, curCCTVX, 2); //하
            cctvSetChecked(curCCTVY, curCCTVX, 3); //좌
            solve(idx + 1);
            cctvSetUnChecked(curCCTVY, curCCTVX, 2);
            cctvSetUnChecked(curCCTVY, curCCTVX, 3);

            cctvSetChecked(curCCTVY, curCCTVX, 3); //좌
            cctvSetChecked(curCCTVY, curCCTVX, 0); //상
            solve(idx + 1);
            cctvSetUnChecked(curCCTVY, curCCTVX, 3);
            cctvSetUnChecked(curCCTVY, curCCTVX, 0);
        }
        else if (curCCTVNum == 4) {
            cctvSetChecked(curCCTVY, curCCTVX, 3); //좌
            cctvSetChecked(curCCTVY, curCCTVX, 0); //상
            cctvSetChecked(curCCTVY, curCCTVX, 1); //우
            solve(idx + 1);
            cctvSetUnChecked(curCCTVY, curCCTVX, 3);
            cctvSetUnChecked(curCCTVY, curCCTVX, 0);
            cctvSetUnChecked(curCCTVY, curCCTVX, 1);

            cctvSetChecked(curCCTVY, curCCTVX, 0); //상
            cctvSetChecked(curCCTVY, curCCTVX, 1); //우
            cctvSetChecked(curCCTVY, curCCTVX, 2); //하
            solve(idx + 1);
            cctvSetUnChecked(curCCTVY, curCCTVX, 0);
            cctvSetUnChecked(curCCTVY, curCCTVX, 1);
            cctvSetUnChecked(curCCTVY, curCCTVX, 2);

            cctvSetChecked(curCCTVY, curCCTVX, 1); //우
            cctvSetChecked(curCCTVY, curCCTVX, 2); //하
            cctvSetChecked(curCCTVY, curCCTVX, 3); //좌
            solve(idx + 1);
            cctvSetUnChecked(curCCTVY, curCCTVX, 1);
            cctvSetUnChecked(curCCTVY, curCCTVX, 2);
            cctvSetUnChecked(curCCTVY, curCCTVX, 3);

            cctvSetChecked(curCCTVY, curCCTVX, 2); //하
            cctvSetChecked(curCCTVY, curCCTVX, 3); //좌
            cctvSetChecked(curCCTVY, curCCTVX, 0); //상
            solve(idx + 1);
            cctvSetUnChecked(curCCTVY, curCCTVX, 2);
            cctvSetUnChecked(curCCTVY, curCCTVX, 3);
            cctvSetUnChecked(curCCTVY, curCCTVX, 0);
        }
        else if (curCCTVNum == 5) {
            cctvSetChecked(curCCTVY, curCCTVX, 0); //상
            cctvSetChecked(curCCTVY, curCCTVX, 1); //우
            cctvSetChecked(curCCTVY, curCCTVX, 2); //하
            cctvSetChecked(curCCTVY, curCCTVX, 3); //좌
            solve(idx + 1);
            cctvSetUnChecked(curCCTVY, curCCTVX, 0);
            cctvSetUnChecked(curCCTVY, curCCTVX, 1);
            cctvSetUnChecked(curCCTVY, curCCTVX, 2);
            cctvSetUnChecked(curCCTVY, curCCTVX, 3);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> height >> width;

    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            cin >> office[i][j];
            if (1 <= office[i][j] && office[i][j] <= 5) { cctvVec.push_back({ office[i][j], {i,j} }); }
            if (office[i][j] == 0) { ans++; }
        }
    }

    solve(0);

    cout << ans;

    return 0;
}