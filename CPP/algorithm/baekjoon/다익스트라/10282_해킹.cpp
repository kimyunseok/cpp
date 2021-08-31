/*
* 백준 10282번 해킹
* https://www.acmicpc.net/problem/10282
* 다익스트라
*/
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

vector<vector<pair<int, int>>> adj(10001);
int test_case;
int com_cnt, adj_num, start_num;
int infested_num;
int max_cost = 0;
int com_cost[10001];
bool visit[10001];

void dijikstra(int com_num) {
    com_cost[com_num] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, com_num });
    while (!pq.empty()) {
        int cur_num = pq.top().second;
        int cur_cost = pq.top().first;
        pq.pop();

        if (visit[cur_num]) { continue; }

        visit[cur_num] = true;
        infested_num++;
        if (max_cost < cur_cost) {
            max_cost = cur_cost;
        }
        for (int i = 0; i < adj[cur_num].size(); i++) {
            int nxt_num = adj[cur_num][i].second;
            int nxt_cost = adj[cur_num][i].first;
            if (com_cost[nxt_num] > cur_cost + nxt_cost) {
                com_cost[nxt_num] = cur_cost + nxt_cost;
                pq.push({ com_cost[nxt_num], nxt_num });
            }
        }

    }
}

void init() {
    infested_num = 0;
    max_cost = 0;
    for (int i = 0; i < 10001; i++) {
        com_cost[i] = 1e10;
        visit[i] = false;
        adj[i].clear();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> test_case;
    while (test_case--) {
        init();

        cin >> com_cnt >> adj_num >> start_num;

        for (int i = 1; i <= adj_num; i++) {
            int com_num1, com_num2, cost;
            cin >> com_num1 >> com_num2 >> cost;
            adj[com_num2].push_back({ cost, com_num1 });
        }

        dijikstra(start_num);

        cout << infested_num << " " << max_cost << "\n";
    }

    return 0;
}