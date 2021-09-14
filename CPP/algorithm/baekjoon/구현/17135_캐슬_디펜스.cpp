/*
* 백준 17135번 캐슬 디펜스
* https://www.acmicpc.net/problem/17135
* 구현 / 시뮬레이션 / 브루트포스 알고리즘
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

class EnemyForArcher {
public:
    int r;
    int c;
    int distance;
    EnemyForArcher(int r, int c, int distance) {
        this->r = r;
        this->c = c;
        this->distance = distance;
    }
};

int height, width, maxAttackDistance;
vector<pair<int, int>> archerVec; // i - 1부터 시작한다.
vector<pair<int, int>> enemyPointVec;
int board[17][16]; // 높이 + 1이 궁수의 위치, 따라서 16이 높이가 될 수 있다.
int boardForGame[17][16];
vector<EnemyForArcher> enemyInfoVec[4]; //궁수가 적의 좌표를 보고 거리와 좌표를 담아두는 벡터.
int ans;

bool comp(EnemyForArcher e1, EnemyForArcher e2) {
    if (e1.distance < e2.distance) {
        return true;
    }
    else if (e1.distance == e2.distance) {
        if (e1.c < e2.c) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

void saveEnemyInfo(int archerIdx, int r, int c) {
    for (pair<int, int> enemyPoint : enemyPointVec) {
        int enemyR = enemyPoint.first;
        int enemyC = enemyPoint.second;
        int distance = abs(r - enemyR) + abs(c - enemyC);

        enemyInfoVec[archerIdx].push_back(EnemyForArcher(enemyR, enemyC, distance));
    }
    sort(enemyInfoVec[archerIdx].begin(), enemyInfoVec[archerIdx].end(), comp);
}

void startGame() {
    int enemyCnt = enemyPointVec.size();
    int killCnt = 0;
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            boardForGame[i][j] = board[i][j];
        }
    }

    for (int i = 1; i <= 3; i++) {
        enemyInfoVec[i].clear();
        int archerC = archerVec[i - 1].second;
        saveEnemyInfo(i, height + 1, archerC);
    }

    while (enemyCnt > 0) {
        // 1. 궁수가 거리 D 이하 & 가장 왼쪽 & 가장 가까운 적 공격
        for (int i = 1; i <= 3; i++) {
            for (int j = 0; j < enemyInfoVec[i].size(); j++) {
                int enemyDistance = enemyInfoVec[i][j].distance;
                int enemyR = enemyInfoVec[i][j].r;
                int enemyC = enemyInfoVec[i][j].c;
                int curState = boardForGame[enemyR][enemyC];

                if (enemyDistance > maxAttackDistance) { break; }
                else {
                    if (curState == 1) {
                        killCnt++;
                        enemyCnt--;
                        boardForGame[enemyR][enemyC] = 0;
                    }
                    break; // 동시공격이므로,
                }
            }
        }

        // 2 - 1. 적 아래로 한 칸 이동(격자)
        for (int i = height; i >= 0; i--) { // 범위를 0까지 해야 1높이에 있는 적의 정보가 사라질 수 있다.
            for (int j = 1; j <= width; j++) {
                if (i == height) {
                    if (boardForGame[i][j] == 1) {
                        enemyCnt--; // 적 N + 1로 와서 게임에서 제외.
                    }
                }
                else {
                    boardForGame[i + 1][j] = boardForGame[i][j]; // 아래 칸으로 이동시킴.
                }
            }
        }

        // 2 - 2. 적 아래로 한 칸 이동(좌표 저장 벡터)
        for (int i = 1; i <= 3; i++) {
            for (int j = 0; j < enemyInfoVec[i].size(); j++) {
                int enemyDistance = enemyInfoVec[i][j].distance;
                int enemyR = enemyInfoVec[i][j].r;
                int enemyC = enemyInfoVec[i][j].c;
                int nxtR = enemyR + 1;
                int curState = boardForGame[nxtR][enemyC];

                if (enemyR + 1 > height || curState == 0) {
                    // 아래로 한 칸 이동했을 때, height보다 크다면 벡터에서 뺀다.
                    enemyInfoVec[i].erase(enemyInfoVec[i].begin() + j);
                    j--; // 벡터 사이즈가 1줄어들었으므로, j를 증가시키지 않는다.
                    continue;
                }

                enemyInfoVec[i][j].r = nxtR;

                //거리 새로 계산해줌.
                int archerR = archerVec[i - 1].first;
                int archerC = archerVec[i - 1].second;
                enemyInfoVec[i][j].distance = abs(archerR - (enemyR + 1)) + abs(archerC - enemyC);
            }
            sort(enemyInfoVec[i].begin(), enemyInfoVec[i].end(), comp);
        }

    }
    ans = max(ans, killCnt);
}

void setArcher(int startArcherPoint) {
    if (archerVec.size() >= 3) {
        startGame();
        return;
    }
    else {
        int archerIdx = archerVec.size() + 1;
        for (int i = startArcherPoint; i <= width; i++) {
            archerVec.push_back({ height + 1, i });
            setArcher(i + 1);
            archerVec.pop_back();
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> height >> width >> maxAttackDistance;

    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            cin >> board[i][j];
            if (board[i][j] == 1) {
                enemyPointVec.push_back({ i, j });
            }
        }
    }

    setArcher(1);

    cout << ans;

    return 0;
}