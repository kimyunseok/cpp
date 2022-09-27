/*
* 백준 16637번 괄호 추가하기
* https://www.acmicpc.net/problem/16637
* - 브루트포스 알고리즘
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int len;
vector<char> originalVec;
vector<char> checkVec;
long long result = -10000000000;

void go(bool alreadyAdd, int currentIdx, int putCnt) {

    if (putCnt >= len) {

        long long current = 0;
        char prev = '+';

        //for (int i = 0; i < checkVec.size(); i++) {
        //    cout << checkVec[i];
        //}
        //cout << " = " << current << "\n\n";

        for (int i = 0; i < checkVec.size(); i += 2) {
            int check = 0;
            if (checkVec[i] == '(') {
                int check2 = checkVec[i + 1] - '0';
                char type = checkVec[i + 2];
                int check3 = checkVec[i + 3] - '0';

                if (type == '+') {
                    check = check2 + check3;
                }
                else if (type == '-') {
                    check = check2 - check3;
                }
                else if (type == '*') {
                    check = check2 * check3;
                }

                i += 4;
            }
            else {
                check = checkVec[i] - '0';
            }
            //cout << i << " : " << current << prev << check << "\n";

            if (prev == '+') {
                current += check;
            }
            else if (prev == '-') {
                current -= check;
            }
            else if (prev == '*') {
                current *= check;
            }

            if (i != checkVec.size() - 1) prev = checkVec[i + 1];
        }

        result = max(result, current);
    }
    else {
        if (!alreadyAdd && currentIdx != len - 1) {
            checkVec.push_back('(');
            checkVec.push_back(originalVec[currentIdx]);
            checkVec.push_back(originalVec[currentIdx + 1]);
            go(true, currentIdx + 2, putCnt + 2);
            checkVec.pop_back();
            checkVec.pop_back();
            checkVec.pop_back();
        }
        else if (alreadyAdd) {
            checkVec.push_back(originalVec[currentIdx]);
            checkVec.push_back(')');
            if (currentIdx != len - 1) checkVec.push_back(originalVec[currentIdx + 1]);
            go(false, currentIdx + 2, putCnt + 2);
            if (currentIdx != len - 1) checkVec.pop_back();
            checkVec.pop_back();
            checkVec.pop_back();
        }
        
        if (!alreadyAdd) {
            checkVec.push_back(originalVec[currentIdx]);
            if (currentIdx != len - 1) checkVec.push_back(originalVec[currentIdx + 1]);
            go(false, currentIdx + 2, putCnt + 2);
            if (currentIdx != len - 1) checkVec.pop_back();
            checkVec.pop_back();
        }
    }
}

int main() {

    cin >> len;

    char input;
    for (int i = 0; i < len; i++) {
        cin >> input;
        originalVec.push_back(input);
    }

    go(false, 0, 0);

    cout << result;

    return 0;

}