/*
* ¹éÁØ 14891¹ø Åé´Ï¹ÙÄû
* https://www.acmicpc.net/problem/14891
* ±¸Çö / ½Ã¹Ä·¹ÀÌ¼Ç
*/
#include <iostream>
#include <cstring>
using namespace std;

int gear[5][8];
bool isSpin[5];
int gearSpinDirection[5];
int spinCnt;
int spinGearNum, spinDirection;
int answer;

void spinReverseClockDirection(int gearNum) {
    int zero = gear[gearNum][0];
    for (int i = 0; i < 7; i++) {
        gear[gearNum][i] = gear[gearNum][i + 1];
    }
    gear[gearNum][7] = zero;
}

void spinClockDirection(int gearNum) {
    int last = gear[gearNum][7];
    int prev = gear[gearNum][0];
    for (int i = 1; i <= 7; i++) {
        int tmp = gear[gearNum][i];
        gear[gearNum][i] = prev;
        prev = tmp;
    }
    gear[gearNum][0] = last;
}

void checkSpin(int gearNum, int direction) {
    int leftGearNum = gearNum - 1;
    int rightGearNum = gearNum + 1;
    int reverseDirection = (direction == 1) ? -1 : 1;

    if (leftGearNum >= 1 && !isSpin[leftGearNum] && gear[leftGearNum][2] != gear[gearNum][6]) {
        isSpin[leftGearNum] = true;
        gearSpinDirection[leftGearNum] = reverseDirection;
        checkSpin(leftGearNum, reverseDirection);
    }

    if (rightGearNum <= 4 && !isSpin[rightGearNum] && gear[rightGearNum][6] != gear[gearNum][2]) {
        isSpin[rightGearNum] = true;
        gearSpinDirection[rightGearNum] = reverseDirection;
        checkSpin(rightGearNum, reverseDirection);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string input;
    for (int i = 1; i <= 4; i++) {
        cin >> input;
        for (int j = 0; j < input.length(); j++) {
            gear[i][j] = input[j] - '0';
        }
    }

    cin >> spinCnt;

    while (spinCnt--) {
        memset(isSpin, false, sizeof(isSpin));

        cin >> spinGearNum >> spinDirection;

        isSpin[spinGearNum] = true;
        gearSpinDirection[spinGearNum] = spinDirection;

        checkSpin(spinGearNum, spinDirection);

        for (int i = 1; i <= 4; i++) {
            if (isSpin[i]) {
                if (gearSpinDirection[i] == 1) {
                    spinClockDirection(i);
                }
                else {
                    spinReverseClockDirection(i);
                }
            }
        }
    }

    if (gear[1][0] == 1) { answer++; }
    if (gear[2][0] == 1) { answer += 2; }
    if (gear[3][0] == 1) { answer += 4; }
    if (gear[4][0] == 1) { answer += 8; }

    cout << answer;

    return 0;
}