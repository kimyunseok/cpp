/*
* 백준 5430번 AC
* https://www.acmicpc.net/problem/5430
* 구현 / 문자열 / 파싱 / 자료구조 - 덱
*/
#include <iostream>
#include <deque>

using namespace std;
deque<int> deq;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int tc;
    cin >> tc;
    while (tc--) {
        int numCnt;
        string cmd;
        string numArrStr;
        bool dirIsFront = true;
        bool errorOccur = false;
        cin >> cmd;
        cin >> numCnt;
        cin >> numArrStr;

        int curNum = -1;
        for (int i = 1; i < numArrStr.length(); i++) {
            if (numArrStr[i] >= '0' && numArrStr[i] <= '9') {
                if (curNum == -1) { curNum = 0; }
                curNum *= 10;
                curNum += (numArrStr[i] - '0');
            }
            else if (curNum != -1) {
                deq.push_back(curNum);
                curNum = -1;
            }
        }

        for (int i = 0; i < cmd.length(); i++) {
            if (cmd[i] == 'R') {
                dirIsFront = !dirIsFront;
            }
            else {
                if (deq.empty()) {
                    errorOccur = true;
                    break;
                }

                if (dirIsFront) {
                    deq.pop_front();
                }
                else {
                    deq.pop_back();
                }
            }
        }

        if (errorOccur) {
            cout << "error\n";
        }
        else {
            cout << "[";
            while (!deq.empty()) {
                int num = 0;
                if (dirIsFront) {
                    num = deq.front();
                    deq.pop_front();
                }
                else {
                    num = deq.back();
                    deq.pop_back();
                }
                cout << num;

                if (!deq.empty()) { cout << ","; }
            }
            cout << "]\n";
        }
    }

    return 0;
}