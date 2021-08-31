/*
* 백준 11403번 경로 찾기
* https://www.acmicpc.net/problem/11403
* 그래프 탐색 이론
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int vertex;
vector<int> adjList[101];
int check[101][101];

void bfs(int startVertex) {
    queue<int> q;
    q.push(startVertex);
    while (!q.empty()) {
        int curVertex = q.front();
        q.pop();
        for (int adjVertex : adjList[curVertex]) {
            if (check[startVertex][adjVertex] == 0) {
                check[startVertex][adjVertex] = 1;
                q.push(adjVertex);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> vertex;

    int input;
    for (int i = 1; i <= vertex; i++) {
        for (int j = 1; j <= vertex; j++) {
            cin >> input;
            if (input == 1) {
                adjList[i].push_back(j);
            }
        }
    }

    for (int i = 1; i <= vertex; i++) {
        bfs(i);
    }

    for (int i = 1; i <= vertex; i++) {
        for (int j = 1; j <= vertex; j++) {
            cout << check[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}