/*
* 백준 1260번 DFS와 BFS
* https://www.acmicpc.net/problem/1260
* 그래프 탐색
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int vertex_cnt, edge_cnt, start_vertex_num;
vector<int> adj_list[1001]; // (1001)과 [1001]은 다르다.
bool visit_dfs[1001];
bool visit_bfs[1001];

void dfs(int cur_vertex_num) {
    cout << cur_vertex_num << " ";
    visit_dfs[cur_vertex_num] = true;
    for (int vertex : adj_list[cur_vertex_num]) {
        if (!visit_dfs[vertex]) {
            dfs(vertex);
        }
    }
}

void bfs(int start_vertex_num) {
    queue<int> q; // 
    q.push(start_vertex_num);
    visit_bfs[start_vertex_num] = true;
    while (!q.empty()) {
        int cur_vertex_num = q.front();
        q.pop();
        cout << cur_vertex_num << " ";
        for (int vertex : adj_list[cur_vertex_num]) {
            if (!visit_bfs[vertex]) {
                visit_bfs[vertex] = true;
                q.push(vertex);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> vertex_cnt >> edge_cnt >> start_vertex_num;

    for (int i = 1; i <= edge_cnt; i++) {
        int source, dest;
        cin >> source >> dest;
        adj_list[source].push_back(dest);
        adj_list[dest].push_back(source);
    }

    for (int i = 1; i <= vertex_cnt; i++) {
        sort(adj_list[i].begin(), adj_list[i].end());
    }

    dfs(start_vertex_num);
    cout << "\n";
    bfs(start_vertex_num);

    return 0;
}