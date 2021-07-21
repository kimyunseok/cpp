/*
* 백준 1002번 터렛
* https://www.acmicpc.net/problem/1002
* 수학 / 기하학
*/
#include <iostream>
#include <math.h>
using namespace std;

int test_case;
double x_1, x_2, y_1, y_2;
int r_1, r_2;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> test_case;

    while (test_case--) {
        int x_dist = 0;
        int y_dist = 0;
        double point_dist = 0;

        int radius_sub = 0;
        int radius_sum = 0;
        cin >> x_1 >> y_1 >> r_1 >> x_2 >> y_2 >> r_2;

        if (x_1 > x_2) {
            x_dist = pow((x_1 - x_2), 2);
        }
        else {
            x_dist = pow((x_2 - x_1), 2);
        }

        if (y_1 > y_2) {
            y_dist = pow((y_1 - y_2), 2);
        }
        else {
            y_dist = pow((y_2 - y_1), 2);
        }

        point_dist = sqrt(x_dist + y_dist);

        if (r_1 > r_2) {
            radius_sub = r_1 - r_2;
        }
        else {
            radius_sub = r_2 - r_1;
        }
        radius_sum = r_1 + r_2;

        if (x_1 == x_2 && y_1 == y_2) {
            if (r_1 == r_2) { cout << -1 << "\n"; }
            else { cout << 0 << "\n"; }
        }
        else if (point_dist < radius_sub) {
            cout << 0 << "\n";
        }
        else if (point_dist == radius_sub) {
            cout << 1 << "\n";
        }
        else if (point_dist < radius_sum) {
            cout << 2 << "\n";
        }
        else if (point_dist == radius_sum) {
            cout << 1 << "\n";
        }
        else {
            cout << 0 << "\n";
        }
    }

    return 0;
}