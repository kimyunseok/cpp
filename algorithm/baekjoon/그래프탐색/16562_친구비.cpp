/*
* 백준 16562번 친구비
* https://www.acmicpc.net/problem/16562
* 그래프 탐색
*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int studentCnt, friendCnt, money;
vector<vector<int>> adjFriendVec(10001);
int needMoney[10001];
bool visit[10001];
bool canAllFriend = true;
int ans = 0;

int findMinMoney(int startNum) {
    visit[startNum] = true;
    int minMoney = needMoney[startNum];
    queue<int> q;
    q.push(startNum);
    while (!q.empty()) {
        int num = q.front();
        q.pop();
        
        if (minMoney > needMoney[num]) {
            minMoney = needMoney[num];
        }

        for (int nxtNum : adjFriendVec[num]) {
            if (!visit[nxtNum]) {
                q.push(nxtNum);
                visit[nxtNum] = true;
            }
        }
    }
    return minMoney;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> studentCnt >> friendCnt >> money;

    int input;
    for (int i = 1; i <= studentCnt; i++) {
        cin >> input;
        needMoney[i] = input;
    }

    int f1, f2;
    for (int i = 0; i < friendCnt; i++) {
        cin >> f1 >> f2;
        adjFriendVec[f1].push_back(f2);
        adjFriendVec[f2].push_back(f1);
    }

    for (int i = 1; i <= studentCnt; i++) {
        if (!visit[i]) {
            int friendMinMoney = findMinMoney(i);

            if (friendMinMoney > money) { canAllFriend = false; break; }
            ans += friendMinMoney;
            money -= friendMinMoney;
        }
    }

    if (canAllFriend) {
        cout << ans;
    }
    else {
        cout << "Oh no";
    }

    return 0;
}