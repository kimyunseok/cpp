/*
* 백준 17825번 주사위 윷놀이
* https://www.acmicpc.net/problem/17825
* 구현 / 시뮬레이션
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Horse {
    bool beforeIsBlue = false;
    int curNum = 0;
};

vector<Horse> horseVec(4);
vector<int> diceNumVec;
int diceNumFrom10[8] = {
    -1, 13, 16, 19, 25, 30, 35, 40
};
int diceNumFrom20[7] = {
    -1, 22, 24, 25, 30, 35, 40
};
int diceNumFrom30[8] = {
    -1, 28, 27, 26, 25, 30, 35, 40
};
bool isVisit[41][2]; // 두번째 0 : 그냥 , 두번째 1 : 전에 파란칸
int result;

void checkMaxScore(int startIdx, int cnt, int curScore) {
    //cout << cnt << " , " << curScore << "\n";
    //for (int i = 0; i < 4; i++) {
    //    cout << horseVec[i].curNum << " ";
    //}
    //cout << "\n\n";

    if (cnt >= 10) {
        //cout << curScore << "\n";
        //for (int i = 0; i < 4; i++) {
        //    cout << horseVec[i].curNum << " ";
        //}
        //cout << "\n\n";

        result = max(result, curScore);
    }
    else {
        for (int i = startIdx; i < 10; i++) {
            int curDiceNum = diceNumVec[i];
            for (int j = 0; j < 4; j++) {
                if (horseVec[j].curNum == 41) continue;

                if (horseVec[j].curNum == 10) {
                    if (!isVisit[diceNumFrom10[curDiceNum]][1]) {
                        int saveNum = horseVec[j].curNum;
                        isVisit[saveNum][0] = false;
                        isVisit[diceNumFrom10[curDiceNum]][1] = true;
                        horseVec[j].beforeIsBlue = true;
                        horseVec[j].curNum = diceNumFrom10[curDiceNum];
                        checkMaxScore(i + 1, cnt + 1, curScore + diceNumFrom10[curDiceNum]);
                        isVisit[saveNum][0] = true;
                        isVisit[diceNumFrom10[curDiceNum]][1] = false;
                        horseVec[j].beforeIsBlue = false;
                        horseVec[j].curNum = saveNum;
                    }
                }
                else if (horseVec[j].curNum == 13 && horseVec[j].beforeIsBlue) {
                    if (!isVisit[diceNumFrom10[curDiceNum + 1]][1]) {
                        int saveNum = horseVec[j].curNum;
                        horseVec[j].curNum = diceNumFrom10[curDiceNum + 1];
                        isVisit[saveNum][1] = false;
                        isVisit[diceNumFrom10[curDiceNum + 1]][1] = true;
                        checkMaxScore(i + 1, cnt + 1, curScore + diceNumFrom10[curDiceNum + 1]);
                        isVisit[diceNumFrom10[curDiceNum + 1]][1] = false;
                        isVisit[saveNum][1] = true;
                        horseVec[j].curNum = saveNum;
                    }
                }
                else if (horseVec[j].curNum == 16 && horseVec[j].beforeIsBlue) {
                    if (!isVisit[diceNumFrom10[curDiceNum + 2]][1]) {
                        int saveNum = horseVec[j].curNum;
                        horseVec[j].curNum = diceNumFrom10[curDiceNum + 2];
                        isVisit[diceNumFrom10[curDiceNum + 2]][1] = true;
                        isVisit[saveNum][1] = false;
                        checkMaxScore(i + 1, cnt + 1, curScore + diceNumFrom10[curDiceNum + 2]);
                        isVisit[diceNumFrom10[curDiceNum + 2]][1] = false;
                        isVisit[saveNum][1] = true;
                        horseVec[j].curNum = saveNum;
                    }

                }
                else if (horseVec[j].curNum == 19 && horseVec[j].beforeIsBlue) {
                    if (curDiceNum < 5) {

                        if (!isVisit[diceNumFrom10[curDiceNum + 3]][1]) {
                            int saveNum = horseVec[j].curNum;
                            horseVec[j].curNum = diceNumFrom10[curDiceNum + 3];
                            isVisit[diceNumFrom10[curDiceNum + 3]][1] = true;
                            isVisit[saveNum][1] = false;
                            checkMaxScore(i + 1, cnt + 1, curScore + diceNumFrom10[curDiceNum + 3]);
                            isVisit[diceNumFrom10[curDiceNum + 3]][1] = false;
                            isVisit[saveNum][1] = true;
                            horseVec[j].curNum = saveNum;
                        }

                    }
                    else {
                        horseVec[j].curNum = 41;
                        isVisit[19][1] = false;
                        checkMaxScore(i + 1, cnt + 1, curScore);
                        isVisit[19][1] = true;
                        horseVec[j].curNum = 19;
                    }
                }
                else if (horseVec[j].curNum == 20) {

                    if (!isVisit[diceNumFrom20[curDiceNum]][1]) {
                        int saveNum = horseVec[j].curNum;
                        horseVec[j].curNum = diceNumFrom20[curDiceNum];
                        isVisit[diceNumFrom20[curDiceNum]][1] = true;
                        isVisit[saveNum][0] = false;
                        horseVec[j].beforeIsBlue = true;
                        checkMaxScore(i + 1, cnt + 1, curScore + diceNumFrom20[curDiceNum]);
                        isVisit[diceNumFrom20[curDiceNum]][1] = false;
                        isVisit[saveNum][0] = true;
                        horseVec[j].beforeIsBlue = false;
                        horseVec[j].curNum = saveNum;
                    }

                }
                else if (horseVec[j].curNum == 22 && horseVec[j].beforeIsBlue) {

                    if (!isVisit[diceNumFrom20[curDiceNum + 1]][1]) {
                        int saveNum = horseVec[j].curNum;
                        horseVec[j].curNum = diceNumFrom20[curDiceNum + 1];
                        isVisit[saveNum][1] = false;
                        isVisit[diceNumFrom20[curDiceNum + 1]][1] = true;
                        checkMaxScore(i + 1, cnt + 1, curScore + diceNumFrom20[curDiceNum + 1]);
                        isVisit[diceNumFrom20[curDiceNum + 1]][1] = false;
                        isVisit[saveNum][1] = true;
                        horseVec[j].curNum = saveNum;
                    }

                }
                else if (horseVec[j].curNum == 24 && horseVec[j].beforeIsBlue) {
                    if (curDiceNum < 5) {
                        if (!isVisit[diceNumFrom20[curDiceNum + 2]][1]) {
                            int saveNum = horseVec[j].curNum;
                            horseVec[j].curNum = diceNumFrom20[curDiceNum + 2];
                            isVisit[diceNumFrom20[curDiceNum + 2]][1] = true;
                            isVisit[saveNum][1] = false;
                            checkMaxScore(i + 1, cnt + 1, curScore + diceNumFrom20[curDiceNum + 2]);
                            isVisit[diceNumFrom20[curDiceNum + 2]][1] = false;
                            isVisit[saveNum][1] = true;
                            horseVec[j].curNum = saveNum;
                        }
                    }
                    else {
                        horseVec[j].curNum = 41;
                        isVisit[24][1] = false;
                        checkMaxScore(i + 1, cnt + 1, curScore);
                        isVisit[24][1] = true;
                        horseVec[j].curNum = 24;
                    }
                }
                else if (horseVec[j].curNum == 28 && horseVec[j].beforeIsBlue) {
                    if (!isVisit[diceNumFrom30[curDiceNum + 1]][1]) {
                        int saveNum = horseVec[j].curNum;
                        horseVec[j].curNum = diceNumFrom30[curDiceNum + 1];
                        isVisit[diceNumFrom30[curDiceNum + 1]][1] = true;
                        isVisit[saveNum][1] = false;
                        checkMaxScore(i + 1, cnt + 1, curScore + diceNumFrom30[curDiceNum + 1]);
                        isVisit[diceNumFrom30[curDiceNum + 1]][1] = false;
                        isVisit[saveNum][1] = true;
                        horseVec[j].curNum = saveNum;
                    }
                }
                else if (horseVec[j].curNum == 27 && horseVec[j].beforeIsBlue) {
                
                    if (!isVisit[diceNumFrom30[curDiceNum + 2]][1]) {
                        int saveNum = horseVec[j].curNum;
                        horseVec[j].curNum = diceNumFrom30[curDiceNum + 2];
                        isVisit[diceNumFrom30[curDiceNum + 2]][1] = true;
                        isVisit[saveNum][1] = false;
                        checkMaxScore(i + 1, cnt + 1, curScore + diceNumFrom30[curDiceNum + 2]);
                        isVisit[diceNumFrom30[curDiceNum + 2]][1] = false;
                        isVisit[saveNum][1] = true;
                        horseVec[j].curNum = saveNum;
                    }
                }
                else if (horseVec[j].curNum == 26 && horseVec[j].beforeIsBlue) {
                    if (curDiceNum < 5) {
                        if (!isVisit[diceNumFrom30[curDiceNum + 3]][1]) {
                            int saveNum = horseVec[j].curNum;
                            horseVec[j].curNum = diceNumFrom30[curDiceNum + 3];
                            isVisit[diceNumFrom30[curDiceNum + 3]][1] = true;
                            isVisit[saveNum][1] = false;
                            checkMaxScore(i + 1, cnt + 1, curScore + diceNumFrom30[curDiceNum + 3]);
                            isVisit[diceNumFrom30[curDiceNum + 3]][1] = false;
                            isVisit[saveNum][1] = true;
                            horseVec[j].curNum = saveNum;
                        }
                    }
                    else {
                        horseVec[j].curNum = 41;
                        isVisit[26][1] = false;
                        checkMaxScore(i + 1, cnt + 1, curScore);
                        isVisit[26][1] = true;
                        horseVec[j].curNum = 26;
                    }
                }
                else if (horseVec[j].curNum == 30 && !horseVec[j].beforeIsBlue) {
                    
                    if (!isVisit[diceNumFrom30[curDiceNum]][1]) {
                        int saveNum = horseVec[j].curNum;
                        horseVec[j].curNum = diceNumFrom30[curDiceNum];
                        horseVec[j].beforeIsBlue = true;
                        isVisit[diceNumFrom30[curDiceNum]][1] = true;
                        isVisit[saveNum][0] = false;
                        checkMaxScore(i + 1, cnt + 1, curScore + diceNumFrom30[curDiceNum]);
                        horseVec[j].beforeIsBlue = false;
                        isVisit[diceNumFrom30[curDiceNum]][1] = false;
                        isVisit[saveNum][0] = true;
                        horseVec[j].curNum = saveNum;
                    }

                }
                else if (horseVec[j].curNum == 40) {
                    horseVec[j].curNum = 41;
                    isVisit[40][1] = false;
                    checkMaxScore(i + 1, cnt + 1, curScore);
                    isVisit[40][1] = true;
                    horseVec[j].curNum = 40;
                }
                else if (horseVec[j].curNum == 25) {
                    if (curDiceNum < 4) {
                        if (!isVisit[diceNumFrom30[curDiceNum + 4]][1]) {
                            int saveNum = horseVec[j].curNum;
                            horseVec[j].curNum = diceNumFrom30[curDiceNum + 4];
                            isVisit[diceNumFrom30[curDiceNum + 4]][1] = true;
                            isVisit[saveNum][1] = false;
                            checkMaxScore(i + 1, cnt + 1, curScore + diceNumFrom30[curDiceNum + 4]);
                            isVisit[diceNumFrom30[curDiceNum + 4]][1] = false;
                            isVisit[saveNum][1] = true;
                            horseVec[j].curNum = saveNum;
                        }
                    }
                    else {
                        horseVec[j].curNum = 41;
                        isVisit[25][1] = false;
                        checkMaxScore(i + 1, cnt + 1, curScore);
                        isVisit[25][1] = true;
                        horseVec[j].curNum = 25;
                    }
                }
                else if (horseVec[j].curNum == 30 && horseVec[j].beforeIsBlue) {
                    if (curDiceNum < 3) {

                        if (!isVisit[diceNumFrom30[curDiceNum + 5]][1]) {
                            int saveNum = horseVec[j].curNum;
                            horseVec[j].curNum = diceNumFrom30[curDiceNum + 5];
                            isVisit[diceNumFrom30[curDiceNum + 5]][1] = true;
                            isVisit[saveNum][1] = false;
                            checkMaxScore(i + 1, cnt + 1, curScore + diceNumFrom30[curDiceNum + 5]);
                            isVisit[diceNumFrom30[curDiceNum + 5]][1] = false;
                            isVisit[saveNum][1] = true;
                            horseVec[j].curNum = saveNum;
                        }
                    }
                    else {
                        horseVec[j].curNum = 41;
                        isVisit[30][1] = false;
                        checkMaxScore(i + 1, cnt + 1, curScore);
                        isVisit[30][1] = true;
                        horseVec[j].curNum = 30;
                    }
                }
                else if (horseVec[j].curNum == 35) {
                    if (curDiceNum < 2) {
                        if (!isVisit[diceNumFrom30[curDiceNum + 6]][1]) {
                            int saveNum = horseVec[j].curNum;
                            horseVec[j].curNum = diceNumFrom30[curDiceNum + 6];
                            isVisit[diceNumFrom30[curDiceNum + 6]][1] = true;
                            isVisit[saveNum][1] = false;
                            checkMaxScore(i + 1, cnt + 1, curScore + diceNumFrom30[curDiceNum + 6]);
                            isVisit[diceNumFrom30[curDiceNum + 6]][1] = false;
                            isVisit[saveNum][1] = true;
                            horseVec[j].curNum = saveNum;
                        }
                    }
                    else {
                        horseVec[j].curNum = 41;
                        isVisit[35][1] = false;
                        checkMaxScore(i + 1, cnt + 1, curScore);
                        isVisit[35][1] = true;
                        horseVec[j].curNum = 35;
                    }
                }
                else {

                if (horseVec[j].curNum + (curDiceNum * 2) == 40) {

                    if (!isVisit[horseVec[j].curNum + (curDiceNum * 2)][1]) {
                        isVisit[horseVec[j].curNum][0] = false;
                        horseVec[j].curNum += (curDiceNum * 2);
                        isVisit[horseVec[j].curNum][1] = true;
                        checkMaxScore(i + 1, cnt + 1, curScore + horseVec[j].curNum);
                        isVisit[horseVec[j].curNum][1] = false;
                        horseVec[j].curNum -= (curDiceNum * 2);
                        isVisit[horseVec[j].curNum][0] = true;
                    }
                }
                else if (horseVec[j].curNum + (curDiceNum * 2) > 40) {
                    int saveNum = horseVec[j].curNum;
                    isVisit[horseVec[j].curNum][0] = false;
                    horseVec[j].curNum = 41;
                    checkMaxScore(i + 1, cnt + 1, curScore);
                    horseVec[j].curNum = saveNum;
                    isVisit[horseVec[j].curNum][0] = true;
                }
                else {
                    if (!isVisit[horseVec[j].curNum + (curDiceNum * 2)][0]) {
                        isVisit[horseVec[j].curNum][0] = false;
                        horseVec[j].curNum += (curDiceNum * 2);
                        isVisit[horseVec[j].curNum][0] = true;
                        checkMaxScore(i + 1, cnt + 1, curScore + horseVec[j].curNum);
                        isVisit[horseVec[j].curNum][0] = false;
                        horseVec[j].curNum -= (curDiceNum * 2);
                        isVisit[horseVec[j].curNum][0] = true;
                    }
                }

                }
            }
        }
    }
}

int main() {

    int input;
    for (int i = 1; i <= 10; i++) {
        cin >> input;
        diceNumVec.push_back(input);
    }

    checkMaxScore(0, 0, 0);

    cout << result;

    return 0;

}