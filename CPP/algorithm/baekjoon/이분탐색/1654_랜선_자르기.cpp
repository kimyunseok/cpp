/*
* 백준 1654번 랜선 자르기
* https://www.acmicpc.net/problem/1654
* 이분 탐색
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int num, need;
int result = 1;
vector<int> vec;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> num >> need;

    int input = 0;
    for (int i = 1; i <= num; i++) {
        cin >> input;
        vec.push_back(input);
    }

    sort(vec.begin(), vec.end());

    long long front = 1;
    long long tail = vec[num - 1];
    while (front <= tail) {
        long long middle = (front + tail) / 2;
        int cur_num = 0;
        for (int i = 0; i < num; i++) {
            cur_num = cur_num + (vec[i] / middle);
        }
        if (cur_num < need) {
            tail = middle - 1;
        }
        else {
            result = result < middle ? middle : result;
            front = middle + 1;
        }
    }

    cout << result;

    return 0;
}