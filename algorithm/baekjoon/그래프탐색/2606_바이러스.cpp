/*
* 백준 2606번 바이러스
* https://www.acmicpc.net/problem/2606
* 그래프 탐색 이론
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int vertex_cnt;
int edge_cnt;
vector<int> adj_list[101];
bool visit[101];
int result;

void bfs() {
    queue<int> q;
    q.push(1);
    visit[1] = true;
    while (!q.empty()) {
        int cur_vertex = q.front();
        q.pop();
        for (int i = 0; i < adj_list[cur_vertex].size(); i++) {
            int nxt_vertex = adj_list[cur_vertex][i];
            if (!visit[nxt_vertex]) {
                visit[nxt_vertex] = true;
                q.push(nxt_vertex);
                result++;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> vertex_cnt >> edge_cnt;

    int vertex_1, vertex_2;
    for (int i = 1; i <= edge_cnt; i++) {
        cin >> vertex_1 >> vertex_2;
        adj_list[vertex_1].push_back(vertex_2);
        adj_list[vertex_2].push_back(vertex_1);
    }

    bfs();
    cout << result;
}
