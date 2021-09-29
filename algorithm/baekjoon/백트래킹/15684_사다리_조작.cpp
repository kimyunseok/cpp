/*
* 백준 15684번 사다리 조작
* https://www.acmicpc.net/problem/15684
* 구현 / 브루트포스 / 백트래킹
*/
#include <iostream>
using namespace std;

int verticalLines, horizontalLines, maxHorizontal;
bool isConnected[31][11][2]; // [높이][선][0] : 앞(-1), [높이][선][1] : 뒤(+1)
int ans = 4;

bool checkAlreadyConnect(int height, int point) {
    return (isConnected[height][point][0] || isConnected[height][point][1]);
}

bool findCanAns() {
    for (int i = 1; i <= verticalLines; i++) {
        int curPoint = i;
        for (int j = 1; j <= maxHorizontal; j++) {
            int frontPoint = curPoint - 1;
            int backPoint = curPoint + 1;
            if (isConnected[j][curPoint][0]) {
                curPoint = frontPoint;
            }
            else if (isConnected[j][curPoint][1]) {
                curPoint = backPoint;
            }
        }
        if (curPoint != i) { return false; }
    }
    return true;
}

// 중복을 제거하기 위해 시작하는 세로선과 시작하는 가로선의 높이을 입력받는다.
void go(int idx, int startVerticalNum, int startHorizontalHeight) {
    if (idx > ans) { return; } //가지치기, 살펴보는 idx가 ans보다 크다면 return. 필수요소는 아님.

    if (findCanAns()) {
        //해당 idx번째까지 가로선을 넣었을 때, 사다리의 i가 모두 i로 간다면 ans값 갱신.
        //더 살펴볼 필요가 없으므로 return
        ans = min(ans, idx);
        return;
    }
    if (idx == 3) { return; } // idx가 이미 3번째라면 4번째 idx는 필요없으므로 return

    int vertical = startVerticalNum; // 시작하는 verticalLine
    int horizontalHeight = startHorizontalHeight; // 시작하는 높이.
    if (horizontalHeight > maxHorizontal) {
        // 높이를 이전 높이의 +1로 해주므로 범위를 넘지 않았는지 check한다.
        horizontalHeight = 1;
        vertical++;
    }
    while (vertical <= verticalLines) {
        int backPoint = vertical + 1; // 현재 탐색하는 수직선의 뒤에있는(+1) 수직선

        if (backPoint <= verticalLines && !checkAlreadyConnect(horizontalHeight, backPoint)) {
            //뒤에있는 수직선이 범위 내에 있고, 현재 높이에서 앞, 뒤에 가로선이 없다면 연결
            isConnected[horizontalHeight][vertical][1] = true;
            isConnected[horizontalHeight][backPoint][0] = true;
            go(idx + 1, vertical, horizontalHeight + 1); //연결한 후 다음 idx를 찾으러 간다.

            //return했을 때, 연결을 해제시켜준다.
            isConnected[horizontalHeight][vertical][1] = false;
            isConnected[horizontalHeight][backPoint][0] = false;
        }


        horizontalHeight++; //다음 높이를 살펴본다
        if (horizontalHeight > maxHorizontal) {
            //높이가 범위를 넘지 않았는지 check.
            //범위를 넘었다면 다음 수직선을 살펴본다.
            horizontalHeight = 1;
            vertical++;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> verticalLines >> horizontalLines >> maxHorizontal;

    int height, number;
    for (int i = 1; i <= horizontalLines; i++) {
        //number와 number + 1을 연결. number의 뒤, number + 1의 앞 연결
        cin >> height >> number;
        isConnected[height][number][1] = true;
        isConnected[height][number + 1][0] = true;
    }

    go(0, 1, 1);

    if (ans == 4) {
        cout << "-1";
    }
    else {
        cout << ans;
    }

    return 0;
}