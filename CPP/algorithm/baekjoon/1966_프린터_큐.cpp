/*
*/
#include <iostream>
#include <queue>
using namespace std;

int t;
int n;
int want_idx;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> t;
    while (t--) {
        priority_queue<int, vector<int>, less<int>> pq;
        queue<pair<int, int>> q;
        int result = 0;
        cin >> n >> want_idx;

        int input;
        for (int i = 0; i < n; i++) {
            cin >> input;
            pq.push(input);
            q.push({ input, i });
        }

        for (int i = 1; i <= n; i++) {
            while (q.front().first != pq.top()) {
                pair<int, int> tmp = q.front();
                q.pop();
                q.push(tmp);
            }
            pq.pop();
            pair<int, int> tmp = q.front();
            q.pop();
            result++;
            if (tmp.second == want_idx) { break; }
        }

        cout << result << "\n";
    }
    return 0;
}