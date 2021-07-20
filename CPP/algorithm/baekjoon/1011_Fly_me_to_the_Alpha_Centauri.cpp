/*
* 백준 1011번 Fly me to the Alpha Centauri
* https://www.acmicpc.net/problem/1011
* 수학
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

int t;
long long x, y;

long long findDistanceByStep(long long step) {
    long long distance = 0;
    if (step % 2 == 0) {
        distance = ((step / 2) * ((step / 2) + 1)) / 2;
        distance *= 2;
    }
    else {
        distance = ((step / 2) * ((step / 2) + 1)) / 2;
        distance *= 2;
        distance += ((step / 2) + 1);
    }
    return distance;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> t;
    while (t--) {
        cin >> x >> y;
        long long distance = y - x;
        long long step = 1;
        while (distance > findDistanceByStep(step)) {
            step++;
        }
        cout << step << "\n";
    }
    return 0;
}