/*
* 백준 1904번 01타일
* https://www.acmicpc.net/problem/1904
* 다이나믹 프로그래밍
*/
#include <iostream>
#include <vector>
using namespace std;

int n;
vector<long long> vec;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    vec.push_back(0);
    vec.push_back(1);
    vec.push_back(2);
    cin >> n;
    for (int i = 3; i <= n; i++) {
        vec.push_back((vec[i - 1] + vec[i - 2]) % 15746);
    }

    cout << vec[n];

    return 0;
}