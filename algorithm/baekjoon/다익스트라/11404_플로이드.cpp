/*
* 백준 11404번 플로이드
* https://www.acmicpc.net/problem/11404
* 그래프 이론 : 플로이드 - 와샬
* 다익스트라를 사용해서 풀었음.
*/
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int vertexCnt, edgeCnt;
int answer[101][101];
bool visit[101];
vector<pair<int, int>> adjList[101];

void solve(int findNum) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({ 0, findNum });
    while (!pq.empty()) {
        int curCost = pq.top().first;
        int curNum = pq.top().second;
        pq.pop();

        if (visit[curNum]) { continue; } // 이미 방문했다는 뜻은, 최소값이 갱신됐다는 뜻임.

        visit[curNum] = true;
        answer[findNum][curNum] = curCost;

        for (int i = 0; i < adjList[curNum].size(); i++) {
            int nxtCost = curCost + adjList[curNum][i].first;
            int nxtNum = adjList[curNum][i].second;
            if (!visit[nxtNum] && nxtCost < answer[findNum][nxtNum]) {
                answer[findNum][nxtNum] = nxtCost;
                pq.push({ nxtCost, nxtNum });
            }
        }
    }
}

void setMaxAndClearVisit(int idx) {
    for (int i = 1; i <= vertexCnt; i++) {
        answer[idx][i] = 100000000; // 100,000 * 100을 가게되면 10,000,000이 최대가 될 수 있다.
        visit[i] = false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> vertexCnt >> edgeCnt;

    for (int i = 1; i <= edgeCnt; i++) {
        int vertex1, vertex2, cost;
        cin >> vertex1 >> vertex2 >> cost;
        adjList[vertex1].push_back({ cost, vertex2 });
    }

    for (int i = 1; i <= vertexCnt; i++) {
        setMaxAndClearVisit(i);
        solve(i);
    }

    for (int i = 1; i <= vertexCnt; i++) {
        for (int j = 1; j <= vertexCnt; j++) {
            if (answer[i][j] == 100000000) { answer[i][j] = 0; }
            cout << answer[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}