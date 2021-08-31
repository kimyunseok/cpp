/*
* 백준 2003번 수들의 합 2
* https://www.acmicpc.net/problem/2003
* 투 포인터
*/
#include <iostream>
using namespace std;

int numCnt, findNum;
int arr[10001];
int result;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> numCnt >> findNum;

    for (int i = 1; i <= numCnt; i++) {
        cin >> arr[i];
    }

    int startIdx = 1;
    int endIdx = 1;
    int sum = 0;

    while (startIdx <= endIdx) {
        if (sum >= findNum) {
            sum -= arr[startIdx++];
        }
        else if (endIdx > numCnt) { break; }
        else if (sum < findNum) {
            sum += arr[endIdx++];
        }
        if (sum == findNum) { result++; }
    }
    cout << result;

    return 0;
}

//DP 풀이
//#include <iostream>
//using namespace std;
//
//int numCnt, findNum;
//int num[10001];
//int dp[10001];
//int result;
//
//int main() {
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
//    cout.tie(NULL);
//
//    cin >> numCnt >> findNum;
//
//    int input;
//    for (int i = 1; i <= numCnt; i++) {
//        cin >> input;
//        num[i] = input;
//        dp[i] = input;
//        if (num[i] == findNum) { result++; }
//    }
//
//    for (int i = 1; i <= numCnt; i++) {
//        for (int j = 1; j <= numCnt; j++) {
//            if (j + i > numCnt) { break; }
//            dp[j] = dp[j] + num[j + i];
//            if (dp[j] == findNum) { result++; }
//        }
//    }
//
//    cout << result;
//
//    return 0;
//}